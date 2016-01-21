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
#ifndef NIC_5DE69ADF00AC01D7_NIC
#define NIC_5DE69ADF00AC01D7_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct has_quiet_nan {};

//------------------------------------------------------------------------------
template <>
struct has_quiet_nan<float> 
: public integral_constant<bool,
    std::numeric_limits<float>::has_quiet_NaN>
{};
template <>
struct has_quiet_nan<double>
: public integral_constant<bool,
    std::numeric_limits<double>::has_quiet_NaN>
{};
template <>
struct has_quiet_nan<long double>
: public integral_constant<bool,
    std::numeric_limits<long double>::has_quiet_NaN>
{};

/** @} */

}}} // namespaces

#endif // NIC_5DE69ADF00AC01D7_NIC