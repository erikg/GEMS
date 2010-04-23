/*
 * $Id: extra.c,v 1.2 2010/04/23 20:48:51 erik Exp $
 */

#include <gtk/gtk.h>

#include "db.h"
#include "defs.h"
#include "extra.h"
#include "ll.h"
#include "message.h"
#include "stringinate.h"
#include "support.h"

GtkTreeStore *store;

void
set_mboxlist(GtkWidget *top)
{
    int x;
    mboxs **mboxlist;
    GtkTreeIter iter;
    GtkWidget *gmbl;

    store = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_STRING);

    mboxlist = (mboxs **) db_read_mboxlist ();
    x = 0;
    while (mboxlist[x] != NULL)
    {
	char buf[64] = {0};
	gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */

	if(mboxlist[x]->hasunread)
	    snprintf(buf, 64, "%d", mboxlist[x]->hasunread);
	gtk_tree_store_set (store, &iter, 0, mboxlist[x]->name, 1, buf, -1); 
	x++;
    }
    gmbl = lookup_widget(top, "mboxlist");
    gtk_tree_view_set_model (GTK_TREE_VIEW (gmbl), GTK_TREE_MODEL(store));
    return;
}
