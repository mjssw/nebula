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
#ifndef NIC_15F768DC23FD11D5_NIC
#define NIC_15F768DC23FD11D5_NIC

#include "utils.h"

namespace nebula { namespace foundation { namespace utf {
namespace unistring {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class String>
inline void to_upper(
     const char *s, const size_t n,
     const char *iso639_lang,
     const normal_form nf,
     String &res)
{
    size_t n_out = 0;
    
    char *r = from_ustr(
        ::u8_toupper(
            to_ustr(s),
            n,
            iso639_lang,
            to_uninorm_t(nf),
            nullptr,
            &n_out));
    
    if(r == nullptr)
        n_throw(utf_error);
        
    n_scope_exit(&) {
        ::free(r);
    };
    
    res.append(r, n_out);
}

//------------------------------------------------------------------------------
template <class String>
inline void to_lower(
     const char *s, const size_t n,
     const char *iso639_lang,
     const normal_form nf,
     String &res)
{
    size_t n_out = 0;
    
    char *r = from_ustr(
        ::u8_tolower(
            to_ustr(s),
            n,
            iso639_lang,
            to_uninorm_t(nf),
            nullptr,
            &n_out));
    
    if(r == nullptr)
        n_throw(utf_error);
        
    n_scope_exit(&) {
        ::free(r);
    };
    
    res.append(r, n_out);
}

//------------------------------------------------------------------------------
template <class String>
inline void to_title(
     const char *s, const size_t n,
     const char *iso639_lang,
     const normal_form nf,
     String &res)
{
    size_t n_out = 0;
    
    char *r = from_ustr(
        ::u8_totitle(
            to_ustr(s),
            n,
            iso639_lang,
            to_uninorm_t(nf),
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

#endif // NIC_15F768DC23FD11D5_NIC

