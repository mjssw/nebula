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
#ifndef NIC_DF02DB96B3164435_NIC
#define NIC_DF02DB96B3164435_NIC

#include "../defs.h"

//------------------------------------------------------------------------------
#if !defined(N_ENDIAN_LITTLE) && !defined(N_ENDIAN_BIG)
#    error Unsupported Endianness.
#endif
//------------------------------------------------------------------------------
#if !defined(INT8_MIN) \
    || !defined(INT16_MIN) \
    || !defined(INT32_MIN) \
    || !defined(INT64_MIN)
#    error Missing integer types.
#endif
//------------------------------------------------------------------------------
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
/** @def n_bswap_2_
 * Swap objects that are 2 bytes long.
 * @warning Only defined if the compiler offers such an intrinsic.
 * */
/** @def n_bswap_4_
 * Swap objects that are 4 bytes long.
 * @warning Only defined if the compiler offers such an intrinsic.
 * */
/** @def n_bswap_8_
 * Swap objects that are 8 bytes long.
 * @warning Only defined if the compiler offers such an intrinsic.
 * */
//------------------------------------------------------------------------------
// For GCC versions >= 4.8.0
#if (defined(N_COMPILER_GNUC) \
    && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 8) || __GNUC__ > 4))
#    define n_bswap_2_(x) __builtin_bswap16(x)
#    define n_bswap_4_(x) __builtin_bswap32(x)
#    define n_bswap_8_(x) __builtin_bswap64(x)
#endif
    
/** @} */

#endif // NIC_DF02DB96B3164435_NIC