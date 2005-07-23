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
 * $Id: callbacks.h,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#include <gtk/gtk.h>

void
on_main_window_destroy                 (GtkObject       *object,
                                        gpointer         user_data);

GtkWidget*
gacx_signal_databox_create (gchar *widget_name, gchar *string1, gchar *string2,
                gint int1, gint int2);

GtkWidget*
gacx_traffic_databox_create (gchar *widget_name, gchar *string1, gchar *string2,
                gint int1, gint int2);

void
on_hscale_channel_value_changed        (GtkRange        *range,
                                        gpointer         user_data);

void
on_hscale_packets_value_changed        (GtkRange        *range,
                                        gpointer         user_data);

void
on_hscale_seconds_min_value_changed    (GtkRange        *range,
                                        gpointer         user_data);

void
on_hscale_seconds_max_value_changed    (GtkRange        *range,
                                        gpointer         user_data);

void
on_spinbutton_channel_value_changed    (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_spinbutton_packets_value_changed    (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_spinbutton_seconds_min_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_spinbutton_seconds_max_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_checkbutton_rate_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_apply_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_cancel_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_button_privileges_clicked        (GtkButton       *button,
                                        gpointer         user_data);
