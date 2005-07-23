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
 * $Id: gacxtimer.c,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#include "support.h"
#include "gacxopt.h"
#include "gacxmain.h"
#include "gacxtimer.h"
#include "gacxsignal.h"
#include "gacxtraffic.h"
#include "gacxrate.h"
#include "gacxbox.h"
#include "gacxset.h"

/***************************************************************************/

gacx_timer_data* _timer_data = 0;

/***************************************************************************/

gdouble gacx_rate_to_kbps ( glong rate,
                            gint  timeout )
{
	gdouble seconds = timeout * 0.001;
	gdouble kbps    = ( rate / 1000 ) / seconds;
	return kbps;
}

/***************************************************************************/

static gint    _val_count        = 0;

static glong   _val_cur_transmit = 0L;
static glong   _val_cur_receive  = 0L;

/***************************************************************************/

gint    _val_quality  = 0;
gint    _val_strength = 0;
gint    _val_noise    = 0;

gdouble _val_transmit = 0.0;
gdouble _val_receive  = 0.0;

/***************************************************************************/

void gacx_delay_proc ( gacx_timer_data* data, acx_interface_stat* stat )
{
	_val_quality  += ( 100 - acx_user_level ( stat->is_noise ) );
	_val_strength += acx_user_level ( stat->is_strength );
	_val_noise    += acx_user_level ( stat->is_noise );
	_val_transmit += gacx_rate_to_kbps (
                                     stat->is_bytes_sent - _val_cur_transmit,
                                     data->td_timeout );
	_val_receive  += gacx_rate_to_kbps (
                                     stat->is_bytes_received - _val_cur_receive,
                                     data->td_timeout );
	_val_count++;
	
	if ( _val_count == _gacx_options.o_delay ) {
		gacx_delay_gui_proc_signal  ( data, stat );
		gacx_delay_gui_proc_traffic ( data, stat );
		_val_quality  = 0;
		_val_strength = 0;
		_val_noise    = 0;
		_val_transmit = 0.0;
		_val_receive  = 0.0;
		_val_count    = 0;
	}
	
	_val_cur_receive  = stat->is_bytes_received;
	_val_cur_transmit = stat->is_bytes_sent;
	
	if ( data->td_state == GACX_CREATED ) {
		data->td_state = GACX_INITIALIZED;
	}
}

/***************************************************************************/

gboolean gacx_timer_proc ( gpointer data )
{
	gchar* val_bssid = NULL;
	acx_interface_stat stat;
	gacx_timer_data* timer_data = ( gacx_timer_data* ) data;
	if ( timer_data && timer_data->td_iface == ACX_NO_ERROR ) {
		if ( acx_interface_get_stat ( &stat ) == ACX_NO_ERROR ) {

			gacx_delay_proc ( timer_data, &stat );
			
			val_bssid = net_wi_get_bssid ();
			gtk_entry_set_text ( GTK_ENTRY ( timer_data->td_ent_status ),
                                 net_wi_get_status ( val_bssid ) );
			gtk_entry_set_text ( GTK_ENTRY ( timer_data->td_ent_bssid  ),
                                 val_bssid );
			gtk_entry_set_text ( GTK_ENTRY ( timer_data->td_ent_ssid   ),
                                 net_80211_get_ssid   () );
			gacx_update_entry ( timer_data->td_ent_channel,
                                net_wi_get_channel () );

			gacx_rate_data_update ( stat.is_rates );
			gacx_settings_data_update ();
		}
		gacx_status_update_main ( _timer_data->td_status_main );
	}
	return TRUE;
} 

/***************************************************************************/

void gacx_hide_raw_data ()
{
	gtk_widget_hide ( _timer_data->td_ent_strength     );
	gtk_widget_hide ( _timer_data->td_ent_strength_avg );
	gtk_widget_hide ( _timer_data->td_ent_strength_max );
	gtk_widget_hide ( _timer_data->td_lab_strength_avg );
	gtk_widget_hide ( _timer_data->td_lab_strength_max );
	gtk_widget_hide ( _timer_data->td_ent_noise        );
	gtk_widget_hide ( _timer_data->td_ent_noise_avg    );
	gtk_widget_hide ( _timer_data->td_ent_noise_max    );
	gtk_widget_hide ( _timer_data->td_lab_noise_avg    );
	gtk_widget_hide ( _timer_data->td_lab_noise_max    );
	gtk_widget_hide ( _timer_data->td_ent_transmit     );
	gtk_widget_hide ( _timer_data->td_ent_receive      );	
}

/***************************************************************************/

void gacx_timer_data_create ( GtkWidget* main_window )
{
	if ( ! _timer_data ) {
    	_timer_data = g_malloc ( sizeof ( gacx_timer_data ) );
		_timer_data->td_iface        = acx_interface_open (
		                                           _gacx_options.o_iface_name );
		_timer_data->td_main_window  = main_window;
		_timer_data->td_bar_quality      = lookup_widget (main_window,
                                                        "quality_progressbar" );
		_timer_data->td_bar_strength     = lookup_widget (main_window,
                                                        "strength_progressbar");
		_timer_data->td_bar_noise        = lookup_widget (main_window,
                                                        "noise_progressbar"   );
		_timer_data->td_ent_strength     = lookup_widget (main_window,
                                                        "strength_entry"      );
		_timer_data->td_ent_strength_avg = lookup_widget (main_window,
                                                        "strength_entry_avg"  );
		_timer_data->td_ent_strength_max = lookup_widget (main_window,
                                                        "strength_entry_max"  );
		_timer_data->td_ent_noise        = lookup_widget (main_window,
                                                        "noise_entry"         );
		_timer_data->td_ent_noise_avg    = lookup_widget (main_window,
                                                        "noise_entry_avg"     );
		_timer_data->td_ent_noise_max    = lookup_widget (main_window,
                                                        "noise_entry_max"     );
		_timer_data->td_ent_status       = lookup_widget (main_window,
                                                        "entry_status"        );
		_timer_data->td_ent_bssid        = lookup_widget (main_window,
                                                        "entry_bssid"         );
		_timer_data->td_ent_ssid         = lookup_widget (main_window,
                                                        "entry_ssid"          );
		_timer_data->td_ent_channel      = lookup_widget (main_window,
                                                        "entry_channel"       );
		_timer_data->td_bar_transmit     = lookup_widget (main_window,
                                                        "transmit_progressbar");
		_timer_data->td_bar_receive      = lookup_widget (main_window,
                                                        "receive_progressbar" );
		_timer_data->td_ent_transmit     = lookup_widget (main_window,
                                                        "transmit_entry");
		_timer_data->td_ent_receive      = lookup_widget (main_window,
                                                        "receive_entry" );
		_timer_data->td_lab_strength_avg = lookup_widget (main_window,
                                                        "strength_label_avg" );
		_timer_data->td_lab_strength_max = lookup_widget (main_window,
                                                        "strength_label_max" );
		_timer_data->td_lab_noise_avg    = lookup_widget (main_window,
                                                        "noise_label_avg" );
		_timer_data->td_lab_noise_max    = lookup_widget (main_window,
                                                        "noise_label_max" );
		_timer_data->td_status_main      = lookup_widget (main_window,
                                                        "main_statusbar"   );
		_timer_data->td_status_device    = lookup_widget (main_window,
                                                        "device_statusbar" );
		_timer_data->td_status_user      = lookup_widget (main_window,
                                                        "user_statusbar" );
		_timer_data->td_state            = GACX_CREATED;
		_timer_data->td_max_rate         = _gacx_options.o_bandwidth;
		_timer_data->td_timeout          = _gacx_options.o_timeout;
		
		gacx_status_update_device ( _timer_data->td_status_device );
		gacx_status_update_user   ( _timer_data->td_status_user   );
		
		if ( _gacx_options.o_rawdata == GACX_FLAG_OFF ) {
			gacx_hide_raw_data ();
		}
		
    	_timer_data->td_timer = g_timeout_add ( _timer_data->td_timeout,
                                                gacx_timer_proc,
                                                _timer_data );
	}
	gacx_rate_data_create     ( main_window );
	gacx_settings_data_create ( main_window );
}

/***************************************************************************/

void gacx_timer_data_destroy ()
{
	gacx_settings_data_destroy ();
	gacx_rate_data_destroy     ();
	if ( _timer_data ) {
		g_source_remove ( _timer_data->td_timer );
		_timer_data->td_state            = GACX_FINALIZED;
		_timer_data->td_timer            = 0;
		_timer_data->td_timeout          = 0;
		_timer_data->td_max_rate         = 0;
		_timer_data->td_main_window      = NULL;
		_timer_data->td_bar_quality      = NULL;
		_timer_data->td_bar_strength     = NULL;
		_timer_data->td_bar_noise        = NULL;
		_timer_data->td_ent_strength     = NULL;
		_timer_data->td_ent_strength_avg = NULL;
		_timer_data->td_ent_strength_max = NULL;
		_timer_data->td_ent_noise        = NULL;
		_timer_data->td_ent_noise_avg    = NULL;
		_timer_data->td_ent_noise_max    = NULL;
		_timer_data->td_ent_status       = NULL;
		_timer_data->td_ent_bssid        = NULL;
		_timer_data->td_ent_ssid         = NULL;
		_timer_data->td_ent_channel      = NULL;
		_timer_data->td_bar_transmit     = NULL;
		_timer_data->td_bar_receive      = NULL;
		_timer_data->td_ent_transmit     = NULL;
		_timer_data->td_ent_receive      = NULL;
		_timer_data->td_lab_strength_avg = NULL;
		_timer_data->td_lab_strength_max = NULL;
		_timer_data->td_lab_noise_avg    = NULL;
		_timer_data->td_lab_noise_max    = NULL;
		_timer_data->td_status_main      = NULL;
		_timer_data->td_status_device    = NULL;
		_timer_data->td_status_user      = NULL;
		_timer_data->td_iface            = acx_interface_close ();
		g_free ( _timer_data );
		_timer_data = NULL;
	}
}

/***************************************************************************/
