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
#ifndef NIC_72BCD170FA874512_NIC
#define NIC_72BCD170FA874512_NIC

#include "../../type_traits.h"
#include "../traits/exponent.h"

#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct max_exponent_impl {};

//------------------------------------------------------------------------------
template <>
struct max_exponent_impl<float> {
    inline static constexpr typename exponent<float>::type
    apply() noexcept 
    {
        return std::numeric_limits<float>::max_exponent;
    }
};
//------------------------------------------------------------------------------
template <>
struct max_exponent_impl<double> {
    inline static constexpr typename exponent<double>::type
    apply() noexcept
    {
        return std::numeric_limits<double>::max_exponent;
    }
};
//------------------------------------------------------------------------------
template <>
struct max_exponent_impl<long double> {
    inline static constexpr typename exponent<long double>::type
    apply() noexcept
    {
        return std::numeric_limits<long double>::max_exponent;
    }
};

//------------------------------------------------------------------------------
template <class T>
inline constexpr typename exponent<T>::type max_exponent() noexcept
{
    return max_exponent_impl<T>::apply();
}

/** @} */

}}} // namespaces

#endif // NIC_72BCD170FA874512_NIC