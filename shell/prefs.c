#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    str = (char *) malloc (strlen (in));
    strcpy (str, extract (in));
    len = strlen (str);
    if (!strncmp ("LIBDIR", in, 6))
    {
	free (p->libdir);
	len--;
	/*
	 * if(p->libdir)free(p->libdir); 
	 */
	p->libdir = (char *) malloc (len + 2);
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
    char *in, *homedir, *rc;
    FILE *fp;

    if (m->rc == NULL)
    {
	if ((homedir = getenv ("HOME")) == NULL)
	{
	    printf ("Couldn't find your home directory, please set $HOME\n");
	    return NULL;
	}
	rc = (char *) malloc (strlen (homedir) + strlen ("/.gemsrc") + 1);

	sprintf (rc, "%s/.gemsrc", homedir);
	/*
	 * free (homedir); 
	 */
    } else
    {
	rc = m->rc;
    }

    if ((fp = fopen (rc, "r")) == NULL)
    {
	printf ("Couldn't open %s for reading\n", rc);
	free (rc);
	return NULL;
    }
    free (rc);

    p = (prefs *) malloc (sizeof (prefs));
    in = (char *) malloc (MAXSTRING);

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
