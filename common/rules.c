#include "rules.h"
#include "message.h"
#include "db.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

char *inbox;

rule *rules;
int numrules;

regex_t **preg;

regmatch_t *pmatch;

int
rule_init ()
{
  int x;
  inbox = (char *) malloc (sizeof ("inbox") + sizeof (char));
  
  sprintf (inbox, "inbox");
  rules = (rule *) db_fetch_rules ((int *) &numrules);
  preg = (void *) malloc (sizeof (void *) * (numrules + 1));
  for (x = 0; x < numrules; x++)
    {
      preg[x] = (regex_t *) malloc (sizeof (regex_t));
      regcomp (preg[x], rules[x].regex, REG_EXTENDED);
    }
  pmatch = (regmatch_t *) malloc (65535 * sizeof (regmatch_t));
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
  fflush (0);
  return NULL;
}

char *
rule_check (message * m)
{
  int x;
  char *c;			/* the section of the email we care about */
  for (x = 0; x < numrules; x++)
    {
      c = rule_concern (&rules[x], m);
      if (regexec (preg[x], c, 0, pmatch, REG_NOSUB) == 0)
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
      regfree (preg[x]);
      free (preg[x]);
      free (rules[x].regex);
      free (rules[x].mbox);
    }
  free (preg);
  free (rules);
  free (inbox);
  free (pmatch);
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
  return GEMS_FALSE;
}
