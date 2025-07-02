AM_CPPFLAGS = -I$(top_srcdir)/ui $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)

noinst_LTLIBRARIES = libpowerglui.la
libpowerglui_ladir = $(includedir)/powergl/ui
libpowerglui_la_HEADERS = \
        scene_hierarchy.h
libpowerglui_la_LDFLAGS = -no-undefined
libpowerglui_la_SOURCES = \
        scene_hierarchy.c \
        nuklear_impl.c
libpowerglui_la_LIBADD = $(CODE_COVERAGE_LIBS)

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean
