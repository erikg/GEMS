# $Id: Makefile.am,v 1.5 2004/03/03 13:02:10 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.MySQL.la

libgems_db_MySQL_la_SOURCES = db.mysql.c

libgems_db_MySQL_la_LIBADD = @MYSQL_LIBADD@ $(top_srcdir)/common/libgemscommon.a @MY_LDADD@

libgems_db_MySQL_la_LDFLAGS = @MY_LDFLAGS@
