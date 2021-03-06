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
#ifndef NIC_F7E60C15FF200486_NIC
#define NIC_F7E60C15FF200486_NIC

#include "../config.h"

#ifdef N_RANDOM_dev_random
#include "dev_random/dev_random_device.h"
#endif

namespace nebula { namespace foundation { namespace random {
/** @ingroup Foundation
  * @{ 
  * */
//------------------------------------------------------------------------------
#ifdef N_RANDOM_dev_random
using random_device = dev_random_device;
#endif

/** @} */

}}} // namespaces

#endif // NIC_F7E60C15FF200486_NIC