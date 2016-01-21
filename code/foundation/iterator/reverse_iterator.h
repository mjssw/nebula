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
#ifndef NIC_EF8F5056BEE2A2EC_NIC
#define NIC_EF8F5056BEE2A2EC_NIC

#include "iterator_facade.h"
#include "algorithm/prev.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 * */
//------------------------------------------------------------------------------
/** A simple helper template to create reverse iterators from normal iterators.
 * */
template <class I, class Foo = I>
class reverse_iterator 
: public iterator_facade<
    reverse_iterator<I, Foo>,
    typename iterator_value<I>::type,
    typename iterator_traversal<I>::type,
    typename iterator_access<I>::type,
    typename iterator_reference<I>::type,
    typename iterator_pointer<I>::type,
    typename iterator_difference<I>::type
>
{
    n_static_assert(
        n_arg(
            has_tag<typename iterator_category<I>::type,
            bidirectional_traversal_tag>::value),
        "Bidirectional iterator required.");
    
public:
    inline explicit reverse_iterator(I i_) noexcept
    : i(i_)
    {}
    reverse_iterator(const reverse_iterator &) noexcept = default;
    reverse_iterator(reverse_iterator &&) noexcept = default;
    
    template <class J>
    inline reverse_iterator(const reverse_iterator<J, Foo> &other) noexcept
    : i(other.get())
    {}
    template <class J>
    inline reverse_iterator(reverse_iterator<J, Foo> &&other) noexcept
    : i(foundation::move(other.get()))
    {}
    
    reverse_iterator &operator = (const reverse_iterator &) noexcept = default;
    reverse_iterator &operator = (reverse_iterator &&) noexcept = default;
    
    template <class J>
    inline reverse_iterator &
    operator = (const reverse_iterator<J, Foo> &other) noexcept
    {
        i = other.get();
        return *this;
    }
    template <class J>
    inline reverse_iterator &
    operator = (reverse_iterator<J, Foo> &&other) noexcept
    {
        i = foundation::move(other.get());
        return *this;
    }
    
    inline typename iterator_reference<I>::type dereference() const
    {
        return *foundation::iterator::prev(i);
    }
    
    inline void increment()
    {
        i--;
    }
    inline void decrement()
    {
        i++;
    }
    template <class C = typename iterator_category<I>::type,
        typename enable_if<
            has_tag<C, random_access_traversal_tag>, int>::type = 0>
    inline void advance(const typename iterator_difference<I>::type n)
    {
        i -= n;
    }
    
    template <class C = typename iterator_category<I>::type,
        typename enable_if<
            has_tag<C, random_access_traversal_tag>, int>::type = 0>
    inline typename iterator_difference<I>::type
    distance_to(const reverse_iterator &other) const
    {
        return i - other.i;
    }
    
    inline bool equal(const reverse_iterator &other) const
    {
        return i == other.i;
    }
    
    inline const I &get() const noexcept { return i; }
    inline I &get() noexcept { return i; }
    
private:
    I i;
};

/** @} */

}}} // namespaces

#endif // NIC_EF8F5056BEE2A2EC_NIC
