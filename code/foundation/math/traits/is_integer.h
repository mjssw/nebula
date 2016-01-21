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
#ifndef NIC_1DE3D8E86F8BD990_NIC
#define NIC_1DE3D8E86F8BD990_NIC

#include "../../type_traits.h"

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct is_integer {};

//------------------------------------------------------------------------------
template <>
struct is_integer<signed char> : public true_type {};

template <>
struct is_integer<char> : public true_type {};
template <>
struct is_integer<short> : public true_type {};
template <>
struct is_integer<int> : public true_type {};
template <>
struct is_integer<long> : public true_type {};
template <>
struct is_integer<long long> : public true_type {};

template <>
struct is_integer<wchar_t> : public true_type {};
template <>
struct is_integer<char16_t> : public true_type {};
template <>
struct is_integer<char32_t> : public true_type {};

template <>
struct is_integer<unsigned char> : public true_type {};
template <>
struct is_integer<unsigned short> : public true_type {};
template <>
struct is_integer<unsigned int> : public true_type {};
template <>
struct is_integer<unsigned long> : public true_type {};
template <>
struct is_integer<unsigned long long> : public true_type {};

template <>
struct is_integer<float> : public false_type {};
template <>
struct is_integer<double> : public false_type {};
template <>
struct is_integer<long double> : public false_type {};

/** @} */

}}} // namespaces

#endif // NIC_1DE3D8E86F8BD990_NIC