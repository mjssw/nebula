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
#include "thread_pool.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
void thread_pool::init(const size_t n)
{
    threads = memory::allocate(thread_alloc, n);
    try 
    {
        this->shared = new shared_state;
        
        for( ; n_threads < n; ++n_threads)
        {
            memory::construct(
                thread_alloc, 
                threads+n_threads,
                worker(shared));
        }
    }
    catch(...)
    {
        this->shutdown();
        throw;
    }
}
//------------------------------------------------------------------------------
void thread_pool::shutdown() noexcept
{
    if(threads)
    {            
        async::lock(shared->job_q_mtx);
        shared->stop = true;
        async::unlock(shared->job_q_mtx);
        async::broadcast(shared->job_q_cv);
        
        for(size_t i = 0; i < n_threads; ++i)
        {
            async::join(threads[i]);
            memory::destroy(thread_alloc, threads+i);
        }
        memory::deallocate(thread_alloc, threads, n_threads);
        threads = nullptr;
    }
    if(shared)
    {
        delete shared;
        shared = nullptr;
    }
}
//------------------------------------------------------------------------------
void thread_pool::worker::operator () () noexcept
{
    while(true)
    {
        async::lock(shared->job_q_mtx);
        auto sul_ = async::sul(shared->job_q_mtx);
        
        while(shared->job_q.empty() && !shared->stop)
            async::wait(shared->job_q_cv, shared->job_q_mtx);
        
        if(shared->stop)
            break;
                        
        job_t j = foundation::move(shared->job_q.front());
        shared->job_q.pop();
        async::unlock(shared->job_q_mtx);
        sul_.dismiss();
        
        j();
    }
    while(true)
    {
        async::lock(shared->job_q_mtx);
        auto sul_ = async::sul(shared->job_q_mtx);
        
        if(shared->job_q.empty())
            break;
            
        job_t j = foundation::move(shared->job_q.front());
        shared->job_q.pop();
        async::unlock(shared->job_q_mtx);
        sul_.dismiss();
        
        j();
    }
}

}}} // namespaces
