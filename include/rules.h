#ifndef __RULES_H
#define __RULES_H

#ifndef __MESSAGE_H
#include "message.h"
#endif

#ifndef __DEFS_H
#include "defs.h"
#endif

typedef struct _rule
{
  char *name;
  char *regex;
  char *mbox;
  char *peice;
  int order;
}
rule;

	/** a generic regex wrapper */
extern int regex (char *, char *);
	/** load the rules and set them */
extern int rule_init ();
	/** see which mbox this message belongs in */
extern char *rule_check (message *);
	/** destroy the rule set */
extern int rule_close ();
	/** create a new set of rules (overwriting the old ones) */
extern int rule_set(rule **);
	/** return a list of rules */
extern rule **rule_get();

#endif
