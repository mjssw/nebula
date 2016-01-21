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
#include "ei_container.h"
#include "../message.h"
#include "../../utils/demangle_type_info_name.h"

namespace nebula { namespace foundation { namespace exception_detail {
//------------------------------------------------------------------------------
ei_container::ei_container() noexcept
{
    h = nullptr;
}
//------------------------------------------------------------------------------
ei_container::ei_container(ei_container &other)
{
    h = other.clone();
}
//------------------------------------------------------------------------------
ei_container::ei_container(const ei_container &other)
{
    h = other.clone();
}
//------------------------------------------------------------------------------
ei_container::ei_container(ei_container &&other) noexcept
{
    h = other.h;
    other.h = nullptr;
}
//------------------------------------------------------------------------------
ei_container::~ei_container() noexcept
{
    this->reset();
}

//------------------------------------------------------------------------------
ei_container &ei_container::operator = (const ei_container &other)
{
    this->reset();
    this->h = other.clone();
    return *this;
}
//------------------------------------------------------------------------------
ei_container &ei_container::operator = (ei_container &&other) noexcept
{
    this->reset();
    h = other.h;
    other.h = nullptr;
    return *this;
}

//------------------------------------------------------------------------------
string ei_container::message(uintptr_t exc_id) const
{
    io::msink<string> ss;
    if(!empty())
    {
        node *i = h;
        do
        {
            fmt::fwrite(
                ss,
                "~~ (", fmt::hex(exc_id), ") [ ",
                demangle_type_info_name(i->ei->type_name()), " ] \n",
                i->ei->message());
            i = i->nxt;
            if(i) {
                fmt::fwrite(ss, fmt::endl);
                continue;
            }
            else
                break;
        } while(true);
    }
    return foundation::move(ss.container());
}
//------------------------------------------------------------------------------
bool ei_container::empty() const noexcept
{
    return h == nullptr;
}
//------------------------------------------------------------------------------
void ei_container::reset() noexcept
{
    this->kill(h);
    h = nullptr;
}
//------------------------------------------------------------------------------
void ei_container::kill(ei_container::node *n) const noexcept
{
    if(n)
    {
        node *i = n;
        do
        {
            node *n = i;
            i = i->nxt;
            delete n;
        } while(i);
    }
}
//------------------------------------------------------------------------------
ei_container::node *ei_container::clone() const
{
    if(!empty())
    {
        node *n = nullptr;
        try {
            node *i = h;
            n = new node(nullptr, i->ei->clone());   
            i = i->nxt;
            node *prev = n;
            while(i)
            {
                node *cur = new node(nullptr, i->ei->clone());
                prev->nxt = cur;
                prev = cur;
                i = i->nxt;
            }  
        } catch(...) {
            this->kill(n);
            throw;
        }
        return n;
    }
    else 
        return nullptr;
}

}}} // namespaces
