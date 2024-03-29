
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
 * $Id: spool2sqlfast.c,v 1.11 2010/01/06 00:47:31 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"
#include "spoolread.h"
#include "message.h"
#include "db.h"

#ifndef _
#define _(X) (X)
#endif

#undef BUFSIZ
#define BUFSIZ (1024*1024)

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
    char *spoolname, *mbox, *buf;
    int numrules, fd, s;
    rule *rules;

    printf("%d %s\n", argc, *argv);

    spoolname = argv[1];
    buf = (char *)malloc (BUFSIZ);

    rules = (rule *) db_fetch_rules ((int *)&numrules);
    if (rule_init (rules, numrules) == GEMS_FALSE)
    {
	printf (_("Failed to initialize ruleset\n"));
	exit (EXIT_FAILURE);
    }
    if (open_spool (spoolname) != GEMS_TRUE)
    {
	printf (_("Failed to open spool %s\n"), spoolname);
	exit (EXIT_FAILURE);
    }
    fd = spool_fd ();
    s = BUFSIZ;
    memset (buf, 0, BUFSIZ);
    while (read (fd, buf, BUFSIZ) != 0)
    {
	mess = message_build_from_buffer (buf);
	if (mess == 0)
	{
	    printf ("Bad mssage\n");
	    return -1;
	}
	if (mess->body == NULL)
	    printf (_("\nNull body!\n"));
	mbox = rule_check (mess);
	if (db_insert_msg (mbox, mess) == GEMS_FALSE)
	    printf ("db_insert_msg failed in spool2sqlfast\n");
	if (message_destroy (mess) == GEMS_FALSE)
	    printf (_("Couldn't flush message out of memory!\n"));
	printf (".");
	fflush (stdout);
    }
    if (rule_close () == GEMS_FALSE)
    {
	printf (_("Failed closing ruleset\n"));
    }
    if (close_spool () != GEMS_TRUE)
	printf (_("Couldn't close the spool\n"));
    free (buf);
    printf ("\n");
    return GEMS_TRUE;
}
