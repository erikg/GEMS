# $Id: Makefile.am,v 1.2 2003/04/05 18:06:01 erik Exp $

gemslibdir = $(libdir)/gems
gemslib_LTLIBRARIES = libgems_face.GNOME_a.la

libgems_face_GNOME_a_la_SOURCES = composewindow.cc main.cc mboxlist.cc mboxtree.cc menu.cc readwindow.cc statusbar.cc toolbar.cc ui.cc
 
noinst_HEADERS=composewindow.hh main.hh mboxlist.hh mboxtree.hh menu.hh readwindow.hh statusbar.hh toolbar.hh ui.hh 

 
INCLUDES =  @GNOME_INCLUDEDIR@ -I$(top_srcdir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\" -I$(top_srcdir)/include
LDFLAGS  = -rdynamic @GNOMEUI_LIBS@ -L/usr/X11R6/lib
LDDADD   = @INTLLIBS@ $(top_srcdir)/common/libgemscommon.a
localedir= $(datadir)/locale

