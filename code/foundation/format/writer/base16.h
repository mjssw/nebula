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
#ifndef NIC_EEF456E718ABAECC_NIC
#define NIC_EEF456E718ABAECC_NIC

#include "../detail/wrapping_sink.h"
#include "../fwrite.h"
#include "../digit_codec.h"
#include "../../io.h"
#include "../../exception.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
namespace base16_detail {
//------------------------------------------------------------------------------
template <class Codec, class Sink>
inline void encode(Sink &&out, const char *buf_, const size_t n)
{
    n_static_assert(Codec::size::value == 16, "");
    n_static_assert(n_char_bit == 8, "");
    
    if(0 == n)
        return;
    if(!buf_)
        n_throw(logic_error);
    
    const unsigned char *buf = static_cast<const unsigned char *>(
        static_cast<const void *>(buf_));
    
    for(size_t i = 0; i < n; ++i)
    {
        const unsigned char high = buf[i] >> 4;
        const unsigned char low = buf[i] & 0b1111;
        io::put(out, Codec::encode(high));
        io::put(out, Codec::encode(low));
    }
}

//------------------------------------------------------------------------------
template <class Codec, class Sink>
inline bool decode(Sink &&s, const char *buf, const size_t n)
{
    n_static_assert(Codec::size::value == 16, "");
    n_static_assert(n_char_bit == 8, "");
    
    size_t i = 0;
    while(i < n)
    {
        unsigned high;
        
        while(true)
        {   
            high = Codec::decode(buf[i], nothrow_tag());
            if(unsigned(-1) == high) {
                if('\n' != buf[i])
                    return false;
            }
            else {
                ++i;
                break;
            }
            
            ++i;
            if(i == n)
                return false;
        }
        
        unsigned low;
        
        while(true)
        {
            if(i == n)
                return false;
            
            low = Codec::decode(buf[i], nothrow_tag());
            if(unsigned(-1) == low) {
                if('\n' != buf[i])
                    return false;
            }
            else {
                ++i;
                break;
            }
            
            ++i;
        }
        
        const char c = (high << 4) | low;
        io::put(s, c);
    }
    
    return true;
}

} // base16_detail

//------------------------------------------------------------------------------
template <class Sink>
inline void base16_encode(Sink &&snk, const char *buf, const size_t n)
{
    base16_detail::encode<digit_codec>(snk, buf, n);
}
//------------------------------------------------------------------------------
template <class Sink>
inline void base16_encode(Sink &&snk, const size_t ncols,
    const char *buf, const size_t n)
{
    if(ncols == 0)
        base16_detail::encode<digit_codec>(snk, buf, n);
    else
        base16_detail::encode<digit_codec>(
            fmt_detail::wrapping_sink<ctraits::_value<Sink>>(snk, ncols),
            buf, n);
}

//------------------------------------------------------------------------------
template <class Sink>
inline bool base16_decode(Sink &&snk, const char *buf, const size_t n)
{
    return base16_detail::decode<digit_codec>(snk, buf, n);
}
//------------------------------------------------------------------------------
template <class Sink>
inline bool base16_decode(Sink &&snk, const char *beg, const char *end)
{
    return base16_detail::decode<digit_codec>(snk, beg, end-beg);
}

//------------------------------------------------------------------------------
/** Simple base16 encoder.
 *
 *  This does not wrap lines.
 *
 *  @see base16_ex
 * */
class base16
{
public:
    /** Constructor
     *
     *  @param buf_ The input data which must be null-terminated.
     * */
    inline base16(const char *buf_) noexcept
    : buf(buf_), n(strlen(buf_))
    {}
    /** Constructor
     *
     *  @param buf_ The input data.
     *  @param n_ Size of the input data in bytes.
     * */
    inline base16(const char *buf_, const size_t n_) noexcept
    : buf(buf_), n(n_)
    {}
    /** Constructor
     *
     *  @param beg The start of the input data.
     *  @param end The end of the input data.
     * */
    inline base16(const char *beg, const char *end) noexcept
    : buf(beg), n(end-beg)
    {}
    
    template <class Sink>
    inline void operator () (Sink &snk, fout_tag) const
    {
        base16_encode(snk, buf, n);
    }
    
private:
    const char *buf;
    const size_t n;
};
//------------------------------------------------------------------------------
/** base16 encoder which is a little more customizable than format::base16.
 *
 *  @see base16
 * */
class base16_ex
{
public:
    /** Constructor
     *
     *  @param cols The number of characters per line (0 = no wrapping).
     *  @param buf_ The input data which must be null-terminated.
     * */
    inline base16_ex(const size_t cols,
        const char *buf_) noexcept
    : ncols(cols), buf(buf_), n(strlen(buf_))
    {}
    /** Constructor
     *
     *  @param cols The number of characters per line (0 = no wrapping).
     *  @param buf_ The input data.
     *  @param n_ Size of the input data in bytes.
     * */
    inline base16_ex(const size_t cols,
        const char *buf_, const size_t n_) noexcept
    : ncols(cols), buf(buf_), n(n_)
    {}
    /** Constructor
     *
     *  @param cols The number of characters per line (0 = no wrapping).
     *  @param beg The start of the input data.
     *  @param end The end of the input data.
     * */
    inline base16_ex(const size_t cols,
        const char *beg, const char *end) noexcept
    : ncols(cols), buf(beg), n(end-beg)
    {}
    
    template <class Sink>
    inline void operator () (Sink &snk, fout_tag) const
    {
        base16_encode(snk, ncols, buf, n);
    }
    
private:
    const size_t ncols;
    const char *buf;
    const size_t n;
};
//------------------------------------------------------------------------------
/** Simple base16 decoder.
 * */
class base16_d
{
public:
    /** Constructor
     *
     *  @param buf_ The input data which must be null-terminated.
     * */
    inline base16_d(const char *buf_) noexcept
    : buf(buf_), n(strlen(buf_))
    {}
    /** Constructor
     *
     *  @param buf_ The input data.
     *  @param n_ Size of the input data in bytes.
     * */
    inline base16_d(const char *buf_, const size_t n_) noexcept
    : buf(buf_), n(n_)
    {}
    /** Constructor
     *
     *  @param beg The start of the input data.
     *  @param end The end of the input data.
     * */
    inline base16_d(const char *beg, const char *end) noexcept
    : buf(beg), n(end-beg)
    {}
    
    template <class Sink>
    inline void operator () (Sink &snk, fout_tag) const
    {
        if(!base16_decode(snk, buf, n))
            n_throw(runtime_error)
            << ei_msg_c("Base-16 decoding failed");
    }
    
private:
    const char *buf;
    const size_t n;
};

/** @} */

}}} // namespaces

#endif // NIC_EEF456E718ABAECC_NIC
