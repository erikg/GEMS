gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_db.MySQL.la

libgems_db_MySQL_la_SOURCES = db.mysql.c

libgems_db_MySQL_la_LIBADD = @MYSQL_LIBADD@

LDADD = $(top_srcdir)/common/libgemscommon.a @MY_LDADD@
LDFLAGS = @MY_LDFLAGS@
