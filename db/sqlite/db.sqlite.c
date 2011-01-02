
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
 * $Id: db.sqlite.c,v 1.4 2011/01/02 17:39:14 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		/* strcasecmp() */
#include <ctype.h>
#include <time.h>

#include <sqlite3.h>

#include "defs.h"
#include "message.h"
#include "db.h"
#include "rules.h"
#include "face.h"		/* for oops() */

#define MAXRULES 1024

static sqlite3 *sqldb;

int /* TODO */
db_init (char *host, char *db, char *user, char *pass) {
    if(sqlite3_open(host, &sqldb) == SQLITE_OK) {
	return GEMS_TRUE;
    }
    oops("sqlite3 init", sqlite3_errmsg(sqldb));
    return GEMS_FALSE;
}

int
db_init_firstrun () {
    char *errmsg = NULL;
#define TRYEXEC(STMT) if(sqlite3_exec(sqldb, STMT, NULL, NULL, &errmsg) != SQLITE_OK) { fprintf(stderr, "SQL Error doing \"%s\": %s\n", STMT, sqlite3_errmsg(sqldb)); }
TRYEXEC("CREATE TABLE attachments ( id int(10) NOT NULL default '0', attachment longtext NOT NULL)");
TRYEXEC("CREATE TABLE body ( id int(10) NOT NULL default '0', body longtext NOT NULL, compressed varchar NOT NULL default 'false', PRIMARY KEY  (id))");
TRYEXEC("CREATE TABLE header ( id serial, header text NOT NULL, compressed varchar NOT NULL default 'false', PRIMARY KEY  (id))");
TRYEXEC("CREATE TABLE mmbox ( mbox serial, mboxname text NOT NULL, query text, PRIMARY KEY  (mbox))");
TRYEXEC("CREATE TABLE preferences ( name text NOT NULL, value text NOT NULL)");
TRYEXEC("CREATE TABLE recipt ( id int(10) NOT NULL default '0', recipt text NOT NULL, type tinytext NOT NULL)");
TRYEXEC("CREATE TABLE refs ( id int(10) NOT NULL default '0', refs text, childof int(10) default NULL)");
TRYEXEC("CREATE TABLE replyto ( id int(10) NOT NULL default '0', replyto text NOT NULL)");
TRYEXEC("CREATE TABLE rules ( sort int(10) NOT NULL default '0', name text, regex text, mbox text, piece varchar default NULL)");
TRYEXEC("CREATE TABLE synopsis ( id int(10) NOT NULL default '0', mbox int(11) NOT NULL default '0', status set('read','marked') NOT NULL default '', senddate datetime NOT NULL default '0000-00-00 00:00:00', sender text NOT NULL, subject text NOT NULL, charid text NOT NULL UNIQUE, PRIMARY KEY  (id))");
#undef TRYEXEC
}

int
db_insert_msg (char *mboxname, message * m) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int
db_flush (char *table) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int /* TODO */
db_addmbox (char *mbox) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int /* TODO */
db_addmbox_view (char *mbox, char *query) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int /* TODO */
db_dropmbox (char *mbox) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int /* TODO */
db_close () {
    if(sqlite3_close(sqldb) != SQLITE_OK) {
	oops("Closing db: ", sqlite3_errmsg(sqldb));
	return GEMS_FALSE;
    }
    return GEMS_TRUE;
}

synopsis ** /* TODO */
db_read_synopsis (int mbox, int status) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

mboxs **    /* TODO */
db_read_mboxlist (void) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

char *	/* TODO */
db_read_body (int id) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

message *
db_read_message (int id) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int
db_normalize () {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int
db_is_child_of (int msg) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

static int fetchruleidnumber = 0;
static int fetch_rule_cb(void *usr, int argc, char **argv, char **colname) {
    rule *r = ((rule *)usr) + fetchruleidnumber;

    printf("Boom!\n");
    if(argc != 5) {
	oops("Bad rule while fetching", sqlite3_errmsg(sqldb));
	return -1;
    }
    r->name = strdup(argv[0]);
    r->order = atoi(argv[1]);
    r->regex = strdup(argv[2]);
    r->mbox = strdup(argv[3]);
    r->piece = strdup(argv[4]);
    return 0;
}

rule * /* TODO */
db_fetch_rules (int *numrows) {
    char buf[BUFSIZ];
    void *l;
    int i;
    rule *r;

    r = malloc(sizeof(rule) * MAXRULES);
    /* LOCK */
    fetchruleidnumber = 0;
printf("Ayup\n");
    sqlite3_exec(sqldb, "select name,sort,regex,mbox,piece from rules order by sort", fetch_rule_cb, r, &buf);
    printf("Here we go\n");

    r = (rule *)realloc(r, sizeof(rule) * fetchruleidnumber+1);
    fetchruleidnumber = 0;
    /* UNLOCK */

    return r;
}

int /* TODO */
db_set_rules (rule ** rulelist) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int /* TODO */
db_pref_set (char *pref, char *val) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

char *	/* TODO */
db_pref_get (char *pref) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

void
db_syncharhash (void) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

void
db_purge_empty () {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}
