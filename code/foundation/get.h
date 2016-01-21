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
#ifndef NIC_4BAC426D94E91A16_NIC
#define NIC_4BAC426D94E91A16_NIC

#include "defs.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{ 
 * */
//------------------------------------------------------------------------------
template <class T>
struct get_impl
{
    template <size_t N>
    inline static auto apply(T &x)
    noexcept(noexcept(x.template get<N>()))
    -> decltype(x.template get<N>())
    {
        return x.template get<N>();
    }
    template <size_t N>
    inline static auto apply(const T &x)
    noexcept(noexcept(x.template get<N>()))
    -> decltype(x.template get<N>())
    {
        return x.template get<N>();
    }
};
//------------------------------------------------------------------------------
template <size_t N, class T>
inline auto get(T &x)
noexcept(noexcept(get_impl<T>::template apply<N>(x)))
-> decltype(get_impl<T>::template apply<N>(x))
{
    return get_impl<T>::template apply<N>(x);
}
template <size_t N, class T>
inline auto get(const T &x)
noexcept(noexcept(get_impl<T>::template apply<N>(x)))
-> decltype(get_impl<T>::template apply<N>(x))
{
    return get_impl<T>::template apply<N>(x);
}

/** @} */

}} // namespaces

#endif // NIC_4BAC426D94E91A16_NIC