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
/** @file defs.h
 * Collection of the most common/basic types and macros.
 * */
#ifndef NIC_9340EF70FD7826CA_NIC
#define NIC_9340EF70FD7826CA_NIC

#include "config.h"
#include <cstdint>
#include <climits>

namespace nebula { namespace foundation {

/** @ingroup Foundation
 * @{ 
 * */

//------------------------------------------------------------------------------
#ifdef N_COMPILER_GNUC
#   define n_stdcall
#   define n_fastcall
#   define n_cdecl

#   define n_forceinline inline

#   define n_threadlocal __thread

#   define n_dll_export
#   define n_dll_import

#   define n_unused_variable(type, var, ...) \
        type __attribute__((unused)) var __VA_ARGS__
        
#   define n_current_function __PRETTY_FUNCTION__

#   define n_expect( x, y ) __builtin_expect( !!(x), (y) )

#   define n_deprecated_type( _msg ) __attribute__ ((deprecated))
#   define n_deprecated_method( _msg ) __attribute__ ((deprecated))
#   define n_deprecated_variable( _msg ) __attribute__ ((deprecated))
#else
#   error Unknown Compiler!
#endif

//------------------------------------------------------------------------------
/** Always use this instead of static_assert. */
#define n_static_assert(xpr, msg) static_assert(xpr, #xpr " : " msg)
//------------------------------------------------------------------------------
/** This prevents macro substitution. */
#define n_no_macro() ()
//------------------------------------------------------------------------------
/** So you can use commas inside macro parameter lists. */
#define n_arg(...) __VA_ARGS__
//------------------------------------------------------------------------------
#define n_char_bit CHAR_BIT

//------------------------------------------------------------------------------
/** If you have a meta function myfunc, then this macro creates
 * the aliases myfunc_ and _myfunc, whereby myfunc_ is exactly myfunc
 * and _myfunc is the return type of myfunc.
 * @attention name must not start with a capital letter!
 * @see nebula::foundation::meta
 * */
#define n_meta_alias(name) \
    template <class ... T> \
    using _##name = typename name<T...>::type; \
    template <class ... T> \
    using name##_ = name<T...>;

//------------------------------------------------------------------------------
using llong = long long;

//------------------------------------------------------------------------------
using uchar = unsigned char;
using schar = signed char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using ullong = unsigned long long;

//------------------------------------------------------------------------------
using size_t = std::size_t;
using ptrdiff_t = std::ptrdiff_t;

//------------------------------------------------------------------------------
using bitmask_t = unsigned long;

//------------------------------------------------------------------------------
using int8_t = std::int8_t;
using int16_t = std::int16_t;
using int32_t = std::int32_t;
using int64_t = std::int64_t;

using int_fast8_t = std::int_fast8_t;
using int_fast16_t = std::int_fast16_t;
using int_fast32_t = std::int_fast32_t;
using int_fast64_t = std::int_fast64_t;

using int_least8_t = std::int_least8_t;
using int_least16_t = std::int_least16_t;
using int_least32_t = std::int_least32_t;
using int_least64_t = std::int_least64_t;

using intmax_t = std::intmax_t;
using intptr_t = std::intptr_t;

//------------------------------------------------------------------------------
using uint8_t = std::uint8_t;
using uint16_t = std::uint16_t;
using uint32_t = std::uint32_t;
using uint64_t = std::uint64_t;

using uint_fast8_t = std::uint_fast8_t;
using uint_fast16_t = std::uint_fast16_t;
using uint_fast32_t = std::uint_fast32_t;
using uint_fast64_t = std::uint_fast64_t;

using uint_least8_t = std::uint_least8_t;
using uint_least16_t = std::uint_least16_t;
using uint_least32_t = std::uint_least32_t;
using uint_least64_t = std::uint_least64_t;

using uintmax_t = std::uintmax_t;
using uintptr_t = std::uintptr_t;

//------------------------------------------------------------------------------
using ldouble = long double;

//------------------------------------------------------------------------------
using float_fast_t = float;
using double_fast_t = double;
using ldouble_fast_t = long double;

//------------------------------------------------------------------------------
struct nothrow_tag {};
struct throw_tag {};

/** @} */

}} // namespaces

#endif // NIC_9340EF70FD7826CA_NIC
