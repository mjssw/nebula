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
#ifndef NIC_312A600C6FFCC350_NIC
#define NIC_312A600C6FFCC350_NIC

#include "../../io.h"
#include "../../defs.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace fmt_detail {
//------------------------------------------------------------------------------
struct endl_
{
    template <class Sink>
    inline void operator () (Sink &sink, fout_tag) const {
        io::put(sink, '\n');
    }
};
//------------------------------------------------------------------------------
} // fmt_detail
//------------------------------------------------------------------------------
n_unused_variable(static fmt_detail::endl_, endl);

/** @} */

}}} // namespaces

#endif // NIC_312A600C6FFCC350_NIC