
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
 * $Id: sql2spool.c,v 1.7 2005/01/13 14:29:53 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "defs.h"
#include "spoolread.h"
#include "ll.h"
#include "message.h"
#include "db.h"

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
face_run (int argc, char **margv)
{
    FILE *fp;
    char *spoolname;
    mboxs **boxes;
    synopsis **msgs;
    message *m;
    int status = DB_ALL;
    int i = 0, j = 0;

    /*
     * if(argc==1)
     */
    fp = stdout;

    /*
     * else { spoolname = argv[1];
     * 
     * if ((fp = fopen (spoolname, "w")) == NULL) { printf (_("Failed to open %s
     * for writing\n"), spoolname); exit (EXIT_FAILURE); } }
     */

    boxes = db_read_mboxlist ();
    while (boxes[i] != NULL)
    {
	fprintf (stderr, "box: %s\n", boxes[i]->name);
	msgs = db_read_synopsis (boxes[i]->id, DB_ALL);
	j = 0;
	while (msgs[j] != NULL)
	{
	    m = db_read_message (msgs[j]->id);

	    fprintf (fp, "%s%s\n", m->header, m->body);
	    message_destroy (m);
	    ++j;
	}
	++i;
    }

    /*
     * close out the spool 
     */
    if (fp != stdout)
	if (fclose (fp) != 0)
	    printf (_("Couldn't close the spool\n"));

    printf ("\n");
    return 0;
}
