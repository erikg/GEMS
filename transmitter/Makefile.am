# $Id: Makefile.am,v 1.4 2007/02/12 21:15:03 erik Exp $

transmitterdir = $(libdir)/gems
transmitter_LTLIBRARIES = libgemstransmitter.la

libgemstransmitter_la_SOURCES = transmitter.c
libgemstransmitter_la_LDFLAGS = @MY_LDFLAGS@
libgemstransmitter_la_LIBADD = @MY_LDADD@

EXTRA_DIST=sendmail.c smtp.c
