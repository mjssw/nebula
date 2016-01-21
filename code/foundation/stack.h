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
#ifndef NIC_FB12924BD2DD8E93_NIC
#define NIC_FB12924BD2DD8E93_NIC

#include "vector.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T, class Allocator = memory::allocator<T>>
class stack
{
    using vector_type = vector<T, Allocator>;
    
public:
    using allocator_type = Allocator;
    using value_type = typename memory::allocator_value<allocator_type>::type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    
    stack() = default;
    stack(stack &) = default;
    stack(const stack &) = default;
    stack(stack &&) = default;
    
    inline stack(const allocator_type &alc)
    : v(allocator_type(alc))
    {}
    inline stack(allocator_type &&alc)
    : v(allocator_type(foundation::move(alc)))
    {}
    
    stack &operator = (const stack &other) = default;
    stack &operator = (stack &&other) = default;
    
    inline void swap(stack &other) noexcept
    {
        foundation::swap(v, other.v);
    }
    
    reference back() noexcept {
        return v.back();
    }
    const_reference back() const noexcept {
        return v.back();
    }
    
    inline void reserve(const size_type n) {
        v.reserve(n);
    }
    
    template <class ... X>
    inline void emplace_back(X && ... x)
    {
        v.emplace_back(foundation::forward<X>(x)...);
    }
    inline void push_back(const_reference x)
    {
        this->emplace_back(x);
    }
    inline void push_back(value_type &&x)
    {
        this->emplace_back(foundation::move(x));
    }
    
    inline void pop_back() noexcept
    {
        v.pop_back();
    }
    
    inline void push(const_reference x) {
        this->push_back(x);
    }
    inline void push(value_type &&x) {
        this->push_back(foundation::move(x));
    }
    inline void pop() noexcept {
        pop_back();
    }
    
    inline void reset() noexcept
    {
        v.reset();
    }
    inline void clear() noexcept {
        v.clear();
    }
    
    inline bool empty() const noexcept {
        return v.empty();
    }
    inline size_type size() const noexcept {
        return v.size();
    }
    inline size_type capacity() const noexcept {
        return v.capacity();
    }
    
    inline allocator_type get_allocator() const noexcept {
        return v.get_allocator();
    }
    
private:    
    vector_type v;
};

/** @} */

}} // namespaces

#endif // NIC_FB12924BD2DD8E93_NIC