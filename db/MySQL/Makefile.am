# $Id: Makefile.am,v 1.6 2004/05/21 13:27:52 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.MySQL.la

libgems_db_MySQL_la_SOURCES = db.mysql.c

AM_CFLAGS = @MYSQL_CFLAGS@
libgems_db_MySQL_la_LIBADD = @MYSQL_LIBADD@ $(top_srcdir)/common/libgemscommon.a @MY_LDADD@
libgems_db_MySQL_la_LDFLAGS = @MY_LDFLAGS@
