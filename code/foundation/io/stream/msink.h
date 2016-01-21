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
#ifndef NIC_E8CECC56F0CCBD9F_NIC
#define NIC_E8CECC56F0CCBD9F_NIC

#include "stream.h"
#include "../../declval.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
/** This is a very minimalistic stream designed to easily write into a container
 * by appending data. In order for this to work, the container type must support
 * the two member functions append() and push_back().
 * */
template <class Container>
class msink : public stream_base
{
public:
    using container_type = Container;
    using stream_size = streamsize;
    using stream_offset = streamoff;
    using stream_position = streampos;
    using stream_category = tag<out_tag, flush_tag>;
    
    msink() = default;
    msink(msink &) = default;
    msink(const msink &) = default;
    msink(msink &&) = default;
    
    template <class ... X>
    inline msink(X && ... x)
    : c(foundation::forward<X>(x)...)
    {}
    
    msink &operator = (msink &) = default;
    msink &operator = (const msink &) = default;
    msink &operator = (msink &&) = default;
    
    inline void swap(msink &other)
    noexcept(noexcept(foundation::declval<container_type>()
        .swap(foundation::declval<container_type>())))
    {
        c.swap(other.c);
    }
    
    inline void write(const char *x, stream_size n) final {
        c.append(x, x+n);
    }
    inline void put(char c_) final {
        c.push_back(c_);
    }
    
    inline void swap_container(container_type &c_)
    noexcept(noexcept(c_.swap(c_)))
    {
        c.swap(c_);
    }
    
    inline container_type &container() & noexcept {
        return c;
    }
    inline container_type container() && noexcept {
        return move(c);
    }
    inline const container_type &container() const & noexcept {
        return c;
    }
    
private:
    container_type c;
};

/** @} */

}}} // namespaces

#endif // NIC_E8CECC56F0CCBD9F_NIC
