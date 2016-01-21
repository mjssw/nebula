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
#ifndef NIC_C801048443591CF0_NIC
#define NIC_C801048443591CF0_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct traps {};

//------------------------------------------------------------------------------
template <>
struct traps<signed char> 
: public integral_constant<bool, std::numeric_limits<signed char>::traps>  {};

template <>
struct traps<char> 
: public integral_constant<bool, std::numeric_limits<char>::traps>  {};
template <>
struct traps<short>
: public integral_constant<bool, std::numeric_limits<short>::traps>  {};
template <>
struct traps<int> 
: public integral_constant<bool, std::numeric_limits<int>::traps>  {};
template <>
struct traps<long> 
: public integral_constant<bool, std::numeric_limits<long>::traps>  {};
template <>
struct traps<long long> 
: public integral_constant<bool, std::numeric_limits<long long>::traps>  {};

template <>
struct traps<wchar_t> 
: public integral_constant<bool, std::numeric_limits<wchar_t>::traps>  {};
template <>
struct traps<char16_t>
: public integral_constant<bool, std::numeric_limits<char16_t>::traps>  {};
template <>
struct traps<char32_t> 
: public integral_constant<bool, std::numeric_limits<char32_t>::traps>  {};

template <>
struct traps<unsigned char> 
: public integral_constant<bool, std::numeric_limits<unsigned char>::traps>  {};
template <>
struct traps<unsigned short>
: public integral_constant<bool, std::numeric_limits<unsigned short>::traps>  {};
template <>
struct traps<unsigned int> 
: public integral_constant<bool, std::numeric_limits<unsigned int>::traps>  {};
template <>
struct traps<unsigned long> 
: public integral_constant<bool, std::numeric_limits<unsigned long>::traps>  {};
template <>
struct traps<unsigned long long> 
: public integral_constant<bool, std::numeric_limits<unsigned long long>::traps>  {};

template <>
struct traps<float>
: public integral_constant<bool, std::numeric_limits<float>::traps>  {};
template <>
struct traps<double> 
: public integral_constant<bool, std::numeric_limits<double>::traps>  {};
template <>
struct traps<long double> 
: public integral_constant<bool, std::numeric_limits<long double>::traps>  {};

/** @} */

}}} // namespaces

#endif // NIC_C801048443591CF0_NIC