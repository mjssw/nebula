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
#include "error.h"

namespace nebula { namespace foundation { namespace net {
//------------------------------------------------------------------------------
/** @ingroup Foundation */
class network_category_impl : public system::error_category
{
public:
    inline network_category_impl() noexcept {}
    inline ~network_category_impl() noexcept {}

    inline const char *name() const noexcept {
        return "network";
    }
    inline string message(system::errval_t e) const {        
        switch(e)
        {
        case static_cast<int>(net::errc::success):
            return "success";
            
        case static_cast<int>(net::errc::address_in_use):
            return "address_in_use";
            
        case static_cast<int>(net::errc::connection_refused):
            return "connection_refused";
        case static_cast<int>(net::errc::connection_aborted):
            return "connection_aborted";
        case static_cast<int>(net::errc::connection_reset):
            return "connection_reset";
            
        case static_cast<int>(net::errc::network_down):
            return "network_down";
        case static_cast<int>(net::errc::network_unreachable):
            return "network_unreachable";
        case static_cast<int>(net::errc::network_reset):
            return "network_reset";
            
        case static_cast<int>(net::errc::host_unreachable):
            return "host_unreachable";
            
        case static_cast<int>(net::errc::again):
            return "again";
        case static_cast<int>(net::errc::timedout):
            return "timedout";
            
        default: break;
        }
        
        return "unknown";
    }

    inline system::error_condition default_error_condition(
        system::errval_t e) const noexcept
    {
        return system::error_condition(e, network_category());
    }
};

//------------------------------------------------------------------------------
const system::error_category &network_category() noexcept {
    static network_category_impl x;
    return x;
}

}}} // namespaces
