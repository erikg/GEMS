# $Id: Makefile.am,v 1.11 2005/04/02 20:19:04 erik Exp $

localedir= $(datadir)/locale
gemslibdir = $(libdir)/gems
gemslib_LTLIBRARIES = libgems_face.GNOME_o.la

libgems_face_GNOME_o_la_SOURCES = callbacks.c extra.c interface.c main.c support.c
libgems_face_GNOME_o_la_LIBADD = @INTLLIBS@ $(top_builddir)/common/libgemscommon.la @GNOME_LIBS@ -L/usr/X11R6/lib
AM_CFLAGS =  -I$(top_srcdir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\" @GNOME_CFLAGS@
LDADD = -rdynamic

noinst_HEADERS= callbacks.h extra.h interface.h support.h

EXTRA_DIST = gems.glade
 
