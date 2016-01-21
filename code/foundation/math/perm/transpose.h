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
#ifndef NIC_17740EEC3262FB09_NIC
#define NIC_17740EEC3262FB09_NIC

#include "traits.h"

namespace nebula { namespace foundation { namespace math { namespace perm {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class P>
struct transpose_impl
{
    template <class P_,
        _enable_if<is_lvalue_reference<P_>>* = nullptr>
    inline static P apply(P_ &&x, const size_t i, const size_t j)
    {
        P res = x;
        res[i] = x[j];
        res[j] = x[i];
        return res;
    }
    template <class P_,
        _disable_if<is_lvalue_reference<P_>>* = nullptr>
    inline static P apply(P_ &&x, const size_t i, const size_t j)
    {
        foundation::swap(x[i], x[j]);
        return foundation::move(x);
    }
};
//------------------------------------------------------------------------------
template <class P,
    class Res = ctraits::_value<P>>
inline Res transpose(P &&x, const size_t i, const size_t j)
{
    return transpose_impl<Res>::apply(
        foundation::forward<P>(x), i,j);
}

/** @} */

}}}} // namespaces

#endif // NIC_17740EEC3262FB09_NIC

