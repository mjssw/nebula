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

#include "posix_thread.h"
#include "../../assert.h"
#include "../../system_error.h"
#include "../../scope_exit.h"

#include <limits.h> // PTHREAD_STACK_MIN

//------------------------------------------------------------------------------
static void *nebula_thread_routine(void *p) // don't declare as noexcept
{
    using namespace nebula::foundation;
    
    n_assert(p);
    function<void ()> *pf = reinterpret_cast<function<void ()>*>(p);
    try {
        pf->operator () ();
    } catch(...) {
        std::terminate();
    }
    try {
        delete pf;
    }
    catch(...) {
        std::terminate();
    }
    ::pthread_exit(nullptr);
}

//------------------------------------------------------------------------------
namespace nebula { namespace foundation { namespace async { namespace posix {
//------------------------------------------------------------------------------
void thread::create_(typename thread::func_t f)
{
    typename thread::func_t *pf = new func_t(foundation::move(f));
    const int r = ::pthread_create(&h, nullptr, &nebula_thread_routine, pf);
    if(r != 0)
    {
        try {
            delete pf;
        }
        catch(...) {
            std::terminate();
        }
        
        n_throw(system::system_error)
            << ei_msg_c("pthread_create() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
}
//------------------------------------------------------------------------------
thread::~thread() noexcept 
{
    if(is_joinable())
    {
        try { this->join(); }
        catch(...) {
            throw; // results in std::terminate();
        }
    }
}
//------------------------------------------------------------------------------
void thread::join()
{
    if(!is_joinable())
    {
        n_throw(system::system_error)
            << ei_msg_c("Attempt to join non-joinable thread.");
    }
    
    void *rult;
    const int r = ::pthread_join(h, &rult);
    ::free(rult);
    jable = false;
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_join() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
}
//------------------------------------------------------------------------------
void thread::detach()
{
    if(!is_joinable())
    {
        n_throw(system::system_error)
            << ei_msg_c("Attempt to detach non-joinable thread.");
    }
    const int r = ::pthread_detach(h);
    if(r != 0)
    {
        n_throw(system::system_error)
            << ei_msg_c("pthread_detach() failed.")
            << system::ei_error_code(system::error_code(
                r, system::system_category()));
    }
    jable = false;
}

}}}} // namespaces

#endif // N_ASYNC_pthread
