# $Id: Makefile.am,v 1.2 2004/02/01 18:13:29 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.PostgreSQL.la

libgems_db_PostgreSQL_la_SOURCES = db.pgsql.c

libgems_db_PostgreSQL_la_LIBADD = @POSTGRESQL_LIBADD@

LDADD = $(top_srcdir)/common/libgemscommon.a @POSTGRE_LDADD@
LDFLAGS = @POSTGRE_LDFLAGS@
