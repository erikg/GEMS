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
