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
#ifndef NIC_6120249D26ABA986_NIC
#define NIC_6120249D26ABA986_NIC

#include "../../type_traits.h"
#include "../tags.h"
#include <iterator>

namespace nebula { namespace foundation { namespace iterator { namespace iterator_detail {
/** @ingroup Foundation
  @{ */
//------------------------------------------------------------------------------
template <class X, class Cat>
struct _has_category : public has_tag<Cat, X> {};

//------------------------------------------------------------------------------
template <class Cat>
struct _is_strict_std_iterator_category
    : integral_constant<bool,
      !_has_category<incrementable_traversal_tag, Cat>::value
      && (_has_category<std::output_iterator_tag, Cat>::value
          || _has_category<std::input_iterator_tag, Cat>::value
          || _has_category<std::forward_iterator_tag, Cat>::value
          || _has_category<std::bidirectional_iterator_tag, Cat>::value
          || _has_category<std::random_access_iterator_tag, Cat>::value)>
{};
//------------------------------------------------------------------------------
template <class I>
struct _is_strict_std_iterator
    : integral_constant<bool,
          _is_strict_std_iterator_category<typename std::iterator_traits<I>::iterator_category>::value
      >
{};

//------------------------------------------------------------------------------
template <class I, bool _F = _is_strict_std_iterator<I>::value>
struct _iterator_value {
    typedef typename I::value_type type;
};
template <class I>
struct _iterator_value<I, true> {
    typedef typename std::iterator_traits<I>::value_type type;
};

//------------------------------------------------------------------------------
template <class I, bool _F = _is_strict_std_iterator<I>::value>
struct _iterator_reference {
    typedef typename I::reference type;
};
template <class I>
struct _iterator_reference<I, true> {
    typedef typename std::iterator_traits<I>::reference type;
};

//------------------------------------------------------------------------------
template <class I, bool _F = _is_strict_std_iterator<I>::value>
struct _iterator_pointer {
    typedef typename I::pointer type;
};
template <class I>
struct _iterator_pointer<I, true> {
    typedef typename std::iterator_traits<I>::pointer type;
};

//------------------------------------------------------------------------------
template <class I, bool _F = _is_strict_std_iterator<I>::value>
struct _iterator_difference {
    typedef typename I::difference_type type;
};
template <class I>
struct _iterator_difference<I, true> {
    typedef typename std::iterator_traits<I>::difference_type type;
};

//------------------------------------------------------------------------------
template <class Cat>
struct _traversal_from_std_iterator {};

template <>
struct _traversal_from_std_iterator<std::output_iterator_tag> {
    typedef incrementable_traversal_tag type;
};

template <>
struct _traversal_from_std_iterator<std::input_iterator_tag> {
    typedef single_pass_traversal_tag type;
};

template <>
struct _traversal_from_std_iterator<std::forward_iterator_tag> {
    typedef forward_traversal_tag type;
};

template <>
struct _traversal_from_std_iterator<std::bidirectional_iterator_tag> {
    typedef bidirectional_traversal_tag type;
};

template <>
struct _traversal_from_std_iterator<std::random_access_iterator_tag> {
    typedef random_access_traversal_tag type;
};

//------------------------------------------------------------------------------
template <class I, bool _F = _is_strict_std_iterator<I>::value>
struct _iterator_traversal {
    typedef typename I::iterator_traversal type;
};

template <class I>
struct _iterator_traversal<I, true> {
    typedef typename _traversal_from_std_iterator<
        typename std::iterator_traits<I>::iterator_category
    >::type type;
};

//------------------------------------------------------------------------------
template <bool F>
struct _access_tag_helper {
    typedef readable_iterator_tag type;
};

template <>
struct _access_tag_helper<false> {
    typedef tag<readable_iterator_tag, 
        writable_iterator_tag, swapable_iterator_tag> type;
};

//------------------------------------------------------------------------------
template <class Cat, class T>
struct _access_from_std_iterator {};

template <class T>
struct _access_from_std_iterator<std::forward_iterator_tag, T> {
    typedef typename _access_tag_helper<is_assignable<T,T>::value>::type type;
};

template <class T>
struct _access_from_std_iterator<std::bidirectional_iterator_tag, T> {
    typedef typename _access_tag_helper<is_assignable<T,T>::value>::type type;
};

template <class T>
struct _access_from_std_iterator<std::random_access_iterator_tag, T> {
    typedef typename _access_tag_helper<is_assignable<T,T>::value>::type type;
};

template <class T>
struct _access_from_std_iterator<std::output_iterator_tag, T> {
    typedef writable_iterator_tag type;
};

//------------------------------------------------------------------------------
template <class I, bool _F = _is_strict_std_iterator<I>::value>
struct _iterator_access {
    typedef typename I::iterator_access type;
};

template <class I>
struct _iterator_access<I, true> {
    typedef typename _access_from_std_iterator<
        typename std::iterator_traits<I>::iterator_category,
        typename std::iterator_traits<I>::value_type
    >::type type;
};

//------------------------------------------------------------------------------
template <class I, bool _F = _is_strict_std_iterator<I>::value>
struct _iterator_category {
private:
    struct _X :
        _iterator_access<I>::type,
        _iterator_traversal<I>::type
    {};
public:
    typedef _X type;
};

template <class I>
struct _iterator_category<I, true> {
private:
    struct _X :
        _iterator_access<I>::type,
        _iterator_traversal<I>::type,
        std::iterator_traits<I>::iterator_category
    {};
public:
    typedef _X type;
};

/** @} */

}}}} // namespaces

#endif // NIC_6120249D26ABA986_NIC