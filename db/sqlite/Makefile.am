# $Id: Makefile.am,v 1.2 2011/01/02 17:39:14 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.sqlite.la

libgems_db_sqlite_la_SOURCES = db.sqlite.c

AM_CFLAGS = $(SQLITE3_CFLAGS)
libgems_db_sqlite_la_LIBADD = $(top_builddir)/common/libgemscommon.la @MY_LDADD@
libgems_db_sqlite_la_LDFLAGS = @MY_LDFLAGS@ $(SQLITE3_LDFLAGS)
