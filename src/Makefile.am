AM_CFLAGS = -I$(top_srcdir)
SUBDIRS = \
	window \
	rendering \
	math \
	collada

lib_LTLIBRARIES = libpowergl.la
libpowergl_ladir = $(includedir)/powergl
libpowergl_la_HEADERS = \
	powergl.h
libpowergl_la_LDFLAGS = -no-undefined
libpowergl_la_SOURCES = \
	powergl.c
libpowergl_la_LIBADD = \
	window/libpowerglwindow.la \
	rendering/libpowerglrendering.la \
	math/libpowerglmath.la \
	collada/libpowerglcollada.la

