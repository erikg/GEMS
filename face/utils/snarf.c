#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "message.h"
#include "db.h"

#define BIGBUFSIZ (4096*1024*2)

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
    return;
}

int
parse (char *buf, unsigned int size)
{
    int i, linecount, linecountsize, msgcount, msgcountsize;
    char **line, *walk;
    struct msg_s {
	char *head, *body;
    } *msg;

    msgcount = linecount = 0;
    msgcountsize = linecountsize = 1024;
    line = malloc (sizeof (char *) * linecountsize);
    msg = malloc (sizeof (struct msg_s) * msgcountsize);

    if (!strncmp ("From ", buf, 5))
	line[linecount++] = buf;
    for (walk = buf; walk < (buf + size); walk++)
	if (walk[0] == '\n')
	{
	    if (linecount >= linecountsize)
		line = realloc (line, (linecountsize *= 2) * sizeof (char *));
	    line[linecount++] = walk + 1;
	}

    for (i = 0; i < linecount; ++i)
	if (!strncmp (line[i], "From ", 5))
	    if (i == 0 || line[i - 1][0] == '\n')
	    {
		if (i > 0)
		    line[i - 1][0] = 0;
		msg[msgcount].head = line[i];
		msgcount++;
	    }

    for (i = 0; i < msgcount; i++)
	{
		message *m;
		m = message_build_from_buffer(msg[i].head);
		message_destroy(m);
	}
    return 0;
}

int
face_run (int argc, char **argv)
{
    int fd;
    unsigned int size;
    char *buf;

    fd = open (argv[1], O_RDONLY);

    if (fd <= 0)
	return (-1);

    buf = (char *)malloc (BIGBUFSIZ);	// 4 meg buffer

    size = read (fd, buf, BIGBUFSIZ);
    buf[size] = 0;

    parse (buf, size);

    free (buf);
    close (fd);
    return GEMS_TRUE;
}
