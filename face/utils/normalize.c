#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "defs.h"
#include "db.h"

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
  if (db_normalize () == GEMS_FALSE)
  {
    printf (_("Failed to normalize the db"));
    return GEMS_FALSE;
  }

  printf ("\n");

  return GEMS_TRUE;
}
