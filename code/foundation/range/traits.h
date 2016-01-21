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
#ifndef NIC_ED6F85A38DEAC48B_NIC
#define NIC_ED6F85A38DEAC48B_NIC

#include "../iterator.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
// Cut down typing.
// May only be used inside the range library.
namespace ins_ = ::nebula::foundation::iterator;

//------------------------------------------------------------------------------
using ins_::incrementable_traversal_tag;
using ins_::single_pass_traversal_tag;
using ins_::forward_traversal_tag;
using ins_::bidirectional_traversal_tag;
using ins_::random_access_traversal_tag;

//------------------------------------------------------------------------------
template <class R>
struct range_iterator {
    typedef typename R::iterator type;
};

template <class R>
struct range_iterator<const R> {
    typedef typename R::const_iterator type;
};
//------------------------------------------------------------------------------
template <class R>
struct range_reverse_iterator {
    typedef typename R::reverse_iterator type;
};

template <class R>
struct range_reverse_iterator<const R> {
    typedef typename R::const_reverse_iterator type;
};

//------------------------------------------------------------------------------
template <class R>
struct range_category {
    typedef typename ins_::iterator_traversal<
        typename range_iterator<R>::type
    >::type type;
};

//------------------------------------------------------------------------------
template <class R>
struct range_traversal {
    typedef typename ins_::iterator_traversal<
        typename range_iterator<R>::type
    >::type type;
};
//------------------------------------------------------------------------------
template <class R>
struct range_difference {
    typedef typename ins_::iterator_difference<
        typename range_iterator<R>::type
        >::type type;
};

//------------------------------------------------------------------------------
template <class R>
struct range_size {
    typedef typename R::size_type type;
};

//------------------------------------------------------------------------------
template <class R>
struct range_value {
    typedef typename R::value_type type;
};

//------------------------------------------------------------------------------
template <class R>
struct range_reference {
    typedef typename R::reference type;
};
//------------------------------------------------------------------------------
template <class R>
struct range_reference<const R> {
    typedef typename R::const_reference type;
};

//------------------------------------------------------------------------------
template <class R>
struct range_pointer {
    typedef typename R::pointer type;
};
//------------------------------------------------------------------------------
template <class R>
struct range_pointer<const R> {
    typedef typename R::const_pointer type;
};

//------------------------------------------------------------------------------
n_meta_alias(range_value);
n_meta_alias(range_reference);
n_meta_alias(range_pointer);
n_meta_alias(range_size);
n_meta_alias(range_difference);
n_meta_alias(range_iterator);
n_meta_alias(range_reverse_iterator);
n_meta_alias(range_category);
n_meta_alias(range_traversal);

/** @} */

}}} // namespaces

#endif // NIC_ED6F85A38DEAC48B_NIC
