# $Id: Makefile.am,v 1.5 2004/01/23 00:34:38 erik Exp $

gemslibdir = $(libdir)/gems
gemslib_LTLIBRARIES = libgems_face.GNOME_o.la

libgems_face_GNOME_o_la_SOURCES = callbacks.c extra.c interface.c main.c support.c
noinst_HEADERS= callbacks.h extra.h interface.h support.h
CFLAGS =  -I$(toplevel_dir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\" @GNOME_CFLAGS@
LDFLAGS  = -rdynamic -L/usr/X11R6/lib
LDADD   = $(toplevel_dir)/common/libgemscommon.a @MY_LDADD@
LIBS = @GNOME_LIBS@ @INTLLIBS@

localedir= $(datadir)/locale

EXTRA_DIST = gems.glade
