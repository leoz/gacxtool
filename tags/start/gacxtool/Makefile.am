#############################################################################
#  Copyright (C) 2004 Leonid Zolotarev
#
#  Licensed under the terms of the BSD license, see file COPYING
#  for details.
#
#  GTK ACX Tool.
#
#  Process this file with automake to produce Makefile.in
#
#  $Id: Makefile.am,v 1.1.1.1 2005-07-23 23:16:09 zoleo Exp $
#############################################################################

SUBDIRS = src po icons themes

EXTRA_DIST =           \
	autogen.sh         \
	ROADMAP            \
	USAGE              \
	gui/gacxtool.glade \
	gui/gacxtool.gladep

install-data-local:

dist-hook:

clean:
	rm -f -r \
	*~ \
	*.bak \
	po/*~ \
	po/*.bak \
	gui/*~ \
	gui/*.bak \
	gacxtool*.tar.gz \
	aclocal.m4 \
	configure \
	configure.lineno \
	Makefile.in \
	po/Makefile.in.in \
	mkinstalldirs \
	stamp-h.in \
	autom4te.cache
	

#############################################################################
