# $Id: Makefile.am,v 1.9 2004/03/03 13:02:11 erik Exp $

bin_PROGRAMS = gems

gems_SOURCES = shell.c prefs.c parms.c

noinst_HEADERS = prefs.h parms.h

gems_INCLUDES = @GETOPT_LONG_CFLAGS@
gems_LDFLAGS = -rdynamic @MY_LDFLAGS@ @GETOPT_LONG_LIBS@
gems_LDADD = $(top_srcdir)/common/libgemscommon.la @MY_LDADD@
