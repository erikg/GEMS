# $Id: Makefile.am,v 1.3 2004/03/03 14:24:24 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.PostgreSQL.la

libgems_db_PostgreSQL_la_SOURCES = db.pgsql.c
libgems_db_PostgreSQL_la_LIBADD = @POSTGRESQL_LIBADD@ $(top_srcdir)/common/libgemscommon.a @POSTGRE_LDADD@
libgems_db_PostgreSQL_la_LDFLAGS = @POSTGRE_LDFLAGS@
