#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "db.h"

extern int do_db_flush (char *);

int
face_uses_X ()
{
    return GEMS_FALSE;
}

void
oops (char *a, char *b)
{
    printf ("%s\n%s\n", a, b);
}

int
face_run (char *trash)
{
    /*
     * assume the db is already set up 
     */

    db_flush ("attachments");
    putchar ('.');
    db_flush ("body");
    putchar ('.');
    db_flush ("header");
    putchar ('.');

    /*
     * db_flush ("mmbox"); putchar ('.'); db_flush ("preferences"); putchar
     * ('.');
     */
    db_flush ("recipt");
    putchar ('.');
    db_flush ("replyto");
    putchar ('.');
    db_flush ("synopsis");
    putchar ('.');
    db_flush ("refs");
    putchar ('.');

    /*
     * db_addmbox ("inbox"); putchar ('.'); db_addmbox ("sent"); putchar
     * ('.'); db_addmbox ("trash"); putchar ('.'); db_addmbox ("drafts");
     * putchar ('.');
     */
    printf ("\n");

    return 0;
}
