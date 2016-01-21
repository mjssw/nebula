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
#ifndef NIC_233986935755BAE1_NIC
#define NIC_233986935755BAE1_NIC

#include "carray.h"
#include "char_traits.h"
#include "minmax.h"
#include "enable_if.h"
#include "fwd.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** 
 * */
template <class T, 
class CTraits = char_traits<typename remove_const<T>::type>>
struct basic_cstring : public carray<T>
{
    using char_type = typename remove_const<T>::type;    
    using traits_type = CTraits;
    
    basic_cstring() = default;
    basic_cstring(basic_cstring &) = default;
    basic_cstring(const basic_cstring &) = default;
    basic_cstring(basic_cstring &&) = default;
    
    template <class Cond = typename is_const<T>::type,
        typename enable_if<Cond>::type* = nullptr>
    inline basic_cstring(basic_cstring<char_type, traits_type> s) noexcept
    : basic_cstring(s.data(), s.size())
    {}
    
    inline basic_cstring(T *x)
    : carray<T>(x, traits_type::length(x))
    {}
    inline basic_cstring(T *a, T *b)
    : carray<T>(a, b)
    {}
    
    template <class Alloc_>
    inline basic_cstring(
        basic_string<char_type, traits_type, Alloc_> &s) noexcept
    : carray<T>(s.data(), s.size())
    {}
    template <class Alloc_>
    inline basic_cstring(
        const basic_string<char_type, traits_type, Alloc_> &s) noexcept
    : carray<T>(s.data(), s.data()+s.size())
    {}
    
    inline basic_cstring &assign(
        T *first_, T *last_) noexcept
    {
        carray<T>::assign(first_, last_);
        return *this;
    }
    inline basic_cstring &assign(
        T *first_, const size_t n) noexcept {
        carray<T>::assign(first_, n);
        return *this;
    }
    inline basic_cstring &assign(
        T *first_) noexcept 
    {
        carray<T>::assign(first_, traits_type::length(first_));
        return *this;
    }
    template <class Alloc_>
    inline basic_cstring &assign(
        const basic_string<char_type, traits_type, Alloc_> &s) noexcept 
    {
        return this->assign(s.data(), s.size());
    }
    
    inline basic_cstring &operator = (const basic_cstring &) = default;
    inline basic_cstring &operator = (basic_cstring &&) = default;
    
    inline basic_cstring &operator = (T *s) noexcept {
        return this->assign(s);
    }
    template <class Alloc_>
    inline basic_cstring &operator = (
        basic_string<char_type, traits_type, Alloc_> &s) noexcept 
    {
        return this->assign(s);
    }
    template <class Alloc_>
    inline basic_cstring &operator = (
        const basic_string<char_type, traits_type, Alloc_> &s) noexcept 
    {
        return this->assign(s);
    }
    
    inline int compare(const char *str) const noexcept
    {
        return compare(basic_cstring(str, str + strlen(str)));
    }
    inline int compare(const basic_cstring other) const noexcept
    {
        const auto m = foundation::min(this->size(), other.size());
        const int r = traits_type::compare(this->data(), other.data(), m);
        if(r == 0) {
            if(this->size() == other.size())
                return 0;
            else if(this->size() < other.size())
                return -1;
            else
                return 1;
        }
        return r;
    }
    template <class Alloc_>
    inline int compare(
        const basic_string<char_type, traits_type, Alloc_> &other
    ) const noexcept
    {
        const auto m = foundation::min(this->size(), other.size());
        const int r = traits_type::compare(this->data(), other.data(), m);
        if(r == 0) {
            if(this->size() == other.size())
                return 0;
            else if(this->size() < other.size())
                return -1;
            else
                return 1;
        }
        return r;
    }
};

//------------------------------------------------------------------------------
using cstring = basic_cstring<char>;
using const_cstring = basic_cstring<const char>;

//==============================================================================
template <class C, class CTraits>
inline bool operator == (
    const basic_cstring<C, CTraits> lhs, 
    const basic_cstring<C, CTraits> rhs) noexcept
{
    if(lhs.size() != rhs.size())
        return false;
    return CTraits::compare(lhs.data(), rhs.data(), lhs.size()) == 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits>
inline bool operator != (
    const basic_cstring<C, CTraits> lhs, 
    const basic_cstring<C, CTraits> rhs) noexcept
{
    return !(lhs == rhs);
}
//------------------------------------------------------------------------------
template <class C, class CTraits>
inline bool operator < (
    const basic_cstring<C, CTraits> lhs, 
    const basic_cstring<C, CTraits> rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits>
inline bool operator <= (
    const basic_cstring<C, CTraits> lhs, 
    const basic_cstring<C, CTraits> rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits>
inline bool operator > (
    const basic_cstring<C, CTraits> lhs, 
    const basic_cstring<C, CTraits> rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits>
inline bool operator >= (
    const basic_cstring<C, CTraits> lhs,
    const basic_cstring<C, CTraits> rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

//==============================================================================
template <class C, class D, class CTraits, class Alloc>
inline bool operator == (
    const basic_string<C, CTraits, Alloc> &lhs, 
    const basic_cstring<D, CTraits> rhs) noexcept
{
    if(lhs.size() != rhs.size())
        return false;
    return CTraits::compare(lhs.data(), rhs.data(), lhs.size()) == 0;
}
//------------------------------------------------------------------------------
template <class C, class D, class CTraits, class Alloc>
inline bool operator != (
    const basic_string<C, CTraits, Alloc> &lhs, 
    const basic_cstring<D, CTraits> rhs) noexcept
{
    return !(lhs == rhs);
}
//------------------------------------------------------------------------------
template <class C, class D, class CTraits, class Alloc>
inline bool operator < (
    const basic_string<C, CTraits, Alloc> &lhs, 
    const basic_cstring<D, CTraits> rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}
//------------------------------------------------------------------------------
template <class C, class D, class CTraits, class Alloc>
inline bool operator <= (
    const basic_string<C, CTraits, Alloc> &lhs, 
    const basic_cstring<D, CTraits> rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}
//------------------------------------------------------------------------------
template <class C, class D, class CTraits, class Alloc>
inline bool operator > (
    const basic_string<C, CTraits, Alloc> &lhs, 
    const basic_cstring<D, CTraits> rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}
//------------------------------------------------------------------------------
template <class C, class D, class CTraits, class Alloc>
inline bool operator >= (
    const basic_string<C, CTraits, Alloc> &lhs,
    const basic_cstring<D, CTraits> rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

//==============================================================================
template <class C, class D, class CTraits, class Alloc>
inline bool operator == (
    const basic_cstring<C, CTraits> lhs, 
    const basic_string<D, CTraits, Alloc> &rhs) noexcept
{
    if(lhs.size() != rhs.size())
        return false;
    return CTraits::compare(lhs.data(), rhs.data(), lhs.size()) == 0;
}
//------------------------------------------------------------------------------
template <class C, class D, class CTraits, class Alloc>
inline bool operator != (
    const basic_cstring<C, CTraits> lhs, 
    const basic_string<D, CTraits, Alloc> &rhs) noexcept
{
    return !(lhs == rhs);
}
//------------------------------------------------------------------------------
template <class C, class D, class CTraits, class Alloc>
inline bool operator < (
    const basic_cstring<C, CTraits> lhs, 
    const basic_string<D, CTraits, Alloc> &rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}
//------------------------------------------------------------------------------
template <class C, class D, class CTraits, class Alloc>
inline bool operator <= (
    const basic_cstring<C, CTraits> lhs, 
    const basic_string<D, CTraits, Alloc> &rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}
//------------------------------------------------------------------------------
template <class C, class D, class CTraits, class Alloc>
inline bool operator > (
    const basic_cstring<C, CTraits> lhs, 
    const basic_string<D, CTraits, Alloc> &rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}
//------------------------------------------------------------------------------
template <class C, class D, class CTraits, class Alloc>
inline bool operator >= (
    const basic_cstring<C, CTraits> lhs,
    const basic_string<D, CTraits, Alloc> &rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

//==============================================================================
template <class C, class CTraits, class C2>
inline bool operator == (
    const basic_cstring<C, CTraits> &lhs, 
    const C2 *rhs) noexcept
{
    if(lhs.size() != CTraits::length(rhs))
        return false;
    return CTraits::compare(lhs.data(), rhs, lhs.size()) == 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class C2>
inline bool operator != (
    const basic_cstring<C, CTraits> &lhs, 
    const C2 *rhs) noexcept
{
    return !(lhs == rhs);
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class C2>
inline bool operator < (
    const basic_cstring<C, CTraits> &lhs, 
    const C2 *rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class C2>
inline bool operator <= (
    const basic_cstring<C, CTraits> &lhs, 
    const C2 *rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class C2>
inline bool operator > (
    const basic_cstring<C, CTraits> &lhs, 
    const C2 *rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}
//------------------------------------------------------------------------------
template <class C, class CTraits, class C2>
inline bool operator >= (
    const basic_cstring<C, CTraits> &lhs,
    const C2 *rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

//==============================================================================
template <class C, class CTraits>
struct hash<basic_cstring<C, CTraits> >
    : public hash_detail::string_hash<C>
{};

/** @} */

}} // namespaces

#endif // NIC_233986935755BAE1_NIC
