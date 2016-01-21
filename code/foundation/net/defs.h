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
#ifndef NIC_8D175C6376B33442_NIC
#define NIC_8D175C6376B33442_NIC

#include "config.h"
#include "../defs.h"
#include "../dll_interface.h"

#ifdef N_NET_posix_socket
#   include <sys/types.h>
#   include <sys/socket.h>
#endif

namespace nebula { namespace foundation { namespace net {
/** @ingroup Foundation
 * @{
 */  
#ifdef N_NET_posix_socket

n_static_assert(AF_UNIX == AF_LOCAL, "");

//------------------------------------------------------------------------------
enum class address_family : int
{    
    // unix = AF_UNIX,
    local = AF_LOCAL,
    inet = AF_INET,
    inet6 = AF_INET6,
    ipx = AF_IPX,
    netlink = AF_NETLINK,
    x25 = AF_X25,
    ax25 = AF_AX25,
    atmpvc = AF_ATMPVC,
    appletalk = AF_APPLETALK,
    packet = AF_PACKET,
    alg = AF_ALG,
    unspecified = AF_UNSPEC
};

//------------------------------------------------------------------------------
enum class socket_category : int
{
    stream = SOCK_STREAM,
    dgram = SOCK_DGRAM,
    seqpacket = SOCK_SEQPACKET,
    raw = SOCK_RAW,
    rdm = SOCK_RDM,
    packet = SOCK_PACKET,
    unspecified = 0
};

//------------------------------------------------------------------------------
enum class channel : int 
{
    send,
    recv,
    both
};

#endif // N_NET_posix_socket

//------------------------------------------------------------------------------
namespace net_detail {
extern address_family n_foundation_dll to_address_family(const int x);
extern socket_category n_foundation_dll to_socket_category(const int x);
} // net_detail

//------------------------------------------------------------------------------
using protocol_type = int;

//------------------------------------------------------------------------------
const char * n_foundation_dll to_cstr(const address_family) noexcept;
const char * n_foundation_dll to_cstr(const socket_category) noexcept;
const char * n_foundation_dll to_cstr(const channel) noexcept;

/** @} */    

}}} // namespaces

#endif // NIC_8D175C6376B33442_NIC
