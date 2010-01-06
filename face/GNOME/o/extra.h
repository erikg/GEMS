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
 * $Id: extra.h,v 1.14 2010/01/06 00:47:30 erik Exp $
 */

#ifndef __EXTRAS_H
#define __EXTRAS_H

#include <message.h>

extern int default_mboxlistbehavior;
extern unsigned char sort;
extern GdkColor *color_magenta, *color_black;

typedef struct _mboxview
{
    mboxs *mailbox;
    int status;
}
mboxview;

mboxview *new_mboxview (mboxs * mb, int status);
int putmail (GtkWidget * widget);
char *replyify (synopsis * syn, char *buf);
gint update_mboxlist (gpointer nothing);
void set_mboxlist ();
int get_mboxlistbehavior(void);
void set_mboxlistbehavior(int);

#endif
