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
#ifndef NIC_65CB9173799CE576_NIC
#define NIC_65CB9173799CE576_NIC

#include "config.h"
#include "../dll_interface.h"
#include "../string.h"
#include "../cstring.h"
#include "../format/tags.h"
#include "../io/common.h"

namespace nebula { namespace foundation { namespace filesystem {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** This class represents a path in posix format regardless of the underlying
 * system.
 * @note If you really need fast string operations then consider using string
 * directly instead of path - this class is not designed for such a case.
 * @internal Not a template, so we can use it accross code units.
 * */
class n_foundation_dll path
{
public:
    path() = default;
    path(const path &) = default;
    path(path &&) = default;
    
    inline path(const char *s_)
    : s(s_)
    {}
    inline path(const string &s_)
    : s(s_)
    {}
    inline path(const const_cstring &s_)
    : s(s_)
    {}
    
    path &operator = (const path &) = default;
    path &operator = (path &&) = default;
    
    inline void swap(path &other) noexcept {
        foundation::swap(s, other.s);
    }
    
    /** @return Path as a string in posix format. */
    inline const string &str() const noexcept {
        return s;
    }
    /** @return Path as a c-style string in posix format. */
    inline const char *c_str() const noexcept {
        return s.c_str();
    }
    
    inline bool empty() const noexcept {
        return s.empty();
    }
    
    inline path &operator /= (const path &p)
    {
        s.push_back('/');
        s.append(p.str());
        return *this;
    }
    inline path operator / (const path &p) const
    {
        path r(*this);
        r /= p;
        return r;
    }
    
    inline path &operator += (const path &p)
    {
        s.append(p.str());
        return *this;
    }
    inline path operator + (const path &p) const
    {
        path r(*this);
        r += p;
        return r;
    }
    
    inline bool operator == (const path &p) const noexcept {
        return s == p.s;
    }
    inline bool operator != (const path &p) const noexcept {
        return s != p.s;
    }
    inline bool operator < (const path &p) const noexcept {
        return s < p.s;
    }
    inline bool operator <= (const path &p) const noexcept {
        return s <= p.s;
    }
    inline bool operator > (const path &p) const noexcept {
        return s > p.s;
    }
    inline bool operator >= (const path &p) const noexcept {
        return s >= p.s;
    }
    
    template <class S>
    inline void operator () (S &s_, fmt::fout_tag) const
    {
        io::write(s_, s.data(), s.size());
    }
    
private:
    string s;
};

/** @} */

}}}

#endif // NIC_65CB9173799CE576_NIC
