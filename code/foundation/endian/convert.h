/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 (lis@tutanota.com)
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
#ifndef NIC_814074AD700F1F99_NIC
#define NIC_814074AD700F1F99_NIC

#include "byteswap.h"

namespace nebula { namespace foundation { namespace endian {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T, class From, class To>
struct convert_impl {
    inline static T apply(const T x) noexcept {
        return x;
    }
};
template <class T>
struct convert_impl<T, little_endian_tag, big_endian_tag> {
    inline static T apply(const T x) noexcept {
        return endian::bswap(x);
    }
};
template <class T>
struct convert_impl<T, big_endian_tag, little_endian_tag> {
    inline static T apply(const T x) noexcept {
        return endian::bswap(x);
    }
};
//------------------------------------------------------------------------------
template <class From, class To, class T>
inline T convert(const T x) noexcept
{
    return convert_impl<T, From, To>::apply(x);
}

//------------------------------------------------------------------------------
// Below are some convenience functions.
//------------------------------------------------------------------------------
template <class T>
inline T htole(const T x) noexcept
{
    return endian::convert<host_endian_tag, little_endian_tag>(x);
}
//------------------------------------------------------------------------------
template <class T>
inline T htobe(const T x) noexcept
{
    return endian::convert<host_endian_tag, big_endian_tag>(x);
}
//------------------------------------------------------------------------------
template <class T>
inline T letoh(const T x) noexcept
{
    return htole(x);
}
//------------------------------------------------------------------------------
template <class T>
inline T betoh(const T x) noexcept
{
    return htobe(x);
}
//------------------------------------------------------------------------------
template <class T>
inline T hton(const T x) noexcept
{
    return endian::convert<host_endian_tag, network_endian_tag>(x);
}
//------------------------------------------------------------------------------
template <class T>
inline T ntoh(const T x) noexcept
{
    return endian::convert<network_endian_tag, host_endian_tag>(x);
}
    
/** @} */

}}} // namespaces

#endif // NIC_814074AD700F1F99_NIC