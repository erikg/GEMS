# $Id: Makefile.am,v 1.11 2005/04/02 20:20:27 erik Exp $

if INTL
intl = intl
endif

SUBDIRS = $(intl) include common receptor transmitter db face shell doc

EXTRA_DIST=ChangeLog $(PACKAGE).spec

.PHONY : doc
doc:
	doc++ --dir=doc++ `find -name *.[ch]`

packages: deb rpm

.PHONY : rpm
rpm: dist
	cp $(PACKAGE)-$(VERSION).tar.gz ${HOME}/rpm/SOURCES/
	rpmbuild -ba $(PACKAGE).spec
	cp ${HOME}/rpm/RPMS/i386/$(PACKAGE)-$(VERSION)-*.i386.rpm .
	cp ${HOME}/rpm/SRPMS/$(PACKAGE)-$(VERSION)-*.src.rpm .

.PHONY : deb
deb:
	debian/rules
	debuild
	debc
	debi
	release

lint:
	make -C src lint
indent:
	make -C src indent

docs:
	doxygen doc/doxygen.conf
	(cd doc/doxygen/latex && make)
	dvips -f doc/doxygen/latex/refman.dvi > doc/@PACKAGE@-devmanual.ps
	ps2pdf doc/@PACKAGE@-devmanual.ps doc/@PACKAGE@-devmanual.pdf

test:
	(cd tests && make test)

