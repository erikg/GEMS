# $Id: Makefile.am,v 1.9 2005/01/19 01:15:48 erik Exp $

gemslibdir = $(libdir)/gems
gemslib_LTLIBRARIES = libgems_face.GNOME2_o.la

libgems_face_GNOME2_o_la_SOURCES = callbacks.c interface.c main.c support.c
libgems_face_GNOME2_o_la_LIBADD = @GNOME2_LIBS@ $(INTLLIBS) $(top_builddir)/common/libgemscommon.la @MY_LDADD@
 
noinst_HEADERS= callbacks.h interface.h support.h

EXTRA_DIST = gems.glade gems.gladep
 
AM_CFLAGS = \
        -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
        -DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
        @GNOME2_CFLAGS@

LDADD = -rdynamic
