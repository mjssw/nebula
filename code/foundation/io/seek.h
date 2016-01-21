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
#ifndef NIC_41597E39CB9E61B2_NIC
#define NIC_41597E39CB9E61B2_NIC

#include "traits.h"
#include "../call_traits.h"
#include "../enable_if.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class Stream>
struct seekg_beg_impl
{
    inline static void apply(Stream &s,
        typename stream_offset<Stream>::type off)
    {
        s.seekg_beg(off);
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline void seekg_beg(Stream &&s,
    typename stream_offset<typename ctraits::value<Stream>::type>::type off)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_read<stream_t>::value), 
        "");
    n_static_assert(n_arg(
        has_seekg_beg<stream_t>::value), 
        "");
    
    seekg_beg_impl<stream_t>::apply(s, off);
}

//------------------------------------------------------------------------------
template <class Stream>
struct seekg_cur_impl
{
    inline static void apply(Stream &s,
        typename stream_offset<Stream>::type off)
    {
        s.seekg_cur(off);
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline void seekg_cur(Stream &&s,
    typename stream_offset<typename ctraits::value<Stream>::type>::type off)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_read<stream_t>::value), 
        "");
    n_static_assert(n_arg(
        has_seekg_cur<stream_t>::value), 
        "");
    
    seekg_cur_impl<stream_t>::apply(s, off);
}

//------------------------------------------------------------------------------
template <class Stream>
struct seekg_end_impl
{
    inline static void apply(Stream &s,
        typename stream_offset<Stream>::type off)
    {
        s.seekg_end(off);
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline void seekg_end(Stream &&s,
    typename stream_offset<typename ctraits::value<Stream>::type>::type off)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_read<stream_t>::value), 
        "");
    n_static_assert(n_arg(
        has_seekg_end<stream_t>::value), 
        "");
    
    seekg_end_impl<stream_t>::apply(s, off);
}

//------------------------------------------------------------------------------
template <class Stream>
struct seekp_beg_impl
{
    inline static void apply(Stream &s,
        typename stream_offset<Stream>::type off)
    {
        s.seekp_beg(off);
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline void seekp_beg(Stream &&s,
    typename stream_offset<typename ctraits::value<Stream>::type>::type off)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_write<stream_t>::value), 
        "");
    n_static_assert(n_arg(
        has_seekp_beg<stream_t>::value), 
        "");
    
    seekp_beg_impl<stream_t>::apply(s, off);
}

//------------------------------------------------------------------------------
template <class Stream>
struct seekp_cur_impl
{
    inline static void apply(Stream &s,
        typename stream_offset<Stream>::type off)
    {
        s.seekp_cur(off);
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline void seekp_cur(Stream &&s,
    typename stream_offset<typename ctraits::value<Stream>::type>::type off)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_write<stream_t>::value), 
        "");
    n_static_assert(n_arg(
        has_seekp_cur<stream_t>::value), 
        "");
    
    seekp_cur_impl<stream_t>::apply(s, off);
}

//------------------------------------------------------------------------------
template <class Stream>
struct seekp_end_impl
{
    inline static void apply(Stream &s,
        typename stream_offset<Stream>::type off)
    {
        s.seekp_end(off);
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline void seekp_end(Stream &&s,
    typename stream_offset<typename ctraits::value<Stream>::type>::type off)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_write<stream_t>::value), 
        "");
    n_static_assert(n_arg(
        has_seekp_end<stream_t>::value), 
        "");
    
    seekp_end_impl<stream_t>::apply(s, off);
}

/** @} */

}}} // namespaces

#endif // NIC_41597E39CB9E61B2_NIC