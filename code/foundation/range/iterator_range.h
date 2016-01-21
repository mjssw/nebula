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
#ifndef NIC_EBBEA5EA97583B68_NIC
#define NIC_EBBEA5EA97583B68_NIC

#include "common.h"
#include "../tuple.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
namespace iterator_range_detail {
//------------------------------------------------------------------------------
template <class Iter, 
bool is_bidir = 
    has_tag<
        typename ins_::iterator_traversal<Iter>::type,
        ins_::bidirectional_traversal_tag
    >::type::value>
struct reverse_iterator_types {
    using reverse_iterator = 
        typename ins_::reverse_iterator<Iter>;
    using const_reverse_iterator = reverse_iterator;
};

template <class Iter>
struct reverse_iterator_types<Iter, false> {};
//------------------------------------------------------------------------------
} // iterator_range_detail
//------------------------------------------------------------------------------
/**
 * */
template <class Iter>
class iterator_range : 
public iterator_range_detail::reverse_iterator_types<Iter>
{    
    using is_bidir = 
        typename has_tag<
            typename ins_::iterator_traversal<Iter>::type,
            ins_::bidirectional_traversal_tag
        >::type;
    
public:
    using iterator = Iter;
    using const_iterator = Iter;
    
    using value_type = typename ins_::iterator_value<iterator>::type;
    using reference = typename ins_::iterator_reference<iterator>::type;
    using const_reference = reference;
    using pointer = typename ins_::iterator_pointer<iterator>;
    using const_pointer = pointer;
    
    using difference_type = typename ins_::iterator_difference<iterator>::type;
    using size_type = typename make_unsigned<difference_type>::type;
    
    struct adaptor_id_ {};
    
    iterator_range(iterator_range &) = default;
    iterator_range(const iterator_range &) = default;
    iterator_range(iterator_range &&) = default;
    
    inline iterator_range(iterator first, iterator last) noexcept
    :   beg_(first), end_(last)
    {}
    
    template <class J>
    inline iterator_range(const iterator_range<J> &other) noexcept
    : beg_(other.beg_), end_(other.end_)
    {}
    
    iterator_range &operator = (iterator_range &) = default;
    iterator_range &operator = (const iterator_range &) = default;
    iterator_range &operator = (iterator_range &&) = default;
    
    template <class J>
    inline iterator_range &operator = (const iterator_range<J> &other) noexcept
    {
        *this = iterator_range(other);
        return *this;
    }

    inline iterator begin() const noexcept {
        return beg_;
    }
    inline iterator cbegin() const noexcept {
        return beg_;
    }
    inline iterator end() const noexcept {
        return end_;
    }
    inline iterator cend() const noexcept {
        return end_;
    }
    
    template <class Cond = is_bidir,
        typename enable_if<Cond>::type* = nullptr>
    inline ins_::reverse_iterator<iterator> 
    rbegin() const noexcept {
        return ins_::reverse_iterator<iterator>(end());
    }
    template <class Cond = is_bidir,
        typename enable_if<Cond>::type* = nullptr>
    inline ins_::reverse_iterator<iterator>  
    crbegin() const noexcept {
        return ins_::reverse_iterator<iterator>(end());
    }
    template <class Cond = is_bidir,
        typename enable_if<Cond>::type* = nullptr>
    inline ins_::reverse_iterator<iterator>  
    rend() const noexcept {
        return ins_::reverse_iterator<iterator>(begin());
    }
    template <class Cond = is_bidir,
        typename enable_if<Cond>::type* = nullptr>
    inline ins_::reverse_iterator<iterator>  
    crend() const noexcept {
        return ins_::reverse_iterator<iterator>(begin());
    }
    
    inline size_type size() const noexcept {
        return foundation::iterator::distance(beg_, end_);
    }
    inline bool empty() const noexcept {
        return range::empty(*this);
    }
    
private:
    iterator beg_, end_;
    
    template <class X>
    friend class iterator_range;
};
//------------------------------------------------------------------------------
template <class Iter>
inline iterator_range<Iter> make_iterator_range(Iter f, Iter l)
{
    return iterator_range<Iter>(f, l);
}

/** @} */

}}} // namespaces

#endif // NIC_EBBEA5EA97583B68_NIC