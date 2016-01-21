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
#ifdef N_FILESYSTEM_posix_realpath

#include "../path.h"
#include "../exception.h"
#include "../../scope_exit.h"

#include <limits.h>
#include <stdlib.h>

namespace nebula { namespace foundation { namespace filesystem {
//------------------------------------------------------------------------------
path canonical(const path &p)
{    
    char *r = ::realpath(p.c_str(), nullptr);
    
    if(r == nullptr)
    {
        n_throw(system::system_error)
            << ei_msg_c("realpath() failed.")
            << ei_path(p)
            << system::ei_error_code(system::error_code(
                errno, system::system_category()));
    }
    
    n_scope_exit(&) {
        ::free(r);
    };
    
    return path(r);
}

}}} // namespaces

#endif // N_FILESYSTEM_posix_stat