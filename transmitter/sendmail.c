
/*
 * $Id: sendmail.c,v 1.2 2003/04/05 18:29:45 erik Exp $
 */

#include <stdio.h>
#include "transmitter.h"

static char *cmd[] = { "/usr/sbin/sendmail", "-oi", "-t", NULL };

int transmit_sendmail (message *)
{
	int pid;
	pid = fork();
	switch(pid)
	{
		case -1:
			oops("Whoa, catastauphic failure","Fork failed!!!");
			return -1;
			break;
		case 0:		/* child */
			execve(cmd);
			break;
		default:	/* parent */	

			waitpid(pid,NULL,0);
			break;
	}
	return 0;
}
