#ifndef __PREFS_H
#define __PREFS_H

#ifndef __PARMS_H
#include "parms.h"
#endif

typedef struct
{
  char *libdir;
  char *dbiname;
  char *dbihost;
  char *dbiuser;
  char *dbipasswd;
  char *dbidb;

  char *facename;
}
prefs;

extern prefs *load_prefs (parms *);
extern void save_prefs (prefs *);

#endif
