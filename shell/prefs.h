
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
 * $Id: prefs.h,v 1.7 2009/08/31 13:45:33 erik Exp $
 */

#ifndef __PREFS_H
#define __PREFS_H

#ifndef __PARMS_H
#include "parms.h"
#endif

typedef struct {
    char *libdir;
    char *dbiname;
    char *dbihost;
    char *dbiuser;
    char *dbipasswd;
    char *dbidb;

    char *facename;
} prefs;

extern prefs *load_prefs (parms *);
extern void save_prefs (prefs *);

#endif
