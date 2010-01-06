
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
 * $Id: db.sqlite.c,v 1.3 2010/01/06 00:47:29 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		/* strcasecmp() */
#include <ctype.h>
#include <time.h>

#include "defs.h"
#include "message.h"
#include "db.h"
#include "rules.h"
#include "face.h"		/* for oops() */

int /* TODO */
db_init (char *host, char *db, char *user, char *pass) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
}

int
db_init_firstrun () {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
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
	oops(__FILE__,__FUNCTION__);
	exit(-1);
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

rule * /* TODO */
db_fetch_rules (int *numrows) {
	oops(__FILE__,__FUNCTION__);
	exit(-1);
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
