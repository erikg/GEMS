gemslibdir = $(libdir)/gems
gemslib_LTLIBRARIES = libgems_face.GNOME_xf.la

libgems_face_GNOME_xf_la_SOURCES = callbacks.c interface.c main.c support.c
 
noinst_HEADERS= callbacks.h interface.h support.h

EXTRA_DIST = gems.glade
 
INCLUDES = -I$(toplevel_dir)/intl -DLOCALEDIR=\"$(localedir)\" -DPACKAGE_LOCALE_DIR=\"$(localedir)\"
LDFLAGS  = -rdynamic -L/usr/X11R6/lib @@MY_LDFLAGS@
LDDADD   = @INTLLIBS@ $(toplevel_dir)/common/libgemscommon.a @MY_LDADD@
localedir= $(datadir)/locale

