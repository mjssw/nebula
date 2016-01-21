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
#ifndef NIC_B3474BD5AC888F4C_NIC
#define NIC_B3474BD5AC888F4C_NIC

#include "../defs.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace scope_exit_detail {
//------------------------------------------------------------------------------
template <class F>
class scope_exit_holder
{
public:
    template <class F_>
    inline scope_exit_holder(F_ &&f_)
    : _f(std::forward<F_>(f_)), _commit(true)
    {}

    inline scope_exit_holder(scope_exit_holder &&x)
    : _f(std::move(x._f)), _commit(true)
    {
        x.dismiss();
    }

    scope_exit_holder() = delete;
    scope_exit_holder(scope_exit_holder &) = delete;
    scope_exit_holder(const scope_exit_holder &) = delete;
    scope_exit_holder &operator = (const scope_exit_holder &) = delete;
    scope_exit_holder &operator = (scope_exit_holder &) = delete;
    scope_exit_holder &operator = (scope_exit_holder &&) = delete;

    /** If dismiss() hasn't been called prior to the destructor invokation
     * then the user-defined lambda is executed. Throwing within this destructor
     * is valid behaviour.
     * */
    inline ~scope_exit_holder()
    {
        if(_commit)
            _f();
    }

    /** If called, the destructor won't call the user-defined lambda when
     * invoked. Subsequent calls have no effect.
     * @throw noexcept
     * */
    inline void dismiss() noexcept { _commit = false; }

private:
    F _f;
    bool _commit;
};

} // scope_exit_detail

/** @} */

}} // namespaces

#endif // NIC_B3474BD5AC888F4C_NIC