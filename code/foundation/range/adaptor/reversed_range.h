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
#ifndef NIC_E62BC899C3AA4957_NIC
#define NIC_E62BC899C3AA4957_NIC

#include "../../adaptor.h"
#include "../common.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
/** */
template <class R>
class reversed_range : public adaptor_base<R>
{
    using range_ = typename remove_const<R>::type;
    
    n_static_assert(n_arg(
        has_tag<typename range_traversal<range_>::type,
        bidirectional_traversal_tag>::type::value),
        "Random Access - Range required.");
    
public:
    using value_type = typename range_value<range_>::type;
    using reference = typename range_reference<R>::type;
    using const_reference = typename range_reference<const range_>::type;
    using pointer = typename range_pointer<R>::type;
    using const_pointer = typename range_pointer<const range_>::type;
    
    using size_type = typename range_size<range_>::type;
    using difference_type = typename range_difference<range_>::type;
    
    using iterator = typename range_reverse_iterator<R>::type;
    using const_iterator = typename range_reverse_iterator<const range_>::type;
    using reverse_iterator = typename range_iterator<R>::type;
    using const_reverse_iterator = typename range_iterator<const range_>::type;
    
    reversed_range(reversed_range &) = default;
    reversed_range(const reversed_range &) = default;
    reversed_range(reversed_range &&) = default;
    
    template <class R_>
    inline reversed_range(R_ &&r)
    : adaptor_base<R>(foundation::forward<R_>(r))
    {}
    
    reversed_range &operator = (const reversed_range &rhs) = default;
    reversed_range &operator = (reversed_range &&rhs) = default;
    
    inline iterator begin() noexcept {
        return range::rbegin(this->adaptee());
    }
    inline const_iterator begin() const noexcept {
        return range::rbegin(this->adaptee());
    }
    inline const_iterator cbegin() const noexcept {
        return range::rbegin(this->adaptee());
    }
    inline iterator end() noexcept {
        return range::rend(this->adaptee());
    }
    inline const_iterator end() const noexcept {
        return range::rend(this->adaptee());
    }
    inline const_iterator cend() const noexcept {
        return range::rend(this->adaptee());
    }
    
    inline reverse_iterator rbegin() noexcept {
        return range::begin(this->adaptee());
    }
    inline const_reverse_iterator rbegin() const noexcept {
        return range::begin(this->adaptee());
    }
    inline const_reverse_iterator crbegin() const noexcept {
        return range::begin(this->adaptee());
    }
    inline reverse_iterator rend() noexcept {
        return range::end(this->adaptee());
    }
    inline const_reverse_iterator rend() const noexcept {
        return range::end(this->adaptee());
    }
    inline const_reverse_iterator crend() const noexcept {
        return range::end(this->adaptee());
    }
    
    inline size_type size() const noexcept {
        return range::size(this->adaptee());
    }
    inline bool empty() const noexcept {
        return range::empty(this->adaptee());
    }
};

//------------------------------------------------------------------------------
namespace reversed_range_detail {
struct reversed_range_trigger {};
//------------------------------------------------------------------------------
template <class R>
inline reversed_range<typename remove_reference<R>::type> operator | (
    R &&r,
    reversed_range_trigger)
{
    return reversed_range<typename remove_reference<R>::type>(
        foundation::forward<R>(r));
}
//------------------------------------------------------------------------------
} // reversed_range_detail

//------------------------------------------------------------------------------
constexpr reversed_range_detail::reversed_range_trigger reversed;

/** @} */

}}} // namespaces

#endif // NIC_E62BC899C3AA4957_NIC