#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "ll.h"
#include "stringinate.h"
#include "face.h"		/* for oops() */

char *
stringinate (void *list)
{
  char *x;
  char *line;
  int l = 0;
  x = NULL;
  line = (char *) malloc (1024);

  if (ll_rewind (list) == GEMS_FALSE)
    {
      oops ("Stringinate", "failed to rewind");
      exit (EXIT_FAILURE);
    }
  do
    {
      char *blah;
      blah = ll_showline (list);
      l += (strlen (blah) + 1);
/*      free (blah);	*/
    }
  while (ll_next (list) == GEMS_TRUE);
  l++;

  x = (char *) malloc (sizeof (char) * (l + 1));
  if (x == NULL)
    {
      oops ("Stringinate", "Failed to allocate");
      exit (EXIT_FAILURE);
    }
  else
    memset (x, (size_t) 0, (size_t) l);

  if (ll_rewind (list) == GEMS_FALSE)
    oops ("Stringinate", "failed rewind");
  do
    {
      char *blah;
      blah = ll_showline (list);
      if (blah == NULL)
	{
	  oops ("Stringinate", "bad ll_showline()");
	  exit (EXIT_FAILURE);
	}
      strcat (x, blah);
/*      free (blah);	*/
    }
  while (ll_next (list) == GEMS_TRUE);

  free (line);

  return x;
}
