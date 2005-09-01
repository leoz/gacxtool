/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Traffic widgets.
 *
 * $Id: gacxtraffic.c,v 1.2 2005-09-01 23:07:15 zoleo Exp $
 ***************************************************************************/

#include "gacxopt.h"
#include "gacxbox.h"
#include "gacxtraffic.h"

/***************************************************************************/

void gacx_update_bar_rate ( GtkWidget* bar,
                            gdouble    kbps,
                            gint       max_rate )
{
	gchar*  text = NULL;
	gdouble val  = kbps / max_rate;
	if ( val > 1.0 ) {
		val = 1.0;
	}
	else if ( val < 0.0 ) {
		val = 0.0;
	}
	gtk_progress_bar_set_fraction ( GTK_PROGRESS_BAR ( bar ), val );
	text = g_strdup_printf ( "%.1f Kbps", kbps );
    gtk_progress_bar_set_text ( GTK_PROGRESS_BAR ( bar ), text );
	g_free  ( text );
}

/***************************************************************************/

void gacx_update_entry_kb ( GtkWidget* entry, long bytes )
{
	gdouble kbs = 0.0;
	gchar* text = NULL;
	if ( bytes < 1024 ) {
		text = g_strdup_printf ( "%d byte", bytes );
	}
	else {
		if ( bytes < 1024 * 1024 ) {
			text = g_strdup_printf ( "%d KB", bytes / 1024 );
		}
		else {
			if ( bytes < 1024 * 1024 * 1024 ) {
				kbs = (gdouble) bytes / (gdouble) ( 1024 * 1024 );
				text = g_strdup_printf ( "%.1f MB", kbs );
			}
			else {
				kbs = (gdouble) bytes / (gdouble) ( 1024 * 1024 * 1024 );
				text = g_strdup_printf ( "%.1f GB", kbs );
			}
		}
	}
    gtk_entry_set_text ( GTK_ENTRY ( entry ), text );
	g_free  ( text );
}

/***************************************************************************/

void gacx_delay_gui_proc_traffic ( gacx_timer_data*    data,
                                   acx_interface_stat* stat )
{
	gdouble val_transmit = _val_transmit  / _gacx_options.o_delay;
	gdouble val_receive  = _val_receive   / _gacx_options.o_delay;

	data->td_max_rate = gacx_get_max_rate ( val_transmit, data->td_max_rate );
	data->td_max_rate = gacx_get_max_rate ( val_receive , data->td_max_rate );

	gacx_update_bar_rate ( data->td_bar_transmit, val_transmit,
	                       data->td_max_rate );
	gacx_update_bar_rate ( data->td_bar_receive, val_receive,
	                       data->td_max_rate );

	gacx_update_entry_kb ( data->td_ent_transmit, stat->is_bytes_sent     );
	gacx_update_entry_kb ( data->td_ent_receive , stat->is_bytes_received );

	if ( data->td_state == GACX_INITIALIZED ) {
		gacx_traffic_databox_data_set ( (gint) val_transmit ,
		                                (gint) val_receive,
		                                 data->td_max_rate );
	}
}

/***************************************************************************/
