#ifndef __EXTRAS_H
#define __EXTRAS_H

extern int default_mboxlistbehavior;
extern unsigned char sort;
extern GdkColor *color_magenta, *color_black;

typedef struct _mboxview {
    mboxs *mailbox;
    int status;
} mboxview;

mboxview *new_mboxview (mboxs * mb, int status);

int putmail (GtkWidget * widget);

#endif
