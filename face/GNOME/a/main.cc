#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

	// the gnome header
#include <gnome.h>

	// the  C++ headers for this face
#include "ui.hh"

	// C headers for interface
#include "defs.h"
#include "face.h"
#include "db.h"

int face_uses_X(){return TRUE;}

int
face_run (int argc, char *argv[])
{
	ui *myui;
#ifdef ENABLE_NLS
  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
  textdomain (PACKAGE);
#endif

  gnome_init ("gems", VERSION, argc, argv);

  myui = new ui();
  myui->run();
  return 0;
}

