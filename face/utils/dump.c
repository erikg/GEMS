
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2004-2007 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: dump.c,v 1.4 2007/02/12 21:15:03 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "defs.h"
#include "spoolread.h"
#include "ll.h"
#include "message.h"
#include "db.h"
#include "receptor.h"

#ifndef _
#define _(X) (X)
#endif

int
face_uses_X ()
{
    return GEMS_FALSE;
}

void
oops (char *a, char *b)
{
    printf ("%s: %s\n", a, b);
}

int
face_run (int argc, char **argv)
{
    message *mess;
    mboxs **mb;
    int i = 0, j = 0;

    printf("%d %s\n", argc, *argv);
    mb =  db_read_mboxlist();

    for( j = 0; mb[j]; ++j)
    {
	synopsis **s = db_read_synopsis (mb[j]->id, DB_ALL);
	for(i=0; s[i] ; ++i)
	{
	    mess = db_read_message(s[i]->id);
	    printf("%s\n\n%s\n\n", mess->header, mess->body);
	}
    }

/*
    if (close_spool () != GEMS_TRUE)
	printf (_("Couldn't close the spool\n"));
*/

    printf ("\n");

    return GEMS_TRUE;
}
