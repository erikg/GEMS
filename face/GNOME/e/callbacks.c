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
 * $Id: callbacks.c,v 1.5 2007/02/12 19:26:33 erik Exp $
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gnome.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "defs.h"
#include "message.h"
#include "db.h"

extern GtkWidget *gems;

void
on_new_file1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_open1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_save1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_save_as1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_exit1_activate (GtkMenuItem * menuitem, gpointer user_data)
{
    gtk_main_quit ();

}


void
on_cut1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_copy1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_paste1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_clear1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_properties1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_preferences1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_about1_activate (GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_tree1_select_child (GtkTree * tree, GtkWidget * widget, gpointer user_data)
{

    GtkWidget *ctree, *hpaned, *stat, *ch2;
    GtkCTree *tmp;
    GtkCList *clist;
    gchar *text[3];
    synopsis **syn;
    int mbox, x = 0;

    // if (user_data != NULL)
    // mbox = *user_data;
    // 
    else
    mbox = 1;
    hpaned = lookup_widget (gems, "hpaned1");
    stat = lookup_widget (gems, "appbar1");
    ch2 = GTK_PANED (hpaned)->child2;

    if (GTK_IS_CTREE (GTK_BIN (ch2)->child))
    {
	ctree = GTK_BIN (ch2)->child;
    } else
    {
	gtk_widget_destroy (ch2);
	ctree = create_scrolledwindow6 ();
	gtk_widget_show (ctree);
	gtk_paned_add2 (GTK_PANED (hpaned), ctree);
	ctree = GTK_BIN (ctree)->child;
    }

    gnome_appbar_push (GNOME_APPBAR (stat), "Reading synopsis");
    while (gtk_events_pending ())
	gtk_main_iteration ();

    syn = (synopsis **) db_read_synopsis (mbox);

    tmp = GTK_CTREE (ctree);
    clist = &tmp->clist;

    gtk_clist_clear (clist);

    gtk_clist_freeze (clist);

    while (syn[x] != NULL)
    {
	GtkCTreeNode *n;

	text[0] = syn[x]->sender;
	text[1] = syn[x]->date;
	text[2] = syn[x]->subject;

	n = gtk_ctree_insert_node (GTK_CTREE (ctree), NULL, NULL, text, 5,
				   NULL, NULL, NULL, NULL, TRUE, TRUE);
	gtk_ctree_node_set_row_data (GTK_CTREE (ctree), n, syn[x]);
	x++;
    }
    free (syn);

    gtk_clist_thaw (clist);
    gnome_appbar_pop (GNOME_APPBAR (stat));

    return;
}



void
show_propertbox (GtkMenuItem * menuitem, gpointer user_data)
{
    gtk_widget_show (create_propertybox1 ());
}


void
show_about (GtkMenuItem * menuitem, gpointer user_data)
{
    gtk_widget_show (create_about2 ());
}


void
on_trash_clicked (GtkButton * button, gpointer user_data)
{

}


void
on_check_clicked (GtkButton * button, gpointer user_data)
{

}


void
on_compose_clicked (GtkButton * button, gpointer user_data)
{
    GtkWidget *hpaned, *ch2, *newish;

    hpaned = lookup_widget (gems, "hpaned1");
    ch2 = GTK_PANED (hpaned)->child2;
    gtk_widget_destroy (ch2);
    newish = create_vbox2 ();
    gtk_widget_show (newish);
    gtk_paned_add2 (GTK_PANED (hpaned), newish);
}


void
on_reply_clicked (GtkButton * button, gpointer user_data)
{

}


void
on_forward_clicked (GtkButton * button, gpointer user_data)
{

}


void
on_prev_clicked (GtkButton * button, gpointer user_data)
{

}


void
on_next_clicked (GtkButton * button, gpointer user_data)
{

}


void
on_attach_clicked (GtkButton * button, gpointer user_data)
{

}


void
on_addr_clicked (GtkButton * button, gpointer user_data)
{

}


void
on_print_clicked (GtkButton * button, gpointer user_data)
{

}


void
on_help_clicked (GtkButton * button, gpointer user_data)
{

}


gboolean
on_clist_event (GtkWidget * widget, GdkEvent * event, gpointer user_data)
{
    if ((event) && (event->type == GDK_2BUTTON_PRESS))
    {
	synopsis *s;
	GtkCTreeNode *n;
	GtkWidget *hpaned, *ch2, *newish;
	GtkWidget *from, *subj, *date, *recipt, *body;
	char *shtuff;

	n = gtk_ctree_node_nth (GTK_CTREE (widget),
				(&(GTK_CTREE (widget)->clist))->focus_row);
	s = (synopsis *) gtk_ctree_node_get_row_data (GTK_CTREE (widget), n);

	hpaned = lookup_widget (gems, "hpaned1");
	ch2 = GTK_PANED (hpaned)->child2;
	gtk_widget_destroy (ch2);
	newish = create_readbox ();
	gtk_widget_show (newish);
	gtk_paned_add2 (GTK_PANED (hpaned), newish);

	from =
	    (GtkWidget *) gtk_object_get_data (GTK_OBJECT (newish), "from");
	subj =
	    (GtkWidget *) gtk_object_get_data (GTK_OBJECT (newish),
					       "subject");
	date =
	    (GtkWidget *) gtk_object_get_data (GTK_OBJECT (newish), "date");
	recipt =
	    (GtkWidget *) gtk_object_get_data (GTK_OBJECT (newish), "recipt");
	body =
	    (GtkWidget *) gtk_object_get_data (GTK_OBJECT (newish), "body");

	gtk_entry_set_text (GTK_ENTRY (from), s->sender);
	gtk_entry_set_text (GTK_ENTRY (subj), s->subject);
	gtk_entry_set_text (GTK_ENTRY (date), s->date);
	// gtk_entry_set_text (GTK_ENTRY (recipt), s->);

	shtuff = (char *) db_read_body (s->id);
	gtk_text_insert (GTK_TEXT (body), NULL, NULL, NULL, shtuff, -1);

	return TRUE;
    }
    return FALSE;
}
