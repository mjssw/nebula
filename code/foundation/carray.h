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
#ifndef NIC_B452279A3BA21D2B_NIC
#define NIC_B452279A3BA21D2B_NIC

#include "iterator.h"
#include "assert.h"
#include "enable_if.h"
#include "swap.h"
#include "exception/exception.h"
#include "hash.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** 
 * */
template <class T>
struct carray
{
    using value_type = typename remove_const<T>::type;
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
    
    inline carray() noexcept
    : beg_(nullptr), end_(nullptr)
    {}
    carray(carray &) = default;
    carray(const carray &) = default;
    carray(carray &&) = default;
    
    inline carray(pointer first_, pointer last_) noexcept
    : beg_(first_), end_(last_)
    {}
    inline carray(pointer first_, const size_type n) noexcept
    : beg_(first_), end_(first_ + n)
    {}
    
    carray &operator = (const carray &) = default;
    carray &operator = (carray &&) = default;
    
    inline carray &assign(pointer first_, pointer last_) noexcept {
        beg_ = first_;
        end_ = last_;
        return *this;
    }
    inline carray &assign(pointer first_, const size_type n) noexcept {
        beg_ = first_;
        end_ = first_ + n;
        return *this;
    }
    
    inline void swap(carray &other) 
    noexcept(noexcept(foundation::swap(other, other)))
    {
        foundation::iterator::for_each(begin(), end(),
            [] (value_type &x, value_type &y) {
                foundation::swap(x, y);
            },
            other.begin());
    }
    
    inline iterator begin() noexcept { return beg_; }
    inline iterator end() noexcept { return end_; }
    inline const_iterator begin() const noexcept { return beg_; }
    inline const_iterator end() const noexcept { return end_; }
    inline const_iterator cbegin() const noexcept { return beg_; }
    inline const_iterator cend() const noexcept { return end_; }
    
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
    
    inline pointer data() noexcept { return beg_; }
    inline const_pointer data() const noexcept { return beg_; }
    
    inline reference front() { return beg_[0]; }
    inline constexpr const_reference front() const { return beg_[0]; }
    inline reference back() { return *(end_-1); }
    inline constexpr const_reference back() const { return *(end_-1); }
    
    inline constexpr size_t size() const noexcept { return end_-beg_; }
    inline constexpr size_t max_size() const noexcept { return end_-beg_; }
    inline constexpr bool empty() const noexcept { return beg_==end_; }
    
    inline constexpr const_reference operator [] (const size_type i) const {
        return beg_[i];
    }
    inline reference operator [] (const size_type i) {
        return beg_[i];
    }
    inline const_reference at(const size_type i) const {
        if(i >= size())
            n_throw(out_of_range);
        return beg_[i];
    }
    inline reference at(const size_type i) {
        if(i >= size())
            n_throw(out_of_range);
        return beg_[i];
    }
    
    inline void fill(const value_type &x) {
        iterator::fill(begin(), end(), x);
    }
    
private:
    pointer beg_, end_;
};

//==============================================================================
template <class T>
inline bool operator == (const carray<T> lhs, const carray<T> rhs)
{
    return foundation::iterator::equal(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end());
}
//------------------------------------------------------------------------------
template <class T>
inline bool operator != (const carray<T> lhs, const carray<T> rhs)
{
    return !(lhs == rhs);
}
//------------------------------------------------------------------------------
template <class T>
inline bool operator < (const carray<T> lhs, const carray<T> rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        less<T>());
}
//------------------------------------------------------------------------------
template <class T>
inline bool operator <= (const carray<T> lhs, const carray<T> rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        less_equal<T>());
}
//------------------------------------------------------------------------------
template <class T>
inline bool operator > (const carray<T> lhs, const carray<T> rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        greater<T>());
}
//------------------------------------------------------------------------------
template <class T>
inline bool operator >= (const carray<T> lhs, const carray<T> rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        greater_equal<T>());
}

//==============================================================================
template <class T>
struct hash<carray<T>>
{
    using result_type = size_t;
    inline size_t operator () (const carray<T> &x) const noexcept
    {
        return hash_detail::hash_blob(x.data(), x.size());
    }
};

/** @} */

}} // namespaces

#endif // NIC_B452279A3BA21D2B_NIC
