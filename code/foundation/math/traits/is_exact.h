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
#ifndef NIC_9952CB513D525735_NIC
#define NIC_9952CB513D525735_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct is_exact {};

//------------------------------------------------------------------------------
template <>
struct is_exact<signed char> : public true_type {};

template <>
struct is_exact<char> : public true_type {};
template <>
struct is_exact<short> : public true_type {};
template <>
struct is_exact<int> : public true_type {};
template <>
struct is_exact<long> : public true_type {};
template <>
struct is_exact<long long> : public true_type {};

template <>
struct is_exact<wchar_t> : public true_type {};
template <>
struct is_exact<char16_t> : public true_type {};
template <>
struct is_exact<char32_t> : public true_type {};

template <>
struct is_exact<unsigned char> : public true_type {};
template <>
struct is_exact<unsigned short> : public true_type {};
template <>
struct is_exact<unsigned int> : public true_type {};
template <>
struct is_exact<unsigned long> : public true_type {};
template <>
struct is_exact<unsigned long long> : public true_type {};

template <>
struct is_exact<float> 
: public integral_constant<bool,
    std::numeric_limits<float>::is_exact>
{};
template <>
struct is_exact<double>
: public integral_constant<bool,
    std::numeric_limits<double>::is_exact>
{};
template <>
struct is_exact<long double>
: public integral_constant<bool,
    std::numeric_limits<long double>::is_exact>
{};

/** @} */

}}} // namespaces

#endif // NIC_9952CB513D525735_NIC