/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 lis (lis@tutanota.com)
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
#ifndef NIC_736FAD8CA578CD36_NIC
#define NIC_736FAD8CA578CD36_NIC

#include "config.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
template <class T, class M, class D>
struct wait_for_impl
{
    inline static bool apply(T &x, M &m, const D &d)
    {
        return x.wait_for(m, d);
    }
    template <class F>
    inline static bool apply(T &x, M &m, const D &d, F &&f)
    {
        return x.wait_for(m, d, f);
    }
};
//------------------------------------------------------------------------------
/** Wait for a condition variable.
 *
 *  Can only fail if
 *  - Different mutexes were supplied for concurrent wait_for()
 *  or wait() operations on the same condition variable.
 *  - The mutex was not owned by the calling thread.
 * */
template <class T, class M, class D>
inline bool wait_for(T &x, M &m, const D &d)
{
    return wait_for_impl<T, M, D>::apply(x, m, d);
}
//------------------------------------------------------------------------------
template <class T, class M, class D, class F>
inline bool wait_for(T &x, M &m, const D &d, F &&f)
{
    return wait_for_impl<T, M, D>::apply(x, m, d, f);
}

}}} // namespaces

#endif // NIC_736FAD8CA578CD36_NIC
