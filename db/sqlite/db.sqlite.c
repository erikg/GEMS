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
 * $Id: db.sqlite.c,v 1.5 2011/01/02 20:27:29 erik Exp $
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
TRYEXEC("CREATE TABLE attachments (id INTEGER NOT NULL, attachment longtext NOT NULL);");
TRYEXEC("CREATE TABLE body (id INTEGER PRIMARY KEY, body longtext NOT NULL, compressed VARCHAR NOT NULL default 'false');");
TRYEXEC("CREATE TABLE header (id INTEGER PRIMARY KEY, header text NOT NULL, compressed VARCHAR NOT NULL default 'false');");
TRYEXEC("CREATE TABLE mmbox (mbox INTEGER PRIMARY KEY, mboxname text NOT NULL, query text);");
TRYEXEC("CREATE TABLE preferences (name text NOT NULL, value text NOT NULL);");
TRYEXEC("CREATE TABLE recipt (id INTEGER NOT NULL default '0', recipt text NOT NULL, type tinytext NOT NULL);");
TRYEXEC("CREATE TABLE refs (id INTEGER NOT NULL default '0', refs text, childof INTEGER default NULL);");
TRYEXEC("CREATE TABLE replyto (id INTEGER NOT NULL default '0', replyto text NOT NULL);");
TRYEXEC("CREATE TABLE rules (sort INTEGER NOT NULL default '0', name text, regex text, mbox text, piece VARCHAR default NULL);");
TRYEXEC("CREATE TABLE synopsis (id INTEGER PRIMARY KEY, mbox INTEGER NOT NULL default '0', status VARCHAR NOT NULL default '', senddate datetime NOT NULL default '0000-00-00 00:00:00', sender text NOT NULL, subject text NOT NULL, charid text NOT NULL UNIQUE);");
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

rule *
db_fetch_rules (int *numrows) {
    const char **results = NULL, **colnames = NULL, **pzTail = NULL;
    char *buf = NULL;
    rule *rules, *r;
    int rval;
    const char stmt_str[] = "select name,sort,regex,mbox,piece from rules order by sort";
    sqlite3_stmt *stmt;

    *numrows = 0;
    r = rules = malloc(sizeof(rule) * MAXRULES);
    if(sqlite3_prepare_v2(sqldb, stmt_str, strlen(stmt_str)+1, &stmt, pzTail) != SQLITE_OK) {
	oops("Problem generating statement to fetch rules", sqlite3_errmsg(sqldb));
	return NULL;
    }
    while((rval=sqlite3_step(stmt)) != SQLITE_DONE) {
	r->name = strdup(sqlite3_column_text(stmt, 0));
	r->order = sqlite3_column_int(stmt, 1);
	r->regex = strdup(sqlite3_column_text(stmt, 2));
	r->mbox = strdup(sqlite3_column_text(stmt, 3));
	r->piece = strdup(sqlite3_column_text(stmt, 4));
	r++;
	(*numrows)++;
    }
    sqlite3_finalize(stmt);
    rules = (rule *)realloc(rules, sizeof(rule) * *numrows);

    return rules;
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
