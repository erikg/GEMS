# $Id: Makefile.am,v 1.4 2005/04/02 20:19:17 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.PostgreSQL.la

libgems_db_PostgreSQL_la_SOURCES = db.pgsql.c
libgems_db_PostgreSQL_la_LIBADD = @POSTGRESQL_LIBADD@ $(top_builddir)/common/libgemscommon.la @POSTGRE_LDADD@
libgems_db_PostgreSQL_la_LDFLAGS = @POSTGRE_LDFLAGS@
