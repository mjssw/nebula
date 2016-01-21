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
#ifndef NIC_363398DCD075C71E_NIC
#define NIC_363398DCD075C71E_NIC

#include "lock.h"
#include "unlock.h"
#include "../swap.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
template <class T>
struct scoped_unlock
{
public:
    inline scoped_unlock(T &x) noexcept
    : m(&x), dismiss_(false)
    {}
    inline scoped_unlock(scoped_unlock &&other) noexcept 
    : m(other.m), dismiss_(false)
    {
        other.dismiss();
    }
    inline ~scoped_unlock()
    {
        if(!dismiss_)
            async::unlock(*m);
    }
    
    inline scoped_unlock operator = (scoped_unlock &&other) noexcept {
        m = other.m;
        other.dismiss();
        return *this;
    }
    
    inline void swap(scoped_unlock &other) noexcept {
        foundation::swap(m, other.m);
        foundation::swap(dismiss_, other.dismiss_);
    }
    
    inline void dismiss() noexcept {
        dismiss_ = true;
    }
    
    inline bool operator == (const scoped_unlock &other) const noexcept {
        return m == other.m;
    }
    inline bool operator != (const scoped_unlock &other) const noexcept {
        return m != other.m;
    }
    
private:
    T *m;
    bool dismiss_;
};

//------------------------------------------------------------------------------
template <class M>
inline scoped_unlock<M> make_scoped_unlock(M &m)
{
    return scoped_unlock<M>(m);
}
//------------------------------------------------------------------------------
template <class M>
inline scoped_unlock<M> sul(M &m)
{
    return scoped_unlock<M>(m);
}

//------------------------------------------------------------------------------
#define _n_scope_unlock_concat_string_impl(_s0, _s1) _s0 ## _s1
#define _n_scope_unlock_concat_string(_s0, _s1) \
    _n_scope_unlock_concat_string_impl(_s0, _s1)
#define _n_scope_unlock_make_var_name(_s) \
    _n_scope_unlock_concat_string(_s, __COUNTER__)
//------------------------------------------------------------------------------
#define n_scoped_unlock( x ) \
    auto _n_scope_unlock_make_var_name(nebula_scope_unlock_) \
    = ::nebula::foundation::async::make_scoped_unlock( x )

}}} // namespaces

#endif // NIC_363398DCD075C71E_NIC
