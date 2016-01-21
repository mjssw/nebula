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
#ifndef NIC_214E4A8F9AC655AA_NIC
#define NIC_214E4A8F9AC655AA_NIC

#include "../config.h"
#ifdef N_NET_posix_netdb

#include "../defs.h"
#include "../../dll_interface.h"
#include "../../string.h"

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
class n_foundation_dll protocol_server
{
public:
    protocol_server() = default;
    protocol_server(protocol_server &) = delete;
    protocol_server(const protocol_server &) = delete;
    protocol_server(protocol_server &&) = default;
    
    protocol_server &operator = (protocol_server &) = delete;
    protocol_server &operator = (const protocol_server &) = delete;
    protocol_server &operator = (protocol_server &&) = default;
    
    template <class String>
    inline protocol_type get(const String &name) const
    {
        return get(name.data(), name.size());
    }
    inline protocol_type get(const string &name) const {
        this->get(name.c_str());
    }
    protocol_type get(const char *name, const size_t n) const;
    protocol_type get(const char *name) const;
};

/** @} */

}}}} // namespaces

#endif // N_NET_posix_netdb

#endif // NIC_214E4A8F9AC655AA_NIC
