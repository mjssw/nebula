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
#ifndef NIC_CBB843C3E4401171_NIC
#define NIC_CBB843C3E4401171_NIC

#include "range.h"
#include "vector.h"
#include "ops.h"
#include "hash.h"

#define N_HASH_SET_DEFAULT_SIZE_ 100
#define N_HASH_SET_GROW_RATE_ 10
#define N_HASH_SET_MAX_LOAD_FACTOR_ 1.0f

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** A simple hash set container.
 * 
 *  @attention The hash and comparison functions must not throw when invoked
 *  and they must be no-throw move constructible/assignable.
 * 
 *  @param T The value type which is also used as the key type.
 *  @param Hash A Hash function which must return a type convertible to size_t.
 *  @param Equal To compare elements.
 *  @param Allocator The allocator used by the container.
 * */
template <
    class T,
    class Hash = hash<T>,
    class Equal = equal_to<>,
    class Allocator = memory::allocator<T>>
class hash_set
{
    using bucket_allocator_type
        = typename memory::rebind<Allocator, T>::type;
    using bucket_type = vector<T, bucket_allocator_type>;
    
    using container_allocator_type
        = typename memory::rebind<Allocator, bucket_type>::type;
    using container_type = vector<bucket_type, container_allocator_type>;
    
public:
    using hash_type = Hash;
    using equal_type = Equal;
    
    using key_type = T;
    using mapped_type = T;
    
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    
    using allocator_type = bucket_allocator_type;
    
    n_static_assert(is_nothrow_movable<container_type>::value, "");
    n_static_assert(is_nothrow_movable<hash_type>::value, "");
    n_static_assert(is_nothrow_movable<equal_type>::value, "");
    
    inline hash_set()
    : size_(0), max_load_factor_(N_HASH_SET_MAX_LOAD_FACTOR_)
    {}
    
    hash_set(hash_set &) = default;
    hash_set(const hash_set &) = default;
    hash_set(hash_set &&) = default;
    
    template <class H, class E, class A>
    inline hash_set(const float lf, H &&h, E &&e, A &&a)
    : size_(0), 
    max_load_factor_(lf),
    v(container_type(foundation::forward<A>(a))),
    hash_(foundation::forward<H>(h)),
    eq(foundation::forward<E>(e))
    {         
        if(lf <= 0.0f)
            n_throw(logic_error);
    }
    
    hash_set &operator = (const hash_set &) = default;
    hash_set &operator = (hash_set &&) = default;
    
    inline void swap(hash_set &x) noexcept
    {
        foundation::swap(v, x.v);
        foundation::swap(hash_, x.hash_);
        foundation::swap(eq, x.eq);
        foundation::swap(size_, x.size_);
        foundation::swap(max_load_factor_, x.max_load_factor_);
    }
    
    inline bool empty() const noexcept {
        return size() == 0;
    }
    inline size_type size() const noexcept {
        return size_;
    }
    inline size_type bucket_count() const noexcept {
        return v.size();
    }
    inline size_type bucket_size(const size_type i) const noexcept {
        return v[i].size();
    }
    inline float load_factor() const noexcept {
        return static_cast<float>(size())
            / static_cast<float>(bucket_count()); 
    }
    inline float max_load_factor() const noexcept {
        return max_load_factor_;
    }
    inline void max_load_factor(const float x) {
        if(x <= 0.0f)
            n_throw(exception);
        max_load_factor = x;
    }
    
    inline void reserve(const size_type n)
    {
        float nb = float(n) / max_load_factor();
        rehash(size_t(nb)+1);
    }
    
    inline void rehash(const size_type n)
    {
        if(n > bucket_count())
        {
            if(empty())
            {
                init(n);
                return;
            }
            
            container_type new_v(v.get_allocator());
            new_v.resize(n, bucket_type(v[0].get_allocator()));

            if(is_nothrow_movable<value_type>::value)
            {                
                for(bucket_type &b : v)
                {
                    for(reference e : b)
                    {
                        const size_t idx = hash(e, n);
                        new_v[idx].emplace_back(foundation::move(e));
                    }
                }
            }
            else
            {
                for(bucket_type &b : v)
                {
                    for(reference e : b)
                    {
                        const size_t idx = hash(e, n);
                        new_v[idx].emplace_back(e);
                    }
                }
            }
            
            // doesn't throw.
            v = foundation::move(new_v);
        }
    }
    
    template <class X>
    inline tuple<pointer, bool> emplace(X &&x)
    {
        if(v.empty())
            this->init();
        else 
            try_rehash();
        
        value_type x_ = foundation::forward<X>(x);
        auto &b = v[hash(x_)];
        auto i = foundation::iterator::find( 
            b.begin(), b.end(), x_, eq);
        if(i != b.end())
            return foundation::make_tuple(i, false);
        b.emplace_back(foundation::move(x_));
        ++size_;
        return foundation::make_tuple(&b.back(), true);
    }
    
    template <class X>
    inline pointer find(const X &x)
    {
        if(empty())
            return nullptr;
        auto &v_ = v[hash(x)];
        // We do a simple linear search.
        auto i = foundation::iterator::find(
            v_.begin(), v_.end(), x, eq);
        if(i != v_.end())
           return i;
        return nullptr;
    }
    template <class X>
    inline const_pointer find(const X &x) const
    {
        if(empty())
            return nullptr;
        auto &v_ = v[hash(x)];
        // We do a simple linear search.
        auto i = foundation::iterator::find(
            v_.begin(), v_.end(), x, eq);
        if(i != v_.end())
           return i;
        return nullptr;
    }
    template <class X>
    inline bool search(const X &x)
    {
        return this->find(x);
    }
    
    template <class X, class F>
    inline void for_each(const X &x, F &&f)
    {
        const size_t idx = hash(x);
        bucket_type &b = v[idx];     
        typename range::range_iterator<bucket_type>::type i
            = foundation::iterator::find(b.begin(), b.end(), x, eq);
        if(i != b.end())
        {
            do
            {
                f(*i++);
            }
            while(i != b.end() && eq(x, *i));
        }
    }
    
    inline size_type erase(const value_type &x)
    {        
        const size_t idx = hash(x);
        bucket_type &b = v[idx];
        size_type n = this->size();
        typename range::range_iterator<bucket_type>::type i = b.begin();
        while((i = foundation::iterator::find(
            i, b.end(), x, eq)) != b.end())
        {
            i = b.erase(i);
            --size_;
        }
        return n - this->size();
    }
    
    inline void clear() noexcept {
        v.clear();
        size_ = 0;
    }
    inline void reset() noexcept {
        v.reset();
        size_ = 0;
    }
    
    inline hash_type &hash() noexcept {
        return hash_;
    }
    inline const hash_type &hash() const noexcept {
        return hash_;
    }
    
    inline equal_type &equal() noexcept {
        return eq;
    }
    inline const equal_type &equal() const noexcept {
        return eq;
    }
    
    inline allocator_type get_allocator() const {
        return allocator_type(v.get_allocator());
    }
    
private:
    inline size_t hash(const value_type &x) const
    {
        return size_t(hash_(x)) % this->bucket_count();
    }
    inline size_t hash(const value_type &x, const size_t n) const
    {
        return size_t(hash_(x)) % n;
    }

    inline void init(const size_type n = N_HASH_SET_DEFAULT_SIZE_)
    {
        v.resize(
            n,
            bucket_type(bucket_allocator_type(v.get_allocator())));
    }
    
    inline void try_rehash()
    {
        if(load_factor() > max_load_factor()) {
            rehash(bucket_count() * N_HASH_SET_GROW_RATE_);
        }
    }
    
    size_t size_;
    float max_load_factor_;
    container_type v;
    hash_type hash_;
    equal_type eq;
    
    // Stuff below is for hash_map.
    
    template <class, class, class, class, class>
    friend class hash_map;
    
    template <class Key>
    inline size_t hash_key_(const Key &x) const
    {
        return size_t(hash_(x)) % this->bucket_count();
    }
    template <class Key>
    inline pointer find_by_key_(const Key &x)
    {
        if(empty())
            return nullptr;
        auto &v_ = v[hash_key_(x)];
        // We do a simple linear search.
        auto i = foundation::iterator::find(
            v_.begin(), v_.end(), x, eq);
        if(i != v_.end())
           return i;
        return nullptr;
    }
    template <class Key>
    inline const_pointer find_by_key_(const Key &x) const
    {
        if(empty())
            return nullptr;
        auto &v_ = v[hash_key_(x)];
        // We do a simple linear search.
        auto i = foundation::iterator::find(
            v_.begin(), v_.end(), x, eq);
        if(i != v_.end())
           return i;
        return nullptr;
    }    
    template <class Key>
    inline size_type erase_by_key_(const Key &x)
    {
        const size_t idx = hash_key_(x);
        bucket_type &b = v[idx];
        size_type n = this->size();
        typename range::range_iterator<bucket_type>::type i = b.begin();
        while((i = foundation::iterator::find(
            i, b.end(), x, eq)) != b.end())
        {
            i = b.erase(i);
            --size_;
        }
        return n - this->size();
    }
    template <class Key, class F>
    inline void for_each_by_key_(const Key &x, F &&f)
    {
        const size_t idx = hash_key_(x);
        bucket_type &b = v[idx];     
        typename range::range_iterator<bucket_type>::type i
            = foundation::iterator::find(b.begin(), b.end(), x, eq);
        if(i != b.end())
        {
            do
            {
                f(*i++);
            }
            while(i != b.end() && eq(x, *i));
        }
    }
};

#undef N_HASH_SET_DEFAULT_SIZE_
#undef N_HASH_SET_GROW_RATE_
#undef N_HASH_SET_MAX_LOAD_FACTOR_

/** @} */

}} // namespaces

#endif // NIC_CBB843C3E4401171_NIC
