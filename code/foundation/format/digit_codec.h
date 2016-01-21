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
#ifndef NIC_46B8CED65E078B2F_NIC
#define NIC_46B8CED65E078B2F_NIC

#include "../exception.h"
#include "../meta.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** A simple policy to map the digits "0123456789ABCDEF" to numbers and vice 
 * versa.
 * 
 * This is a 'more or less' bijective map of the form char<->unsigned, 
 * where the right direction decodes a glyph (which must fit into a char) and
 * returns the respective numeric value and the left direction encodes number
 * to a glyph.
 * */
struct digit_codec
{
    /** The number of different digits that can be converted. */
    using size = meta::size_t_<16>;
    
    /** Maps a number to a digit. 
     * @throw out_of_range If x >= size::value.
     * */
    inline static char encode(unsigned x) {
        static const char *digits = "0123456789ABCDEF";
        if(x >= size::value)
            n_throw(out_of_range);
        return digits[x];
    }
    /** Maps a number to a digit.
     * @throw out_of_range If the character couldn't be mapped.
     * */
    inline static unsigned decode(char x) {
        switch(x)
        {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
        case 'A':
            return 10;        
        case 'b':
        case 'B':
            return 11;
        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;
        default:
            n_throw(out_of_range);
            return 0;
        }
    }
};

/** @} */

}}} // namespaces

#endif // NIC_46B8CED65E078B2F_NIC
