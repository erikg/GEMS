
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2004 Erik Greenwald <erik@smluc.org>                    *
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
 * $Id: db.pgsql.c,v 1.5 2004/02/14 19:41:28 erik Exp $
 */

#include <libpq-fe.h>

#include "defs.h"
#include "message.h"
#include "db.h"
#include "rules.h"
#include "face.h"		/* for oops() */

PGconn *conn;

/** initialize the db connection (done in shell) */
int
db_init (char *host, char *db, char *user, char *pass)
{
    char buf[4096];

    snprintf (buf, 4095, "host='%s' dbname='%s' user='%s' password='%s'", host,
	db, user, pass);
    conn = PQconnectdb (buf);
    if (PQstatus (conn) != CONNECTION_OK)
    {
	oops ("Unable to connect to PostgreSQL database",
	    PGerrorMessage (conn));
	db_close (conn);
	return GEMS_FALSE;
    }
    return GEMS_TRUE;
}

int
db_init_firstrun ()
{
}

/** add a message to the db */
int
db_insert_msg (char *mbox, message * m)
{
    return;
}

/** add a mailbox to the db */
int
db_addmbox (char *mbox)
{
    return;
}

int
db_addmbox_view (char *mbox, char *query)
{
    return;
}

/** drop a mailbox */
int
db_dropmbox (char *mbox)
{
    char buf[BUFSIZ];
    PGresult *res;
    snprintf(buf,BUFSIZ,"delete from mbox where name=%s", mbox);
    res = PGexec(con, buf);
    return;
}

/** delete all entries in a table */
int
db_flush (char *table)
{
    char buf[BUFSIZ];
    PGresult *res;
    snprintf(buf,BUFSIZ,"delete from %s", table);
    res = PQexec(con, buf);
    return;
}

/** shut down the db connection (done in shell) */
int
db_close ()
{
    PGfinish (conn);
    return;
}

/** read the sender/subject/date/etc from a mailbox
 * matching the status */
synopsis **
db_read_synopsis (int mbox, int status)
{
    return;
}

synopsis **
db_read_synopsis_raw (char *query)
{
    return;
}

/** read a list of all mailboxes on the system */
mboxs **
db_read_mboxlist (void)
{
    return;
}

/** read the body of an email for reading */
char *
db_read_body (int id)
{
    return;
}

/** read the entire message for forwarding, replying,
 * and creating spools */
message *
db_read_message (int id)
{
    return;
}

/** make sure the tables are sane */
int
db_normalize ()
{
    return;
}

/** returns 0 if no parent */
int
db_is_child_of (int msg)
{
    return;
}

/** return an array of rules */
rule *
db_fetch_rules (int *i)
{
    return;
}

/** set the rules (erasing the old ones)*/
int
db_set_rules (rule ** r)
{
    return;
}

/** set a preference */
int
db_pref_set (char *pref, char *val)
{
    return;
}

/** retrieve a preference */
char *
db_pref_get (char *pref)
{
    return;
}

void
db_syncharhash (void)
{
    return;
}

/** remove all entries with null/empty bodies. */
void
db_purge_empty ()
{
    return;
}
