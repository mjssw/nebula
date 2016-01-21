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
#ifndef NIC_DBCB8BB267E3540B_NIC
#define NIC_DBCB8BB267E3540B_NIC

#include "../traits.h"

#include "../../../format.h"

namespace nebula { namespace foundation { namespace math { namespace vec {
/** @ingroup Foundation
 * @{
 * */
namespace vec_fmt_detail {
//------------------------------------------------------------------------------
template <class Vector>
class vector_writer_impl
{
public:
    inline vector_writer_impl(const Vector &x) noexcept
    : v(x)
    {}
    
    template <class Stream>
    inline void operator () (Stream &s, fmt::fout_tag) const
    {
        n_static_assert(vec::_size<Vector>::value > 0, "");
        
        fmt::fwrite(s, '(', v[0]);
        for(size_t i = 1; i < vec::_size<Vector>::value; ++i)
            fmt::fwrite(s, ", ", v[i]);
        io::put(s, ')');
    }
    
private:
    const Vector &v;
};

} // vec_fmt_detail

//------------------------------------------------------------------------------
template <class Vector>
inline vec_fmt_detail::vector_writer_impl<Vector> vector_writer(
    const Vector &v)
{
    return vec_fmt_detail::vector_writer_impl<Vector>(v);
}

/** @} */

}}}} // namespaces

#endif // NIC_DBCB8BB267E3540B_NIC

