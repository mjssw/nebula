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
#include "epoll_proactor.h"

#if defined(N_NET_posix_socket) && defined(N_NET_epoll)

namespace nebula { namespace foundation { namespace net { namespace posix {
//------------------------------------------------------------------------------
thread_local static size_t instance_count = 0;
thread_local static vector<::epoll_event> ep_events;

//------------------------------------------------------------------------------
epoll_proactor::epoll_proactor()
: h(-1), event_count(0)
{
    h = ::epoll_create1(::EPOLL_CLOEXEC);
    if(-1 == h)
    {
        n_throw(network_error, system::system_error)
        << ei_msg_c("epoll_create1() failed")
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
    }
    
    ++instance_count;
}
//------------------------------------------------------------------------------
void epoll_proactor::add(epoll_socket *sock, const int flags)
{
    n_assert(-1 != h);
    
    ::epoll_event epev = ::epoll_event {
        flags | ::EPOLLONESHOT,
        ::epoll_data{ sock }
    };
    
    if(-1 == ::epoll_ctl(h, EPOLL_CTL_ADD, sock->sock.native_handle(), &epev))
    {
        n_throw(network_error, system::system_error)
        << ei_msg_c("epoll_ctl() failed")
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
    }
    
    async::lock(mtx);
    n_scoped_unlock(mtx);
    
    ++event_count;
}
//------------------------------------------------------------------------------
void epoll_proactor::mod(epoll_socket *sock, const int flags)
{
    n_assert(-1 != h);
    
    ::epoll_event epev = ::epoll_event {
        flags | ::EPOLLONESHOT,
        ::epoll_data{ sock }
    };
    
    if(-1 == ::epoll_ctl(h, EPOLL_CTL_MOD, sock->sock.native_handle(), &epev))
    {
        n_throw(network_error, system::system_error)
        << ei_msg_c("epoll_ctl() failed")
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
    }
}
//------------------------------------------------------------------------------
void epoll_proactor::remove(epoll_socket *sock) noexcept
{
    n_assert(-1 != h);
    
    ::epoll_ctl(h, EPOLL_CTL_DEL, sock->sock.native_handle(), nullptr);
    
    async::lock(mtx);
    n_scoped_unlock(mtx);
    
    --event_count;
}
//------------------------------------------------------------------------------
size_t epoll_proactor::update(size_t max_events)
{
    n_assert(-1 != h);
    
    size_t buf_size = 0;
    {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        if(event_count == 0)
            return 0;
        buf_size = max_events > event_count ? event_count : max_events;
    }
    
    ep_events.resize(buf_size);
    
    const int r = ::epoll_wait(h, ep_events.data(), buf_size, 0);
    
    if(-1 == r)
    {
        n_throw(network_error, system::system_error)
        << ei_msg_c("epoll_wait() failed")
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
    }
    
    buf_size = r; // r >= 0
    ep_events.resize(buf_size);
    
    for(auto &x : ep_events)
    {
        epoll_socket *as = static_cast<epoll_socket *>(x.data.ptr);
        
        as->finalize();
    }
    
    return buf_size;
}
//------------------------------------------------------------------------------
void epoll_proactor::kill() noexcept
{
    if(h)
    {
        ::close(h);
        h = -1;
        if(--instance_count == 0)
        {
            ep_events.reset();
        }
    }
}

}}}} // namespaces

#endif
