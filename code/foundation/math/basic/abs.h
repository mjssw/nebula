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
#ifndef NIC_9F27AEC5B4E590E9_NIC
#define NIC_9F27AEC5B4E590E9_NIC

#include "../traits.h"
#include "../../enable_if.h"
#include "../../move.h"
#include "../../defs.h"
#include "../../call_traits.h"
#include "../../declval.h"
#include <cmath>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct abs_impl
{    
    template <class Cond = is_signed<T>,
        typename enable_if<Cond>::type* = nullptr>
    inline static T apply(T x)
    {
        return std::abs(x);
    }
    template <class X,
        class Cond = is_signed<T>,
        typename disable_if<Cond>::type* = nullptr>
    inline static T apply(X &&x)
    {
        return foundation::forward<X>(x);
    }
};

//------------------------------------------------------------------------------
template <class T>
inline auto abs(T &&x)
-> decltype(abs_impl<
    typename ctraits::value<T>::type>::apply(foundation::declval<T>()))
{
    return abs_impl<
        typename ctraits::value<T>::type>::apply(foundation::forward<T>(x));
}

/** @} */

}}} // namespaces

#endif // NIC_9F27AEC5B4E590E9_NIC
