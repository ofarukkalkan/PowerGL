# Automake file for unit tests
AM_CPPFLAGS = \
    -I$(top_srcdir) \
    $(GTEST_CFLAGS) \
    $(CODE_COVERAGE_CPPFLAGS)
AM_CXXFLAGS = -std=c++17 $(CODE_COVERAGE_CXXFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)
CODE_COVERAGE_LCOV_OPTIONS = --ignore-errors mismatch

check_PROGRAMS = gtest_math
TESTS = $(check_PROGRAMS)

gtest_math_SOURCES = gtest_math.cpp

gtest_math_LDADD = $(top_builddir)/src/math/libpowerglmath.la $(GTEST_LIBS) -lm $(CODE_COVERAGE_LIBS)

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean

# Run tests via make check
