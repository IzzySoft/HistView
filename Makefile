# Makefile for histview
# $Id$

DESTDIR=
prefix=/usr/local
datarootdir=$(DESTDIR)$(prefix)/share
datadir=$(datarootdir)/histview
docdir=$(datarootdir)/doc/histview
INSTALL=install
INSTALL_DATA=$(INSTALL) -m 644

WEBROOT=$(DESTDIR)/var/www
LINKTO=$(WEBROOT)/histview

install: installdirs
	$(INSTALL_DATA) histview.* $(datadir)
	$(INSTALL_DATA) filelist.* $(datadir)
	$(INSTALL_DATA) class.* $(datadir)
	$(INSTALL_DATA) dl_latest.php $(datadir)
	$(INSTALL_DATA) icons/* $(datadir)/icons
	$(INSTALL_DATA) doc/* $(docdir)
	if [ ! -e $(LINKTO) ]; then ln -s $(datadir) $(LINKTO); fi

installdirs:
	mkdir -p $(datadir)/icons
	mkdir -p $(docdir)
	if [ ! -e $(WEBROOT) ]; then mkdir -p $(WEBROOT); fi

uninstall:
	rm -rf $(datadir)
	rm -rf $(docdir)
