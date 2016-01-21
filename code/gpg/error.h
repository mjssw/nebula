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
#ifndef NIC_3812E2B2A3943B93_NIC
#define NIC_3812E2B2A3943B93_NIC

#include "config.h"

namespace nebula { namespace gpg {
/** @ingroup GPG
 * @{
 * */
//------------------------------------------------------------------------------
enum class errc
{
    success = GPG_ERR_NO_ERROR,
    general_error = GPG_ERR_GENERAL,
    bad_passphrase = GPG_ERR_BAD_PASSPHRASE,
    decryption_error = GPG_ERR_DECRYPT_FAILED,
    no_public_key = GPG_ERR_NO_PUBKEY,
    unusable_public_key = GPG_ERR_UNUSABLE_PUBKEY,
    unusable_secret_key = GPG_ERR_UNUSABLE_SECKEY,
    expired_signature = GPG_ERR_SIG_EXPIRED,
    bad_signature = GPG_ERR_BAD_SIGNATURE,
    expired_key = GPG_ERR_KEY_EXPIRED,
    revoked_certificate = GPG_ERR_CERT_REVOKED
};

//------------------------------------------------------------------------------
extern const foundation::system::error_category & n_gpg_dll
gpg_category() noexcept;

/** @} */

}} // namespaces

//------------------------------------------------------------------------------
n_register_error_code_enum(::nebula::gpg::errc,
    ::nebula::gpg::gpg_category());
n_register_error_condition_enum(::nebula::gpg::errc,
    ::nebula::gpg::gpg_category());

#endif // NIC_3812E2B2A3943B93_NIC

