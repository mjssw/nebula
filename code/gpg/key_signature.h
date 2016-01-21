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
#ifndef NIC_FFBB031E283D626C_NIC
#define NIC_FFBB031E283D626C_NIC

#include "defs.h"

namespace nebula { namespace gpg { namespace detail {
/** @ingroup GPG
 *  @{
 * */
//------------------------------------------------------------------------------
/** This represents a key signature.
 *
 *  @attention Lifetime is bound to the lifetime of the associated key. 
 *  @internal This only holds a pointer to the actual data which is owned by
 *  the associated key. So copy/move operations only copy the internally
 *  stored pointer.
 * */
class key_signature
{
public:
    inline void swap(key_signature &other) noexcept {
        foundation::swap(h, other.h);
    }
    
    inline bool revoked() const {
        return h->revoked;
    }
    inline bool expired() const {
        return h->expired;
    }
    inline bool exportable() const {
        return h->exportable;
    }
    
    /** This is the key ID of the key (in hexadecimal digits) used to create
     *  the signature.
     * */
    inline const_cstring keyid() const {
        return h->keyid;
    }
    
    inline chrono::seconds creation_time() const {
        return h->timestamp;
    }
    inline chrono::seconds expiration_time() const {
        return h->timestamp;
    }
    
    /** This is the main user ID of the key used to create the signature. */
    inline const_cstring user_id_str() const {
        return h->uid;
    }
    /** This is the name component of uid, if available. */
    inline const_cstring name() const {
        return h->name;
    }
    /** This is the comment component of uid, if available. */
    inline const_cstring comment() const {
        return h->comment;
    }
    /** This is the email component of uid, if available. */
    inline const_cstring email() const {
        return h->email;
    }
    
    inline detail::public_key_algorithm public_key_algorithm() const {
        return to_public_key_algorithm(h->pubkey_algo);
    }
    
    inline gpgme_key_sig_t native_handle() const noexcept {
        return h;
    }
    
private:
    inline key_signature(gpgme_key_sig_t x) noexcept
    : h(x)
    {}
    
    gpgme_key_sig_t h;
    
    friend class key_signature_iterator;
};

//------------------------------------------------------------------------------
class key_signature_iterator : public iterator::iterator_facade<
    key_signature_iterator,
    key_signature,
    iterator::forward_traversal_tag,
    iterator::readable_iterator_tag,
    key_signature,
    key_signature *,
    ptrdiff_t>
{
public:
    inline key_signature_iterator(gpgme_key_sig_t x = nullptr) noexcept
    : h(x)
    {}
    
    inline key_signature dereference() const
    {
        return key_signature(h);
    }
    
    inline void increment()
    {
        h = h->next;
    }
    
    inline bool equal(const key_signature_iterator other) const
    {
        return h == other.h;
    }

private:
    gpgme_key_sig_t h;
};

//------------------------------------------------------------------------------
using key_signature_range = range::iterator_range<key_signature_iterator>;

/** @} */

}}} // namespaces

#endif // NIC_FFBB031E283D626C_NIC

