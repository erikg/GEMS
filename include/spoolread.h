#ifndef __SPOOLREAD_H
#define __SPOOLREAD_H

/** open up a spool file for reading */
extern int open_spool (char *spoolname);

/** read the next message from the spool */
/*
 * @null@ 
 */
extern void *read_message ();

FILE *spool_file();
int spool_fd();

/** close the spool... */
extern int close_spool ();

#endif
