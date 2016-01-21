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
#ifndef NIC_276F77E6DCDD7FA3_NIC
#define NIC_276F77E6DCDD7FA3_NIC

#include "../exception.h"
#include "../../common.h"
#include "../../scoped_unlock.h"
#include "../../../move.h"
#include "../../../scope_exit.h"
#include "../../../ptr.h"
#include "../../../tagged_type.h"
#include "../../../variant.h"

namespace nebula { namespace foundation { namespace async {
namespace future_detail {
//------------------------------------------------------------------------------
using tagged_exception_ptr_t = tagged_type<
        exception_ptr,
        struct future_backend_exc_>;
//------------------------------------------------------------------------------
template <class T>
struct future_backend_base : public ref_counted
{
protected:
    variant<T, tagged_exception_ptr_t> var;
};

template <>
struct future_backend_base<void> : public ref_counted
{
protected:
    exception_ptr exc;
};
//------------------------------------------------------------------------------
template <class T>
class future_backend : public future_backend_base<T>
{
    enum class state
    {
        ready,
        pending,
        consumed,
        broken
    };

public:
    using value_type = T;
    
    inline future_backend()
    : st(state::pending)
    {}
    future_backend(future_backend &) = delete;
    future_backend(const future_backend &) = delete;
    future_backend(future_backend &&) = default;
    
    inline ~future_backend() noexcept
    {}
    
    future_backend &operator = (const future_backend &) = delete;
    future_backend &operator = (future_backend &&) = default;
    
    template <class ... X,
        class Cond = value_type,
        typename disable_if<is_same<Cond, void>>::type* = nullptr>
    inline void value(X && ... x)
    {        
        if(st != state::pending)
            n_throw(promise_fulfilled);
        
        try {
            this->var = value_type(foundation::forward<X>(x) ...);
        } catch(...) {
            async::lock(mtx);
            n_scoped_unlock(mtx);
            n_scope_exit(&) { async::broadcast(cond); };
            st = state::broken;
            throw;
        }
        
        async::lock(mtx);
        n_scoped_unlock(mtx);
        n_scope_exit(&) { async::broadcast(cond); };
        st = state::ready;
    }
    template <class Cond = value_type,
        typename enable_if<is_same<Cond, void>>::type* = nullptr>
    inline void value()
    {        
        if(st != state::pending)
            n_throw(promise_fulfilled);
        
        async::lock(mtx);
        n_scoped_unlock(mtx);
        n_scope_exit(&) { async::broadcast(cond); };
        st = state::ready;
    }
    template <class X,
        class Cond = value_type,
        typename disable_if<is_same<Cond, void>>::type* = nullptr>
    inline void exception(X &&x)
    {        
        if(st != state::pending)
            n_throw(promise_fulfilled);
        
        try {
            this->var = tagged_exception_ptr_t{foundation::forward<X>(x)};
        } catch(...) {
            async::lock(mtx);
            n_scoped_unlock(mtx);
            n_scope_exit(&) { async::broadcast(cond); };
            st = state::broken;
            throw;
        }
        
        async::lock(mtx);
        n_scoped_unlock(mtx);
        n_scope_exit(&) { async::broadcast(cond); };
        st = state::ready;
    }
    template <class X,
        class Cond = value_type,
        typename enable_if<is_same<Cond, void>>::type* = nullptr>
    inline void exception(X &&x)
    {        
        if(st != state::pending)
            n_throw(promise_fulfilled);
        
        try {
            this->exc = foundation::forward<X>(x);
        } catch(...) {
            async::lock(mtx);
            n_scoped_unlock(mtx);
            n_scope_exit(&) { async::broadcast(cond); };
            st = state::broken;
            throw;
        }
        
        async::lock(mtx);
        n_scoped_unlock(mtx);
        n_scope_exit(&) { async::broadcast(cond); };
        st = state::ready;
    }
    
    inline void wait()
    {
        switch(st)
        {
        case state::ready:
            return;
        case state::broken:
            n_throw(broken_promise);
            return;
        case state::consumed:
            n_throw(invalid_future);
            return;
        default: break; // pending
        }
        
        async::lock(mtx);
        n_scoped_unlock(mtx);
        
        while(st == state::pending)
            async::wait(cond, mtx);
            
        switch(st)
        {
        case state::broken:
            n_throw(broken_promise);
        case state::consumed:
            n_throw(invalid_future);
        default: break;
        }
    }
    template <class Duration>
    inline bool wait_for(const Duration &dur)
    {
        switch(st)
        {           
        case state::ready:
            return true;
        case state::broken:
            n_throw(broken_promise);
            break;
        case state::consumed:
            n_throw(invalid_future);
            break;
        default: break; // pending
        }
            
        async::lock(mtx);
        n_scoped_unlock(mtx);
        
        const bool ret = async::wait_for(
            cond, mtx, dur, [&](){return st != state::pending;});
            
        switch(st)
        {
        case state::broken:
            n_throw(broken_promise);
        case state::consumed:
            n_throw(invalid_future);
        default: break;
        }
        return ret;
    }
    
    template <class Cond = value_type,
        typename disable_if<is_same<Cond, void>>::type* = nullptr>
    inline value_type get()
    {        
        this->wait();
        
        st = state::consumed;
        
        if(this->var.index() == 1)
            foundation::rethrow_exception(
                foundation::move(
                variant_cast<tagged_exception_ptr_t>(this->var).value));
        
        return foundation::move(variant_cast<value_type>(this->var));
    }
    template <class Cond = value_type,
        typename enable_if<is_same<Cond, void>>::type* = nullptr>
    inline void get()
    {        
        this->wait();
        
        st = state::consumed;
        
        if(this->exc)
            foundation::rethrow_exception(foundation::move(this->exc));
    }
    
    inline bool valid() const noexcept {
        return st == state::ready || st == state::pending;
    }
    
private:
    async::mutex mtx;
    async::condition_variable cond;
    volatile state st;
};

}}}} // namespaces

#endif // NIC_276F77E6DCDD7FA3_NIC
