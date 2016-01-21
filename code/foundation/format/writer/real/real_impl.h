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
#ifndef NIC_9938A934BD0FA342_NIC
#define NIC_9938A934BD0FA342_NIC

#include "../../tags.h"
#include "../../../io.h"
#include "../../../math/basic/abs.h"
#include "../../../math/basic/split.h"
#include "../../../math/basic/floor.h"
#include "../../../math/basic/ceil.h"
#include "../../../math/basic/get_exp.h"
#include "../../../math/division/div.h"
#include "../../../math/division/mod.h"
#include "../../../math/exp/log.h"
#include "../../../math/pow/pow.h"
#include "../../../math/classification.h"
#include "../../../string.h"
#include "../../../assert.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace real_impl_detail {
//------------------------------------------------------------------------------
template <class T, class D>
struct real_writer_
{
private:
    using exp_t = typename math::exponent<T>::type;
    
public:
    template <class S>
    inline void operator () (S &sink, fout_tag) const
    {
        switch(math::classify(x))
        {
        case math::f_state::infinite:
            if(math::isnegative(x))
                io::write(sink, "-inf", 4);
            else
                io::write(sink, "inf", 3);
            return;
        case math::f_state::NaN:
            if(math::isnegative(x))
                io::write(sink, "-nan", 4);
            else
                io::write(sink, "nan", 3);
            return;
        default: break;
        }
        
        if(e_lit != 0)
        {
            write_sci(sink);
        }
        else
        {
            write_fixed(sink);
        }
    }
    
private:        
    template <class S>
    inline void write_i(S &sink, T x_, const T &b) const
    {                
        string buf;
        buf.reserve(10);
        
        do 
        {
            unsigned r;
            foundation::tie(x_, r) = math::div(x_, b);
            buf.push_back(D::encode(r));
        }
        while(x_ != T(0));
        
        for(const char c : buf | range::reversed)
        {
            io::put(sink, c);
        }
    }
    template <class S>
    inline void write_f(S &sink, T f, const T &b, const bool neg) const
    {
        n_assert(prec > 0);
        
        {
            f *= b;
            unsigned d;
            foundation::tie(d, f) = math::split(f);
            io::put(sink, D::encode(d));
        }
        
        size_t z = 0;
        for(size_t k = 1; k < prec; ++k)
        {
            f *= b;
            unsigned d;
            foundation::tie(d, f) = math::split(f);
            if(d == 0)
                ++z;
            else
            {
                if(z)
                {
                    for(size_t l = 0; l < z; ++l)
                        io::put(sink, D::encode(0));
                    z = 0;
                }
                io::put(sink, D::encode(d));
            }
        }
    }
    template <class S>
    inline void write_sci(S &sink) const
    {
        bool neg = false;
        
        if(math::isnegative(x))
        {
            neg = true;
            io::put(sink, '-');
        }
        
        if(math::iszero(x))
        {
            io::put(sink, D::encode(0));
            return;
        }
        
        const T b = base;
        const exp_t e = math::get_exp(x);
        const exp_t conv_e = math::floor(
            T(e) * (math::log(T(math::base<T>::value)) / math::log(b)));
        
        T f = round(math::abs(x * math::pow(b, T(-conv_e))), b, neg);
        
        tuple<T,T> spl = math::split(f);
        
        const unsigned lead = foundation::get<0>(spl); // trunc
        fmt::fwrite(sink, fmt::integer<D>(lead, base));
        
        if(prec)
        {
            io::put(sink, comma_lit);
            this->write_f(sink, foundation::get<1>(spl), b, neg);
        }
        
        if(conv_e >= 0)
            fmt::fwrite(sink, e_lit, '+', fmt::integer<D>(conv_e, base));
        else
            fmt::fwrite(sink, e_lit, fmt::integer<D>(conv_e, base));
    }
    template <class S>
    inline void write_fixed(S &sink) const
    {
        bool neg = false;
        if(math::isnegative(x)) {
            neg = true;
            io::put(sink, '-');
        }
        
        const T b = base;
        const T f = math::abs(x);
        
        tuple<T,T> spl = math::split(f);
        
        write_i(sink, foundation::get<0>(spl), b);
        
        if(prec)
        {
            io::put(sink, comma_lit);
            this->write_f(sink, foundation::get<1>(spl), b, neg);
        }
    }
    
    inline T round(const T &f, const T &b, const bool neg) const
    {
        switch(rounding)
        {
        case math::rounding_style::to_zero:
            {
                const T factor = math::pow(b, prec);
                if(neg)
                    return math::ceil(f * factor) / factor;
                return math::floor(f * factor) / factor;
            }
        case math::rounding_style::to_infinity:
            {
                const T factor = math::pow(b, prec);
                return math::ceil(f * factor) / factor;
            }
        case math::rounding_style::to_neg_infinity:
            {
                const T factor = math::pow(b, prec);
                return math::floor(f * factor) / factor;
            }
        case math::rounding_style::to_nearest:
            {
                const T factor = math::pow(b, prec);
                const T h = b/T(2) * math::pow(b, -1);
                if(neg)
                    return math::ceil(f * factor - h) / factor;
                return math::floor(f * factor + h) / factor;
            }
        default:
            return f;
        }
    }
    
public:
    T x;
    unsigned base;
    size_t prec;
    math::rounding_style rounding;
    char e_lit;
    char comma_lit;
};

} // real_impl_detail

/** @} */

}}} // namespaces

#endif // NIC_9938A934BD0FA342_NIC
