
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2005 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: sckt.c,v 1.6 2005/01/13 14:29:53 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "sckt.h"

int
socket_open (char *hostname, int port)
{
    int s;
    struct hostent *h;
    struct sockaddr_in sockinf;

    h = gethostbyname (hostname);

    memset (&sockinf, 0, sizeof (struct sockaddr));
    sockinf.sin_family = AF_INET;
    sockinf.sin_port = htons (port);
    sockinf.sin_addr.s_addr =
	inet_addr (inet_ntoa (*((struct in_addr *)h->h_addr_list[0])));

    if ((s = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
	perror ("socket_open socket");
	exit (-1);
    }
    if (connect (s, (struct sockaddr *)&sockinf, sizeof (struct sockaddr)))
    {
	perror ("socket_open connect");
	exit (-1);
    }
    return s;
}
