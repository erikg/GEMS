#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "message.h"
#include "db.h"

#define MEGS *1024*1024

	/* 8 megs */
#define BIGBUFSIZ (8 MEGS)

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
    char **line, *walk, **msg, *mbox;

    msgcount = linecount = 0;
    msgcountsize = linecountsize = 1024;
    line = malloc (sizeof (char *) * linecountsize);
    msg = malloc (sizeof (char *) * msgcountsize);

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
		msg[msgcount] = line[i];
		msgcount++;
	    }

    for (i = 1; i <= msgcount; i++)
	{
		message *m;
		printf("\r                                                                               \r");
		printf("%d/%d  (%.2f%%)", i, msgcount, 100.0*(float)i/(float)msgcount);
		fflush(stdout);
		m = message_build_from_buffer(msg[i-1]);
		mbox = rule_check(m);
		db_insert_msg(mbox,m);	/* this sucks up time */
		message_destroy(m);
	}
	printf("\n");
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

    if (rule_init () == GEMS_FALSE)
    {
        printf (_("Failed to initialize ruleset\n"));
        exit (EXIT_FAILURE);
    }

    buf = (char *)malloc (BIGBUFSIZ);

    size = read (fd, buf, BIGBUFSIZ);
    buf[size] = 0;
    parse (buf, size);

    if (rule_close () == GEMS_FALSE)
    {
        printf (_("Failed closing ruleset\n"));
    }

    free (buf);
    close (fd);
    return GEMS_TRUE;
}
