# $Id: Makefile.am,v 1.2 2003/04/05 18:06:01 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_face.GTK_e.la

libgems_face_GTK_e_la_SOURCES = callbacks.c interface.c main.c support.c
 
noinst_HEADERS = callbacks.h  interface.h  support.h

 
INCLUDES =  @GTK_CFLAGS@ -I$(toplevel_dir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\"
LDFLAGS  = -rdynamic @GTK_LIBS@
LDDADD   = @INTLLIBS@
localedir= $(datadir)/locale
