# $Id: Makefile.am,v 1.6 2004/01/23 00:41:28 erik Exp $

bin_PROGRAMS = gems

gems_SOURCES = shell.c prefs.c parms.c

noinst_HEADERS = prefs.h parms.h

INCLUDES = @GETOPT_LONG_CFLAGS@
LDFLAGS = -rdynamic @GETOPT_LONG_LIBS@
LDADD = $(top_srcdir)/common/libgemscommon.a
