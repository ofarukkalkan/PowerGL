# Automake file for unit tests
AM_CPPFLAGS = \
    -I$(top_srcdir)/src \
    -I$(top_srcdir)/googletest/googletest \
    -I$(top_srcdir)/googletest/googletest/include
AM_CXXFLAGS = -std=c++17

check_LTLIBRARIES = libgtest.la
libgtest_la_SOURCES = $(top_srcdir)/googletest/googletest/src/gtest-all.cc

check_PROGRAMS = gtest_mat4_inv
TESTS = $(check_PROGRAMS)

gtest_mat4_inv_SOURCES = gtest_mat4_inv.cpp

gtest_mat4_inv_LDADD = libgtest.la $(top_builddir)/src/math/libpowerglmath.la -lm

# Run tests via make check
