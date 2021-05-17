lib_LTLIBRARIES = libgbe.la
libgbe_la_SOURCES = emu.c

bin_PROGRAMS = gbe
gbe_SOURCES = main.c
gbe_LDADD = libgbe.la

AM_LDFLAGS = -pthread -lSDL2 -lSDL2_ttf
AM_CFLAGS = -I$(top_srcdir)/include -Wall -Werror

