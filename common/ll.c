#include <stdio.h>		/* for NULL */
#include <stdlib.h>
#include "defs.h"
#include "ll.h"
#include "../include/face.h"	/* for oops() */


/*
 * singly linked list 
 */
typedef struct anode
{
    char *line;
    struct anode *next;
}
node;

typedef struct alist
{
    node *head;
    node *current;
    node *last;
}
list;


/*
 * @null@ 
 */
void *
ll_newlist ()
{
    list *x;

    x = (list *) malloc (sizeof (list));
    if (x != NULL)
      {
	  x->head = NULL;
	  x->current = NULL;
	  x->last = NULL;
	  return x;
      }
    oops ("Failed to gnerate new list", NULL);
    return NULL;
}

int
ll_next (void *this)
{
    list *x;

    x = (list *) this;
    if (x == NULL || x->current == NULL || x->current->next == NULL)
	return GEMS_FALSE;
    x->current = x->current->next;
    return GEMS_TRUE;
}

int
ll_rewind (void *this)
{
    list *x;

    if (this == NULL)
	return GEMS_FALSE;
    x = (list *) this;
    x->current = x->head;
    return GEMS_TRUE;
}

int				/* this is a major bottleneck (50% of * * *
				 * spool2sql is here) */
ll_addnode (void *this, char *line)
{
    node *x;
    list *l;

    if (this == NULL || line == NULL)	/* bad list */
	return GEMS_FALSE;

    x = (node *) malloc (sizeof (node));
    if (x == NULL)
	return GEMS_FALSE;

    x->line = (char *) malloc (sizeof (char) * (strlen (line) + 1));
    if (x->line == NULL)
	return GEMS_FALSE;	/* no malloc */

    strcpy (x->line, line);
    x->next = NULL;

    l = (list *) this;

    if (l->head == NULL)
	l->head = l->current = l->last = x;
    else
      {
	  l->last->next = x;
	  l->last = x;
      }

    return GEMS_TRUE;
}

char *
ll_showline (void *this)
{
    list *l;

    l = (list *) this;
    if (l == NULL || l->current == NULL || l->current->line == NULL)
	return NULL;
    return l->current->line;
}

static void
rec_clearlist (node * this)
{
    if (this == NULL)
	return;
    if (this->next != NULL)
	rec_clearlist (this->next);
    free (this->line);
    free (this);
    return;
}


int
ll_clearlist (void *this)
{
    /*
     * node *x, *y; 
     */
    if (this == NULL || ((list *) this)->head == NULL)
	return GEMS_FALSE;

    /*
     * x = ((list *) this)->head; while (x->next != NULL) { y = x->next; if
     * (x->line != NULL) free (x->line); free (x); x = y; }
     */
    rec_clearlist (((list *) this)->head);
    free (this);
    return GEMS_TRUE;
}

int
ll_empty (void *v)
{
    list *l;

    l = (list *) v;
    if (l == NULL || l->head == NULL)
	return GEMS_TRUE;
    return GEMS_FALSE;
}

int
ll_deletenode (void *v)
{
    list *l;
    node *n, *t;

    l = (list *) v;
    if (l == NULL || l->head == NULL)
	return GEMS_FALSE;
    n = l->head;

    while (n->next != NULL && n->next != l->current)
	n = n->next;

    if (n->next == NULL)
	return GEMS_FALSE;

    t = n->next;
    n->next = t->next;
    free (t);
    l->current = n->next;

    return GEMS_TRUE;
}

int
ll_end (void *n)
{
    list *l;

    l = (list *) n;
    if (l->current == NULL)
	return GEMS_TRUE;
    return GEMS_FALSE;
}

void *
ll_append (void *lista, void *listb)
{
    if (lista == NULL)
	return listb;
    if (listb == NULL)
	return lista;
    ((list *) lista)->last->next = ((list *) listb)->head;
    return lista;
}
