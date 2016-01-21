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
#ifndef NIC_8AA67B775E9DEDF7_NIC
#define NIC_8AA67B775E9DEDF7_NIC

#include "../algo_fwd.h"
#include "../seq_fwd.h"
#include "../iter_fwd.h"
#include "../or.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace find_detail {
//------------------------------------------------------------------------------
/** @internal Evaluate F<> only if Iter != Last. */
template <
    template <class ...> class F,
    class Iter,
    class Last>
struct eval_
{
    using type = F<_deref<Iter>>;
};

template <
    template <class ...> class F,
    class Last>
struct eval_<F, Last, Last>
{
    using type = true_; // doesn't matter if true_ or false_;
};

//------------------------------------------------------------------------------
template <
    class First,
    class Last, 
    template <class ...> class F,
    class Cond = _or<eval_<F, First, Last>, equal_<First, Last>> >
struct find_impl_
{
    using type =
        typename find_impl_<
            _next<First>,
            Last,
            F>::type;
};

template <
    class First,
    class Last, 
    template <class ...> class F>
struct find_impl_<First, Last, F, meta::true_>
{
    using type = First;
};

} // find_detail

//------------------------------------------------------------------------------
template <
    class Range, 
    template <class ...> class F>
struct find_
{
    using type =
        typename find_detail::find_impl_<
            _begin<Range>,
            _end<Range>,
            F>::type;
};

/** @} */

}}} // namespaces

#endif // NIC_8AA67B775E9DEDF7_NIC