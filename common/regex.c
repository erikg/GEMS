#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "defs.h"

int
regex (char *r, char *s)
{
  void *preg;
  regmatch_t *pmatch;
  int val;

  preg = (void *) malloc (1000 * sizeof (void *));
  pmatch = (regmatch_t *) malloc (1000 * sizeof (regmatch_t));

  regcomp (preg, r, 0);

  if (regexec (preg, s, strlen (s), pmatch, 0) == 0)
    val = GEMS_TRUE;
  else
    val = GEMS_FALSE;

  regfree (preg);
  return val;
}
