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
#ifndef NIC_47069A396BA026C6_NIC
#define NIC_47069A396BA026C6_NIC

#include "config.h"

#ifdef N_ASYNC_posix_pthread
#   include "posix/posix_mutex.h"
#endif

namespace nebula { namespace foundation { namespace async {
#ifdef N_ASYNC_posix_pthread
//------------------------------------------------------------------------------
class n_foundation_dll mutex : public posix::mutex
{
public:
    inline mutex()
    : posix::mutex(false)
    {}
    mutex(mutex &&) = default;
    
    mutex &operator = (mutex &&other) = default;
    
    template <class D>
    bool try_lock_for(const D &) = delete;
    template <class Clock, class D>
    bool try_lock_until(const D &) = delete;
};
//------------------------------------------------------------------------------
class n_foundation_dll recursive_mutex : public posix::mutex
{
public:
    inline recursive_mutex()
    : posix::mutex(true)
    {}
    recursive_mutex(recursive_mutex &&) = default;
    
    recursive_mutex &operator = (recursive_mutex &&other) = default;
    
    template <class D>
    bool try_lock_for(const D &) = delete;
    template <class Clock, class D>
    bool try_lock_until(const D &) = delete;
};
//------------------------------------------------------------------------------
class n_foundation_dll timed_mutex : public posix::mutex
{
public:
    inline timed_mutex()
    : posix::mutex(false)
    {}
    timed_mutex(timed_mutex &&) = default;
    
    timed_mutex &operator = (timed_mutex &&other) = default;
};
//------------------------------------------------------------------------------
class n_foundation_dll recursive_timed_mutex : public posix::mutex
{
public:
    inline recursive_timed_mutex()
    : posix::mutex(true)
    {}
    recursive_timed_mutex(recursive_timed_mutex &&) = default;
    
    recursive_timed_mutex &operator = (recursive_timed_mutex &&other) = default;
};

#endif // N_ASYNC_posix_pthread

}}} // namespaces

#endif // NIC_47069A396BA026C6_NIC