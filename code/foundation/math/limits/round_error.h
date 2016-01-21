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
#ifndef NIC_54C18D02515CCF04_NIC
#define NIC_54C18D02515CCF04_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct round_error_impl {};

//------------------------------------------------------------------------------
template <>
struct round_error_impl<float> {
    inline static constexpr float apply() noexcept {
        return std::numeric_limits<float>::round_error();
    }
};
//------------------------------------------------------------------------------
template <>
struct round_error_impl<double> {
    inline static constexpr double apply() noexcept {
        return std::numeric_limits<double>::round_error();
    }
};
//------------------------------------------------------------------------------
template <>
struct round_error_impl<long double> {
    inline static constexpr long double apply() noexcept {
        return std::numeric_limits<long double>::round_error();
    }
};

//------------------------------------------------------------------------------
template <class T>
inline constexpr auto round_error() noexcept
-> decltype(round_error_impl<T>::apply())
{
    return round_error_impl<T>::apply();
}

/** @} */

}}} // namespaces

#endif // NIC_54C18D02515CCF04_NIC