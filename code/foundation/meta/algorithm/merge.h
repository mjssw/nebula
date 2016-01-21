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
#ifndef NIC_610D29531EDB38B9_NIC
#define NIC_610D29531EDB38B9_NIC

#include "for_each.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace merge_detail {
//------------------------------------------------------------------------------
template <class Result, class First, class ... Rest>
struct do_merge_
{
    template <class R, class T>
    struct F {
        using type = _push_back<R, T>;
    };
    
    using new_state = _for_each<
        First,
        F,
        Result
    >;
    
    using type = typename do_merge_<new_state, Rest...>::type;
};
//------------------------------------------------------------------------------
template <class Result, class Last>
struct do_merge_<Result, Last>
{
    template <class R, class T>
    struct F {
        using type = _push_back<R, T>;
    };
    
    using type = _for_each<
        Last,
        F,
        Result
    >;
};
//------------------------------------------------------------------------------
template <class Result, class ... Rest>
struct merge_impl_
{
    using type = typename merge_detail::do_merge_<Result, Rest...>::type;
};
//------------------------------------------------------------------------------
template <class Result>
struct merge_impl_<Result>
{
    using type = Result;
};
//------------------------------------------------------------------------------
} // merge_detail
//------------------------------------------------------------------------------
/** Merging sequences using push_back.
 * */
template <class ... S>
struct merge_
{
    using type = typename merge_detail::merge_impl_<S...>::type;
};

template <class ... S>
using _merge = typename merge_<S...>::type;

/** @} */

}}} // namespaces

#endif // NIC_610D29531EDB38B9_NIC