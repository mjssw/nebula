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
#ifndef NIC_BA5A59C2633AB0C6_NIC
#define NIC_BA5A59C2633AB0C6_NIC

#include "fwrite_impl_fwd.h"
#include "../writer/dec.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<short>
{
    template <class Sink>
    inline static void apply (Sink &sink, const short x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<unsigned short>
{
    template <class Sink>
    inline static void apply (Sink &sink, const unsigned short x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};

//------------------------------------------------------------------------------
template <>
struct fwrite_impl<int>
{
    template <class Sink>
    inline static void apply (Sink &sink, const int x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<unsigned int>
{
    template <class Sink>
    inline static void apply (Sink &sink, const unsigned int x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};

//------------------------------------------------------------------------------
template <>
struct fwrite_impl<long>
{
    template <class Sink>
    inline static void apply (Sink &sink, const long x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<unsigned long>
{
    template <class Sink>
    inline static void apply (Sink &sink, const unsigned long x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};

//------------------------------------------------------------------------------
template <>
struct fwrite_impl<long long>
{
    template <class Sink>
    inline static void apply (Sink &sink, const long long x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<unsigned long long>
{
    template <class Sink>
    inline static void apply (Sink &sink, const unsigned long long x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};

/** @} */

}}} // namespaces

#endif // NIC_BA5A59C2633AB0C6_NIC