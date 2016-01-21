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
/** @file userconfig.h
 * Do not include this file directly but instead include config.h.
 * Definitions from config.h are guaranteed to be available here.
 * */

/** @ingroup Foundation
 * @{
 * */

//------------------------------------------------------------------------------
/** @def N_USE_ASSERT
 * If defined it anables the macro n_assert.
 * @warning Do not enable this in production code. It is not designed that way.
 * */
#ifdef N_DEBUG
#   define N_USE_ASSERT
#endif

//------------------------------------------------------------------------------
/** @def N_EXCEPTIONS_STORE_FUNCTION_NAME
 * Define this if you desire to have the function name where an exceptions
 * occurred to be stored inside the exception object. Otherwise only
 * the source file name and line number is stored by default.
 * @note Function names can get very(!) long if templates are involved.
 * */
#ifdef N_DEBUG
#   define N_EXCEPTIONS_STORE_FUNCTION_NAME
#endif

//------------------------------------------------------------------------------
/** @def N_CHRONO_INLINE
 * Do you want to inline timing stuff in the chrono library? Then define this,
 * but beware that verious system headers might pollute the global namespace.
 * Inlining may help the clocks to be more accurate.
 * */
#define N_CHRONO_INLINE

//------------------------------------------------------------------------------
/** @def N_ASYNC_SAFE
 * Makes sure that certain operations performed by the async library are valid,
 * otherwise error out with an exception. One example of an invalid operation
 * woulb be a dead-lock. Note that such checks come with a perfomance overhead.
 * */
#ifdef N_DEBUG
#   define N_ASYNC_SAFE
#endif

/** @} */