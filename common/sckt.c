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
	inet_addr (inet_ntoa (*((struct in_addr *) h->h_addr_list[0])));

    if ((s = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
	perror ("socket_open socket");
	exit (-1);
    }
    if (connect (s, (struct sockaddr *) &sockinf, sizeof (struct sockaddr)))
    {
	perror ("socket_open connect");
	exit (-1);
    }
    return s;
}
