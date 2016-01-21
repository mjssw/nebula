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
#ifndef NIC_B745889C7C4A0DE3_NIC
#define NIC_B745889C7C4A0DE3_NIC

#include "traits/base.h"
#include "traits/digits.h"
#include "traits/has_denorm.h"
#include "traits/has_denorm_loss.h"
#include "traits/has_infinity.h"
#include "traits/has_quiet_nan.h"
#include "traits/has_signaling_nan.h"
#include "traits/is_bounded.h"
#include "traits/is_exact.h"
#include "traits/is_iec559.h"
#include "traits/is_integer.h"
#include "traits/is_modulo.h"
#include "traits/is_signed.h"
#include "traits/rounding.h"
#include "traits/traps.h"
#include "traits/exponent.h"

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 * */
n_meta_alias(base);
n_meta_alias(digits);
n_meta_alias(has_denorm);
n_meta_alias(has_denorm_loss);
n_meta_alias(has_infinity);
n_meta_alias(has_quiet_nan);
n_meta_alias(has_signaling_nan);
n_meta_alias(is_bounded);
n_meta_alias(is_exact);
n_meta_alias(is_iec559);
n_meta_alias(is_integer);
n_meta_alias(is_modulo);
n_meta_alias(is_signed);
n_meta_alias(rounding);
n_meta_alias(traps);
n_meta_alias(exponent);
 
/** @} */

}}} // namespaces

#endif // NIC_B745889C7C4A0DE3_NIC
