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
#include "demangle_type_info_name.h"

#include "../exception.h"

#ifdef N_COMPILER_GNUC
/* Used for abi::__cxa_demangle() in demangle_type_info_name(). */
#    include <cxxabi.h>
#endif // N_COMPILER_GNUC

namespace nebula { namespace foundation {
//------------------------------------------------------------------------------
string demangle_type_info_name(const char *_in)
{
#   ifdef N_COMPILER_GNUC
    int status = 0;
    char *r = abi::__cxa_demangle(_in, nullptr, nullptr, &status);
    switch(status)
    {
    case 0:
        break;
    case -1:
        n_throw(bad_alloc);
        break;
    case -2:
        n_throw(logic_error)
            << ei_msg_c("Input name is invalid!");
        break;
    case -3:
    default:
        // Dragons!
        n_throw(exception);
        break;
    }
    try {
        string res(r);
        ::free(r);
        return res;
    } catch(...) {
        ::free(r);
        throw;
    }
#   else
    /* Implement name mangling here for other compilers if needed. */
    return _in;
#   endif // N_COMPILER_GNUC
}

}} // namespaces