#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "defs.h"
#include "spoolread.h"
#include "ll.h"
#include "message.h"
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
    void *list;
    message *mess;
    char *spoolname, *mbox;

    /*
     * if(argc!=2){printf("this face requires the name of a spool\n%s
     * spool2sql -- <spool>\n\n",argv[0]);}
     */
    spoolname = margv[1];

    if (rule_init () == GEMS_FALSE)
    {
	printf (_("Failed to initialize ruleset\n"));
	exit (EXIT_FAILURE);
    }
    /*
     * initialize the spoolread system 
     */
    if (open_spool (spoolname) != GEMS_TRUE)
    {
	printf (_("Failed to open spool %s\n"), spoolname);
	exit (EXIT_FAILURE);
    }
    while ((list = read_message ()) != NULL)
    {
	if (ll_rewind (list) == GEMS_FALSE)
	    printf (_("Failed rewind\n"));
	mess = message_build_from_list (list);

	if (mess->body == NULL)
	    printf (_("\nNull body!\n"));

	mbox = rule_check (mess);
	db_insert_msg (mbox, mess);
	if (ll_clearlist (list) == GEMS_FALSE)
	    printf (_("Couldn't flush list out of memory!\n"));
	if (message_destroy (mess) == GEMS_FALSE)
	    printf (_("Couldn't flush message out of memory!\n"));
	printf (".");
	fflush (0);
    }

    if (rule_close () == GEMS_FALSE)
    {
	printf (_("Failed closing ruleset\n"));
    }
    /*
     * close out the spool 
     */
    if (close_spool () != GEMS_TRUE)
	printf (_("Couldn't close the spool\n"));
/*
//    printf ("Normalizing\n");
//    if (db_normalize () == GEMS_FALSE)
//	printf (_("Failed to normalize the db"));
*/
    printf ("\n");

    return GEMS_TRUE;
}
