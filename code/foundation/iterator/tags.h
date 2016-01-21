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
#ifndef NIC_42905EA7B85A5F31_NIC
#define NIC_42905EA7B85A5F31_NIC

#include "../utils/tag.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
struct incrementable_traversal_tag {};
struct single_pass_traversal_tag : incrementable_traversal_tag {};
struct forward_traversal_tag : single_pass_traversal_tag {};
struct bidirectional_traversal_tag : forward_traversal_tag {};
struct random_access_traversal_tag : bidirectional_traversal_tag {};
//------------------------------------------------------------------------------
struct readable_iterator_tag {};
struct writable_iterator_tag {};
struct swapable_iterator_tag {};
struct lvalue_iterator_tag {};

/** @} */

}}} // namespaces

#endif // NIC_42905EA7B85A5F31_NIC