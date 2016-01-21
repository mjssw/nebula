/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 lis (lis@tutanota.com)
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
#ifndef NIC_4B8E37F671DE3312_NIC
#define NIC_4B8E37F671DE3312_NIC

#include "../hal/fnv1a.h"
#include "../type_traits.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
  * @{ 
  * */
namespace hash_detail {
//------------------------------------------------------------------------------
inline static size_t hash_blob_(const char *p, const size_t n) noexcept 
{
    hal::fnv1a<> h;
    io::write(h, p, n);
    return h.result();
}
//------------------------------------------------------------------------------
template <class T>
inline static size_t hash_blob(const T *p, const size_t n) noexcept 
{
    return hash_blob_(static_cast<const char *>(static_cast<const void *>(p)),
        n * sizeof(T));
}

} // hash_detail

//------------------------------------------------------------------------------
/** This is the default hash function used by the foundation library.
 *
 *  For all integer types including (signed/unsigned) char the returned
 *  'hash' is actually just the identity.
 *  Any other type is hashed using a reasonable hash funciton.
 * 
 *  For hash algorithms
 *  @see nebula::foundation::hal
 * */
template <class T>
struct hash {
    using result_t = size_t;
    
    inline size_t operator () (const T &x) const noexcept {
        return hash_detail::hash_blob(&x, 1);
    }
};

//------------------------------------------------------------------------------
#define _n_int_hash( type ) \
    template <>\
    struct hash<type> \
    {\
        using result_type = size_t; \
        inline result_type operator () (const type x) const noexcept \
        {\
            return static_cast<result_type>(x); \
        }\
    };
    
_n_int_hash(char);
_n_int_hash(signed char);
_n_int_hash(unsigned char);
_n_int_hash(short);
_n_int_hash(unsigned short);
_n_int_hash(int);
_n_int_hash(unsigned int);
_n_int_hash(long);
_n_int_hash(unsigned long);
_n_int_hash(long long);
_n_int_hash(unsigned long long)
    
#undef _n_int_hash

namespace hash_detail {
//------------------------------------------------------------------------------
template <class C>
struct string_hash
{
    using result_type = size_t;
    template <class String>
    inline size_t operator () (const String &x) const noexcept
    {
        return hash_detail::hash_blob(x.data(), x.size());
    }
    inline size_t operator () (
        const C *x) const noexcept
    {
        return hash_detail::hash_blob(x, strlen(x));
    }
};

} // hash_detail

/** @} */

}} // namespaces

#endif // NIC_4B8E37F671DE3312_NIC
