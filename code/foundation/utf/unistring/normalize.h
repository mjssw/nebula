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
#ifndef NIC_F9C2F08C6F04D57F_NIC
#define NIC_F9C2F08C6F04D57F_NIC

#include "utils.h"
#include "../../scope_exit.h"

namespace nebula { namespace foundation { namespace utf {
namespace unistring {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class String>
inline void normalize(
     const char *s, const size_t n,
     const normal_form nf,
     String &res)
{
    size_t n_out = 0;
    
    char *r = from_ustr(
        ::u8_normalize(
            to_uninorm_t(nf),
            to_ustr(s),
            n,
            nullptr,
            &n_out));
    
    if(r == nullptr)
        n_throw(utf_error);
        
    n_scope_exit(&) {
        ::free(r);
    };
    
    res.append(r, n_out);
}

/** @} */

}}}} // namespaces

#endif // NIC_F9C2F08C6F04D57F_NIC

