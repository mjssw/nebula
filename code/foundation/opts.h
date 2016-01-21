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
#ifndef NIC_857703E33963F740_NIC
#define NIC_857703E33963F740_NIC

#include "cstring.h"
#include "array.h"
#include "tuple.h"
#include "call_traits.h"

namespace nebula { namespace foundation { namespace opts {
/** @ingroup Foundation
 * @{
 * */
namespace opts_detail {

//------------------------------------------------------------------------------
template <
    class CB,
    size_t NumNames>
struct argument
{
    CB do_named_arg;
    array<const_cstring, NumNames> names;
};
//------------------------------------------------------------------------------
template <
    class InputError,
    class PositionalArg,
    class ... Args>
struct context
{
    InputError input_error;
    PositionalArg do_positional_arg;
    tuple<Args...> args;
};

//------------------------------------------------------------------------------
template <class Context>
struct parser_callback
{
    struct abort_parsing {};
    
    inline bool argument(const_cstring id, const_cstring val, size_t i)
    {        
        bool triggered = false;
        
        auto f = [&] (auto x) 
        {
            for(auto name : x.names)
            {
                if(name == id)
                {
                    triggered = true;
                    if(!x.do_named_arg(id, val, i))
                        return false;
                    break;
                }
            }
            return true;
        };
        for_each(ctx.args, f);
        
        if(!triggered) {
            ctx.input_error(id, val, i);
            return false;
        }
        return true;
    }
    inline bool argument(const_cstring val, size_t i)
    {
        return ctx.do_positional_arg(val, i);
    }
    
    ctraits::_ref<Context> ctx;
};

}; // opts_detail

//------------------------------------------------------------------------------
template <class CB, class ... Names,
    class Ret = opts_detail::argument<
        ctraits::_value<CB>,
        sizeof ... (Names)>>
inline Ret argument(
    CB &&cb,
    Names ... names)
{
    using namespace foundation;
    
    return Ret{foundation::forward<CB>(cb),
        array<const_cstring, sizeof... (Names)>{names ...}};
}
//------------------------------------------------------------------------------
template <
    class InputError,
    class PositionalArg,
    class ... Args,
    class Ret = opts_detail::context<
        ctraits::_value<InputError>,
        ctraits::_value<PositionalArg>,
        ctraits::_value<Args> ...>>
inline Ret context(
    InputError &&err,
    PositionalArg &&pos_cb,
    Args && ... args)
{
    return Ret{
        foundation::forward<InputError>(err),
        foundation::forward<PositionalArg>(pos_cb),
        foundation::make_tuple(foundation::forward<Args>(args)...)};
}
//------------------------------------------------------------------------------
template <class Context>
inline void parse_command_line(Context &&ctx, int argc, char **argv)
{
    if(argc < 0)
        n_throw(logic_error);
    if(argv == nullptr)
        n_throw(logic_error);
    
    if(argc == 0)
        return;
    
    auto cb = opts_detail::parser_callback<Context>{ctx};
        
    if(!cb.argument(argv[0], 0))
        return;
    
    for(int i = 1; i < argc; ++i)
    {
        const_cstring arg(argv[i]);
        
        if(arg.size() == 1)
        {
            if(arg[0] == '-')
            {
                if(i < argc-1)
                {
                    ++i;
                    if(!cb.argument(const_cstring(argv[i]), i))
                        return;
                }
            }
            else
            {
                if(!cb.argument(arg, i))
                    return;
            }
            continue;
        }
        else if(arg.size() == 2)
        {
            if(arg[0] == '-' && arg[1] == '-')
            {
                ++i;
                for( ; i < argc; ++i)
                {
                    if(!cb.argument(const_cstring(argv[i]), i))
                        return;
                }
                return;
            }
        }
        
        if(arg[0] == '-')
        {
            // strip dashes
            if(arg[1] == '-')
                arg = const_cstring(arg.begin()+2, arg.end());
            else
                arg = const_cstring(arg.begin()+1, arg.end());
            
            size_t n = 1;
            for( ; n < arg.size(); ++n)
            {
                if(arg[n] == '=')
                    break;
            }
            if(n == arg.size())
            {
                if(!cb.argument(arg, const_cstring(), i))
                    return;
            }
            else
            {
                const const_cstring name(arg.begin(), arg.begin()+n);
                const const_cstring value(arg.begin()+n+1, arg.end());
                if(!cb.argument(name, value, i))
                    return;
            }
        }
        else
        {
            if(!cb.argument(arg, i))
                return;
        }
    }
}

/** @} */

}}} // namespaces

#endif // NIC_857703E33963F740_NIC
