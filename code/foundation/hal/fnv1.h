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
#ifndef NIC_19CAF98AEE6E1022_NIC
#define NIC_19CAF98AEE6E1022_NIC

#include "../io/stream/stream.h"

namespace nebula { namespace foundation { namespace hal {
/** @ingroup Foundation
  * @{ 
  * */
//------------------------------------------------------------------------------
namespace fnv1_detail {
//------------------------------------------------------------------------------
template <class T, size_t = sizeof(T) * n_char_bit> struct params;

template <class T> struct params<T, 32> {
    constexpr static T prime() noexcept {
        return 16777619UL; 
    }
    constexpr static T base() noexcept {
        return 2166136261UL; 
    }
};

template <class T> struct params<T, 64> {
    constexpr static T prime() noexcept {
        return 1099511628211ULL;
    }
    constexpr static T base() noexcept {
        return 14695981039346656037ULL;
    }
};

} // fnv1_detail

//------------------------------------------------------------------------------
/** @see http://www.isthe.com/chongo/tech/comp/fnv/index.html#FNV-1 */
template <
    class UnsignedType = unsigned,
    UnsignedType Prime = fnv1_detail::params<UnsignedType>::prime(),
    UnsignedType Base = fnv1_detail::params<UnsignedType>::base()>
class fnv1 final : io::stream_base
{
    using ui_t = UnsignedType;
    
public:
    using stream_size = io::streamsize;
    using stream_offset = io::streamoff;
    using stream_position = io::streampos;
    using stream_category = tag<io::out_tag>;
    
    using result_type = ui_t;
    
    inline fnv1() noexcept
    : state(Base)
    {}
    inline fnv1(const ui_t seed) noexcept
    : state(seed)
    {}
    
    fnv1(fnv1 &) = default;
    fnv1(const fnv1 &) = default;
    fnv1(fnv1 &&) = default;
    
    fnv1 &operator = (fnv1 &) = default;
    fnv1 &operator = (const fnv1 &) = default;
    fnv1 &operator = (fnv1 &&) = default;
    
    inline void write(const char *x, const size_t n)
    {
        const unsigned char *i = static_cast<const unsigned char*>(
            static_cast<const void*>(x));
        const unsigned char *e = i + n;
        
        while(i < e)
        {
            state *= Prime;
            state ^= ui_t(*i++);
        }
    }
    inline void put(char c)
    {
        state *= Prime;
        state ^= ui_t(c);
    }
    inline ui_t result() {
        return state;
    }
    
    inline void reset() noexcept { state = Base; }
    inline void reset(const ui_t x) noexcept { state = x; }
    
private:   
    ui_t state;
};

/** @} */

}}} // namespaces

#endif // NIC_19CAF98AEE6E1022_NIC

