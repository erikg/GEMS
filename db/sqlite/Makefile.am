# $Id: Makefile.am,v 1.1 2009/09/07 16:58:53 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.sqlite.la

libgems_db_sqlite_la_SOURCES = db.sqlite.c

AM_CFLAGS = 
libgems_db_sqlite_la_LIBADD = $(top_builddir)/common/libgemscommon.la @MY_LDADD@
libgems_db_sqlite_la_LDFLAGS = @MY_LDFLAGS@
