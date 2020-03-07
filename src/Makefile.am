AM_CFLAGS = -I$(top_srcdir)
SUBDIRS = \
	util \
	rendering \
	math \
	physics \
	collada

lib_LTLIBRARIES = libpowergl.la
libpowergl_ladir = $(includedir)/powergl
libpowergl_la_HEADERS = \
	powergl.h
libpowergl_la_LDFLAGS = -no-undefined
libpowergl_la_SOURCES = \
	powergl.c
libpowergl_la_LIBADD = \
	util/libpowerglutil.la \
	rendering/libpowerglrendering.la \
	math/libpowerglmath.la \
	physics/libpowerglphysics.la \
	collada/libpowerglcollada.la

