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
#ifndef NIC_31B0CF34C9813EA4_NIC
#define NIC_31B0CF34C9813EA4_NIC

#include "../basic/abs.h"
#include "../../range.h"

namespace nebula { namespace foundation { namespace math { namespace vec {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Vector>
struct scalar_value
{
    using type = typename range::range_value<Vector>::type;
};

n_meta_alias(scalar_value);

//------------------------------------------------------------------------------
template <class Vector>
struct metric_value
{
    using type = decltype(
        math::abs(foundation::declval<
            _scalar_value<Vector>>()));
};

n_meta_alias(metric_value);

//------------------------------------------------------------------------------
template <class Vector>
struct layout {};

n_meta_alias(layout);

//------------------------------------------------------------------------------
template <class Vector, class Layout>
struct resize {};

n_meta_alias(resize);

//------------------------------------------------------------------------------
template <class Vector, class NewT>
struct rebind {};

n_meta_alias(rebind);

//------------------------------------------------------------------------------
/** @note Do not specialize. */
template <class ... Vector>
struct order
{
    using type = meta::_size<_layout<Vector...>>;
};

n_meta_alias(order);

//------------------------------------------------------------------------------
/** @note Do not specialize. */
template <class Vector, size_t N>
struct size_at
{
    using type = meta::_at<_layout<Vector>, meta::size_t_<N>>;
};
template <class Vector, class N>
struct size_at_ : public size_at<Vector, N::type::value> {};
template <class Vector, class N>
using _size_at = typename size_at_<Vector, N>::type;

//------------------------------------------------------------------------------
/** @note Do not specialize. */
template <class Vector>
struct size
{
    using type = meta::_for_each<
        _layout<Vector>,
        n_bind(meta::mul_<meta::_1, meta::_2>),
        meta::size_t_<1>>;
};

n_meta_alias(size);

//------------------------------------------------------------------------------
/** Simple helper function. */
template <size_t ... N>
using make_layout = meta::seq<meta::size_t_<N>...>;

/** @} */

}}}} // namespaces

#endif // NIC_31B0CF34C9813EA4_NIC

