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
#ifndef NIC_9409D561565974DE_NIC
#define NIC_9409D561565974DE_NIC

#include "vector.h"
#include "iterator.h"
#include "ops.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <
    class T,
    class F = less<T>,
    class Allocator = memory::allocator<T>>
class heap
{
    using container_type = vector<T, Allocator>;
public:
    using allocator_type = Allocator;
    
    using value_type = typename container_type::value_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    
    using size_type = typename container_type::size_type;
    using difference_type = typename container_type::difference_type;
    
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator 
        = typename container_type::const_reverse_iterator;
    
    heap() = default;
    heap(heap &) = default;
    heap(const heap &) = default;
    heap(heap &&) = default;
    
    template <class T_>
    inline heap(std::initializer_list<T_> ilist)
    : v(ilist)
    {
        try {
            foundation::iterator::make_heap(begin(), end(), f);
        } catch(...) {
            v.reset();
            throw;
        }
    }
    template <class T_, class A>
    inline heap(std::initializer_list<T_> ilist, A &&alc)
    : v(ilist, foundation::forward<A>(alc))
    {
        try {
            foundation::iterator::make_heap(begin(), end(), f);
        } catch(...) {
            v.reset();
            throw;
        }
    }
    
    template <class I>
    inline heap(I frst, I lst)
    : v(frst, lst)
    {
        try {
            foundation::iterator::make_heap(begin(), end(), f);
        } catch(...) {
            v.reset();
            throw;
        }
    }
    template <class I, class A>
    inline heap(I frst, I lst, A &&alc)
    : v(frst, lst, foundation::forward<A>(alc))
    {
        try {
            foundation::iterator::make_heap(begin(), end(), f);
        } catch(...) {
            v.reset();
            throw;
        }
    }
    
    heap &operator = (const heap &) = default;
    heap &operator = (heap &&) = default;
    template <class T_>
    heap &operator = (std::initializer_list<T_> ilist)
    {
        container_type x(ilist, v.get_allocator());
        foundation::iterator::make_heap(x.begin(), x.end(), f);
        v = foundation::move(x);
        return *this;
    }
    
    inline void swap(heap &other)
    noexcept(noexcept(foundation::swap(other.f, other.f)))
    {
        foundation::swap(f, other.f);
        foundation::swap(v, other.v);
    }
    
    template <class T_, class A>
    inline void assign(std::initializer_list<T_> ilist, A &&alc)
    {
        container_type x(ilist, foundation::forward<A>(alc));
        foundation::iterator::make_heap(x.begin(), x.end(), f);
        v = foundation::move(x);
    }
    inline void assign(const_pointer p, const size_type n)
    {
        container_type x(p, p + n, v.get_allocator());
        foundation::iterator::make_heap(x.begin(), x.end(), f);
        v = foundation::move(x);
    }
    template <class I>
    inline void assign(I frst, I lst)
    {
        container_type x(frst, lst, v.get_allocator());
        foundation::iterator::make_heap(x.begin(), x.end(), f);
        v = foundation::move(x);
    }
    template <class I, class A>
    inline void assign(I frst, I lst, A &&alc)
    {
        container_type x(frst, lst, foundation::forward<A>(alc));
        foundation::iterator::make_heap(x.begin(), x.end(), f);
        v = foundation::move(x);
    }
    template <class A>
    inline void assign(const_pointer p, const size_type n, A &&alc)
    {
        container_type x(p, p + n, foundation::forward<A>(alc));
        foundation::iterator::make_heap(x.begin(), x.end(), f);
        v = foundation::move(x);
    }
    
    inline iterator begin() noexcept { return v.begin(); }
    inline iterator end() noexcept { return v.end(); }
    inline const_iterator begin() const noexcept { return v.begin(); }
    inline const_iterator end() const noexcept { return v.end(); }
    inline const_iterator cbegin() const noexcept { return v.cbegin(); }
    inline const_iterator cend() const noexcept { return v.cend(); }
    inline iterator rbegin() noexcept { return v.rbegin(); }
    inline iterator rend() noexcept { return v.rend(); }
    inline const_iterator rbegin() const noexcept { return v.rbegin(); }
    inline const_iterator rend() const noexcept { return v.rend(); }
    inline const_iterator crbegin() const noexcept { return v.crbegin(); }
    inline const_iterator crend() const noexcept { return v.crend(); }
    
    inline pointer data() noexcept { return v.data(); }
    inline const_pointer data() const noexcept { return v.data(); }
    
    inline reference front() { return v.front(); }
    inline constexpr const_reference front() const { return v.front(); }
    inline reference back() { return v.back(); }
    inline constexpr const_reference back() const { return v.back(); }
    
    inline bool empty() const noexcept { return v.empty(); }
    inline size_type size() const noexcept { return v.size(); }
    inline size_type capacity() const noexcept { return v.capacity(); }
    
    inline void reserve(size_type x)
    {
        v.reserve(x);
    }
    
    template <class ... X>
    inline void emplace(X && ... x)
    {
        v.emplace_back(foundation::forward<X>(x)...);
        foundation::iterator::push_heap(begin(), end(), f);
    }
    
    inline void pop_front() {
        foundation::iterator::pop_heap(begin(), end(), f);
        v.pop_back();
    }
    
    inline vector<T, Allocator> get_sorted()
    {
        vector<T, Allocator> r(v);
        foundation::iterator::sort_heap(r.begin(), r.end(), f);
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
    F f;
    container_type v;
};

/** @} */

}} // namespaces

#endif // NIC_9409D561565974DE_NIC