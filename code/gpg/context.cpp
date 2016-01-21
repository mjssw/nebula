/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2016 lis (lis@tutanota.com)
    (PGP: 0x98E65B43B03E8A6B68BA3132568ACAF1A05DE1CE)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------------<!--*/
#include "context.h"

namespace nebula { namespace gpg { namespace detail {
//------------------------------------------------------------------------------
bool init_gpgme_called = false;
//------------------------------------------------------------------------------
void init_gpgme()
{   
    if(!init_gpgme_called)
    {
        if(gpgme_check_version("1.5.1") == nullptr)
        {
            n_throw(gpg_error)
            << ei_msg_c("gpgme_check_version() failed");
        }
        
        ::gpgme_set_locale(NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));
        #ifdef LC_MESSAGES
        ::gpgme_set_locale (NULL, LC_MESSAGES, setlocale (LC_MESSAGES, NULL));
        #endif
        
        init_gpgme_called = true;
    }
}
//------------------------------------------------------------------------------
bool init_engine_called = false;
//------------------------------------------------------------------------------
void init_engine(gpgme_protocol_t proto)
{
   if(!init_engine_called)
    {
        const gpgme_error_t err = gpgme_engine_check_version(proto);
        if(GPG_ERR_NO_ERROR != err) {
            n_throw(gpg_error)
            << ei_msg_c("gpgme_engine_check_version() failed")
            << ei_gpgme_error(err);
        }
    }
    
    init_engine_called = true;
}

//------------------------------------------------------------------------------
context::context(const string &filename, const string &homedir)
: ctx(nullptr)
{
    init_gpgme();
    init_engine(GPGME_PROTOCOL_OpenPGP);
    
    gpgme_error_t err = gpgme_new(&ctx);
    
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(gpg_error)
        << ei_msg_c("gpgme_new() failed")
        << ei_gpgme_error(err);
    }
    
    auto se_kill = scope_exit([&] () {
        kill();
    });
    
    err = gpgme_ctx_set_engine_info(
        ctx,
        GPGME_PROTOCOL_OpenPGP,
        filename.empty() ? nullptr : filename.c_str(),
        homedir.empty() ? nullptr : homedir.c_str());
    
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(gpg_error)
        << ei_msg_c("gpgme_ctx_set_engine_info() failed")
        << ei_gpgme_error(err);
    }
    
    se_kill.dismiss();
}
//------------------------------------------------------------------------------
context::~context() noexcept
{
    kill();
}
//------------------------------------------------------------------------------
tuple<vector<key>, bool>
context::keys(
    const detail::keylist_mode::type klm,
    const string &pattern,
    const bool secr_only)
{
    n_assert(initialized());
    
    this->keylist_mode(klm);
    
    const gpgme_error_t err = gpgme_op_keylist_start(
        ctx,
        pattern.empty() ? nullptr : pattern.c_str(),
        secr_only ? 1 : 0);
    
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(gpg_error)
        << ei_msg_c("gpgme_op_keylist_start() failed")
        << ei_gpgme_error(err);
    }
    
    tuple<vector<key>, bool> res;
    
    {
        n_scope_exit(&) {
            gpgme_op_keylist_end(ctx);
        };
        
        gpgme_key_t i = nullptr;
        while(!gpgme_op_keylist_next(ctx, &i))
            get<0>(res).emplace_back(key(i));
        
        get<0>(res).shrink_to_fit();
    } // calling gpgme_op_keylist_end()
    
    get<1>(res) = gpgme_op_keylist_result(ctx)->truncated;
    
    return res;
}
//------------------------------------------------------------------------------
struct istream_hook
{
    io::stream_ref<io::in_tag, io::in_seek_tag> &strm;
    exception_ptr exc;
};
//------------------------------------------------------------------------------
inline gpgme_data_t make_data_t(istream_hook &h)
{   
    gpgme_data_cbs cbs
    {
        // read
        [] (void *handle, void *buffer, size_t size) -> ssize_t
        {
            istream_hook *h = static_cast<istream_hook *>(handle);
            
            try {
                const size_t n = io::read(
                    h->strm,
                    static_cast<char *>(buffer),
                    size);
                
                math::require_exact_cast<ssize_t>(n);
                return n;
            }
            catch(...)
            {
                errno = EIO;
                h->exc = current_exception();
                return -1;
            }
        },
        
        // write
        [] (void *handle, const void *buffer, size_t size) -> ssize_t
        {
            istream_hook *h = static_cast<istream_hook *>(handle);
            
            try {
                n_throw(logic_error);
            } catch(...) {
                h->exc = current_exception();
            }
            
            errno = EIO;
            return -1;
        },
        
        // seek
        [] (void *handle, off_t offset, int whence) -> off_t
        {
            istream_hook *h = static_cast<istream_hook *>(handle);
            
            try
            {
                math::require_exact_cast<io::streamoff>(offset);
                
                switch(whence)
                {
                case SEEK_CUR:
                    io::seekg_cur(h->strm, offset);
                    break;
                case SEEK_SET:
                    io::seekg_beg(h->strm, offset);
                    break;
                case SEEK_END:
                    io::seekg_end(h->strm, offset);
                    break;
                default:
                    n_throw(logic_error);
                }
                
                const io::streampos res = io::tellg(h->strm);
                math::require_exact_cast<off_t>(res);
                return res;
            }
            catch(...)
            {
                errno = EIO;
                h->exc = current_exception();
                return -1;
            }
        },
        
        // release
        [] (void *handle) -> void
        {
            // empty
        },
    };
    
    gpgme_data_t dh = nullptr;
    
    const gpgme_error_t err = gpgme_data_new_from_cbs(&dh, &cbs, &h);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(gpg_error)
        << ei_msg_c("gpgme_data_new_from_cbs() failed")
        << ei_gpgme_error(err);
    }
    
    return dh;
}
//------------------------------------------------------------------------------
struct ostream_hook
{
    io::stream_ref<io::out_tag, io::out_seek_tag> &strm;
    exception_ptr exc;
};
//------------------------------------------------------------------------------
inline gpgme_data_t make_data_t(ostream_hook &h)
{   
    gpgme_data_cbs cbs
    {
        // read
        [] (void *handle, void *buffer, size_t size) -> ssize_t
        {
            ostream_hook *h = static_cast<ostream_hook *>(handle);
            
            try {
                n_throw(logic_error);
            } catch(...) {
                h->exc = current_exception();
            }
            
            errno = EIO;
            return -1;
        },
        
        // write
        [] (void *handle, const void *buffer, size_t size) -> ssize_t
        {
            ostream_hook *h = static_cast<ostream_hook *>(handle);
            
            try {
                io::write(
                    h->strm,
                    static_cast<const char *>(buffer),
                    size);
                
                return size;
            }
            catch(...)
            {
                errno = EIO;
                h->exc = current_exception();
                return -1;
            }
        },
        
        // seek
        [] (void *handle, off_t offset, int whence) -> off_t
        {
            ostream_hook *h = static_cast<ostream_hook *>(handle);
            
            try
            {
                math::require_exact_cast<io::streamoff>(offset);
                
                switch(whence)
                {
                case SEEK_CUR:
                    io::seekp_cur(h->strm, offset);
                    break;
                case SEEK_SET:
                    io::seekp_beg(h->strm, offset);
                    break;
                case SEEK_END:
                    io::seekp_end(h->strm, offset);
                    break;
                default:
                    n_throw(logic_error);
                }
                
                const io::streampos res = io::tellp(h->strm);
                math::require_exact_cast<off_t>(res);
                return res;
            }
            catch(...)
            {
                errno = EIO;
                h->exc = current_exception();
                return -1;
            }
        },
        
        // release
        [] (void *handle) -> void
        {
            // empty
        },
    };
    
    gpgme_data_t dh = nullptr;
    
    const gpgme_error_t err = gpgme_data_new_from_cbs(&dh, &cbs, &h);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(gpg_error)
        << ei_msg_c("gpgme_data_new_from_cbs() failed")
        << ei_gpgme_error(err);
    }
    
    return dh;
}
//------------------------------------------------------------------------------
errc context::decrypt(
    io::stream_ref<io::in_tag, io::in_seek_tag> in,
    io::stream_ref<io::out_tag, io::out_seek_tag> out)
{
    n_assert(initialized());
    
    ostream_hook osh{out};
    gpgme_data_t odh = make_data_t(osh);    
    n_scope_exit(&) {
        gpgme_data_release(odh);
    };
    
    istream_hook ish{in};
    gpgme_data_t idh = make_data_t(ish);    
    n_scope_exit(&) {
        gpgme_data_release(idh);
    };
    
    const gpgme_error_t err = gpgme_op_decrypt(ctx, idh, odh);
    
    if(osh.exc)
        n_throw(gpg_error)
        << ei_exc(move(osh.exc));
    if(ish.exc)
        n_throw(gpg_error)
        << ei_exc(move(ish.exc));
    
    switch(gpgme_err_code(err))
    {
    case GPG_ERR_NO_ERROR:
    case GPG_ERR_BAD_PASSPHRASE:
    case GPG_ERR_DECRYPT_FAILED:
        return static_cast<errc>(err);
    default:
        n_throw(gpg_error)
        << ei_msg_c("gpgme_op_decrypt() failed")
        << ei_gpgme_error(err);
    }
}
//------------------------------------------------------------------------------
errc context::encrypt(const vector<key> &keys,
    io::stream_ref<io::in_tag, io::in_seek_tag> in,
    io::stream_ref<io::out_tag, io::out_seek_tag> out,
    const bool _ascii_armor)
{
    n_assert(initialized());
    
    if(keys.empty())
        n_throw(logic_error);
    
    ostream_hook osh{out};
    gpgme_data_t odh = make_data_t(osh);    
    n_scope_exit(&) {
        gpgme_data_release(odh);
    };
    
    istream_hook ish{in};
    gpgme_data_t idh = make_data_t(ish);    
    n_scope_exit(&) {
        gpgme_data_release(idh);
    };
    
    vector<gpgme_key_t> native_keys;
    native_keys.resize(keys.size()+1);
    for(size_t i = 0; i < keys.size(); ++i)
        native_keys[i] = keys[i].native_handle();
    native_keys.back() = nullptr;
    
    ascii_armor(_ascii_armor);
    
    const gpgme_error_t err = gpgme_op_encrypt(
        ctx,
        native_keys.data(),
        GPGME_ENCRYPT_ALWAYS_TRUST,
        idh,
        odh);
    
    if(osh.exc)
        n_throw(gpg_error)
        << ei_exc(move(osh.exc));
    if(ish.exc)
        n_throw(gpg_error)
        << ei_exc(move(ish.exc));
    
    switch(gpgme_err_code(err))
    {
    case GPG_ERR_NO_ERROR:
    case GPG_ERR_UNUSABLE_PUBKEY:
        return static_cast<errc>(err);
    default:
        n_throw(gpg_error)
        << ei_msg_c("gpgme_op_encrypt() failed")
        << ei_gpgme_error(err);
    }
    
    return errc::success;
}
//------------------------------------------------------------------------------
vector<signature_info> context::verify(
    io::stream_ref<io::in_tag, io::in_seek_tag> data,
    io::stream_ref<io::in_tag, io::in_seek_tag> sig)
{
    n_assert(initialized());
    
    istream_hook data_ish{data};
    gpgme_data_t data_dh = make_data_t(data_ish);    
    n_scope_exit(&) {
        gpgme_data_release(data_dh);
    };
    istream_hook sig_ish{sig};
    gpgme_data_t sig_dh = make_data_t(sig_ish);    
    n_scope_exit(&) {
        gpgme_data_release(sig_dh);
    };
    
    const gpgme_error_t err = gpgme_op_verify(ctx, sig_dh, data_dh, nullptr);
    
    if(data_ish.exc)
        n_throw(gpg_error)
        << ei_exc(move(data_ish.exc));
    if(sig_ish.exc)
        n_throw(gpg_error)
        << ei_exc(move(sig_ish.exc));
    
    if(GPG_ERR_NO_ERROR != err)
        n_throw(gpg_error)
        << ei_msg_c("gpgme_op_verify() failed")
        << ei_gpgme_error(err);
        
    gpgme_verify_result_t vres = gpgme_op_verify_result(ctx);
    
    if(!vres)
        n_throw(gpg_error)
        << ei_msg_c("gpgme_op_verify() failed")
        << ei_gpgme_error(err);
    
    gpgme_signature_t s = vres->signatures;
    vector<signature_info> r;
    
    while(s)
    {
        errc err = errc::success;
        switch(gpgme_err_code(s->status))
        {
        case GPG_ERR_NO_ERROR:
        case GPG_ERR_SIG_EXPIRED:
        case GPG_ERR_KEY_EXPIRED:
        case GPG_ERR_CERT_REVOKED:
        case GPG_ERR_BAD_SIGNATURE:
        case GPG_ERR_NO_PUBKEY:
        case GPG_ERR_GENERAL:
            err = static_cast<errc>(gpgme_err_code(s->status));
            break;
        default:
            n_throw(logic_error)
            << ei_msg_c("^o^");
        }
        
        r.emplace_back(
            err,
            s->fpr,
            s->timestamp,
            s->exp_timestamp,
            to_public_key_algorithm(s->pubkey_algo),
            to_hash_algorithm(s->hash_algo));
        
        s = s->next;
    }
    
    r.shrink_to_fit();
    
    return r;
}
//------------------------------------------------------------------------------
errc context::sign(const vector<key> &keys,
    io::stream_ref<io::in_tag, io::in_seek_tag> in,
    io::stream_ref<io::out_tag, io::out_seek_tag> out,
    const bool _ascii_armor)
{
    n_assert(initialized());
    
    if(keys.empty())
        n_throw(logic_error);
    
    n_scope_exit(&) {
        gpgme_signers_clear(ctx);
    };
    
    for(const key &k : keys)
    {
        const gpgme_error_t err = gpgme_signers_add(ctx, k.native_handle());
        if(GPG_ERR_NO_ERROR != err)
            n_throw(gpg_error)
            << ei_msg_c("gpgme_signers_add() failed")
            << ei_gpgme_error(err);
    }
    
    ostream_hook osh{out};
    gpgme_data_t odh = make_data_t(osh);    
    n_scope_exit(&) {
        gpgme_data_release(odh);
    };
    
    istream_hook ish{in};
    gpgme_data_t idh = make_data_t(ish);    
    n_scope_exit(&) {
        gpgme_data_release(idh);
    };
    
    ascii_armor(_ascii_armor);
    const gpgme_error_t err = gpgme_op_sign(
        ctx,
        idh,
        odh,
        GPGME_SIG_MODE_DETACH);
        
    if(osh.exc)
        n_throw(gpg_error)
        << ei_exc(move(osh.exc));
    if(ish.exc)
        n_throw(gpg_error)
        << ei_exc(move(ish.exc));
    
    switch(gpgme_err_code(err))
    {
    case GPG_ERR_NO_ERROR:
    case GPG_ERR_UNUSABLE_SECKEY:
    case GPG_ERR_BAD_PASSPHRASE:
        return static_cast<errc>(err);
    default:
        n_throw(gpg_error)
        << ei_msg_c("gpgme_op_sign() failed")
        << ei_gpgme_error(err);
    }
}
//------------------------------------------------------------------------------
void context::kill() noexcept
{
    if(initialized())
    {
        gpgme_release(ctx);
    }
}
//------------------------------------------------------------------------------
void context::keylist_mode(const detail::keylist_mode::type x)
{
    n_assert(initialized());
    gpgme_set_keylist_mode(ctx, x);
}
//------------------------------------------------------------------------------
detail::keylist_mode::type context::keylist_mode() const
{
    n_assert(initialized());
    return gpgme_get_keylist_mode(ctx);
}
//------------------------------------------------------------------------------
void context::ascii_armor(const bool flag)
{
    n_assert(initialized());
    gpgme_set_armor(ctx, flag ? 1 : 0);
}
//------------------------------------------------------------------------------
bool context::ascii_armor() const
{
    n_assert(initialized());
    return gpgme_get_armor(ctx) == 1 ? true : false;
}
//------------------------------------------------------------------------------
void context::text_mode(const bool flag)
{
    n_assert(initialized());
    gpgme_set_textmode(ctx, flag ? 1 : 0);
}
//------------------------------------------------------------------------------
bool context::text_mode() const
{
    n_assert(initialized());
    return gpgme_get_textmode(ctx) == 1 ? true : false;
}

}}} // namespaces

