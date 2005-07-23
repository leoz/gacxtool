/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Timer.
 *
 * $Id: gacxtimer.h,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#ifndef __GACXTIMER_H__
#define __GACXTIMER_H__

/***************************************************************************/

#include <gtk/gtk.h>

/***************************************************************************/

typedef struct gacx_timer_data {
	GtkWidget* td_main_window;
	GtkWidget* td_bar_quality;
	GtkWidget* td_bar_strength;
	GtkWidget* td_bar_noise;
	GtkWidget* td_ent_strength;
	GtkWidget* td_ent_strength_avg;
	GtkWidget* td_ent_strength_max;
	GtkWidget* td_ent_noise;
	GtkWidget* td_ent_noise_avg;
	GtkWidget* td_ent_noise_max;
	GtkWidget* td_ent_status;
	GtkWidget* td_ent_bssid;
	GtkWidget* td_ent_ssid;
	GtkWidget* td_ent_channel;
	GtkWidget* td_bar_transmit;
	GtkWidget* td_bar_receive;
	GtkWidget* td_ent_transmit;
	GtkWidget* td_ent_receive;
	GtkWidget* td_lab_strength_avg;
	GtkWidget* td_lab_strength_max;
	GtkWidget* td_lab_noise_avg;
	GtkWidget* td_lab_noise_max;
	GtkWidget* td_status_main;
	GtkWidget* td_status_device;
	GtkWidget* td_status_user;
	int        td_max_rate;
	int        td_timeout;
	int        td_timer;
	int        td_iface;
	int        td_state;
} gacx_timer_data;

/***************************************************************************/

void gacx_timer_data_create  ( GtkWidget* main_window );
void gacx_timer_data_destroy ();

/***************************************************************************/

void gacx_update_entry ( GtkWidget* entry, gint val );

/***************************************************************************/

extern gint    _val_quality;
extern gint    _val_strength;
extern gint    _val_noise;

extern gdouble _val_transmit;
extern gdouble _val_receive;

/***************************************************************************/

#endif /* __GACXTIMER_H__ */
