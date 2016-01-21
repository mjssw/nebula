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
#include "posix_socket.h"
#ifdef N_NET_posix_socket

#include "posix_error.h"
#include "../exception.h"
#include "../../assert.h"
#include "../../math/exact_cast.h"

#include <unistd.h>
#include <fcntl.h>

//------------------------------------------------------------------------------
/** @ingroup Foundation */
#define n_conv_error(code, msg_c) \
    posix::map_error(code) == errc::unknown \
    ? (n_throw(network_error, system::system_error) \
        << ei_msg_c(msg_c) \
        << system::ei_error_code(\
            system::error_code(code, system::system_category()))) \
    : posix::map_error(code);

namespace nebula { namespace foundation { namespace net { namespace posix {
namespace socket_detail {
//------------------------------------------------------------------------------
/** @ingroup Foundation
 * Used for more descriptive error messages.
 * */
inline const char *socket_option_to_cstr(const int opt) noexcept
{
    switch(opt)
    {
    case SO_ACCEPTCONN:
        return "SO_ACCEPTCONN";
    case SO_BINDTODEVICE:
        return "SO_BINDTODEVICE";
    case SO_BROADCAST:
        return "SO_BROADCAST";
    case SO_DEBUG:
        return "SO_DEBUG";
    case SO_DONTROUTE:
        return "SO_DONTROUTE";
    case SO_KEEPALIVE:
        return "SO_KEEPALIVE";
    case SO_REUSEADDR:
        return "SO_REUSEADDR";
    case SO_REUSEPORT:
        return "SO_REUSEPORT";
    default:
        return "unknown";
    }
}
    
} // socket_detail

//------------------------------------------------------------------------------
void socket::open_(
    const net::address_family fam,
    const net::socket_category cat,
    const protocol_type proto)
{
    n_assert(h == -1);
    
    h = ::socket(
        static_cast<int>(fam),
        static_cast<int>(cat),
        static_cast<int>(proto));
    if(h == -1)
    {
        n_throw(network_error, system::system_error)
            << ei_msg_c("::socket() failed.")
            << system::ei_error_code(system::error_code(
                errno, system::system_category()));
    }
}
//------------------------------------------------------------------------------
void socket::close() noexcept
{
    if(h != -1)
    {
        ::close(h);
        h = -1;
    }
}

//------------------------------------------------------------------------------
errc socket::connect(const endpoint &ep)
{
    n_assert(h != -1);
    
    ::sockaddr addr;
    const ::socklen_t addr_size = to_sockaddr(ep, addr);
    
    const int res = ::connect(h, &addr, addr_size);    
    if(res == -1)
        return n_conv_error(errno, "::connect() failed.");
    return errc::success;
}

//------------------------------------------------------------------------------
void socket::shutdown(const channel c) noexcept
{
    n_assert(h != -1);
    
    int flgs;
    switch(c)
    {
    case channel::send:
        flgs = SHUT_WR;
        break;
    case channel::recv:
        flgs = SHUT_RD;
        break;
    default: // channel::both
        flgs = SHUT_RDWR;
        break;
    };
    
    ::shutdown(h, flgs);
}

//------------------------------------------------------------------------------
errc socket::listen(const size_t backlog)
{
    n_assert(h != -1);
    
    math::require_exact_cast<int>(backlog);
    
    const int res = ::listen(h, backlog);    
    if(res == -1)
        return n_conv_error(errno, "::listen() failed.");
    return errc::success;
}

//------------------------------------------------------------------------------
errc socket::bind(const endpoint &ep)
{
    n_assert(h != -1);
    
    ::sockaddr addr;
    const ::socklen_t addr_size = to_sockaddr(ep, addr);
    
    const int res = ::bind(h, &addr, addr_size);   
    if(res == -1)
        return n_conv_error(errno, "::bind() failed.");
    return errc::success;
}

//------------------------------------------------------------------------------
expect<socket, errc> socket::accept(endpoint &ep)
{
    n_assert(h != -1);
    
    ::sockaddr addr = {};
    ::socklen_t n = sizeof(::sockaddr);
    
    const int res = ::accept(
        h,
        &addr,
        &n);    
    if(res == -1)
        return n_conv_error(errno, "::accept() failed.");
    
    ep = to_endpoint(addr);
    
    return socket(res);
}
//------------------------------------------------------------------------------
expect<socket, errc> socket::accept()
{
    n_assert(h != -1);
    
    ::sockaddr addr = {};
    ::socklen_t n = sizeof(::sockaddr);
    
    const int res = ::accept(
        h,
        &addr,
        &n);    
    if(res == -1)
        return n_conv_error(errno, "::accept() failed.");
    
    return socket(res);
}

//------------------------------------------------------------------------------
endpoint socket::bound_endpoint() const
{
    n_assert(h != -1);
    
    ::sockaddr addr = {};
    ::socklen_t addr_len = sizeof(::sockaddr);
    
    const int res = ::getsockname(
        h,
        &addr,
        &addr_len);    
    if(res == -1)
        n_throw(network_error, system::system_error)
        << ei_msg_c("::getsockname() failed.")
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
        
    return to_endpoint(addr);
}
//------------------------------------------------------------------------------
endpoint socket::peer_endpoint() const
{
    n_assert(h != -1);
    
    ::sockaddr addr = {};
    ::socklen_t addr_len = sizeof(::sockaddr);
    
    const int res = ::getpeername(
        h,
        &addr,
        &addr_len);    
    if(res == -1)
        n_throw(network_error, system::system_error)
        << ei_msg_c("::getpeername() failed.")
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
        
    return to_endpoint(addr);
}

//------------------------------------------------------------------------------
expect<size_t, errc> socket::send(const char *ptr, const size_t n)
{
    n_assert(h != -1);
    const ::ssize_t res = ::send(h, ptr, n, MSG_NOSIGNAL);
    if(res == -1)
        return n_conv_error(errno, "::send() failed.");
    math::require_exact_cast<size_t>(res);
    return res;
}

//------------------------------------------------------------------------------
expect<size_t, errc> socket::recv(char *ptr, const size_t n)
{    
    const ::ssize_t res = ::recv(h, ptr, n, 0);
    if(res == -1)
        return n_conv_error(errno, "::recv() failed.");
    math::require_exact_cast<size_t>(res);
    return res;
}

//------------------------------------------------------------------------------
expect<size_t, errc> socket::send_to(
    const endpoint &ep, 
    const char *ptr,
    const size_t n)
{
    n_assert(h != -1);
    
    ::sockaddr addr;
    const ::socklen_t addr_size = to_sockaddr(ep, addr);
    
    const ::ssize_t res = ::sendto(h, ptr, n, MSG_NOSIGNAL, &addr, addr_size);
    if(res == -1)
        return n_conv_error(errno, "::sendto() failed.");
    
    math::require_exact_cast<size_t>(res);
    return res;
}

//------------------------------------------------------------------------------
expect<size_t, errc> socket::recv_from(
    endpoint &ep, 
    char *ptr,
    const size_t n)
{
    n_assert(h != -1);
    
    ::sockaddr addr = {};
    ::socklen_t sn = sizeof(::sockaddr);
    
    const ::ssize_t res = ::recvfrom(h, ptr, n, MSG_NOSIGNAL, &addr, &sn);
    
    if(res == -1)
        return n_conv_error(errno, "::recvfrom() failed.");
        
    ep = to_endpoint(addr);
    
    math::require_exact_cast<size_t>(res);
    return res;
}

//------------------------------------------------------------------------------
void socket::blocking(const bool x)
{
    int res = ::fcntl(h, F_GETFL, 0);
    if(res == -1)
    {
        n_throw(network_error, system::system_error)
            << ei_msg_c("::fcntl() failed.")
            << system::ei_error_code(system::error_code(
                errno, system::system_category()));
    }
    int flgs = x ? (res & ~O_NONBLOCK) : (res | O_NONBLOCK);
    res = ::fcntl(h, F_SETFL, flgs);
    if(res == -1)
    {
        n_throw(network_error, system::system_error)
            << ei_msg_c("::fcntl() failed.")
            << system::ei_error_code(system::error_code(
                errno, system::system_category()));
    }
}
//------------------------------------------------------------------------------
bool socket::blocking() const
{
    long res = ::fcntl(h, F_GETFL, NULL);
    if(res == -1) { 
        n_throw(network_error, system::system_error)
            << ei_msg_c("::fcntl() failed.")
            << system::ei_error_code(system::error_code(
                errno, system::system_category()));
    }
    return (res & O_NONBLOCK) == 0;
}

//------------------------------------------------------------------------------
void socket::get_opt_(int level, int name, void *ptr, size_t &len) const
{
    math::require_exact_cast<::socklen_t>(len);
    ::socklen_t len_ = len;
    const int res = ::getsockopt(h, level, name, ptr, &len_);
    if(res == -1)
    {
        string msg = fmt::to_string(
            "::getsockopt() failed. Option: ",
            socket_detail::socket_option_to_cstr(name));
        
        n_throw(network_error, system::system_error)
        << ei_msg(foundation::move(msg))
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
    }
    math::require_exact_cast<size_t>(len_);
    len = len_;
}
//------------------------------------------------------------------------------
void socket::set_opt_(int level, int name, const void *ptr, size_t len)
{
    math::require_exact_cast<::socklen_t>(len);
    const int res = ::setsockopt(
        h, level, name, ptr, static_cast<::socklen_t>(len));
    if(res == -1)
    {
        string msg = fmt::to_string(
            "::setsockopt() failed. Option: ",
            socket_detail::socket_option_to_cstr(name));
        
        n_throw(network_error, system::system_error)
        << ei_msg(foundation::move(msg))
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
    }
}

}}}} // namespaces

#endif // N_NET_posix_socket
