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
#ifndef NIC_F615A9ACDB23ADB0_NIC
#define NIC_F615A9ACDB23ADB0_NIC

#include "duration.h"
#include "../math/exact_cast.h"

#ifdef N_HEADER_TIME_H
#   include <time.h>
#   define N_CHRONO_timespec_available
#endif

namespace nebula { namespace foundation { namespace chrono {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
#ifdef N_CHRONO_timespec_available
// Always use the native posix time_t and timespec if available!
// We just pull it into our namespace here.
using time_t = ::time_t;
using timespec = ::timespec;
#else
using time_t = long;
struct timespec {
    time_t tv_sec;
    long tv_nsec;
};
#endif

//------------------------------------------------------------------------------
template <class D>
inline timespec to_timespec(const D &x)
{
    timespec ts;
    const chrono::seconds s
        = chrono::duration_cast<chrono::seconds>(x);
    const chrono::nanoseconds ns
        = chrono::duration_cast<chrono::nanoseconds>(x)
        - chrono::duration_cast<chrono::nanoseconds>(s);
        
    math::require_exact_cast<decltype(ts.tv_sec)>(s.count());
    ts.tv_sec = s.count();
    math::require_exact_cast<decltype(ts.tv_nsec)>(ns.count());
    ts.tv_nsec = ns.count();
    
    return ts;
}
//------------------------------------------------------------------------------
template <class D>
inline D to_duration(const timespec &ts) noexcept
{
    seconds s(ts.tv_sec);
    nanoseconds ns(ts.tv_nsec);
    return duration_cast<D>(s) + duration_cast<D>(ns);
}

/** @} */

}}} // namespaces

#undef N_CHRONO_timespec_available

#endif // NIC_F615A9ACDB23ADB0_NIC