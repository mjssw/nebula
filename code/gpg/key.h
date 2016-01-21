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
#ifndef NIC_AFDAA59EBB2AD781_NIC
#define NIC_AFDAA59EBB2AD781_NIC

#include "user_id.h"
#include "subkey.h"

namespace nebula { namespace gpg { namespace detail {
/** @ingroup GPG
 * @{
 * */
//------------------------------------------------------------------------------
/** This represents a key.
 * */
class key
{
public:
    key() = delete;
    key(const key &);
    inline key(key &&other) noexcept
    : h(other.h)
    {
        other.h = nullptr;
    }
    inline ~key() noexcept
    {
        kill();
    }
    
    key &operator = (const key &);
    key &operator = (key &&other) noexcept
    {
        kill();
        h = other.h;
        other.h = nullptr;
        return *this;
    }
    
    inline void swap(key &other) noexcept {
        foundation::swap(h, other.h);
    }
    
    inline detail::keylist_mode::type keylist_mode() const {
        return h->keylist_mode;
    }
    
    inline bool revoked() const {
        return h->revoked;
    }
    inline bool expired() const {
        return h->expired;
    }
    inline bool disabled() const {
        return h->disabled;
    }
    inline bool invalid() const {
        return h->invalid;
    }
    inline bool can_encrypt() const {
        return h->can_encrypt;
    }
    inline bool can_sign() const {
        return h->can_sign;
    }
    inline bool can_certify() const {
        return h->can_certify;
    }
    inline bool can_authenticate() const {
        return h->can_authenticate;
    }
    inline bool secret() const {
        return h->secret;
    }
    
    inline subkey_range subkeys() const {
        return subkey_range(
            subkey_iterator(h->subkeys),
            subkey_iterator());
    }
    inline user_id_range user_ids() const {
        return user_id_range(
            user_id_iterator(h->uids),
            user_id_iterator());
    }
    
    inline gpgme_key_t native_handle() const noexcept {
        return h;
    }
    
private:
    inline key(gpgme_key_t x) noexcept
    : h(x)
    {}
    
    void kill() noexcept;
    
    gpgme_key_t h;
    
    friend class context;
};

//------------------------------------------------------------------------------
inline key::key(const key &other)
: h(other.h)
{
    gpgme_key_ref(h);
}
//------------------------------------------------------------------------------
inline key &key::operator = (const key &other)
{
    kill();
    h = other.h;
    gpgme_key_ref(h);
}
//------------------------------------------------------------------------------
inline void key::kill() noexcept
{
    if(h)
    {
        gpgme_key_unref(h);
        h = nullptr;
    }
}

/** @} */

}}} // namespaces

#endif // NIC_AFDAA59EBB2AD781_NIC

