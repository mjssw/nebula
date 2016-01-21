/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2016 lis (lis@tutanota.com)
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
#ifndef NIC_6DF5946CE6D87792_NIC
#define NIC_6DF5946CE6D87792_NIC

#include "../foundation/config.h"
#include "../foundation/assert.h"
#include "../foundation/string.h"
#include "../foundation/cstring.h"
#include "../foundation/vector.h"
#include "../foundation/range.h"
#include "../foundation/io.h"
#include "../foundation/format.h"
#include "../foundation/system_error.h"
#include "../foundation/tuple.h"
#include "../foundation/chrono.h"
#include "../foundation/scope_exit.h"
#include "../foundation/math/exact_cast.h"

#include <gpgme.h>

namespace nebula { namespace gpg {
/** @ingroup GPG
 * @{
 * */
namespace detail {
//------------------------------------------------------------------------------
namespace system = foundation::system;
namespace io = foundation::io;
namespace fmt = foundation::fmt;
namespace chrono = foundation::chrono;
namespace iterator = foundation::iterator;
namespace range = foundation::range;
namespace math = foundation::math;

using foundation::runtime_error;
using foundation::logic_error;
using foundation::exception_ptr;
using foundation::error_info;
using foundation::ei_exc;
using foundation::ei_msg_c;
using foundation::current_exception;
using foundation::string;
using foundation::cstring;
using foundation::const_cstring;
using foundation::swap;
using foundation::move;
using foundation::forward;
using foundation::vector;
using foundation::tuple;
using foundation::get;
using foundation::scope_exit;

} // detail

//------------------------------------------------------------------------------
/** @def n_gpg_dll
 * */
#ifdef N_GPG_SHARED
#    ifdef N_GPG_BUILD_DLL
#        define n_gpg_dll n_dll_export
#    else
#        define n_gpg_dll n_dll_import
#    endif
#else
#    define n_gpg_dll
#endif

//------------------------------------------------------------------------------
#define NEBULA_GPG_NAME              NAUTO_GPG_NAME
#define NEBULA_GPG_VERSION           NAUTO_GPG_VERSION
#define NEBULA_GPG_STRING            NAUTO_GPG_STRING
#define NEBULA_GPG_BUGREPORT         NAUTO_GPG_BUGREPORT
#define NEBULA_GPG_URL               NAUTO_GPG_URL
#define NEBULA_GPG_VERSION_MAJOR     NAUTO_GPG_VERSION_MAJOR
#define NEBULA_GPG_VERSION_MINOR     NAUTO_GPG_VERSION_MINOR
#define NEBULA_GPG_VERSION_MICRO     NAUTO_GPG_VERSION_MICRO

/** @} */

}} // namespaces

#endif // NIC_6DF5946CE6D87792_NIC

