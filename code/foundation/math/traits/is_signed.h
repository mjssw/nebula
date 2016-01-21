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
#ifndef NIC_761BB1EA6ECDD3A8_NIC
#define NIC_761BB1EA6ECDD3A8_NIC

#include "../../type_traits.h"

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct is_signed {};

//------------------------------------------------------------------------------
template <>
struct is_signed<signed char> : public true_type {};

template <>
struct is_signed<char> : public true_type {};
template <>
struct is_signed<short> : public true_type {};
template <>
struct is_signed<int> : public true_type {};
template <>
struct is_signed<long> : public true_type {};
template <>
struct is_signed<long long> : public true_type {};

template <>
struct is_signed<wchar_t> : public false_type {};
template <>
struct is_signed<char16_t> : public false_type {};
template <>
struct is_signed<char32_t> : public false_type {};

template <>
struct is_signed<unsigned char> : public false_type {};
template <>
struct is_signed<unsigned short> : public false_type {};
template <>
struct is_signed<unsigned int> : public false_type {};
template <>
struct is_signed<unsigned long> : public false_type {};
template <>
struct is_signed<unsigned long long> : public false_type {};

template <>
struct is_signed<float> : public true_type {};
template <>
struct is_signed<double> : public true_type {};
template <>
struct is_signed<long double> : public true_type {};

/** @} */

}}} // namespaces

#endif // NIC_761BB1EA6ECDD3A8_NIC