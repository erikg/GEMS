#ifndef __PARMS_H
#define __PARMS_H

/** parms contains all the information gotten from the config file */

typedef struct {
    char *libdir;
    char *dbiname;
    char *dbihost;
    char *dbiuser;
    char *dbipasswd;
    char *dbidb;

    char *facename;

    char *rc;
} parms;

/** loads the configuration information from the file
 * @param
 * @param
 */

extern parms *load_parms (int *, char **);
void parms_destroy (parms * p);

#endif
