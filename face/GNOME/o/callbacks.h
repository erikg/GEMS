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
on_ctree1_event (GtkWidget * widget, GdkEvent * event, gpointer user_data);

gboolean
on_gems_quit (GtkWidget * widget, GdkEvent * event, gpointer user_data);


void
on_ctree2_tree_select_row (GtkCTree * ctree,
			   GList * node, gint column, gpointer user_data);

void
on_ctree2_tree_select_row (GtkCTree * ctree,
			   GList * node, gint column, gpointer user_data);

void on_toolbar_prev_clicked (GtkButton * button, gpointer user_data);

void on_toolbar_next_clicked (GtkButton * button, gpointer user_data);

gboolean
on_ctree1_key_press_event (GtkWidget * widget,
			   GdkEventKey * event, gpointer user_data);

void on_toolbar_compose_clicked (GtkButton * button, gpointer user_data);

void on_toolbar_reply_clicked (GtkButton * button, gpointer user_data);

void on_toolbar_forward_clicked (GtkButton * button, gpointer user_data);

void
on_ctree1_click_column (GtkCList * clist, gint column, gpointer user_data);

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
