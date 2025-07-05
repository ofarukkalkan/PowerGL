AM_CPPFLAGS = -I$(top_srcdir)/rendering $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)

noinst_LTLIBRARIES = libpowerglrendering.la
libpowerglrendering_ladir = $(includedir)/powergl/rendering
libpowerglrendering_la_HEADERS = \
	object.h \
	pipeline.h \
	visualscene.h \
	dae2object.h \
        objectlibrary.h \
        3dtext.h \
        grid.h
libpowerglrendering_la_LDFLAGS = -no-undefined
libpowerglrendering_la_SOURCES = \
        object.c \
        pipeline.c \
        visualscene.c \
        dae2object.c \
        objectlibrary.c \
        3dtext.c \
        grid.c
libpowerglrendering_la_LIBADD = $(CODE_COVERAGE_LIBS)

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean
