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
 * $Id: rules.h,v 1.10 2011/01/02 17:40:37 erik Exp $
 */

#ifndef __RULES_H
#define __RULES_H

#ifndef __MESSAGE_H
#include "message.h"
#endif

#ifndef __DEFS_H
#include "defs.h"
#endif

typedef struct _rule {
    char *name;
    char *regex;
    char *mbox;
    char *piece;
    int order;
} rule;

/** a generic regex wrapper */
int regex (char *, char *);

/** set the rules */
int rule_init (rule *r, int nr);

/** see which mbox this message belongs in */
char *rule_check (message *);

/** destroy the rule set */
int rule_close ();

/** create a new set of rules (overwriting the old ones) */
int rule_set (rule **);

/** return a list of rules */
rule **rule_get ();

#endif
