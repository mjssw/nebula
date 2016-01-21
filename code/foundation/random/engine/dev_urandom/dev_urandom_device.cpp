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
#include "../../config.h"

#ifdef N_RANDOM_dev_urandom

#include "dev_urandom_device.h"

namespace nebula { namespace foundation { namespace random {
//------------------------------------------------------------------------------
dev_urandom_device::dev_urandom_device()
{
    f.open("/dev/urandom");
}
//------------------------------------------------------------------------------
typename dev_urandom_device::result_type
dev_urandom_device::operator () ()
{
    result_type r;
    io::read(
        f,
        static_cast<char *>(static_cast<void *>(&r)),
        sizeof(r));
    return r;
}
//------------------------------------------------------------------------------
typename dev_urandom_device::stream_size
dev_urandom_device::read(char *buf, typename dev_urandom_device::stream_size n)
{
    return io::read(f, buf, n);
}

}}} // namespaces

#endif // N_RANDOM_dev_urandom
