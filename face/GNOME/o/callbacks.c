
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2010 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: callbacks.c,v 1.32 2011/01/05 01:31:02 erik Exp $
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <ctype.h>
#include <gnome.h>

#include "defs.h"		/* gems includes */
#include "message.h"
#include "db.h"	/* ??? */

#include "callbacks.h"		/* gnome/o includes */
#include "interface.h"
#include "support.h"
#include "rules.h"

extern GtkWidget *gems;		/* nasty. Must preceed extra.h */

#include "extra.h"

#define SORT_DIRECTION 128
extern unsigned char sort;

void
on_new_file1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_open1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_save1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_save_as1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_cut1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_copy1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_paste1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_clear1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_properties1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_preferences1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_about1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data))
{
    gtk_widget_show (create_about2 ());
}

gboolean
on_mailbox_event (GtkWidget * widget, GdkEvent * event, gpointer UNUSED(user_data))
{
    if ((event) && (event->type == GDK_2BUTTON_PRESS))
    {
	putmail (widget);
	return TRUE;
    }
    return FALSE;
}

gboolean
on_gems_quit (GtkWidget * UNUSED(widget), GdkEvent * UNUSED(event), gpointer UNUSED(user_data))
{
    char *x;

    x = (char *)malloc (1024);
    sprintf (x, "%d",
	GTK_PANED (lookup_widget (gems, "hpaned1"))->handle_xpos + 2);
    db_pref_set ("GNOME_o_hpaned_pos", x);
    sprintf (x, "%d",
	GTK_PANED (lookup_widget (gems, "vpaned1"))->handle_ypos + 2);
    db_pref_set ("GNOME_o_vpaned_pos", x);
    sprintf (x, "%d", GTK_WIDGET (gems)->allocation.width);
    db_pref_set ("GNOME_o_gems_width", x);
    sprintf (x, "%d", GTK_WIDGET (gems)->allocation.height);
    db_pref_set ("GNOME_o_gems_height", x);
    sprintf (x, "%d", GTK_WIDGET (gems)->allocation.x);
    db_pref_set ("GNOME_o_gems_xpos", x);
    sprintf (x, "%d", GTK_WIDGET (gems)->allocation.y);
    db_pref_set ("GNOME_o_gems_ypos", x);
    sprintf (x, "%d", get_mboxlistbehavior());
    db_pref_set ("mboxdefaultaction", x);
    sprintf (x, "%d",
	GTK_CLIST (&
	    ((GTK_CTREE (lookup_widget (gems, "mailbox")))->
		clist))->column[0].width);
    db_pref_set ("GNOME_o_maillist_col1", x);
    sprintf (x, "%d",
	GTK_CLIST (&
	    ((GTK_CTREE (lookup_widget (gems, "mailbox")))->
		clist))->column[1].width);
    db_pref_set ("GNOME_o_maillist_col2", x);

    free (x);
    gtk_main_quit ();
    return FALSE;
}

/* a mailbox was clicked 
 * TODO: this is called twice on keypress... up and down?
 */
void
on_mailboxlist_tree_select_row (GtkCTree * ctree,
    GList * UNUSED(node), gint UNUSED(column), gpointer UNUSED(user_data))
{
    GtkWidget *mailbox, *stat;
    GtkCTreeNode *n;
    GtkCList *clist;
    GtkWidget *appbar;
    gchar *text[3];
    synopsis **syn;
    int x = 0, mboxcount;
    mboxview *m;

    n = gtk_ctree_node_nth (ctree, (&(ctree->clist))->focus_row);
    m = (mboxview *) gtk_ctree_node_get_row_data (ctree, n);

    if (m == NULL)
    {
	printf (_("Bad mbox (null)\n"));
	exit (-1);
    }
    stat = lookup_widget (gems, "appbar1");
    mailbox = lookup_widget (gems, "mailbox");
    appbar = lookup_widget (gems, "appbar1");

    /*** TODO *** clear the mail things */
    putmail (NULL);

    gnome_appbar_push (GNOME_APPBAR (stat), _("Reading synopsis"));
    while (gtk_events_pending ())
	gtk_main_iteration ();
    syn = (synopsis **) db_read_synopsis (m->mailbox->id, m->status);
    gnome_appbar_pop (GNOME_APPBAR (stat));
    gnome_appbar_push (GNOME_APPBAR (stat), _("Displaying mailbox"));
    while (gtk_events_pending ())
	gtk_main_iteration ();

    clist = &GTK_CTREE (mailbox)->clist;

    gtk_clist_clear (clist);
    while (gtk_events_pending ())
	gtk_main_iteration ();

    gtk_clist_freeze (clist);

    if(syn) {
	mboxcount = 0;
	while (syn[mboxcount] != NULL)
	    mboxcount++;

	while (syn[x] != NULL)
	{
	    GtkCTreeNode *n;

	    text[0] = syn[x]->sender;
	    text[1] = syn[x]->date;
	    text[2] = syn[x]->subject;

	    n = gtk_ctree_insert_node (GTK_CTREE (mailbox), NULL, NULL, text, 5,
		    NULL, NULL, NULL, NULL, TRUE, TRUE);
	    gtk_ctree_node_set_row_data (GTK_CTREE (mailbox), n, syn[x]);

	    gnome_appbar_set_progress (GNOME_APPBAR (appbar),
		    (float)x / (float)mboxcount);
	    /*
	     * pump the status bar 
	     */
	    if (gtk_events_pending ())
		gtk_main_iteration ();

	    x++;
	}
	free (syn);
    }
    gtk_clist_set_sort_column (clist, 1);
    gtk_clist_set_sort_type (clist, GTK_SORT_ASCENDING);
    gtk_clist_sort (clist);
    gtk_clist_thaw (clist);
    update_mboxlist (NULL);
    gnome_appbar_set_progress (GNOME_APPBAR (appbar), 0.0);
    gnome_appbar_pop (GNOME_APPBAR (stat));

    /*
     * gtk_signal_handler_unblock(GTK_OBJECT(ctree), select_row);
     */

}

void
on_toolbar_prev_clicked (GtkButton * UNUSED(button), gpointer UNUSED(user_data))
{
    GtkCTree *ctree;
    GtkCTreeNode *n;

    ctree = GTK_CTREE (lookup_widget (gems, "mailbox"));

    if (ctree->clist.rows < 1)
	return;

    n = gtk_ctree_node_nth (GTK_CTREE (ctree),
	(&(GTK_CTREE (ctree)->clist))->focus_row);
    gtk_ctree_unselect (GTK_CTREE (ctree), n);
    if ((&(GTK_CTREE (ctree)->clist))->focus_row > 0)
	(&(GTK_CTREE (ctree)->clist))->focus_row--;

    n = gtk_ctree_node_nth (GTK_CTREE (ctree),
	(&(GTK_CTREE (ctree)->clist))->focus_row);
    gtk_ctree_select (GTK_CTREE (ctree), n);

    if (gtk_ctree_node_is_visible (GTK_CTREE (ctree), n) !=
	GTK_VISIBILITY_FULL)
	gtk_ctree_node_moveto (GTK_CTREE (ctree), n, 0, 0, 0);

    putmail (GTK_WIDGET (ctree));
    return;
}

void
on_toolbar_next_clicked (GtkButton * UNUSED(button), gpointer UNUSED(user_data))
{
    GtkCTree *ctree;
    GtkCTreeNode *n;

    ctree = GTK_CTREE (lookup_widget (gems, "mailbox"));
    if (ctree->clist.rows == 0)
	return;
    n = gtk_ctree_node_nth (GTK_CTREE (ctree),
	(&(GTK_CTREE (ctree)->clist))->focus_row);

    gtk_ctree_unselect (GTK_CTREE (ctree), n);
    if ((&(GTK_CTREE (ctree)->clist))->focus_row <
	((&(GTK_CTREE (ctree)->clist))->rows - 1))
	(&(GTK_CTREE (ctree)->clist))->focus_row++;
    n = gtk_ctree_node_nth (GTK_CTREE (ctree),
	(&(GTK_CTREE (ctree)->clist))->focus_row);
    gtk_ctree_select (GTK_CTREE (ctree), n);

    if (gtk_ctree_node_is_visible (GTK_CTREE (ctree),
	    n) != GTK_VISIBILITY_FULL)
	gtk_ctree_node_moveto (GTK_CTREE (ctree), n, 0, 1, 0);

    putmail (GTK_WIDGET (ctree));
    return;
}

gboolean
on_mailbox_key_press_event (GtkWidget * widget,
    GdkEventKey * event, gpointer UNUSED(user_data))
{
    switch (event->keyval)
    {
    case GDK_Return:
    case GDK_space:
	putmail (widget);
	break;
    case GDK_N:
    case GDK_n:
    case GDK_Right:
	on_toolbar_next_clicked (NULL, NULL);
	break;
    case GDK_P:
    case GDK_p:
    case GDK_Left:
	on_toolbar_prev_clicked (NULL, NULL);
	break;
    case GDK_Down:
	{
	    GtkWidget *text;
	    GtkAdjustment *adj;

	    text = lookup_widget (gems, "text1");
	    adj = GTK_TEXT (text)->vadj;
	    gtk_adjustment_set_value (adj, adj->value + adj->step_increment);
	}
	break;
    case GDK_Page_Down:
	{
	    GtkWidget *text;
	    GtkAdjustment *adj;

	    text = lookup_widget (gems, "text1");
	    adj = GTK_TEXT (text)->vadj;
	    gtk_adjustment_set_value (adj, adj->value + adj->page_increment);
	}
	break;
    case GDK_Up:
	{
	    GtkWidget *text;
	    GtkAdjustment *adj;

	    text = lookup_widget (gems, "text1");
	    adj = GTK_TEXT (text)->vadj;
	    gtk_adjustment_set_value (adj, adj->value - adj->step_increment);
	}
	break;
    case GDK_Page_Up:
	{
	    GtkWidget *text;
	    GtkAdjustment *adj;

	    text = lookup_widget (gems, "text1");
	    adj = GTK_TEXT (text)->vadj;
	    gtk_adjustment_set_value (adj, adj->value - adj->page_increment);
	}
	break;
    default:
	return FALSE;
    }

    /*
     * the return TRUE; should stop the event, but it doesn't :/ 
     */
    gtk_signal_emit_stop_by_name (GTK_OBJECT (widget), "key_press_event");
    return TRUE;
}

void
on_toolbar_compose_clicked (GtkButton * UNUSED(button), gpointer UNUSED(user_data))
{
    GtkWidget *w;

    w = create_compose ();
    gtk_text_set_editable (GTK_TEXT (lookup_widget (w, "text2")), TRUE);
    gtk_widget_show (w);
}

void
on_toolbar_reply_clicked (GtkButton * UNUSED(button), gpointer UNUSED(user_data))
{
    synopsis *s;
    GtkCTreeNode *n;
    GtkWidget *from, *subj, *date, *recipt, *body, *comp, *widget;
    char *shtuff, buf[1024];

    if ((widget = lookup_widget (gems, "mailbox")) == NULL)
	return;
    comp = create_compose ();
    from = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (comp), "entry1");
    /* to = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (comp), "entry5"); */
    date = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (comp), "entry2");
    subj = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (comp), "entry6");
    recipt = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (comp), "entry4");
    body = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (comp), "text2");

    n = gtk_ctree_node_nth (GTK_CTREE (widget),
	(&(GTK_CTREE (widget)->clist))->focus_row);
    s = (synopsis *) gtk_ctree_node_get_row_data (GTK_CTREE (widget), n);
    shtuff = replyify (s, (char *)db_read_body (s->id));

    gtk_entry_set_text (GTK_ENTRY (from), s->sender);
    /*
     * if(!strncasecmp("re: ", s->subject, 4)) 
     */
    if (tolower (s->subject[0]) == 'r' && tolower (s->subject[1]) == 'e'
	&& s->subject[2] == ':' && s->subject[3] == ' ')
	sprintf (buf, "%s", s->subject);
    else
	sprintf (buf, "Re: %s", s->subject);
    gtk_entry_set_text (GTK_ENTRY (subj), buf);
    gtk_entry_set_text (GTK_ENTRY (date), s->date);


    gtk_text_freeze (GTK_TEXT (body));
    gtk_text_set_point (GTK_TEXT (body), 0);
    gtk_text_forward_delete (GTK_TEXT (body),
	gtk_text_get_length (GTK_TEXT (body)));
    gtk_text_insert (GTK_TEXT (body), NULL, NULL, NULL, shtuff, -1);
    gtk_text_thaw (GTK_TEXT (body));
    if (widget == NULL)
    {
	free (s);
	free (shtuff);
    }
    gtk_text_set_editable (GTK_TEXT (body), TRUE);
    gtk_widget_show (comp);
    return;
}

void
on_toolbar_forward_clicked (GtkButton * UNUSED(button), gpointer UNUSED(user_data)) {}

void
on_mailbox_click_column (GtkCList * clist, gint column, gpointer UNUSED(user_data))
{
    if ((sort & (~SORT_DIRECTION)) == column)
	sort ^= SORT_DIRECTION;
    else
	sort = column | (sort & SORT_DIRECTION);
    gtk_clist_set_sort_column (clist, column);
    gtk_clist_set_sort_type (clist,
	(sort & SORT_DIRECTION) ? GTK_SORT_ASCENDING : GTK_SORT_DESCENDING);
    gtk_clist_sort (clist);
}

void
on_create1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data))
{
    gtk_widget_show (create_create_mbox ());
}

void
on_open2_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data)) {}

void
on_delete1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data))
{
    GtkWidget *w;
    GtkCTree *ctree;
    GtkCTreeNode *n;
    mboxs *m;

    ctree = GTK_CTREE (lookup_widget (gems, "mailboxlist"));
    n = gtk_ctree_node_nth (ctree, (&(ctree->clist))->focus_row);
    m = (mboxs *) gtk_ctree_node_get_row_data (ctree, n);

    w = create_delete_mbox ();
    gtk_widget_show (w);

    gtk_object_set_user_data (GTK_OBJECT (w), m);
}


gboolean
on_mboxlist_event (GtkWidget * UNUSED(widget), GdkEvent * event, gpointer UNUSED(user_data))
{
    GtkMenu *m;

    if ((event) && (event->type == GDK_BUTTON_PRESS)
	&& (((GdkEventButton *) event)->button == 3))
    {
	m = GTK_MENU (create_menu1 ());
	gtk_widget_show (GTK_WIDGET (m));
	gtk_menu_popup (m, NULL, NULL, NULL, NULL, 0, 0);
    }
    return FALSE;
}

void
on_mailboxdeleteok_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    char *m;

    m = ((mboxs *)
	gtk_object_get_user_data(GTK_OBJECT
	    (lookup_widget (GTK_WIDGET (button), "delete_mbox"))))->name;
    db_dropmbox (m);
    gtk_widget_destroy (lookup_widget (GTK_WIDGET (button), "delete_mbox"));
    set_mboxlist ();
}

void
on_mailboxdeletecancel_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    gtk_widget_destroy (lookup_widget (GTK_WIDGET (button), "delete_mbox"));
}


void
on_mailboxcreateok_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    db_addmbox (gtk_entry_get_text
	(GTK_ENTRY (lookup_widget (GTK_WIDGET (button), "entry7"))));
    gtk_widget_destroy (lookup_widget (GTK_WIDGET (button), "create_mbox"));
    set_mboxlist ();
}


void
on_mailboxcreateapply_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    db_addmbox (gtk_entry_get_text
	(GTK_ENTRY (lookup_widget (GTK_WIDGET (button), "entry7"))));
    set_mboxlist ();
}


void
on_mailboxcreatecancel_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    GtkWidget *w;

    w = lookup_widget (GTK_WIDGET (button), "create_mbox");
    gtk_widget_destroy (w);
}

void
gnome_o_put_the_damn_rules_in_the_box (GtkWidget * w)
{
    int numrules, x;
    rule *r;
    GtkCList *clist;

    clist = GTK_CLIST (lookup_widget (w, "clist1"));
    gtk_clist_clear (clist);
    r = (rule *) db_fetch_rules (&numrules);
    for (x = 0; x < numrules; x++)
    {
	gtk_clist_insert (clist, x, &(r[x].name));
	gtk_clist_set_row_data (clist, x, &r[x]);
    }
    return;
}

int rule_row_current;

void
face_gnome_o_rule_setpiece (GtkWidget * w, gpointer * trash)
{
    rule *r;

    r = (rule *)
	gtk_clist_get_row_data (GTK_CLIST (lookup_widget (w, "clist1")),
	rule_row_current);
    free (r->piece);
    r->piece = g_strdup ((gchar *) trash);
}

void
on_toolbar_rule_clicked (GtkButton * UNUSED(button), gpointer UNUSED(user_data))
{
    GtkWidget *r;
    GList *gl = NULL;
    mboxs **mboxlist;
    int x;

    r = create_Rules ();
    gtk_widget_show (r);
    gtk_paned_set_position (GTK_PANED (lookup_widget (r, "hpaned2")), 150);
    gnome_o_put_the_damn_rules_in_the_box (r);
    mboxlist = (mboxs **) db_read_mboxlist ();
    x = 0;
    while (mboxlist[x] != NULL)
	gl = g_list_append (gl, mboxlist[x++]->name);
    gtk_combo_set_popdown_strings (GTK_COMBO (lookup_widget (r, "combo2")),
	gl);
    gtk_signal_connect (GTK_OBJECT
	(gtk_option_menu_get_menu
	    (GTK_OPTION_MENU
		(lookup_widget (r, "optionmenu2")))),
	"focus_out_event", face_gnome_o_rule_setpiece, NULL);
}

void
on_rule_list_select_row (GtkCList * clist,
    gint row, gint UNUSED(column), GdkEvent * UNUSED(event), gpointer UNUSED(user_data))
{
    rule *r;
    GtkCombo *c2;
    GtkOptionMenu *om;
    GtkMenu *menu;
    GtkWidget *mi;
    int x;

    rule_row_current = row;
    r = (rule *) gtk_clist_get_row_data (clist, row);
    gtk_entry_set_text (GTK_ENTRY
	(lookup_widget (GTK_WIDGET (clist), "entry8")), r->name);
    gtk_entry_set_text (GTK_ENTRY
	(lookup_widget (GTK_WIDGET (clist), "entry9")), r->regex);

    c2 = GTK_COMBO (lookup_widget (GTK_WIDGET (clist), "combo2"));
    gtk_entry_set_editable (GTK_ENTRY (c2->entry), FALSE);
    gtk_entry_set_text (GTK_ENTRY (c2->entry), r->mbox);

    om = GTK_OPTION_MENU (lookup_widget (GTK_WIDGET (clist), "optionmenu2"));
    gtk_option_menu_remove_menu (om);
    menu = GTK_MENU (gtk_menu_new ());

    if (!strcmp (r->piece, "Message"))
	x = 0;
    mi = gtk_menu_item_new_with_label ("Message");
    gtk_signal_connect (GTK_OBJECT (mi), "activate",
	GTK_SIGNAL_FUNC (face_gnome_o_rule_setpiece), (gpointer) "Message");
    gtk_menu_append (menu, mi);
    gtk_widget_show (mi);
    if (!strcmp (r->piece, "Header"))
	x = 1;
    mi = gtk_menu_item_new_with_label ("Header");
    gtk_signal_connect (GTK_OBJECT (mi), "activate",
	GTK_SIGNAL_FUNC (face_gnome_o_rule_setpiece), (gpointer) "Header");
    gtk_menu_append (menu, mi);
    gtk_widget_show (mi);
    if (!strcmp (r->piece, "Subject"))
	x = 2;
    mi = gtk_menu_item_new_with_label ("Subject");
    gtk_signal_connect (GTK_OBJECT (mi), "activate",
	GTK_SIGNAL_FUNC (face_gnome_o_rule_setpiece), (gpointer) "Subject");
    gtk_menu_append (menu, mi);
    gtk_widget_show (mi);
    if (!strcmp (r->piece, "From"))
	x = 3;
    mi = gtk_menu_item_new_with_label ("From");
    gtk_signal_connect (GTK_OBJECT (mi), "activate",
	GTK_SIGNAL_FUNC (face_gnome_o_rule_setpiece), (gpointer) "From");
    gtk_menu_append (menu, mi);
    gtk_widget_show (mi);
    if (!strcmp (r->piece, "Recipients"))
	x = 4;
    mi = gtk_menu_item_new_with_label ("Recipients");
    gtk_signal_connect (GTK_OBJECT (mi), "activate",
	GTK_SIGNAL_FUNC (face_gnome_o_rule_setpiece), (gpointer) "Recipients");
    gtk_menu_append (menu, mi);
    gtk_widget_show (mi);
    if (!strcmp (r->piece, "Sender"))
	x = 5;
    mi = gtk_menu_item_new_with_label ("Sender");
    gtk_signal_connect (GTK_OBJECT (mi), "activate",
	GTK_SIGNAL_FUNC (face_gnome_o_rule_setpiece), (gpointer) "Sender");
    gtk_menu_append (menu, mi);
    gtk_widget_show (mi);
    if (!strcmp (r->piece, "Body"))
	x = 6;
    mi = gtk_menu_item_new_with_label ("Body");
    gtk_signal_connect (GTK_OBJECT (mi), "activate",
	GTK_SIGNAL_FUNC (face_gnome_o_rule_setpiece), (gpointer) "Body");
    gtk_menu_append (menu, mi);
    gtk_widget_show (mi);

    gtk_option_menu_set_menu (om, GTK_WIDGET (menu));
    gtk_option_menu_set_history (om, x);
}


void
on_rule_up_clicked (GtkButton * UNUSED(button), gpointer UNUSED(user_data)) {}

void
on_rule_down_clicked (GtkButton * UNUSED(button), gpointer UNUSED(user_data)) {}

void
on_rule_ok_clicked (GtkButton * button, gpointer user_data)
{
    on_rule_apply_clicked (button, user_data);
    on_rule_cancel_clicked (button, user_data);
}

void
on_rule_apply_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    rule **rulelist;
    GtkCList *clist;
    int length, x;

    clist = GTK_CLIST (lookup_widget (GTK_WIDGET (button), "clist1"));
    length = clist->rows + 1;
    rulelist = (void *)malloc (sizeof (void *) * length);

    for (x = 0; x < length; x++)
	rulelist[x] = gtk_clist_get_row_data (clist, x);

    db_set_rules (rulelist);
    free (rulelist);

    gnome_o_put_the_damn_rules_in_the_box (GTK_WIDGET (button));
    return;
}

void
on_rule_cancel_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    gtk_widget_destroy (lookup_widget (GTK_WIDGET (button), "Rules"));
}

void
on_rule_name_changed (GtkEditable * editable, gpointer UNUSED(user_data))
{
    rule *r;

    r = (rule *)
	gtk_clist_get_row_data (GTK_CLIST
	(lookup_widget (GTK_WIDGET (editable), "clist1")), rule_row_current);
    free (r->name);
    r->name = g_strdup (gtk_editable_get_chars (editable, 0, -1));
    gtk_clist_set_text (GTK_CLIST
	(lookup_widget (GTK_WIDGET (editable), "clist1")),
	rule_row_current, 0, r->name);
}

void
on_rule_mbox_changed (GtkEditable * editable, gpointer UNUSED(user_data))
{
    rule *r;

    r = (rule *)
	gtk_clist_get_row_data (GTK_CLIST
	(lookup_widget (GTK_WIDGET (editable), "clist1")), rule_row_current);
    if (r == NULL)
	return;
    free (r->mbox);
    r->mbox =
	g_strdup (gtk_entry_get_text
	(GTK_ENTRY
	    (GTK_COMBO
		(lookup_widget (GTK_WIDGET (editable), "combo2"))->entry)));
}

void
on_rule_regex_changed (GtkEditable * editable, gpointer UNUSED(user_data))
{
    free (((rule *)
	    gtk_clist_get_row_data (GTK_CLIST
		(lookup_widget
		    (GTK_WIDGET (editable), "clist1")),
		rule_row_current))->regex);
    ((rule *)
	gtk_clist_get_row_data (GTK_CLIST
	    (lookup_widget
		(GTK_WIDGET (editable), "clist1")),
	    rule_row_current))->regex =
	g_strdup (gtk_editable_get_chars (editable, 0, -1));
}

void
on_rule_new_rule_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    rule *r;
    int x;
    GtkCList *clist;

    r = (rule *) malloc (sizeof (rule));
    r->regex = g_strdup ("");
    r->mbox = g_strdup ("Inbox");
    r->name = g_strdup ("New rule");
    r->piece = g_strdup ("Header");
    clist = GTK_CLIST (lookup_widget (GTK_WIDGET (button), "clist1"));
    x = clist->rows;
    gtk_clist_insert (clist, x, &(r->name));
    gtk_clist_set_row_data (clist, x, r);
    gtk_clist_select_row (clist, x, 0);
}

void
on_custom1_activate (GtkMenuItem * UNUSED(menuitem), gpointer UNUSED(user_data))
{
    gtk_widget_show (create_custom_mbox ());
}

void
on_mboxcustomok_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    db_addmbox_view (gtk_entry_get_text (GTK_ENTRY (lookup_widget (GTK_WIDGET
		    (button), "mbox_create_custom_name"))),
	gtk_entry_get_text (GTK_ENTRY (lookup_widget (GTK_WIDGET (button),
		    "mbox_create_custom_query"))));
    gtk_widget_destroy (lookup_widget (GTK_WIDGET (button), "custom_mbox"));
    set_mboxlist ();
}

void
on_mboxcustomapply_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    db_addmbox_view (gtk_entry_get_text (GTK_ENTRY (lookup_widget (GTK_WIDGET
		    (button), "mbox_create_custom_name"))),
	gtk_entry_get_text (GTK_ENTRY (lookup_widget (GTK_WIDGET (button),
		    "mbox_create_custom_query"))));
    set_mboxlist ();
}

void
on_mboxcustomcancel_clicked (GtkButton * button, gpointer UNUSED(user_data))
{
    gtk_widget_destroy (lookup_widget (GTK_WIDGET (button), "custom_mbox"));
}

gboolean
on_mboxlist_keyevent (GtkWidget * UNUSED(widget),
    GdkEventKey * event, gpointer UNUSED(user_data))
{
    switch (event->keyval)
    {

    case GDK_Return:
    case GDK_space:
	/*
	on_mailboxlist_tree_select_row (widget, NULL, 0, NULL);
	*/
	break;
    case GDK_N:
    case GDK_n:
    case GDK_Right:
	on_toolbar_next_clicked (NULL, NULL);
	break;
    case GDK_P:
    case GDK_p:
    case GDK_Left:
	on_toolbar_prev_clicked (NULL, NULL);
	break;
    default:
	break;
    }

    return FALSE;
}
