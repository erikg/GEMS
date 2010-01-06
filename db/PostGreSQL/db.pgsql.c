
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2004-2010 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: db.pgsql.c,v 1.13 2010/01/06 00:47:29 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

#include "defs.h"
#include "message.h"
#include "db.h"
#include "rules.h"
#include "face.h"		/* for oops() */

#define QSIZ 40000000
static char q[QSIZ];
#define QEX(m, args...) snprintf(q, QSIZ, m, ##args); PQexec(conn, q)
struct table_s {
    char *name, *vals;
};

struct table_s table[] = {
    {"attachments", "id int, attachment text"},
    {"body", "id int, body text"},
    {"header", "id serial, header text"},
    {"mbox", "name text"},
    {"prefs", "pref text, val text"},
    {"recipt", "id int, recipt text"},
    {"refs", "id int, childof int"},
    {"replyto", "id int, replyto text"},
    {"rules", "sort int, name text, regex text, mbox text, piece enum('Message','Body','Header','Subject','From','Recipients','Sender')"},
    {"synopsis", "id int, mbox text, status set('read','marked') NOT NULL default '', senddate timestamp with timezone NOT NULL, sender text NOT NULL, subject text, charid text, PRIMARY KEY  (id)"},
    {NULL,NULL}
};

PGconn *conn;

/** initialize the db connection (done in shell) */
int
db_init (char *host, char *db, char *user, char *pass)
{
    char buf[BUFSIZ];

    snprintf (buf, BUFSIZ, "host='%s' dbname='%s' user='%s' password='%s'", host,
	db, user, pass);
    conn = PQconnectdb (buf);
    if (PQstatus (conn) != CONNECTION_OK)
    {
	oops ("Unable to connect to PostgreSQL database",
	    (char *)PQerrorMessage (conn));
	db_close (conn);
	return GEMS_FALSE;
    }
    return GEMS_TRUE;
}

int
db_init_firstrun ()
{
    struct table_s *t;
    PGresult *res;
    char buf[BUFSIZ];

    t = table;
    while (t && t->name && t->vals)
    {
	printf("%s\n\t%s\n\n", t->name, t->vals);
	snprintf (buf, BUFSIZ, "create table \"%s\" (%s)", t->name, t->vals);
	res = PQexec (conn, buf);
	if (res == NULL)
	    oops ("Whoa, critical error", "res was returned as null");
	++t;
    }
    return GEMS_TRUE;
}

/** add a message to the db */
int
db_insert_msg (char *mbox, message * m)
{
    if(mbox==NULL || m==NULL) return GEMS_FALSE;
    QEX("INSERT INTO header VALUES (DEFAULT, '%s')", m->header);
/*   QEX("INSERT INTO synopsis VALUES (DEFAULT,(SELECT mbox FROM mmbox WHERE mboxname='%s'),)"); */
    oops("not implemented: ",__FUNCTION__);
    return GEMS_FALSE;
}

/** add a mailbox to the db */
int
db_addmbox (char *mbox)
{
    mbox=mbox;
    oops("not implemented: ",__FUNCTION__);
    return GEMS_FALSE;
}

int
db_addmbox_view (char *mbox, char *query)
{
    mbox=query;
    oops("not implemented: ",__FUNCTION__);
    return GEMS_FALSE;
}

/** drop a mailbox */
int
db_dropmbox (char *mbox)
{
    char buf[BUFSIZ];
    PGresult *res;

    snprintf (buf, BUFSIZ, "delete from mbox where name=%s", mbox);
    res = PQexec (conn, buf);
    if (res == NULL)
	oops ("Whoa, critical error", "res was returned as null");
    return GEMS_TRUE;
}

/** delete all entries in a table */
int
db_flush (char *table)
{
    char buf[BUFSIZ];
    PGresult *res;

    snprintf (buf, BUFSIZ, "delete from %s", table);
    res = PQexec (conn, buf);
    if (res == NULL)
	oops ("Whoa, critical error", "res was returned as null");
    return GEMS_TRUE;
}

/** shut down the db connection (done in shell) */
int
db_close ()
{
    PQfinish (conn);
    return GEMS_TRUE;
}

/** read the sender/subject/date/etc from a mailbox
 * matching the status */
synopsis **
db_read_synopsis (int mbox, int status)
{
    mbox=status;
    oops("not implemented: ",__FUNCTION__);
    return NULL;
}

synopsis **
db_read_synopsis_raw (char *query)
{
    query=NULL;
    oops("not implemented: ",__FUNCTION__);
    return NULL;
}

/** read a list of all mailboxes on the system */
mboxs **
db_read_mboxlist (void)
{
    oops("not implemented: ",__FUNCTION__);
    return NULL;
}

/** read the body of an email for reading */
char *
db_read_body (int id)
{
    id=0;
    oops("not implemented: ",__FUNCTION__);
    return NULL;
}

/** read the entire message for forwarding, replying,
 * and creating spools */
message *
db_read_message (int id)
{
    id=0;
    oops("not implemented: ",__FUNCTION__);
    return NULL;
}

/** make sure the tables are sane */
int
db_normalize ()
{
    oops("not implemented: ",__FUNCTION__);
    return GEMS_FALSE;
}

/** returns 0 if no parent */
int
db_is_child_of (int msg)
{
    msg=0;
    oops("not implemented: ",__FUNCTION__);
    return GEMS_FALSE;
}

/** return an array of rules */
rule *
db_fetch_rules (int *numrows)
{
    PGresult *r;
    rule *rules;
    int nr, x;

    r = PQexec(conn, "select name,sort,regex,mbox,piece from rules order by sort");
    if(r==NULL || (nr = PQntuples(r)) == 0) {
	oops ("failed to read rule set\n", "");
	exit(0);
    }
    rules = (rule *)malloc (sizeof(rule) * nr);
    for(x=0;x<nr;x++) {
	rules[x].name  = strdup(PQgetvalue(r,x,0));
	rules[x].order = atoi(PQgetvalue(r,x,1));
	rules[x].regex = strdup(PQgetvalue(r,x,2));
	rules[x].mbox  = strdup(PQgetvalue(r,x,3));
	rules[x].peice = strdup(PQgetvalue(r,x,4));
    }
    PQclear(r);
    *numrows = nr;
    return rules;
}

/** set the rules (erasing the old ones)*/
int
db_set_rules (rule ** r)
{
    r=NULL;
    oops("not implemented: ",__FUNCTION__);
    return GEMS_FALSE;
}

/** set a preference */
int
db_pref_set (char *pref, char *val)
{
    pref=val;
    oops("not implemented: ",__FUNCTION__);
    return GEMS_FALSE;
}

/** retrieve a preference */
char *
db_pref_get (char *pref)
{
    pref=NULL;
    oops("not implemented: ",__FUNCTION__);
    return NULL;
}

void
db_syncharhash (void)
{
    oops("not implemented: ",__FUNCTION__);
    return;
}

/** remove all entries with null/empty bodies. */
void
db_purge_empty ()
{
    oops("not implemented: ",__FUNCTION__);
    return;
}
