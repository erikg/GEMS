# $Id: Makefile.am,v 1.8 2005/04/02 20:19:21 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.MySQL.la

libgems_db_MySQL_la_SOURCES = db.mysql.c

AM_CFLAGS = @MYSQL_CFLAGS@
libgems_db_MySQL_la_LIBADD = @MYSQL_LIBADD@ $(top_builddir)/common/libgemscommon.la @MY_LDADD@
libgems_db_MySQL_la_LDFLAGS = @MY_LDFLAGS@
