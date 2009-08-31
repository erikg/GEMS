
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
 * $Id: ll-block.c,v 1.8 2009/08/31 13:45:28 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "ll.h"

typedef struct _ll {
    int size;
    struct _ll *head;
    struct _ll *tail;
    struct _ll *current;
} ll;

void *
ll_newlist (void)
{
    void *x;
    ll *l;

    x = malloc (BUFSIZ);
    l = (ll *) malloc (sizeof (ll));
    if (x == NULL || l == NULL)
	return NULL;
    l->size = BUFSIZ;
    l->head = l->tail = l->current = x;
    memset (x, 0, BUFSIZ);
    return l;
}

int
ll_next (void *list)
{
    ll *x;

    x = (ll *) list;
    if (x != NULL && (int)(x->current) != 0)
    {
	x->current += (int)(x->current);
	return GEMS_TRUE;
    }
    return GEMS_FALSE;
}

int
ll_rewind (void *list)
{
    if (list == NULL)
	return GEMS_FALSE;
    ((ll *) list)->current = ((ll *) list)->head;
    return GEMS_TRUE;
}

int
ll_addnode (void *list, char *line)
{
    ll *x;
    int nodelen = strlen (line) + 5;	/* line + terminator + 'next' offset */

    if (list == NULL || line == NULL)
	return GEMS_FALSE;
    x = (ll *) list;
    while ((x->tail + nodelen) > (x->head + x->size))
    {
	int current_offset, tail_offset;

	current_offset = x->current - x->head;
	tail_offset = x->tail - x->head;
	x->head = realloc (x->head, x->size << 1);
	x->current = x->head + current_offset;
	x->tail = x->head + tail_offset;
	memset (x->head + x->size, 0, x->size);
	x->size = x->size << 1;
    }
    *(int *)(x->tail) = nodelen;
    strncpy (x->tail + 4, line, strlen (line));
}

int
ll_deletenode (void *list)
{
    int x;
    ll *l;

    if (list == NULL)
	return GEMS_FALSE;
    printf ("ll_deletenode: Not implemented...\n");
    return GEMS_FALSE;
}

char *
ll_showline (void *list)
{
    ll *l;

    if (list == NULL)
	return NULL;
    l = (ll *) list;
    return (char *)((int)(l->current) + 4);
}

int
ll_clearlist (void *list)
{
    ll *x;

    if (list == NULL)
	return GEMS_FALSE;
    x = (ll *) list;
    free (x->head);
    free (x);
    return GEMS_TRUE;
}

int
ll_empty (void *list)
{
    if ((int)(((ll *) list)->head) == 0)
	return GEMS_TRUE;
    return GEMS_FALSE;
}

int
ll_end (void *list)
{
    if ((int)(((ll *) list)->current) == 0)
	return GEMS_TRUE;
    return GEMS_FALSE;
}
