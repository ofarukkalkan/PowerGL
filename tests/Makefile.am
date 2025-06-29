# Automake file for unit tests
AM_CPPFLAGS = \
    -I$(top_srcdir) \
    $(GTEST_CFLAGS) \
    $(CODE_COVERAGE_CPPFLAGS) \
    -DTEST_SRCDIR=\"$(srcdir)\"
AM_CXXFLAGS = -std=c++17 $(CODE_COVERAGE_CXXFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)
CODE_COVERAGE_LCOV_OPTIONS = --ignore-errors mismatch

check_PROGRAMS = gtest_math gtest_collada
noinst_PROGRAMS = vertexcoloredcube_demo
TESTS = $(check_PROGRAMS)

gtest_math_SOURCES = gtest_math.cpp

gtest_math_LDADD = $(top_builddir)/src/math/libpowerglmath.la $(GTEST_LIBS) -lm $(CODE_COVERAGE_LIBS)

gtest_collada_SOURCES = gtest_collada.cpp
gtest_collada_LDADD = \
    $(top_builddir)/src/collada/libpowerglcollada.la \
    $(top_builddir)/src/libpowergl.la \
    $(GTEST_LIBS) -lm $(CODE_COVERAGE_LIBS)

vertexcoloredcube_demo_SOURCES = vertexcoloredcube_demo.c
vertexcoloredcube_demo_LDADD = \
    $(top_builddir)/src/libpowergl.la -lm $(CODE_COVERAGE_LIBS)

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean

# Test data files shipped with the distribution
EXTRA_DIST = vertexcolored_cube.dae vertexcoloredcube_demo.png

# Remove generated files produced during tests
CLEANFILES = cube_exported.dae exported.dae

# Run tests via make check
