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
#ifndef NIC_38204CB2C8BBA5A0_NIC
#define NIC_38204CB2C8BBA5A0_NIC

#include "../common.h"
#include "../future.h"
#include "../scoped_unlock.h"
#include "../../function.h"
#include "../../queue.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
/** Simple implementation of the thread pool pattern.
 *
 *  This class creates a specified number of background threads which are used
 *  to execute arbitrary functions.
 *  Such functions may have a return value but are not allowed to accept
 *  any arguments. Another restriction is that they must be nothrow
 *  move-assignable and nothrow move-constructible.
 *  
 *  A certain function F can be enqueued using the member add(), thereby F
 *  gets copied (or moved) into an internal queue and a signal is sent to
 *  waiting threads that a new function to execute has become available.
 *  Then a thread, which is chosen according to the kernel's scheduling policy,
 *  removes F (using move-construction) from the internal queue,
 *  executes and also destructs it.
 *
 *  Choosing more threads than can be supported by the hardware will result in
 *  poor performance. Also add()'ed functions should be of sufficient complexity
 *  to outweigh the overhead of thread synchronization, context switches, etc.
 *
 *  @warning The execution order of added functions is not specified, but the
 *  order in which background threads collect functions from the queue follows
 *  the FIFO principle.
 *  @warning If a function has been enqueued then it will be destructed by
 *  the same thread which will also call it.
 *  @warning The effect of an enqueued function's move-assignment operator or
 *  move-constructor throwing an exception is unspecified.
 *  @warning Functions, when executed, should return in a timely manner to 
 *  prevent congestion of the internal queue.
 *
 *  @note This class is nothrow-movable and not copyable.
 * */
class n_foundation_dll thread_pool
{    
    using job_t = function<void ()>;
    
    using job_queue_t = queue<job_t>;
    
    struct shared_state
    {
        inline shared_state()
        : stop(false)
        {}
        
        bool stop;
        job_queue_t job_q;
        condition_variable job_q_cv;
        mutex job_q_mtx;
    };
    
    class worker
    {
    public:
        inline worker(shared_state *ss) noexcept
        : shared(ss)
        {}
        
        void operator () () noexcept;

    private:        
        shared_state *shared;
    };
    
public:
    thread_pool(const size_t n)
    : threads(nullptr), n_threads(0), shared(nullptr)
    {
        if(n == 0)
            n_throw(logic_error);
        this->init(n);
    }
    thread_pool(thread_pool &) = delete;
    thread_pool(const thread_pool &) = delete;
    inline thread_pool(thread_pool &&other) noexcept
    : threads(other.threads), n_threads(other.n_threads), shared(other.shared)
    {
        other.invalidate();
    }
    
    inline ~thread_pool() noexcept
    {
        this->shutdown();
    }
    
    thread_pool &operator = (const thread_pool &) = delete;
    inline thread_pool &operator = (thread_pool &&other) noexcept 
    {
        this->threads = other.threads;
        this->n_threads = other.n_threads;
        this->shared = other.shared;
        other.invalidate();
    }
    
    template <class F, 
        class R = decltype(declval<F>()()),
        typename disable_if<is_same<R, void>>::type* = nullptr>
    inline future<R> add(F &&f)
    {
        future<R> fut;
        promise<R> prom = fut.promise();
        
        async::lock(shared->job_q_mtx);
        n_scoped_unlock(shared->job_q_mtx);
        shared->job_q.emplace_back(
            [prom_ = foundation::move(prom),
            f_ = foundation::forward<F>(f)] () mutable
            {
                try {
                    prom_.value(f_());
                } catch(...) {
                    try {
                        prom_.exception(current_exception());
                    } catch(...) {
                        // unable to set an exception - do nothing
                        // results in 'broken_promise'
                    }
                }
            });
        async::signal(shared->job_q_cv);
        return fut;
    }
    template <class F, 
        class R = decltype(declval<F>()()),
        typename enable_if<is_same<R, void>>::type* = nullptr>
    inline future<void> add(F &&f)
    {
        future<void> fut;
        promise<void> prom = fut.promise();
        
        async::lock(shared->job_q_mtx);
        n_scoped_unlock(shared->job_q_mtx);
        shared->job_q.emplace_back(
            [prom_ = foundation::move(prom),
            f_ = foundation::forward<F>(f)] () mutable
            {
                try {
                    f_();
                    prom_.value();
                } catch(...) {
                    try {
                        prom_.exception(current_exception());
                    } catch(...) {
                        // unable to set an exception - do nothing
                        // results in 'broken_promise'
                    }
                }
            });
        async::signal(shared->job_q_cv);
        return fut;
    }    

private:
    void init(const size_t n);
    void shutdown() noexcept;
    inline void invalidate() noexcept
    {
        threads = nullptr;
        n_threads = 0;
        shared = nullptr;
    }

    thread *threads;
    size_t n_threads;
    memory::allocator<thread> thread_alloc;
    shared_state *shared;
};

}}} // namespaces

#endif // NIC_38204CB2C8BBA5A0_NIC
