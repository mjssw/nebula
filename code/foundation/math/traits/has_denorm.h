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
#ifndef NIC_D55779AA9E3D3E75_NIC
#define NIC_D55779AA9E3D3E75_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
enum class denorm_style
{
    indeterminate,
    present,
    absent
};

//------------------------------------------------------------------------------
namespace math_traits_detail {
//------------------------------------------------------------------------------
template <std::float_denorm_style>
struct from_float_denorm_style {};
template <>
struct from_float_denorm_style<std::denorm_indeterminate> 
: public integral_constant<denorm_style, denorm_style::indeterminate> {};
template <>
struct from_float_denorm_style<std::denorm_present> 
: public integral_constant<denorm_style, denorm_style::present> {};
template <>
struct from_float_denorm_style<std::denorm_absent> 
: public integral_constant<denorm_style, denorm_style::absent> {};
//------------------------------------------------------------------------------
} // math_traits_detail
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template <class T>
struct has_denorm {};

//------------------------------------------------------------------------------
template <>
struct has_denorm<float> 
: public math_traits_detail::from_float_denorm_style 
<std::numeric_limits<float>::has_denorm> 
{};
template <>
struct has_denorm<double> 
: public math_traits_detail::from_float_denorm_style 
<std::numeric_limits<double>::has_denorm> 
{};
template <>
struct has_denorm<long double> 
: public math_traits_detail::from_float_denorm_style 
<std::numeric_limits<long double>::has_denorm> 
{};

/** @} */

}}} // namespaces

#endif // NIC_D55779AA9E3D3E75_NIC