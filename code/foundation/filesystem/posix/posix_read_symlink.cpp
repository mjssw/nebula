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
#include "../config.h"
#ifdef N_FILESYSTEM_posix_readlink

#include "../path.h"
#include "../exception.h"

#include <unistd.h>

namespace nebula { namespace foundation { namespace filesystem {
//------------------------------------------------------------------------------
path read_symlink(const path &p)
{
    string buf;
    buf.resize(4096);
    
    const ::ssize_t r = ::readlink(p.c_str(), buf.data(), buf.size());
    if(r == -1)
    {
        n_throw(system::system_error)
            << ei_msg_c("readlink() failed.")
            << ei_path(p)
            << system::ei_error_code(system::error_code(
                errno, system::system_category()));
    }
    
    buf.resize(r);
    
    return path(foundation::move(buf));
}

}}} // namespaces

#endif // N_FILESYSTEM_posix_stat
