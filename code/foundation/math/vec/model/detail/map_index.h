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
#ifndef NIC_CA7AF439B0247DFD_NIC
#define NIC_CA7AF439B0247DFD_NIC

#include "../../traits.h"

#include "../../../../tuple.h"
#include "../../../../meta.h"

namespace nebula { namespace foundation { namespace math { namespace vec {
/** @ingroup Foundation
 * @{
 * */
namespace vec_indexer_detail {
//------------------------------------------------------------------------------
template <class Seq>
struct c_storage_order_indexer;

template <class First, class ... Rest>
struct c_storage_order_indexer<meta::seq<First, Rest...>>
{
    inline static size_t apply(
        const size_t first,
        const typename Rest::value_type ... rest) noexcept
    {
        return first * meta::_mul<Rest...>::value
            + c_storage_order_indexer<meta::seq<Rest...>>::apply(rest...);
    }
};

template <class Last>
struct c_storage_order_indexer<meta::seq<Last>>
{
    inline static size_t apply(const size_t last) noexcept
    {
        return last;
    }
};
//------------------------------------------------------------------------------
template <class Layout, class Tuple>
inline size_t map_index(const Tuple &tpl)
{
    return foundation::expand_tuple(c_storage_order_indexer<
        typename Layout::type>::apply, tpl);
}

} // vec_indexer_detail

/** @} */

}}}} // namespaces

#endif // NIC_CA7AF439B0247DFD_NIC

