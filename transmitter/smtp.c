/*
 * 
 */

#include <stdio.h>		/* for NULL */
#include <stdlib.h>		/* getenv */
#include "defs.h"
#include "transmitter.h"

/*
 * these are the most significant digit of the return codes. 
 */
#define SMTP_OK		2
#define SMTP_PROMPT	3
#define SMTP_ERROR	5

/*
 * this is the actual code. 
 */
unsigned int smtp_reply_code;
char *smtp_error;

unsigned int
smtp_get_response ()
{
    return SMTP_OK;
}

char *
smtp_get_error ()
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
