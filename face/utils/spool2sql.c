
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
 * $Id: spool2sql.c,v 1.15 2009/08/31 13:45:31 erik Exp $
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
face_run (int argc, char **argv)
{
    void *list;
    message *mess;
    char *spoolname, *mbox;
    rule *rules;
    int numrules;

    /*
     * if(argc!=2){printf("this face requires the name of a spool\n%s
     * spool2sql -- <spool>\n\n",argv[0]);}
     */
    spoolname = argv[1];

    rules = (rule *) db_fetch_rules ((int *)&numrules);
    if (rule_init (rules, numrules) == GEMS_FALSE)
    {
	printf (_("Failed to initialize ruleset\n"));
	exit (EXIT_FAILURE);
    }
    /*
     * initialize the spoolread system 
     */
    if (open_spool (spoolname) != GEMS_TRUE)
    {
	printf (_("Failed to open spool %s\n"), spoolname);
	exit (EXIT_FAILURE);
    }
    while ((list = read_message ()) != NULL)
    {
	if (ll_rewind (list) == GEMS_FALSE)
	    printf (_("Failed rewind\n"));
	mess = message_build_from_list (list);

	if (mess->body == NULL)
	    printf (_("\nNull body!\n"));

	mbox = rule_check (mess);
	db_insert_msg (mbox, mess);
	if (ll_clearlist (list) == GEMS_FALSE)
	    printf (_("Couldn't flush list out of memory!\n"));
	if (message_destroy (mess) == GEMS_FALSE)
	    printf (_("Couldn't flush message out of memory!\n"));
	printf (".");
	fflush (0);
    }

    if (rule_close () == GEMS_FALSE)
    {
	printf (_("Failed closing ruleset\n"));
    }
    /*
     * close out the spool 
     */
    if (close_spool () != GEMS_TRUE)
	printf (_("Couldn't close the spool\n"));

/*
//    printf ("Normalizing\n");
//    if (db_normalize () == GEMS_FALSE)
//	printf (_("Failed to normalize the db"));
*/
    printf ("\n");

    return GEMS_TRUE;
}
