#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([PowerGL], [0.1.0], [omerfarukkalkan@outlook.com.tr])
AC_CONFIG_SRCDIR([src/powergl.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

LT_PREREQ([2.4.6])
LT_INIT

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h string.h])
# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([strtol strtoul])

AC_CONFIG_FILES([Makefile
		src/Makefile
		src/util/Makefile
		src/rendering/Makefile
		src/math/Makefile
		src/asset/Makefile
		src/util/app/Makefile
		src/util/window/Makefile
		src/util/window/xorg/Makefile])
AC_OUTPUT
