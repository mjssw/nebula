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
#ifndef NIC_14162B4009B6E310_NIC
#define NIC_14162B4009B6E310_NIC

#include "traits.h"
#include "../call_traits.h"
#include "../enable_if.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class Stream>
struct tellg_impl
{
    inline static typename stream_position<Stream>::type apply(Stream &s)
    {
        return s.tellg();
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline typename stream_position<typename ctraits::value<Stream>::type>::type 
tellg(Stream &&s)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_read<stream_t>::value), 
        "");

    return tellg_impl<stream_t>::apply(s);
}

//------------------------------------------------------------------------------
template <class Stream>
struct tellp_impl
{
    inline static typename stream_position<Stream>::type apply(Stream &s)
    {
        return s.tellp();
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline typename stream_position<typename ctraits::value<Stream>::type>::type 
tellp(Stream &&s)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_write<stream_t>::value), 
        "");
    
    return tellp_impl<stream_t>::apply(s);
}

/** @} */

}}} // namespaces

#endif // NIC_14162B4009B6E310_NIC