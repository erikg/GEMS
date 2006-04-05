# $Id: Makefile.am,v 1.5 2006/04/05 13:21:02 erik Exp $

gemslibdir = $(libdir)/gems

gemslib_LTLIBRARIES = libgems_face.GTK_e.la

libgems_face_GTK_e_la_SOURCES = callbacks.c interface.c main.c support.c
 
noinst_HEADERS = callbacks.h  interface.h  support.h

 
AM_INCLUDES =  @GTK_CFLAGS@ -I$(toplevel_dir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\"
AM_LDFLAGS  = -rdynamic @GTK_LIBS@
AM_LDDADD   = @INTLLIBS@
localedir= $(datadir)/locale
