/*
 * interface to the single linked list object. Multiple instances are handled
 * by passing the pointer around as a void*.
 */

#ifndef __LL_H
#define __LL_H

/** creates a new empty linked list */
/*
 * @null@ 
 */
extern void *ll_newlist (void);

/** sets the 'current' node to the next one */
extern int ll_next (void *list);

/** sets the 'current' node to the head */
extern int ll_rewind (void *list);

/** appends a node to the end of this list */
extern int ll_addnode (void *list, char *line);

/** delete the current node, place pointer at next node
  * a->B->c->d    =>    a->C->d   (cap is current)  */
extern int ll_deletenode (void *list);

/** returns the line in the current node. does NOT change current. */
/*
 * @null@ 
 */
extern char *ll_showline (void *list);

/** purge the list, do this when you're done with the list */
extern int ll_clearlist (void *list);

/** returns GEMS_TRUE if the list has no elements, GEMS_FALSE if it does */
extern int ll_empty (void *list);

/** returns GEMS_TRUE if the current node is the last node of the list
 */
extern int ll_end (void *list);

/** append two lists. Damages lista. */
extern void *ll_append (void *lista, void *listb);


#endif
