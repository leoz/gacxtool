/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Settings widgets.
 *
 * $Id: gacxset.h,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#ifndef __GACXSET_H__
#define __GACXSET_H__

/***************************************************************************/

#include <gtk/gtk.h>

/***************************************************************************/

typedef struct gacx_settings {
	int s_starts_fast;
	int s_scan_period;
	int s_threshold;
	int s_min_time;
	int s_max_time;
} gacx_settings;

/***************************************************************************/

typedef enum gacx_setting {
	gacx_setting_rate = 0,
	gacx_setting_channel,
	gacx_setting_packets,
	gacx_setting_seconds_min,
	gacx_setting_seconds_max
} gacx_setting;

/***************************************************************************/

typedef struct gacx_settings_data {
	GtkWidget* sd_range_channel;
	GtkWidget* sd_spin_channel;

	GtkWidget* sd_range_packets;
	GtkWidget* sd_spin_packets;

	GtkWidget* sd_range_seconds_min;
	GtkWidget* sd_spin_seconds_min;

	GtkWidget* sd_range_seconds_max;
	GtkWidget* sd_spin_seconds_max;

	GtkWidget* sd_check_rate;

	GtkWidget* sd_btn_apply;
	GtkWidget* sd_btn_cancel;

	int        sd_initialized;
	int        sd_changed;
} gacx_settings_data;

/***************************************************************************/

void gacx_settings_data_create   ( GtkWidget* main_window );
void gacx_settings_data_destroy  ();
void gacx_settings_data_update   ();
void gacx_settings_range_changed ( gacx_setting setting );
void gacx_settings_spin_changed  ( gacx_setting setting );
void gacx_settings_check_changed ();
void gacx_settings_apply         ();
void gacx_settings_cancel        ();

/***************************************************************************/

void gacx_update_entry ( GtkWidget* entry, gint val );

/***************************************************************************/

#endif /* __GACXSET_H__ */
