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
#ifndef NIC_AC36BA8669BE5DB8_NIC
#define NIC_AC36BA8669BE5DB8_NIC

#include "config.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
template <class T, class D>
struct try_lock_for_impl
{
    inline static bool apply(T &x, const D &t)
    {
        return x.try_lock_for(t);
    }
};
//------------------------------------------------------------------------------
/** Try to acquire a lock for a certain amount of time.
 *
 *  This can fail (throw) if
 *  - the maximum number of recursive locks has already been reached.
 *  - a deadlock was detected.
 * */
template <class T, class D>
inline bool try_lock_for(T &x, const D &t)
{
    return try_lock_for_impl<T, D>::apply(x, t);
}

}}} // namespaces

#endif // NIC_AC36BA8669BE5DB8_NIC
