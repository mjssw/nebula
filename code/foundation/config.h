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
#ifndef NIC_B504129BED7A8267_NIC
#define NIC_B504129BED7A8267_NIC

#include "config/compiler.h"
#include "config/stdlib.h"
#include "config/architecture.h"
#include "config/os.h"
#include "config/endian.h"
#include "config/headers.h"
#include "config/api.h"

/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** Package Name String*/
#define NEBULA_NAME                 NAUTO_PACKAGE_NAME
/** Package Version String */
#define NEBULA_VERSION              NAUTO_PACKAGE_VERSION
/** Package Name + Version String */
#define NEBULA_STRING               NAUTO_PACKAGE_STRING
/** Bugreport String */
#define NEBULA_BUGREPORT            NAUTO_PACKAGE_BUGREPORT
/** Project URL */
#define NEBULA_URL                  NAUTO_PACKAGE_URL
/** Package Major Version Integer */
#define NEBULA_VERSION_MAJOR        NAUTO_PACKAGE_VERSION_MAJOR
/** Package Minor Version Integer */
#define NEBULA_VERSION_MINOR        NAUTO_PACKAGE_VERSION_MINOR
/** Package Micro Version Integer */
#define NEBULA_VERSION_MICRO        NAUTO_PACKAGE_VERSION_MICRO
//------------------------------------------------------------------------------
#define NEBULA_FOUNDATION_NAME              NAUTO_FOUNDATION_NAME
#define NEBULA_FOUNDATION_VERSION           NAUTO_FOUNDATION_VERSION
#define NEBULA_FOUNDATION_STRING            NAUTO_FOUNDATION_STRING
#define NEBULA_FOUNDATION_BUGREPORT         NAUTO_FOUNDATION_BUGREPORT
#define NEBULA_FOUNDATION_URL               NAUTO_FOUNDATION_URL
#define NEBULA_FOUNDATION_VERSION_MAJOR     NAUTO_FOUNDATION_VERSION_MAJOR
#define NEBULA_FOUNDATION_VERSION_MINOR     NAUTO_FOUNDATION_VERSION_MINOR
#define NEBULA_FOUNDATION_VERSION_MICRO     NAUTO_FOUNDATION_VERSION_MICRO

/** @} */

//==============================================================================
/* Must be included last to provide previous definitions in userconfig.h. */
#include "userconfig.h"

#endif // NIC_B504129BED7A8267_NIC
