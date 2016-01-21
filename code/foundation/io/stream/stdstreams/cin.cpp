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
streamsize cin_impl_::read(char *x, streamsize n)
{
    const size_t res = fread(x, 1, n, stdin);
    if(ferror(stdin))
        n_throw(io_error) << ei_msg_c("fread() failed.");
    return res;
}
//------------------------------------------------------------------------------
ceof cin_impl_::get()
{
    const int res = getc(stdin);
    if(res == EOF) {
        if(ferror(stdin))
            n_throw(io_error) << ei_msg_c("getc() failed.");
        return io::eof;
    }
    return static_cast<char>(res);
}
//------------------------------------------------------------------------------
} // stdstreams_detail
//------------------------------------------------------------------------------
stdstreams_detail::cin_impl_ cin;

}}} // namespaces
