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
#ifndef NIC_12FA2A212334B9CF_NIC
#define NIC_12FA2A212334B9CF_NIC

#include "../traits.h"
#include "../../call_traits.h"

#include <cmath>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct copy_sign_impl
{
    template <class B>
    inline static T apply(const T &x, const B &y)
    {
        return std::copysign(x, y);
    }
};

//------------------------------------------------------------------------------
/** Return a with the sign of b. */
template <class A, class B>
inline ctraits::_value<A> copy_sign(A &&a, B &&b)
{
    n_static_assert(!is_integer<ctraits::_value<A>>::type::value,
        "Floating point type required.");
    n_static_assert(!is_integer<ctraits::_value<B>>::type::value,
        "Floating point type required.");
    
    return copy_sign_impl<ctraits::_value<A>>::apply(
        foundation::forward<A>(a),
        foundation::forward<B>(b));
}

/** @} */

}}} // namespaces

#endif // NIC_12FA2A212334B9CF_NIC
