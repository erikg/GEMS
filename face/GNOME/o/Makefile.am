# $Id: Makefile.am,v 1.4 2003/04/05 18:06:01 erik Exp $

gemslibdir = $(libdir)/gems
gemslib_LTLIBRARIES = libgems_face.GNOME_o.la

libgems_face_GNOME_o_la_SOURCES = callbacks.c extra.c interface.c main.c support.c
 
noinst_HEADERS= callbacks.h extra.h interface.h support.h

EXTRA_DIST = gems.glade
 
INCLUDES =  -I$(toplevel_dir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\" @GNOME_CFLAGS@
LDFLAGS  = -rdynamic -L/usr/X11R6/lib
LDDADD   = @INTLLIBS@ $(toplevel_dir)/common/libgemscommon.a @MY_LDADD@ @GNOME_LIBS@
localedir= $(datadir)/locale

