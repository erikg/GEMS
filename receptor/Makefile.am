# $Id: Makefile.am,v 1.2 2003/04/05 18:06:02 erik Exp $

receptordir = $(libdir)/gems

receptor_LIBRARIES = libgemsreceptor.a
receptor_LTLIBRARIES = libgemsreceptor.la

SRCFILES = imap4.c pop1.c pop2.c pop3.c spool.c

libgemsreceptor_a_SOURCES = $(SRCFILES)
libgemsreceptor_la_SOURCES = $(SRCFILES)

LDFLAGS = @MY_LDFLAGS@
LDADD = @MY_LDADD@
