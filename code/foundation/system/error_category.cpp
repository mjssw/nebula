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
#include "error_code.h"
#include "enum_utils.h"
#include "map_windows_error.h"
#include "../scope_exit.h"

#ifdef N_API_WINDOWS
#   include <windows.h>
#endif

#ifdef N_API_POSIX
#   include <string.h> // strerror_r
#endif

//------------------------------------------------------------------------------
namespace nebula { namespace foundation { namespace system {
//------------------------------------------------------------------------------
error_condition error_category::default_error_condition(
    errval_t e) const noexcept 
{
    return error_condition(e,*this);
}
//------------------------------------------------------------------------------
bool error_category::equivalent(
    errval_t e, const error_condition &c) const noexcept
{
    return this->default_error_condition(e) == c;
}
//------------------------------------------------------------------------------
bool error_category::equivalent(
    const error_code &e, errval_t c) const noexcept 
{
    return *this == e.category() && e.value() == c;
}
//------------------------------------------------------------------------------
namespace detail {
//------------------------------------------------------------------------------
/** @ingroup Foundation */
class generic_category_impl : public error_category
{
public:
    inline generic_category_impl() noexcept {}
    inline ~generic_category_impl() noexcept {}

    inline const char *name() const noexcept {
        return "generic";
    }
    inline string message(errval_t e) const {
        return detail::to_cstr(detail::to_errc(e));
    }
};
//------------------------------------------------------------------------------
/** @ingroup Foundation */
class system_category_impl : public error_category
{
public:
    inline system_category_impl() noexcept {}
    inline ~system_category_impl() noexcept {}

    inline const char *name() const noexcept {
        return "system";
    }
    inline string message(errval_t e) const {
#       ifdef N_API_WINDOWS
        
        LPVOID msg_buf = NULL;
        const DWORD r = ::FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            e,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            (LPSTR) &msg_buf,
            0,
            NULL
        );

        n_scope_exit(&) { ::LocalFree(msg_buf); };

        if (r)
            return static_cast<LPCSTR>(msg_buf);
        
#       else
        
        locale_t loc = ::newlocale(LC_ALL, "C", (locale_t) 0);
        if(loc == (locale_t) 0)
            return "Failed to get an error description - newlocale() failed.";
        n_scope_exit(&) { ::freelocale(loc); };
        errno = 0;
        const char *s = ::strerror_l(e, loc);
        if(errno != 0)
            return "Failed to get an error description - strerror_l() failed.";
        return s;
        
#       endif
        
        /* Couldn't translate the message. */
        return "No error description available.";
    }

    inline error_condition default_error_condition(errval_t e) const noexcept {
#       ifdef N_API_WINDOWS
        const errc r = detail::map_windows_error(e);
#       else
        const errc r = detail::to_errc(e);
#       endif

        return system::make_error_condition(r);
    }
};

} // detail

//------------------------------------------------------------------------------
const error_category &generic_category() noexcept {
    static detail::generic_category_impl r;
    return r;
}
//------------------------------------------------------------------------------
const error_category &system_category() noexcept {
    static detail::system_category_impl r;
    return r;
}

}}} // namespaces