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
#ifndef NIC_1EBCF0B1EF386BB6_NIC
#define NIC_1EBCF0B1EF386BB6_NIC

#include "../defs.h"

//------------------------------------------------------------------------------
#ifdef N_API_PTHREAD
#   define N_ASYNC_posix_pthread
#   define N_ASYNC_posix_clock_nanosleep
#else
#   error Missing pthread api
#endif

#ifdef N_HEADER_SCHED_H
#   define N_ASYNC_posix_sched
#else
#   error Missing sched.h
#endif

#ifdef N_ASYNC_SAFE
#   define N_ASYNC_DETECT_DEADLOCK
#endif

#endif // NIC_1EBCF0B1EF386BB6_NIC