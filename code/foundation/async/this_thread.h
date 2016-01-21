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
#ifndef NIC_CD7628E88EA0CBC8_NIC
#define NIC_CD7628E88EA0CBC8_NIC

#include "config.h"
#include "../dll_interface.h"
#include "../chrono.h"

namespace nebula { namespace foundation { namespace async { 
namespace this_thread {
//------------------------------------------------------------------------------
/** Yield the calling thread. 
 *
 *  @throw nothing
 * */
extern void n_foundation_dll yield() noexcept;
//------------------------------------------------------------------------------
#ifdef N_ASYNC_posix_clock_nanosleep
namespace posix {
extern void n_foundation_dll sleep(const chrono::timespec &);
} // posix
/** Give up the thread's timeslice for a duration defined by a timespec obj.
 *
 *  This can only fail (throw) if the requested time to sleep exceeds a certain
 *  threshold. On posix systems this is the case if
 *  tv_nsec field is not in the range 0 to 999999999 or tv_sec is negative.
 * */
template <class D>
inline void sleep(const D &t)
{
    posix::sleep(chrono::to_timespec(t));
}
#endif

//------------------------------------------------------------------------------
/** Alias for sleep(chrono::timespec). */
template <class D>
inline void sleep_for(const D &t)
{
    this_thread::sleep(t);
}

}}}} // namespaces

#endif // NIC_CD7628E88EA0CBC8_NIC
