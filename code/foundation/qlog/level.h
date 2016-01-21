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
#ifndef NIC_377ABFD789A1337A_NIC
#define NIC_377ABFD789A1337A_NIC

#include "../format.h"

namespace nebula { namespace foundation { namespace qlog {
//------------------------------------------------------------------------------
enum class level : int
{
    none,
    fatal,
    alert,
    critical,
    error,
    warning,
    notice,
    info,
    debug,
    off
};

//------------------------------------------------------------------------------
inline const char *to_cstr(const level lvl) noexcept
{
    switch(lvl)
    {
    case level::none:       return "none";
    case level::fatal:      return "fatal";
    case level::alert:      return "alert";
    case level::critical:   return "critical";
    case level::error:      return "error";
    case level::warning:    return "warning";
    case level::notice:     return "notice";
    case level::info:       return "info";
    case level::debug:      return "debug";
    default:                return "off";
    }
}

} // qlog

namespace fmt {
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<qlog::level>
{
    template <class Sink>
    inline static void apply(Sink &&s, qlog::level lvl)
    {
        const char *str = qlog::to_cstr(lvl);
        io::write(s, str, foundation::strlen(str));
    }
};

} // fmt

}} // namespaces

#endif // NIC_377ABFD789A1337A_NIC
