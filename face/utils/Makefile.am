gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_face.cleantables.la libgems_face.normalize.la libgems_face.showmail.la libgems_face.spool2sql.la libgems_face.sql2spool.la

libgems_face_cleantables_la_SOURCES = cleantables.c  
libgems_face_normalize_la_SOURCES = normalize.c
libgems_face_showmail_la_SOURCES = showmail.c  
libgems_face_spool2sql_la_SOURCES = spool2sql.c  
libgems_face_sql2spool_la_SOURCES = sql2spool.c  

LDFLAGS = -rdynamic @MY_LDFLAGS@
LDADD = @MY_LDADD@
