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
#include "../../exception.h"
#include "../stdstreams.h"
#include <stdio.h>

namespace nebula { namespace foundation { namespace io {
//------------------------------------------------------------------------------
namespace stdstreams_detail {
//------------------------------------------------------------------------------
cout_impl_::~cout_impl_() noexcept {
    /* Try a flush, ignore errors. */
    fflush(stdout);
}
//------------------------------------------------------------------------------
void cout_impl_::write(const char *x, streamsize n)
{
    while(n > 0)
    {
        const size_t r = fwrite(x, 1, n, stdout);
        if(ferror(stdout))
            n_throw(io_error) << ei_msg_c("fwrite() failed.");
        x += r;
        n -= r;
    }
}
//------------------------------------------------------------------------------
void cout_impl_::put(char x)
{
    if(EOF == fputc(x, stdout))
        n_throw(io_error) << ei_msg_c("fputc() failed.");
}
//------------------------------------------------------------------------------
void cout_impl_::flush() {
    if(fflush(stdout))
        n_throw(io_error) << ei_msg_c("fflush() failed.");
}
//------------------------------------------------------------------------------
} // stdstreams_detail
//------------------------------------------------------------------------------
stdstreams_detail::cout_impl_ cout;

}}} // namespaces
