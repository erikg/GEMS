#ifndef __GEMS_RECEPTOR_H_
#define __GEMS_RECEPTOR_H_

/* some amusing stuff here. */

	/** retreives messages from a pop3 server */
int receive_pop3(char *host, int port, char *username, char *passwd);
	/** retreives messages from an imap4  server */
void receive_imap4();
	/** retreives messages from a spool */
void receive_spool(char *spoolname);

#endif
