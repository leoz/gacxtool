/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Options.
 *
 * $Id: gacxopt.h,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#ifndef __GACXOPT_H__
#define __GACXOPT_H__

/***************************************************************************/

#include <gtk/gtk.h>

/***************************************************************************/

typedef struct gacx_options {
	gint   o_bandwidth;
	gint   o_delay;
	gint   o_rawdata;
	gint   o_timeout;
	gint   o_verbose;
	gchar* o_iface_name;
} gacx_options;

/***************************************************************************/

extern gacx_options _gacx_options;

/***************************************************************************/

void gacx_options_initialize ();
void gacx_options_finalize   ();
void gacx_options_correct    ();
void gacx_options_trace      ();

/***************************************************************************/

#endif /* __GACXOPT_H__ */
