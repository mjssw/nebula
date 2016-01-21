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
#ifndef NIC_FE2827317FB9AC5D_NIC
#define NIC_FE2827317FB9AC5D_NIC

#include "../string.h"
#include "../cstring.h"
#include "match_result.h"
#include "regex.h"

namespace nebula { namespace foundation { namespace regex {
//------------------------------------------------------------------------------
/**
 * */
template <class R>
struct search_impl
{
    template <class A>
    inline static bool apply(
        const char *first,
        const char *last,
        const R &r,
        match_result<A> &m)
    {
        return r.search_(first, last, m);
    }
    
    inline static bool apply(
        const char *first,
        const char *last,
        const R &r)
    {
        return r.search_(first, last);
    }
};
//------------------------------------------------------------------------------
template <class R, class Alloc>
inline bool search(
    const char *first,
    const char *last, 
    const R &r,
    match_result<Alloc> &m)
{
    return search_impl<R>::apply(
        first, last, r, m);
}
//------------------------------------------------------------------------------
template <class R, class Alloc>
inline bool search(
    const char *s,
    const R &r,
    match_result<Alloc> &m)
{
    return search_impl<R>::apply(
        s, s + foundation::strlen(s), r, m);
}
//------------------------------------------------------------------------------
template <class C, class CT, class A, class R, class Alloc>
inline bool search(
    const basic_string<C, CT, A> &s, 
    const R &r,
    match_result<Alloc> &m)
{
    return search_impl<R>::apply(
        s.c_str(), s.c_str() + s.size(), r, m);
}
//------------------------------------------------------------------------------
template <class C, class CT, class R, class Alloc>
inline bool search(
    basic_cstring<C, CT> s, 
    const R &r,
    match_result<Alloc> &m)
{
    return search_impl<R>::apply(
        s.data(), s.data() + s.size(), r, m);
}

//------------------------------------------------------------------------------
template <class R>
inline bool search(
    const char *first,
    const char *last, 
    const R &r)
{
    return search_impl<R>::apply(
        first, last, r);
}
//------------------------------------------------------------------------------
template <class R>
inline bool search(
    const char *s,
    const R &r)
{
    return search_impl<R>::apply(
        s, s + foundation::strlen(s), r);
}
//------------------------------------------------------------------------------
template <class C, class CT, class A, class R>
inline bool search(
    const basic_string<C, CT, A> &s, 
    const R &r)
{
    return search_impl<R>::apply(
        s.data(), s.data() + s.size(), r);
}
//------------------------------------------------------------------------------
template <class C, class CT, class R>
inline bool search(
    basic_cstring<C, CT> s, 
    const R &r)
{
    return search_impl<R>::apply(
        s.data(), s.data() + s.size(), r);
}

}}} // namespaces

#endif // NIC_FE2827317FB9AC5D_NIC