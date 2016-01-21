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
#ifndef NIC_FF6E03223CBF4A54_NIC
#define NIC_FF6E03223CBF4A54_NIC

#include "iterator.h"
#include "assert.h"
#include "swap.h"
#include "exception/exception.h"
#include "get.h"
#include "hash.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** 
 * */
template <class T, size_t N, 
    class Allocator = memory::allocator<T>>
struct dynamic_array
{
    using allocator_type = Allocator;
    
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = iterator::reverse_iterator<iterator>;
    using const_reverse_iterator = iterator::reverse_iterator<const_iterator>;
    
    inline dynamic_array() noexcept(N == 0)
    : v(nullptr)
    {   
        if(N)
            v = memory::allocate(alloc, N);
    }
    inline dynamic_array(dynamic_array &other) noexcept(N == 0)
    : v(nullptr), alloc(memory::socc(other.alloc))
    {
        cc_from(other);
    }
    inline dynamic_array(const dynamic_array &other) noexcept(N == 0)
    : v(nullptr), alloc(memory::socc(other.alloc))
    {
        cc_from(other);
    }
    template <class A>
    inline dynamic_array(const dynamic_array &other, A &&alc) noexcept(N == 0)
    : v(nullptr), alloc(foundation::forward<A>(alc))
    {
        cc_from(other);
    }
    inline dynamic_array(dynamic_array &&other) noexcept
    : v(other.v), alloc(foundation::move(other.alloc))
    {
        other.v = nullptr;
    }
    template <class A>
    inline dynamic_array(dynamic_array &&other, A &&alc) noexcept
    : v(other.v), alloc(foundation::forward<A>(alc))
    {
        other.v = nullptr;
    }
    template <class X>
    inline dynamic_array(std::initializer_list<X> lst)
    : dynamic_array(lst.begin(), lst.end())
    {}
    template <class X, class A>
    inline dynamic_array(std::initializer_list<X> lst, A &&alc)
    : dynamic_array(lst.begin(), lst.end(), foundation::forward<A>(alc))
    {}
    
    inline dynamic_array(const allocator_type &alc)
    : v(nullptr), alloc(alc)
    {
        if(N)
            v = memory::allocate(alloc, N);
    }
    inline dynamic_array(allocator_type &&alc)
    : v(nullptr), alloc(foundation::move(alc))
    {
        if(N)
            v = memory::allocate(alloc, N);
    }
    
    template <class I>
    inline dynamic_array(I first, I last)
    : v(nullptr)
    {
        if(N == iterator::distance(first, last))
        {
            if(N)
            {
                v = memory::allocate(alloc, N);
                copy_construct_delete_(
                    first, last, v, alloc);
            }
        }
        else
            n_throw(out_of_range);
    }
    template <class I, class A>
    inline dynamic_array(I first, I last, A &&alc)
    : v(nullptr), alloc(foundation::forward<A>(alc))
    {
        if(N == iterator::distance(first, last))
        {
            if(N)
            {
                v = memory::allocate(alloc, N);
                copy_construct_delete_(
                    first, last, v, alloc);
            }
        }
        else
            n_throw(out_of_range);
    }
    
    inline ~dynamic_array() noexcept
    {
        kill();
    }
    
    inline void swap(dynamic_array &other) noexcept
    {
        foundation::swap(v, v);
        foundation::swap(alloc, alloc);
    }
    
    /** @attention Weak exception guarantee. 
     * */
    inline dynamic_array &operator = (const dynamic_array &other)
    {
        iterator::copy(other.begin(), other.end(), v);
        return *this;
    }
    inline dynamic_array &operator = (dynamic_array &&other) noexcept
    {
        kill();
        alloc = foundation::move(other.alloc);
        v = other.v;
        other.v = nullptr;
    }
    
    template <class X>
    inline dynamic_array &assign(std::initializer_list<X> lst)
    {
        return assign(lst.begin(), lst.end());
    }
    template <class I>
    inline dynamic_array &assign(I first, I last)
    {
        if(N == iterator::distance(first, last))
        {
            if(N)
            {
                T *new_v = memory::allocate(alloc, N);
                copy_construct_delete_(
                    first, last, new_v, alloc);
                kill();
                v = new_v;
            }
        }
        else
            n_throw(out_of_range);
        
        return *this;
    }
    
    inline T *dismiss() noexcept {
        T *x = v;
        v = nullptr;
        return x;
    }
    inline void adopt(T *x) noexcept {
        kill();
        v = x;
    }
    
    inline iterator begin() noexcept { return v; }
    inline iterator end() noexcept { return v+N; }
    inline const_iterator begin() const noexcept { return v; }
    inline const_iterator end() const noexcept { return v+N; }
    inline const_iterator cbegin() const noexcept { return v; }
    inline const_iterator cend() const noexcept { return v+N; }
    
    inline reverse_iterator rbegin() noexcept { 
        return reverse_iterator(end());
    }
    inline reverse_iterator rend() noexcept { 
        return reverse_iterator(begin());
    }
    inline const_reverse_iterator rbegin() const noexcept { 
        return const_reverse_iterator(end());
    }
    inline const_reverse_iterator rend() const noexcept { 
        return const_reverse_iterator(begin());
    }
    inline const_reverse_iterator crbegin() const noexcept { 
        return const_reverse_iterator(cend());
    }
    inline const_reverse_iterator crend() const noexcept { 
        return const_reverse_iterator(cbegin());
    }
    
    inline pointer data() noexcept { return v; }
    inline const_pointer data() const noexcept { return v; }
    
    inline reference front() { return v[0]; }
    inline constexpr const_reference front() const { return v[0]; }
    inline reference back() { return v[N-1]; }
    inline constexpr const_reference back() const { return v[N-1]; }
    
    inline constexpr size_t size() const noexcept { return N; }
    inline constexpr size_t max_size() const noexcept { return N; }
    inline constexpr bool empty() const noexcept { return N == 0; }
    
    inline constexpr const_reference operator [] (const size_type i) const {
        return v[i];
    }
    inline reference operator [] (const size_type i) {
        return v[i];
    }
    inline const_reference at(const size_type i) const {
        if(i >= size())
            n_throw(out_of_range);
        return v[i];
    }
    inline reference at(const size_type i) {
        if(i >= size())
            n_throw(out_of_range);
        return v[i];
    }
    
    inline void fill(const value_type &x) {
        iterator::fill(begin(), end(), x);
    }
    
    template <size_t I>
    inline reference get() noexcept {
        n_static_assert(I < N, "Index out of range.");
        return v[I];
    }
    template <size_t I>
    inline constexpr const_reference get() const noexcept {
        n_static_assert(I < N, "Index out of range.");
        return v[I];
    }
    
    inline allocator_type get_allocator() const noexcept {
        return alloc;
    }
    
private:
    inline void cc_from(const dynamic_array &other) noexcept(N == 0)
    {
        if(N)
        {
            v = memory::allocate(alloc, N);
            try
            {
                copy_construct_delete_(other.begin(), other.end(), v, alloc);
            }
            catch(...)
            {
                v = nullptr;
                throw;
            }            
        }
    }
    
    inline void kill() noexcept
    {
        if(N)
        {
            if(v)
            {
                for(size_t i = 0; i < N; ++i)
                    memory::destroy(alloc, &v[i]);
                memory::deallocate(alloc, v, N);
                v = nullptr;
            }
        }
    }
    
    template <class P, class Q, class Alloc>
    inline void copy_construct_delete_(
        P first, 
        const P last, 
        Q first2,
        Alloc &alc)
    {
        using Cond = meta::_and<
                is_pointer<P>,
                is_pointer<Q>,
                is_pod<value_type>,
                is_same<value_type,
                    typename foundation::iterator::iterator_value<P>::type>>;
                
        if(Cond::value)
        {
            // Quick copy for POD types.
            foundation::iterator::copy(first, last, first2);
        }
        else
        {
            pointer i = first2;
            try {
                while(first < last)
                {
                    memory::construct(
                        alc,
                        i++,
                        *first++);
                }
            } catch(...) {
                delete_range_(first2, i, alc);
                throw;
            }
        }
    }
    template <class P, class A>
    inline void 
    delete_range_(P first, const P last, A &alc) noexcept
    {
        destroy_range_(first, last, alc);
        memory::deallocate(alc, first, N); 
    }
    template <class P, class A>
    inline void destroy_range_(P first, const P last, A &alc) noexcept
    {
        while(first < last)
            memory::destroy(alc, first++);
    }

    T *v;
    allocator_type alloc;
};

//==============================================================================
template <class T, size_t N>
inline bool operator == (
    const dynamic_array<T, N> &lhs, const dynamic_array<T, N> &rhs)
{
    return foundation::iterator::equal(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end());
}
//------------------------------------------------------------------------------
template <class T, size_t N>
inline bool operator != (
    const dynamic_array<T, N> &lhs, const dynamic_array<T, N> &rhs)
{
    return !(lhs == rhs);
}
//-------- ----------------------------------------------------------------------
template <class T, size_t N>
inline bool operator < (
    const dynamic_array<T, N> &lhs, const dynamic_array<T, N> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        less<T>());
}
//------------------------------------------------------------------------------
template <class T, size_t N>
inline bool operator <= (
    const dynamic_array<T, N> &lhs, const dynamic_array<T, N> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        less_equal<T>());
}
//------------------------------------------------------------------------------
template <class T, size_t N>
inline bool operator > (
    const dynamic_array<T, N> &lhs, const dynamic_array<T, N> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        greater<T>());
}
//------------------------------------------------------------------------------
template <class T, size_t N>
inline bool operator >= (
    const dynamic_array<T, N> &lhs, const dynamic_array<T, N> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        greater_equal<T>());
}

//==============================================================================
template <class T, size_t N>
struct hash<dynamic_array<T, N>>
{
    using result_type = size_t;
    inline size_t operator () (const dynamic_array<T, N> &x) const noexcept
    {
        return hash_detail::hash_blob(x.data(), x.size());
    }
};

/** @} */

}} // namespaces

#endif // NIC_FF6E03223CBF4A54_NIC
