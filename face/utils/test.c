
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2009 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: test.c,v 1.9 2009/08/31 13:45:32 erik Exp $
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
    rule *rules;
    int numrules;

    printf("%d %s\n", argc, *argv);

    /*
     * if(argc!=2){printf("this face requires the name of a spool\n%s
     * spool2sql -- <spool>\n\n",argv[0]);}
     */

    rules = (rule *) db_fetch_rules ((int *)&numrules);
    if (rule_init (rules, numrules) == GEMS_FALSE)
    {
	printf (_("Failed to initialize ruleset\n"));
	exit (EXIT_FAILURE);
    }
    /*
     * do shit. 
     */
    receive_pop3 ("freya", 110, "test", "tester");

    if (rule_close () == GEMS_FALSE)
    {
	printf (_("Failed closing ruleset\n"));
    }
    /*
     * close out the spool 
     */
    if (close_spool () != GEMS_TRUE)
	printf (_("Couldn't close the spool\n"));

    printf ("Normalizing\n");
    if (db_normalize () == GEMS_FALSE)
	printf (_("Failed to normalize the db"));

    printf ("\n");

    return GEMS_TRUE;
}
