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
#ifndef NIC_5FE878C246D14513_NIC
#define NIC_5FE878C246D14513_NIC

#include "stream.h"
#include "../../dll_interface.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace stdstreams_detail {
//------------------------------------------------------------------------------
class n_foundation_dll cin_impl_ : public stream_base
{
public:
    using stream_size = streamsize;
    using stream_offset = streamoff;
    using stream_position = streampos;
    using stream_category = tag<in_tag>;
    
    stream_size read(char *x, stream_size n) final;
    ceof get() final;
};
//------------------------------------------------------------------------------
class n_foundation_dll cout_impl_ : public stream_base
{
public:
    using stream_size = streamsize;
    using stream_offset = streamoff;
    using stream_position = streampos;
    using stream_category = tag<out_tag, flush_tag>;
    
    ~cout_impl_() noexcept;
    
    void write(const char *x, stream_size n) final;
    void put(char) final;
    void flush() final;
};
//------------------------------------------------------------------------------
class n_foundation_dll cerr_impl_ : public stream_base
{
public:
    using stream_size = streamsize;
    using stream_offset = streamoff;
    using stream_position = streampos;
    using stream_category = tag<out_tag, direct_tag>;
        
    void write(const char *x, stream_size n) noexcept final;
    void put(char) noexcept final;
};
//------------------------------------------------------------------------------
} // stdstreams_detail
//------------------------------------------------------------------------------
extern stdstreams_detail::cin_impl_ n_foundation_dll cin;
extern stdstreams_detail::cout_impl_ n_foundation_dll cout;
extern stdstreams_detail::cerr_impl_ n_foundation_dll cerr;

/** @} */

}}} // namespaces

#endif // NIC_5FE878C246D14513_NIC
