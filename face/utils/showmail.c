#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "defs.h"
#include "message.h"
#include "db.h"
#include "spoolread.h"
#include "ll.h"

#ifndef _
#define _
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
face_run (int argc, char **argv)
{
  void *list;
  message *mess;

  if (open_spool (argv[1]) == GEMS_FALSE)
    {
      printf (_("Failed to open spool\n"));
      return EXIT_FAILURE;
    }

  while ((list = read_message ()) != NULL)
    {
      if (ll_rewind (list) == GEMS_FALSE)
	printf (_("Failed rewind\n"));
      mess = message_build_from_list (list);

      printf (_("%s: %s -> %s Subject: %s\n%s\n"), mess->id,
	      mess->sender, mess->recipt, mess->subject, mess->body);

      if (ll_clearlist (list) == GEMS_FALSE)
	printf (_("Couldn't flush list out of memory!\n"));
      if (message_destroy (mess) == GEMS_FALSE)
	printf (_("Couldn't flush message out of memory!\n"));
    }

  /* close out the spool */
  if (close_spool () != GEMS_TRUE)
    printf (_("Couldn't close the spool\n"));

  return 0;
}
