# $Id: Makefile.am,v 1.2 2003/04/05 18:06:02 erik Exp $

transmitterdir = $(libdir)/gems

transmitter_LIBRARIES = libgemstransmitter.a
transmitter_LTLIBRARIES = libgemstransmitter.la

SRCFILES = sendmail.c smtp.c transmitter.c

libgemstransmitter_a_SOURCES = $(SRCFILES)
libgemstransmitter_la_SOURCES = $(SRCFILES)

LDFLAGS = @MY_LDFLAGS@
LDADD = @MY_LDADD@
