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
 * $Id: regex.c,v 1.5 2003/04/05 18:36:27 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include "defs.h"

int
regex (char *r, char *s)
{
    void *preg;
    int val;

    preg = (void *) malloc (1000 * sizeof (void *));

    regcomp (preg, r, 0);

    if (regexec (preg, s, 0, NULL, 0) == 0)
	val = GEMS_TRUE;
    else
	val = GEMS_FALSE;

    regfree (preg);
    return val;
}
