# $Id: Makefile.am,v 1.1 2004/02/01 15:56:09 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.PostgreSQL.la

libgems_db_PostgreSQL_la_SOURCES = db.pgsql.c

libgems_db_PostgreSQL_la_LIBADD = @MYSQL_LIBADD@

LDADD = $(top_srcdir)/common/libgemscommon.a @MY_LDADD@
LDFLAGS = @MY_LDFLAGS@
