
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
 * $Id: cleantables.c,v 1.8 2009/08/31 13:45:31 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "db.h"

extern int do_db_flush (char *);

int
face_uses_X ()
{
    return GEMS_FALSE;
}

void
oops (char *a, char *b)
{
    printf ("%s\n%s\n", a, b);
}

int
face_run (char *trash)
{
    /*
     * assume the db is already set up 
     */

    printf("trash: %s\n", trash);

    db_flush ("attachments");
    putchar ('.');
    db_flush ("body");
    putchar ('.');
    db_flush ("header");
    putchar ('.');

    /*
     * db_flush ("mmbox"); putchar ('.'); db_flush ("preferences"); putchar
     * ('.');
     */
    db_flush ("recipt");
    putchar ('.');
    db_flush ("replyto");
    putchar ('.');
    db_flush ("synopsis");
    putchar ('.');
    db_flush ("refs");
    putchar ('.');

    /*
     * db_addmbox ("inbox"); putchar ('.'); db_addmbox ("sent"); putchar
     * ('.'); db_addmbox ("trash"); putchar ('.'); db_addmbox ("drafts");
     * putchar ('.');
     */
    printf ("\n");

    return 0;
}
