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
#ifndef NIC_4689076FD624990E_NIC
#define NIC_4689076FD624990E_NIC

#include "exception.h"
#include "../range.h"
#include "../assert.h"
#include "../call_traits.h"

namespace nebula { namespace foundation { namespace utf {
/** @ingroup Foundation
 * @{
 * */
namespace utf_detail {
//------------------------------------------------------------------------------
inline bool is_trailing(const char x) noexcept {
    return (x & 0b11000000) == 0b10000000;
}
//------------------------------------------------------------------------------
inline bool is_leading(const char x) noexcept {
    return !is_trailing(x);
}
//------------------------------------------------------------------------------
inline size_t sequence_length(const char x) noexcept 
{    
    switch((x >> 3) & 0b11111)
    {
        case 0b11110:
            return 4;
            
        case 0b11100:
        case 0b11101:
            return 3;
            
        case 0b11000:
        case 0b11001:
        case 0b11010:
        case 0b11011:
            return 2;
            
        case 0b10000:
        case 0b10001:
        case 0b10010:
        case 0b10100:
        case 0b10011:
        case 0b10101:
        case 0b10110:
        case 0b10111:
        case 0b11111:
            return 0;
            
        default: 
            return 1;
    }
}
//------------------------------------------------------------------------------
inline bool u16_is_trailing(const char16_t c) noexcept
{
    return (c >= 0xdc00) && (c <= 0xdfff);
}
//------------------------------------------------------------------------------
inline bool u16_is_leading(const char16_t c) noexcept
{
    return !is_trailing(c);
}
//------------------------------------------------------------------------------
inline size_t u16_sequence_length(const char16_t c) noexcept {
    if( (c >= 0xd800) && (c <= 0xdbff) )
        return 2;
    else if( (c >= 0xdc00) && (c <= 0xdfff) )
        return 0; // trailing
    return 1;
}
//------------------------------------------------------------------------------
inline size_t u32_to_u8_codeunit_count(const char32_t x) noexcept
{
    if(x < 0b10000000)
        return 1;
    else if(x < 0b100000000000)
        return 2;
    else if(x < 0b10000000000000000)
        return 3;
    else if(x < 0b1000000000000000000000)
        return 4;
    else
        return 0;
}
//------------------------------------------------------------------------------
template <class Sink>
inline void u8_to_u32(const char *i, const size_t n, Sink &&sink)
{
    char32_t res;
    
    switch(n)
    {
    case 1: 
        res = i[0];
        break;
    case 2:
        res = (i[0] & 0b11111) << 6;
        res |= i[1] & 0b111111;
        break;
    case 3:
        res = (i[0] & 0b1111) << 12;
        res |= (i[1] & 0b111111) << 6;
        res |= i[2] & 0b111111;
        break;
    case 4:
        res = (i[0] & 0b1111) << 18;
        res |= (i[1] & 0b111111) << 12;
        res |= (i[2] & 0b111111) << 6;
        res |= i[3] & 0b111111;
        break;
        
    default:
        n_throw(logic_error);
        return;
    }
    
    sink(res);
}
//------------------------------------------------------------------------------
template <class Sink>
inline void u32_to_u8(const char32_t c, const size_t n, Sink &&sink)
{
    switch(n)
    {
    case 1: 
        sink(c);
        break;
    case 2:
        sink(((c >> 6) & 0b11111) | 0b11000000);
        sink((c & 0b111111) | 0b10000000);
        break;
    case 3:
        sink(((c >> 12) & 0b1111) | 0b11100000);
        sink(((c >> 6) & 0b111111) | 0b10000000);
        sink((c & 0b111111) | 0b10000000);
        break;
    case 4:
        sink(((c >> 18) & 0b111) | 0b11110000);
        sink(((c >> 12) & 0b111111) | 0b10000000);
        sink(((c >> 6) & 0b111111) | 0b10000000);
        sink((c & 0b111111) | 0b10000000);
        break;
    
    default:
        n_throw(logic_error);
    }
}
//------------------------------------------------------------------------------
template <class Sink>
inline void u32_to_u16(const char32_t c, Sink &&sink)
{      
    if(c < 0x10000)
        sink(c);
    else {
        n_assert(c < 0x10ffff);
        sink((c >> 10) + 0xd7c0);
        sink((c & 0x3ff) + 0xdc00);
    }
}
//------------------------------------------------------------------------------
template <class Sink>
inline void u8_to_u16(const char *i, const size_t n, Sink &&sink)
{
    char32_t c32 = 0;
    u8_to_u32(i, n, [&] (char32_t x) { c32=x; });
    u32_to_u16(c32, sink);
}
//------------------------------------------------------------------------------
inline char32_t u16_to_u32(const char16_t *i, const size_t n)
{
    if(n == 2)
        return (i[0] << 10) + i[1] - 0x35fdc00;
    else
        return i[0];
}
//------------------------------------------------------------------------------
template <class Sink>
inline void u16_to_u8(const char16_t *i, const size_t n, Sink &&sink)
{
    char32_t c32 = u16_to_u32(i, n);
    u32_to_u8(c32, u32_to_u8_codeunit_count(c32), sink);
}

} // utf_detail

//------------------------------------------------------------------------------
template <class Range>
struct widen_impl
{
    inline static char32_t apply(const Range &r)
    {
        auto i = range::begin(r);
        const auto last = range::end(r);
        char32_t c = 0;
        const range::_range_difference<Range> n
            = utf_detail::sequence_length(*i);
        if(n == 0)
            n_throw(utf_error);
        if(n > iterator::distance(i, last))
            n_throw(utf_error, out_of_range);
        utf_detail::u8_to_u32(
            i, n, [&] (const char32_t x) { c=x; });
        return c;
    }
};
//------------------------------------------------------------------------------
/** @return The first codepoint in r in utf-32 encoding.
 * */
template <class Range>
inline char32_t widen(const Range &r)
{
    return widen_impl<Range>::apply(r);
}

//------------------------------------------------------------------------------
template <class Iter>
struct unsafe_widen_impl
{
    inline static char32_t apply(Iter i)
    {
        char32_t c = 0;
        const size_t n = utf_detail::sequence_length(*i);
        utf_detail::u8_to_u32(
            i, n, [&] (const char32_t x) { c=x; });
        return c;
    }
};
//------------------------------------------------------------------------------
/** @warning Does not perform any safety checks.
 *  @return The first codepoint in r in utf-32 encoding.
 * */
template <class Iter>
inline char32_t unsafe_widen(Iter i)
{
    return unsafe_widen_impl<Iter>::apply(i);
}

//------------------------------------------------------------------------------
/** Write the codepoint c as utf-8 into sink.
 * */
template <class Sink>
inline void narrow(const char32_t c, Sink &&sink)
{
    utf_detail::u32_to_u8(
        c,
        utf_detail::u32_to_u8_codeunit_count(c),
        sink);
}
//------------------------------------------------------------------------------
/** @return the codepoint c as a utf-8 string, which is valid until this
 *  function is called again (thread local storage).
 * */
inline const_cstring narrow(const char32_t c)
{
    thread_local static char buf[5] = {};
    char *i = buf;
    utf::narrow(c, [&] (const char x) noexcept { *i++ = x; });
    return const_cstring(buf, i);
}

/** @} */

}}} // namespaces

#endif // NIC_4689076FD624990E_NIC

