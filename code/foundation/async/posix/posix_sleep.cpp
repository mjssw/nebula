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
#include "../config.h"
#ifdef N_ASYNC_posix_clock_nanosleep

#include "../../chrono.h"

#include <time.h>

#ifndef _POSIX_MONOTONIC_CLOCK
#   error "Implement me!"
#endif

namespace nebula { namespace foundation { namespace async {
namespace this_thread { namespace posix {
//------------------------------------------------------------------------------
void sleep(const chrono::timespec &ts)
{
    chrono::timespec rem;
    int r = ::clock_nanosleep(
        CLOCK_MONOTONIC,
        0,
        &ts,
        &rem);
    
    while(r == EINTR)
    {
        r = ::clock_nanosleep(
            CLOCK_MONOTONIC,
            TIMER_ABSTIME,
            &rem,
            &rem);
    }
    
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("clock_nanosleep() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
}

}}}}} // namespaces

#endif // N_ASYNC_pthread
