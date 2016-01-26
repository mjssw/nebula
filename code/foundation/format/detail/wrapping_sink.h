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
#ifndef NIC_20ACA6BB64629630_NIC
#define NIC_20ACA6BB64629630_NIC

#include "../fwrite.h"
#include "../../io.h"
#include "../../exception.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
namespace fmt_detail {
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

} // fmt_detail

/** @} */

}}} // namespaces

#endif // NIC_20ACA6BB64629630_NIC
