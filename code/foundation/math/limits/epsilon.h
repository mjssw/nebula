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
#ifndef NIC_5EA01B413A37D94C_NIC
#define NIC_5EA01B413A37D94C_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct epsilon_impl {};

//------------------------------------------------------------------------------
template <>
struct epsilon_impl<float> {
    inline static constexpr float apply() noexcept {
        return std::numeric_limits<float>::epsilon();
    }
};
//------------------------------------------------------------------------------
template <>
struct epsilon_impl<double> {
    inline static constexpr double apply() noexcept {
        return std::numeric_limits<double>::epsilon();
    }
};
//------------------------------------------------------------------------------
template <>
struct epsilon_impl<long double> {
    inline static constexpr long double apply() noexcept {
        return std::numeric_limits<long double>::epsilon();
    }
};

//------------------------------------------------------------------------------
template <class T>
inline constexpr auto epsilon() noexcept
-> decltype(epsilon_impl<T>::apply())
{
    return epsilon_impl<T>::apply();
}

/** @} */

}}} // namespaces

#endif // NIC_5EA01B413A37D94C_NIC