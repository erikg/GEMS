/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2007 Erik Greenwald <erik@smluc.org>               *
 *                                                                           *
 *     This program is free software; you can redistribute it and/or modify  *
 *     it under the terms of the GNU General Public License as published by  *
 *     the Free Software Foundation; either version 2 of the License, or     *
 *     (at your option) any later version.                                   *
 *                                                                           *
 *     This program is distributed in the hope that it will be useful,       *
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *     GNU General Public License for more details.                          *
 *                                                                           *
 *     You should have received a copy of the GNU General Public License     *
 *     along with this program; if not, write to the Free Software           *
 *     Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.             *
 *                                                                           *
 *****************************************************************************/

/*
 * $Id: main.c,v 1.5 2007/02/12 19:26:33 erik Exp $
 */

/*
 * Initial main.c file generated by Glade. Edit as required. Glade will not
 * overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gnome.h>

#include "interface.h"
#include "support.h"

#include "defs.h"
#include "face.h"
#include "db.h"

GtkWidget *gems;

int
face_uses_X ()
{
    return TRUE;
}

int
face_run (int argc, char *argv[])
{
    GtkWidget *tree;
    char **mbox;
    int x;

#ifdef ENABLE_NLS
    bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
    textdomain (PACKAGE);
#endif

    gnome_init ("gems", VERSION, argc, argv);

    /*
     * The following code was added by Glade to create one of each component
     * (except popup menus), just so that you see something after building
     * the project. Delete any components that you don't want shown
     * initially.
     */

    mbox = db_read_mboxlist ();
    gems = create_gems ();

    gtk_widget_show (gems);

    tree = lookup_widget (gems, "tree1");

    x = 0;
    while (mbox[x] != NULL)
    {
	GtkWidget *item;

	item = gtk_tree_item_new_with_label (mbox[x]);
	gtk_tree_append (GTK_TREE (tree), item);
	gtk_widget_show (item);
	free (mbox[x]);
	x++;
    }

    free (mbox);

    {
	GtkWidget *child, *newish;
	GtkPaned *pane;

	pane = GTK_PANED (lookup_widget (gems, "hpaned1"));
	newish = create_scrolledwindow6 ();
	child = pane->child2;
	gtk_widget_destroy (child);
	gtk_widget_show (newish);
	gtk_paned_add2 (pane, newish);
    }

    gtk_main ();
    return 0;
}
