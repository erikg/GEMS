SUBDIRS = @GETOPT_LONG_DIR@ po intl include common receptor transmitter db face shell

EXTRA_DIST=ChangeLog rpm-$(PACKAGE).spec

.PHONY : doc
doc:
	doc++ --dir=doc++ `find -name *.[ch]`

packages: deb rpm

.PHONY : rpm
rpm: dist
	cp $(PACKAGE)-$(VERSION).tar.gz /usr/src/redhat/SOURCES/
	rpm -ba rpm-$(PACKAGE).spec
	cp /usr/src/redhat/RPMS/i386/$(PACKAGE)-$(VERSION)-*.i386.rpm .
	cp /usr/src/redhat/SRPMS/$(PACKAGE)-$(VERSION)-*.src.rpm .

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
