#include <stdio.h>
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
    read (s, buf, 1024);
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
    if (_pop3_username (s, username) == GEMS_FALSE)
	return -1;
    if (_pop3_password (s, password) == GEMS_FALSE)
	return -1;
    last = _pop3_last_message (s);
    max = _pop3_stat (s);

    for (x = last; x <= max; x++)
      {
	  char *buf;
	int i=0;

	  buf = (char *) malloc (BUFSIZ);
	  list = ll_newlist ();
	while(read(s,buf+(i*BUFSIZ),BUFSIZ)==BUFSIZ)
	{
		buf = realloc(buf, (i+1)*BUFSIZ);	
		i++;
	}
	printf("Message: %s\n",buf);
//              while(getline != ".")
//                      list_add(l, getline)

    free (buf);
//	  mess = message_build (list);
//	  mbox = rule_check (mess);
//	  db_insert_msg (mbox, mess);
//	  message_destroy (mess);
	  ll_clearlist (list);
      }
    close (s);
    return GEMS_TRUE;
}
