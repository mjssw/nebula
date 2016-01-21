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
#ifndef NIC_BDF743CA7E5B0420_NIC
#define NIC_BDF743CA7E5B0420_NIC

#include "intrin.h"
#include "tags.h"

namespace nebula { namespace foundation { namespace endian {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
namespace bswap_detail {
//------------------------------------------------------------------------------
inline uint16_t bswap_(const uint16_t x) noexcept
{
#   ifdef n_bswap_2_
    return n_bswap_2_(x);
#   else
    return (x << 8) | (x >> 8)
#   endif
}
//------------------------------------------------------------------------------
inline int16_t bswap_(const int16_t x) noexcept
{
    return static_cast<int16_t>(bswap_(static_cast<const int16_t>(x)));
}
//------------------------------------------------------------------------------
inline uint32_t bswap_(const uint32_t x) noexcept
{
#   ifdef n_bswap_4_
    return n_bswap_4_(x);
#   else
    return (x >> 24) |
        ((x<<8) & 0x00FF0000) |
        ((x>>8) & 0x0000FF00) |
        (x << 24);
#   endif
}
//------------------------------------------------------------------------------
inline int32_t bswap_(const int32_t x) noexcept
{
    return static_cast<uint32_t>(bswap_(static_cast<const uint32_t>(x)));
}
//------------------------------------------------------------------------------
inline uint64_t bswap_(const uint64_t x) noexcept
{
#   ifdef n_bswap_8_
    return n_bswap_8_(x);
#   else
    return (x >> 56) |
        ((x << 40) & 0x00FF000000000000) |
        ((x << 24) & 0x0000FF0000000000) |
        ((x << 8) & 0x000000FF00000000) |
        ((x >> 8) & 0x00000000FF000000) |
        ((x >> 24) & 0x0000000000FF0000) |
        ((x >> 40) & 0x000000000000FF00) |
        (x << 56);
#   endif
}
//------------------------------------------------------------------------------
inline int64_t bswap_(const int64_t x) noexcept
{
    return static_cast<uint64_t>(bswap_(static_cast<const uint64_t>(x)));
}
//------------------------------------------------------------------------------
} // bswap_detail
//------------------------------------------------------------------------------
template <class T>
struct bswap_impl
{
    inline static T apply(const T x) noexcept {
        return bswap_detail::bswap_(x);
    }
};
//------------------------------------------------------------------------------
template <class T>
inline T bswap(const T x) noexcept
{
    return bswap_impl<T>::apply(x);
}
    
/** @} */

}}} // namespaces

#endif // NIC_BDF743CA7E5B0420_NIC