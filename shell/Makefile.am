# $Id: Makefile.am,v 1.8 2004/02/01 19:07:45 erik Exp $

bin_PROGRAMS = gems

gems_SOURCES = shell.c prefs.c parms.c

noinst_HEADERS = prefs.h parms.h

INCLUDES = @GETOPT_LONG_CFLAGS@
LDFLAGS = -rdynamic @MY_LDFLAGS@ @GETOPT_LONG_LIBS@
LDADD = $(top_srcdir)/common/libgemscommon.a @MY_LDADD@
