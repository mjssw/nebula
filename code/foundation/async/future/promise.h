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
#ifndef NIC_C456ED732DD0C788_NIC
#define NIC_C456ED732DD0C788_NIC

#include "detail/future_backend.h"
#include "../../assert.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
template <class T = void>
class promise
{
public:
    using value_type = T;
    
    promise(promise &) = default;
    promise(const promise &) = default;
    promise(promise &&) = default;
    
    promise &operator = (const promise &) = default;
    promise &operator = (promise &&) = default;
    
    template <class ... X>
    inline void value(X && ... x)
    {
        impl->value(foundation::forward<X>(x)...);
    }
    template <class X>
    inline void exception(X &&x)
    {
        impl->exception(foundation::forward<X>(x));
    }
    
private:    
    inline promise(
        const intrusive_ptr<future_detail::future_backend<T>> &x)
    : impl(x)
    {
        n_assert(impl != nullptr);
    }
    
    intrusive_ptr<future_detail::future_backend<T>> impl;
    
    template <class Q>
    friend class future;
};

}}} // namespaces

#endif // NIC_C456ED732DD0C788_NIC
