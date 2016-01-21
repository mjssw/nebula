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
#ifndef NIC_766A6E9DCAAABB5F_NIC
#define NIC_766A6E9DCAAABB5F_NIC

#include "str.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** */
template <class T>
struct char_traits
{
    using char_type = T;
    
    /** @attention Must not throw.
     * */
    inline static size_t length(const char_type *s) noexcept
    {
        const char_type* i = s;
        for( ; *i; ++i)
            ;
        return i - s;
    }
    
    /** @attention Must not throw.
     * */
    inline static int compare(
        const char_type *s0,
        const char_type *s1,
        const size_t n) noexcept
    {
        for(size_t i = 0; i < n; ++i)
        {
            if(s0[i] > s1[i]) return 1;
            if(s0[i] < s1[i]) return -1;
        }
        return 0;
    }
};

//------------------------------------------------------------------------------
template <>
struct char_traits<char>
{
    using char_type = char;
    
    inline static size_t length(const char_type *s) noexcept
    {
        return strlen(s);
    }
    
    inline static int compare(
        const char_type *s0, 
        const char_type *s1, 
        const size_t n) noexcept
    {
        return strncmp(s0, s1, n);
    }
};

/** @} */

}} // namespaces

#endif // NIC_766A6E9DCAAABB5F_NIC
