# $Id: Makefile.am,v 1.5 2006/07/16 19:46:38 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.PostGreSQL.la

libgems_db_PostGreSQL_la_SOURCES = db.pgsql.c
libgems_db_PostGreSQL_la_LIBADD = @POSTGRESQL_LIBADD@ $(top_builddir)/common/libgemscommon.la
