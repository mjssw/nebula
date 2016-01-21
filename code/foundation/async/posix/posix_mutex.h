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
#ifndef NIC_EC2D4E0E696F769F_NIC
#define NIC_EC2D4E0E696F769F_NIC

#include "../config.h"
#include "../../dll_interface.h"
#include "../../move.h"
#include "../../swap.h"
#include "../../chrono.h"

#include <pthread.h>

namespace nebula { namespace foundation { namespace async { namespace posix {
//------------------------------------------------------------------------------
/** @todo Looks like there is no way to implement try_lock_until() in posix?
 * @todo Find a way to not use CLOCK_REALTIME in pthread_mutex_timedlock.
 * */
class n_foundation_dll mutex
{
    using handle_t = pthread_mutex_t;
    using sec_t = chrono::seconds;
    using nsec_t = chrono::nanoseconds;
    
public:
    using native_handle_type = handle_t;
    
    mutex(bool recursive = false);
    inline mutex(mutex &&other) noexcept
    : h(other.h), alive(other.alive)
    {}
    ~mutex() noexcept;
    
    inline mutex &operator = (mutex &&other) noexcept {
        this->~mutex();
        h = other.h;
        alive = other.alive;
        return *this;
    }
    
    inline void swap(mutex &other) noexcept
    {
        foundation::swap(h, other.h);
        foundation::swap(alive, other.alive);
    }
    
    void lock();
    bool try_lock();
    /** @warning chrono::system_clock must be based on CLOCK_REALTIME, thus
     * this function might actually delivers unexpected results due to clock
     * adjustments. Read: Avoid if possible!
     * */
    template <class D>
    bool try_lock_for(const D &t)
    {
        const chrono::timespec ts = chrono::to_timespec(
            chrono::system_clock::now() + t);
        return timed_lock(ts);
    }
//     template <class Clock, class D>
//     bool try_lock_until(const D &tpoint)
//     {
//         return timed_lock(chrono::to_timespec(tpoint));
//     }
    void unlock();
    
    inline handle_t &native_handle() noexcept {
        return h;
    }
    inline const handle_t &native_handle() const noexcept {
        return h;
    }
    
private:
    bool timed_lock(const chrono::timespec &t);
    
    handle_t h;
    bool alive; /// @todo needed?
};

}}}} // namespaces

#endif // NIC_EC2D4E0E696F769F_NIC