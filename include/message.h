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
 * $Id: message.h,v 1.10 2010/01/06 00:47:31 erik Exp $
 */

#ifndef _MESSAGE_H
#define _MESSAGE_H

/** An email message */
typedef struct {
    char **attachments;
    char *body;
    char *header;
    char *id;
    char *mbox;
    char *recipt;
    char *recvdate;
    char *references;
    char *replyto;
    char *senddate;
    char *sender;
    char *status;
    char *subject;
} message;

/** the info useful for displaying lists of emails */
typedef struct _synopsis {
    int id;
    char *sender;
    char *date;
    char *subject;
} synopsis;

/** info pertaining to a mail box */
typedef struct {
    int id;
    char *name;
    int sub;
    int hasunread;
} mboxs;

/** convert a linked list to a message struct */
message *message_build_from_list (void *list);

/** convert a text buffer to a message struct */
message *message_build_from_buffer (char *buf);

/** purge a message from memory */
int message_destroy (message * mess);

#endif
