
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2005 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: prefs.c,v 1.5 2005/01/13 14:29:54 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "prefs.h"

#define MAXSTRING 65535

static char *
extract (char *in)
{
    int x;

    x = 0;
    while (in[x] != 0 && in[x] != '=')
	x++;
    x++;
    while (in[x] != 0 && in[x] == ' ')
	x++;
    return &in[x];
}

static void
parse (prefs * p, char *in, parms * m)
{
    char *str;
    int len;

    if (in == NULL)
	return;
    str = (char *)malloc (strlen (in));
    strcpy (str, extract (in));
    len = strlen (str);
    if (!strncmp ("LIBDIR", in, 6))
    {
	free (p->libdir);
	len--;
	/*
	 * if(p->libdir)free(p->libdir); 
	 */
	p->libdir = (char *)malloc (len + 2);
	strcpy (p->libdir, str);
	if (str[len] != '/' && strlen (str) > 0)
	{
	    p->libdir[len + 1] = '/';
	    p->libdir[len + 2] = 0;
	}
    } else if (!strncmp ("DBINAME", in, 7) && m->dbiname == NULL)
    {
	free (p->dbiname);
	p->dbiname = str;
    } else if (!strncmp (in, "DBIHOST", 7) && m->dbihost == NULL)
    {
	free (p->dbihost);
	p->dbihost = str;
    } else if (!strncmp (in, "DBIUSER", 7) && m->dbiuser == NULL)
    {
	free (p->dbiuser);
	p->dbiuser = str;
    } else if (!strncmp (in, "DBIPASSWORD", 11) && m->dbipasswd == NULL)
    {
	free (p->dbipasswd);
	p->dbipasswd = str;
    } else if (!strncmp (in, "DBIDATABASE", 11) && m->dbidb == NULL)
    {
	free (p->dbidb);
	p->dbidb = str;
    } else if (!strncmp (in, "FACENAME", 8) && m->facename == NULL)
    {
	free (p->facename);
	p->facename = str;
    }
    return;
}

prefs *
load_prefs (parms * m)
{
    prefs *p;
    char *in, *homedir, *rc, *orc;
    FILE *fp;

    if (m->rc == NULL)
    {
	char *gemsconfigdir;
	struct stat sb;

	if ((homedir = getenv ("HOME")) == NULL)
	{
	    printf ("Couldn't find your home directory, please set $HOME\n");
	    return NULL;
	}

	orc = (char *)malloc (strlen (homedir) + strlen ("/.gemsrc") + 1);
	gemsconfigdir =
	    (char *)malloc (strlen (homedir) + strlen ("/.gems") + 1);
	rc = (char *)malloc (strlen (homedir) + strlen ("/.gems/gemsrc") + 1);

	sprintf (orc, "%s/.gemsrc", homedir);
	sprintf (gemsconfigdir, "%s/.gems", homedir);
	sprintf (rc, "%s/.gems/gemsrc", homedir);

	/*
	 * if the .gems dir doesn't exist, create it 
	 */
	if (stat (gemsconfigdir, &sb) == -1)
	    mkdir (gemsconfigdir, 0700);

	if (stat (rc, &sb) == -1)
	{
	    if (stat (orc, &sb) == 0)
	    {
		printf ("Linking to %s the file %s\n", orc, rc);
		if (link (orc, rc) == -1)
		{
		    printf ("Whoa, link failed! %d\n", errno);
		    perror ("gems:link");
		    exit (-1);
		}
		unlink (orc);
		printf
		    ("Old config file %s has been deleted. new file is %s\n",
		    orc, rc);
	    } else
	    {
		printf ("Must create an RC file\n");
		exit (-1);
	    }
	}

    } else
	rc = m->rc;

    if ((fp = fopen (rc, "r")) == NULL)
    {
	printf ("Couldn't open %s for reading\n", rc);
	free (rc);
	return NULL;
    }
    free (rc);

    p = (prefs *) malloc (sizeof (prefs));
    in = (char *)malloc (MAXSTRING);

    p->libdir = malloc (1);
    p->dbiname = malloc (1);
    p->dbihost = malloc (1);
    p->dbiuser = malloc (1);
    p->dbipasswd = malloc (1);
    p->dbidb = malloc (1);
    p->facename = malloc (1);
    p->libdir[0] = p->dbiname[0] = p->dbihost[0] = p->dbiuser[0] =
	p->dbipasswd[0] = p->dbidb[0] = p->facename[0] = 0;

    while (!feof (fp))
    {
	int x;

	in[0] = 0;
	fgets (in, MAXSTRING, fp);
	if (in != NULL && strlen (in) > 1)
	{
	    for (x = 0; x < strlen (in); x++)
		if (in[x] == '#' || in[x] == '\n')
		    in[x] = 0;
	    if (in[0] == 'L' || in[0] == 'D' || in[0] == 'F')
		parse (p, in, m);
	}
    }

    fclose (fp);

    if (m->libdir != NULL)
	p->libdir = m->libdir;
    if (m->dbiname != NULL)
	p->dbiname = m->dbiname;
    if (m->dbihost != NULL)
	p->dbihost = m->dbihost;
    if (m->dbiuser != NULL)
	p->dbiuser = m->dbiuser;
    if (m->dbipasswd != NULL)
	p->dbipasswd = m->dbipasswd;
    if (m->dbidb != NULL)
	p->dbidb = m->dbidb;
    if (m->facename != NULL)
	p->facename = m->facename;

    free (in);

    return p;
}

void
save_prefs (prefs * p)
{
    FILE *fp;
    char *rc;
    char *homedir;

    homedir = getenv ("HOME");
    if (homedir == NULL)
    {
	printf ("Couldn't find your home directory, please set $HOME\n");
	return;
    }
    sprintf (rc, "%s/.gemsrc", homedir);
    free (homedir);
    fp = fopen (rc, "w");
    free (rc);
    if (fp == NULL)
    {
	printf ("Couldn't open %s for writing\n", rc);
	return;
    }
    fprintf (fp, "#this is a machine generated file\n\n");
    fprintf (fp,
	"#this is the full path to where the libgems_*.so libraries are\n");
    fprintf (fp, "LIBDIR = %s\n\n", p->libdir);
    fprintf (fp, "\nname of the DBMS to use (mysql, postgresql, etc)\n");
    fprintf (fp, "DBINAME = %s\n", p->dbiname);
    fprintf (fp, "\nmachine that the dbms resides on (ip or hostname)\n");
    fprintf (fp, "DBIHOST = %s\n", p->dbihost);
    fprintf (fp, "\nuser account for the dbms\n");
    fprintf (fp, "DBIUSER = %s\n", p->dbiuser);
    fprintf (fp, "\npassword for the dbms\n");
    fprintf (fp, "DBIPASSWORD = %s\n", p->dbipasswd);
    fprintf (fp, "\ndatabase name in dbms\n");
    fprintf (fp, "DBIDATABASE = %s\n\n", p->dbidb);
    fprintf (fp, "\n\nname of the 'face' to use (gnome_e, curses_m, etc)\n");
    fprintf (fp, "FACENAME = %s\n", p->facename);

    fclose (fp);
    return;
}
