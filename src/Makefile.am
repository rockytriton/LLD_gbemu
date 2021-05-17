lib_LTLIBRARIES = libgbe.la
libgbe_la_SOURCES = emu.c

bin_PROGRAMS = $(top_builddir)/gbe
__top_builddir__gbe_SOURCES = main.c
__top_builddir__gbe_LDADD = libgbe.la

AM_LDFLAGS = -pthread -lSDL2 -lSDL2_ttf
AM_CFLAGS = -I$(top_srcdir)/include -Wall -Werror

