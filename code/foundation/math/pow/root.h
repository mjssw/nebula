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
#ifndef NIC_1ED0348AD791F916_NIC
#define NIC_1ED0348AD791F916_NIC

#include "../traits.h"
#include "../../call_traits.h"

#include <cmath>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct root_impl
{
    template <class X, class Y>
    inline static T apply(X &&x, Y &&y)
    {
        return math::pow(
            foundation::forward<X>(x),
            ctraits::_value<Y>(1) / foundation::forward<Y>(y));
    }
};

//------------------------------------------------------------------------------
template <class X, class Y>
inline ctraits::_value<X> root(X &&x, Y &&y)
{
    n_static_assert(!is_integer<ctraits::_value<X>>::type::value,
        "Floating point type required.");
    n_static_assert(!is_integer<ctraits::_value<Y>>::type::value,
        "Floating point type required.");
    
    return root_impl<ctraits::_value<X>>::apply(
        foundation::forward<X>(x), foundation::forward<Y>(y));
}

/** @} */

}}} // namespaces

#endif // NIC_1ED0348AD791F916_NIC
