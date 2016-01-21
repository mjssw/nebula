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
#ifndef NIC_FACBA6DAE7F15EB6_NIC
#define NIC_FACBA6DAE7F15EB6_NIC

#include "posix_mutex.h"
#include "../config.h"
#include "../../dll_interface.h"
#include "../../chrono.h"

#include <pthread.h>

namespace nebula { namespace foundation { namespace async { namespace posix {
//------------------------------------------------------------------------------
/** @warning Spurious wake-ups may happen.
 * @todo Looks like there is no way to implement wait_until() in posix? 
 * */
class n_foundation_dll condition_variable
{
public:
    using native_handle_type = pthread_cond_t;
    
    condition_variable();
    ~condition_variable() noexcept;
    
    inline void wait(posix::mutex &m)
    {
        this->wait(m.native_handle());
    }
    /** @warning crono::monotonic_clock must be based on CLOCK_MONOTONIC. */
    template <class D>
    inline bool wait_for(posix::mutex &m, const D &t)
    {
        const chrono::timespec ts = chrono::to_timespec(
            chrono::monotonic_clock::now() + t);            
        return this->timed_wait(m.native_handle(), ts);
    }
    template <class D, class F>
    inline bool wait_for(posix::mutex &m, const D &t, F &&f)
    {            
        const chrono::timespec ts = chrono::to_timespec(
            chrono::monotonic_clock::now() + t);
        
        while(!f())
        {
            if(!this->timed_wait(m.native_handle(), ts))
                return f();
        }
        
        return true;
    }
//     template <class Clock, class D>
//     inline bool wait_until(posix::mutex &m, const D &tpoint)
//     {
//         return this->timed_wait(
//             m.native_handle(), chrono::to_timespec(tpoint));
//     }
    
    void signal() noexcept;
    void broadcast() noexcept;
    
    inline native_handle_type &native_handle() noexcept {
        return h;
    }
    inline const native_handle_type &native_handle() const noexcept {
        return h;
    }
    
private:
    void wait(pthread_mutex_t &);
    bool timed_wait(pthread_mutex_t &, const chrono::timespec &);
    
    bool alive; /// @todo needed?
    native_handle_type h;
};

}}}} // namespaces

#endif // NIC_FACBA6DAE7F15EB6_NIC
