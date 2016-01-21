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
#ifndef NIC_ADE12508F93ADAC3_NIC
#define NIC_ADE12508F93ADAC3_NIC

#include "../config.h"
#include "../vector.h"
#include "../cstring.h"
#include "../tuple.h"
#include "../range.h"

namespace nebula { namespace foundation { namespace regex {
//------------------------------------------------------------------------------
/** Treat this as an opaque type - i.e. use the provided free functions to 
 * access stored information.
 * */
template <class Allocator = memory::allocator<tuple<bool, const_cstring>>>
class match_result
{
public:
    using sub_match_type = tuple<bool, const_cstring>;
    using allocator_type = typename memory::rebind<
        Allocator,
        sub_match_type>::type;
        
private:
    using container_type = vector<sub_match_type, allocator_type>;
    
public:        
    using sub_match_range_type = range::iterator_range<
        typename range::range_iterator<const container_type>::type>;
        
    inline match_result()
    {}
    template <class Alloc>
    inline match_result(Alloc &&alc)
    : v(foundation::forward<Alloc>(alc))
    {}
    match_result(match_result &) = default;
    match_result(const match_result &) = default;
    match_result(match_result &&) = default;
    
    match_result &operator = (const match_result &) = default;
    match_result &operator = (match_result &&) = default;
    
    inline void swap(match_result &other) noexcept
    {
        foundation::swap(v, other.v);
    }
    
    inline void suffix(const_cstring x) noexcept {
        sfx = x;
    }
    inline void prefix(const_cstring x) noexcept {
        pfx = x;
    }
    inline void match(const_cstring x) noexcept {
        m = x;
    }
    inline void add_sub_match(bool f, const_cstring x) noexcept {
        v.push_back(tuple<bool, const_cstring>(f,x));
    }
    
    inline const_cstring suffix() const noexcept {
        return sfx;
    }
    inline const_cstring prefix() const noexcept {
        return pfx;
    }
    
    inline const_cstring match() const noexcept {
        return m;
    }
    
    inline sub_match_range_type sub_matches() const noexcept {
        return sub_match_range_type(
            range::begin(v),
            range::end(v));
    }
    
private:
    const_cstring m;
    container_type v;
    const_cstring sfx;
    const_cstring pfx;
};

//------------------------------------------------------------------------------
template <class T>
struct sub_match_range {
    using type = typename T::sub_match_range_type;
};

//------------------------------------------------------------------------------
template <class T>
inline const_cstring suffix(const T &x) noexcept {
    return x.suffix();
}
//------------------------------------------------------------------------------
template <class T>
inline const_cstring prefix(const T &x) noexcept {
    return x.prefix();
}

//------------------------------------------------------------------------------
template <class T>
inline bool test(const T &x) noexcept {
    return !x.match().empty();
}
//------------------------------------------------------------------------------
template <class T>
inline const_cstring match(const T &x) noexcept {
    return x.match();
}

//------------------------------------------------------------------------------
template <class T>
inline typename sub_match_range<T>::type sub_matches(const T &x) noexcept {
    return x.sub_matches();
}
//------------------------------------------------------------------------------
inline bool test(tuple<bool, const_cstring> x) noexcept {
    return foundation::get<0>(x);
}
//------------------------------------------------------------------------------
inline const_cstring match(tuple<bool, const_cstring> x) noexcept {
    return foundation::get<1>(x);
}

}}} // namespaces

#endif // NIC_ADE12508F93ADAC3_NIC