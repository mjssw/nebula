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
#ifndef NIC_787EDA9B6964533A_NIC
#define NIC_787EDA9B6964533A_NIC

#include "sink_base.h"

namespace nebula { namespace foundation { namespace qlog { namespace sink {
//------------------------------------------------------------------------------
extern void n_foundation_dll init_console();
extern intrusive_ptr<sink_base> console();

}}}} // namespaces

#endif // NIC_787EDA9B6964533A_NIC
