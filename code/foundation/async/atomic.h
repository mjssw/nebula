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
#ifndef NIC_7465AC91A4DF7CD7_NIC
#define NIC_7465AC91A4DF7CD7_NIC

#include <atomic>
#include "../defs.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
using std::memory_order;
using std::atomic;

using atomic_bool = atomic<bool>;
using atomic_char = atomic<char>;
using atomic_schar = atomic<schar>;
using atomic_uchar = atomic<uchar>;
using atomic_short = atomic<short>;  
using atomic_ushort = atomic<ushort>;  
using atomic_int = atomic<int>; 
using atomic_uint = atomic<uint>;
using atomic_long = atomic<long>;
using atomic_ulong = atomic<ulong>;   
using atomic_llong = atomic<llong>;  
using atomic_ullong = atomic<ullong>;  
using atomic_char16_t = atomic<char16_t>;
using atomic_char32_t = atomic<char32_t>;
using atomic_wchar_t = atomic<wchar_t>; 
using atomic_int_least8_t = atomic<int_least8_t>;
using atomic_uint_least8_t = atomic<uint_least8_t>;   
using atomic_int_least16_t = atomic<int_least16_t>;  
using atomic_uint_least16_t = atomic<uint_least16_t>;  
using atomic_int_least32_t = atomic<int_least32_t>;   
using atomic_uint_least32_t = atomic<uint_least32_t>;  
using atomic_int_least64_t = atomic<int_least64_t>;   
using atomic_uint_least64_t = atomic<uint_least64_t>;  
using atomic_int_fast8_t = atomic<int_fast8_t>; 
using atomic_uint_fast8_t = atomic<uint_fast8_t>;
using atomic_int_fast16_t = atomic<int_fast16_t>;
using atomic_uint_fast16_t = atomic<uint_fast16_t>;   
using atomic_int_fast32_t = atomic<int_fast32_t>;
using atomic_uint_fast32_t = atomic<uint_fast32_t>;   
using atomic_int_fast64_t = atomic<int_fast64_t>;
using atomic_uint_fast64_t = atomic<uint_fast64_t>;   
// using atomic_intptr_t = atomic<intptr_t>;
// using atomic_uintptr_t = atomic<uintptr_t>;   
using atomic_size_t = atomic<size_t>;
using atomic_ptrdiff_t = atomic<ptrdiff_t>;   
using atomic_intmax_t = atomic<intmax_t>;
using atomic_uintmax_t = atomic<uintmax_t>;

using std::atomic_flag;

using std::atomic_is_lock_free;
using std::atomic_store;
using std::atomic_store_explicit;
using std::atomic_load;
using std::atomic_load_explicit;
using std::atomic_exchange;
using std::atomic_exchange_explicit;
using std::atomic_compare_exchange_weak;
using std::atomic_compare_exchange_weak_explicit;
using std::atomic_compare_exchange_strong;
using std::atomic_compare_exchange_strong_explicit;
using std::atomic_fetch_add;
using std::atomic_fetch_add_explicit;
using std::atomic_fetch_sub;
using std::atomic_fetch_sub_explicit;
using std::atomic_fetch_and;
using std::atomic_fetch_and_explicit;
using std::atomic_fetch_or;
using std::atomic_fetch_or_explicit;
using std::atomic_fetch_xor;
using std::atomic_fetch_xor_explicit;

}}} // namespaces

#endif // NIC_7465AC91A4DF7CD7_NIC
