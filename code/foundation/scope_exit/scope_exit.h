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
#ifndef NIC_CC796024C4F6D00B_NIC
#define NIC_CC796024C4F6D00B_NIC

#include "scope_exit_holder.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class F>
inline scope_exit_detail::scope_exit_holder<F> scope_exit(F &&f)
{
    return scope_exit_detail::scope_exit_holder<F>(std::forward<F>(f));
}

//------------------------------------------------------------------------------
namespace scope_exit_detail {
//------------------------------------------------------------------------------
struct _anon_helper {};
//------------------------------------------------------------------------------
template <class F>
inline scope_exit_holder<F> operator + (_anon_helper, F &&f) {
    return scope_exit_holder<F>(std::forward<F>(f));
}
//------------------------------------------------------------------------------
} // scope_exit_detail
//------------------------------------------------------------------------------
#define _n_scope_exit_concat_string_impl(_s0, _s1) _s0 ## _s1
#define _n_scope_exit_concat_string(_s0, _s1) \
    _n_scope_exit_concat_string_impl(_s0, _s1)
#define _n_scope_exit_make_var_name(_s) \
    _n_scope_exit_concat_string(_s, __COUNTER__)
//------------------------------------------------------------------------------
/** Creates an anonymous scope guard object.
 * @code
 * n_scope_exit(capture) mutable(optional) exception attribute -> ret { ... };
 * // is the same as
 * auto -unique_name- = scope_exit(
 * [capture]() mutable(optional) exception attribute -> ret { ... });
 * @endcode
 * */
#define n_scope_exit(...) \
    auto _n_scope_exit_make_var_name(N_ON_SCOPE_EXIT_) \
    = ::nebula::foundation::scope_exit_detail::_anon_helper() + [__VA_ARGS__]()

/** @} */

}} // namespaces

#endif // NIC_CC796024C4F6D00B_NIC