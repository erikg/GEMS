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
 * $Id: face.h,v 1.5 2005/01/13 14:29:53 erik Exp $
 */


	/** returns GEMS_TRUE if requires X */
int face_uses_X ();

	/** actually execute the 'face' */
int face_run (int argc, char **argv);

	/** if an error occurs in the shell or subsystem, the face is
	 * responsible for reporting it. This is the mechanism used.
	 * gems_err refers to the component error (dbi, shell, etc)
	 * subsystem_err is what the component could find out (mysql_error, etc)
	 */
void oops (char *gems_err, char *subsystem_err);
