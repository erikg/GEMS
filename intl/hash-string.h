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
 * $Id: hash-string.h,v 1.7 2010/01/06 00:47:31 erik Exp $
 */

/*
 * Implements a string hashing function. Copyright (C) 1995, 1997 Free
 * Software Foundation, Inc.
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
 * You should have received a copy of the GNU Library General Public License
 * along with the GNU C Library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

/*
 * @@ end of prolog @@ 
 */

#ifndef PARAMS
#if __STDC__
#define PARAMS(Args) Args
#else
#define PARAMS(Args) ()
#endif
#endif

/*
 * We assume to have `unsigned long int' value with at least 32 bits.  
 */
#define HASHWORDBITS 32


/*
 * Defines the so called `hashpjw' function by P.J. Weinberger [see
 * Aho/Sethi/Ullman, COMPILERS: Principles, Techniques and Tools, 1986, 1987
 * Bell Telephone Laboratories, Inc.]
 */
static unsigned long int hash_string PARAMS ((const char *__str_param));

static inline unsigned long int
hash_string (str_param)
    const char *str_param;
{
    unsigned long int hval, g;
    const char *str = str_param;

    /*
     * Compute the hash value for the given string.  
     */
    hval = 0;
    while (*str != '\0')
    {
	hval <<= 4;
	hval += (unsigned long int) *str++;
	g = hval & ((unsigned long int) 0xf << (HASHWORDBITS - 4));
	if (g != 0)
	{
	    hval ^= g >> (HASHWORDBITS - 8);
	    hval ^= g;
	}
    }
    return hval;
}
