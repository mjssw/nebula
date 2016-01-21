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
#ifndef NIC_322A14E51E08037D_NIC
#define NIC_322A14E51E08037D_NIC

#include "../error_info.h"
#include "../../dll_interface.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace exception_detail {
//------------------------------------------------------------------------------
class n_foundation_dll ei_container
{
    struct node
    {
        inline node(node *nxt_, error_info_base *ei_) noexcept
        : nxt(nxt_), ei(ei_)
        {}
        inline ~node() noexcept
        {
            delete ei;
            ei = nullptr;
        }
        node *nxt;
        error_info_base *ei;
    };

public:
    ei_container() noexcept;
    ei_container(ei_container &);
    ei_container(const ei_container &);
    ei_container(ei_container &&) noexcept;
    ~ei_container() noexcept;
    
    ei_container &operator = (const ei_container &);
    ei_container &operator = (ei_container &&) noexcept;
    
    template <class EInfo>
    inline const EInfo *get() const noexcept
    {
        if(!empty())
        {
            node *i = h;
            do
            {
                const EInfo *ptr = dynamic_cast<const EInfo *>(i->ei);
                if(ptr)
                    return ptr;
                i = i->nxt;
            } while(i);
        }
        return nullptr;
    }
    template <class EInfo>
    inline EInfo *get() noexcept
    {
        if(!empty())
        {
            node *i = h;
            do
            {
                EInfo *ptr = dynamic_cast<EInfo *>(i->ei);
                if(ptr)
                    return ptr;
                i = i->nxt;
            } while(i);
        }
        return nullptr;
    }
    
    template <class EInfo>
    inline void push(EInfo &&ei)
    {
        using EI = typename remove_const<
            typename remove_reference<EInfo>::type
        >::type;
        error_info_base *nei = new EI(foundation::forward<EInfo>(ei));
        node *n;
        try {
            n = new node(h, nei);
        } catch(...) {
            delete nei;
            throw;
        }
        h = n;
    }
    
    string message(uintptr_t) const;
    
private:
    bool empty() const noexcept;
    void reset() noexcept;
    void kill(node *) const noexcept;
    node *clone() const;
    
    node *h;
};
//------------------------------------------------------------------------------
} // exception_detail
//------------------------------------------------------------------------------

/** @} */

}} // namespaces

#endif // NIC_322A14E51E08037D_NIC