# $Id: Makefile.am,v 1.11 2010/05/28 00:20:04 erik Exp $

gemslibdir = $(libdir)/gems
gemslib_LTLIBRARIES = libgems_face.GNOME2_o.la

libgems_face_GNOME2_o_la_SOURCES = main.c
libgems_face_GNOME2_o_la_LIBADD = @GNOME2_LIBS@ $(INTLLIBS) $(top_builddir)/common/libgemscommon.la @MY_LDADD@
 
noinst_HEADERS=

EXTRA_DIST = gems.glade gems.gladep
 
AM_CFLAGS = \
        -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
        -DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
        @GNOME2_CFLAGS@

LDADD = -rdynamic
