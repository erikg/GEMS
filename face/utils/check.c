
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2004-2010 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: check.c,v 1.7 2010/01/06 00:47:30 erik Exp $
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
    printf("Huh, %d %s\n", argc, *argv);

/*
    if (close_spool () != GEMS_TRUE)
	printf (_("Couldn't close the spool\n"));
*/

    printf ("\n");

    return GEMS_TRUE;
}
