/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2007 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: smtp.c,v 1.6 2007/02/12 19:26:33 erik Exp $
 */

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
