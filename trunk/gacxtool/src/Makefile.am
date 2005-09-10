#############################################################################
#  Copyright (C) 2004 - 2005 Leonid Zolotarev
#
#  Licensed under the terms of the BSD license, see file COPYING
#  for details.
#
#  GTK ACX Tool.
#
#  Process this file with automake to produce Makefile.in
#
#  $Id: Makefile.am,v 1.2 2005-09-10 21:02:47 zoleo Exp $
#############################################################################

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DGACXTOOL_MAJOR=$(GACXTOOL_MAJOR) \
	-DGACXTOOL_MINOR=$(GACXTOOL_MINOR) \
	-DGACXTOOL_MICRO=$(GACXTOOL_MICRO) \
	$(GTK_CFLAGS) $(GTKDATABOX_CFLAGS) $(SYSTEM_CFLAGS)

bin_PROGRAMS = gacxtool

gacxtool_SOURCES = \
	main.c        gacxmain.h    \
	support.c     support.h     \
	interface.c   interface.h   \
	callbacks.c   callbacks.h   \
	gacxopt.c     gacxopt.h     \
	gacxtimer.c   gacxtimer.h   \
	gacxsignal.c  gacxsignal.h  \
	gacxtraffic.c gacxtraffic.h \
	gacxstatus.c  gacxstatus.h  \
	gacxrate.c    gacxrate.h    \
	gacxbox.c     gacxbox.h     \
	gacxset.c     gacxset.h     \
	acxlib.c      acxlib.h

gacxtool_LDADD = $(GTK_LIBS) $(GTKDATABOX_LIBS) $(SYSTEM_LIBS) $(INTLLIBS)

clean:
	rm -f \
	*.o \
	*~ \
	*.bak \
	Makefile.in \
	gacxtool \
	gacxtool.core

#############################################################################
