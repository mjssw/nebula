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
#ifndef NIC_7F2F3C46B8175184_NIC
#define NIC_7F2F3C46B8175184_NIC

#include "traits.h"
#include "../math.h"

namespace nebula { namespace foundation { namespace random {
/** @ingroup Foundation
  * @{ 
  * */
//------------------------------------------------------------------------------
template <class T>
class min_impl
{
    using yes = char;
    using no = char[2];
    template <class X>
    static auto has_mem_(void*) 
        -> decltype(std::declval<X>().min(), yes{});
    template <class X>
    static no &has_mem_(...);
    template <class X>
    inline constexpr static bool has_mem() noexcept {
        return sizeof(has_mem_<X>(0)) == sizeof(yes);
    }
    
    using result_type = decltype(declval<T>()());
    
public:    
    template <class X = T,
        typename enable_if_c<has_mem<X>()>::type* = nullptr>
    inline static auto apply(const T &x) noexcept {
        return x.min();
    }
    
    template <class X = T,
        typename disable_if_c<has_mem<X>()>::type* = nullptr>
    inline static auto apply(const T &x) noexcept {
        return math::minimum<result_type>();
    }
};

//------------------------------------------------------------------------------
template <class T>
inline auto min(const T &x) noexcept {
    return min_impl<T>::apply(x);
}

//------------------------------------------------------------------------------
template <class T>
class max_impl
{
    using yes = char;
    using no = char[2];
    template <class X>
    static auto has_mem_(void*) 
        -> decltype(std::declval<X>().max(), yes{});
    template <class X>
    static no &has_mem_(...);
    template <class X>
    inline constexpr static bool has_mem() noexcept {
        return sizeof(has_mem_<X>(0)) == sizeof(yes);
    }
    
    using result_type = decltype(declval<T>()());
    
public:
    template <class X = T,
        typename enable_if_c<has_mem<X>()>::type* = nullptr>
    inline static auto apply(const T &x) noexcept {
        return x.max();
    }
    
    template <class X = T,
        typename disable_if_c<has_mem<X>()>::type* = nullptr>
    inline static auto apply(const T &x) noexcept {
        return math::maximum<result_type>();
    }
};

//------------------------------------------------------------------------------
template <class T>
inline auto max(const T &x) noexcept {
    return max_impl<T>::apply(x);
}

/** @} */

}}} // namespaces

#endif // NIC_7F2F3C46B8175184_NIC