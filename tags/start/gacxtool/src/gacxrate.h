/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Rate widget.
 *
 * $Id: gacxrate.h,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#ifndef __GACXRATE_H__
#define __GACXRATE_H__

/***************************************************************************/

#include <gtk/gtk.h>

/***************************************************************************/

typedef struct gacx_rate_data {
	GtkWidget* rd_1;
	GtkWidget* rd_2;
	GtkWidget* rd_5;
	GtkWidget* rd_11;
	GtkWidget* rd_22;
	GtkWidget* rd_f1;
	GtkWidget* rd_f2;
	GtkWidget* rd_f5;
	GtkWidget* rd_f11;
	GtkWidget* rd_f22;
	GdkColor   rd_color_enable;
	GdkColor   rd_color_disable;
	gint       rd_rates;
} gacx_rate_data;

/***************************************************************************/

void gacx_rate_data_create  ( GtkWidget* main_window );
void gacx_rate_data_destroy ();
void gacx_rate_data_update  ( gint rates );

/***************************************************************************/

#endif /* __GACXRATE_H__ */
