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
#ifndef NIC_28FAAFCCC4E590E9_NIC
#define NIC_28FAAFCCC4E590E9_NIC

#include "../traits.h"
#include "../../enable_if.h"
#include "../../call_traits.h"

#include <cmath>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{#include "../../type_traits.h"
 */
//------------------------------------------------------------------------------
template <class T>
struct mod_impl
{
    template <
        class X,
        class Y,
        class T_ = T,
        _enable_if<is_integer<T_>>* = nullptr>
    inline static T apply(X &&x, Y &&y) 
    {
        return foundation::forward<X>(x) % foundation::forward<Y>(y);
    }
    template <
        class X,
        class Y,
        class T_ = T,
        _disable_if<is_integer<T_>>* = nullptr>
    inline static T apply(const X &x, const Y &y)
    {
        return std::fmod(x,y);
    }
};

//------------------------------------------------------------------------------
template <class X, class Y>
inline ctraits::_value<X> mod(X &&x, Y &&y)
{
    return mod_impl<ctraits::_value<X>>::apply(
        foundation::forward<X>(x), foundation::forward<Y>(y));
}

/** @} */

}}} // namespaces

#endif // NIC_28FAAFCCC4E590E9_NIC
