AM_CFLAGS = -I$(top_srcdir)
SUBDIRS = \
	util

lib_LTLIBRARIES = libpowergl.la
libpowergl_ladir = $(includedir)/powergl
libpowergl_la_HEADERS = \
	powergl.h
libpowergl_la_LDFLAGS = -no-undefined
libpowergl_la_SOURCES = \
	powergl.c
libpowergl_la_LIBADD = \
	util/libpowerglutil.la

