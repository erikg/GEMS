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
face_run (int argc, char **margv)
{
  void *list;
  message *mess;
  char *spoolname, *mbox;
/*  if(argc!=2){printf("this face requires the name of a spool\n%s spool2sql -- <spool>\n\n",argv[0]);}
*/

  if (rule_init () == GEMS_FALSE)
    {
      printf (_("Failed to initialize ruleset\n"));
      exit (EXIT_FAILURE);
    }

  /* do shit. */
  receive_pop3("freya",110,"test","tester");

  if (rule_close () == GEMS_FALSE)
    {
      printf (_("Failed closing ruleset\n"));
    }

  /* close out the spool */
  if (close_spool () != GEMS_TRUE)
    printf (_("Couldn't close the spool\n"));

  printf ("Normalizing\n");
  if (db_normalize () == GEMS_FALSE)
    printf (_("Failed to normalize the db"));

  printf ("\n");

  return GEMS_TRUE;
}
