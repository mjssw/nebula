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
#include "defs.h"
#include "../exception.h"

namespace nebula { namespace foundation { namespace net {
namespace net_detail {
//------------------------------------------------------------------------------
address_family to_address_family(const int x)
{
    switch(x)
    {
    case AF_LOCAL: return address_family::local;
    case AF_INET: return address_family::inet;
    case AF_INET6: return address_family::inet6;
    case AF_IPX: return address_family::ipx;
    case AF_NETLINK: return address_family::netlink;
    case AF_X25: return address_family::x25;
    case AF_AX25: return address_family::ax25;
    case AF_ATMPVC: return address_family::atmpvc;
    case AF_APPLETALK: return address_family::appletalk;
    case AF_PACKET: return address_family::packet;
    case AF_ALG: return address_family::alg;
    default:
        n_throw(logic_error);
    }
}

//------------------------------------------------------------------------------
socket_category to_socket_category(const int x)
{
    switch(x)
    {
    case SOCK_STREAM: return socket_category::stream;
    case SOCK_DGRAM: return socket_category::dgram;
    case SOCK_SEQPACKET: return socket_category::seqpacket;
    case SOCK_RAW: return socket_category::raw;
    case SOCK_RDM: return socket_category::rdm;
    case SOCK_PACKET: return socket_category::packet;
    default:
        n_throw(logic_error);
    }
}
    
} // net_detail

//------------------------------------------------------------------------------
const char *to_cstr(const address_family x) noexcept
{    
    switch(x)
    {
    case address_family::local: return "local";
    case address_family::inet: return "inet";
    case address_family::inet6: return "inet6";
    case address_family::ipx: return "ipx";
    case address_family::netlink: return "netlink";
    case address_family::x25: return "x25";
    case address_family::ax25: return "ax25";
    case address_family::atmpvc: return "atmpvc";
    case address_family::appletalk: return "appletalk";
    case address_family::packet: return "packet";
    case address_family::alg: return "alg";
    default: return "unknown";
    }
}
//------------------------------------------------------------------------------
const char *to_cstr(const socket_category x) noexcept
{    
    switch(x)
    {
    case socket_category::stream: return "stream";
    case socket_category::dgram: return "dgram";
    case socket_category::seqpacket: return "seqpacket";
    case socket_category::raw: return "raw";
    case socket_category::rdm: return "rdm";
    case socket_category::packet: return "packet";
    default: return "unknown";
    }
}
//------------------------------------------------------------------------------
const char *to_cstr(const channel x) noexcept
{    
    switch(x)
    {
    case channel::send: return "send";
    case channel::recv: return "recv";
    case channel::both: return "both";
    default: return "unknown";
    }
}

}}} // namespaces
