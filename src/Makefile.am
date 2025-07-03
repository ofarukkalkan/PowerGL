AM_CPPFLAGS = -I$(top_srcdir) $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)
SUBDIRS = \
        window \
        rendering \
        ui \
        math \
        collada \
        png

lib_LTLIBRARIES = libpowergl.la
libpowergl_ladir = $(includedir)/powergl
libpowergl_la_HEADERS = \
        powergl.h \
        event.h
libpowergl_la_LDFLAGS = -no-undefined
libpowergl_la_SOURCES = \
	powergl.c
libpowergl_la_LIBADD = \
        window/libpowerglwindow.la \
        rendering/libpowerglrendering.la \
        ui/libpowerglui.la \
        math/libpowerglmath.la \
        collada/libpowerglcollada.la \
        png/libpowerglpng.la \
        $(CODE_COVERAGE_LIBS)

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean

