#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "spoolread.h"
#include "ll.h"
#include "message.h"
#include "db.h"
#include "receptor.h"

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
}

int parse(char *buf, unsigned int size)
{
	int i, linecount, linecountsize, msgcount, msgcountsize;
	char **line, *walk;
    struct msg_s {
		char *head, *body;
	} *msg;

	linecount = 0;
	linecountsize=1024;
	line = malloc(sizeof(char *) * linecountsize);

	if(!strncmp("From ",buf,5))
		line[linecount++]=buf;
	for(walk=buf;walk<(buf+size);walk++)
		if(walk[0]=='\n')
		{
			if(linecount>=linecountsize)
				line = realloc(line,(linecountsize*=2)*sizeof(char *));
			line[linecount++] = walk+1;
		}

	msgcount = 0;
	msgcountsize=1024;
	msg = malloc(sizeof(struct msg_s) * msgcountsize);
//	memset(msg,0,sizeof(struct msg_s) * msgcountsize);
	for(i=0;i<linecount;++i)
	{
		if(!strncmp(line[i],"From ",5))
			if(i==0||line[i-1][0]=='\n')
			{
				if(i>0)
					line[i-1][0]=0;
				msg[msgcount].head=line[i];
				msgcount++;
			}
	}
/*
	for(i=0;i<msgcount;i++)
	{
		int j;
		printf("==============================================================================\n");
		printf("%s\n",msg[i]);
	}
*/
	return 0;
}

int face_run(int argc, char **argv)
{
	int fd;
	unsigned int size;
	char *buf;

	if(argc>=2)
		fd=open(argv[1],O_RDONLY);
	else
		fd=open("test",O_RDONLY);

	if(fd<=0)
		return(-1);

	buf = (char *)malloc(BIGBUFSIZ);	// 4 meg buffer
//	memset (buf, 0, BIGBUFSIZ);

	size = read(fd,buf,BIGBUFSIZ);

	parse(buf, size);

	free(buf);
	close(fd);
	return GEMS_TRUE;
}
