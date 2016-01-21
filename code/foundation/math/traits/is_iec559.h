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
#ifndef NIC_AD5E16BF680367C3_NIC
#define NIC_AD5E16BF680367C3_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct is_iec559 {};

//------------------------------------------------------------------------------
template <>
struct is_iec559<signed char> : public false_type {};

template <>
struct is_iec559<char> : public false_type {};
template <>
struct is_iec559<short> : public false_type {};
template <>
struct is_iec559<int> : public false_type {};
template <>
struct is_iec559<long> : public false_type {};
template <>
struct is_iec559<long long> : public false_type {};

template <>
struct is_iec559<wchar_t> : public false_type {};
template <>
struct is_iec559<char16_t> : public false_type {};
template <>
struct is_iec559<char32_t> : public false_type {};

template <>
struct is_iec559<unsigned char> : public false_type {};
template <>
struct is_iec559<unsigned short> : public false_type {};
template <>
struct is_iec559<unsigned int> : public false_type {};
template <>
struct is_iec559<unsigned long> : public false_type {};
template <>
struct is_iec559<unsigned long long> : public false_type {};

template <>
struct is_iec559<float> 
: public integral_constant<bool,
    std::numeric_limits<float>::is_iec559>
{};
template <>
struct is_iec559<double>
: public integral_constant<bool,
    std::numeric_limits<double>::is_iec559>
{};
template <>
struct is_iec559<long double>
: public integral_constant<bool,
    std::numeric_limits<long double>::is_iec559>
{};

/** @} */

}}} // namespaces

#endif // NIC_AD5E16BF680367C3_NIC