AM_CFLAGS = -I$(top_srcdir)/util/window
SUBDIRS = \
	xorg

noinst_LTLIBRARIES = libpowerglutilwindow.la
libpowerglutilwindow_ladir = $(includedir)/powergl/util/window
libpowerglutilwindow_la_HEADERS = \
	window.h
libpowerglutilwindow_la_LDFLAGS = -no-undefined
libpowerglutilwindow_la_SOURCES = \
	window.c
libpowerglutilwindow_la_LIBADD = \
	xorg/libpowerglutilwindowxorg.la

