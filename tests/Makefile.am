# Automake file for unit tests
AM_CPPFLAGS = \
    -I$(top_srcdir) \
    $(GTEST_CFLAGS) \
    $(CODE_COVERAGE_CPPFLAGS) \
    -DTEST_SRCDIR=\"$(srcdir)\"
AM_CXXFLAGS = -std=c++17 $(CODE_COVERAGE_CXXFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)
CODE_COVERAGE_LCOV_OPTIONS = --ignore-errors mismatch

check_PROGRAMS = gtest_math gtest_collada gtest_intersect vertexcoloredcube_demo animatedcube_demo \
    flat_demo gouraud_demo lambert_demo blinnphong_demo
TESTS = gtest_math gtest_collada gtest_intersect run_vertexcoloredcube_headless.sh run_flatshadedcube_headless.sh \
    run_gouraudshadedcube_headless.sh run_lambertshadedcube_headless.sh run_blinnphongshadedcube_headless.sh

gtest_math_SOURCES = gtest_math.cpp

gtest_math_LDADD = $(top_builddir)/src/math/libpowerglmath.la $(GTEST_LIBS) -lm $(CODE_COVERAGE_LIBS)

gtest_collada_SOURCES = gtest_collada.cpp
gtest_collada_LDADD = \
    $(top_builddir)/src/collada/libpowerglcollada.la \
    $(top_builddir)/src/libpowergl.la \
    $(GTEST_LIBS) -lm $(CODE_COVERAGE_LIBS)

gtest_intersect_SOURCES = gtest_intersect.cpp
gtest_intersect_LDADD = \
    $(top_builddir)/src/math/libpowerglmath.la $(GTEST_LIBS) -lm $(CODE_COVERAGE_LIBS)

vertexcoloredcube_demo_SOURCES = vertexcoloredcube_demo.c
vertexcoloredcube_demo_LDADD = \
    $(top_builddir)/src/libpowergl.la -lm $(CODE_COVERAGE_LIBS)

animatedcube_demo_SOURCES = animatedcube_demo.c
animatedcube_demo_LDADD = \
    $(top_builddir)/src/libpowergl.la -lm $(CODE_COVERAGE_LIBS)

flat_demo_SOURCES = flat_demo.c
flat_demo_LDADD = \
    $(top_builddir)/src/libpowergl.la -lm $(CODE_COVERAGE_LIBS)

gouraud_demo_SOURCES = gouraud_demo.c
gouraud_demo_LDADD = \
    $(top_builddir)/src/libpowergl.la -lm $(CODE_COVERAGE_LIBS)

lambert_demo_SOURCES = lambert_demo.c
lambert_demo_LDADD = \
    $(top_builddir)/src/libpowergl.la -lm $(CODE_COVERAGE_LIBS)

blinnphong_demo_SOURCES = blinnphong_demo.c
blinnphong_demo_LDADD = \
    $(top_builddir)/src/libpowergl.la -lm $(CODE_COVERAGE_LIBS)

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean

# Test data files shipped with the distribution
EXTRA_DIST = vertexcolored_cube.dae vertexcoloredcube_demo.png \
    blinnphongshadedcube.png gouraudshadedcube.png lambertshadedcube.png \
    run_vertexcoloredcube_headless.sh run_flatshadedcube_headless.sh \
    run_gouraudshadedcube_headless.sh run_lambertshadedcube_headless.sh \
    run_blinnphongshadedcube_headless.sh

# Remove generated files produced during tests
CLEANFILES = cube_exported.dae exported.dae frame_*.png flat_frame_*.png \
    gouraud_frame_*.png lambert_frame_*.png blinnphong_frame_*.png

# Run tests via make check
