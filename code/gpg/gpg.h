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
#ifndef NIC_BCE37A3FD6CADFCD_NIC
#define NIC_BCE37A3FD6CADFCD_NIC

#include "context.h"

namespace nebula {
/** @ingroup GPG
 * @{
 * */
//------------------------------------------------------------------------------
/** Simple wrapper of libgpgme.
 *
 *  Some comments are verbatim copies of the official manual which can be
 *  found here
 *  @see https://www.gnupg.org/documentation/manuals/gpgme/
 * */
namespace gpg {

namespace keylist_mode = detail::keylist_mode;
using public_key_algorithm = detail::public_key_algorithm;
using hash_algorithm = detail::hash_algorithm;
using subkey = detail::subkey;
using subkey_iterator = detail::subkey_iterator;
using subkey_range = detail::subkey_range;
using key_signature = detail::key_signature;
using key_signature_iterator = detail::key_signature_iterator;
using key_signature_range = detail::key_signature_range;
using user_id = detail::user_id;
using user_id_iterator = detail::user_id_iterator;
using user_id_range = detail::user_id_range;
using key = detail::key;
using signature_info = detail::signature_info;
using context = detail::context;

} // gpg

/** @} */

} // namespaces

#endif // NIC_BCE37A3FD6CADFCD_NIC

