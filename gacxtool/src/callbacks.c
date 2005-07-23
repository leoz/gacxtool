/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Callbacks.
 *
 * $Id: callbacks.c,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <gtkdatabox.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "gacxtimer.h"
#include "gacxbox.h"
#include "gacxset.h"

void
on_main_window_destroy (GtkObject *object, gpointer user_data)
{
	gacx_timer_data_destroy ();
	gacx_signal_databox_data_destroy ();
	gacx_traffic_databox_data_destroy ();
	gtk_main_quit ();
}

GtkWidget*
gacx_signal_databox_create (gchar *widget_name, gchar *string1, gchar *string2,
                gint int1, gint int2)
{
	GtkWidget* databox = gtk_databox_new ();
	gacx_signal_databox_data_create ( databox );
	return databox;
}

GtkWidget*
gacx_traffic_databox_create (gchar *widget_name, gchar *string1, gchar *string2,
                gint int1, gint int2)
{
	GtkWidget* databox = gtk_databox_new ();
	gacx_traffic_databox_data_create ( databox );
	return databox;
}


void
on_hscale_channel_value_changed        (GtkRange        *range,
                                        gpointer         user_data)
{
	gacx_settings_range_changed ( gacx_setting_channel );
}


void
on_hscale_packets_value_changed        (GtkRange        *range,
                                        gpointer         user_data)
{
	gacx_settings_range_changed ( gacx_setting_packets );
}


void
on_hscale_seconds_min_value_changed    (GtkRange        *range,
                                        gpointer         user_data)
{
	gacx_settings_range_changed ( gacx_setting_seconds_min );
}


void
on_hscale_seconds_max_value_changed    (GtkRange        *range,
                                        gpointer         user_data)
{
	gacx_settings_range_changed ( gacx_setting_seconds_max );
}


void
on_spinbutton_channel_value_changed    (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	gacx_settings_spin_changed ( gacx_setting_channel );
}


void
on_spinbutton_packets_value_changed    (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	gacx_settings_spin_changed ( gacx_setting_packets );
}


void
on_spinbutton_seconds_min_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	gacx_settings_spin_changed ( gacx_setting_seconds_min );
}


void
on_spinbutton_seconds_max_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	gacx_settings_spin_changed ( gacx_setting_seconds_max );
}


void
on_checkbutton_rate_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gacx_settings_check_changed ();
}


void
on_button_apply_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	gacx_settings_apply ();
}


void
on_button_cancel_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	gacx_settings_cancel ();
}


void
on_ok_button_privileges_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy ( gtk_widget_get_toplevel ( GTK_WIDGET ( button ) ) );
}

