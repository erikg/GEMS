# $Id: Makefile.am,v 1.13 2004/10/17 17:14:57 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = \
	libgems_face.check.la \
	libgems_face.cleantables.la \
	libgems_face.cull.la \
	libgems_face.initdb.la \
	libgems_face.normalize.la \
	libgems_face.pop3check.la \
	libgems_face.showmail.la \
	libgems_face.snarf.la \
	libgems_face.spool2sql.la \
	libgems_face.spool2sqlfast.la \
	libgems_face.sql2spool.la \
	libgems_face.synhash.la \
	libgems_face.test.la

libgems_face_check_la_SOURCES = check.c  
libgems_face_cleantables_la_SOURCES = cleantables.c  
libgems_face_cull_la_SOURCES = cull.c  
libgems_face_initdb_la_SOURCES = initdb.c  
libgems_face_normalize_la_SOURCES = normalize.c
libgems_face_pop3check_la_SOURCES = pop3check.c
libgems_face_showmail_la_SOURCES = showmail.c  
libgems_face_snarf_la_SOURCES = snarf.c  
libgems_face_spool2sql_la_SOURCES = spool2sql.c  
libgems_face_spool2sqlfast_la_SOURCES = spool2sqlfast.c  
libgems_face_sql2spool_la_SOURCES = sql2spool.c  
libgems_face_synhash_la_SOURCES = synhash.c  
libgems_face_test_la_SOURCES = test.c  

LDFLAGS = -rdynamic @MY_LDFLAGS@
LIBADD = @MY_LDADD@
