# $Id: Makefile.am,v 1.6 2004/01/23 01:01:31 erik Exp $

gemslibdir = $(libdir)/gems
gemslib_LTLIBRARIES = libgems_face.GNOME2_o.la

libgems_face_GNOME2_o_la_SOURCES = callbacks.c interface.c main.c support.c
 
noinst_HEADERS= callbacks.h interface.h support.h

EXTRA_DIST = gems.glade gems.gladep
 
INCLUDES = \
        -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
        -DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
        @GNOME2_CFLAGS@

LDFLAGS  = -rdynamic -L/usr/X11R6/lib
LDADD = @GNOME2_LIBS@ $(INTLLIBS) $(toplevel_dir)/common/libgemscommon.a @MY_LDADD@


