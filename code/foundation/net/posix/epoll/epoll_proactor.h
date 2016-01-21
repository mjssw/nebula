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
#ifndef NIC_7083D51A7DD8B064_NIC
#define NIC_7083D51A7DD8B064_NIC

#include "../../config.h"
#if defined(N_NET_posix_socket) && defined(N_NET_epoll)

#include "epoll_socket.h"
#include "../../../async.h"
#include "../../../ptr.h"

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
class n_foundation_dll epoll_proactor : public ref_counted
{
public:
    epoll_proactor();
    epoll_proactor(epoll_proactor &) = delete;
    epoll_proactor(const epoll_proactor &) = delete;
    inline epoll_proactor(epoll_proactor &&other) noexcept
    : h(other.h)
    {
        other.h = -1;
    }
    inline ~epoll_proactor() noexcept
    {
        kill();
    }
    
    epoll_proactor &operator = (epoll_proactor &) = delete;
    epoll_proactor &operator = (const epoll_proactor &) = delete;
    inline epoll_proactor &operator = (epoll_proactor &&other) noexcept
    {
        kill();
        h = other.h;
        other.h = -1;
        return *this;
    }
    
    inline void swap(epoll_proactor &other) noexcept
    {
        foundation::swap(h, other.h);
    }
    
    void add(epoll_socket *sock, const int flags);
    void mod(epoll_socket *sock, const int flags);
    void remove(epoll_socket *sock) noexcept;
    
    size_t update(size_t max_events);
    
private:
    void kill() noexcept;

    int h;
    size_t event_count;
    async::mutex mtx;
};

/** @} */    

}}}} // namespaces

#endif

#endif // NIC_B65CA44FF35A676D_NIC
