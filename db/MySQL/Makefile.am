# $Id: Makefile.am,v 1.7 2005/01/06 02:39:13 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.MySQL.la

libgems_db_MySQL_la_SOURCES = db.mysql.c

AM_CFLAGS = @MYSQL_CFLAGS@
libgems_db_MySQL_la_LIBADD = @MYSQL_LIBADD@ $(top_srcdir)/common/libgemscommon.la @MY_LDADD@
libgems_db_MySQL_la_LDFLAGS = @MY_LDFLAGS@
