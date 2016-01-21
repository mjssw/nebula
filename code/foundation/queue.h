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
#ifndef NIC_C8007E76F72F8F70_NIC
#define NIC_C8007E76F72F8F70_NIC

#include "vector.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T, class Allocator = memory::allocator<T>>
class queue
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
    
    inline queue()
    : pos(pointer()), beg_(pointer()), end_(pointer()), fin_(pointer())
    {}
    inline queue(queue &other)
    : pos(pointer()), beg_(pointer()), end_(pointer()), fin_(pointer()),
    b(other.copied())
    {}
    inline queue(const queue &other)
    : pos(pointer()), beg_(pointer()), end_(pointer()), fin_(pointer()),
    b(other.copied())
    {}
    inline queue(queue &&other) noexcept
    : pos(other.pos), beg_(other.beg_), end_(other.end_), fin_(other.fin_),
    b(foundation::move(other.b))
    {
        other.invalidate();
    }
    
    inline queue(const allocator_type &alc)
    : b(allocator_type(alc))
    {}
    inline queue(allocator_type &&alc)
    : b(allocator_type(foundation::move(alc)))
    {}
    
    inline queue &operator = (const queue &other) {
        if(this == &other)
            return *this;
        vector_type tmp = other.copied();
        this->reset();
        b.adopt(tmp.transfer(), tmp.get_allocator()); // fail-safe
        return *this;
    }
    inline queue &operator = (queue &&other) noexcept
    {
        this->reset();
        beg_ = other.beg_;
        pos = other.pos;
        end_ = other.end_;
        fin_ = other.fin_;
        b = foundation::move(other.b);
        return *this;
    }
    inline ~queue() noexcept {
        this->reset();
    }
    
    inline void swap(queue &other) noexcept
    {
        foundation::swap(beg_, other.beg_);
        foundation::swap(pos, other.pos);
        foundation::swap(end_, other.end_);
        foundation::swap(fin_, other.fin_);
        b.swap(other.b);
    }
    
    reference front() noexcept {
        return pos == end_ ? b.front() : *pos;
    }
    const_reference front() const noexcept {
        return pos == end_ ? b.front() : *pos;
    }
    
    inline void reserve(const size_type n) {
        b.reserve(n);
    }
    
    template <class ... X>
    inline void emplace_back(X && ... x)
    {
        b.emplace_back(foundation::forward<X>(x)...);
    }
    inline void push_back(const_reference x)
    {
        this->emplace_back(x);
    }
    inline void push_back(value_type &&x)
    {
        this->emplace_back(foundation::move(x));
    }
    
    inline void pop_front() noexcept
    {
        if(pos == end_)
        {
            // This is basically a swap operation.
            auto x = b.dismiss();
            b.adopt(beg_, beg_, fin_);
            foundation::tie(beg_, end_, fin_) = x;
            pos = beg_;
        }
        memory::destroy(b.get_allocator(), pos++);
    }
    
    inline void push(const_reference x) {
        this->push_back(x);
    }
    inline void push(value_type &&x) {
        this->push_back(foundation::move(x));
    }
    inline void pop() noexcept {
        pop_front();
    }
    
    inline void reset() noexcept
    {
        for( ; pos != end_; ++pos)
            memory::destroy(b.get_allocator(), pos);
        memory::deallocate(b.get_allocator(), beg_, fin_-beg_);
        
        beg_ = pos = end_ = fin_ = pointer();

        b.reset();
    }
    inline void clear() noexcept {
        this->reset();
    }
    
    inline bool empty() const noexcept {
        return size() == 0;
    }
    inline size_type size() const noexcept {
        return (end_-pos) + b.size();
    }
    inline size_type capacity() const noexcept {
        return (fin_-beg_) + b.capacity();
    }
    
    inline allocator_type get_allocator() const noexcept {
        return b.get_allocator();
    }
    
private:
    inline vector_type copied() const
    {
        vector_type tmp(b.get_allocator());
        tmp.reserve(size());
        tmp.append(pos, end_);
        tmp.append(b.begin(), b.end());
        return tmp;
    }
    inline void invalidate()
    {
        beg_ = pos = end_ = fin_ = pointer();
    }
    
    pointer pos;
    pointer beg_, end_, fin_;
    vector_type b;
};

/** @} */

}} // namespaces

#endif // NIC_C8007E76F72F8F70_NIC
