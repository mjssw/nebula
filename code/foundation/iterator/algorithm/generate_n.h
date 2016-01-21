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
#ifndef NIC_772776740BF4F418_NIC
#define NIC_772776740BF4F418_NIC

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct generate_n_impl
{
    template <class S, class F_>
    inline static void apply(I first, const S &n, F_ &&f)
    {
        for(S i = 0; i < n; ++i)
            *first++ = f();
    }
};
//------------------------------------------------------------------------------
/** Replaces all elements in the [first, first+n) with the result of f() in
 * consecutive order.
 * @param I Must be an incrementable iterator.
 * @param f A function which takes no arguments and returns a type implicitely
 * convertible to the value_type of the range in question.
 * @return void
 * @return Weak exception safety - elements are replaces until the functor
 * fails with an exception.
 * */
template <class I, class S, class F>
inline void generate_n(I first, const S &n, F &&f)
{
    generate_n_impl<I>::apply(first, n, f);
}

/** @} */

}}} // namespaces

#endif // NIC_772776740BF4F418_NIC
