# $Id: Makefile.am,v 1.5 2003/04/05 18:06:02 erik Exp $

bin_PROGRAMS = gems

gems_SOURCES = shell.c prefs.c parms.c

noinst_HEADERS = prefs.h parms.h

INCLUDES = @GNOME_CFLAGS@ @GETOPT_LONG_CFLAGS@
LDFLAGS = -rdynamic @MY_LDFLAGS@ @GNOME_LIBS@ @GETOPT_LONG_LIBS@
LDADD = $(top_srcdir)/common/libgemscommon.a @MY_LDADD@
