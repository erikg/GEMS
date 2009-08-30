dnl $Id: configure.ac,v 1.16 2009/08/30 18:15:40 erik Exp $

AC_INIT
AC_CONFIG_SRCDIR([README])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(gems, 0.1)
#AM_MAINTAINER_MODE

AM_CONFIG_HEADER([include/config.h])

ALL_LINGUAS=""

AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_ISC_POSIX

AC_C_CONST
AC_HEADER_STDC([])

CPPFLAGS="${CPPFLAGS}"' -I${top_srcdir}'/include

# add /usr/local to shtuff
if test -d /usr/local
then
	CPPFLAGS="${CPPFLAGS} -I/usr/local/include"
	LDFLAGS="${LDFLAGS} -L/usr/local/lib"
fi

#AM_GNU_GETTEXT_VERSION(0.11.5)
#AM_GNU_GETTEXT([external])
dnl AM_GNU_GETTEXT()
#GETTEXT_PACKAGE=gems
#AC_SUBST(GETTEXT_PACKAGE)
#AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [gettext package?])
#AM_GLIB_GNU_GETTEXT
#intl=
#AC_SUBST(intl)
#AM_CONDITIONAL(INTL, false)

dnl **************************************************************************
dnl ********************************* DBIs ***********************************
dnl **************************************************************************

DB=""

AC_MSG_CHECKING([MySQL])
have_mysql=yes
MYSQL_LIBADD="-L/usr/local/lib/mysql -L/usr/lib/mysql -lmysqlclient"
MYSQL_CFLAGS="-I/usr/local/include"
AC_SUBST(MYSQL_CFLAGS)
AC_SUBST(MYSQL_LIBADD)
AM_CONDITIONAL(MYSQL, [test "x$have_mysql" == "xyes"])
if test "x$have_mysql" == "xyes"
then
	AC_MSG_RESULT([Yes])
	DB="${DB} MySQL"
else
	AC_MSG_RESULT([No])
fi

AC_MSG_CHECKING([PostgreSQL])
have_postgresql=no
POSTGRESQL_LIBADD=""
AC_CHECK_LIB(pq, PQconnectdb, have_postgresql="yes")
AM_CONDITIONAL(POSTGRESQL, [test "x$have_postgresql" == xyes])
if test "x$have_postgresql" == xyes
then
	AC_MSG_RESULT([Yes])
	POSTGRESQL_LIBADD="${LDFLAGS} -lpq"
	DB="${DB} PostGreSQL"
else
	AC_MSG_RESULT([No])
fi
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

AC_MSG_CHECKING([GTK1])
have_gtk=no
AC_ARG_ENABLE(gtk,
[  --enable-gtk            Use GTK (default=yes)],use_gtk=no,use_gtk=yes)
if test "x$use_gtk" == "xyes"
then
    AM_PATH_GTK(1.1.0,have_gtk=yes)
fi
AM_CONDITIONAL(GTK1, [test "x$have_gtk" == "xyes"])
if test "x$have_gtk" == "xyes"
then 
	FACE="${FACE} GTK1"
fi
AC_MSG_RESULT($have_gtk)

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

AC_MSG_CHECKING([GNOME1])
AC_ARG_ENABLE(gnome, [  --enable-gnome          Use GNOME [default=yes]], use_gnome=yes, use_gnome=no)
if test "x$use_gnome" = "xyes"
then
        AC_PATH_PROG(GNOME_CONFIG,gnome-config)
        AC_MSG_CHECKING(for GNOME)
        if $GNOME_CONFIG --libs-only-l gnome >/dev/null 2>&1 
	then
		have_gnome=yes
		FACE="${FACE} GNOME"
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
AM_CONDITIONAL(GNOME,[test "x$have_gnome" == xyes])

dnl **************************************************************************

pkg_modules="libgnomeui-2.0"
PKG_CHECK_MODULES(PACKAGE, [$pkg_modules])
GNOME2_CFLAGS=$PACKAGE_CFLAGS
GNOME2_LIBS=$PACKAGE_LIBS
AC_SUBST(GNOME2_CFLAGS)
AC_SUBST(GNOME2_LIBS)
AM_CONDITIONAL(GNOME2,[test "x$have_gnome2" == xyes])
if test "x$have_gnome2" == "xyes" ; then FACE="${FACE} GNOME2" ; fi

dnl **************************************************************************

#AC_CHECK_CURSES
has_curses=yes
AM_CONDITIONAL(HAS_CURSES, [ test "$has_curses" == true ])
if test "x$has_curses" == "xyes" ; then FACE="${FACE} CURSES"; fi

dnl **************************************************************************

AC_CHECK_FUNCS(dlopen, [MY_LDADD=""], [
  AC_CHECK_LIB(dl, dlopen, [MY_LDADD="-ldl"], [
    AC_MSG_ERROR([could not find dlopen().]) ]) ])


MY_LDFLAGS="$LDFLAGS"
MY_LDADD="$LDADD"
AC_SUBST(MY_LDFLAGS)
AC_SUBST(MY_LDADD)

AC_CONFIG_FILES([
	Makefile common/Makefile receptor/Makefile transmitter/Makefile shell/Makefile include/Makefile
	gems.spec doc/Makefile doc/doxygen.conf
	po/Makefile.in
	db/Makefile db/MySQL/Makefile db/PostGreSQL/Makefile
	face/Makefile face/utils/Makefile
	face/GTK/Makefile face/GTK/e/Makefile
	face/GNOME/Makefile face/GNOME/e/Makefile face/GNOME/o/Makefile face/GNOME/xf/Makefile
	face/GNOME2/Makefile face/GNOME2/o/Makefile
	face/curses/Makefile face/curses/CURSES_p/Makefile
	])
AC_OUTPUT

dnl print out what we learned...
echo -e \\n\\n
echo "==============================================================================="
echo "DBMS's: $DB"
echo "Face sets: $FACE"
echo "Installing to: $prefix"
echo "==============================================================================="

