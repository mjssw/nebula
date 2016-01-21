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
#ifdef N_ASYNC_posix_pthread

#include "posix_mutex.h"
#include "../../assert.h"
#include "../../system_error.h"
#include "../../scope_exit.h"

namespace nebula { namespace foundation { namespace async { namespace posix {
//------------------------------------------------------------------------------
mutex::mutex(bool recursive)
{
    pthread_mutexattr_t attr;
    int r = pthread_mutexattr_init(&attr);
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_mutexattr_destroy() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
    n_scope_exit(&) {
        pthread_mutexattr_destroy(&attr);
    };
    if(recursive)
        r = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    else
    {
#       ifdef N_ASYNC_DETECT_DEADLOCK
        r = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
#       else
        r = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
#       endif
    }
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_mutexattr_settype() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
    
    r = pthread_mutex_init(&h, &attr);
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_mutex_init() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
    alive = true;
}
//------------------------------------------------------------------------------
mutex::~mutex() noexcept
{
    if(alive) {
        pthread_mutex_destroy(&h);
        alive = false;
    }
}
//------------------------------------------------------------------------------
void mutex::lock()
{    
    const int r = pthread_mutex_lock(&h);
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_mutex_lock() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
}
//------------------------------------------------------------------------------
void mutex::unlock()
{    
    const int r = pthread_mutex_unlock(&h);
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_mutex_unlock() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
}
//------------------------------------------------------------------------------
bool mutex::try_lock()
{    
    const int r = pthread_mutex_trylock(&h);
    if(r == 0)
        return true;
    if(r == EBUSY)
        return false;
    else
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_mutex_trylock() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
}
//------------------------------------------------------------------------------
bool mutex::timed_lock(const chrono::timespec &t)
{    
    const int r = pthread_mutex_timedlock(&h, &t);
    if(r == 0)
        return true;
    else if(r == ETIMEDOUT)
        return false;
    else
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_mutex_timedlock() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
}

}}}} // namespaces

#endif // N_ASYNC_pthread
