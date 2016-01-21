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
#ifndef NIC_84658F61173075B1_NIC
#define NIC_84658F61173075B1_NIC

#include "hash_set.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <
    class Key,
    class T, 
    class Hash = hash<Key>, 
    class Equal = equal_to<>,
    class Allocator = memory::allocator<tuple<Key, T>>>
class hash_map
{
public:
    using hash_type = Hash;
    using equal_type = Equal;
    
    using key_type = Key;
    using mapped_type = T;
    
    using value_type = tuple<Key, T>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    
    using allocator_type 
        = typename memory::rebind<Allocator, value_type>::type;
    
private:
    struct hash_
    {
        using result_type = typename hash_result<hash_type>::type;
        inline result_type operator () (const value_type &x) const {
            return h(foundation::get<0>(x));
        }
        template <class X>
        inline result_type operator () (const X &k) const {
            return h(k);
        }
        hash_type h;
    };
    struct equal_
    {
        inline bool operator () (
            const value_type &x, const value_type &y) const {
            return eq(foundation::get<0>(x), foundation::get<0>(y));
        }
        template <class Y>
        inline bool operator () (
            const value_type &x, const Y &y) const {
            return eq(foundation::get<0>(x), y);
        }
        
        equal_type eq;
    };
    
    // Implemented using hash_set
    // see the bottom of the hash_set class for details
    using container_type = hash_set<
        value_type, hash_, equal_, allocator_type>;
        
public:
    hash_map() = default;    
    hash_map(hash_map &) = default;
    hash_map(const hash_map &) = default;
    hash_map(hash_map &&) = default;
    
    template <class H, class E, class A>
    inline hash_map(const float lf, H &&h, E &&e, A &&a)
    : v(lf,
        foundation::forward<H>(h),
        foundation::forward<E>(e),
        foundation::forward<A>(a))
    {}
    
    hash_map &operator = (const hash_map &) = default;
    hash_map &operator = (hash_map &&) = default;
    
    inline void swap(hash_map &other)
    noexcept(noexcept(foundation::swap(declval<container_type>(), other.v)))
    {
        foundation::swap(v, other.v);
    }
    
    inline bool empty() const noexcept {
        return v.empty();
    }
    inline size_type size() const noexcept {
        return v.size();
    }
    inline size_type bucket_count() const noexcept {
        return v.bucket_count();
    }
    inline size_type bucket_size(const size_type i) const noexcept {
        return v.bucket_size(i);
    }
    inline float load_factor() const noexcept {
        return v.load_factor();
    }
    inline float max_load_factor() const noexcept {
        return v.max_load_factor();
    }
    inline void max_load_factor(const float x) {
        v.max_load_factor(x);
    }
    
    inline void reserve(const size_type n)
    {
        v.reserve(n);
    }
    inline void rehash(const size_type n)
    {
        v.rehash(n);
    }
    
    template <class K, class ... X>
    inline tuple<pointer, bool> emplace(K &&k, X && ... x)
    {
        value_type n(foundation::forward<K>(k), foundation::forward<X>(x)...);
        return v.emplace(foundation::move(n));
    }
    
    template <class X>
    inline pointer find(const X &k) {
        return v.find_by_key_(k);
    }
    template <class X>
    inline const_pointer find(const X &k) const {
        return v.find_by_key_(k);
    }
    template <class X>
    inline bool search(const X &k) const {
        return this->find(k) != nullptr;
    }
    template <class X, class F>
    inline void for_each(const X &k, F &&f)
    {
        v.for_each_by_key_(k, f);
    }
    
    inline size_type erase(const key_type &k) {
        return v.erase_by_key_(k);
    }
    
    inline void clear() noexcept {
        v.clear();
    }
    inline void reset() noexcept {
        v.reset();
    }
    
    inline hash_type &hash() noexcept {
        return v.hash().h;
    }
    inline const hash_type &hash() const noexcept {
        return v.hash().h;
    }
    
    inline equal_type &equal() noexcept {
        return v.equal().eq;
    }
    inline const equal_type &equal() const noexcept {
        return v.equal().eq;
    }
    
    inline allocator_type get_allocator() const noexcept {
        return v.get_allocator();
    }
    
private:
    container_type v;
};

/** @} */

}} // namespaces

#endif // NIC_84658F61173075B1_NIC
