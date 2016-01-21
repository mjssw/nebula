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
#ifndef NIC_5518003F9481EDC7_NIC
#define NIC_5518003F9481EDC7_NIC

#include "../../config.h"
#include "../../../dll_interface.h"
#include "../../../io.h"

namespace nebula { namespace foundation { namespace random {
/** @ingroup Foundation
  * @{ 
  * */
//------------------------------------------------------------------------------
class n_foundation_dll dev_random_device : public io::stream_base
{
public:
    using stream_size = io::_stream_size<io::ifstream>;
    using stream_offset = io::_stream_offset<io::ifstream>;
    using stream_position = io::_stream_position<io::ifstream>;
    using stream_category = tag<io::in_tag>;
    
    using result_type = unsigned long;

    dev_random_device();
    
    inline void swap(dev_random_device &other) noexcept {
        foundation::swap(f, other.f);
    }
    
    result_type operator () ();
    stream_size read(char *buf, stream_size n);
    inline io::ceof get() {
        char r;
        read(&r, 1);
        return r;
    }
    
private:
    io::ifstream f;
};

/** @} */

}}} // namespaces

#endif // NIC_5518003F9481EDC7_NIC
