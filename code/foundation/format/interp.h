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
#ifndef NIC_8C3B62ED65E083BA_NIC
#define NIC_8C3B62ED65E083BA_NIC

#include "fwrite.h"
#include "../string.h"
#include "../array.h"
#include "../cstring.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace interp_detail {
//------------------------------------------------------------------------------
struct buffer
{
    static constexpr size_t Size = 1;
    
    using stream_category = tag<io::out_tag>;
    using stream_size = io::streamsize;
    using stream_offset = io::streamoff;
    using stream_position = io::streampos;
    
    template <class T>
    inline buffer(const T &x)
    : cur(stat)
    {
        fmt::fwrite(*this, x);
    }
    
    inline void write(const char *s, const stream_size n)
    {
        if(!dyn.empty())
        {
            dyn.append(s, n);
        }
        else
        {
            if(cur - stat + n < Size)
                cur = foundation::iterator::copy(s, s+n, cur);
            else
            {
                if(cur-stat)
                    dyn.append(stat, cur);
                dyn.append(s, n);
            }
        }
    }
    inline void put(const char c)
    {
        if(!dyn.empty())
        {
            dyn.emplace_back(c);
        }
        else
        {
            if(cur-stat + 1 < Size)
                *cur++ = c;
            else
            {
                if(cur-stat)
                    dyn.append(stat, cur);
                dyn.emplace_back(c);
            }
        }
    }
    
    inline const_cstring str() const noexcept {
        if(!dyn.empty())
            return const_cstring(dyn.begin(), dyn.end());
        else
            return const_cstring(stat, cur);
    }
    
    char stat[Size];
    char *cur;
    vector<char> dyn;
};
    
} // interp_detail

//------------------------------------------------------------------------------
/** Simple string interpolation function. Tokens of the form %i% are replaced
 * by the associated value at index i. Indexing in decimal format beginning
 * at 0. Type %% to print a single %.
 * @param str The string to interpolate (must be utf-8 encoded).
 */
template <class Stream, class ... T>
inline void interp(Stream &s, const const_cstring str, const T & ... w)
{
    array<interp_detail::buffer, sizeof ... (T)> arr{
        interp_detail::buffer(w)...};
    const char *prev_str = str.begin();
    
    for(const char *i = str.begin(); i < str.end(); )
    {
        if(*i == '%')
        {
            if(i-prev_str) 
                io::write(s, prev_str, i-prev_str);
            
            ++i;
            if(i == str.end())
                n_throw(runtime_error)
                << ei_msg_c("Unterminated '%'");
            else if(*i == '%') {
                prev_str = i++;
                continue;
            }
            else if(*i < 48 || *i > 57)
                n_throw(runtime_error)
                << ei_msg_c("Not a number.");
            
            size_t index = *i++ - 48;
            if(i == str.end())
                n_throw(runtime_error)
                << ei_msg_c("Unterminated '%'");
            
            while(*i != '%')
            {
                if(*i < 48 || *i > 57)
                    n_throw(runtime_error)
                    << ei_msg_c("Not a number.");
                
                index *= 10;
                index += *i++ - 48;
    
                if(i == str.end())
                    n_throw(runtime_error)
                    << ei_msg_c("Unterminated '%'");
            }
            
            fmt::fwrite(s, arr.at(index).str());
            
            ++i;
            if(i == str.end())
                return;
            prev_str = i;
        }
        else
            ++i;
    }
    
    if(str.end() - prev_str)
        io::write(s, prev_str, str.end() - prev_str);
}

/** @} */

}}} // namespaces

#endif // NIC_8C3B62ED65E083BA_NIC
