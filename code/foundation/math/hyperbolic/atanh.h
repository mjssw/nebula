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
#ifndef NIC_343DE201ADEED45F_NIC
#define NIC_343DE201ADEED45F_NIC

#include "../traits.h"
#include "../../call_traits.h"

#include <cmath>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct atanh_impl
{
    inline static T apply(const T &x)
    {
        return std::atanh(x);
    }
};

//------------------------------------------------------------------------------
template <class T>
inline ctraits::_value<T> atanh(T &&x)
{
    n_static_assert(!is_integer<ctraits::_value<T>>::type::value,
        "Floating point type required.");
    return atanh_impl<ctraits::_value<T>>::apply(foundation::forward<T>(x));
}

/** @} */

}}} // namespaces

#endif // NIC_343DE201ADEED45F_NIC
