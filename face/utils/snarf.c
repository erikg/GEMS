
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2003 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: snarf.c,v 1.14 2004/02/16 13:43:11 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "message.h"
#include "db.h"

#define MEGS *1024*1024

/* 8 megs */
#define BIGBUFSIZ (8 MEGS)

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
    printf ("\n%s: %s\n", a, b);
    return;
}

int
parse (char *buf, unsigned int size)
{
    int i, linecount, linecountsize, msgcount, msgcountsize;
    char **line, *walk, **msg, *mbox;

    msgcount = linecount = 0;
    msgcountsize = linecountsize = 1024;
    line = malloc (sizeof (char *) * linecountsize);
    msg = malloc (sizeof (char *) * msgcountsize);

    if (!strncmp ("From ", buf, 5))
	line[linecount++] = buf;
    for (walk = buf; walk < (buf + size); walk++)
	if (walk[0] == '\n')
	{
	    if (linecount >= linecountsize)
		line = realloc (line, (linecountsize *= 2) * sizeof (char *));
	    line[linecount++] = walk + 1;
	}
    for (i = 0; i < linecount; ++i)
	if (!strncmp (line[i], "From ", 5))
	    if (i == 0 || line[i - 1][0] == '\n')
	    {
		if (i > 0)
		    line[i - 1][0] = 0;
		msg[msgcount] = line[i];
		msgcount++;
	    }

    for (i = 1; i <= msgcount; ++i)
    {
	message *m;
	int ins;

	m = message_build_from_buffer (msg[i-1]);
	if (m == NULL)
	    continue;
	mbox = rule_check (m); 
	ins = db_insert_msg (mbox, m);	/* this sucks up time */
	message_destroy (m);
	printf ("\r%d/%d  (%.2f%%)%s",  i, msgcount,
	    100.0 * (float)i / (float)msgcount,ins==GEMS_FALSE?"  FAILED\n":"");
	fflush (stdout);
    }
    printf ("\n");
    return 0;
}

int
face_run (int argc, char **argv)
{
    int fd;
    unsigned int size;
    char *buf;

    if (rule_init () == GEMS_FALSE)
    {
	printf (_("Failed to initialize ruleset\n"));
	exit (EXIT_FAILURE);
    }
    buf = (char *)malloc (BIGBUFSIZ + 1);

    while (++argv, --argc)
    {
	fd = open (argv[1], O_RDONLY);

	if (fd <= 0)
	{
	    free (buf);
	    return (-1);
	}

	size = read (fd, buf, BIGBUFSIZ);
	buf[size] = 0;
	parse (buf, size);
	close (fd);
    }

    if (rule_close () == GEMS_FALSE)
    {
	printf (_("Failed closing ruleset\n"));
    }
    free (buf);
    return GEMS_TRUE;
}
