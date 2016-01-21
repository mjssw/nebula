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
#ifndef NIC_9B62D14C2545A78C_NIC
#define NIC_9B62D14C2545A78C_NIC

#include "../config.h"
#ifdef N_NET_posix_socket

#include "../address.h"
#include "../endpoint.h"
#include "../exception.h"
#include "../../endian.h"
#include <arpa/inet.h>

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
extern ip::ipv6_address n_foundation_dll
to_ipv6_address(const ::in6_addr &addr);
//------------------------------------------------------------------------------
extern ::socklen_t n_foundation_dll
to_sockaddr(const ip::ipv4_endpoint &ep, ::sockaddr &addr);

extern ::socklen_t n_foundation_dll
to_sockaddr(const endpoint &ep, ::sockaddr &addr);

extern endpoint n_foundation_dll to_endpoint(const ::sockaddr &addr);

/** @} */

}}}} // namespaces

#endif // N_NET_posix_socket

#endif // NIC_9B62D14C2545A78C_NIC
