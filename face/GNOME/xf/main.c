/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>

#include "interface.h"
#include "support.h"

#include "defs.h"

int face_uses_X(){return GEMS_TRUE;}

void oops(char *gems_error, char *subsystem_error)
{
	printf("%s\n%s\n\n",gems_error,subsystem_error);
	exit(-1);
}

int
face_run (int argc, char *argv[])
{
  GtkWidget *gems;

#ifdef ENABLE_NLS
  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
  textdomain (PACKAGE);
#endif

  gnome_init ("gems", VERSION, argc, argv);

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  gems = create_gems ();
  gtk_widget_show (gems);

  gtk_main ();
  return 0;
}

