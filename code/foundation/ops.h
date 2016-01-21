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
#ifndef NIC_6A1084102EFC8EA9_NIC
#define NIC_6A1084102EFC8EA9_NIC

#include "defs.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{ 
 * */
//------------------------------------------------------------------------------
template <class T = void>
struct less 
{
    template <class RHS>
    inline constexpr bool operator() (const T &lhs, const RHS &rhs) const {
        return lhs < rhs;
    }
};

template <>
struct less<void> 
{
    template <class LHS, class RHS>
    inline constexpr bool operator() (const LHS &lhs, const RHS &rhs) const {
        return less<LHS>()(lhs, rhs);
    }
};
//------------------------------------------------------------------------------
template <class T = void>
struct less_equal
{
    template <class RHS>
    inline constexpr bool operator() (const T &lhs, const RHS &rhs) const {
        return lhs <= rhs;
    }
};

template <>
struct less_equal<void> 
{
    template <class LHS, class RHS>
    inline constexpr bool operator() (const LHS &lhs, const RHS &rhs) const {
        return less_equal<LHS>()(lhs, rhs);
    }
};
//------------------------------------------------------------------------------
template <class T = void>
struct greater
{
    template <class RHS>
    inline constexpr bool operator() (const T &lhs, const RHS &rhs) const {
        return lhs > rhs;
    }
};

template <>
struct greater<void> 
{
    template <class LHS, class RHS>
    inline constexpr bool operator() (const LHS &lhs, const RHS &rhs) const {
        return greater<LHS>()(lhs, rhs);
    }
};
//------------------------------------------------------------------------------
template <class T = void>
struct greater_equal
{
    template <class RHS>
    inline constexpr bool operator() (const T &lhs, const RHS &rhs) const {
        return lhs >= rhs;
    }
};

template <>
struct greater_equal<void> 
{
    template <class LHS, class RHS>
    inline constexpr bool operator() (const LHS &lhs, const RHS &rhs) const {
        return greater_equal<LHS>()(lhs, rhs);
    }
};
//------------------------------------------------------------------------------
template <class T = void>
struct equal_to
{
    template <class RHS>
    inline constexpr bool operator() (const T &lhs, const RHS &rhs) const {
        return lhs == rhs;
    }
};

template <>
struct equal_to<void> 
{
    template <class LHS, class RHS>
    inline constexpr bool operator() (const LHS &lhs, const RHS &rhs) const {
        return equal_to<LHS>()(lhs, rhs);
    }
};
//------------------------------------------------------------------------------
template <class T = void>
struct not_equal_to
{
    template <class RHS>
    inline constexpr bool operator() (const T &lhs, const RHS &rhs) const {
        return lhs != rhs;
    }
};

template <>
struct not_equal_to<void> 
{
    template <class LHS, class RHS>
    inline constexpr bool operator() (const LHS &lhs, const RHS &rhs) const {
        return not_equal_to<LHS>()(lhs, rhs);
    }
};

/** @} */

}} // namespaces

#endif // NIC_6A1084102EFC8EA9_NIC
