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
#include "posix_protocol_server.h"
#ifdef N_NET_posix_netdb

#include "../../format.h"
#include "../exception.h"

#include <netdb.h>

namespace nebula { namespace foundation { namespace net { namespace posix {
//------------------------------------------------------------------------------
protocol_type protocol_server::get(const char *name, const size_t n) const
{
    string s(name, n);
    return this->get(s.c_str());
}
//------------------------------------------------------------------------------
protocol_type protocol_server::get(const char *name) const
{
    const ::protoent *pe = ::getprotobyname(name);
    if(!pe)
    {
        n_throw(network_error)
            << ei_msg(fmt::to_string("getprotobyname() failed: name"));
    }
    return pe->p_proto;
}

}}}} // namespaces

#endif // N_NET_posix_netdb
