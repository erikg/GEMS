
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
 * $Id: shell.c,v 1.9 2007/02/12 19:26:33 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dlfcn.h>

#include "defs.h"
#include "message.h"

#include "prefs.h"
#include "parms.h"

#define FACEDEC 40

prefs *p;
parms *parm;

/*
 * this gets redefined when the face is loaded (I hope) 
 */
void
oops (char *a, char *b)
{
    printf ("%s: %s\n", a, b);
}

int
main (int argc, char **argv)
{
    void *dbi;
    void *face;
    void *common;
    void *receptor;

    char *dbifullname;
    char *facefullname;
    char *commonname;
    char *receptorname;
    char *transmittorname;
    char **margv;		/* mutable argv */

    void (*_db_init) (char *, char *, char *, char *);
    void (*_db_close) ();
    int (*_face_uses_X) ();
    void (*_face_run) (int, char **);

    int x;

    margv = malloc (sizeof (void *) * argc);
    for (x = 0; x < argc; x++)
    {
	margv[x] = (char *)malloc (strlen (argv[x]) + 1);
	strcpy (margv[x], argv[x]);
    }

    dbi = NULL;
    face = NULL;

    parm = load_parms (&argc, margv);
    p = load_prefs (parm);

    commonname =
	(char *)malloc (strlen (p->libdir) +
	strlen ("/gems/libgemscommon.so."));

    dbifullname =
	(char *)malloc (strlen (p->libdir) + strlen (p->dbiname) +
	strlen ("/gems/libgems_db..so.."));
    facefullname =
	(char *)malloc (strlen (p->libdir) + strlen (p->facename) +
	strlen ("/gems/libgems_face..so.."));

    receptorname =
	(char *)malloc (strlen (p->libdir) +
	strlen ("/gems/libgemsreceptor.so."));

    if (p->libdir[0] != '\n' && p->libdir[0] != 0 && p->libdir[0] != '\r')
    {
	sprintf (dbifullname, "%s/gems/libgems_db.%s.so", p->libdir,
	    p->dbiname);
	sprintf (facefullname, "%s/gems/libgems_face.%s.so", p->libdir,
	    p->facename);
	sprintf (commonname, "%s/gems/libgemscommon.so", p->libdir);
	sprintf (receptorname, "%s/gems/libgemsreceptor.so", p->libdir);
    } else
    {
	sprintf (dbifullname, "gems/libgems_db.%s.so", p->dbiname);
	sprintf (facefullname, "gems/libgems_face.%s.so", p->facename);
	sprintf (commonname, "gems/libgemscommon.so");
	sprintf (receptorname, "gems/libgemsreceptor.so");
    }

    if (p == NULL)
    {
	printf ("config the crud...\n");
	return EXIT_FAILURE;
    }
    if ((common = dlopen (commonname, RTLD_LAZY | RTLD_GLOBAL)) == NULL)
    {
	printf ("Unable to open common library %s\n%s\n", commonname,
	    dlerror ());
	return EXIT_FAILURE;
    }
    free (commonname);

    if ((receptor = dlopen (receptorname, RTLD_LAZY | RTLD_GLOBAL)) == NULL)
    {
	printf ("Unable to open receptor library %s\n%s\n", receptorname,
	    dlerror ());
	return EXIT_FAILURE;
    }
    free (receptorname);

    dbi = dlopen (dbifullname, RTLD_LAZY | RTLD_GLOBAL);
    if (dbi == NULL)
    {
	printf ("Unable to open DBI %s\n%s\n", dbifullname, dlerror ());
	return EXIT_FAILURE;
    }
    free (dbifullname);

    face = dlopen (facefullname, RTLD_LAZY | RTLD_GLOBAL);
    if (face == NULL)
    {
	printf ("Unable to open face %s\n%s\n", facefullname, dlerror ());
	return EXIT_FAILURE;
    }
    free (facefullname);

    _db_init = dlsym (dbi, "db_init");
    _db_close = dlsym (dbi, "db_close");
    _face_uses_X = dlsym (face, "face_uses_X");
    _face_run = dlsym (face, "face_run");

    _db_init (p->dbihost, p->dbidb, p->dbiuser, p->dbipasswd);

    _face_run (argc, margv);

    for (x = 0; x < argc; x++)
	free (margv[x]);
    free (margv);

    parms_destroy (parm);
    _db_close ();
#if 0
    dlclose (face);		/* this freaks out gnome and causes segfault */
#endif
    dlclose (dbi);
    dlclose (common);
    dlclose (receptor);
    return 0;
    /*
     * return EXIT_SUCCESS; 
     */
}
