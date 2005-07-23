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
 * $Id: gacxset.c,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#include "support.h"
#include "interface.h"
#include "acxlib.h"
#include "gacxset.h"

/***************************************************************************/

gacx_settings*      _set_cur  = NULL;
gacx_settings*      _set_new  = NULL;
gacx_settings_data* _set_data = NULL;

/***************************************************************************/

void gacx_settings_enable_buttons ()
{
	gtk_widget_set_sensitive ( _set_data->sd_btn_apply , _set_data->sd_changed );
	gtk_widget_set_sensitive ( _set_data->sd_btn_cancel, _set_data->sd_changed );
}

/***************************************************************************/

void gacx_settings_data_create ( GtkWidget* main_window )
{
	if ( ! _set_data ) {
    	_set_data = g_malloc ( sizeof ( gacx_settings_data ) );

		_set_data->sd_range_channel     = lookup_widget ( main_window, "hscale_channel"         );
		_set_data->sd_spin_channel      = lookup_widget ( main_window, "spinbutton_channel"     );

		_set_data->sd_range_packets     = lookup_widget ( main_window, "hscale_packets"         );
		_set_data->sd_spin_packets      = lookup_widget ( main_window, "spinbutton_packets"     );

		_set_data->sd_range_seconds_min = lookup_widget ( main_window, "hscale_seconds_min"     );
		_set_data->sd_spin_seconds_min  = lookup_widget ( main_window, "spinbutton_seconds_min" );

		_set_data->sd_range_seconds_max = lookup_widget ( main_window, "hscale_seconds_max"     );
		_set_data->sd_spin_seconds_max  = lookup_widget ( main_window, "spinbutton_seconds_max" );

		_set_data->sd_check_rate        = lookup_widget ( main_window, "checkbutton_rate"       );

		_set_data->sd_btn_apply         = lookup_widget ( main_window, "button_apply"           );
		_set_data->sd_btn_cancel        = lookup_widget ( main_window, "button_cancel"          );

		_set_data->sd_initialized       = FALSE;
		_set_data->sd_changed           = FALSE;
	}
	if ( ! _set_cur ) {
    	_set_cur = g_malloc0 ( sizeof ( gacx_settings ) );
	}
	if ( ! _set_new ) {
    	_set_new = g_malloc0 ( sizeof ( gacx_settings ) );
	}

	gacx_settings_enable_buttons ();
}

/***************************************************************************/

void gacx_settings_data_destroy ()
{
	if ( _set_data ) {
		_set_data->sd_range_channel     = NULL;
		_set_data->sd_spin_channel      = NULL;

		_set_data->sd_range_packets     = NULL;
		_set_data->sd_spin_packets      = NULL;

		_set_data->sd_range_seconds_min = NULL;
		_set_data->sd_spin_seconds_min  = NULL;

		_set_data->sd_range_seconds_max = NULL;
		_set_data->sd_spin_seconds_max  = NULL;

		_set_data->sd_check_rate        = NULL;

		_set_data->sd_btn_apply         = NULL;
		_set_data->sd_btn_cancel        = NULL;

		_set_data->sd_initialized       = FALSE;
		_set_data->sd_changed           = FALSE;

		g_free ( _set_data );
		_set_data = NULL;

		g_free ( _set_cur );
		_set_cur = NULL;

		g_free ( _set_new );
		_set_new = NULL;
	}
}

/***************************************************************************/

void gacx_settings_get_widgets ( gacx_setting    setting,
                                 GtkRange**      range,
                                 GtkSpinButton** spin )
{
	if ( range && spin ) {
		switch ( setting ) {
		case gacx_setting_channel:
			*range = GTK_RANGE       ( _set_data->sd_range_channel );
			*spin  = GTK_SPIN_BUTTON ( _set_data->sd_spin_channel  );
			break;
		case gacx_setting_packets:
			*range = GTK_RANGE       ( _set_data->sd_range_packets );
			*spin  = GTK_SPIN_BUTTON ( _set_data->sd_spin_packets  );
			break;
		case gacx_setting_seconds_min:
			*range = GTK_RANGE       ( _set_data->sd_range_seconds_min );
			*spin  = GTK_SPIN_BUTTON ( _set_data->sd_spin_seconds_min  );
			break;
		case gacx_setting_seconds_max:
			*range = GTK_RANGE       ( _set_data->sd_range_seconds_max );
			*spin  = GTK_SPIN_BUTTON ( _set_data->sd_spin_seconds_max  );
			break;
		default:
			*range = NULL;
			*spin  = NULL;
			break;
		}
	}
}

/***************************************************************************/

void gacx_settings_set_check ( int value )
{
	gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( _set_data->sd_check_rate ), value );
}

/***************************************************************************/

void gacx_settings_set_value ( gacx_setting setting, int value )
{
	GdkColor       color_base;
	GdkColor       color_text;
	GtkRange*      range = NULL;
	GtkSpinButton* spin  = NULL;

	gacx_settings_get_widgets ( setting, &range, &spin );

	if ( range && spin ) {
		gtk_range_set_value ( range, value );
		if ( gtk_range_get_value ( range ) != value ) {
			gdk_color_parse ( "yellow", &color_base );
			gdk_color_parse ( "red"   , &color_text );
			gtk_widget_modify_base ( GTK_WIDGET ( spin ), GTK_STATE_NORMAL, &color_base );
			gtk_widget_modify_text ( GTK_WIDGET ( spin ), GTK_STATE_NORMAL, &color_text );
			gacx_update_entry ( GTK_WIDGET ( spin ), value );
		}
		else {
			/* Reset color back. */
			gtk_widget_modify_base ( GTK_WIDGET ( spin ), GTK_STATE_NORMAL, NULL );
			gtk_widget_modify_text ( GTK_WIDGET ( spin ), GTK_STATE_NORMAL, NULL );
		}
	}
}

/***************************************************************************/

void gacx_settings_data_reset ()
{
	memset ( _set_cur, 0, sizeof ( gacx_settings ) );
	memset ( _set_new, 0, sizeof ( gacx_settings ) );

	_set_data->sd_initialized = FALSE;
	_set_data->sd_changed     = FALSE;

	gacx_settings_set_check ( 0 );
	gacx_settings_set_value ( gacx_setting_channel    , 0 );
	gacx_settings_set_value ( gacx_setting_packets    , 0 );
	gacx_settings_set_value ( gacx_setting_seconds_min, 0 );
	gacx_settings_set_value ( gacx_setting_seconds_max, 0 );
}

/***************************************************************************/

void gacx_settings_save_new_value ( gacx_setting setting, int value )
{
	switch ( setting ) {
	case gacx_setting_rate:
		_set_new->s_starts_fast = value;
		if ( _set_new->s_starts_fast != _set_cur->s_starts_fast ) {
			_set_data->sd_changed = TRUE;
		}
		break;
	case gacx_setting_channel:
		_set_new->s_scan_period = value;
		if ( _set_new->s_scan_period != _set_cur->s_scan_period ) {
			_set_data->sd_changed = TRUE;
		}
		break;
	case gacx_setting_packets:
		_set_new->s_threshold   = value;
		if ( _set_new->s_threshold   != _set_cur->s_threshold   ) {
			_set_data->sd_changed = TRUE;
		}
		break;
	case gacx_setting_seconds_min:
		_set_new->s_min_time    = value;
		if ( _set_new->s_min_time    != _set_cur->s_min_time    ) {
			_set_data->sd_changed = TRUE;
		}
		break;
	case gacx_setting_seconds_max:
		_set_new->s_max_time    = value;
		if ( _set_new->s_max_time    != _set_cur->s_max_time    ) {
			_set_data->sd_changed = TRUE;
		}
		break;
	default:
		break;
	}
	gacx_settings_enable_buttons ();
}

/***************************************************************************/

void gacx_settings_value_update ( int  cur_val,
                                  int* new_val,
                                  int* val,
                                  int* changed )
{
	if ( *new_val != cur_val ) {
		if ( _set_data->sd_changed == TRUE ) {
			*changed = TRUE;
		}
		else {
			*new_val = cur_val;
		}
		*val = *new_val;
	}
}

/***************************************************************************/

void gacx_settings_data_update ()
{
	int starts_fast = acx_get_starts_fast ();
	int scan_period = acx_get_scan_period ();
	int threshold   = acx_get_threshold   ();
	int min_time    = acx_get_min_time    ();
	int max_time    = acx_get_max_time    ();
	int changed     = FALSE;

	_set_cur->s_starts_fast = starts_fast;
	_set_cur->s_scan_period = scan_period;
	_set_cur->s_threshold   = threshold;
	_set_cur->s_min_time    = min_time;
	_set_cur->s_max_time    = max_time;

	if ( _set_data->sd_initialized == FALSE ) {
		_set_data->sd_initialized = TRUE;
		_set_new->s_starts_fast   = _set_cur->s_starts_fast;
		_set_new->s_scan_period   = _set_cur->s_scan_period;
		_set_new->s_threshold     = _set_cur->s_threshold;
		_set_new->s_min_time      = _set_cur->s_min_time;
		_set_new->s_max_time      = _set_cur->s_max_time;
	}
	else {
		gacx_settings_value_update (  _set_cur->s_starts_fast,
                                     &_set_new->s_starts_fast,
                                     &starts_fast,
                                     &changed );
		gacx_settings_value_update (  _set_cur->s_scan_period,
                                     &_set_new->s_scan_period,
                                     &scan_period,
                                     &changed );
		gacx_settings_value_update (  _set_cur->s_threshold  ,
                                     &_set_new->s_threshold  ,
                                     &threshold  ,
                                     &changed );
		gacx_settings_value_update (  _set_cur->s_min_time   ,
                                     &_set_new->s_min_time   ,
                                     &min_time   ,
                                     &changed );
		gacx_settings_value_update (  _set_cur->s_max_time   ,
                                     &_set_new->s_max_time   ,
                                     &max_time   ,
                                     &changed );
	}

	if ( changed == FALSE ) {
		_set_data->sd_changed = FALSE;
	}

	gacx_settings_set_check ( starts_fast );
	gacx_settings_set_value ( gacx_setting_channel    , scan_period );
	gacx_settings_set_value ( gacx_setting_packets    , threshold   );
	gacx_settings_set_value ( gacx_setting_seconds_min, min_time    );
	gacx_settings_set_value ( gacx_setting_seconds_max, max_time    );

	gacx_settings_enable_buttons ();
}

/***************************************************************************/

void gacx_settings_seconds_changed ( gacx_setting setting, int value )
{
	int value_min = 0;
	int value_max = 0;
	switch ( setting ) {
	case gacx_setting_seconds_min:
		value_min = value;
		value_max = gtk_range_get_value ( GTK_RANGE ( _set_data->sd_range_seconds_max ) );
		if ( value_min >= value_max ) {
			value_max = value_min + 1;
			gtk_range_set_value          ( GTK_RANGE ( _set_data->sd_range_seconds_max ), value_max );
			gtk_spin_button_set_value    ( GTK_SPIN_BUTTON ( _set_data->sd_spin_seconds_max ), value_max );
			gacx_settings_save_new_value ( gacx_setting_seconds_max, value_max );
		}
		break;
	case gacx_setting_seconds_max:
		value_max = value;
		value_min = gtk_range_get_value ( GTK_RANGE ( _set_data->sd_range_seconds_min ) );
		if ( value_max <= value_min ) {
			value_min = value_max - 1;
			gtk_range_set_value          ( GTK_RANGE ( _set_data->sd_range_seconds_min ), value_min );
			gtk_spin_button_set_value    ( GTK_SPIN_BUTTON ( _set_data->sd_spin_seconds_min ), value_min );
			gacx_settings_save_new_value ( gacx_setting_seconds_min, value_min );
		}
		break;
	default:
		break;
	}
}

/***************************************************************************/

void gacx_settings_range_changed ( gacx_setting setting )
{
	GtkRange*      range = NULL;
	GtkSpinButton* spin  = NULL;
	int            value = 0;

	gacx_settings_get_widgets ( setting, &range, &spin );

	if ( range && spin ) {
		value = gtk_range_get_value ( range );
		gtk_spin_button_set_value ( spin, value );
		gacx_settings_save_new_value ( setting, value );
		gacx_settings_seconds_changed ( setting, value );
	}
}

/***************************************************************************/

void gacx_settings_spin_changed ( gacx_setting setting )
{
	GtkRange*      range = NULL;
	GtkSpinButton* spin  = NULL;
	int            value = 0;

	gacx_settings_get_widgets ( setting, &range, &spin );

	if ( range && spin ) {
		value = gtk_spin_button_get_value ( spin );
		gtk_range_set_value ( range, value );
		gacx_settings_save_new_value ( setting, value );
		gacx_settings_seconds_changed ( setting, value );
	}
}

/***************************************************************************/

void gacx_settings_check_changed ()
{
	gacx_settings_save_new_value ( gacx_setting_rate,
                                   gtk_toggle_button_get_active (
                                   GTK_TOGGLE_BUTTON ( _set_data->sd_check_rate ) ) );
}

/***************************************************************************/

int gacx_settings_privileges_check ()
{
	GtkWidget* main_dialog = NULL;
	int result = 0;
	seteuid ( 0 );
	if ( geteuid () != 0 ) {
		main_dialog = create_main_dialog ();
		gtk_widget_show ( main_dialog );
		result = 1;
	}
	return result;
}

/***************************************************************************/

void gacx_settings_apply ()
{
	if ( ! gacx_settings_privileges_check () ) {
		acx_set_starts_fast ( _set_new->s_starts_fast );
		acx_set_scan_period ( _set_new->s_scan_period );
		acx_set_threshold   ( _set_new->s_threshold   );
		acx_set_min_time    ( _set_new->s_min_time    );
		acx_set_max_time    ( _set_new->s_max_time    );

		gacx_settings_cancel ();
	}
}

/***************************************************************************/

void gacx_settings_cancel ()
{
	gacx_settings_data_reset  ();
	gacx_settings_data_update ();
}

/***************************************************************************/

void gacx_update_entry ( GtkWidget* entry, gint val )
{
	gchar* text = NULL;
	text = g_strdup_printf ( "%d", val );
    gtk_entry_set_text ( GTK_ENTRY ( entry ), text );
	g_free  ( text );
}

/***************************************************************************/
