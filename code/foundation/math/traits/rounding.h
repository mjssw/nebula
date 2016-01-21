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
#ifndef NIC_EEC1A824DE3D476E_NIC
#define NIC_EEC1A824DE3D476E_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
enum class rounding_style
{
    indeterminate,
    to_zero,
    to_nearest,
    to_infinity,
    to_neg_infinity
};

//------------------------------------------------------------------------------
namespace math_traits_detail {
//------------------------------------------------------------------------------
template <std::float_round_style>
struct from_float_round_style {};
template <>
struct from_float_round_style<std::round_indeterminate> 
: public integral_constant<rounding_style, rounding_style::indeterminate> {};
template <>
struct from_float_round_style<std::round_toward_zero> 
: public integral_constant<rounding_style, rounding_style::to_zero> {};
template <>
struct from_float_round_style<std::round_to_nearest> 
: public integral_constant<rounding_style, rounding_style::to_nearest> {};
template <>
struct from_float_round_style<std::round_toward_infinity> 
: public integral_constant<rounding_style, rounding_style::to_infinity> {};
template <>
struct from_float_round_style<std::round_toward_neg_infinity> 
: public integral_constant<rounding_style, rounding_style::to_neg_infinity> {};
//------------------------------------------------------------------------------
} // math_traits_detail
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template <class T>
struct rounding {};

//------------------------------------------------------------------------------
template <>
struct rounding<float> 
: public math_traits_detail::from_float_round_style 
<std::numeric_limits<float>::round_style> 
{};
template <>
struct rounding<double> 
: public math_traits_detail::from_float_round_style 
<std::numeric_limits<double>::round_style> 
{};
template <>
struct rounding<long double> 
: public math_traits_detail::from_float_round_style 
<std::numeric_limits<long double>::round_style> 
{};

/** @} */

}}} // namespaces

#endif // NIC_EEC1A824DE3D476E_NIC