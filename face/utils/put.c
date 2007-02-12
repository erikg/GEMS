
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2006-2007 Erik Greenwald <erik@smluc.org>               *
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
 * $Header: /mnt/fenris/usr/cvs/devel/gems/face/utils/put.c,v 1.2 2007/02/12 19:26:33 erik Exp $
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
#define BIGBUFSIZ (32 MEGS)

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
add (char *buf, unsigned int size)
{
    char *mbox;
    message *m;

    m = message_build_from_buffer (buf);
    if (m == NULL)
	return -1;
    mbox = rule_check (m);
    db_insert_msg (mbox, m);	/* this sucks up time */
    message_destroy (m);

    return 0;
}

int
face_run (int argc, char **argv)
{
    int fd, numrules;
    unsigned int size;
    char *buf;
    rule *rules;

    rules = (rule *) db_fetch_rules ((int *)&numrules);
    if (rule_init (rules, numrules) == GEMS_FALSE)
    {
	printf (_("Failed to initialize ruleset\n"));
	exit (EXIT_FAILURE);
    }
    buf = (char *)malloc (BIGBUFSIZ + 1);

    while (++argv, --argc)
    {
	size = read (STDIN_FILENO, buf, BIGBUFSIZ);
	buf[size] = 0;
	add (buf, size);
    }

    if (rule_close () == GEMS_FALSE)
    {
	printf (_("Failed closing ruleset\n"));
    }
    free (buf);
    return GEMS_TRUE;
}
