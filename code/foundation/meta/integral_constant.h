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
#ifndef NIC_A7237F16B3CBD009_NIC
#define NIC_A7237F16B3CBD009_NIC

#include "../defs.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I, I Value>
struct integral_constant
{
    using value_type = I;
    /** integral_constant is a meta-function that evals to itself (idenity).
     * This is to avoid frequent checking if a type is indeed a meta-function,
     * we just make everything a metafunction.
     * */
    using type = integral_constant<I, Value>;
    constexpr static I value = Value;
    
    inline constexpr operator value_type() const noexcept { return Value; }
    // req. by C++14
    inline constexpr value_type operator () () const noexcept {
        return Value;
    }
};

template <class I, I Value>
constexpr I integral_constant<I, Value>::value;

//------------------------------------------------------------------------------
template <bool Val>
using bool_ = integral_constant<bool, Val>;

template <char Val>
using char_ = integral_constant<char, Val>;
template <unsigned char Val>
using uchar_ = integral_constant<unsigned char, Val>;

template <short Val>
using short_ = integral_constant<short, Val>;
template <unsigned short Val>
using ushort_ = integral_constant<unsigned short, Val>;

template <int Val>
using int_ = integral_constant<int, Val>;
template <unsigned int Val>
using uint_ = integral_constant<unsigned int, Val>;

template <long Val>
using long_ = integral_constant<long, Val>;
template <unsigned long Val>
using ulong_ = integral_constant<unsigned long, Val>;

template <long long Val>
using llong_ = integral_constant<long long, Val>;
template <unsigned long long Val>
using ullong_ = integral_constant<unsigned long long, Val>;

template <long Val>
using intmax_t_ = integral_constant<intmax_t, Val>;
template <unsigned long Val>
using uintmax_t_ = integral_constant<uintmax_t, Val>;

template <size_t Val>
using size_t_ = integral_constant<size_t, Val>;

template <ptrdiff_t Val>
using ptrdiff_t_ = integral_constant<ptrdiff_t, Val>;

using true_ = bool_<true>;
using false_ = bool_<false>;

// C++11 has such types.
using true_type = true_;
using false_type = false_;
//------------------------------------------------------------------------------
template <class T>
struct is_integral_constant : public false_ {};
template <class T, T Val>
struct is_integral_constant<integral_constant<T, Val>> : public true_ {};

/** @} */

}}} // namespaces

#endif // NIC_A7237F16B3CBD009_NIC