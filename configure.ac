AC_DEFUN([PROJECT_NAME_], [Nebula])
AC_DEFUN([PROJECT_BUGREPORT_], [lis@tutanota.com])
AC_DEFUN([PROJECT_URL_], [https://www.github.com/defudger/nebula])
AC_DEFUN([PROJECT_VERSION_MAJOR_], [0])
AC_DEFUN([PROJECT_VERSION_MINOR_], [0])
AC_DEFUN([PROJECT_VERSION_MICRO_], [0])

AC_INIT(PROJECT_NAME_, PROJECT_VERSION_MAJOR_.PROJECT_VERSION_MINOR_.PROJECT_VERSION_MICRO_, PROJECT_BUGREPORT_, [], PROJECT_URL_)

AC_PREREQ([2.68])

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([code/foundation/vector.h])

AC_CONFIG_HEADERS([config.h])
AX_PREFIX_CONFIG_H([code/foundation/config/nebula_auto_config.h], [NAUTO])

AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.14 subdir-objects -Wall -Werror])
AM_PROG_AR

LT_INIT

AC_LANG([C++])

#-------------------------------------------------------------------------------

AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_MKDIR_P

#-------------------------------------------------------------------------------

AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])
AC_TYPE_INTMAX_T
AC_TYPE_UINTMAX_T
AC_HEADER_TIME

AX_PTHREAD( [
    AC_DEFINE(HAVE_PTHREAD, 1, [Define if you have POSIX threads libraries and header files.])
    CLIBS="$PTHREAD_LIBS $LIBS"
    CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
    LDFLAGS="$LDFLAGS $PTHREAD_CFLAGS"
    CC="$PTHREAD_CC"], [])
    
AS_IF([test "x$GCC" = "xyes"],[
    AX_CHECK_COMPILE_FLAG([-std=c++14], [
        CXXFLAGS="$CXXFLAGS -std=c++14 -DBUILDING_NEBULA_"], [
        AC_MSG_ERROR([no C++14 support])])
])
    
AC_SEARCH_LIBS([sched_yield], [dl, dld], [], [
    AC_MSG_ERROR([unable to find shed_yield])])
    
AC_CHECK_HEADERS_ONCE([sched.h])
AC_CHECK_HEADERS_ONCE([dirent.h])
AC_CHECK_HEADERS_ONCE([sys/stat.h])
AC_CHECK_HEADERS_ONCE([ftw.h])
AC_CHECK_HEADERS_ONCE([sys/socket.h])
AC_CHECK_HEADERS_ONCE([netdb.h])
AC_CHECK_HEADERS_ONCE([arpa/inet.h])
AC_CHECK_HEADERS([limits.h])

AC_CHECK_FILE([/dev/random], [
    AH_TOP([#define HAVE_DEV_RANDOM 1])
])
AC_CHECK_FILE([/dev/urandom], [
    AH_TOP([#define HAVE_DEV_URANDOM 1])
])

AC_CHECK_HEADERS_ONCE([unistr.h])
AC_CHECK_LIB(unistring,u8_check)

AC_CHECK_HEADERS_ONCE([gpgme.h])
AC_CHECK_LIB(gpgme,gpgme_check_version)

AC_CHECK_FUNCS([clock_gettime floor getcwd memmove memset mkdir pow realpath socket sqrt])

#-------------------------------------------------------------------------------
AC_DEFINE([PACKAGE_VERSION_MAJOR], PROJECT_VERSION_MAJOR_, [Major version])
AC_DEFINE([PACKAGE_VERSION_MINOR], PROJECT_VERSION_MINOR_, [Minor version])
AC_DEFINE([PACKAGE_VERSION_MICRO], PROJECT_VERSION_MICRO_, [Micro version])

#-------------------------------------------------------------------------------
AC_DEFUN([FOUNDATION_VERSION_MAJOR_], [0])
AC_DEFUN([FOUNDATION_VERSION_MINOR_], [0])
AC_DEFUN([FOUNDATION_VERSION_MICRO_], [0])

AC_DEFINE([FOUNDATION_NAME], ["Nebula.Foundation"], [Name])
AC_DEFINE([FOUNDATION_VERSION], "FOUNDATION_VERSION_MAJOR_.FOUNDATION_VERSION_MINOR_.FOUNDATION_VERSION_MICRO_", [Version String])
AC_DEFINE([FOUNDATION_STRING], "Nebula.Foundation FOUNDATION_VERSION_MAJOR_.FOUNDATION_VERSION_MINOR_.FOUNDATION_VERSION_MICRO_", [Name Version String])
AC_DEFINE([FOUNDATION_BUGREPORT], "PROJECT_BUGREPORT_", [Bugreport])
AC_DEFINE([FOUNDATION_URL], "PROJECT_URL_", [URL])
AC_DEFINE([FOUNDATION_VERSION_MAJOR], FOUNDATION_VERSION_MAJOR_, [Major version])
AC_DEFINE([FOUNDATION_VERSION_MINOR], FOUNDATION_VERSION_MINOR_, [Minor version])
AC_DEFINE([FOUNDATION_VERSION_MICRO], FOUNDATION_VERSION_MICRO_, [Micro version])

#-------------------------------------------------------------------------------
AC_DEFUN([GPG_VERSION_MAJOR_], [0])
AC_DEFUN([GPG_VERSION_MINOR_], [0])
AC_DEFUN([GPG_VERSION_MICRO_], [0])

AC_DEFINE([GPG_NAME], ["Nebula.GPG"], [Name])
AC_DEFINE([GPG_VERSION], "GPG_VERSION_MAJOR_.GPG_VERSION_MINOR_.GPG_VERSION_MICRO_", [Version String])
AC_DEFINE([GPG_STRING], "Nebula.GPG GPG_VERSION_MAJOR_.GPG_VERSION_MINOR_.GPG_VERSION_MICRO_", [Name Version String])
AC_DEFINE([GPG_BUGREPORT], "PROJECT_BUGREPORT_", [Bugreport])
AC_DEFINE([GPG_URL], "PROJECT_URL_", [URL])
AC_DEFINE([GPG_VERSION_MAJOR], GPG_VERSION_MAJOR_, [Major version])
AC_DEFINE([GPG_VERSION_MINOR], GPG_VERSION_MINOR_, [Minor version])
AC_DEFINE([GPG_VERSION_MICRO], GPG_VERSION_MICRO_, [Micro version])

#-------------------------------------------------------------------------------
AC_DEFUN([NML_VERSION_MAJOR_], [0])
AC_DEFUN([NML_VERSION_MINOR_], [0])
AC_DEFUN([NML_VERSION_MICRO_], [0])

AC_DEFINE([NML_NAME], ["Nebula.NML"], [Name])
AC_DEFINE([NML_VERSION], "NML_VERSION_MAJOR_.NML_VERSION_MINOR_.NML_VERSION_MICRO_", [Version String])
AC_DEFINE([NML_STRING], "Nebula.NML NML_VERSION_MAJOR_.NML_VERSION_MINOR_.NML_VERSION_MICRO_", [Name Version String])
AC_DEFINE([NML_BUGREPORT], "PROJECT_BUGREPORT_", [Bugreport])
AC_DEFINE([NML_URL], "PROJECT_URL_", [URL])
AC_DEFINE([NML_VERSION_MAJOR], NML_VERSION_MAJOR_, [Major version])
AC_DEFINE([NML_VERSION_MINOR], NML_VERSION_MINOR_, [Minor version])
AC_DEFINE([NML_VERSION_MICRO], NML_VERSION_MICRO_, [Micro version])

#-------------------------------------------------------------------------------

AC_CONFIG_FILES([Makefile code/Makefile nebula-foundation.pc nebula-gpg.pc nebula-nml.pc])
AC_OUTPUT
