#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "defs.h"
#include "ll.h"
#include "stringinate.h"
#include "face.h"		/* for oops() */

char *
stringinate (void *list)
{
    char *x;
    char *line;
    int l = 0;

    x = NULL;
    line = (char *)malloc (1024);

    if (ll_rewind (list) == GEMS_FALSE)
    {
	oops ("Stringinate", "failed to rewind");
	exit (EXIT_FAILURE);
    }
    do
    {
	char *blah;

	blah = ll_showline (list);
	l += (strlen (blah) + 1);
    }
    while (ll_next (list) == GEMS_TRUE);
    l++;

    x = (char *)malloc (sizeof (char) * (l + 1));
    if (x == NULL)
    {
	oops ("Stringinate", "Failed to allocate");
	exit (EXIT_FAILURE);
    } else
	memset (x, (size_t) 0, (size_t) l);

    if (ll_rewind (list) == GEMS_FALSE)
	oops ("Stringinate", "failed rewind");
    do
    {
	char *blah;

	blah = ll_showline (list);
	if (blah == NULL)
	{
	    oops ("Stringinate", "bad ll_showline()");
	    exit (EXIT_FAILURE);
	}
	strcat (x, blah);
    }
    while (ll_next (list) == GEMS_TRUE);
    free (line);
    return x;
}

void *
read_file_to_list (char *filename)
{
    void *list;
    char *buf, *s;
    struct stat sb;
    int fd;

    if (stat (filename, &sb) || sb.st_size == 0
	|| !(sb.st_mode & (S_IFREG | S_IFLNK))){
	printf("Not readable...\n");
	return NULL;}
    list = ll_newlist ();
    fd = open (filename, O_RDONLY);
	printf("fd: %d\n", fd);
    if (fd == -1)
	return NULL;
    s = buf = (char *)malloc (sizeof (char) * sb.st_size);
    read (fd, buf, sb.st_size);
	printf("buf: %s\n\n", buf);
    while (s < (buf + sb.st_size))
    {
	if (*s == '\n' || *s == '\r')
	    *s = 0; 
	++s;
    }
	s = buf;
    while (s < (buf + sb.st_size))
    {
	char sigline[1024];
#if 0
	while 
#else
	if
#endif
	(*s == 0)
	    ++s;
	printf("Adding line: %s\n", s);
	snprintf(sigline, 1023, "%s\n", s);
	ll_addnode (list, sigline);
	s += strlen (s);
    }
    return list;
}
