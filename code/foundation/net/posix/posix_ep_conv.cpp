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
#include "posix_ep_conv.h"
#include "../exception.h"
#include "../../endian.h"

#ifdef N_NET_posix_socket

namespace nebula { namespace foundation { namespace net { namespace posix {
//------------------------------------------------------------------------------
ip::ipv6_address to_ipv6_address(const ::in6_addr &addr)
{
    ip::ipv6_address res;
    for(unsigned i = 0; i < 16; ++i)
        res.octet(i, addr.s6_addr[i]);
    return res;
}
//------------------------------------------------------------------------------
::socklen_t to_sockaddr(const ip::ipv4_endpoint &ep, ::sockaddr &addr)
{
    ::sockaddr_in * in_addr = static_cast<::sockaddr_in *>(
        static_cast<void *>(&addr));
    foundation::memset(in_addr, 0, sizeof(::sockaddr_in));
    in_addr->sin_family = AF_INET;
    in_addr->sin_port = endian::hton(ep.port());
    in_addr->sin_addr.s_addr = endian::hton(ep.address().integer());
    return sizeof(::sockaddr_in);
}
//------------------------------------------------------------------------------
::socklen_t to_sockaddr(const ip::ipv6_endpoint &ep, ::sockaddr &addr)
{
    ::sockaddr_in6 * in_addr = static_cast<::sockaddr_in6 *>(
        static_cast<void *>(&addr));
    foundation::memset(in_addr, 0, sizeof(::sockaddr_in6));
    in_addr->sin6_family = AF_INET6;
    in_addr->sin6_port = endian::hton(ep.port());
    for(unsigned i = 0; i < 16; ++i)
        in_addr->sin6_addr.s6_addr[i] = ep.address().octet(i);
    return sizeof(::sockaddr_in6);
}
//------------------------------------------------------------------------------
::socklen_t to_sockaddr(const endpoint &ep, ::sockaddr &addr)
{
    if(ep.empty())
        n_throw(logic_error);
    switch(ep.address_family())
    {
    case address_family::inet:
        return to_sockaddr(endpoint_cast<ip::ipv4_endpoint>(ep), addr);
    case address_family::inet6:
        return to_sockaddr(endpoint_cast<ip::ipv6_endpoint>(ep), addr);
    default:
        n_throw(network_error)
        << ei_msg_c("Address family is not supported.");
        break;
    }
}
//------------------------------------------------------------------------------
endpoint to_endpoint(const ::sockaddr &addr)
{
    endpoint ep;
    switch(addr.sa_family)
    {
    case AF_INET:
        {
            const ::sockaddr_in * in_addr 
                = static_cast<const ::sockaddr_in *>(
                    static_cast<const void *>(&addr));
            ep = ip::ipv4_endpoint(
                ip::ipv4_address(endian::ntoh(in_addr->sin_addr.s_addr)),
                endian::ntoh(in_addr->sin_port));
        }
        break;
    case AF_INET6:
        {
            const ::sockaddr_in6 * in_addr 
                = static_cast<const ::sockaddr_in6 *>(
                    static_cast<const void *>(&addr));
            ip::ipv6_address addr6;
            for(unsigned i = 0; i < 16; ++i)
                addr6.octet(i, in_addr->sin6_addr.s6_addr[i]);
            ep = ip::ipv6_endpoint(foundation::move(addr6),
                endian::ntoh(in_addr->sin6_port));
        }
        break;
    default:
        n_throw(network_error)
        << ei_msg_c("Address family is not valid.");
    }
    
    return ep;
}

}}}} // namespaces

#endif // N_NET_posix_socket
