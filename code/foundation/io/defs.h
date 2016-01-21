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
#ifndef NIC_57AF4A676FF7A32C_NIC
#define NIC_57AF4A676FF7A32C_NIC

#include "../defs.h"
#include "../assert.h"
#include "exception.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
/** Default size type for streams.
 * @attention Is always size_t.
 * */
using streamsize = size_t;
/** Default offset type for streams.
 * @attention Is always ptrdiff_t.
 * */
using streamoff = ptrdiff_t;
/** Default position type for streams.
 * @attention Is always ptrdiff_t.
 * */
using streampos = streamoff;

namespace io_detail {
//------------------------------------------------------------------------------
struct eof_type {};
} // io_detail
//------------------------------------------------------------------------------
static constexpr io_detail::eof_type eof;

//------------------------------------------------------------------------------
struct ceof
{
    inline ceof(io_detail::eof_type) noexcept
    : eof_(true)
    {}
    inline ceof(char x) noexcept
    : c(x), eof_(false)
    {}
    
    inline void swap(ceof &other) noexcept {
        char tmp_c = c;
        c = other.c;
        other.c = tmp_c;
        bool tmp_flg = eof_;
        tmp_flg = other.eof_;
        eof_ = tmp_flg;
    }
    
    inline bool eof() const noexcept {
        return eof_;
    }
    
    inline bool operator == (io_detail::eof_type) const noexcept {
        return eof();
    }
    inline bool operator != (io_detail::eof_type) const noexcept {
        return !eof();
    }
    
    inline char get() {
        if(eof())
            n_throw(io_error) << ei_msg_c("EOF");
        n_assert(x <= CHAR_MAX);
        n_assert(x >= CHAR_MIN);
        return c;
    }
    
private:
    char c;
    bool eof_;
};

//------------------------------------------------------------------------------
inline bool operator == (io_detail::eof_type, const ceof x) noexcept {
    return x == io::eof;
}
inline bool operator != (io_detail::eof_type, const ceof x) noexcept {
    return x != io::eof;
}

//------------------------------------------------------------------------------
namespace io_detail {
//------------------------------------------------------------------------------
enum class mode
{
    in,
    out,
    in_out
};
//------------------------------------------------------------------------------
enum class origin
{
    beg,
    cur,
    end
};

} // io_detail

/** @} */

}}} // namespaces

#endif // NIC_57AF4A676FF7A32C_NIC
