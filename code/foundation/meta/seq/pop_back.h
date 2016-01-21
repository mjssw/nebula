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
#ifndef NIC_283BC0E883EA0E6F_NIC
#define NIC_283BC0E883EA0E6F_NIC

#include "push_back.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace pop_back_detail {
//------------------------------------------------------------------------------
template <class Out, class First, class ... Rest>
struct do_pop_back {
    using type = typename do_pop_back<
        _push_back<Out, First>,
        Rest ...>::type;
};

template <class Out, class Last>
struct do_pop_back<Out, Last> {
    using type = Out;
};
//------------------------------------------------------------------------------
} // pop_back_detail
//------------------------------------------------------------------------------
template <class ... T>
struct pop_back_<seq<T...>>  {
    using type = typename pop_back_detail::do_pop_back<seq<>, T...>::type;
};

/** @} */

}}} // namespaces

#endif // NIC_283BC0E883EA0E6F_NIC