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
#ifndef NIC_3554F11546213CD5_NIC
#define NIC_3554F11546213CD5_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct digits {};

//------------------------------------------------------------------------------
template <>
struct digits<signed char> 
: public integral_constant<size_t, std::numeric_limits<signed char>::digits>  {};

template <>
struct digits<char> 
: public integral_constant<size_t, std::numeric_limits<char>::digits>  {};
template <>
struct digits<short>
: public integral_constant<size_t, std::numeric_limits<short>::digits>  {};
template <>
struct digits<int> 
: public integral_constant<size_t, std::numeric_limits<int>::digits>  {};
template <>
struct digits<long> 
: public integral_constant<size_t, std::numeric_limits<long>::digits>  {};
template <>
struct digits<long long> 
: public integral_constant<size_t, std::numeric_limits<long long>::digits>  {};

template <>
struct digits<wchar_t> 
: public integral_constant<size_t, std::numeric_limits<wchar_t>::digits>  {};
template <>
struct digits<char16_t>
: public integral_constant<size_t, std::numeric_limits<char16_t>::digits>  {};
template <>
struct digits<char32_t> 
: public integral_constant<size_t, std::numeric_limits<char32_t>::digits>  {};

template <>
struct digits<unsigned char> 
: public integral_constant<size_t, std::numeric_limits<unsigned char>::digits>  {};
template <>
struct digits<unsigned short>
: public integral_constant<size_t, std::numeric_limits<unsigned short>::digits>  {};
template <>
struct digits<unsigned int> 
: public integral_constant<size_t, std::numeric_limits<unsigned int>::digits>  {};
template <>
struct digits<unsigned long> 
: public integral_constant<size_t, std::numeric_limits<unsigned long>::digits>  {};
template <>
struct digits<unsigned long long> 
: public integral_constant<size_t, std::numeric_limits<unsigned long long>::digits>  {};

template <>
struct digits<float>
: public integral_constant<size_t, std::numeric_limits<float>::digits>  {};
template <>
struct digits<double> 
: public integral_constant<size_t, std::numeric_limits<double>::digits>  {};
template <>
struct digits<long double> 
: public integral_constant<size_t, std::numeric_limits<long double>::digits>  {};

/** @} */

}}} // namespaces

#endif // NIC_3554F11546213CD5_NIC