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
#ifndef NIC_EAE6EEE029B748E0_NIC
#define NIC_EAE6EEE029B748E0_NIC

#include "iterator_facade.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 * */
//------------------------------------------------------------------------------
/** A simple helper template to create iterators from other iterators.
 * */
template <class I, class Foo = I>
class normal_iterator 
: public iterator_facade<
    normal_iterator<I, Foo>,
    typename iterator_value<I>::type,
    typename iterator_traversal<I>::type,
    typename iterator_access<I>::type,
    typename iterator_reference<I>::type,
    typename iterator_pointer<I>::type,
    typename iterator_difference<I>::type
>
{
public:
    explicit inline normal_iterator(I i_) noexcept
    : i(i_)
    {}
    normal_iterator(normal_iterator &) noexcept = default;
    normal_iterator(const normal_iterator &) noexcept = default;
    normal_iterator(normal_iterator &&) noexcept = default;
    
    template <class J>
    inline normal_iterator(const normal_iterator<J, Foo> &other) noexcept
    : i(other.get())
    {}
    template <class J>
    inline normal_iterator(normal_iterator<J, Foo> &&other) noexcept
    : i(foundation::move(other.get()))
    {}
    
    normal_iterator &operator = (const normal_iterator &) noexcept = default;
    normal_iterator &operator = (normal_iterator &&) noexcept = default;
    
    template <class J>
    inline normal_iterator &
    operator = (const normal_iterator<J, Foo> other) noexcept
    {
        i = other.get();
        return *this;
    }
    template <class J>
    inline normal_iterator &
    operator = (normal_iterator<J, Foo> &&other) noexcept
    {
        i = foundation::move(other.get());
        return *this;
    }
    
    inline typename iterator_reference<I>::type dereference() const
    {
        return *i;
    }
    
    inline void increment()
    {
        i++;
    }
    template <class C = typename iterator_category<I>::type,
        typename enable_if<
            has_tag<C, bidirectional_traversal_tag>, int>::type = 0>
    inline void decrement()
    {
        i--;
    }
    template <class C = typename iterator_category<I>::type,
        typename enable_if<
            has_tag<C, random_access_traversal_tag>, int>::type = 0>
    inline void advance(const typename iterator_difference<I>::type n)
    {
        i += n;
    }
    
    template <class C = typename iterator_category<I>::type,
        typename enable_if<
            has_tag<C, random_access_traversal_tag>, int>::type = 0>
    inline typename iterator_difference<I>::type
    distance_to(const normal_iterator &other) const
    {
        return other.i - i;
    }
    
    inline bool equal(const normal_iterator &other) const
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

#endif // NIC_EAE6EEE029B748E0_NIC
