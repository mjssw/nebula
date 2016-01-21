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
#ifndef NIC_D38778C3911E33E3_NIC
#define NIC_D38778C3911E33E3_NIC

#include "../../adaptor.h"
#include "../common.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
/** */
template <class R>
class sliced_range : public adaptor_base<R>
{
    using range_ = typename remove_const<R>::type;
    
    n_static_assert(n_arg(
        has_tag<typename range_traversal<range_>::type,
        random_access_traversal_tag>::type::value),
        "Random Access - Range required.");
    
public:
    using value_type = typename range_value<range_>::type;
    using reference = typename range_reference<R>::type;
    using const_reference = typename range_reference<const range_>::type;
    using pointer = typename range_pointer<R>::type;
    using const_pointer = typename range_pointer<const range_>::type;
    
    using size_type = typename range_size<range_>::type;
    using difference_type = typename range_difference<range_>::type;
    
    using iterator = typename range_iterator<R>::type;
    using const_iterator = typename range_iterator<const range_>::type;
    using reverse_iterator = typename range_reverse_iterator<R>::type;
    using const_reverse_iterator
        = typename range_reverse_iterator<const range_>::type;
    
    sliced_range(sliced_range &) = default;
    sliced_range(const sliced_range &) = default;
    sliced_range(sliced_range &&) = default;
    
    template <class R_>
    inline sliced_range(R_ &&r,
        const difference_type first_,
        const difference_type last_)
    : adaptor_base<R>(foundation::forward<R_>(r)),
    f(first_), l(last_)
    {}
    
    sliced_range &operator = (const sliced_range &rhs) = default;
    sliced_range &operator = (sliced_range &&rhs) = default;
    
    inline iterator begin() noexcept {
        return range::begin(this->adaptee()) + f;
    }
    inline const_iterator begin() const noexcept {
        return range::begin(this->adaptee()) + f;
    }
    inline const_iterator cbegin() const noexcept {
        return range::begin(this->adaptee()) + f;
    }
    inline iterator end() noexcept {
        return range::begin(this->adaptee()) + l;
    }
    inline const_iterator end() const noexcept {
        return range::begin(this->adaptee()) + l;
    }
    inline const_iterator cend() const noexcept {
        return range::begin(this->adaptee()) + l;
    }
    
    inline reverse_iterator rbegin() noexcept {
        return range::rend(this->adaptee()) - l;
    }
    inline const_reverse_iterator rbegin() const noexcept {
        return range::rend(this->adaptee()) - l;
    }
    inline const_reverse_iterator crbegin() const noexcept {
        return range::rend(this->adaptee()) - l;
    }
    inline reverse_iterator rend() noexcept {
        return range::rend(this->adaptee()) - f;
    }
    inline const_reverse_iterator rend() const noexcept {
        return range::rend(this->adaptee()) - f;
    }
    inline const_reverse_iterator crend() const noexcept {
        return range::rend(this->adaptee()) - f;
    }
    
    inline size_type size() const noexcept {
        return size_type(l-f);
    }
    inline bool empty() const noexcept {
        return f == l;
    }
    
private:
    difference_type f, l;
};

//------------------------------------------------------------------------------
namespace sliced_range_detail {
//------------------------------------------------------------------------------
template <class I, class J>
struct sliced_range_params
{
    I a;
    J b;
};
//------------------------------------------------------------------------------
template <class R, class I, class J>
inline sliced_range<typename remove_reference<R>::type> operator | (
    R &&r,
    sliced_range_params<I, J> x)
{
    using result_type = sliced_range<typename remove_reference<R>::type>;
    return result_type(
        foundation::forward<R>(r),
        typename range_difference<result_type>::type(x.a), 
        typename range_difference<result_type>::type(x.a)
            + typename range_difference<result_type>::type(x.b));
}
//------------------------------------------------------------------------------
} // sliced_range_detail

//------------------------------------------------------------------------------
template <class I, class J>
inline sliced_range_detail::sliced_range_params<I, J> sliced(
    I a,
    J b) noexcept
{
    return sliced_range_detail::sliced_range_params<I, J>{a, b};
}

/** @} */

}}} // namespaces

#endif // NIC_D38778C3911E33E3_NIC