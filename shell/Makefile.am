# $Id: Makefile.am,v 1.10 2004/09/06 20:30:53 erik Exp $

bin_PROGRAMS = gems

gems_SOURCES = shell.c prefs.c parms.c

noinst_HEADERS = prefs.h parms.h

gems_INCLUDES = @GETOPT_LONG_CFLAGS@
gems_LDFLAGS = -rdynamic @MY_LDFLAGS@ @GETOPT_LONG_LIBS@
gems_LDADD = $(top_builddir)/common/libgemscommon.la @MY_LDADD@
