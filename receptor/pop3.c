#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "defs.h"
#include "receptor.h"
#include "message.h"
#include "ll.h"
#include "rules.h"
#include "sckt.h"

int
_pop3_last_message (int s)
{
    char buf[1024];

    if (s == -1)
	return -1;
    write (s, "LAST\r\n", 6);
    printf ("Sent 'last' to %d\n", s);
    fflush (stdout);
    read (s, buf, 1024);
    printf ("Got \"%s\"\n", buf);
    fflush (stdout);
    if (strncmp (buf, "+OK ", 4))
	return -1;
    return atoi (buf + 4);
}

int
_pop3_stat (int s)
{
    char buf[1024];

    if (s == -1)
	return -1;
    write (s, "STAT\r\n", 6);
    read (s, buf, 1024);
    if (strncmp (buf, "+OK ", 4))
	return -1;
    return atoi (buf + 4);
}

int
_pop3_user (int s, char *username)
{
    char buf[1024];

    if (s == -1)
	return GEMS_FALSE;
    sprintf (buf, "USER %s\r\n", username);
    write (s, buf, strlen (buf) + 1);
    read (s, buf, 1024);
    if (strncmp (buf, "+OK ", 4))
	return GEMS_FALSE;
    return GEMS_TRUE;
}

int
_pop3_passwd (int s, char *password)
{
    char buf[1024];

    if (s == -1)
	return GEMS_FALSE;
    sprintf (buf, "PASS %s\r\n", password);
    write (s, buf, strlen (buf) + 1);
    read (s, buf, 1024);
    if (strncmp (buf, "+OK ", 4))
	return GEMS_FALSE;
    return GEMS_TRUE;
}

int
receive_pop3 (char *hostname, int port, char *username, char *password)
{
    int x, n, s, last, max;
    void *list;
    message *mess;
    char *mbox, stat[5];

    s = socket_open (hostname, port);
    if (_pop3_user (s, username) == GEMS_FALSE)
	return -1;
    printf ("User accepted\n");
    fflush (stdout);
    if (_pop3_passwd (s, password) == GEMS_FALSE)
	return -1;
    printf ("Password accepted, I am logged in.\n");
    fflush (stdout);
    last = _pop3_last_message (s);
    printf ("Last message: %d\n", last);
    fflush (stdout);
    max = _pop3_stat (s);
    printf ("Max message: %d\n", max);
    fflush (stdout);

    for (x = last; x <= max; x++)
    {
	char *buf;
	int i = 0;

	buf = (char *) malloc (BUFSIZ);
	list = ll_newlist ();
	while (read (s, buf + (i * BUFSIZ), BUFSIZ) == BUFSIZ)
	{
	    buf = realloc (buf, (i + 1) * BUFSIZ);
	    i++;
	}
	printf ("Message: %s\n", buf);
#if 0
	// while (getline != ".")
	// list_add (l, getline)

	free (buf);
	// mess = message_build (list);
	// mbox = rule_check (mess);
	// db_insert_msg (mbox, mess);
	// message_destroy (mess);
#endif
	ll_clearlist (list);

    }
    close (s);
    return GEMS_TRUE;
}
