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
#ifndef NIC_F3AD208A806A0451_NIC
#define NIC_F3AD208A806A0451_NIC

#include "../../ptr.h"
#include "../../swap.h"
#include "../../move.h"

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
template <class Backend>
class async_service
{
public:
    inline async_service()
    : be(new Backend())
    {}
        
    async_service(async_service &) = delete;
    async_service(const async_service &) = delete;
    async_service(async_service &&) = default;
    
    async_service &operator = (async_service &) = delete;
    async_service &operator = (const async_service &) = delete;
    async_service &operator = (async_service &&) = default;
    
    inline void swap(async_service &other) noexcept {
        foundation::swap(be, other.be);
    }
    
    inline size_t update(const size_t n)
    {
        return be->update(n);
    }
    
private:
    template <class BackendPtr>
    inline async_service(BackendPtr &&bp)
    : be(foundation::forward<BackendPtr>(bp))
    {}
    
    intrusive_ptr<Backend> backend_() & {
        return be;
    }
    intrusive_ptr<Backend> backend_() && noexcept {
        return move(be);
    }
    intrusive_ptr<Backend> backend_() const & {
        return be;
    }

    intrusive_ptr<Backend> be;
    
    template <class Endpoint, class AsyncServ, class Base>
    friend class async_stream_socket;
    template <class Endpoint, class AsyncServ, class Base>
    friend class async_stream_socket_acceptor;
    template <class Endpoint, class AsyncServ, class Base>
    friend class async_dgram_socket;
};

/** @} */    

}}}} // namespaces

#endif // NIC_F3AD208A806A0451_NIC
