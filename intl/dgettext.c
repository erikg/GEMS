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
 * $Id: dgettext.c,v 1.7 2010/01/06 00:47:31 erik Exp $
 */

/*
 * Implementation of the dgettext(3) function Copyright (C) 1995, 1996, 1997
 * Free Software Foundation, Inc.
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if defined HAVE_LOCALE_H || defined _LIBC
#include <locale.h>
#endif

#ifdef _LIBC
#include <libintl.h>
#else
#include "libgettext.h"
#endif

/*
 * @@ end of prolog @@ 
 */

/*
 * Names for the libintl functions are a problem.  They must not clash with
 * existing names and they should follow ANSI C.  But this source code is
 * also used in GNU C Library where the names have a __ prefix.  So we have
 * to make a difference here.
 */
#ifdef _LIBC
#define DGETTEXT __dgettext
#define DCGETTEXT __dcgettext
#else
#define DGETTEXT dgettext__
#define DCGETTEXT dcgettext__
#endif

/*
 * Look up MSGID in the DOMAINNAME message catalog of the current LC_MESSAGES
 * locale.
 */
char *
DGETTEXT (domainname, msgid)
    const char *domainname;
    const char *msgid;
{
    return DCGETTEXT (domainname, msgid, LC_MESSAGES);
}

#ifdef _LIBC
/*
 * Alias for function name in GNU C Library.  
 */
weak_alias (__dgettext, dgettext);
#endif
