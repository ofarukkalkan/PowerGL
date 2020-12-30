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
AC_CHECK_LIB([m], [sqrtf])
AC_CHECK_LIB([GL], [glEnable])
AC_CHECK_LIB([X11], [XFree])
AC_CHECK_LIB([expat], [XML_Parse])
AC_CHECK_LIB([SDL2], [SDL_Init])
AC_CHECK_LIB([GLEW], [glewInit])
AC_CHECK_LIB([png16], [png_read_image])

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
		src/rendering/Makefile
		src/math/Makefile
		src/collada/Makefile
		src/collada/core/Makefile
		src/window/Makefile
		src/png/Makefile])
AC_OUTPUT
