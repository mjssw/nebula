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
#ifndef NIC_83C05D3A37FA4896_NIC
#define NIC_83C05D3A37FA4896_NIC

#include "common.h"
#include "../tuple.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
namespace sub_range_detail {
//------------------------------------------------------------------------------
template <class Range, 
bool is_bidir = 
    has_tag<
        typename range_traversal<Range>::type,
        bidirectional_traversal_tag
    >::type::value>
struct reverse_iterator_types {
    using reverse_iterator = 
        typename range_reverse_iterator<Range>::type;
    using const_reverse_iterator =
        typename range_reverse_iterator<const Range>::type;
};

template <class Range>
struct reverse_iterator_types<Range, false> {};
//------------------------------------------------------------------------------
} // sub_range_detail
//------------------------------------------------------------------------------
/**
 * */
template <class Range>
class sub_range : 
public sub_range_detail::reverse_iterator_types<
    typename remove_const<Range>::type>
{
    using range_ = Range;
    using range_no_const_ = typename remove_const<range_>::type;
    
    using is_bidir = 
    typename has_tag<
        typename range_traversal<range_no_const_>::type,
        bidirectional_traversal_tag
    >::type;
    
public:    
    using value_type = typename range_value<range_no_const_>::type;
    using reference = typename range_reference<range_>::type;
    using const_reference = typename range_reference<const range_>::type;
    using pointer = typename range_pointer<range_>::type;
    using const_pointer = typename range_pointer<const range_>::type;
    
    using size_type = typename range_size<range_no_const_>::type;
    using difference_type = typename range_difference<range_no_const_>::type;
    
    using range_category = typename range_category<range_no_const_>::type;
    
    using iterator = typename range_iterator<range_>::type;
    using const_iterator = typename range_iterator<const range_>::type;
    
    struct adaptor_id_ {};
    
    sub_range(sub_range &) = default;
    sub_range(const sub_range &) = default;
    sub_range(sub_range &&) = default;
    
    inline sub_range(iterator first, iterator last) noexcept
    :   beg_(first), end_(last)
    {}
    
    sub_range &operator = (sub_range &) = default;
    sub_range &operator = (const sub_range &) = default;
    sub_range &operator = (sub_range &&) = default;
    
    inline iterator begin() noexcept {
        return beg_;
    }
    inline const_iterator begin() const noexcept {
        return beg_;
    }
    inline const_iterator cbegin() const noexcept {
        return beg_;
    }
    inline iterator end() noexcept {
        return end_;
    }
    inline const_iterator end() const noexcept {
        return end_;
    }
    inline const_iterator cend() const noexcept {
        return end_;
    }
    
    template <class Cond = is_bidir,
        typename enable_if<Cond>::type* = nullptr>
    inline typename range_reverse_iterator<range_no_const_>::type 
    rbegin() noexcept {
        return typename range_reverse_iterator<range_no_const_>::type(end());
    }
    template <class Cond = is_bidir,
        typename enable_if<Cond>::type* = nullptr>
    inline typename range_reverse_iterator<const range_no_const_>::type 
    rbegin() const noexcept {
        return typename range_reverse_iterator<
            const range_no_const_>::type(end());
    }
    template <class Cond = is_bidir,
        typename enable_if<Cond>::type* = nullptr>
    inline typename range_reverse_iterator<const range_no_const_>::type 
    crbegin() const noexcept {
        return typename range_reverse_iterator<
            const range_no_const_>::type(cend());
    }
    template <class Cond = is_bidir,
        typename enable_if<Cond>::type* = nullptr>
    inline typename range_reverse_iterator<range_no_const_>::type 
    rend() noexcept {
        return typename range_reverse_iterator<range_no_const_>::type(begin());
    }
    template <class Cond = is_bidir,
        typename enable_if<Cond>::type* = nullptr>
    inline typename range_reverse_iterator<const range_no_const_>::type 
    rend() const noexcept {
        return typename range_reverse_iterator<
            const range_no_const_>::type(begin());
    }
    template <class Cond = is_bidir,
        typename enable_if<Cond>::type* = nullptr>
    inline typename range_reverse_iterator<const range_no_const_>::type 
    crend() const noexcept {
        return typename range_reverse_iterator<
            const range_no_const_>::type(cbegin());
    }
    
    inline size_type size() const noexcept {
        return foundation::iterator::distance(beg_, end_);
    }
    inline bool empty() const noexcept {
        return range::empty(*this);
    }
    
private:
    iterator beg_, end_;
};

/** @} */

}}} // namespaces

#endif // NIC_83C05D3A37FA4896_NIC