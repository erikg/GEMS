/* 
 * this is a cut'n'paste from telnetting to my smtp server (smail)
 * 
 * 250-The following SMTP commands are recognized:
 * 250-
 * 250-   HELO hostname                   - startup and give your hostname
 * 250-   EHLO hostname                   - startup with extension info
 * 250-   MAIL FROM:<sender-address>      - start transaction from sender
 * 250-   RCPT TO:<recipient-address>     - name recipient for message
 * 250-   VRFY <address>                  - verify deliverability of address
 * 250-   EXPN <address>                  - expand mailing list address
 * 250-   DATA                            - start text of mail message
 * 250-   RSET                            - reset state, drop transaction
 * 250-   NOOP                            - do nothing
 * 250-   DEBUG [level]                   - set debugging level, default 1
 * 250-   HELP                            - produce this help message
 * 250-   QUIT                            - close SMTP connection
 * 
 *
 * This is from some literature I have on the subject...
 *
 * HELO domain
 * MAIL FROM:username
 * RCPT TO:username
 * DATA
 * QUIT
 *
 *
 * We should also note the return values. Here's some catagories (as best
 * as I can guess them) and some specific returns.
 *
 * 2XX ok message (success)
 * 250 OK
 * 251 forwarding/routing
 *
 * 3XX prompt for input
 * 354 'start mail input' (messages get ended with a . on a single line.)
 *
 * 5XX errors
 * 550 no such user
 */

#include <stdio.h>	/* for NULL */
#include <stdlib.h>	/* getenv */
#include "defs.h"
#include "transmitter.h"

 	/* these are the most significant digit of the return codes. */
#define SMTP_OK		2
#define SMTP_PROMPT	3
#define SMTP_ERROR	5

 	/* this is the actual code. */
unsigned int smtp_reply_code;
char *smtp_error;

unsigned int smtp_get_response()
{
	return SMTP_OK;
}

char *smtp_get_error()
{
	return NULL;
}

int
smtp_send (message * m, char *server, int port, char *username,
	   char *password)
{
  smtp_send_line ("HELO %s\r\n", getenv ("HOSTNAME"));
  if (smtp_get_response () == SMTP_ERROR)
    {
      oops ("SMTP Error", smtp_get_error ());
      return GEMS_FALSE;
    }

  smtp_send_line ("MAIL FROM:%s\r\n", m->sender);
  if (smtp_get_response () == SMTP_ERROR)
    {
      oops ("SMTP Error", smtp_get_error ());
      return GEMS_FALSE;
    }

  smtp_send_line ("RCPT TO:%s\r\n", m->recipt);
  if (smtp_get_response () == SMTP_ERROR)
    {
      oops ("SMTP Error", smtp_get_error ());
      return GEMS_FALSE;
    }

  smtp_send_line ("DATA\r\n");
  if (smtp_get_response () == SMTP_ERROR)
    {
      oops ("SMTP Error", smtp_get_error ());
      return GEMS_FALSE;
    }

  smtp_send_line ("%s\r\n.\r\n", m->body);
  if (smtp_get_response () == SMTP_ERROR)
    {
      oops ("SMTP Error", smtp_get_error ());
      return GEMS_FALSE;
    }

  smtp_send_line ("QUIT");
  if (smtp_get_response () == SMTP_ERROR)
    {
      oops ("SMTP Error", smtp_get_error ());
      return GEMS_FALSE;
    }

  return GEMS_TRUE;
}
