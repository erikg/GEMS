#include <gnome.h>
#include "toolbar.hh"
#include "statusbar.hh"
#include "menu.hh"
#include "mboxlist.hh"
#include "mboxtree.hh"

class ui
{
	public:
		ui();
		ui(char **mbox);
		~ui();
		void run();
	private:
		GtkWidget *main, *hpane, *p1, *p2;
		toolbar *tb;
		statusbar *sb;
		menu *mn;
		mboxlist *mbl;
		mboxtree *mbt;
};

