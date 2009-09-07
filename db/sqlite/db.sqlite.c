
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2009 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: db.sqlite.c,v 1.1 2009/09/07 16:56:35 erik Exp $
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

int
db_init (char *host, char *db, char *user, char *pass) {
}

int
db_init_firstrun () {
}

int
db_insert_msg (char *mboxname, message * m) {
}

int
db_addmbox (char *mbox) {
}

int
db_addmbox_view (char *mbox, char *query) {
}

int
db_dropmbox (char *mbox) {
}

int
db_flush (char *table) {
}

int
db_close () {
}

synopsis **
db_read_synopsis_raw (char *query) {
}

synopsis **
db_read_synopsis (int mbox, int status) {
}

mboxs **
db_read_mboxlist (void) {
}

char *
db_read_body (int id) {
}

message *
db_read_message (int id) {
}

int
db_normalize () {
}

int
db_is_child_of (int msg) {
}

rule *
db_fetch_rules (int *numrows) {
}

int
db_set_rules (rule ** rulelist) {
}

int
db_pref_set (char *pref, char *val) {
}

char *
db_pref_get (char *pref) {
}

void
db_syncharhash (void) {
}

void
db_purge_empty () {
}
