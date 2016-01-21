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
#ifndef NIC_AB16A77E6DD0B2AB_NIC
#define NIC_AB16A77E6DD0B2AB_NIC

#include "config.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
template <class T>
struct lock_impl
{
    inline static void apply(T &x)
    {
        x.lock();
    }
};
//------------------------------------------------------------------------------
/** Perform a locking operation.
 *
 *  This can fail (throw) if
 *  - the maximum number of recursive locks has already been reached.
 *  - a deadlock was detected.
 * */
template <class T>
inline void lock(T &x)
{
    lock_impl<T>::apply(x);
}

}}} // namespaces

#endif // NIC_AB16A77E6DD0B2AB_NIC
