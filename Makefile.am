ACLOCAL_AMFLAGS = -I m4 --install

pkgconfigdir = $(libdir)/pkgconfig

nodist_pkgconfig_DATA =\
nebula-foundation.pc \
nebula-nml.pc \
nebula-gpg.pc

#-------------------------------------------------------------------------------
lib_LTLIBRARIES =\
libnebula-foundation.la \
libnebula-nml.la \
libnebula-gpg.la

#-------------------------------------------------------------------------------
libnebula_foundation_la_SOURCES =\
code/foundation/async/posix/posix_condition_variable.cpp \
code/foundation/async/posix/posix_mutex.cpp \
code/foundation/async/posix/posix_sleep.cpp \
code/foundation/async/posix/posix_thread.cpp \
code/foundation/async/posix/posix_yield.cpp \
code/foundation/async/thread_pool/thread_pool.cpp \
code/foundation/chrono/high_resolution_clock/high_resolution_clock.cpp \
code/foundation/chrono/monotonic_clock/monotonic_clock.cpp \
code/foundation/chrono/system_clock/system_clock.cpp \
code/foundation/exception/detail/ei_container.cpp \
code/foundation/exception/exception.cpp \
code/foundation/exception/message.cpp \
code/foundation/filesystem/file_status.cpp \
code/foundation/filesystem/posix/posix_canonical.cpp \
code/foundation/filesystem/posix/posix_create_directory.cpp \
code/foundation/filesystem/posix/posix_create_link.cpp \
code/foundation/filesystem/posix/posix_create_symlink.cpp \
code/foundation/filesystem/posix/posix_current_directory.cpp \
code/foundation/filesystem/posix/posix_read_symlink.cpp \
code/foundation/filesystem/posix/posix_recursive_scan.cpp \
code/foundation/filesystem/posix/posix_remove.cpp \
code/foundation/filesystem/posix/posix_rename.cpp \
code/foundation/filesystem/posix/posix_scan.cpp \
code/foundation/filesystem/posix/posix_status.cpp \
code/foundation/io/stream/fstream/fstream.cpp \
code/foundation/io/stream/stdstreams/cerr.cpp \
code/foundation/io/stream/stdstreams/cin.cpp \
code/foundation/io/stream/stdstreams/cout.cpp \
code/foundation/net/error.cpp \
code/foundation/net/ip/ipv4_address.cpp \
code/foundation/net/ip/ipv6_address.cpp \
code/foundation/net/net_defs.cpp \
code/foundation/net/posix/epoll/epoll_proactor.cpp \
code/foundation/net/posix/epoll/epoll_socket.cpp \
code/foundation/net/posix/posix_ep_conv.cpp \
code/foundation/net/posix/posix_protocol_server.cpp \
code/foundation/net/posix/posix_socket.cpp \
code/foundation/qlog/sink/console.cpp \
code/foundation/qlog/sink/syslog.cpp \
code/foundation/random/engine/dev_random/dev_random_device.cpp \
code/foundation/random/engine/dev_urandom/dev_urandom_device.cpp \
code/foundation/system/error_category.cpp \
code/foundation/system_error.cpp \
code/foundation/utils/demangle_type_info_name.cpp
libnebula_foundation_la_LDFLAGS = -version 0:0:0

#-------------------------------------------------------------------------------
libnebula_nml_la_SOURCES =\
code/nml/nml.cpp
libnebula_nml_la_LDFLAGS = -version 0:0:0

#-------------------------------------------------------------------------------
libnebula_gpg_la_SOURCES =\
code/gpg/context.cpp \
code/gpg/error.cpp \
code/gpg/exception.cpp
libnebula_gpg_la_LDFLAGS = -version 0:0:0

#-------------------------------------------------------------------------------
SUBDIRS = code
