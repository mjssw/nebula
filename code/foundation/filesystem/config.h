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
#ifndef NIC_66640C84034ADBAF_NIC
#define NIC_66640C84034ADBAF_NIC

#include "../config.h"

#ifdef N_HEADER_SYS_STAT_H
#   define N_FILESYSTEM_posix_stat
#   define N_FILESYSTEM_posix_mkdir
#else
#   error Missing sys/stat.h
#endif

#ifdef N_HEADER_DIRENT_H
#   define N_FILESYSTEM_posix_scandir
#else
#   error Missing dirent.h
#endif

#ifdef N_HEADER_FTW_H
#   define N_FILESYSTEM_posix_nftw
#else
#   error Missing ftw.h
#endif

#ifdef N_HEADER_UNISTD_H
#   define N_FILESYSTEM_posix_readlink
#   define N_FILESYSTEM_posix_getcwd
#   define N_FILESYSTEM_posix_symlink
#   define N_FILESYSTEM_posix_link
#else
#   error Missing unistd.h
#endif

#ifdef N_API_REALPATH
#   define N_FILESYSTEM_posix_realpath
#else
#   error Missing realpath()
#endif

// C std
#define N_FILESYSTEM_posix_rename
#define N_FILESYSTEM_posix_remove

#endif // NIC_66640C84034ADBAF_NIC