/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2016 lis (lis@tutanota.com)
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
#include "error.h"

namespace nebula { namespace gpg { namespace detail {
//------------------------------------------------------------------------------
class gpg_category_impl : public system::error_category
{
public:
    gpg_category_impl() = default;

    inline const char *name() const noexcept {
        return "gpg";
    }
    inline string message(system::errval_t e) const
    {
        switch(e)
        {
        case static_cast<system::errval_t>(errc::success):
            return "success";
        case static_cast<system::errval_t>(errc::general_error):
            return "general_error";
        case static_cast<system::errval_t>(errc::bad_passphrase):
            return "bad_passphrase";
        case static_cast<system::errval_t>(errc::decryption_error):
            return "decryption_error";
        case static_cast<system::errval_t>(errc::no_public_key):
            return "no_public_key";
        case static_cast<system::errval_t>(errc::unusable_public_key):
            return "unusable_public_key";
        case static_cast<system::errval_t>(errc::unusable_secret_key):
            return "unusable_secret_key";
        case static_cast<system::errval_t>(errc::expired_signature):
            return "expired_signature";
        case static_cast<system::errval_t>(errc::bad_signature):
            return "bad_signature";
        case static_cast<system::errval_t>(errc::expired_key):
            return "expired_key";
        case static_cast<system::errval_t>(errc::revoked_certificate):
            return "revoked_certificate";
        default: "unknown";
        }
    }

    inline system::error_condition default_error_condition(
        system::errval_t e) const noexcept
    {
        return system::error_condition(e, *this);
    }
};

} // detail

//------------------------------------------------------------------------------
const foundation::system::error_category &gpg_category() noexcept {
    static detail::gpg_category_impl r;
    return r;
}

}} // namespaces

