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
#ifndef NIC_1E59F000C75B3FC6_NIC
#define NIC_1E59F000C75B3FC6_NIC

#include "vector.h"
#include "minmax.h"
#include "cstring.h"
#include "hash.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace string_detail {
//------------------------------------------------------------------------------
/** Simple wrapper such that the wrapped allocator allocates an additional
 * object which we can use for null-termination. 
 * Most of the time we don't need that extra space, but we need to allocate it
 * before hand so we can guarantee that, for example, c_str() is noexcept.
 * */
template <class T>
struct str_allocator_facade 
: public T // We derive from T - is this sane?
{
    using value_type = typename memory::allocator_value<T>::type;
    
    using T::T;
    
    inline value_type* allocate(
        const size_t n, 
        const value_type *h = nullptr)
    {
        value_type *res = T::allocate(n+1, h);
        res[n] = 0;
        return res;
    }
    inline value_type* reallocate(
        value_type *ptr, 
        const size_t old_size,
        const size_t new_size) 
    {
        return memory::reallocate(*this, ptr, old_size+1, new_size+1);
    }
    inline void deallocate(value_type *ptr, const size_t n) noexcept {
        T::deallocate(ptr, n+1);
    }
};
//------------------------------------------------------------------------------
} // string_detail
//------------------------------------------------------------------------------
/** 
 * */
template <class Char = char,
    class CharTraits = char_traits<Char>,
    class Allocator = memory::allocator<Char>
>
class basic_string
{    
    using allocator_type_ = string_detail::str_allocator_facade<Allocator>;
    using container_type_ = vector<Char, allocator_type_>;
    
public:
    using char_type = Char;
    using value_type = Char;
    using pointer = Char*;
    using const_pointer = const Char*;
    using reference = Char&;
    using const_reference = const Char&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    
    using allocator_type = Allocator;
    using traits_type = CharTraits;
    
    using iterator = typename container_type_::iterator;
    using const_iterator = typename container_type_::const_iterator;
    using reverse_iterator = typename container_type_::reverse_iterator;
    using const_reverse_iterator = 
        typename container_type_::const_reverse_iterator;
    
    basic_string() = default;
    basic_string(basic_string &) = default;
    basic_string(const basic_string &other) = default;
    basic_string(basic_string &&other) = default;
    
    inline explicit basic_string(const allocator_type &al)
    : v(al)
    {}
    inline explicit  basic_string(allocator_type &&al)
    : v(foundation::move(al))
    {}
    
    inline basic_string(const size_type n, const char_type c)
    : v(n, c)
    {}
    template <class Alloc>
    inline basic_string(const size_type n, const char_type c, Alloc &&al)
    : v(n, c, foundation::forward<Alloc>(al))
    {}
    
    inline basic_string(const char_type *s, const size_type n)
    : v(s, s + n)
    {}
    template <class Alloc>
    inline basic_string(const char_type *s, const size_type n, Alloc &&al)
    : v(s, s + n, foundation::forward<Alloc>(al))
    {}
    
    inline basic_string(const char_type *s)
    : basic_string(s, slen(s))
    {}
    inline basic_string(const char_type *s, const allocator_type &al)
    : basic_string(s, slen(s), al)
    {}
    inline basic_string(const char_type *s, allocator_type &&al)
    : basic_string(s, slen(s), foundation::move(al))
    {}
    
    template <class C_>
    inline basic_string(basic_cstring<C_, traits_type> s)
    : basic_string(s.data(), s.size())
    {}
    
    inline basic_string(std::initializer_list<char_type> ilist)
    : v(ilist)
    {}
    template <class Alloc>
    inline basic_string(std::initializer_list<char_type> ilist, Alloc &&al)
    : v(ilist, foundation::forward<Alloc>(al))
    {}
    
    
    inline basic_string &operator = (const basic_string &other) = default;
    basic_string &operator = (basic_string &&other) = default;
    
    template <class C_>
    basic_string &operator = (basic_cstring<C_, traits_type> s) {
        v.assign(s.data(), s.data() + s.size());
        return *this;
    }
    basic_string &operator = (std::initializer_list<char_type> ilist) {
        v = ilist;
        return *this;
    }
    basic_string &operator = (const char_type *s) {
        v.assign(s, s + slen(s));
        return *this;
    }
    
    inline basic_string &operator += (const basic_string &other) {
        return this->append(other);
    }
    inline basic_string &operator += (basic_string &&other) {
        if(empty())
        {
            *this = foundation::move(other);
            return *this;
        }
        else
            return this->append(other);
    }
    
    inline basic_string operator + (const basic_string &other) const {
        basic_string r(*this);
        r += other;
        return r;
    }
    inline basic_string operator + (basic_string &&other) const {
        basic_string r(*this);
        r += foundation::move(other);
        return r;
    }
    
    inline basic_string &operator += (const char_type *s) {
        return this->append(s);
    }
    inline basic_string operator + (const char_type *s) const {
        basic_string r(*this);
        r += s;
        return r;
    }
    
    inline basic_string &operator += (const char_type c) {
        this->push_back(c);
        return *this;
    }
    inline basic_string operator + (const char_type c) const {
        basic_string r(*this);
        r += c;
        return r;
    }

    inline void swap(basic_string &other)
    noexcept(noexcept(
        std::declval<container_type_>().swap(std::declval<container_type_>())
    ))
    {
        v.swap(other.v);
    }
    
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
    
    inline const_pointer c_str() const noexcept {
        *const_cast<pointer>(v.end()) = char_type();
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
        return v.max_size()-1; // cause of nulltermination.
    }
    
    inline void reserve(const size_type n) {
        v.reserve(n);
    }
    inline void resize(const size_type n, 
        const char_type c = char_type()) 
    {
        v.resize(n, c);
    }
    inline void shrink_to_fit() {
        v.shrink_to_fit();
    }
    
    inline void push_back(const char_type c) {
        v.push_back(c);
    }
    inline iterator insert(const_iterator pos, const char_type c) {
        iterator r = v.insert(pos, c);
        return r;
    }
    template <class I,
        typename enable_if<foundation::iterator::is_iterator<I>, int>::type = 0>
    inline iterator insert(const_iterator pos, I first, I last)
    {
        iterator r = v.insert(pos, first, last);
        return r;
    }
    inline iterator insert(
        const_iterator pos, const size_type n, const char_type e)
    {
        iterator r = v.insert(pos, n, e);
        return r;
    }
    
    template <class I>
    inline basic_string &append(I first, I last) {
        v.append(first, last);
        return *this;
    }
    inline basic_string &append(const basic_string &s) {
        v.append(s.v);
        return *this;
    }
    inline basic_string &append(basic_string &&s) {
        v.append(foundation::move(s.v));
        return *this;
    }
    inline basic_string &append(const char_type *s, const size_type n) {
        return this->append(s, s+n);
    }
    inline basic_string &append(const char_type *s) {
        return this->append(s, s + slen(s));
    }
    inline basic_string &append(std::initializer_list<char_type> ilist) {
        v.append(ilist.begin(), ilist.end());
        return *this;
    }
    
    inline void pop_back() noexcept {
        v.pop_back();
    }
    
    inline iterator erase(const_iterator i)
    {
        iterator r = v.erase(i);
        return r;
    }
    inline iterator erase(const_iterator first, const_iterator last)
    {
        iterator r = v.erase(first, last);
        return r;
    }
    
    inline void clear() noexcept {
        v.clear();
    }
    
    inline void reset() noexcept {
        v.reset();
    }
    
    inline tuple<pointer, pointer, pointer> transfer() noexcept {
        tuple<pointer, pointer, pointer> r = v.transfer();
        ++foundation::get<2>(r);
        return r;
    }
    
    inline allocator_type get_allocator() const {
        return allocator_type(v.get_allocator());
    }
    
    inline int compare(const basic_string &other) const noexcept
    {
        const size_type m = foundation::min(size(), other.size());
        const int r = traits_type::compare(data(), other.data(), m);
        if(r == 0) {
            if(size() == other.size())
                return 0;
            else if(size() < other.size())
                return -1;
            else
                return 1;
        }
        return r;
    }
    template <class C_>
    inline int compare(
        const basic_cstring<C_, traits_type> other) const noexcept
    {
        const size_type m = foundation::min(size(), other.size());
        const int r = traits_type::compare(data(), other.data(), m);
        if(r == 0) {
            if(size() == other.size())
                return 0;
            else if(size() < other.size())
                return -1;
            else
                return 1;
        }
        return r;
    }
    inline int compare(const char_type *s) const noexcept
    {
        const size_type other_size = traits_type::length(s);
        const size_type m = foundation::min(size(), other_size);
        const int r = traits_type::compare(data(), s, m);
        if(r == 0) {
            if(size() == other_size)
                return 0;
            else if(size() < other_size)
                return -1;
            else
                return 1;
        }
        return r;
    }
    
private:    
    inline static size_type slen(const char_type *s) {
        return traits_type::length(s);
    }
    
    container_type_ v;
};

//==============================================================================
template <class C, class CTraits, class A>
inline bool operator == (
    const basic_string<C, CTraits, A> &lhs, 
    const basic_string<C, CTraits, A> &rhs) noexcept
{
    if(lhs.size() != rhs.size())
        return false;
    return CTraits::compare(lhs.data(), rhs.data(), lhs.size()) == 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class A>
inline bool operator != (
    const basic_string<C, CTraits, A> &lhs, 
    const basic_string<C, CTraits, A> &rhs) noexcept
{
    return !(lhs == rhs);
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class A>
inline bool operator < (
    const basic_string<C, CTraits, A> &lhs, 
    const basic_string<C, CTraits, A> &rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class A>
inline bool operator <= (
    const basic_string<C, CTraits, A> &lhs, 
    const basic_string<C, CTraits, A> &rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class A>
inline bool operator > (
    const basic_string<C, CTraits, A> &lhs, 
    const basic_string<C, CTraits, A> &rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class A>
inline bool operator >= (
    const basic_string<C, CTraits, A> &lhs,
    const basic_string<C, CTraits, A> &rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

//==============================================================================
template <class C, class CTraits, class A, class C2>
inline bool operator == (
    const basic_string<C, CTraits, A> &lhs, 
    const C2 *rhs) noexcept
{
    if(lhs.size() != CTraits::length(rhs))
        return false;
    return CTraits::compare(lhs.data(), rhs, lhs.size()) == 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class A, class C2>
inline bool operator != (
    const basic_string<C, CTraits, A> &lhs, 
    const C2 *rhs) noexcept
{
    return !(lhs == rhs);
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class A, class C2>
inline bool operator < (
    const basic_string<C, CTraits, A> &lhs, 
    const C2 *rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class A, class C2>
inline bool operator <= (
    const basic_string<C, CTraits, A> &lhs, 
    const C2 *rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class A, class C2>
inline bool operator > (
    const basic_string<C, CTraits, A> &lhs, 
    const C2 *rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class A, class C2>
inline bool operator >= (
    const basic_string<C, CTraits, A> &lhs,
    const C2 *rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

//==============================================================================
template <class C, class CTraits, class A>
struct hash<basic_string<C, CTraits, A> >
    : public hash_detail::string_hash<C>
{};

/** @} */

}} // namespaces

#endif // NIC_1E59F000C75B3FC6_NIC
