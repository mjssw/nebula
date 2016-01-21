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
#ifndef NIC_4F584B275B0AA525_NIC
#define NIC_4F584B275B0AA525_NIC

#include "../../adaptor.h"
#include "../common.h"
#include "../../assert.h"
#include "../../math/basic/abs.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
/** */
template <class R>
class stridden_range : public adaptor_base<R>
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
    
private:
    template <class I>
    class striding_iterator : 
    public ins_::iterator_facade
    <
        striding_iterator<I>,
        typename ins_::iterator_value<I>::type,
        typename ins_::iterator_traversal<I>::type,
        typename ins_::iterator_access<I>::type,
        typename ins_::iterator_reference<I>::type,
        typename ins_::iterator_pointer<I>::type,
        typename ins_::iterator_difference<I>::type
    >
    {
    public:
        inline explicit striding_iterator(
            I i_, const difference_type step_) noexcept
        : i(i_), step(step_)
        {}
        
        striding_iterator(striding_iterator &) = default;
        striding_iterator(const striding_iterator &) = default;
        striding_iterator(striding_iterator &&) = default;
        
        striding_iterator &operator = (const striding_iterator &) = default;
        striding_iterator &operator = (striding_iterator &&) = default;
        
        inline typename ins_::iterator_reference<I>::type dereference() const
        {
            return *i;
        }
        
        inline void increment()
        {
            i += step;
        }
        inline void decrement()
        {
            i -= step;
        }
        inline void advance(const difference_type n)
        {
            i += (n * step);
        }
        
        inline difference_type distance_to(const striding_iterator &other) const
        {
            return (other.i - i) / step;
        }
        
        inline bool equal(const striding_iterator &other) const
        {
            return math::abs(other.i - i) < step;
        }
        
    private:
        I i;
        difference_type step;
    };
    
public:
    using iterator = striding_iterator<
        typename range_iterator<R>::type>;
    using const_iterator = striding_iterator<
        typename range_iterator<const range_>::type>;
    using reverse_iterator = ins_::reverse_iterator<iterator>;
    using const_reverse_iterator = ins_::reverse_iterator<const_iterator>;
    
    stridden_range(stridden_range &) = default;
    stridden_range(const stridden_range &) = default;
    stridden_range(stridden_range &&) = default;
    
    /** @param step_ Defines the step size which must be > 0.
     *  @param r A random access range.
     * */
    template <class R_>
    inline stridden_range(R_ &&r, const difference_type step_)
    : adaptor_base<R>(foundation::forward<R_>(r)), step(step_)
    {
        n_assert(step_ > 0);
    }
    
    stridden_range &operator = (const stridden_range &rhs) = default;
    stridden_range &operator = (stridden_range &&rhs) = default;
    
    inline iterator begin() noexcept {
        return iterator(range::begin(this->adaptee()), step);
    }
    inline const_iterator begin() const noexcept {
        return const_iterator(range::begin(this->adaptee()), step);
    }
    inline const_iterator cbegin() const noexcept {
        return const_iterator(range::begin(this->adaptee()), step);
    }
    inline iterator end() noexcept {
        return iterator(range::end(this->adaptee()), step);
    }
    inline const_iterator end() const noexcept {
        return const_iterator(range::end(this->adaptee()), step);;
    }
    inline const_iterator cend() const noexcept {
        return const_iterator(range::end(this->adaptee()), step);
    }
    
    inline reverse_iterator rbegin() noexcept {
        return reverse_iterator(this->end());
    }
    inline const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(this->end());
    }
    inline const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(this->end());
    }
    inline reverse_iterator rend() noexcept {
        return reverse_iterator(this->begin());
    }
    inline const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(this->begin());
    }
    inline const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(this->begin());
    }
    
    inline size_type size() const noexcept {
        const size_type n = range::size(this->adaptee());
        return n == 0 ? 0 : (n-1) / step + 1;
    }
    inline bool empty() const noexcept {
        return range::empty(this->adaptee());
    }
    
private:
    difference_type step;
};

//------------------------------------------------------------------------------
namespace stridden_range_detail {
template <class N>
struct stridden_range_trigger {
    N n;
};
//------------------------------------------------------------------------------
template <class R, class N>
inline stridden_range<typename remove_reference<R>::type> operator | (
    R &&r,
    stridden_range_trigger<N> x)
{
    return stridden_range<typename remove_reference<R>::type>(
        foundation::forward<R>(r), x.n);
}
//------------------------------------------------------------------------------
} // stridden_range_detail

//------------------------------------------------------------------------------
template <class N>
inline stridden_range_detail::stridden_range_trigger<N> stridden(N x) noexcept
{
    return stridden_range_detail::stridden_range_trigger<N>{x};
}

/** @} */

}}} // namespaces

#endif // NIC_4F584B275B0AA525_NIC
