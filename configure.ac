dnl $Id: configure.ac,v 1.1 2004/04/27 21:58:48 erik Exp $

AC_INIT
AC_CONFIG_SRCDIR([README])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(gems, 0.0)
AM_MAINTAINER_MODE

AC_CONFIG_HEADERS([include/config.h])

ALL_LINGUAS=""

AC_PROG_CC
AM_PROG_LIBTOOL
AC_PROG_INSTALL
AC_ISC_POSIX

AC_C_CONST
AC_HEADER_STDC([])

CFLAGS="$CFLAGS -I\$(top_srcdir)/include -I/usr/local/include"

dnl AM_GNU_GETTEXT([external])
dnl AM_GNU_GETTEXT()
dnl GETTEXT_PACKAGE=gems
dnl AC_SUBST(GETTEXT_PACKAGE)
dnl AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [gettext package?])
dnl AM_GLIB_GNU_GETTEXT
intl=
AC_SUBST(intl)

dnl **************************************************************************
dnl ********************************* DBIs ***********************************
dnl **************************************************************************

MYSQL=MySQL
MYSQL_LIBADD="-L/usr/local/lib/mysql -L/usr/lib/mysql -lmysqlclient"
AC_SUBST(MYSQL_LIBADD)

POSTGRESQL=PostgreSQL
POSTGRESQL_LIBADD="-L/usr/local/lib/ -lpq"
AC_SUBST(POSTGRESQL_LIBADD)

dnl **************************************************************************

GETOPT_LONG_LIBS=""
GETOPT_LONG_CFLAGS=""
AC_CHECK_FUNCS(getopt_long , , [
        GETOPT_LONG_LIBS="-lgnugetopt"
        ] )
AC_SUBST(GETOPT_LONG_LIBS)
AC_SUBST(GETOPT_LONG_CFLAGS)

LDL_LIBS=""
AC_CHECK_FUNCS(dlopen , , [AC_CHECK_LIB(dl, dlopen, LDL_LIBS="")])
AC_SUBST(LDL_LIBS)

dnl **************************************************************************
dnl ************************  FACES  *****************************************
dnl **************************************************************************

GTK=
AC_ARG_ENABLE(gtk,
[  --enable-gtk            Use GTK (default=yes)],use_gtk=no,use_gtk=yes)
if test "$use_gtk" = "yes"
then
    AM_PATH_GTK(1.1.0,GTK=GTK,GTK=)
fi

dnl **************************************************************************

GNOME=
AC_ARG_WITH(gnome-includes,
        [  --with-gnome-includes   Specify location of GNOME headers],[
        CFLAGS="$CFLAGS -I$withval"
        ])
AC_ARG_WITH(gnome-libs,
        [  --with-gnome-libs       Specify location of GNOME libs],[
        LDFLAGS="$LDFLAGS -L$withval"
        gnome_prefix=$withval
        ])

AC_ARG_ENABLE(gnome,
[  --enable-gnome          Use GNOME [default=yes]], use_gnome=no, use_gnome=yes)
if test "x$use_gnome" = xyes; then
        AC_PATH_PROG(GNOME_CONFIG,gnome-config)
        AC_MSG_CHECKING(for GNOME)
        if $GNOME_CONFIG --libs-only-l gnome >/dev/null 2>&1; then
		GNOME=GNOME
                GNOME_CFLAGS=`gnome-config --cflags gnomeui`
                GNOME_LIBS=`gnome-config --libs gnomeui`
		AC_SUBST(GNOME_CFLAGS)
		AC_SUBST(GNOME_LIBS)
                AC_MSG_RESULT(yes)
        else
                AC_MSG_RESULT(no)
        fi
else
                AC_MSG_RESULT(no)
fi

dnl **************************************************************************

GNOME2=GNOME2
pkg_modules="libgnomeui-2.0"
PKG_CHECK_MODULES(PACKAGE, [$pkg_modules])
GNOME2_CFLAGS=$PACKAGE_CFLAGS
GNOME2_LIBS=$PACKAGE_LIBS
AC_SUBST(GNOME2_CFLAGS)
AC_SUBST(GNOME2_LIBS)

dnl **************************************************************************

CURSES=
CURSEMAKE=
dnl AC_CHECK_CURSES
dnl AM_CONDITIONAL(HAS_CURSES, test "$has_curses" = true)
dnl if HAS_CURSES
dnl CURSES=curses
dnl CURSEMAKE=face/curses/Makefile
dnl fi

dnl the DBI's
AC_SUBST(MYSQL)
AC_SUBST(POSTGRESQL)

dnl the faces
AC_SUBST(GTK)
AC_SUBST(GNOME)
AC_SUBST(GNOME2)
AC_SUBST(CURSES)

dnl **************************************************************************

AC_CHECK_FUNCS(dlopen, [MY_LDADD=""], [
  AC_CHECK_LIB(dl, dlopen, [MY_LDADD="-ldl"], [
    AC_MSG_ERROR([could not find dlopen().]) ]) ])


MY_LDFLAGS="$LDFLAGS"
dnl MY_LDADD="$LDADD"
echo "MY_LDADD: $MY_LDADD"
AC_SUBST(MY_LDFLAGS)
AC_SUBST(MY_LDADD)

AC_CONFIG_FILES([
	Makefile po/Makefile.in intl/Makefile common/Makefile db/Makefile face/Makefile
	face/utils/Makefile shell/Makefile include/Makefile
	receptor/Makefile transmitter/Makefile
	db/MySQL/Makefile db/PostgreSQL/Makefile
	face/GTK/Makefile face/GTK/e/Makefile
	face/GNOME/Makefile face/GNOME/e/Makefile face/GNOME/o/Makefile face/GNOME/xf/Makefile
	face/GNOME2/Makefile face/GNOME2/o/Makefile
	doc/Makefile gems.spec doc/doxygen.conf])
AC_OUTPUT

dnl print out what we learned...
echo -e \\n\\n
echo "==============================================================================="
echo "DBMS's: $MYSQL $POSTGRESQL"
echo "Face sets: $GTK $GNOME $GNOME2 $CURSES"
echo "Installing to: $prefix"
echo "==============================================================================="
