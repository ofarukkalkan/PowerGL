AM_CPPFLAGS = -I$(top_srcdir)/math $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)
noinst_LTLIBRARIES = libpowerglmath.la
libpowerglmath_ladir = $(includedir)/powergl/math/
libpowerglmath_la_HEADERS = \
	mat4x4.h \
	vec3.h \
	intersect.h
libpowerglmath_la_SOURCES = \
        mat4x4.c \
        vec3.c \
        intersect.c
libpowerglmath_la_LDFLAGS = -no-undefined
libpowerglmath_la_LIBADD = $(CODE_COVERAGE_LIBS)

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean
