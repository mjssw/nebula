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
#ifndef NIC_F2B1097380206504_NIC
#define NIC_F2B1097380206504_NIC

#include "key_signature.h"

namespace nebula { namespace gpg { namespace detail {
/** @ingroup GPG
 * @{
 * */
//------------------------------------------------------------------------------
/** This represents a user id.
 *
 *  @attention Lifetime is bound to the lifetime of the associated key. 
 *  @internal This only holds a pointer to the actual data which is owned by
 *  the associated key. So copy/move operations only copy the internally
 *  stored pointer.
 * */
class user_id
{
public:
    inline void swap(user_id &other) noexcept {
        foundation::swap(h, other.h);
    }
    
    inline bool revoked() const {
        return h->revoked;
    }
    inline bool invalid() const {
        return h->invalid;
    }
    
    inline const_cstring user_id_string() const {
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
    
    inline key_signature_range signatures() const {
        return key_signature_range(
            key_signature_iterator(h->signatures),
            key_signature_iterator());
    }
    
    inline gpgme_user_id_t native_handle() const noexcept {
        return h;
    }
    
private:
    inline user_id(gpgme_user_id_t x) noexcept
    : h(x)
    {}
    
    gpgme_user_id_t h;
    
    friend class user_id_iterator;
};

//------------------------------------------------------------------------------
class user_id_iterator : public iterator::iterator_facade<
    user_id_iterator,
    user_id,
    iterator::forward_traversal_tag,
    iterator::readable_iterator_tag,
    user_id,
    user_id *,
    ptrdiff_t>
{
public:    
    inline user_id_iterator(gpgme_user_id_t x = nullptr) noexcept
    : h(x)
    {}
    
    inline user_id dereference() const
    {
        return user_id(h);
    }
    
    inline void increment()
    {
        h = h->next;
    }
    
    inline bool equal(const user_id_iterator other) const
    {
        return h == other.h;
    }

private:
    gpgme_user_id_t h;
};

//------------------------------------------------------------------------------
using user_id_range = range::iterator_range<user_id_iterator>;

/** @} */

}}} // namespaces

#endif // NIC_F2B1097380206504_NIC

