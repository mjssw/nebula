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
#ifndef NIC_BACE5472F76F05BF_NIC
#define NIC_BACE5472F76F05BF_NIC

#include "traits.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace detail {
//------------------------------------------------------------------------------
template <class T>
class _is_iterator {
private:
    typedef char yes_type;
    typedef char no_type[2];
    
    template <class X>
    inline constexpr static bool is_ptr() noexcept
    {
        return is_pointer<X>::value
            && !is_function<typename remove_pointer<X>::type>::value; 
    };

    template <class X>
    static no_type &_test(...);
    template <class X,
        typename disable_if_c<is_ptr<X>(), int>::type = 0>
    static yes_type _test(typename X::iterator_category *);
    template <class X,
        typename enable_if_c<is_ptr<X>(), int>::type = 0>
    static yes_type _test(void *);

public:
    static const bool value = sizeof(_test<T>(nullptr)) == sizeof(yes_type);
};
//------------------------------------------------------------------------------
} // detail
//------------------------------------------------------------------------------
/** Meta-function to test if a type is an iterator. Works with std iterators too.
 * */
template <class T>
struct is_iterator
    : public integral_constant<bool, detail::_is_iterator<T>::value>
{};

/** @} */

}}} // namespaces

#endif // NIC_BACE5472F76F05BF_NIC