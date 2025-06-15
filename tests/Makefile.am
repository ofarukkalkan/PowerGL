# Automake file for unit tests
AM_CPPFLAGS = \
    -I$(top_srcdir) \
    $(GTEST_CFLAGS)
AM_CXXFLAGS = -std=c++17

check_PROGRAMS = gtest_mat4_inv
TESTS = $(check_PROGRAMS)

gtest_mat4_inv_SOURCES = gtest_mat4_inv.cpp

gtest_mat4_inv_LDADD = $(top_builddir)/src/math/libpowerglmath.la $(GTEST_LIBS) -lm

# Run tests via make check
