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
#ifndef NIC_239FF4DB6824A73C_NIC
#define NIC_239FF4DB6824A73C_NIC

#include "exception.h"
#include "../system_error.h"
#include "../format.h"

namespace nebula { namespace foundation { namespace net {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
enum class errc : int
{
    unknown = -1,
    success = 0,
    
    address_in_use,
    
    connection_refused,
    connection_aborted,
    connection_reset,
    
    network_down,
    network_unreachable,
    network_reset,
    
    host_unreachable,
    
    again,
    timedout
};

//------------------------------------------------------------------------------
extern const system::error_category & n_foundation_dll 
network_category() noexcept;

}}} // namespaces

//------------------------------------------------------------------------------
n_register_error_code_enum(::nebula::foundation::net::errc,
    ::nebula::foundation::net::network_category());
n_register_error_condition_enum(::nebula::foundation::net::errc,
    ::nebula::foundation::net::network_category());

namespace nebula { namespace foundation { namespace fmt {
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<net::errc>
{
    template <class Sink>
    inline static void apply (Sink &sink, const net::errc e)
    {
        fmt::fwrite(sink, system::error_condition(e));
    }
};

}}} // namespaces

#endif // NIC_239FF4DB6824A73C_NIC
