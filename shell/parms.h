
/*****************************************************************************
 *    GEMS Email Client                                                      *
 *                                                                           *
 *     Copyright (C) 2000-2005 Erik Greenwald <erik@smluc.org>               *
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
 * $Id: parms.h,v 1.6 2005/01/13 14:29:54 erik Exp $
 */

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
