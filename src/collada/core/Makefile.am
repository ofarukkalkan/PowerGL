AM_CPPFLAGS = -I$(top_srcdir)/core $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)

noinst_LTLIBRARIES = libpowerglcolladacore.la
libpowerglcollada_ladir = $(includedir)/powergl/collada/core/
libpowerglcollada_la_HEADERS = core.h
libpowerglcolladacore_la_SOURCES = core.c
libpowerglcolladacore_la_LDFLAGS = -no-undefined
libpowerglcolladacore_la_LIBADD = $(CODE_COVERAGE_LIBS)

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean
