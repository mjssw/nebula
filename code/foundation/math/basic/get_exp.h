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
#ifndef NIC_4FCA20C112334B9C_NIC
#define NIC_4FCA20C112334B9C_NIC

#include "../traits/exponent.h"
#include "../traits.h"
#include "../../type_traits.h"

#include <cmath>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct get_exp_impl
{
    inline static typename exponent<T>::type apply(const T &x)
    {
        return std::ilogb(x);
    }
};

//------------------------------------------------------------------------------
template <class T>
inline typename exponent<T>::type get_exp(const T &x)
{
    n_static_assert(!is_integer<T>::type::value,
        "Floating point type required.");
    return get_exp_impl<T>::apply(x);
}

/** @} */

}}} // namespaces

#endif // NIC_4FCA20C112334B9C_NIC
