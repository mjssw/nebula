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
#ifndef NIC_D2AFAE23A5CD1F53_NIC
#define NIC_D2AFAE23A5CD1F53_NIC

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct generate_impl
{
    template <class F_>
    inline static void apply(I first, const I last, F_ &&f)
    {
        while(first != last)
            *first++ = f();
    }
};
//------------------------------------------------------------------------------
/** Replaces all elements in the [first, last) with the result of f() in
 * consecutive order.
 * @param I Must be an incrementable iterator.
 * @param f A function which takes no arguments and returns a type implicitely
 * convertible to the value_type of the range in question.
 * @return void
 * @return Weak exception safety - elements are replaces until the functor
 * fails with an exception.
 * */
template <class I, class F>
inline void generate(I first, I last, F &&f)
{
    generate_impl<I>::apply(first, last, f);
}

/** @} */

}}} // namespaces

#endif // NIC_D2AFAE23A5CD1F53_NIC
