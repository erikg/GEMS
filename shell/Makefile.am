bin_PROGRAMS = gems

gems_SOURCES = shell.c prefs.c parms.c

noinst_HEADERS = prefs.h parms.h

INCLUDES = @GNOME_CFLAGS@
LDFLAGS = -rdynamic @MY_LDFLAGS@ @GNOME_LIBS@
LDADD = $(top_srcdir)/common/libgemscommon.a @MY_LDADD@
