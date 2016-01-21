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
#ifndef NIC_3B1BB73BDD64A79C_NIC
#define NIC_3B1BB73BDD64A79C_NIC

#include "error_condition.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 */
namespace system {
//------------------------------------------------------------------------------
class error_code;
//------------------------------------------------------------------------------
template <class Enum>
error_code make_error_code(const Enum);

//------------------------------------------------------------------------------
/** */
class error_code
{
public:
    inline error_code() noexcept
        : val(noerr),
          cat(&generic_category())
    {}
    inline error_code(errval_t v, const error_category & c) noexcept
        : val(v),
          cat(&c)
    {}
    template <class ErrorCodeEnum,
        class = enable_if<is_error_code_enum<ErrorCodeEnum>>
    >
    inline error_code(ErrorCodeEnum e)
    {
        *this = system::make_error_code(e);
    }
    inline ~error_code() noexcept {}

    inline void assign(errval_t v, const error_category & c) noexcept {
        val = v;
        cat = &c;
    }
    template<typename ErrorCodeEnum,
        class = enable_if<is_error_code_enum<ErrorCodeEnum>>
    >
    inline error_code &operator = (ErrorCodeEnum e) noexcept {
        *this = system::make_error_code(e);
        return *this;
    }
    void clear() noexcept {
        val = noerr;
        cat = &generic_category();
    }

    inline errval_t value() const noexcept { return val; }
    inline const error_category &category() const noexcept {
        n_assert(cat);
        return *cat;
    }
    error_condition default_error_condition() const noexcept {
        return cat->default_error_condition(val);
    }
    inline string message() const {
        return cat->message(val);
    }

    inline explicit operator bool () const noexcept {
        return val != noerr;
    }

    inline bool operator == (const error_code &ec) const noexcept {
        return val == ec.val && cat == ec.cat;
    }
    inline bool operator != (const error_code &ec) const noexcept {
        return val != ec.val || cat != ec.cat;
    }
    
    template <class Sink>
    inline void operator () (Sink &sink, fmt::fout_tag) const {
        fmt::fwrite(sink,
            "error_code:",
            this->category().name(),
            ':',
            fmt::dec(this->value()),
            ':',
            this->category().message(this->value()));
    }

private:
    errval_t val;
    const error_category *cat;
};

//------------------------------------------------------------------------------
inline bool
operator < (const error_code &lhs, const error_code &rhs) noexcept {
    return (lhs.category() < rhs.category())
        || (lhs.category() == rhs.category() && lhs.value() < rhs.value());
}

//------------------------------------------------------------------------------
inline bool 
operator == (const error_code &lhs, const error_condition &rhs) noexcept {
    return lhs.category().equivalent(lhs.value(), rhs)
        || rhs.category().equivalent(lhs, rhs.value());
}

//------------------------------------------------------------------------------
inline bool 
operator == (const error_condition &lhs, const error_code &rhs) noexcept {
    return rhs.category().equivalent(rhs.value(), lhs)
        || lhs.category().equivalent(rhs, lhs.value());
}

//------------------------------------------------------------------------------
inline bool 
operator != (const error_code &lhs, const error_condition &rhs) noexcept {
    return !(lhs == rhs);
}

//------------------------------------------------------------------------------
inline bool 
operator != (const error_condition &lhs, const error_code &rhs) noexcept {
    return !(lhs == rhs);
}

//------------------------------------------------------------------------------
template <class Enum>
struct make_error_code_impl {};
//------------------------------------------------------------------------------
template <class Enum>
inline error_code make_error_code(const Enum e) {
    return make_error_code_impl<Enum>::apply(e);
}

} // system

/** @} */

}} // namespaces

#endif // NIC_3B1BB73BDD64A79C_NIC