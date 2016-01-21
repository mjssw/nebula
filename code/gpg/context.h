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
#ifndef NIC_9DB44BB0DA6C6BA2_NIC
#define NIC_9DB44BB0DA6C6BA2_NIC

#include "key.h"
#include "signature_info.h"
#include "error.h"

namespace nebula { namespace gpg { namespace detail {
/** @ingroup GPG
 * @{
 * */
//------------------------------------------------------------------------------
/** The context for gpg operations.
 *
 *  Different instances can be safely called asynchronously.
 * 
 *  @warning Don't create static instances of this types.
 * */
class n_gpg_dll context
{
public:
    context(const string &filename = "",
        const string &homedir = "");
    context(context &) = delete;
    context(const context &) = delete;
    inline context(context &&other) noexcept
    {
        ctx = other.ctx;
        other.ctx = nullptr;
    }
    ~context() noexcept;
    
    context &operator = (context &) = delete;
    context &operator = (const context &) = delete;
    inline context &operator = (context &&other) noexcept
    {
        kill();
        ctx = other.ctx;
        other.ctx = nullptr;
        return *this;
    }
    
    inline void swap(context &other) noexcept {
        foundation::swap(ctx, other.ctx);
    }
    
    tuple<vector<key>, bool> keys(
        const detail::keylist_mode::type klm,
        const string &pattern,
        const bool secret_only = false);
    inline tuple<vector<key>, bool> keys(
        const string &pattern, const bool secret_only = false)
    {
        return this->keys(keylist_mode::local, pattern, secret_only);
    }
    
    errc decrypt(
        io::stream_ref<io::in_tag, io::in_seek_tag> in,
        io::stream_ref<io::out_tag, io::out_seek_tag> out);
    errc encrypt(const vector<key> &keys,
        io::stream_ref<io::in_tag, io::in_seek_tag> in,
        io::stream_ref<io::out_tag, io::out_seek_tag> out,
        const bool ascii_armor = false);
    vector<signature_info> verify(
        io::stream_ref<io::in_tag, io::in_seek_tag> data,
        io::stream_ref<io::in_tag, io::in_seek_tag> sig);
    errc sign(const vector<key> &keys,
        io::stream_ref<io::in_tag, io::in_seek_tag> in,
        io::stream_ref<io::out_tag, io::out_seek_tag> out,
        const bool ascii_armor = false);
    
    inline gpgme_ctx_t native_handle() const noexcept {
        return ctx;
    }

private:
    void kill() noexcept;
    inline bool initialized() const noexcept { return ctx != nullptr; }
    
    void keylist_mode(const detail::keylist_mode::type x);
    detail::keylist_mode::type keylist_mode() const;
    void ascii_armor(const bool flag);
    bool ascii_armor() const;
    void text_mode(const bool flag);
    bool text_mode() const;
    
    gpgme_ctx_t ctx;
};

/** @} */

}}} // namespaces

#endif // NIC_9DB44BB0DA6C6BA2_NIC

