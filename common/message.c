#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "spoolread.h"
#include "stringinate.h"
#include "ll.h"
#include "message.h"

char *
mutilate_line (char *line, int length)
{
    char *field;

    field = (char *) malloc (sizeof (char) * (strlen (line) - length + 1));
    strcpy (field, line + length);
    return field;
}

message *
message_build_from_list (void *list)
{
    message *x;
    void *header;
    void *body;
    char *line;

    x = NULL;

    x = (message *) malloc (sizeof (message));
    x->attachments = NULL;
    x->body = NULL;
    x->header = NULL;
    x->id = NULL;
    x->mbox = NULL;
    x->recipt = NULL;
    x->recvdate = NULL;
    x->replyto = NULL;
    x->senddate = NULL;
    x->sender = NULL;
    x->subject = NULL;
    x->references = NULL;

    header = ll_newlist ();
    body = ll_newlist ();
    ll_rewind (list);

    while (strcmp ((line = ll_showline (list)), "\n\0") != 0)
    {
	if (ll_addnode (header, line) == GEMS_FALSE)
	    return GEMS_FALSE;
	ll_next (header);
	ll_next (list);
	line[strlen (line) - 1] = 0;

	if (strncmp ("Message-Id: ", line, 12) == 0)
	{
	    if (x->id != NULL)
		free (x->id);
	    x->id = mutilate_line (line, 12);
	} else if (strncmp ("Message-ID: ", line, 12) == 0)
	{
	    if (x->id != NULL)
		free (x->id);
	    x->id = mutilate_line (line, 12);
	} else if (strncmp ("Message-id: ", line, 12) == 0)
	{
	    if (x->id != NULL)
		free (x->id);
	    x->id = mutilate_line (line, 12);
	} else if (strncmp ("References: ", line, 12) == 0)
	{
	    if (x->references != NULL)
		free (x->references);
	    x->references = mutilate_line (line, 12);
	} else if (strncmp ("To: ", line, 4) == 0)
	    x->recipt = mutilate_line (line, 4);
	else if (strncmp ("Cc: ", line, 4) == 0)
	{
	    if (x->recipt == NULL)
		x->recipt = mutilate_line (line, 4);
	} else if (strncmp ("Reply-To: ", line, 10) == 0)
	    x->replyto = mutilate_line (line, 10);
	else if (strncmp ("Date: ", line, 6) == 0)
	    x->senddate = mutilate_line (line, 6);
	else if (strncmp ("From: ", line, 6) == 0)
	    x->sender = mutilate_line (line, 6);
	else if (strncmp ("Subject: ", line, 9) == 0)
	    x->subject = mutilate_line (line, 9);
	/*
	 * need some way to get recvdate? 
	 */
    }
    if (x->replyto == NULL)
    {
	x->replyto = (char *) malloc (sizeof (char) * strlen (x->sender) + 1);
	strcpy (x->replyto, x->sender);
    }
    if (x->subject == NULL)
    {
	x->subject = (char *) malloc (1);
	x->subject[0] = 0;
    }
    do
    {
	line = ll_showline (list);
	ll_addnode (body, line);
    }
    while (ll_next (list) != GEMS_FALSE);

    x->header = (char *) stringinate ((void *) header);
    x->body = (char *) stringinate ((void *) body);

    ll_clearlist (body);
    ll_clearlist (header);

    x->mbox = (char *) malloc (6);
    sprintf (x->mbox, "inbox");

    return x;
}

int
message_destroy (message * m)
{
    if (!m)
	return GEMS_FALSE;
    if (m->id)
	free (m->id);
    if (m->mbox)
	free (m->mbox);
    if (m->attachments)
	free (m->attachments);
    if (m->body)
	free (m->body);
    if (m->header)
	free (m->header);
    if (m->recipt)
	free (m->recipt);
    if (m->recvdate)
	free (m->recvdate);
    if (m->replyto)
	free (m->replyto);
    if (m->senddate)
	free (m->senddate);
    if (m->sender)
	free (m->sender);
    if (m->subject)
	free (m->subject);
    if (m->references)
	free (m->references);

    free (m);
    m = NULL;
    return GEMS_TRUE;
}
