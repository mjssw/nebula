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
#ifndef NIC_027F3C63737AB3A2_NIC
#define NIC_027F3C63737AB3A2_NIC

#include "config.h"

#ifdef N_NET_posix_socket
#   include "posix/posix_dgram_socket.h"
#   include "posix/posix_stream_socket.h"
#   ifdef N_NET_use_epoll
#       include "posix/posix_async_service.h"
#       include "posix/posix_async_dgram_socket.h"
#       include "posix/posix_async_stream_socket.h"
#       include "posix/epoll/epoll_proactor.h"
#       include "posix/epoll/epoll_socket.h"
#   endif // N_NET_use_epoll
#endif // N_NET_posix_socket

namespace nebula { namespace foundation { namespace net {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
#ifdef N_NET_posix_socket
template <address_family AF>
using dgram_socket = posix::dgram_socket<
    typename net_detail::dispatch_address_family<AF>::endpoint_type>;

template <address_family AF>
using stream_socket = posix::stream_socket<
    typename net_detail::dispatch_address_family<AF>::endpoint_type>;
template <address_family AF>
using stream_socket_acceptor = posix::stream_socket_acceptor<
    typename net_detail::dispatch_address_family<AF>::endpoint_type>;
    
#ifdef N_NET_use_epoll
using async_service = posix::async_service<posix::epoll_proactor>;

template <address_family AF>
using async_stream_socket = posix::async_stream_socket<
    typename net_detail::dispatch_address_family<AF>::endpoint_type,
    async_service,
    posix::epoll_socket>;
template <address_family AF>
using async_stream_socket_callback
    = typename async_stream_socket<AF>::callback_base;

template <address_family AF>
using async_stream_socket_acceptor = posix::async_stream_socket_acceptor<
    typename net_detail::dispatch_address_family<AF>::endpoint_type,
    async_service,
    posix::epoll_socket>;
template <address_family AF>
using async_stream_socket_acceptor_callback
    = typename async_stream_socket_acceptor<AF>::callback_base;
    
template <address_family AF>
using async_dgram_socket = posix::async_dgram_socket<
    typename net_detail::dispatch_address_family<AF>::endpoint_type,
    async_service,
    posix::epoll_socket>;
template <address_family AF>
using async_dgram_socket_callback
    = typename async_dgram_socket<AF>::callback_base;
#endif // N_NET_use_epoll

#endif // N_NET_posix_socket

/** @} */    

}}} // namespaces

#endif // NIC_027F3C63737AB3A2_NIC
