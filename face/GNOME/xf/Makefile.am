# $Id: Makefile.am,v 1.4 2004/03/03 13:02:10 erik Exp $

gemslibdir = $(libdir)/gems
localedir= $(datadir)/locale

gemslib_LTLIBRARIES = libgems_face.GNOME_xf.la
noinst_HEADERS= callbacks.h interface.h support.h

libgems_face_GNOME_xf_la_SOURCES = callbacks.c interface.c main.c support.c
libgems_face_GNOME_xf_la_INCLUDES = -I$(toplevel_dir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\"
libgems_face_GNOME_xf_la_LDFLAGS  = -rdynamic -L/usr/X11R6/lib @@MY_LDFLAGS@
libgems_face_GNOME_xf_la_LIBADD   = @INTLLIBS@ $(toplevel_dir)/common/libgemscommon.a @MY_LDADD@

EXTRA_DIST = gems.glade
