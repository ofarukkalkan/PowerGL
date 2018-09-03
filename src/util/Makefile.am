AM_CFLAGS = -I$(top_srcdir)/util
SUBDIRS = \
	window

noinst_LTLIBRARIES = libpowerglutil.la
libpowerglutil_ladir = $(includedir)/powergl/util
libpowerglutil_la_HEADERS = \
	util.h
libpowerglutil_la_LDFLAGS = -no-undefined
libpowerglutil_la_SOURCES = \
	util.c
libpowerglutil_la_LIBADD = \
	window/libpowerglutilwindow.la

