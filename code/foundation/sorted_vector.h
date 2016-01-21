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
#ifndef NIC_D75A29BDFF741EAA_NIC
#define NIC_D75A29BDFF741EAA_NIC

#include "vector.h"
#include "ops.h"
#include "range/iterator_range.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** Sometimes a simple sorted_ vector is quite handy. 
 * */
template <
    class T,
    class P = less<T>,
    class Allocator = memory::allocator<T>>
class sorted_vector
{
    using container_type = vector<T, Allocator>;
    
public:
    using allocator_type = Allocator;
    using predicate_type = P;
    
    using value_type = typename range::range_value<container_type>::type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    
    using iterator = typename range::range_iterator<container_type>::type;
    using const_iterator 
        = typename range::range_iterator<const container_type>::type;
    using reverse_iterator
        = typename range::range_reverse_iterator<container_type>::type;
    using const_reverse_iterator
        = typename range::range_reverse_iterator<const container_type>::type;
        
    inline sorted_vector()
    : sorted_(true)
    {}
    sorted_vector(sorted_vector &x) = default;
    sorted_vector(const sorted_vector &x) = default;
    /** @attention If this isn't noexcept then no exception guarantee can 
     * be given. Destroy participating containers when an exception is thrown.
     * */
    inline sorted_vector(sorted_vector &&x) = default;
    
    template <class Prd, class Alloc>
    inline sorted_vector(Prd &&prd, Alloc &&alc = Allocator())
    : sorted_(true),
    v(foundation::forward<Alloc>(alc)),
    p(foundation::forward<Prd>(prd))
    {}
    
    sorted_vector &operator = (const sorted_vector &x) = default;
    /** @attention If this isn't noexcept then no exception guarantee can 
     * be given. Destroy participating containers when an exception is thrown.
     * */
    sorted_vector &operator = (sorted_vector &&x) = default;
    
    inline const_reference operator [] (const size_type i) const {
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
    
    inline pointer data() noexcept {
        return v.data(); 
    }
    inline const_pointer data() const noexcept {
        return v.data();
    }
    
    inline iterator begin() noexcept {
        return iterator(v.begin());
    }
    inline const_iterator begin() const noexcept {
        return const_iterator(v.begin());
    }
    inline const_iterator cbegin() const noexcept {
        return const_iterator(v.cbegin());
    }
    inline iterator end() noexcept {
        return iterator(v.end());
    }
    inline const_iterator end() const noexcept {
        return const_iterator(v.end());
    }
    inline const_iterator cend() const noexcept {
        return const_iterator(v.cend());
    }
    
    inline reverse_iterator rbegin() noexcept {
        return reverse_iterator(v.rbegin());
    }
    inline const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(v.rbegin());
    }
    inline const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(v.crbegin());
    }
    inline reverse_iterator rend() noexcept {
        return reverse_iterator(v.rend());
    }
    inline const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(v.rend());
    }
    inline const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(v.crend());
    }
    
    inline reference front() {
        return v.front();
    }
    inline const_reference front() const {
        return v.front();
    }
    inline reference back() {
        return v.back();
    }
    inline const_reference back() const {
        return v.back();
    }
    
    inline size_type size() const noexcept {
        return v.size();
    }
    inline size_type capacity() const noexcept {
        return v.capacity();
    }
    inline bool empty() const noexcept {
        return v.empty();
    }
    inline size_type max_size() const noexcept {
        return v.max_size();
    }
    
    template <class ... X>
    inline void resize(const size_type &n, X && ... x) {
        v.resize(n, foundation::forward<X>(x)...);
        sorted_ = false;
    }
    inline void reserve(const size_type n) {
        v.reserve(n);
    }
    inline void shrink_to_fit() {
        v.shrink_to_fit();
    }
    
    inline void sort() {
        if(!sorted_) {
            foundation::iterator::sort(
                this->begin(), this->end(), p);
            sorted_ = true;
        }
    }
    inline bool sorted() const noexcept {
        return sorted_;
    }
    
    template <class X>
    inline iterator find(const X &x) {
        this->assert_sorted();
        return foundation::iterator::lower_bound(
            this->begin(), this->end(), x, p);
    }
    template <class X>
    inline range::iterator_range<iterator> find_all(const X &x) {
        iterator f = find(x);
        iterator i = f+1;
        while(i != end() && !p(x, *i))
            ++i;
        return range::iterator_range<iterator>(f, i);
    }
    template <class X>
    inline const_iterator find(const X &x) const {
        this->assert_sorted();
        return foundation::iterator::lower_bound(
            this->begin(), this->end(), x, p);
    }
    template <class X>
    inline range::iterator_range<const_iterator>
    find_all(const X &x) {
        const_iterator f = find(x);
        const_iterator i = f+1;
        while(i != end() && !p(x, *i))
            ++i;
        return range::iterator_range<const_iterator>(f, i);
    }
    template <class X>
    inline iterator lower_bound(const X &x) {
        this->assert_sorted();
        return foundation::iterator::lower_bound(
            this->begin(), this->end(), x, p);
    }
    template <class X>
    inline const_iterator lower_bound(const X &x) const {
        this->assert_sorted();
        return foundation::iterator::lower_bound(
            this->begin(), this->end(), x, p);
    }
    template <class X>
    inline iterator upper_bound(const X &x) {
        this->assert_sorted();
        return foundation::iterator::lower_bound(
            this->begin(), this->end(), x, p);
    }
    template <class X>
    inline const_iterator upper_bound(const X &x) const {
        this->assert_sorted();
        return foundation::iterator::lower_bound(
            this->begin(), this->end(), x, p);
    }
    template <class X>
    inline range::iterator_range<iterator> equal_range(const X &x) {
        this->assert_sorted();
        return range::iterator_range<iterator>(
            this->lower_bound(x),
            this->upper_bound(x));
    }
    template <class X>
    inline range::iterator_range<const_iterator> equal_range(const X &x) const
    {
        this->assert_sorted();
        return range::iterator_range<const_iterator>(
            this->lower_bound(x),
            this->upper_bound(x));
    }
    
    template <class X>
    inline bool search(const X &x) const {
        this->assert_sorted();
        return foundation::iterator::binary_search(
            this->begin(), this->end(), x, p);
    }
    
    template <class X>
    inline void emplace(X &&x)
    {
        if(this->empty()) {
            v.push_back(foundation::forward<X>(x));
            return;
        }
        this->assert_sorted();
        iterator i = foundation::iterator::lower_bound(
            this->begin(), this->end(), x, p);
        if(i == this->end())
            v.push_back(foundation::forward<X>(x));
        else
            v.emplace(i, foundation::forward<X>(x));
    }
    
    template <class X>
    inline void push_back(X &&x)
    {
        v.emplace_back(foundation::forward<X>(x));
        sorted_ = false;
    }
    template <class X>
    inline void emplace_back(X &&x)
    {
        v.emplace_back(foundation::forward<X>(x));
        sorted_ = false;
    }
    
    template <class X>
    inline iterator emplace(const_iterator pos, X &&x) {
        iterator i = this->emplace(pos, foundation::forward<X>(x));
        sorted_ = false;
        return i;
    }
    template <class X>
    inline iterator insert(const_iterator pos, X &&x) {
        iterator i = this->emplace(pos, foundation::forward<X>(x));
        sorted_ = false;
        return i;
    }
    
    template <class I,
        typename enable_if<foundation::iterator::is_iterator<I>, int>::type = 0>
    inline iterator insert(const_iterator pos, I first, I last)
    {
        iterator i = v.insert(pos, first, last);
        sorted_ = false;
        return i;
    }
    template <class X>
    inline iterator insert(const_iterator pos, const size_type n, const X &e)
    {
        iterator i = v.insert(pos, n, e);
        sorted_ = false;
        return i;
    }
    
    template <class I,
        typename enable_if<foundation::iterator::is_iterator<I>, int>::type = 0>
    inline sorted_vector &append(I first, I last)
    {
        v.append(first, last);
        sorted_ = false;
        return *this;
    }
    inline sorted_vector &append(const_pointer x, const size_type n) {
        sorted_ = false;
        return this->append(x, x+n);
    }
    inline sorted_vector &append(const sorted_vector &other) {
        sorted_ = false;
        return this->append(other.begin(), other.end());
    }
    inline sorted_vector &append(sorted_vector &&other) {
        if(empty())
            *this = foundation::move(other);
        else {
            sorted_ = false;
            this->append(other.v);
        }
        return *this;
    }
    template <class T_>
    inline sorted_vector &append(std::initializer_list<T_> ilist) {
        sorted_ = false;
        return this->append(ilist.begin(), ilist.end());
    }
    
    inline void pop_back() noexcept {
        v.pop_back();
        if(empty())
            sorted_ = true;
    }
    inline void pop_front() noexcept {
        v.pop_front();
        if(empty())
            sorted_ = true;
    }
    
    inline iterator erase(const_iterator i)
    {
        iterator r = v.erase(i);
        if(empty())
            sorted_ = true;
        return r;
    }
    inline iterator erase(const_iterator first, const_iterator last)
    {
        iterator r = v.erase(first, last);
        if(empty())
            sorted_ = true;
        return r;
    }
    
    inline void clear() noexcept {
        v.clear();
        sorted_ = true;
    }
    
    inline void reset() noexcept {
        v.reset();
        sorted_ = true;
    }
    
    inline allocator_type get_allocator() const {
        return allocator_type(v.get_allocator());
    }
    
private:
    inline void assert_sorted() const {
        if(!sorted_)
            n_throw(logic_error);
    }
    
    bool sorted_;
    container_type v;
    predicate_type p;
};

//------------------------------------------------------------------------------
template <class T, class P, class A>
struct hash<sorted_vector<T, P, A>>
{
    using result_type = size_t;
    inline size_t operator () (const sorted_vector<T, P, A> &x) const noexcept
    {
        return hash_detail::hash_blob(x.data(), x.size());
    }
};

/** @} */

}} // namespaces

#endif // NIC_D75A29BDFF741EAA_NIC