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
 * $Id: db.sqlite.c,v 1.9 2011/01/05 20:40:25 erik Exp $
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
#define MBUFSIZ 1024*1024

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
    char buf[MBUFSIZ], *err;
    sqlite3_stmt *stmt;
    const char **results = NULL, **colnames = NULL, **pzTail = NULL;
    int mbox;
    sqlite3_int64 rowid;

    if(m->body == NULL) {
	printf("Got a null body!\n");
	printf("%s\n", m->header);
	return GEMS_FALSE;
    }

    snprintf(buf, MBUFSIZ, "select mbox from mmbox where mboxname=\"%s\";", mboxname);
    if(sqlite3_prepare_v2(sqldb, buf, strlen(buf)+1, &stmt, pzTail) != SQLITE_OK) {
	oops("Unable to get mbox", sqlite3_errmsg(sqldb));
	return GEMS_FALSE;
    }
    sqlite3_step(stmt);
    mbox = sqlite3_column_int(stmt,0);
    sqlite3_finalize(stmt);

    if(sqlite3_exec(sqldb, "BEGIN TRANSACTION;", NULL, NULL, &err) != SQLITE_OK) {
	oops("transaction wasn't able to start", sqlite3_errmsg(sqldb));
	return GEMS_FALSE;
    }

    sqlite3_snprintf(MBUFSIZ, buf, "insert into synopsis (id,mbox,status,sender,subject,senddate,charid) values(NULL,%d,'unread',%Q,%Q,%Q,%Q);", mbox, m->sender, m->subject, m->senddate, m->id);
    if(sqlite3_exec(sqldb, buf, NULL, NULL, &err) != SQLITE_OK) {
	oops("failed insert synopsis", sqlite3_errmsg(sqldb));
	sqlite3_exec(sqldb, "ROLLBACK;", NULL, NULL, &err);
	return GEMS_FALSE;
    }

    rowid = sqlite3_last_insert_rowid(sqldb);

    sqlite3_snprintf(MBUFSIZ, buf, "insert into body values(%d,%Q,'false');", (int)rowid, m->body);
    if(sqlite3_exec(sqldb, buf, NULL, NULL, &err) != SQLITE_OK) {
	oops("failed insert body", sqlite3_errmsg(sqldb));
	sqlite3_exec(sqldb, "ROLLBACK;", NULL, NULL, &err);
	return GEMS_FALSE;
    }

    sqlite3_snprintf(MBUFSIZ, buf, "insert into header values(%d,%Q,'false');", (int)rowid, m->header);
    if(sqlite3_exec(sqldb, buf, NULL, NULL, &err) != SQLITE_OK) {
	oops("failed insert header", sqlite3_errmsg(sqldb));
	sqlite3_exec(sqldb, "ROLLBACK;", NULL, NULL, &err);
	return GEMS_FALSE;
    }

    if(sqlite3_exec(sqldb, "COMMIT;", NULL, NULL, &err) != SQLITE_OK) {
	oops("transaction wasn't able to commit", sqlite3_errmsg(sqldb));
	return GEMS_FALSE;
    }
    return GEMS_TRUE;
}

int
db_flush (char *table) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int
db_addmbox (char *mbox) {
    char buf[BUFSIZ], *err;
    snprintf(buf, BUFSIZ, "insert into mmbox values(NULL, \"%s\", NULL);", mbox);
    if(sqlite3_exec(sqldb, buf, NULL, NULL, &err) != SQLITE_OK) {
	oops("Failed to add mbox", sqlite3_errmsg(sqldb));
	return GEMS_FALSE;
    }
    return GEMS_TRUE;
}

int /* TODO */
db_addmbox_view (char *mbox, char *query) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int
db_dropmbox (char *mbox) {
    char buf[BUFSIZ], *err;
    snprintf(buf, BUFSIZ, "delete from mmbox where mbox=\"%s\";", mbox);
    if(sqlite3_exec(sqldb, buf, NULL, NULL, &err) != SQLITE_OK) {
	oops("Failed to add mbox", sqlite3_errmsg(sqldb));
	return GEMS_FALSE;
    }
    return GEMS_TRUE;
}

int
db_close () {
    if(sqlite3_close(sqldb) != SQLITE_OK) {
	oops("Closing db: ", sqlite3_errmsg(sqldb));
	return GEMS_FALSE;
    }
    return GEMS_TRUE;
}

synopsis **
db_read_synopsis (int mbox, int status) {
    char buf[BUFSIZ], *stat;
    const char **pzTail = NULL;
    sqlite3_stmt *stmt = NULL;
    int i = 0, rval;
    synopsis **syn;
    
    switch(status) {
	case DB_ALL: snprintf(buf, BUFSIZ, "select count(*) from synopsis where mbox=%d;", mbox); break;
	case DB_MARKED: snprintf(buf, BUFSIZ, "select count(*) from synopsis where mbox=%d and status='marked';", mbox); break;
	case DB_READ: snprintf(buf, BUFSIZ, "select count(*) from synopsis where mbox=%d and status='read';", mbox); break;
	case DB_UNREAD: snprintf(buf, BUFSIZ, "select count(*) from synopsis where mbox=%d and status!='read';", mbox); break;
	default: return NULL;
    }
    if((rval = sqlite3_prepare_v2(sqldb, buf, strlen(buf)+1, &stmt, pzTail)) != SQLITE_OK) {
	oops("Problem generating statement to fetch synopsis count", sqlite3_errmsg(sqldb));
	return NULL;
    }
    sqlite3_step(stmt);
    i = sqlite3_column_int(stmt,0);
    sqlite3_finalize(stmt);
    if(i==0) 
	return NULL;
    syn = (synopsis **)malloc(sizeof(synopsis *)*(i+1));
    stmt = NULL;
    pzTail = NULL;
    

    switch(status) {
	case DB_ALL: snprintf(buf, BUFSIZ, "select id,sender,senddate,subject from synopsis where mbox=%d;", mbox); break;
	case DB_MARKED: snprintf(buf, BUFSIZ, "select id,sender,senddate,subject from synopsis where mbox=%d and status='marked';", mbox); break;
	case DB_READ: snprintf(buf, BUFSIZ, "select id,sender,senddate,subject from synopsis where mbox=%d and status='read';", mbox); break;
	case DB_UNREAD: snprintf(buf, BUFSIZ, "select id,sender,senddate,subject from synopsis where mbox=%d and status!='read';", mbox); break;
	default: return NULL;
    };
    
    if((rval = sqlite3_prepare_v2(sqldb, buf, strlen(buf)+1, &stmt, pzTail)) != SQLITE_OK) {
	oops("Problem generating statement to fetch synopsis", sqlite3_errmsg(sqldb));
	return NULL;
    }
    i=0;
    while((rval=sqlite3_step(stmt)) != SQLITE_DONE) {
	syn[i] = (synopsis *)malloc(sizeof(synopsis));
	syn[i]->id = sqlite3_column_int(stmt, 0);
	syn[i]->sender = strdup(sqlite3_column_text(stmt, 1));
	syn[i]->date = strdup(sqlite3_column_text(stmt, 2));
	syn[i]->subject = strdup(sqlite3_column_text(stmt, 3));
	i++;
    }
    sqlite3_finalize(stmt);
    syn[i] = NULL;
    return syn;
}

static int mboxlistcount = -1;
mboxs **
db_read_mboxlist (void) {
    sqlite3_stmt *stmt;
    const char **results = NULL, **colnames = NULL, **pzTail = NULL;
    rule *rules, *r;
    int rval, i;
    char buf[BUFSIZ];
    mboxs **mboxlist;

    if(mboxlistcount == -1) {
	snprintf(buf, BUFSIZ, "select count(*) from mmbox;");
	if(sqlite3_prepare_v2(sqldb, buf, strlen(buf)+1, &stmt, pzTail) != SQLITE_OK) {
	    oops("Problem generating statement to fetch mboxlist", sqlite3_errmsg(sqldb));
	    return NULL;
	}
	i=0;
	sqlite3_step(stmt);
	mboxlistcount = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	stmt = NULL;
	pzTail = NULL;
    }

    mboxlist = (mboxs **)malloc(sizeof(mboxs *) * (mboxlistcount+1));
    memset(mboxlist, 0, sizeof(mboxs *) * MAXRULES);
    snprintf(buf, BUFSIZ, "select mboxname,mbox from mmbox order by mbox;");
    if(sqlite3_prepare_v2(sqldb, buf, strlen(buf)+1, &stmt, pzTail) != SQLITE_OK) {
	oops("Problem generating statement to fetch mboxlist", sqlite3_errmsg(sqldb));
	return NULL;
    }
    i=0;
    while((rval=sqlite3_step(stmt)) != SQLITE_DONE) {
	mboxlist[i] = (mboxs *)malloc(sizeof(mboxs));
	mboxlist[i]->name = strdup(sqlite3_column_text(stmt, 0));
	mboxlist[i]->id = sqlite3_column_int(stmt, 1);
	mboxlist[i]->hasunread = 0;
	i++;
	mboxlist[i] = NULL;
    }
    sqlite3_finalize(stmt);
    mboxlist[i] = NULL;
    while(i--) {
	snprintf(buf, BUFSIZ, "select count(*) from synopsis where status='unread' and mbox=%d", mboxlist[i]->id);
	if(sqlite3_prepare_v2(sqldb, buf, strlen(buf)+1, &stmt, pzTail) != SQLITE_OK) {
	    oops("Problem getting unread count", sqlite3_errmsg(sqldb));
	    return NULL;
	}
	sqlite3_step(stmt);
	mboxlist[i]->hasunread = sqlite3_column_int(stmt,0);
	sqlite3_finalize(stmt);
    }

    return mboxlist;
}

char *	/* TODO */
db_read_body (int id) {
    char buf[BUFSIZ], *body = NULL, *err = NULL;
    const char **pzTail = NULL;
    sqlite3_stmt *stmt;

    snprintf(buf, BUFSIZ, "select body from body where id=%d;", id);
    if(sqlite3_prepare_v2(sqldb, buf, strlen(buf)+1, &stmt, pzTail) != SQLITE_OK) {
	oops("Problem getting unread count", sqlite3_errmsg(sqldb));
	return NULL;
    }
    sqlite3_step(stmt);
    body = strdup(sqlite3_column_text(stmt,0));
    sqlite3_finalize(stmt);
    snprintf(buf, BUFSIZ, "update synopsis set status='read' where id=%d", id);
    sqlite3_exec(sqldb, buf, NULL, NULL, &err);
    return body;
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
    sqlite3_stmt *stmt;
    const char **results = NULL, **colnames = NULL, **pzTail = NULL;
    char *buf = NULL;
    rule *rules, *r;
    int rval;
    const char stmt_str[] = "select name,sort,regex,mbox,piece from rules order by sort";

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
    char *ret, stmt_str[BUFSIZ];
    const char **pzTail = NULL;
    sqlite3_stmt *stmt;

    snprintf(stmt_str, BUFSIZ, "delete from preferences where name='%s';", pref);
    if(sqlite3_prepare_v2(sqldb, stmt_str, strlen(stmt_str)+1, &stmt, pzTail) != SQLITE_OK) {
	oops("Problem generating statement to purge pref", sqlite3_errmsg(sqldb));
	return GEMS_FALSE;
    }
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    pzTail = NULL;
    stmt = NULL;

    snprintf(stmt_str, BUFSIZ, "insert from preferences (name,value) values ('%s','%s');", pref, val);
    if(sqlite3_prepare_v2(sqldb, stmt_str, strlen(stmt_str)+1, &stmt, pzTail) != SQLITE_OK) {
	oops("Problem generating statement to set pref", sqlite3_errmsg(sqldb));
	return GEMS_FALSE;
    }
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return GEMS_TRUE;
}

char *
db_pref_get (char *pref) {
    char *ret, stmt_str[BUFSIZ];
    const char **pzTail = NULL;
    sqlite3_stmt *stmt;

    snprintf(stmt_str, BUFSIZ, "select value from preferences where name='%s';", pref);
    if(sqlite3_prepare_v2(sqldb, stmt_str, strlen(stmt_str)+1, &stmt, pzTail) != SQLITE_OK) {
	oops("Problem generating statement to fetch rules", sqlite3_errmsg(sqldb));
	return NULL;
    }
    sqlite3_step(stmt);
    ret = strdup(sqlite3_column_text(stmt,0));
    sqlite3_finalize(stmt);
    return ret;
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
