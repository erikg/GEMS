/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2003 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: callbacks.h,v 1.3 2003/04/05 18:36:27 erik Exp $
 */

#include <gnome.h>


void
 on_new_file1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_open1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_save1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_save_as1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_exit1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_cut1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_copy1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_paste1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_clear1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_properties1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_preferences1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_about1_activate (GtkMenuItem * menuitem, gpointer user_data);

void
 on_tree1_select_child (GtkTree * tree,
			GtkWidget * widget, gpointer user_data);

void
 show_propertbox (GtkMenuItem * menuitem, gpointer user_data);

void
 show_about (GtkMenuItem * menuitem, gpointer user_data);

void
 on_ctree1_click_column (GtkCList * clist, gint column, gpointer user_data);

void
 on_trash_clicked (GtkButton * button, gpointer user_data);

void
 on_check_clicked (GtkButton * button, gpointer user_data);

void
 on_compose_clicked (GtkButton * button, gpointer user_data);

void
 on_reply_clicked (GtkButton * button, gpointer user_data);

void
 on_forward_clicked (GtkButton * button, gpointer user_data);

void
 on_prev_clicked (GtkButton * button, gpointer user_data);

void
 on_next_clicked (GtkButton * button, gpointer user_data);

void
 on_attach_clicked (GtkButton * button, gpointer user_data);

void
 on_addr_clicked (GtkButton * button, gpointer user_data);

void
 on_print_clicked (GtkButton * button, gpointer user_data);

void
 on_help_clicked (GtkButton * button, gpointer user_data);

gboolean
on_clist_event (GtkWidget * widget, GdkEvent * event, gpointer user_data);
