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

#include "posix_condition_variable.h"
#include "../../assert.h"
#include "../../system_error.h"
#include "../../scope_exit.h"

#ifndef _POSIX_MONOTONIC_CLOCK
#   error "Refusing to work without _POSIX_MONOTONIC_CLOCK"
#endif

namespace nebula { namespace foundation { namespace async { namespace posix {
//------------------------------------------------------------------------------
condition_variable::condition_variable()
{
    pthread_condattr_t attr;
    int r = pthread_condattr_init(&attr);
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_condattr_init() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
    n_scope_exit(&) {
        pthread_condattr_destroy(&attr);
    };
    
    pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
    
    r = pthread_cond_init(&h, &attr);
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_cond_init() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
    alive = true;
}
//------------------------------------------------------------------------------
condition_variable::~condition_variable() noexcept
{
    if(alive) {
        pthread_cond_destroy(&h);
        alive = false;
    }
}
//------------------------------------------------------------------------------
void condition_variable::wait(pthread_mutex_t &m)
{
    const int r = pthread_cond_wait(&h, &m);
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_cond_wait() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
}
//------------------------------------------------------------------------------
bool condition_variable::timed_wait(
    pthread_mutex_t &m,
    const chrono::timespec &t)
{
    const int r = pthread_cond_timedwait(&h, &m, &t);
    if(r == ETIMEDOUT)
        return false;
    else if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_cond_wait() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
    return true;
}
//------------------------------------------------------------------------------
void condition_variable::signal() noexcept
{
    pthread_cond_signal(&h);
}
//------------------------------------------------------------------------------
void condition_variable::broadcast() noexcept
{
    pthread_cond_broadcast(&h);
}

}}}} // namespaces

#endif // N_ASYNC_pthread
