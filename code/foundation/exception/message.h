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
/** @file message.h 
 * This file requires a lot of dependencies. 
 * */
#ifndef NIC_90255C938CE66FFC_NIC
#define NIC_90255C938CE66FFC_NIC

#include "exception.h"
#include "../format.h"
#include "../io.h"
#include "../string.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
extern string n_foundation_dll diagnostic_information(const exception &e);
extern string n_foundation_dll diagnostic_information(exception_ptr e);
//------------------------------------------------------------------------------
template <class Tag, class T>
inline string error_info<Tag, T>::message() const {
    io::msink<string> ss;
    fmt::fwrite(ss, *this);
    return foundation::move(ss.container());
}
//------------------------------------------------------------------------------
namespace fmt {
//------------------------------------------------------------------------------
template <class Tag, class T>
struct fwrite_impl<error_info<Tag, T>>
{
    template <class Sink>
    inline static void apply(Sink &s, const error_info<Tag, T> &x)
    {
        fmt::fwrite(s, x.value());
    }
};
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<exception_ptr>
{
    template <class Sink>
    inline static void apply(Sink &s, const exception_ptr &x)
    {
        fmt::fwrite(s, foundation::diagnostic_information(x));
    }
};
//------------------------------------------------------------------------------
} // namespace fmt

/** @} */

}} // namespaces

#endif // NIC_90255C938CE66FFC_NIC
