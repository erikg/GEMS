
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
 * $Id: rules.c,v 1.24 2010/01/06 00:47:29 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

#include "rules.h"
#include "message.h"
#include "db.h"

static char inbox[] = "inbox";

static rule *rules;
static int numrules = 0;

static regex_t *preg;

int
rule_init (rule * r, int nr)
{
    int x;

    numrules = nr;
    if(nr == 0 || r == NULL)
	return GEMS_FALSE;
    rules = (rule *) r;
    preg = (void *)malloc (sizeof (regex_t) * (numrules + 1));
    memset (preg, 0, sizeof (regex_t) * (numrules + 1));
    for (x = 0; x < numrules; x++)
	regcomp (&preg[x], rules[x].regex,
	    REG_EXTENDED | REG_ICASE | REG_NOSUB);
    return GEMS_TRUE;
}

static char *
rule_concern (rule * r, message * m)
{
    char *c;

    c = r->peice;

    if (!strcmp (c, "Body"))
	return m->body;
    if (!strcmp (c, "Header"))
	return m->header;
    if (!strcmp (c, "Recipients"))
	return m->recipt;
    if (!strcmp (c, "Sender"))
	return m->sender;
    if (!strcmp (c, "Subject"))
	return m->subject;
    if (!strcmp (c, "Message"))	/* fix this */
	return m->header;
    if (!strcmp (c, "From"))
	return m->sender;
    printf ("No peice!!@~!@~!@!@\n");
    return NULL;
}

char *
rule_check (message * m)
{
    int x;
    char *c;			/* the section of the email we care about */

    if (m == NULL)
	return inbox;
    for (x = 0; x < numrules; x++)
    {
	c = rule_concern (&rules[x], m);
	if (c)
	    if (regexec (&preg[x], c, 0, NULL, 0) == 0)
		return rules[x].mbox;
    }
    return inbox;
}

int
rule_close ()
{
    int x;

    for (x = 0; x < numrules; x++)
    {
	regfree (&preg[x]);
	free (rules[x].regex);
	free (rules[x].mbox);
    }
    free (preg);
    free (rules);
    return GEMS_TRUE;
}

rule **
rule_get ()
{
    return NULL;
}

int
rule_set (rule ** r)
{
    fprintf(stderr, "Unimplemnted function: %s(%x) (%s:%d)\n", __FUNCTION__, (unsigned int)r, __FILE__, __LINE__);
    return GEMS_FALSE;
}
