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
#ifndef NIC_16075CC92EA40644_NIC
#define NIC_16075CC92EA40644_NIC

#include "../declval.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
  * @{ 
  * */
//------------------------------------------------------------------------------
namespace hash_detail {
//------------------------------------------------------------------------------
template <class T>
class has_result_type_ {
private:
    typedef char yes_type;
    typedef char no_type[2];

    template <class X>
    static no_type &_test(...);
    template <class X>
    static yes_type _test(typename X::result_type *);

public:
    static const bool value = sizeof(_test<T>(nullptr)) == sizeof(yes_type);
};
//------------------------------------------------------------------------------
template <class T, bool = has_result_type_<T>::value>
struct hash_result_ {
    using type = decltype(declval<T>()());
};
template <class T>
struct hash_result_<T, true> {
    using type = typename T::result_type;
};

} // hash_detail

//------------------------------------------------------------------------------
template <class T>
struct hash_result : public hash_detail::hash_result_<T>
{};

n_meta_alias(hash_result);

/** @} */

}} // namespaces

#endif // NIC_16075CC92EA40644_NIC
