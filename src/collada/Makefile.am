AM_CFLAGS = -I$(top_srcdir)
SUBDIRS = core

noinst_LTLIBRARIES = libpowerglcollada.la

libpowerglcollada_la_LIBADD = core/libpowerglcolladacore.la

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
