#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include "defs.h"

int
regex (char *r, char *s)
{
    void *preg;
    int val;

    preg = (void *) malloc (1000 * sizeof (void *));

    regcomp (preg, r, 0);

    if (regexec (preg, s, 0, NULL, 0) == 0)
	val = GEMS_TRUE;
    else
	val = GEMS_FALSE;

    regfree (preg);
    return val;
}
