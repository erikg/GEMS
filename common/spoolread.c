#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "ll.h"
#include "spoolread.h"
#include "face.h"		/* for oops() */

static char *out, *line;
static FILE *spool;

static int
fake_fungets (FILE * fp, char *string)
{
  fseek (fp, -strlen (string), SEEK_CUR);
  return GEMS_TRUE;
}

int
open_spool (char *spoolname)
{
  if (spoolname == NULL)
    if ((spoolname = getenv ("MAIL")) == NULL)
      {
	oops ("Spoolread", "Couldn't get mail spool name");
	return (EXIT_FAILURE);
      }

  printf ("Opening %s\n", spoolname);

  if ((spool = fopen (spoolname, "r")) == NULL)
    {
      oops ("Spoolread\nUnable to open mail spool", spoolname);
      return (EXIT_FAILURE);
    }
  line = (char *) malloc (1024);
  if (line == NULL)
    {
      oops ("Spoolread", "Failed malloc");
      if (fclose (spool) != 0)
	exit (EXIT_FAILURE);
      return GEMS_FALSE;
    }
  out = (char *) malloc (65535);
  if (out == NULL)
    {
      oops ("Spoolread", "failed malloc");
      exit (EXIT_FAILURE);
    }
  return GEMS_TRUE;
}

/*@null@*/
void *
read_message ()
{
  void *list;
  int inmessage = 0;

  list = ll_newlist ();
  if (list == NULL)
    return NULL;
  out[0] = (char) 0;

  while (fgets (line, 1024, spool) != 0)
    {
      if (!strncmp (line, "From ", 5))	/* could this be better? */
	{
	  if (inmessage == 1)
	    {
	      fake_fungets (spool, line);
	      if (ll_rewind (list) == GEMS_FALSE)
		oops ("Spoolread", "Failed rewind");
	      return list;
	    }
	  else
	    {
	      inmessage = 1;
	    }
	}
else if(inmessage==1)
      if (ll_addnode (list, line) == GEMS_FALSE)
	oops ("Spoolread", "Failed addnode");
    }

    if (ll_rewind (list) == GEMS_FALSE)
      oops ("Spoolread", "Failed rewind");

  if (ll_empty (list) == GEMS_TRUE)
    {
      ll_clearlist (list);
      return NULL;
    }

  return list;
}


int
close_spool ()
{
  free (line);
  free (out);
  if (fclose (spool) != 0)
    oops ("Spoolread", "Failed to close spool");
  return GEMS_TRUE;
}
