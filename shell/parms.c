
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
 * $Id: parms.c,v 1.13 2010/01/06 00:47:32 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "defs.h"
#include "ll.h"
#include "parms.h"

static void
ver ()
{
    printf
	("%s version %s (C) Copyright 2000-2010 Erik Greenwald <erik@smluc.org>\n",
	PACKAGE, VERSION);
    printf
	("%s comes with ABSOLUTELY NO WARRANTY; please refer to COPYING or the\n\tGNU GENERAL PUBLIC LICENSE version 2 (June 1991) for details\n",
	PACKAGE);
    return;
}

void
help_exit (char *name)
{
    ver ();
    printf ("%s [OPTIONS] [FACE]\n", name);
    exit (0);
}

void
ver_exit ()
{
    ver ();
    exit (0);
}

parms *
load_parms (int *argc, char **margv)
{
    parms *p;
    int x = 0;
    void *ll;

    ll = ll_newlist ();

    p = (parms *) malloc (sizeof (parms));

    p->libdir = NULL;
    p->dbiname = NULL;
    p->dbihost = NULL;
    p->dbiuser = NULL;
    p->dbipasswd = NULL;
    p->dbidb = NULL;
    p->facename = NULL;
    p->rc = NULL;

    /*
     * read the parms into a linked list 
     */
    while (x < *argc)
	ll_addnode (ll, margv[x++]);

    ll_rewind (ll);

    for (x = 1; x < *argc; x++)
	free (margv[x]);

    x = *argc;

    /*
     * use the linked list 
     */
    while (ll_next (ll) == GEMS_TRUE)
    {
	char *a;

	a = ll_showline (ll);
	if (!strcmp ("--", a))
	{
	    x--;
	    ll_deletenode (ll);
	    ll_next (ll);
	} else if (!strcmp ("-h", a) || !strcmp ("--help", a))
	{
	    ll_clearlist (ll);
	    help_exit (margv[0]);
	} else if (!strcmp ("-v", a) || !strcmp ("--version", a))
	{
	    ll_clearlist (ll);
	    ver_exit ();
	} else if (!strcmp ("-u", a) || !strcmp ("--dbuser", a))
	{
	    ll_deletenode (ll);
	    if (ll_end (ll) == GEMS_TRUE)
		help_exit (margv[0]);
	    p->dbiuser = strdup (ll_showline (ll));
	    ll_deletenode (ll);
	} else if (!strcmp ("-d", a) || !strcmp ("--dbms", a))
	{
	    ll_deletenode (ll);
	    if (ll_end (ll) == GEMS_TRUE)
		help_exit (margv[0]);
	    p->dbiname = strdup (ll_showline (ll));
	    ll_deletenode (ll);
	} else
	{
	    p->facename = strdup (a);
	    ll_deletenode (ll);
	}
    }

    free (margv[0]);

    ll_rewind (ll);

    /*
     * move the linked list to the array 
     */
    for (*argc = 0; *argc < x;)
    {
	char *a;

	a = ll_showline (ll);
	margv[*argc] = strdup (a);
	*argc = (*argc) + 1;
	ll_next (ll);
    }

    ll_clearlist (ll);
    return p;
}

void
parms_destroy (parms * p)
{
    if (p == NULL)
	return;
    if (p->libdir)
	free (p->libdir);
    if (p->dbiname)
	free (p->dbiname);
    if (p->dbihost)
	free (p->dbihost);
    if (p->dbiuser)
	free (p->dbiuser);
    if (p->dbipasswd)
	free (p->dbipasswd);
    if (p->dbidb)
	free (p->dbidb);
    if (p->facename)
	free (p->facename);
    if (p->rc)
	free (p->rc);

    free (p);
    return;
}
