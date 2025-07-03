AM_CPPFLAGS = -I$(top_srcdir)/window $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)
noinst_LTLIBRARIES = libpowerglwindow.la
libpowerglwindow_ladir = $(includedir)/powergl/window
libpowerglwindow_la_HEADERS = \
        window.h \
        headless.h \
        event.h
libpowerglwindow_la_LDFLAGS = -no-undefined
libpowerglwindow_la_SOURCES = \
        window.c \
        headless.c
if GLFW_BACKEND
libpowerglwindow_la_SOURCES += window_glfw.c
libpowerglwindow_la_LIBADD = $(CODE_COVERAGE_LIBS) -lEGL $(GLFW_LIBS)
AM_CPPFLAGS += $(GLFW_CFLAGS) -DPOWERGL_BACKEND_GLFW
else
libpowerglwindow_la_SOURCES += window_sdl.c
libpowerglwindow_la_LIBADD = $(CODE_COVERAGE_LIBS) -lEGL
AM_CPPFLAGS += -DPOWERGL_BACKEND_SDL
endif

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean

