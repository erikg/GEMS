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
 * $Id: db.h,v 1.13 2007/02/12 19:26:33 erik Exp $
 */

#ifndef __DB_H
#define __DB_H

#ifndef __MESSAGE_H
#include "message.h"
#endif

#include "rules.h"

/*
 * defines to read the synopsis. These not bitwise, even tho they look like
 * it.
 */
#define DB_READ		1
#define DB_UNREAD	2
#define DB_MARKED	4
#define DB_UNMARKED	8
#define DB_ALL		16

/** initialize the db connection (done in shell) */
int db_init (char *host, char *db, char *user, char *pass);

/** generate the tables. */
int db_init_firstrun ();

/** add a message to the db */
int db_insert_msg (char *mbox, message *m);

/** add a mailbox to the db */
int db_addmbox (char *mbox);
int db_addmbox_view (char *mbox, char *query);

/** drop a mailbox */
int db_dropmbox (char *mbox);

/** delete all entries in a table */
int db_flush (char *table);

/** shut down the db connection (done in shell) */
int db_close ();

/** read the sender/subject/date/etc from a mailbox
 * matching the status */
synopsis **db_read_synopsis (int mbox, int status);
synopsis **db_read_synopsis_raw (char *query);

/** read a list of all mailboxes on the system */
mboxs **db_read_mboxlist (void);

/** read the body of an email for reading */
char *db_read_body (int id);

/** read the header of an email for reading */
char *db_read_header (int id);

/** read the entire message for forwarding, replying,
 * and creating spools */
message *db_read_message (int id);

/** make sure the tables are sane */
int db_normalize ();

/** returns 0 if no parent */
int db_is_child_of (int msg);

/** return an array of rules */
rule *db_fetch_rules (int *count);

/** set the rules (erasing the old ones)*/
int db_set_rules (rule **r);

/** set a preference */
int db_pref_set (char *pref, char *val);

/** retrieve a preference */
char *db_pref_get (char *pref);

void db_syncharhash(void);

/** remove all entries with null/empty bodies. */
void db_purge_empty();

#endif
