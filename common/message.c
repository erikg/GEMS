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
    return strdup (line + length);
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

void *memdup(void *src, int size){ void *m = malloc(size); memcpy(m,src,size); return m; }

message *
message_build_from_buffer (char *buf)
{
    message *m;
    int x = 0, i;

    m = (message *) malloc (sizeof (message));
    memset (m, 0, sizeof (message));	/* fill out NULLs */
    while (!(buf[x] == 0 || (buf[x] == '\n' && buf[x + 1] == '\n')))
	x++;
    if (buf[x] == 0)
	return NULL;		/* bad message */
    buf[x] = 0;
    m->header = strdup(buf);
    m->body = strdup (buf + x + 2);
    for (i = x; i; i--)
	if (buf[i] == '\n' && buf[i + 1] == '\n')
	    buf[i + 1] = 0;
    for (i = x; i; i--)
	if (buf[i] == '\n')
	    buf[i] = 0;
    while (i < x)
    {
	switch (tolower (buf[i]))
	{
	case 'c':
	    if (!strncmp (buf + i, "Cc: ", 4))
		m->recipt = strdup (buf + i + 4);
	    break;
	case 'd':
	    if (!strncmp (buf + i, "Date: ", 6))
		m->senddate = strdup (buf + i + 6);
	    break;
	case 'f':
	    if (!strncmp (buf + i, "From: ", 6))
		m->sender = strdup (buf + i + 6);
	    break;
	case 'm':
	    if (!strncmp (buf + i, "Message-", 8)
		&& (tolower (buf[i + 8]) == 'i')
		&& (tolower (buf[i + 9]) == 'd')
		&& !strncmp (buf + i + 10, ": ", 2))
		m->id = strdup (buf + i + 12);
	    break;
	case 'r':
	    if (!strncmp (buf + i, "References: ", 12))
		m->references = strdup (buf + i + 12);
	    if (!strncmp (buf + i, "Reply-To: ", 10))
		m->replyto = strdup (buf + i + 10);
	    break;
	case 's':
	    if (!strncmp (buf + i, "Subject: ", 9))
		m->subject = strdup (buf + i + 9);
	    break;
	case 't':
	    if (!strncmp (buf + i, "To: ", 4))
		m->recipt = strdup (buf + i + 4);
	    break;
	default:
	}
	while (buf[i] != 0)
	    i++;
	i++;
    }
    if (m->replyto == NULL)
	m->replyto = strdup (m->sender);
    return m;
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
