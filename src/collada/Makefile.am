AM_CPPFLAGS = -I$(top_srcdir) $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)
SUBDIRS = core

noinst_LTLIBRARIES = libpowerglcollada.la

libpowerglcollada_la_LIBADD = core/libpowerglcolladacore.la $(CODE_COVERAGE_LIBS)

libpowerglcollada_ladir = $(includedir)/powergl/collada/
libpowerglcollada_la_HEADERS = \
	importer.h \
	exporter.h \
	dom_connector.h \
	parse_utils.h \
	collada.h

libpowerglcollada_la_SOURCES = \
	importer.c \
	exporter.c \
	dom_connector.c \
	parse_utils.c
libpowerglcollada_la_LDFLAGS = -no-undefined

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean
