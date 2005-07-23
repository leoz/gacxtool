#############################################################################
#  Copyright (C) 2004 Leonid Zolotarev
#
#  Licensed under the terms of the BSD license, see file COPYING
#  for details.
#
#  GTK ACX Tool.
#
#  themes/default/Makefile.am
#
#  Process this file with automake to produce Makefile.in
#
#  $Id: Makefile.am,v 1.1.1.1 2005-07-23 23:16:12 zoleo Exp $
#############################################################################

themedir = $(DESTDIR)$(pkgdatadir)/themes/default
theme_DATA =                 \
	README                   \
	default.gtkrc            \
	noise_progressbar.png    \
	quality_progressbar.png  \
	receive_progressbar.png  \
	strength_progressbar.png \
	transmit_progressbar.png
EXTRA_DIST = $(theme_DATA)

clean:
	rm -f \
	*~ \
	*.bak \
	Makefile.in

#############################################################################
