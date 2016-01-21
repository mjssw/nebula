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
#ifndef NIC_2837C4CB2CD23F5A_NIC
#define NIC_2837C4CB2CD23F5A_NIC

#include "future.h"
#include "thread.h"
#include "../call_traits.h"
#include <exception>

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
template <class F,
    class R = decltype(declval<F>()()),
    typename disable_if<is_same<R, void>>::type* = nullptr>
inline future<typename ctraits::value<R>::type>
background(F &&f)
{    
    future<typename ctraits::value<R>::type> fut;
    
    auto f_ = 
    [
        prom = fut.promise(),
        f = foundation::forward<F>(f)
    ] () mutable
    {
        try {
            prom.value(f());
        } catch(...) {
            try {
                prom.exception(foundation::current_exception());
            } catch(...) {
                // unable to set an exception - do nothing
                // -> 'broken_promise'
            }
        }
    };
    
    async::thread thr(foundation::move(f_));    
    async::detach(thr);
    
    return fut;
}
//------------------------------------------------------------------------------
template <class F,
    class R = decltype(declval<F>()()),
    typename enable_if<is_same<R, void>>::type* = nullptr>
inline future<void>
background(F &&f)
{    
    future<void> fut;
    
    auto f_ = 
    [
        prom = fut.promise(),
        f = foundation::forward<F>(f)
    ] () mutable
    {        
        try {
            f();
            prom.value();
        } catch(...) {
            try {
                prom.exception(foundation::current_exception());
            } catch(...) {
                // unable to set an exception - do nothing
                // -> 'broken_promise'
            }
        }
    };
    
    async::thread thr(foundation::move(f_));    
    async::detach(thr);
    
    return fut;
}

}}} // namespaces

#endif // NIC_2837C4CB2CD23F5A_NIC
