/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2010 Erik Greenwald <erik@smluc.org>               *
 *                                                                           *
 *     This program is free software; you can redistribute it and/or modify  *
 *     it under the terms of the GNU General Public License as published by  *
 *     the Free Software Foundation; either version 2 of the License, or     *
 *     (at your option) any later version.                                   *
 *                                                                           *
 *     This program is distributed in the hope that it will be useful,       *
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *     GNU General Public License for more details.                          *
 *                                                                           *
 *     You should have received a copy of the GNU General Public License     *
 *     along with this program; if not, write to the Free Software           *
 *     Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.             *
 *                                                                           *
 *****************************************************************************/

/*
 * $Id: sendmail.c,v 1.9 2010/01/06 00:47:32 erik Exp $
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "face.h"
#include "transmitter.h"

static char *cmd[] = { "/usr/sbin/sendmail", "-oi", "-t", NULL };

int transmit_sendmail (message *m)
{
	int pid;
	printf("This is not done. %x\n", (unsigned int) m);
	pid = fork();
	switch(pid)
	{
		case -1:
			oops("Whoa, catastauphic failure","Fork failed!!!");
			return -1;
			break;
		case 0:		/* child */
			execve(*cmd, &cmd[1], NULL);
			break;
		default:	/* parent */	

			waitpid(pid,NULL,0);
			break;
	}
	return 0;
}
