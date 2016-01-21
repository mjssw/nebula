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
#ifndef NIC_69513F9CF67D7A0C_NIC
#define NIC_69513F9CF67D7A0C_NIC

#include "../config.h"
#ifdef N_REGEX_std_regex

#include "../match_result.h"
#include "../regex_error.h"
#include "../regex_options.h"

#include "../../string.h"

#include <regex>

namespace nebula { namespace foundation { namespace regex { namespace cppstd {
//------------------------------------------------------------------------------
namespace cppstd_detail {
//------------------------------------------------------------------------------
inline typename std::regex::flag_type to_syntax_option_type(
    const regex_option_type x) noexcept
{
    typename std::regex::flag_type r = typename std::regex::flag_type();
    
    if((x & regex::optimize) == regex::optimize)
        r |= std::regex::optimize;
    
    if((x & regex::grep) == regex::grep)
        r |= std::regex::grep;
    else if((x & regex::egrep) == regex::egrep)
        r |= std::regex::egrep;
    else if((x & regex::basic_posix) == regex::basic_posix)
        r |= std::regex::basic;
    else if((x & regex::extended_posix) == regex::extended_posix)
        r |= std::regex::extended;
    else if((x & regex::ecma) == regex::ecma)
        r |= std::regex::ECMAScript;
    
    if((x & regex::nosubs) == regex::nosubs)
        r |= std::regex::nosubs;
    
    return r;
}
//------------------------------------------------------------------------------
} // cppstd_detail
//------------------------------------------------------------------------------
/**
 * */
class std_regex 
{
public:  
    using string_type = string;
    
    std_regex(std_regex &) = default;
    std_regex(const std_regex &) = default;
    std_regex(std_regex &&) = default;
    
    inline std_regex(
        const char *rs, 
        regex_option_type ro = regex::default_regex_option)
    {
        try {
            rx.assign(rs, cppstd_detail::to_syntax_option_type(ro));
        } catch(...) {
            n_throw(regex_error)
            << ei_exc(current_exception());
        }
    }
    inline std_regex(
        const char *rs, 
        const size_t n,
        regex_option_type ro = regex::default_regex_option)
    {
        try {
            rx.assign(rs, n, cppstd_detail::to_syntax_option_type(ro));
        } catch(...) {
            n_throw(regex_error)
            << ei_exc(current_exception());
        }
    }
    inline std_regex(
        const string_type &rs,
        regex_option_type ro = regex::default_regex_option)
    {
        try {
            rx.assign(rs.data(), rs.size(),
                cppstd_detail::to_syntax_option_type(ro));
        } catch(...) {
            n_throw(regex_error)
            << ei_exc(current_exception());
        }
    }
    inline std_regex(
        const const_cstring rs,
        regex_option_type ro = regex::default_regex_option)
    {
        try {
            rx.assign(rs.data(), rs.size(),
                cppstd_detail::to_syntax_option_type(ro));
        } catch(...) {
            n_throw(regex_error)
            << ei_exc(current_exception());
        }
    }
    
    std_regex &operator = (const std_regex &) = default;
    std_regex &operator = (std_regex &&) = default;
    
    inline void swap(std_regex &other) noexcept {
        foundation::swap(rx, other.rx);
    }
    
    /** @attention This is not part of the public API. */
    inline std::basic_regex<char> &get_() noexcept {
        return rx; 
    }
    /** @attention This is not part of the public API. */
    inline const std::basic_regex<char> &get_() const noexcept {
        return rx; 
    }
    
    /** @attention This is not part of the public API. */
    template <class Alloc>
    inline bool search_(
        const char *first,
        const char *last,
        match_result<Alloc> &m) const
    {
        std::cmatch cm;
        try {
            std::regex_search(first, last, cm, rx);
        } catch(...) {
            n_throw(regex_error)
            << ei_exc(current_exception());
        }
        m.suffix(const_cstring(cm.suffix().first, cm.suffix().second));
        m.prefix(const_cstring(cm.prefix().first, cm.prefix().second));
        if(cm.empty())
            return false;
        m.match(const_cstring(cm[0].first, cm[0].second));
        for(size_t i = 1; i < cm.size(); ++i)
        {
            m.add_sub_match(
                cm[i].matched,
                const_cstring(cm[i].first, cm[i].second));
        }
        return true;
    }
    /** @attention This is not part of the public API. */
    inline bool search_(
        const char *first,
        const char *last) const
    {
        try {
            return std::regex_search(first, last, rx);
        } catch(...) {
            n_throw(regex_error)
            << ei_exc(current_exception());
        }
    }
    
    /** @attention This is not part of the public API. */
    template <class Alloc>
    inline bool match_(
        const char *first,
        const char *last,
        match_result<Alloc> &m) const
    {
        std::cmatch cm;
        try {
            std::regex_match(first, last, cm, rx);
        } catch(...) {
            n_throw(regex_error)
            << ei_exc(current_exception());
        }
        m.suffix(const_cstring(cm.suffix().first, cm.suffix().second));
        m.prefix(const_cstring(cm.prefix().first, cm.prefix().second));
        if(cm.empty())
            return false;
        m.match(const_cstring(cm[0].first, cm[0].second));
        for(size_t i = 1; i < cm.size(); ++i)
        {
            m.add_sub_match(
                cm[i].matched,
                const_cstring(cm[i].first, cm[i].second));
        }
        return true;
    }
    /** @attention This is not part of the public API. */
    inline bool match_(
        const char *first,
        const char *last) const
    {
        try {
            return std::regex_match(first, last, rx);
        } catch(...) {
            n_throw(regex_error)
            << ei_exc(current_exception());
        }
    }
    
private:
    std::basic_regex<char> rx;
};

}}}} // namespaces

#endif // N_REGEX_std_regex

#endif // NIC_69513F9CF67D7A0C_NIC
