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
#ifndef NIC_FB6E1A46BEE14F19_NIC
#define NIC_FB6E1A46BEE14F19_NIC

#include "defs.h"
#include "error.h"

namespace nebula { namespace gpg { namespace detail {
/** @ingroup GPG
 * @{
 * */
//------------------------------------------------------------------------------
/** This represents information about (a part of) a signature.
 * */
class signature_info
{
public:
    inline signature_info(
        const errc err_,
        string fpr_,
        const chrono::seconds crtn_,
        const chrono::seconds expr_,
        const detail::public_key_algorithm pka,
        const detail::hash_algorithm ha)
    :   err(err_),
        fpr(move(fpr_)),
        crtn(crtn_),
        expr(expr_),
        pk_algo(pka),
        h_algo(ha)
    {}
    
    inline errc status() const {
        return err;
    }
    
    inline bool valid() const {
        return errc::success == err;
    }
    
    inline const string &fingerprint() const noexcept {
        return fpr;
    }
    /** @warning Must not be called if signature is not valid. */
    inline chrono::seconds creation_time() const {
        if(!valid())
            n_throw(logic_error);
        return crtn;
    }
    /** @warning Must not be called if signature is not valid. */
    inline chrono::seconds expiration_time() const {
        if(!valid())
            n_throw(logic_error);
        return expr;
    }
    /** @warning Must not be called if signature is not valid. */
    inline detail::public_key_algorithm public_key_algorithm() const {
        if(!valid())
            n_throw(logic_error);
        return pk_algo;
    }
    /** @warning Must not be called if signature is not valid. */
    inline detail::hash_algorithm hash_algorithm() const {
        if(!valid())
            n_throw(logic_error);
        return h_algo;
    }
    
private:
    errc err;
    string fpr;
    chrono::seconds crtn;
    chrono::seconds expr;
    detail::public_key_algorithm pk_algo;
    detail::hash_algorithm h_algo;
};

/** @} */

}}} // namespaces

#endif // NIC_FB6E1A46BEE14F19_NIC

