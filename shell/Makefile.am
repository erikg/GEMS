bin_PROGRAMS = gems

gems_SOURCES = shell.c prefs.c parms.c

noinst_HEADERS = prefs.h parms.h

LDFLAGS = -ldl -rdynamic @MY_LDFLAGS@
LDADD = $(top_srcdir)/common/libgemscommon.a @MY_LDADD@
