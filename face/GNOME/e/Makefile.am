# $Id: Makefile.am,v 1.2 2003/04/05 18:06:01 erik Exp $

gemslibdir = $(libdir)/gems
gemslib_LTLIBRARIES = libgems_face.GNOME_e.la

libgems_face_GNOME_e_la_SOURCES =  callbacks.c  interface.c  main.c  support.c
 
noinst_HEADERS= callbacks.h  interface.h  support.h

EXTRA_DIST = gems.glade
 
INCLUDES =  @GNOME_INCLUDEDIR@ -I$(toplevel_dir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\"
LDFLAGS  = -rdynamic @GNOMEUI_LIBS@ @MY_LDFLAGS@
LDDADD   = @INTLLIBS@ $(toplevel_dir)/common/libgemscommon.a @MY_LDADD@
localedir= $(datadir)/locale

