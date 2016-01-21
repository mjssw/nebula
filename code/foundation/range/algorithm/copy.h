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
#ifndef NIC_3E8B952261132066_NIC
#define NIC_3E8B952261132066_NIC

#include "../common.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class InputRange, class OutputIter>
struct copy_impl
{
    inline static OutputIter apply(const InputRange &src, OutputIter trg)
    {
        return ins_::copy(
            range::begin(src),
            range::end(src),
            trg);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class InputRange, class OutputIter>
inline OutputIter copy(const InputRange &src, OutputIter trg)
{
    return copy_impl<InputRange, OutputIter>::apply(src, trg);
}

/** @} */

}}} // namespaces

#endif // NIC_3E8B952261132066_NIC
