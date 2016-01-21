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
#ifdef N_CHRONO_hrc_clock_gettime

#include "../config.h"
#include <time.h>

namespace nebula { namespace foundation { namespace chrono {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
n_chrono_inline 
typename high_resolution_clock::duration_type high_resolution_clock::now()
{
    system::error_code ec;
    const typename high_resolution_clock::duration_type res 
        = high_resolution_clock::now(ec);
    if(ec)
        n_throw(system::system_error) << system::ei_error_code(ec);
    return res;
}
//------------------------------------------------------------------------------
n_chrono_inline 
typename high_resolution_clock::duration_type high_resolution_clock::now(
    system::error_code &ec) noexcept
{
    using dur_t = typename high_resolution_clock::duration_type;
    ::timespec t;
    if(0 != ::clock_gettime(CLOCK_REALTIME, &t))
        ec = system::error_code(errno, system::system_category());
    return dur_t(
        static_cast<typename dur_t::value_type>(t.tv_sec) 
        * dur_t::period::den 
        + t.tv_nsec);
}

/** @} */

}}} // namespaces

#endif
