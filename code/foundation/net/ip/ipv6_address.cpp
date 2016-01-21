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
#include "ipv6_address.h"
#include "../exception.h"

namespace nebula { namespace foundation { namespace net { namespace ip {
//------------------------------------------------------------------------------
/** @ingroup Foundation */
inline typename ipv6_address::hextet_type _parse_num(const const_cstring s)
{
    using hextet_type = typename ipv6_address::hextet_type;

    if(s.empty())
        n_throw(network_error) 
        << ei_msg_c("Expected a number but got nothing.");
        
    hextet_type res;
        
    try { 
        res = fmt::to_integer<hextet_type>(s, 16);
    } catch(...) {
        n_throw(network_error)
        << ei_msg_c("String to integer conversion failed.")
        << ei_exc(current_exception());
    }
    
    if(s.size() > 4)
        n_throw(network_error) 
        << ei_msg_c("Numbers must not exceed 4 digits.");
        
    return res;
}

//------------------------------------------------------------------------------
void ipv6_address::assign_(const const_cstring str)
{    
    using iter_t = typename const_cstring::const_iterator;
    
    if(str.size() < 2)
        n_throw(network_error) << ei_msg_c("Invalid string size.");

    array<hextet_type, 8> ip;
    size_t ip_size = 0;
    size_t skipper_pos = 9;

    iter_t b = str.begin();
    if(*b == ':')
    {
        skipper_pos = 0;
        if(*++b != ':')
            n_throw(network_error)
            << ei_msg_c("An address must not start with a single ':'.");
        ++b;
        if(b == str.end()) // str == "::"
        {
            this->assign(0,0,0,0,0,0,0,0);
            return;
        }
    }
    for(iter_t i = iterator::find(b, str.end(), ':'); 
        ;
        i = iterator::find(b, str.end(), ':'))
    {
        if(b == i)
        {
            if(skipper_pos != 9)
                n_throw(network_error)
                << ei_msg_c("Multiple '::' are not allowed.");
            skipper_pos = ip_size;
            b++;
            if(b == str.end())
            {
                // trailing ::
                break;
            }
        }
        else if(i == str.end())
        {
            if(ip_size == 8)
            {
                n_throw(network_error)
                << ei_msg_c("Address is too long.");
            }
            ip[ip_size++] = _parse_num(const_cstring(b, i));
            break;
        }
        else
        {
            if(ip_size == 8)
            {
                n_throw(network_error)
                << ei_msg_c("Address is too long.");
            }
            ip[ip_size++] = _parse_num(const_cstring(b, i));
            b = i+1;
            if(b == str.end())
            {
                n_throw(network_error)
                << ei_msg_c("A single trailing ':' is not allowed.");
            }
        }
    }
    
    if(ip_size < 8)
    {
        if(skipper_pos == 9)
            n_throw(network_error)
            << ei_msg_c("Address is incomplete.");
        auto i = iterator::copy(
            ip.begin(), ip.begin()+skipper_pos, v.begin());
        iterator::fill_n(i, 8-ip_size, 0);
        iterator::copy(
            ip.begin()+skipper_pos, ip.begin()+ip_size, i+(8-ip_size));
    }
    else
    {
        if(skipper_pos != 9)
            n_throw(network_error)
            << ei_msg_c("A complete address containing '::' is not allowed.");
        range::copy(ip, v.begin());
    }
}

//------------------------------------------------------------------------------
tuple<size_t, size_t> ipv6_address::find_the_funky_skipper() const noexcept 
{
    size_t bg = 0, nd = 0;
    
    for(size_t i = 1; i < 8; ++i) {
        if(get(i-1) == 0 && get(i) == 0)
        {
            const size_t b_ = i-1;
            ++i;
            for( ; i < 8; ++i) {
                if(get(i) != 0)
                    break;
            }
            if(i-b_ > nd-bg) {
                bg = b_;
                nd = i;
            }
        }
    }
    
    return foundation::make_tuple(bg, nd);
}

}}}} // namespaces
