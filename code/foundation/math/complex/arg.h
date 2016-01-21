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
#ifndef NIC_56E9F18BA0F03727_NIC
#define NIC_56E9F18BA0F03727_NIC

#include "common.h"

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T>
struct arg_impl
{
    template<class S>
    inline static vec::_scalar_value<T> apply(S &&s)
    {
        return math::atan2(
            foundation::forward<S>(s)[1],
            foundation::forward<S>(s)[0]);
    }
};
//------------------------------------------------------------------------------
template <class Complex>
inline vec::_scalar_value<ctraits::_value<Complex>> arg(Complex &&z)
{
    return arg_impl<ctraits::_value<Complex>>::apply(
        foundation::forward<Complex>(z));
}

/** @} */

}}} // namespaces

#endif // NIC_56E9F18BA0F03727_NIC

