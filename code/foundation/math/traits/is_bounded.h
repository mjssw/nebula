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
#ifndef NIC_63F164E4F451D36E_NIC
#define NIC_63F164E4F451D36E_NIC

#include "../../type_traits.h"

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct is_bounded {};

//------------------------------------------------------------------------------
template <>
struct is_bounded<signed char> : public true_type {};

template <>
struct is_bounded<char> : public true_type {};
template <>
struct is_bounded<short> : public true_type {};
template <>
struct is_bounded<int> : public true_type {};
template <>
struct is_bounded<long> : public true_type {};
template <>
struct is_bounded<long long> : public true_type {};

template <>
struct is_bounded<wchar_t> : public true_type {};
template <>
struct is_bounded<char16_t> : public true_type {};
template <>
struct is_bounded<char32_t> : public true_type {};

template <>
struct is_bounded<unsigned char> : public true_type {};
template <>
struct is_bounded<unsigned short> : public true_type {};
template <>
struct is_bounded<unsigned int> : public true_type {};
template <>
struct is_bounded<unsigned long> : public true_type {};
template <>
struct is_bounded<unsigned long long> : public true_type {};

template <>
struct is_bounded<float> : public true_type {};
template <>
struct is_bounded<double> : public true_type {};
template <>
struct is_bounded<long double> : public true_type {};

/** @} */

}}} // namespaces

#endif // NIC_63F164E4F451D36E_NIC