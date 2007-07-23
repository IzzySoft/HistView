# Makefile for histview
# $Id$

DESTDIR=
prefix=/usr/local
datarootdir=$(DESTDIR)$(prefix)/share
datadir=$(datarootdir)/histview
INSTALL=

install: installdirs
	cp -pr * $(datadir)
	rm -f $(datadir)/Makefile

installdirs:
	mkdir -p $(datadir)

uninstall:
	rm -rf $(datadir)

