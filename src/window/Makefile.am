AM_CPPFLAGS = -I$(top_srcdir)/window $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)
noinst_LTLIBRARIES = libpowerglwindow.la
libpowerglwindow_ladir = $(includedir)/powergl/window
libpowerglwindow_la_HEADERS = \
        window.h \
        headless.h
libpowerglwindow_la_LDFLAGS = -no-undefined
libpowerglwindow_la_SOURCES = \
        window.c \
        headless.c
libpowerglwindow_la_LIBADD = $(CODE_COVERAGE_LIBS) -lEGL

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean

