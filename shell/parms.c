#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "ll.h"
#include "parms.h"

static void
ver ()
{
  printf
    ("%s version %s (C) Copyright 2000 Erik Greenwald <erik@smluc.org>\n",
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
  int x = 0, y;
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

  /* read the parms into a linked list */
  while (x < *argc)
    ll_addnode (ll, margv[x++]);

  ll_rewind (ll);

  for (x = 1; x < *argc; x++)
    free (margv[x]);

  x = *argc;

  /* use the linked list */
  while (ll_next (ll) == GEMS_TRUE)
    {
      char *a;
      a = ll_showline (ll);
      if (!strcmp ("--", a))
	{
	  x--;
	  ll_deletenode (ll);
	  ll_next (ll);
	}
      else if (!strcmp ("-h", a) || !strcmp ("--help", a))
	{
	  ll_clearlist (ll);
	  help_exit (margv[0]);
	}
      else if (!strcmp ("-v", a) || !strcmp ("--version", a))
	{
	  ll_clearlist (ll);
	  ver_exit ();
	}
      else if (!strcmp ("-u", a) || !strcmp ("--dbuser", a))
	{
	  ll_deletenode (ll);
	  if (ll_end (ll) == GEMS_TRUE)
	    help_exit (margv[0]);
	  p->dbiuser = (char *) malloc (1 + strlen (ll_showline (ll)));
	  strcpy (p->dbiuser, ll_showline (ll));
	  ll_deletenode (ll);
	}
      else if (!strcmp ("-d", a) || !strcmp ("--dbms", a))
	{
	  ll_deletenode (ll);
	  if (ll_end (ll) == GEMS_TRUE)
	    help_exit (margv[0]);
	  p->dbiname = (char *) malloc (1 + strlen (ll_showline (ll)));
	  strcpy (p->dbiname, ll_showline (ll));
	  ll_deletenode (ll);
	}
      else
	{
	  p->facename = (char *) malloc (strlen (a) + 1);
	  strcpy (p->facename, a);
	  ll_deletenode (ll);
	}
    }

  free (margv[0]);

  ll_rewind (ll);

  /* move the linked list to the array */
  for (*argc = 0; *argc < x;)
    {
      char *a;

      a = ll_showline (ll);
      margv[*argc] = malloc (strlen (a) + 1);
      strcpy (margv[*argc], a);
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
