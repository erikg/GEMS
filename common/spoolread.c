
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2007 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: spoolread.c,v 1.11 2007/02/12 21:15:03 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "ll.h"
#include "spoolread.h"
#include "face.h"		/* for oops() */

static char *out, *line;
static FILE *spool;

static int
fake_fungets (FILE * fp, char *string)
{
    fseek (fp, -strlen (string), SEEK_CUR);
    return GEMS_TRUE;
}

FILE *
spool_file ()
{
    return spool;
}

int
spool_fd ()
{
    return fileno (spool);
}

int
open_spool (char *spoolname)
{
    if (spoolname == NULL)
	if ((spoolname = getenv ("MAIL")) == NULL)
	{
	    oops ("Spoolread", "Couldn't get mail spool name");
	    return (EXIT_FAILURE);
	}
    printf ("Opening %s\n", spoolname);

    if ((spool = fopen (spoolname, "r")) == NULL)
    {
	oops ("Spoolread\nUnable to open mail spool", spoolname);
	return (EXIT_FAILURE);
    }
    line = (char *)malloc (65536);
    if (line == NULL)
    {
	oops ("Spoolread", "Failed malloc");
	if (fclose (spool) != 0)
	    exit (EXIT_FAILURE);
	return GEMS_FALSE;
    }
    out = (char *)malloc (65535);
    if (out == NULL)
    {
	oops ("Spoolread", "failed malloc");
	exit (EXIT_FAILURE);
    }
    return GEMS_TRUE;
}

void *
read_message ()
{
    void *list;
    int inmessage = 0;

    list = ll_newlist ();
    if (list == NULL)
	return NULL;
    out[0] = (char)0;

    while (fgets (line, 1024, spool) != 0)
    {
	if (!strncmp (line, "From ", 5))
	{			/* could this be better? */
	    if (inmessage == 1)
	    {
		fake_fungets (spool, line);
		if (ll_rewind (list) == GEMS_FALSE)
		    oops ("Spoolread", "Failed rewind");
		return list;
	    } else
	    {
		inmessage = 1;
	    }
	} else if (inmessage == 1)
	    if (ll_addnode (list, line) == GEMS_FALSE)
		oops ("Spoolread", "Failed addnode");
    }

    if (ll_rewind (list) == GEMS_FALSE)
	oops ("Spoolread", "Failed rewind");

    if (ll_empty (list) == GEMS_TRUE)
    {
	ll_clearlist (list);
	return NULL;
    }
    return list;
}

void *
read_message_quickly ()
{
    fprintf(stderr, "Unimplemented function: %s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    return NULL;
}

int
close_spool ()
{
    free (line);
    free (out);
    if (fclose (spool) != 0)
	oops ("Spoolread", "Failed to close spool");
    return GEMS_TRUE;
}
