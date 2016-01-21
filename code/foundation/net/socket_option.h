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
#ifndef NIC_1D1BAC6376B3F178_NIC
#define NIC_1D1BAC6376B3F178_NIC

#include "config.h"

#ifdef N_NET_posix_socket
#   include "posix/posix_socket_option.h"
#endif

namespace nebula { namespace foundation { namespace net {
/** @ingroup Foundation
 * @{
 */  
#ifdef N_NET_posix_socket

namespace socket_option {
using namespace posix::socket_option;  

} // socket_option

#endif // N_NET_posix_socket

/** @} */    

}}} // namespaces

#endif // NIC_1D1BAC6376B3F178_NIC
