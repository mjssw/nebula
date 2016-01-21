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
#ifndef NIC_6E3BB2969939DF79_NIC
#define NIC_6E3BB2969939DF79_NIC

#include "traits.h"
#include "../enable_if.h"
#include "../defs.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 * */
//------------------------------------------------------------------------------
template <
    class Derived,
    class ValueType,
    class Traversal,
    class Access,
    class Reference = ValueType&,
    class Pointer = ValueType*,
    class Difference = std::ptrdiff_t
>
class iterator_facade
{
    typedef Derived derived_type;

    struct _iterator_category
        : Traversal, Access
    {};

    /** @todo Somehow GCC produced ill-formed code when this function is inlined.
     * The version in question was 4.8.2.
     * I lost my records on this error, so if something behaves strangely
     * with iterators involved then __attribute__((noinline)) might be worth
     * a try? -lis
     * */
    inline Derived &derived() noexcept {
        return *static_cast<Derived*>(this);
    }
    inline const Derived &derived() const noexcept {
        return *static_cast<const Derived*>(this);
    }

public:
    typedef iterator_facade<
        Derived,
        Traversal,
        Access,
        Reference,
        Pointer,
        Difference> iterator_facade_;

public:
    typedef ValueType value_type;
    typedef Reference reference;
    typedef Pointer pointer;
    typedef Difference difference_type;

    typedef Traversal iterator_traversal;
    typedef Access iterator_access;
    typedef _iterator_category iterator_category;
    
    inline reference operator * () const
    {
        return this->derived().dereference();
    }
    inline pointer operator -> () const
    {
        return &this->derived().dereference();
    }
    
    inline derived_type operator ++ (int) // postfix
    {
        Derived r(this->derived());
        this->derived().increment();
        return r;
    }
    template <class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<bidirectional_traversal_tag, IT>,
            int>::type = 0>
    inline derived_type operator -- (int) // postfix
    {
        Derived r(this->derived());
        this->derived().decrement();
        return r;
    }
    inline derived_type &operator ++ () // prefix
    {
        this->derived().increment();
        return this->derived();
    }
    template <class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<bidirectional_traversal_tag, IT>,
            int>::type = 0>
    inline derived_type &operator -- () // prefix
    {
        this->derived().decrement();
        return this->derived();
    }
    
    template <class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<random_access_traversal_tag, IT>,
            int>::type = 0>
    inline derived_type operator + (const difference_type _delta) const
    {
        derived_type x(this->derived());
        x += _delta;
        return x;
    }
    template <class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<random_access_traversal_tag, IT>,
            int>::type = 0>
    inline derived_type & operator += (const difference_type _delta)
    {
        this->derived().advance(_delta);
        return this->derived();
    }
    template <class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<random_access_traversal_tag, IT>,
            int>::type = 0>
    inline derived_type operator - (const difference_type _delta) const
    {
        derived_type x(this->derived());
        x -= _delta;
        return x;
    }
    template <class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<random_access_traversal_tag, IT>,
            int>::type = 0>
    inline derived_type & operator -= (const difference_type _delta)
    {
        this->derived().advance(-_delta);
        return this->derived();
    }

    template <class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<random_access_traversal_tag, IT>,
            int>::type = 0>
    inline reference operator [] (const difference_type _delta) const
    {
        derived_type x(this->derived());
        return *(x + _delta);
    }

    template <class Other, class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<single_pass_traversal_tag, IT>,
            int>::type = 0>
    inline friend bool operator == (const derived_type &lhs, const Other &rhs)
    {
        return lhs.equal(rhs);
    }
    template <class Other, class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<single_pass_traversal_tag, IT>,
            int>::type = 0>
    inline friend bool operator != (const derived_type &lhs, const Other &rhs)
    {
        return !(lhs == rhs);
    }

    template <class Other, class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<random_access_traversal_tag, IT>,
            int>::type = 0>
    inline friend difference_type operator - (
        const Other &lhs, const derived_type &rhs)
    {
        return rhs.distance_to(lhs);
    }

    template <class Other, class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<random_access_traversal_tag, IT>,
            int>::type = 0>
    inline friend bool operator < (const derived_type &lhs, const Other &rhs)
    {
        return (rhs-lhs) > difference_type();
    }
    template <class Other, class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<random_access_traversal_tag, IT>,
            int>::type = 0>
    inline friend bool operator <= (const derived_type &lhs, const Other &rhs)
    {
        return (lhs<rhs) || lhs==rhs;
    }
    template <class Other, class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<random_access_traversal_tag, IT>,
            int>::type = 0>
    inline friend bool operator > (const derived_type &lhs, const Other &rhs)
    {
        return !(lhs<rhs);
    }
    template <class Other, class IT = iterator_traversal,
        typename enable_if<
            iterator_detail::_has_category<random_access_traversal_tag, IT>,
            int>::type = 0>
    inline friend bool operator >= (const derived_type &lhs, const Other &rhs)
    {
        return (lhs>rhs) || lhs==rhs;
    }
};

/** @} */

}}} // namespaces

#endif // NIC_6E3BB2969939DF79_NIC
