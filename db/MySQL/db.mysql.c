
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2003 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: db.mysql.c,v 1.28 2003/04/18 19:24:20 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		/* strcasecmp() */
#include <ctype.h>
#include <mysql/mysql.h>
#include "defs.h"
#include "message.h"
#include "db.h"
#include "rules.h"
#include "face.h"		/* for oops() */

MYSQL *con;

int isnormal = GEMS_FALSE;

static char q[40000000];

static char monthlist[12][4] =
    { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct",
    "nov", "dec"
};

static char *
stuff (MYSQL_RES * result, MYSQL_ROW row, int x, int box)
{
    static char stuff_box[10][1024 * 1024];
    char *a = stuff_box[box];

    if (result == NULL || row == NULL)
	return NULL;
    /*
     * a = (char *) malloc (sizeof (char) *
     * (mysql_fetch_lengths (result)[x] + 1));
     */
    sprintf (a, "%s", row[x]);
    return a;
}

int
db_init (char *host, char *db, char *user, char *pass)
{
    con = (MYSQL *) malloc (sizeof (MYSQL));
    if (!mysql_connect (con, host, user, pass))
	return GEMS_FALSE;
    if (mysql_select_db (con, db) != 0)
	return GEMS_FALSE;
    return GEMS_TRUE;
}

static char spawnbuf[4][1024 * 1024];
float timeinspawn_escape_string = 0;

static char *
spawn_escape_string (char *in, int buf)
{
    char *x = spawnbuf[buf];

    memset (x, 0, 1024 * 1024 - 1);
    if (in == NULL)
	return NULL;

/*    x = (char *) malloc (2 * strlen (in) + 1);*/
    mysql_escape_string (x, in, strlen (in));
    return x;
}

static char *
parse_date (char *in)
{
    static char a[24], mo[4];
    int year, month, day, hour, minute, second, x;

    a[0] = year = month = day = hour = minute = second = 0;

    if (in == NULL)
	return a;
    if (isalpha (in[0]))
	in += 5;

    sscanf (in, "%d %s %d %d:%d:%d", &day, mo, &year, &hour, &minute,
	    &second);

    for (x = 0; x < 12; x++)
	if (strcasecmp (monthlist[x], mo) == 0)
	    month = x + 1;

/*    a = (char *) malloc (24);*/

    sprintf (a, "%04d-%02d-%02d %02d:%02d:%02d",
	     year, month, day, hour, minute, second);

    return a;
}

int
db_insert_msg (char *mboxname, message * m)
{
    long int id, mbox = 0, x, count;
    char *a, *b, *c, *d;
    MYSQL_RES *result;
    MYSQL_ROW row;

    if (m == NULL)
      {
	  printf ("\nNull message!\n");
	  return GEMS_FALSE;
      }

    /*
     * check if it's a redundant entry
     */
    sprintf (q, "select * from synopsis where charid='%s'", m->id);
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to check for dup", NULL);
	  exit (0);
      }
    result = mysql_store_result (con);
    row = mysql_fetch_row (result);
    if (row != NULL)
      {
	  mysql_free_result (result);
	  return GEMS_TRUE;
      }
    mysql_free_result (result);

    /* 01 this can be table-ized or fixed in the db... */
    sprintf (q, "select mbox from mmbox where mboxname='%s'", mboxname);
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to retreive mbox", NULL);
	  exit (0);
      }
    result = mysql_store_result (con);
    row = mysql_fetch_row (result);
    mbox = atoi (row[0]);
    mysql_free_result (result);
    /* /01 */

    /*
     * count = (row == NULL ? 0 : atoi (row[0]));
     * mysql_free_result (result);
     * if (count != 0)
     * return GEMS_TRUE;
     */
    /*
     * for(x=0;x<count;x++) { }
     * 
     * for each simharid if body matches return GEMS_TRUE;
     */

    if (m->header == NULL)
	oops ("NULL header", NULL);
    a = spawn_escape_string (m->header, 0);
    sprintf (q, "insert into header values (0,'%s','false')", a);

/*    free (a);*/
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to insert header", NULL);
	  exit (0);
      }
    mysql_query (con, "select last_insert_id()");
    result = mysql_store_result (con);
    row = mysql_fetch_row (result);
    id = atoi (row[0]);
    mysql_free_result (result);

    if (m->body == NULL)
	oops ("NULL body", NULL);
    a = spawn_escape_string (m->body, 0);
    sprintf (q, "insert into body values (%ld,'%s','false')", id, a);

/*    free (a);*/
    if (mysql_query (con, q) != 0)
      {

/*	FILE *dump;*/

	  oops ("failed to insert body", NULL);
	  /*
	   * dump = fopen ("dump", "a");
	   * fprintf (dump, "%s\n%s\n", m->header, m->body);
	   * fclose (dump);
	   */
      }
    if (m->sender == NULL)
	oops ("NULL sender", NULL);
    if (m->subject == NULL)
	oops ("NULL subject", NULL);
    if (m->senddate == NULL)
	oops ("NULL senddate", NULL);
    a = spawn_escape_string (m->sender, 0);
    b = spawn_escape_string (m->subject, 1);
    c = parse_date (m->senddate);
    d = spawn_escape_string (m->id, 2);
    sprintf (q,
	     "insert into synopsis values (%ld,%ld,'','%s','%s','%s','%s')",
	     id, mbox, c, a, b, d);

/*
    free (a);
    free (b);
    free (c);
    free (d);
*/
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to insert synopsis", mysql_error (con));
	  exit (0);
      }
    if (m->recipt == NULL)
	oops ("NULL recipt", NULL);
#if 0
    a = spawn_escape_string (m->recipt, 0);
    sprintf (q, "insert into recipt values (%ld,'%s','to')", id, a);

/*    free (a);*/
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to insert recipt", NULL);
	  exit (0);
      }
    if (m->replyto == NULL)
	oops ("NULL replyto", NULL);
    a = spawn_escape_string (m->replyto, 0);
    sprintf (q, "insert into replyto values (%ld,'%s')", id, a);

/*    free (a);*/
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to insert replyto", mysql_error (con));
	  exit (0);
      }
    if (m->references != NULL)
      {
	  a = spawn_escape_string (m->references, 0);
	  sprintf (q, "insert into refs values (%ld,'%s',NULL)", id, a);

/*	free (a);*/
	  if (mysql_query (con, q) != 0)
	    {
		oops ("failed to insert refs", mysql_error (con));
		exit (0);
	    }
      }
#endif
    isnormal = GEMS_FALSE;
    return GEMS_TRUE;
}

int
db_addmbox (char *mbox)
{
    int rval;

    sprintf (q, "insert into mmbox values (0,'%s')", mbox);
    if (mysql_query (con, q) != 0)
	rval = GEMS_FALSE;
    else
	rval = GEMS_TRUE;
    return rval;
}

int
db_dropmbox (char *mbox)
{
    int x, r = GEMS_FALSE;
    MYSQL_RES *result;
    MYSQL_ROW row;

    sprintf (q, "select mbox from mmbox where mboxname='%s'", mbox);
    if (mysql_query (con, q) == 0)
      {
	  result = mysql_store_result (con);
	  row = mysql_fetch_row (result);
	  x = atoi (row[0]);
	  sprintf (q, "update synopsis set mbox=3 where mbox=%d", x);
	  mysql_query (con, q);
	  sprintf (q, "delete from mmbox where mbox=%d", x);
	  mysql_query (con, q);
	  r = GEMS_TRUE;
      }
    return r;
}

int
db_flush (char *table)
{
    int rval;

    if (table == NULL)
	return GEMS_FALSE;
    sprintf (q, "delete from %s", table);
    if (mysql_query (con, q) != 0)
	rval = GEMS_FALSE;
    else
	rval = GEMS_TRUE;
    return rval;
}

int
db_close ()
{
    mysql_close (con);
    free (con);
    return GEMS_TRUE;
}

synopsis **
db_read_synopsis (int mbox, int status)
{
    synopsis **synops;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int x, numrows;

    switch (status)
      {
      case DB_READ:
	  sprintf (q,
		   "select id,sender,senddate,subject from synopsis where mbox=%d and status='read' order by senddate",
		   mbox);
	  break;
      case DB_MARKED:
	  sprintf (q,
		   "select id,sender,senddate,subject from synopsis where mbox=%d and status='marked' order by senddate",
		   mbox);
	  break;
      case DB_ALL:
	  sprintf (q,
		   "select id,sender,senddate,subject from synopsis where mbox=%d order by senddate",
		   mbox);
	  break;
      case DB_UNREAD:
	  sprintf (q,
		   "select id,sender,senddate,subject from synopsis where mbox=%d and status!='read' order by senddate",
		   mbox);
	  break;
      default:
	  oops ("Invalid action specified", "Cannot retreive synopsis");
	  break;
      }
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to read synopsis list", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);

    numrows = mysql_num_rows (result);
    synops = (void *) malloc (sizeof (synopsis *) * (numrows + 1));

    for (x = 0; x < numrows; x++)
      {
	  row = mysql_fetch_row (result);
	  synops[x] = (synopsis *) malloc (sizeof (synopsis));

	  synops[x]->id = atoi (row[0]);

	  synops[x]->sender = (char *) malloc (strlen (row[1]) + 1);
	  strcpy (synops[x]->sender, row[1]);

	  synops[x]->date = (char *) malloc (strlen (row[2]) + 1);
	  strcpy (synops[x]->date, row[2]);

	  synops[x]->subject = (char *) malloc (strlen (row[3]) + 1);
	  strcpy (synops[x]->subject, row[3]);
      }
    synops[x] = NULL;		/* to know when to stop inserting... */

    mysql_free_result (result);
    return synops;
}


mboxs **
db_read_mboxlist (void)
{
    int x, y, realcount, mboxcount;
    mboxs **mboxlist, **mboxlistf;
    MYSQL_RES *result;
    MYSQL_ROW row;

    if (mysql_query (con, "select max(mbox) from mmbox") != 0)
      {
	  oops ("failed to read mailbox list", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);
    row = mysql_fetch_row (result);
    realcount = mboxcount = atoi (row[0]);
    mysql_free_result (result);
    mboxlist = (mboxs **) malloc (sizeof (mboxs *) * (mboxcount + 1));
    memset (mboxlist, 0, sizeof (mboxs *) * (mboxcount + 1));
    mboxlistf = (mboxs **) malloc (sizeof (mboxs *) * (mboxcount + 1));
    memset (mboxlistf, 0, sizeof (mboxs *) * (mboxcount + 1));

    if (mysql_query (con, "select mboxname,mbox from mmbox order by mbox") !=
	0)
      {
	  oops ("failed to read mailbox list", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);

    for (x = 0; (row = mysql_fetch_row (result)) != NULL; x++)
      {
	  int y = atoi (row[1]) - 1;

	  mboxlist[y] = (mboxs *) malloc (sizeof (mboxs));
	  if (mboxlist[y] == NULL)
	    {
		oops ("malloc failed building mbox's", mboxlist[y]->name);
		exit (-1);
	    }
	  if (row[0] == NULL)
	    {
		oops ("NULL row", NULL);
		exit (-1);
	    }
	  mboxlist[y]->name = strdup (row[0]);
	  mboxlist[y]->id = atoi (row[1]);
	  mboxlist[y]->hasunread = 0;
      }
    mysql_free_result (result);
    if (mysql_query
	(con,
	 "select mbox,count(*) from synopsis where status!='read' group by mbox")
	!= 0)
      {
	  oops ("failed to count unread messages", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);
    mboxcount = mysql_num_rows (result);

    while ((row = mysql_fetch_row (result)) != NULL)
      {
	  y = atoi (row[0]) - 1;

	  if (mboxlist[y] != NULL)
	      mboxlist[y]->hasunread = atoi (row[1]);
      }
    mysql_free_result (result);

    /*
     * crunch 
     */
    x = 0;
    y = 0;
    while (x <= realcount)
      {
	  if (mboxlist[x])
	      mboxlistf[y++] = mboxlist[x];
	  x++;
      }
    free (mboxlist);

    return mboxlistf;
}

char *
db_read_body (int id)
{
    char *body;
    MYSQL_RES *result;
    MYSQL_ROW row;

    sprintf (q, "select body from body where id='%d'", id);
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to read mail body", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);

    if (result == NULL)
      {
	  oops ("mysql_store_result failed", NULL);
	  exit (EXIT_FAILURE);
      }
    row = mysql_fetch_row (result);
    body = stuff (result, row, 0, 0);
    mysql_free_result (result);

    sprintf (q, "update synopsis set status = 'read' where id='%d'", id);
    if (mysql_query (con, q) != 0)
	oops ("Failed to set mail as read", mysql_error (con));

    return body;
}

message *			/* TODO */
db_read_message (int id)
{
    message *m;
    MYSQL_RES *result;
    MYSQL_ROW row;

    m = (message *) malloc (sizeof (message));

    m->attachments = NULL;

    /*
     * body
     */
    sprintf (q, "select body from body where id='%d'", id);
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to read mail body", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);
    if (result == NULL)
      {
	  oops ("mysql_store_result failed", NULL);
	  exit (EXIT_FAILURE);
      }
    row = mysql_fetch_row (result);
    m->body = (char *) malloc (*mysql_fetch_lengths (result) + 1);
    sprintf (m->body, "%s", row[0]);
    mysql_free_result (result);

    /*
     * header
     */
    sprintf (q, "select header from header where id='%d'", id);
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to read mail header", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);
    if (result == NULL)
      {
	  oops ("mysql_store_result failed", NULL);
	  exit (EXIT_FAILURE);
      }
    row = mysql_fetch_row (result);
    m->header = (char *) malloc (*mysql_fetch_lengths (result) + 1);
    sprintf (m->header, "%s", row[0]);
    mysql_free_result (result);

    /*
     * synopsis (mbox, status, senddate, sender, subject, charid)
     */
    sprintf (q,
	     "select mbox,status,senddate,sender,subject,charid from synopsis where id='%d'",
	     id);
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to read mail synopsis", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);
    if (result == NULL)
      {
	  oops ("mysql_store_result failed", NULL);
	  exit (EXIT_FAILURE);
      }
    row = mysql_fetch_row (result);
    m->mbox = stuff (result, row, 0, 0);
    m->status = stuff (result, row, 1, 1);
    m->senddate = stuff (result, row, 2, 2);
    m->sender = stuff (result, row, 3, 3);
    m->subject = stuff (result, row, 4, 4);
    m->id = stuff (result, row, 5, 5);
    mysql_free_result (result);

    /*
     * recipt
     */
    sprintf (q, "select recipt from recipt where id='%d'", id);
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to read mail recipt", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);
    if (result == NULL)
      {
	  oops ("mysql_store_result failed", NULL);
	  exit (EXIT_FAILURE);
      }
    row = mysql_fetch_row (result);
    m->recipt = (char *) malloc (*mysql_fetch_lengths (result) + 1);
    sprintf (m->recipt, "%s", row[0]);
    mysql_free_result (result);

    /*
     * refs
     */
    sprintf (q, "select refs from refs where id='%d'", id);
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to read mail refs", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);
    if (result == NULL)
      {
	  oops ("mysql_store_result failed", NULL);
	  exit (EXIT_FAILURE);
      }
    row = mysql_fetch_row (result);
    m->references = stuff (result, row, 0, 6);
    mysql_free_result (result);

    /*
     * replyto
     */
    sprintf (q, "select replyto from replyto where id='%d'", id);
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to read mail replyto", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);
    if (result == NULL)
      {
	  oops ("mysql_store_result failed", NULL);
	  exit (EXIT_FAILURE);
      }
    row = mysql_fetch_row (result);
    m->replyto = (char *) malloc (*mysql_fetch_lengths (result) + 1);
    sprintf (m->replyto, "%s", row[0]);
    mysql_free_result (result);

    m->recvdate = NULL;

    sprintf (q, "update synopsis set status='read' where id='%d'", id);
    if (mysql_query (con, q) != 0)
	oops ("Failed to set mail as read", mysql_error (con));

    return m;
}

int				/* TODO */
db_normalize ()
{
    MYSQL_RES *r, *ir;
    MYSQL_ROW row, irow;

    if (mysql_query
	(con,
	 "select refs from refs where childof is NULL and refs is not NULL")
	!= 0)
      {
	  oops ("normalization failed", NULL);
	  exit (0);
      }
    r = mysql_store_result (con);
    if (r == NULL)
      {
	  oops ("db is already normal", NULL);
	  return GEMS_TRUE;
      }
    while ((row = mysql_fetch_row (r)) != NULL)
      {
	  char *blah;

	  blah = spawn_escape_string (row[0], 0);
	  sprintf (q, "select id from synopsis where charid='%s'", blah);

/*	free (blah);*/
	  if (mysql_query (con, q) != 0)
	    {
		oops ("couldn't grok the id during normalization", row[0]);

		/*
		 * exit (-1);
		 */
	    }
	  else
	    {
		ir = mysql_store_result (con);
		while ((irow = mysql_fetch_row (ir)) != NULL)
		  {
		      sprintf (q,
			       "update refs set childof=%s where refs='%s'",
			       irow[0], row[0]);
		      mysql_query (con, q);
		  }
	    }
      }

    isnormal = GEMS_TRUE;
    return GEMS_TRUE;
}

int				/* returns 0 if no parent */
db_is_child_of (int msg)
{
    int parent = 0;
    MYSQL_RES *result;
    MYSQL_ROW row;

    if (isnormal == GEMS_FALSE)
	db_normalize ();
    sprintf (q, "select child from refs where id='%d'", msg);
    if (mysql_query (con, q) != 0)
      {
	  oops ("failed to read child_of", mysql_error (con));
	  exit (0);
      }
    result = mysql_store_result (con);

    if (result == NULL)
      {
	  oops ("mysql_store_result failed", "");
	  exit (-1);
      }
    row = mysql_fetch_row (result);
    if (row[0] != NULL)
	parent = atoi (row[0]);
    mysql_free_result (result);
    return parent;
}

rule *
db_fetch_rules (int *numrows)
{
    int x, nr;
    MYSQL_RES *result;
    MYSQL_ROW row;
    rule *r;

    if (mysql_query (con,
		     "select name,sort,regex,mbox,peice from rules order by sort")
	!= 0)
      {
	  oops ("failed to read rule set\n", "");
	  exit (0);
      }
    result = mysql_store_result (con);
    nr = mysql_num_rows (result);
    if (result == NULL)
      {
	  oops ("ruleset failed on result\n", "");
	  exit (-1);
      }
    r = (rule *) malloc (sizeof (rule) * (nr + 1));
    for (x = 0; x < nr; x++)
      {
	  row = mysql_fetch_row (result);
	  r[x].name = (char *) malloc (strlen (row[0]) + 1);
	  sprintf (r[x].name, row[0]);
	  r[x].order = atoi (row[1]);
	  r[x].regex = (char *) malloc (strlen (row[2]) + 1);
	  sprintf (r[x].regex, row[2]);
	  r[x].mbox = (char *) malloc (strlen (row[3]) + 1);
	  sprintf (r[x].mbox, row[3]);
	  r[x].peice = (char *) malloc (strlen (row[4]) + 1);
	  sprintf (r[x].peice, row[4]);
      }
    *numrows = nr;
    return r;
}

int
db_set_rules (rule ** rulelist)
{
    int x;
    int rval = GEMS_TRUE;

    mysql_query (con, "delete from rules");	/* delete all the rules */
    x = 0;
    while (rulelist[x] != NULL)
      {
	  sprintf (q, "insert into rules values (%d,'%s','%s','%s','%s')", x,
		   rulelist[x]->name, rulelist[x]->regex, rulelist[x]->mbox,
		   rulelist[x]->peice);
	  if (mysql_query (con, q) != 0)
	      rval = GEMS_FALSE;
	  x++;
      }
    return rval;
}

int
db_pref_set (char *pref, char *val)
{
    int x;

    sprintf (q, "delete from preferences where name='%s'", pref);
    mysql_query (con, q);
    sprintf (q, "insert into preferences values ('%s','%s')", pref, val);
    x = mysql_query (con, q);
    if (x != 0)
	return GEMS_FALSE;
    return GEMS_TRUE;
}

char *
db_pref_get (char *pref)
{
    char *a;
    MYSQL_RES *res;
    MYSQL_ROW row;

    sprintf (q, "select value from preferences where name='%s'", pref);
    if (mysql_query (con, q) != 0)
      {
	  return NULL;
      }
    res = mysql_store_result (con);
    row = mysql_fetch_row (res);
    if (row != NULL && row[0] != NULL)
      {
	  a = (char *) malloc (strlen (row[0]) + 1);
	  strcpy (a, row[0]);
      }
    mysql_free_result (res);
    return a;
}

unsigned int
hash (char *str)
{
    char *x = str;
    int i = 0;

    while (*x)
	i += *x++;
    return i;
}

void
db_syncharhash (void)
{
    MYSQL_RES *res1, *res2;
    MYSQL_ROW row1, row2;
    int i = 1, max = 0;
    int start, now, t;

    if (mysql_query (con, "select id,charid from synopsis") != 0)
      {
	  oops ("MySQL::db_syncharhash", "Failed");
	  return;
      }
    res1 = mysql_store_result (con);
    max = mysql_num_rows (res1);
    start = time (NULL);
    while ((row1 = mysql_fetch_row (res1)) != NULL)
      {
	  static float frac;

	  now = time (NULL);
	  sprintf (q, "select * from charid_hash where id=%s", row1[0]);
	  mysql_query (con, q);
	  res2 = mysql_store_result (con);
	  row2 = mysql_fetch_row (res2);
	  frac = (float) i / (float) max;
	  t = start + max * (now - start) / i;
	  printf ("\r%d/%d (%.2f%%) %ds elapsed, ~%d left, ETA: %s", i, max, 100.0 * frac, now - start, /* elapsed */ (float) max * (float) (now - start) / (float) i, /* left */ ctime (&t));	/* ETA */
	  ++i;
	  fflush (stdout);
	  if (row2 == NULL)
	    {
		sprintf (q, "insert into charid_hash values(%d,%s)",
			 hash (row1[1]), row1[0]);
		mysql_query (con, q);
	    }
      }
}
