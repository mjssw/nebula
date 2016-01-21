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
#ifndef NIC_54E5545180F6A509_NIC
#define NIC_54E5545180F6A509_NIC

#include "duration.h"
#include "traits.h"
#include "config.h"
#include "../system_error.h"

namespace nebula { namespace foundation { namespace chrono {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
struct n_foundation_dll high_resolution_clock
{
#   ifdef N_CHRONO_hrc_clock_gettime
    using duration_type = chrono::duration<long, nano>;
#   endif
    using is_monotonic = false_type;
    
    static duration_type now();
    static duration_type now(system::error_code &ec) noexcept;
};

/** @} */

}}} // namespaces

#ifdef N_CHRONO_INLINE
#   include "high_resolution_clock/high_resolution_clock_clock_gettime.h"
#endif

#endif // NIC_54E5545180F6A509_NIC