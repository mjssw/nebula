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
#ifndef NIC_28C9E133BC270BC0_NIC
#define NIC_28C9E133BC270BC0_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct has_signaling_nan {};

//------------------------------------------------------------------------------
template <>
struct has_signaling_nan<float> 
: public integral_constant<bool,
    std::numeric_limits<float>::has_signaling_NaN>
{};
template <>
struct has_signaling_nan<double>
: public integral_constant<bool,
    std::numeric_limits<double>::has_signaling_NaN>
{};
template <>
struct has_signaling_nan<long double>
: public integral_constant<bool,
    std::numeric_limits<long double>::has_signaling_NaN>
{};

/** @} */

}}} // namespaces

#endif // NIC_28C9E133BC270BC0_NIC