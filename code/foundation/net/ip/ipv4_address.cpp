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
#include "ipv4_address.h"
#include "../exception.h"

namespace nebula { namespace foundation { namespace net { namespace ip {
//------------------------------------------------------------------------------
/** @ingroup Foundation */
inline typename ipv4_address::storage_type _parse_num(const const_cstring s)
{
    using storage_type = typename ipv4_address::storage_type;
    
    if(s.empty())
        n_throw(network_error)
        << ei_msg_c("Expected a number but got nothing.");
    
    try {
        if(s[0] == '0')
        {
            if(s.size() == 1)
                return 0;
            else
            {                
                if( (s[1] == 'x') || (s[1] == 'X') )
                {
                    if(s.size() < 3)
                        n_throw(network_error) << ei_msg_c("Invalid number");
                    
                    return fmt::to_integer<storage_type>(
                        s.begin()+2, s.end(), 16);
                }
                else
                    return fmt::to_integer<storage_type>(
                        s.begin()+1, s.end(), 8);
            }
        }
        else
            return fmt::to_integer<storage_type>(s, 10);
    }
    catch(...)
    {
        n_throw(network_error)
        << ei_msg_c("String to integer conversion failed.")
        << ei_exc(current_exception());
    }
}
//------------------------------------------------------------------------------
void ipv4_address::assign_(const const_cstring str)
{    
    if(str.empty())
        n_throw(network_error) << ei_msg_c("Input of empty string.");
    
    const char *i = range::find(str, '.');
    
    if(i == str.end())
    {
        v = _parse_num(str);
    }
    else
    {            
        octet_type a,b,c,d;
        a = _parse_num(const_cstring(str.begin(), i));
        
        const char *beg = i+1;
        i = iterator::find(beg, str.end(), '.');
        if(i == str.end())
            n_throw(network_error) << ei_msg_c("Expected a dot.");
        b = _parse_num(const_cstring(beg, i));
        
        beg = i+1;
        i = iterator::find(beg, str.end(), '.');
        if(i == str.end())
            n_throw(network_error) << ei_msg_c("Expected a dot.");
        c = _parse_num(const_cstring(beg, i));
        
        beg = i+1;
        d = _parse_num(const_cstring(beg, str.end()));
        
        this->assign(a,b,c,d);
    }
}

}}}} // namespaces
