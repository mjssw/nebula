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
#ifndef NIC_55ADE58304EF9957_NIC
#define NIC_55ADE58304EF9957_NIC

#include "traits.h"
#include "exception.h"
#include "../call_traits.h"
#include "../enable_if.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class Stream>
struct read_impl
{
    inline static typename stream_size<Stream>::type apply(Stream &s,
        char *x, 
        typename stream_size<Stream>::type n)
    {
        return s.read(x, n);
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline typename stream_size<typename ctraits::value<Stream>::type>::type 
read(Stream &&s, char *x, 
    typename stream_size<typename ctraits::value<Stream>::type>::type n)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_read<stream_t>::value),
        "");
    
    return read_impl<stream_t>::apply(s, x, n);
}

/** @} */

}}} // namespaces

#endif // NIC_55ADE58304EF9957_NIC