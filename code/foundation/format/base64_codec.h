/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2016 lis (lis@tutanota.com)
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
#ifndef NIC_3E17BD6870DF0271_NIC
#define NIC_3E17BD6870DF0271_NIC

#include "fwrite.h"
#include "../io.h"
#include "../exception.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
namespace base64_detail {
//------------------------------------------------------------------------------
struct base64_digit_codec
{
    using size = meta::size_t_<64>;
    
    inline static char encode(unsigned x, nothrow_tag) {
        static constexpr const char *digits =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789"
            "+/";
        if(x >= size::value)
            return 0;
        return digits[x];
    }
    inline static char encode(unsigned x) {
        const char res = encode(x, nothrow_tag());
        if(0 == res)
            n_throw(out_of_range);
        return res;
    }
    inline static unsigned decode(char x, nothrow_tag) noexcept {
        switch(x)
        {
        case '=':
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 6;
        case 'H': return 7;
        case 'I': return 8;
        case 'J': return 9;
        case 'K': return 10;
        case 'L': return 11;
        case 'M': return 12;
        case 'N': return 13;
        case 'O': return 14;
        case 'P': return 15;
        case 'Q': return 16;
        case 'R': return 17;
        case 'S': return 18;
        case 'T': return 19;
        case 'U': return 20;
        case 'V': return 21;
        case 'W': return 22;
        case 'X': return 23;
        case 'Y': return 24;
        case 'Z': return 25;
        case 'a': return 26;
        case 'b': return 27;
        case 'c': return 28;
        case 'd': return 29;
        case 'e': return 30;
        case 'f': return 31;
        case 'g': return 32;
        case 'h': return 33;
        case 'i': return 34;
        case 'j': return 35;
        case 'k': return 36;
        case 'l': return 37;
        case 'm': return 38;
        case 'n': return 39;
        case 'o': return 40;
        case 'p': return 41;
        case 'q': return 42;
        case 'r': return 43;
        case 's': return 44;
        case 't': return 45;
        case 'u': return 46;
        case 'v': return 47;
        case 'w': return 48;
        case 'x': return 49;
        case 'y': return 50;
        case 'z': return 51;
        case '0': return 52;
        case '1': return 53;
        case '2': return 54;
        case '3': return 55;
        case '4': return 56;
        case '5': return 57;
        case '6': return 58;
        case '7': return 59;
        case '8': return 60;
        case '9': return 61;
        case '+': return 62;
        case '/': return 63;
        default:
            return -1;
        }
    }
    inline static unsigned decode(char x) {
        unsigned res = decode(x, nothrow_tag());
        if(res == -1)
            n_throw(out_of_range);
        return res;
    }
};

//------------------------------------------------------------------------------
template <class Codec, class Sink>
inline void encode(const bool padding,
    const char *buf_, const size_t n, Sink &&out)
{
    n_static_assert(n_char_bit == 8, "");
    
    if(0 == n)
        return;
    if(!buf_)
        n_throw(logic_error);
    
    const unsigned char *buf = static_cast<const unsigned char *>(
        static_cast<const void *>(buf_));
    
    char chnk[4];
    
    size_t i = 0;
    for( ; i+2 < n; i += 3)
    {
        // 12345678 12345678 12345678
        // ^ a   ^ b    ^ c    ^ d
        
        unsigned x = buf[i] >> 2;
        chnk[0] = Codec::encode(x);
        
        x = (buf[i] & 0b11) << 4;
        x |= buf[i+1] >> 4;
        chnk[1] = Codec::encode(x);
        
        x = (buf[i+1] & 0b1111) << 2;
        x |= buf[i+2] >> 6;
        chnk[2] = Codec::encode(x);
        
        x = buf[i+2] & 0b111111;
        chnk[3] = Codec::encode(x);
        
        io::write(out, chnk, 4);
    }
    
    switch(n-i)
    {
    case 2:
        {
            unsigned x = buf[i] >> 2;
            chnk[0] = Codec::encode(x);
            
            x = (buf[i] & 0b11) << 4;
            x |= buf[i+1] >> 4;
            chnk[1] = Codec::encode(x);
            
            x = (buf[i+1] & 0b1111) << 2;
            chnk[2] = Codec::encode(x);
            
            io::write(out, chnk, 3);
            
            if(padding)
                io::put(out, '=');
        }
        break;
    case 1:
        {
            unsigned x = buf[i] >> 2;
            chnk[0] = Codec::encode(x);
            
            x = (buf[i] & 0b11) << 4;
            chnk[1] = Codec::encode(x);
            
            io::write(out, chnk, 2);
            
            if(padding)
                io::write(out, "==", 2);
        }
        break;
    default: break;
    }
}
//------------------------------------------------------------------------------
template <class Sink>
class wrapping_sink : public io::stream_base
{
public:
    using stream_size = io::_stream_size<Sink>;
    using stream_offset = io::_stream_offset<Sink>;
    using stream_position = io::_stream_position<Sink>;
    using stream_category = tag<io::out_tag>;
    
    inline wrapping_sink(Sink &s_, const size_t cols) noexcept
    : s(s_), ncols(cols), col(0)
    {
        if(0 == ncols)
            n_throw(logic_error);
    }
    
    inline void write(const char *buf, const size_t n)
    {
        if(col + n <= ncols)
        {
            io::write(s, buf, n);
            col += n;
        }
        else
        {
            size_t m = ncols-col;
            
            if(m)
                io::write(s, buf, m);
            
            fmt::fwrite(s, fmt::endl);
            col = 0;
            
            for( ; m + ncols < n; m += ncols)
            {
                io::write(s, buf + m, ncols);
                fmt::fwrite(s, fmt::endl);
            }
            
            if(m < n)
            {
                col = n - m;
                io::write(s, buf + m, col);
            }
        }
    }
    inline void put(const char c)
    {
        if(col == ncols)
        {
            fmt::fwrite(s, fmt::endl);
            col = 0;
        }
        
        io::put(s, c);
        ++col;
    }

private:
    Sink &s;
    const size_t ncols;
    size_t col;
};

//------------------------------------------------------------------------------
template <class Codec, class Sink>
inline bool decode(const char *buf, const size_t n, Sink &&s)
{
    n_static_assert(Codec::size::value == 64, "");
    n_static_assert(n_char_bit == 8, "");
    
    uint_least32_t q[4];
    size_t k = 0;
    size_t i = 0;
    
    while(true)
    {
        if(i == n)
            break;
        
        uint_least32_t u = Codec::decode(buf[i++], nothrow_tag());
        while(unsigned(-1) == u)
        {
            if(i == n)
                return false;
            
            u = Codec::decode(buf[i++], nothrow_tag());
        }
        
        q[k++] = u;
        
        if(k == 4)
        {
            k = 0;
            uint_least32_t x = q[0] << 18 | (q[1] << 12) | (q[2] << 6) | q[3];
            char *y = static_cast<char *>(static_cast<void *>(&x));
            swap(y[0], y[2]);
            io::write(s, y, 3);
        }
    }
    
    switch(k)
    {
    case 1: return false;
    case 2:
    case 3:
        {
            for( ; k < 4; ++k)
                q[k] = 0;
            uint_least32_t x = q[0] << 18 | (q[1] << 12) | (q[2] << 6) | q[3];
            char *y = static_cast<char *>(static_cast<void *>(&x));
            swap(y[0], y[2]);
            io::write(s, y, 3);
        }
        break;
    default: break;
    }
    
    return true;
}

} // base64_detail

//------------------------------------------------------------------------------
template <class Sink>
inline void base64_encode(const char *buf, const size_t n, Sink &&snk)
{
    base64_detail::encode<base64_detail::base64_digit_codec>(
        N_FORMAT_DEFAULT_BASE64_PADDING,
        buf, n, snk);
}
//------------------------------------------------------------------------------
template <class Sink>
inline void base64_encode(const bool padding, const size_t ncols,
    const char *buf, const size_t n, Sink &&snk)
{
    if(ncols == 0)
        base64_detail::encode<base64_detail::base64_digit_codec>(
            padding, buf, n, snk);
    else
        base64_detail::encode<base64_detail::base64_digit_codec>(
            padding, buf, n,
            base64_detail::wrapping_sink<ctraits::_value<Sink>>(snk, ncols));
}

//------------------------------------------------------------------------------
template <class Sink>
inline bool base64_decode(const char *buf, const size_t n, Sink &&snk)
{
    return base64_detail::decode<base64_detail::base64_digit_codec>(
        buf, n, snk);
}
//------------------------------------------------------------------------------
template <class Sink>
inline bool base64_decode(const char *beg, const char *end, Sink &&snk)
{
    return base64_detail::decode<base64_detail::base64_digit_codec>(
        beg, end-beg, snk);
}

/** @} */

}}} // namespaces

#endif // NIC_3E17BD6870DF0271_NIC
