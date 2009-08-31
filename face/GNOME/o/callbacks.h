/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2009 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: callbacks.h,v 1.13 2009/08/31 13:45:30 erik Exp $
 */

#include <gnome.h>


void on_new_file1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_open1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_save1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_save_as1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_exit1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_cut1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_copy1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_paste1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_clear1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_properties1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_preferences1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_about1_activate (GtkMenuItem * menuitem, gpointer user_data);

gboolean
on_mailbox_event (GtkWidget * widget, GdkEvent * event, gpointer user_data);

gboolean
on_gems_quit (GtkWidget * widget, GdkEvent * event, gpointer user_data);


void
on_mailboxlist_tree_select_row (GtkCTree * ctree,
			   GList * node, gint column, gpointer user_data);

void
on_mailboxlist_tree_select_row (GtkCTree * ctree,
			   GList * node, gint column, gpointer user_data);

void on_toolbar_prev_clicked (GtkButton * button, gpointer user_data);

void on_toolbar_next_clicked (GtkButton * button, gpointer user_data);

gboolean
on_mailbox_key_press_event (GtkWidget * widget,
			   GdkEventKey * event, gpointer user_data);

void on_toolbar_compose_clicked (GtkButton * button, gpointer user_data);

void on_toolbar_reply_clicked (GtkButton * button, gpointer user_data);

void on_toolbar_forward_clicked (GtkButton * button, gpointer user_data);

void
on_mailbox_click_column (GtkCList * clist, gint column, gpointer user_data);

void on_create1_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_open2_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_delete1_activate (GtkMenuItem * menuitem, gpointer user_data);

gboolean
on_mboxlist_event (GtkWidget * widget, GdkEvent * event, gpointer user_data);

gint on_delete_mbox_close (GnomeDialog * gnomedialog, gpointer user_data);

void on_mailboxdeleteok_clicked (GtkButton * button, gpointer user_data);

void on_mailboxdeletecancel_clicked (GtkButton * button, gpointer user_data);

gint on_create_mbox_close (GnomeDialog * gnomedialog, gpointer user_data);

void on_mailboxcreateok_clicked (GtkButton * button, gpointer user_data);

void on_mailboxcreateapply_clicked (GtkButton * button, gpointer user_data);

void on_mailboxcreatecancel_clicked (GtkButton * button, gpointer user_data);

void on_toolbar_rule_clicked (GtkButton * button, gpointer user_data);

void
on_rule_list_select_row (GtkCList * clist,
			 gint row,
			 gint column, GdkEvent * event, gpointer user_data);

void on_rule_up_clicked (GtkButton * button, gpointer user_data);

void on_rule_down_clicked (GtkButton * button, gpointer user_data);

void on_rule_ok_clicked (GtkButton * button, gpointer user_data);

void on_rule_apply_clicked (GtkButton * button, gpointer user_data);

void on_rule_cancel_clicked (GtkButton * button, gpointer user_data);

void on_rule_name_changed (GtkEditable * editable, gpointer user_data);

void on_rule_mbox_changed (GtkEditable * editable, gpointer user_data);

void on_rule_regex_changed (GtkEditable * editable, gpointer user_data);

void on_rule_new_rule_clicked (GtkButton * button, gpointer user_data);

void
on_custom1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mboxcustomok_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_mboxcustomapply_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_mboxcustomcancel_clicked            (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_mboxlist_keyevent                   (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);
