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
#ifndef NIC_D305D5041316DFC9_NIC
#define NIC_D305D5041316DFC9_NIC

#include "../../io.h"
#include "../fwrite.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
namespace base64_detail {
//------------------------------------------------------------------------------
static constexpr const char *b64_ascii =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "+/";
//------------------------------------------------------------------------------
template <class Sink>
inline void encode(const bool padding, const char *ascii,
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
        chnk[0] = ascii[x];
        
        x = (buf[i] & 0b11) << 4;
        x |= buf[i+1] >> 4;
        chnk[1] = ascii[x];
        
        x = (buf[i+1] & 0b1111) << 2;
        x |= buf[i+2] >> 6;
        chnk[2] = ascii[x];
        
        x = buf[i+2] & 0b111111;
        chnk[3] = ascii[x];
        
        io::write(out, chnk, 4);
    }
    
    switch(n-i)
    {
    case 2:
        {
            unsigned x = buf[i] >> 2;
            chnk[0] = ascii[x];
            
            x = (buf[i] & 0b11) << 4;
            x |= buf[i+1] >> 4;
            chnk[1] = ascii[x];
            
            x = (buf[i+1] & 0b1111) << 2;
            chnk[2] = ascii[x];
            
            io::write(out, chnk, 3);
            
            if(padding)
                io::put(out, '=');
        }
        break;
    case 1:
        {
            unsigned x = buf[i] >> 2;
            chnk[0] = ascii[x];
            
            x = (buf[i] & 0b11) << 4;
            chnk[1] = ascii[x];
            
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

} // base64_detail

//------------------------------------------------------------------------------
/** Simple base64 encoder.
 *
 *  This does not wrap lines and it outputs padding characters.
 *
 *  @see base64_ex
 * */
class base64
{
public:
    /** Constructor
     *
     *  @param buf_ The input data which must be null-terminated.
     * */
    inline base64(const char *buf_) noexcept
    : buf(buf_), n(strlen(buf_))
    {}
    /** Constructor
     *
     *  @param buf_ The input data.
     *  @param n_ Size of the input data in bytes.
     * */
    inline base64(const char *buf_, const size_t n_) noexcept
    : buf(buf_), n(n_)
    {}
    /** Constructor
     *
     *  @param beg The start of the input data.
     *  @param end The end of the input data.
     * */
    inline base64(const char *beg, const char *end) noexcept
    : buf(beg), n(end-beg)
    {}
    
    template <class Sink>
    inline void operator () (Sink &snk, fout_tag) const
    {
        base64_detail::encode(N_FORMAT_DEFAULT_BASE64_PADDING,
            base64_detail::b64_ascii, buf, n, snk);
    }
    
private:
    const char *buf;
    const size_t n;
};
//------------------------------------------------------------------------------
/** Base64 encoder which is a little more customizable than format::base64.
 *
 *  @see base64
 * */
class base64_ex
{
public:
    /** Constructor
     *
     *  @param padding Enable padding.
     *  @param cols The number of characters per line (0 = no wrapping).
     *  @param buf_ The input data which must be null-terminated.
     * */
    inline base64_ex(bool padding, const size_t cols,
        const char *buf_) noexcept
    : ncols(cols), pad(padding), buf(buf_), n(strlen(buf_))
    {}
    /** Constructor
     *
     *  @param padding Enable padding.
     *  @param cols The number of characters per line (0 = no wrapping).
     *  @param buf_ The input data.
     *  @param n_ Size of the input data in bytes.
     * */
    inline base64_ex(bool padding, const size_t cols,
        const char *buf_, const size_t n_) noexcept
    : ncols(cols), pad(padding), buf(buf_), n(n_)
    {}
    /** Constructor
     *
     *  @param padding Enable padding.
     *  @param cols The number of characters per line (0 = no wrapping).
     *  @param beg The start of the input data.
     *  @param end The end of the input data.
     * */
    inline base64_ex(bool padding, const size_t cols,
        const char *beg, const char *end) noexcept
    : ncols(cols), pad(padding), buf(beg), n(end-beg)
    {}
    
    template <class Sink>
    inline void operator () (Sink &snk, fout_tag) const
    {
        if(ncols == 0)
            base64_detail::encode(pad, base64_detail::b64_ascii, buf, n, snk);
        else
            base64_detail::encode(pad, base64_detail::b64_ascii, buf, n,
                base64_detail::wrapping_sink<Sink>(snk, ncols));
    }
    
private:
    const size_t ncols;
    const bool pad;
    const char *buf;
    const size_t n;
};

/** @} */

}}} // namespaces

#endif // NIC_D305D5041316DFC9_NIC
