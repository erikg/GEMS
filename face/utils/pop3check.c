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
    printf ("\n");
    return GEMS_TRUE;
}
