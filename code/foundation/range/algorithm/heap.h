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
#ifndef NIC_8EBAD572BE2988CF_NIC
#define NIC_8EBAD572BE2988CF_NIC

#include "../common.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class R>
struct make_heap_impl
{
    template <class F_>
    inline static void apply(R &r, F_ &&f)
    {
        ins_::make_heap(range::begin(r), range::end(r), f);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class R, class F>
inline void make_heap(R &&r, F &&f)
{
    return make_heap_impl<
        typename ctraits::value<R>::type
    >::apply(r, f);
}

//------------------------------------------------------------------------------
template <class R>
struct pop_heap_impl
{
    template <class F_>
    inline static void apply(R &r, F_ &&f)
    {
        ins_::pop_heap(range::begin(r), range::end(r), f);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class R, class F>
inline void pop_heap(R &&r, F &&f)
{
    return pop_heap_impl<
        typename ctraits::value<R>::type
    >::apply(r, f);
}

//------------------------------------------------------------------------------
template <class R>
struct push_heap_impl
{
    template <class F_>
    inline static void apply(R &r, F_ &&f)
    {
        ins_::push_heap(range::begin(r), range::end(r), f);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class R, class F>
inline void push_heap(R &&r, F &&f)
{
    return push_heap_impl<
        typename ctraits::value<R>::type
    >::apply(r, f);
}

//------------------------------------------------------------------------------
template <class R>
struct sort_heap_impl
{
    template <class F_>
    inline static void apply(R &r, F_ &&f)
    {
        ins_::sort_heap(range::begin(r), range::end(r), f);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class R, class F>
inline void sort_heap(R &&r, F &&f)
{
    return sort_heap_impl<
        typename ctraits::value<R>::type
    >::apply(r, f);
}

//------------------------------------------------------------------------------
template <class R>
struct is_heap_impl
{
    template <class F_>
    inline static bool apply(R &r, F_ &&f)
    {
        return ins_::is_heap(range::begin(r), range::end(r), f);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class R, class F>
inline bool is_heap(R &&r, F &&f)
{
    return is_heap_impl<
        typename ctraits::value<R>::type
    >::apply(r, f);
}

/** @} */

}}} // namespaces

#endif // NIC_8EBAD572BE2988CF_NIC
