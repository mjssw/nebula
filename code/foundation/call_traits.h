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
#ifndef NIC_DCE0C38785B9ECBC_NIC
#define NIC_DCE0C38785B9ECBC_NIC

#include "call_traits/initial.h"
#include "call_traits/param.h"
#include "call_traits/ref.h"
#include "call_traits/cref.h"
#include "call_traits/value.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{ 
 * */
//------------------------------------------------------------------------------
/** @ingroup Foundation
 * The call_traits library is used to make handling parameters in function
 * templates a bit easier.
 * 
 * The problem this library tries to solve is the one arising from the use
 * of rvalue references as function parameter types. Consider the following
 * function template.
 * @code
 * template <class T>
 * void foo(T &&x, const T &y);
 * int i;
 * foo(2, 10); // ok
 * foo(i, 10); // fail
 * @endcode
 * Here is where this little library comes into play.
 * @code
 * template <class T>
 * void foo(T &&x, typename ctraits::param<T>::type y);
 * int i;
 * foo(i, 10); // ok now
 * @endcode
 * 
 * Please take a look at the individual metafunctions for further details.
 * */
namespace ctraits {
}}} // namespaces

#endif // NIC_DCE0C38785B9ECBC_NIC