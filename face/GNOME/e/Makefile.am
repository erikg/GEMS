# $Id: Makefile.am,v 1.3 2004/03/03 13:02:10 erik Exp $

gemslibdir = $(libdir)/gems
localedir= $(datadir)/locale

gemslib_LTLIBRARIES = libgems_face.GNOME_e.la
noinst_HEADERS= callbacks.h  interface.h  support.h

libgems_face_GNOME_e_la_SOURCES =  callbacks.c  interface.c  main.c  support.c
libgems_face_GNOME_e_la_INCLUDES =  @GNOME_INCLUDEDIR@ -I$(toplevel_dir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\"
libgems_face_GNOME_e_la_LDFLAGS  = -rdynamic @GNOMEUI_LIBS@ @MY_LDFLAGS@
libgems_face_GNOME_e_la_LDDADD   = @INTLLIBS@ $(toplevel_dir)/common/libgemscommon.a @MY_LDADD@
 
EXTRA_DIST = gems.glade
