transmitterdir = $(libdir)/gems

transmitter_LIBRARIES = libgemstransmitter.a
transmitter_LTLIBRARIES = libgemstransmitter.la

SRCFILES = sendmail.c smtp.c transmitter.c

libgemstransmitter_a_SOURCES = $(SRCFILES)
libgemstransmitter_la_SOURCES = $(SRCFILES)

LDFLAGS = @MY_LDFLAGS@
LDADD = @MY_LDADD@
