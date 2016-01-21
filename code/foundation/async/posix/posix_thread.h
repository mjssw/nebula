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
#ifndef NIC_5EB4BEFD789EEEB1_NIC
#define NIC_5EB4BEFD789EEEB1_NIC

#include "../config.h"
#include "../../dll_interface.h"
#include "../../function.h"
#include "../../move.h"
#include "../../swap.h"

#include <exception> // std::terminate

#include <pthread.h>

namespace nebula { namespace foundation { namespace async { 
namespace posix {
//------------------------------------------------------------------------------
/** Executes a function f within a new thread. exceptions thrown by f() or
 * f::~f() result in immediate program termination.
 * */
class n_foundation_dll thread
{
    using func_t = function<void ()>;
    
public:
    using native_handle_type = ::pthread_t;
    
    template <class F>
    inline thread(F &&f)
    : jable(true)
    {
        this->create_(foundation::forward<F>(f));
    }
    inline thread(thread &&other) noexcept
    : h(other.h), jable(other.jable)
    {
        other.jable = false;
    }
    ~thread() noexcept;
    
    inline thread &operator = (thread &&other) noexcept {
        if(is_joinable())
            std::terminate();
        h = other.h;
        jable = other.jable;
        other.jable = false;
    }
    
    inline void swap(thread &other) noexcept {
        foundation::swap(h, other.h);
        foundation::swap(jable, other.jable);
    }
    
    void join();
    void detach();
    inline bool is_joinable() const noexcept { return jable; }
    
    inline native_handle_type &native_handle() noexcept {
        return h;
    }
    inline const native_handle_type &native_handle() const noexcept {
        return h;
    }
    
private:
    void create_(func_t);

    ::pthread_t h;
    bool jable;
};

}}}} // namespaces

#endif // NIC_5EB4BEFD789EEEB1_NIC