# $Id: Makefile.am,v 1.13 2007/01/22 21:52:34 erik Exp $

localedir= $(datadir)/locale
gemslibdir = $(libdir)/gems
gemslib_LTLIBRARIES = libgems_face.GNOME_o.la

libgems_face_GNOME_o_la_SOURCES = callbacks.c extra.c interface.c main.c support.c
libgems_face_GNOME_o_la_LIBADD = $(top_builddir)/common/libgemscommon.la @GNOME_LIBS@ -L/usr/X11R6/lib
AM_CFLAGS =  -I$(top_srcdir)/include -I$(top_srcdir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\" @GNOME_CFLAGS@
LDADD = -rdynamic

noinst_HEADERS= callbacks.h extra.h interface.h support.h

EXTRA_DIST = gems.glade
 
