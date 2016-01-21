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
#ifndef NIC_B365EBE95844599E_NIC
#define NIC_B365EBE95844599E_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct base {};

//------------------------------------------------------------------------------
template <>
struct base<signed char> 
: public integral_constant<size_t, std::numeric_limits<signed char>::radix>  {};

template <>
struct base<char> 
: public integral_constant<size_t, std::numeric_limits<char>::radix>  {};
template <>
struct base<short>
: public integral_constant<size_t, std::numeric_limits<short>::radix>  {};
template <>
struct base<int> 
: public integral_constant<size_t, std::numeric_limits<int>::radix>  {};
template <>
struct base<long> 
: public integral_constant<size_t, std::numeric_limits<long>::radix>  {};
template <>
struct base<long long> 
: public integral_constant<size_t, std::numeric_limits<long long>::radix>  {};

template <>
struct base<wchar_t> 
: public integral_constant<size_t, std::numeric_limits<wchar_t>::radix>  {};
template <>
struct base<char16_t>
: public integral_constant<size_t, std::numeric_limits<char16_t>::radix>  {};
template <>
struct base<char32_t> 
: public integral_constant<size_t, std::numeric_limits<char32_t>::radix>  {};

template <>
struct base<unsigned char> 
: public integral_constant<size_t, std::numeric_limits<unsigned char>::radix>  {};
template <>
struct base<unsigned short>
: public integral_constant<size_t, std::numeric_limits<unsigned short>::radix>  {};
template <>
struct base<unsigned int> 
: public integral_constant<size_t, std::numeric_limits<unsigned int>::radix>  {};
template <>
struct base<unsigned long> 
: public integral_constant<size_t, std::numeric_limits<unsigned long>::radix>  {};
template <>
struct base<unsigned long long> 
: public integral_constant<size_t, std::numeric_limits<unsigned long long>::radix>  {};

template <>
struct base<float>
: public integral_constant<size_t, std::numeric_limits<float>::radix>  {};
template <>
struct base<double> 
: public integral_constant<size_t, std::numeric_limits<double>::radix>  {};
template <>
struct base<long double> 
: public integral_constant<size_t, std::numeric_limits<long double>::radix>  {};

/** @} */

}}} // namespaces

#endif // NIC_B365EBE95844599E_NIC