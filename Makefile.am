ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects
AM_MAKEFLAGS = --no-print-directory
AM_CPPFLAGS = -DDATA_DIR=\"$(datadir)\" @CPPFLAGS@                             \
   -I$(top_srcdir) -I$(top_srcdir)/src/include

MAINTAINERCLEANFILES =                                                         \
   ABOUT-NLS Makefile.in aclocal.m4 compile config.guess config.h.in~          \
   config.h.in config.sub configure config.cache-env depcomp install-sh        \
   ltmain.sh missing

include_HEADERS = src/include/Escarg.h

lib_LTLIBRARIES = src/lib/libescarg.la

src_lib_libescarg_la_SOURCES =                                                 \
   src/lib/escarg_main.c                                                       \
   src/lib/escarg_bash.c                                                       \
   src/lib/escarg_posix.c                                                      \
   src/lib/escarg_windows.c                                                    \
   src/lib/escarg_utils.c                                                      \
   src/lib/escarg_private.h
src_lib_libescarg_la_CFLAGS = $(ESCARG_CFLAGS)
src_lib_libescarg_la_CPPFLAGS = $(AM_CPPFLAGS)
src_lib_libescarg_la_LDFLAGS = $(ESCARG_LIBS) -version-info @version_info@
