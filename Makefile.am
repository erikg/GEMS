# $Id: Makefile.am,v 1.7 2004/02/01 19:41:03 erik Exp $

# $Id: Makefile.am,v 1.7 2004/02/01 19:41:03 erik Exp $

SUBDIRS = po $(intl) include common receptor transmitter db face shell doc

EXTRA_DIST=ChangeLog rpm-$(PACKAGE).spec

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
