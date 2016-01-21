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
#ifndef NIC_7D52AD82018F7074_NIC
#define NIC_7D52AD82018F7074_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct is_modulo {};

//------------------------------------------------------------------------------
template <>
struct is_modulo<signed char> 
: public integral_constant<bool, std::numeric_limits<signed char>::is_modulo>  {};

template <>
struct is_modulo<char> 
: public integral_constant<bool, std::numeric_limits<char>::is_modulo>  {};
template <>
struct is_modulo<short>
: public integral_constant<bool, std::numeric_limits<short>::is_modulo>  {};
template <>
struct is_modulo<int> 
: public integral_constant<bool, std::numeric_limits<int>::is_modulo>  {};
template <>
struct is_modulo<long> 
: public integral_constant<bool, std::numeric_limits<long>::is_modulo>  {};
template <>
struct is_modulo<long long> 
: public integral_constant<bool, std::numeric_limits<long long>::is_modulo>  {};

template <>
struct is_modulo<wchar_t> 
: public integral_constant<bool, std::numeric_limits<wchar_t>::is_modulo>  {};
template <>
struct is_modulo<char16_t>
: public integral_constant<bool, std::numeric_limits<char16_t>::is_modulo>  {};
template <>
struct is_modulo<char32_t> 
: public integral_constant<bool, std::numeric_limits<char32_t>::is_modulo>  {};

template <>
struct is_modulo<unsigned char> 
: public integral_constant<bool, std::numeric_limits<unsigned char>::is_modulo>  {};
template <>
struct is_modulo<unsigned short>
: public integral_constant<bool, std::numeric_limits<unsigned short>::is_modulo>  {};
template <>
struct is_modulo<unsigned int> 
: public integral_constant<bool, std::numeric_limits<unsigned int>::is_modulo>  {};
template <>
struct is_modulo<unsigned long> 
: public integral_constant<bool, std::numeric_limits<unsigned long>::is_modulo>  {};
template <>
struct is_modulo<unsigned long long> 
: public integral_constant<bool, std::numeric_limits<unsigned long long>::is_modulo>  {};

template <>
struct is_modulo<float>
: public integral_constant<bool, std::numeric_limits<float>::is_modulo>  {};
template <>
struct is_modulo<double> 
: public integral_constant<bool, std::numeric_limits<double>::is_modulo>  {};
template <>
struct is_modulo<long double> 
: public integral_constant<bool, std::numeric_limits<long double>::is_modulo>  {};

/** @} */

}}} // namespaces

#endif // NIC_7D52AD82018F7074_NIC