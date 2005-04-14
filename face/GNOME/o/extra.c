/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2005 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: extra.c,v 1.14 2005/04/14 02:55:40 erik Exp $
 */

#include <gnome.h>

#include "db.h"
#include "defs.h"
#include "message.h"
#include "extra.h"
#include "ll.h"

extern GtkWidget *gems;

unsigned char sort = 0;

GdkColor *color_magenta, *color_black;

mboxview *
new_mboxview (mboxs * mb, int status)
{
    mboxview *mv;

    mv = (mboxview *) malloc (sizeof (mboxview));
    mv->mailbox = mb;
    mv->status = status;
    return mv;
}

int
putmail (GtkWidget * widget)
{
    synopsis *s;
    GtkCTreeNode *n;
    GtkWidget *from, *subj, *date, *recipt, *body;
    char *shtuff;

    if (widget != NULL)
      {
	  n = gtk_ctree_node_nth (GTK_CTREE (widget),
				  (&(GTK_CTREE (widget)->clist))->focus_row);
	  s = (synopsis *) gtk_ctree_node_get_row_data (GTK_CTREE (widget),
							n);
	  if (s)
	      shtuff = (char *) db_read_body (s->id);
	  else
	    {
		printf ("synopsis for row %d is NULL!\n", n);
		return FALSE;
	    }
      }
    else
      {
	  s = (synopsis *) malloc (sizeof (synopsis));
	  s->sender = strdup (" ");
	  s->subject = strdup (" ");
	  s->date = strdup (" ");
	  s->sender = strdup (" ");
	  shtuff = strdup (" ");
      }
    from = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (gems), "entry1");
    date = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (gems), "entry2");
    subj = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (gems), "entry3");
    recipt = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (gems), "entry4");
    body = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (gems), "text1");

    gtk_entry_set_text (GTK_ENTRY (from), s->sender);
    gtk_entry_set_text (GTK_ENTRY (subj), s->subject);
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
    return TRUE;
}

char *
replyify (synopsis * syn, char *buf)
{
    char *newbuf;
    char tbuf[1024];
    void *list;
    int s = 0, x = 0, len;

    len = strlen (buf);
    list = ll_newlist ();
    snprintf (tbuf, strlen (syn->sender) + 8, "%s said:\n", syn->sender);
    ll_addnode (list, tbuf);
    while (x < len)
      {
	  if (buf[x] == '\n')
	    {
		snprintf (tbuf, x - s + 4, "> %s\n", buf + s);
		ll_addnode (list, tbuf);
		memset (tbuf, 0, 1024);
		s = x + 1;
	    }
	  x++;
      }

    snprintf (tbuf, strlen (getenv ("HOME")) + strlen ("/.signature") + 1,
	      "%s/.signature", getenv ("HOME"));
    printf ("tbuf: %s\n", tbuf);
    list = ll_append (list, read_file_to_list (tbuf));
    free (buf);
    newbuf = stringinate (list);
    ll_clearlist (list);
    return newbuf;
}

gint
update_mboxlist (gpointer nothing)
{
    mboxs **mboxlist;
    GtkCTree *tree;
    int x = 0;

    mboxlist = (mboxs **) db_read_mboxlist ();
    tree = GTK_CTREE (lookup_widget (gems, "mailboxlist"));
    gtk_clist_freeze (&GTK_CTREE (tree)->clist);
    x = 0;
    while (mboxlist[x] != NULL)
      {
	  gtk_clist_set_foreground (&(tree->clist), x,
				    (mboxlist[x]->hasunread >
				     0) ? color_magenta : color_black);
	  x++;
      }
    gtk_clist_thaw (&GTK_CTREE (tree)->clist);
    return 1;
}

static int default_mboxlistbehavior = DB_UNREAD;

void
set_mboxlist ()
{
    int x;
    mboxs **mboxlist;
    GtkCTree *tree;
    char *read, *unread, *marked, *all;

    mboxlist = (mboxs **) db_read_mboxlist ();
    tree = GTK_CTREE (lookup_widget (gems, "mailboxlist"));
    all = strdup ("all");
    read = strdup ("read");
    unread = strdup ("unread");
    marked = strdup ("marked");

    gtk_clist_freeze (&GTK_CTREE (tree)->clist);
    gtk_clist_clear (&GTK_CTREE (tree)->clist);

    x = 0;
    while (mboxlist[x] != NULL)
      {
	  GtkCTreeNode *node, *n;
	  char *text;

	  text = mboxlist[x]->name;
	  node =
	      gtk_ctree_insert_node (tree, NULL, NULL, &text, 5, NULL,
				     NULL, NULL, NULL, FALSE, FALSE);
	  gtk_ctree_node_set_row_data (tree, node,
				       new_mboxview (mboxlist[x],
						     default_mboxlistbehavior));
	  n = gtk_ctree_insert_node (tree, node, NULL, &all, 5, NULL, NULL,
				     NULL, NULL, TRUE, TRUE);
	  gtk_ctree_node_set_row_data (tree, n,
				       new_mboxview (mboxlist[x], DB_ALL));
	  n = gtk_ctree_insert_node (tree, node, NULL, &unread, 5, NULL, NULL,
				     NULL, NULL, TRUE, TRUE);
	  gtk_ctree_node_set_row_data (tree, n,
				       new_mboxview (mboxlist[x], DB_UNREAD));
	  n = gtk_ctree_insert_node (tree, node, NULL, &read, 5, NULL, NULL,
				     NULL, NULL, TRUE, TRUE);
	  gtk_ctree_node_set_row_data (tree, n,
				       new_mboxview (mboxlist[x], DB_READ));
	  n = gtk_ctree_insert_node (tree, node, NULL, &marked, 5, NULL, NULL,
				     NULL, NULL, TRUE, TRUE);
	  gtk_ctree_node_set_row_data (tree, n,
				       new_mboxview (mboxlist[x], DB_MARKED));

	  x++;
      }

    /*
     * gtk_ctree_select(GTK_CTREE (tree), select_node);
     */
    gtk_clist_thaw (&GTK_CTREE (tree)->clist);
    free (mboxlist);
    update_mboxlist (NULL);
    return;
}

void
set_mboxlistbehavior(int x)
{
    default_mboxlistbehavior = x;
    return;
}

int
get_mboxlistbehavior()
{
    return default_mboxlistbehavior;
}
