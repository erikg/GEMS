#include <gnome.h>

#include "defs.h"
#include "message.h"
#include "extra.h"

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

  n =
    gtk_ctree_node_nth (GTK_CTREE (widget),
			(&(GTK_CTREE (widget)->clist))->focus_row);
  s = (synopsis *) gtk_ctree_node_get_row_data (GTK_CTREE (widget), n);

  from = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (gems), "entry1");
  date = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (gems), "entry2");
  subj = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (gems), "entry3");
  recipt = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (gems), "entry4");
  body = (GtkWidget *) gtk_object_get_data (GTK_OBJECT (gems), "text1");

  gtk_entry_set_text (GTK_ENTRY (from), s->sender);
  gtk_entry_set_text (GTK_ENTRY (subj), s->subject);
  gtk_entry_set_text (GTK_ENTRY (date), s->date);
/*              gtk_entry_set_text(GTK_ENTRY(recipt),s->);*/ /*TODO*/
    shtuff = (char *) db_read_body (s->id);
  gtk_text_freeze (GTK_TEXT (body));
  gtk_text_set_point (GTK_TEXT (body), 0);
  gtk_text_forward_delete (GTK_TEXT (body),
			   gtk_text_get_length (GTK_TEXT (body)));
  gtk_text_insert (GTK_TEXT (body), NULL, NULL, NULL, shtuff, -1);
  gtk_text_thaw (GTK_TEXT (body));

  return TRUE;
}
