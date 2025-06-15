AM_CPPFLAGS = -I$(top_srcdir)/png $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)

noinst_LTLIBRARIES = libpowerglpng.la
libpowerglpng_ladir = $(includedir)/powergl/png
libpowerglpng_la_HEADERS = \
	png_loader.h
libpowerglpng_la_LDFLAGS = -no-undefined
libpowerglpng_la_SOURCES = \
        png_loader.c
libpowerglpng_la_LIBADD = $(CODE_COVERAGE_LIBS)

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean
