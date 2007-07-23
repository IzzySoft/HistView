# Makefile for histview
# $Id$

DESTDIR=
prefix=/usr/local
datarootdir=$(DESTDIR)$(prefix)/share
datadir=$(datarootdir)/histview
INSTALL=

WEBROOT=$(DESTDIR)/var/www
LINKTO=$(WEBROOT)/histview

install: installdirs
	cp -pr * $(datadir)
	rm -f $(datadir)/Makefile
	if [ ! -e $(LINKTO) ]; then ln -s $(datadir) $(LINKTO); fi

installdirs:
	mkdir -p $(datadir)
	if [ ! -e $(WEBROOT) ]; then mkdir -p $(WEBROOT); fi

uninstall:
	rm -rf $(datadir)

