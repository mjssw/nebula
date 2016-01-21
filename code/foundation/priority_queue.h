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
#ifndef NIC_45147243DF7BE35D_NIC
#define NIC_45147243DF7BE35D_NIC

#include "heap.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <
    class T,
    class F = less<T>,
    class Allocator = memory::allocator<T>>
class priority_queue
{
    using container_type = heap<T, F, Allocator>;
public:
    using allocator_type = Allocator;
    
    using value_type = typename container_type::value_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    
    using size_type = typename container_type::size_type;
    using difference_type = typename container_type::difference_type;
    
    priority_queue() = default;
    priority_queue(priority_queue &) = default;
    priority_queue(const priority_queue &) = default;
    priority_queue(priority_queue &&) = default;
    
    priority_queue &operator = (const priority_queue &) = default;
    priority_queue &operator = (priority_queue &&) = default;
    
    inline reference front() { return v.front(); }
    inline constexpr const_reference front() const { return v.front(); }
    
    inline bool empty() const noexcept { return v.empty(); }
    inline size_type size() const noexcept { return v.size(); }
    inline size_type capacity() const noexcept { return v.capacity(); }
    
    inline void reserve(size_type n)
    {
        v.reserve(v);
    }
    
    template <class ... X>
    inline void emplace(X && ... x)
    {
        v.emplace(foundation::forward<X>(x)...);
    }
    template <class ... X>
    inline void push(X && ... x)
    {
        v.emplace(foundation::forward<X>(x)...);
    }
    
    inline void pop_front() {
        v.pop_front();
    }
    inline void pop() {
        v.pop_front();
    }
    
    inline void clear() noexcept {
        v.clear();
    }
    inline void reset() noexcept {
        v.reset();
    }
    
    inline allocator_type get_allocator() const noexcept {
        return v.get_allocator();
    }
    
private:
    container_type v;
};

/** @} */

}} // namespaces

#endif // NIC_45147243DF7BE35D_NIC