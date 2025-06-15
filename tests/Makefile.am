# Automake file for unit tests
AM_CPPFLAGS = \
    -I$(top_srcdir) \
    $(GTEST_CFLAGS)
AM_CXXFLAGS = -std=c++17

check_PROGRAMS = gtest_math
TESTS = $(check_PROGRAMS)

gtest_math_SOURCES = gtest_math.cpp

gtest_math_LDADD = $(top_builddir)/src/math/libpowerglmath.la $(GTEST_LIBS) -lm

# Run tests via make check
