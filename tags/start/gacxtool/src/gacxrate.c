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
 * $Id: gacxrate.c,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#include "support.h"
#include "acxlib.h"
#include "gacxrate.h"

/***************************************************************************/

gacx_rate_data* _rate_data = NULL;

/***************************************************************************/

void gacx_rate_data_create ( GtkWidget* main_window )
{
	if ( ! _rate_data ) {
    	_rate_data = g_malloc ( sizeof ( gacx_rate_data ) );
		_rate_data->rd_1   = lookup_widget ( main_window, "eventbox_rate_1"  );
		_rate_data->rd_2   = lookup_widget ( main_window, "eventbox_rate_2"  );
		_rate_data->rd_5   = lookup_widget ( main_window, "eventbox_rate_5"  );
		_rate_data->rd_11  = lookup_widget ( main_window, "eventbox_rate_11" );
		_rate_data->rd_22  = lookup_widget ( main_window, "eventbox_rate_22" );
		_rate_data->rd_f1  = lookup_widget ( main_window, "frame_rate_1"  );
		_rate_data->rd_f2  = lookup_widget ( main_window, "frame_rate_2"  );
		_rate_data->rd_f5  = lookup_widget ( main_window, "frame_rate_5"  );
		_rate_data->rd_f11 = lookup_widget ( main_window, "frame_rate_11" );
		_rate_data->rd_f22 = lookup_widget ( main_window, "frame_rate_22" );
		_rate_data->rd_rates = 0;
	}
}

/***************************************************************************/

void gacx_rate_data_destroy ()
{
	if ( _rate_data ) {
		_rate_data->rd_1   = NULL;
		_rate_data->rd_2   = NULL;
		_rate_data->rd_5   = NULL;
		_rate_data->rd_11  = NULL;
		_rate_data->rd_22  = NULL;
		_rate_data->rd_f1  = NULL;
		_rate_data->rd_f2  = NULL;
		_rate_data->rd_f5  = NULL;
		_rate_data->rd_f11 = NULL;
		_rate_data->rd_f22 = NULL;
		_rate_data->rd_rates = 0;
		g_free ( _rate_data );
		_rate_data = NULL;
	}
}

/***************************************************************************/

void gacx_rate_data_update_current ()
{
	GdkColor color_enable;
	GdkColor color_disable;
	GdkColor color;
	gint rate = 0;
	if ( _rate_data ) {
		color_enable  = _rate_data->rd_color_enable;
		color_disable = _rate_data->rd_color_disable;
		rate = net_wi_get_txrate ();
		if ( rate == 1 ) {
			color = color_enable;
		}
		else {
			color = color_disable;
		}
		gtk_widget_modify_bg ( _rate_data->rd_1, GTK_STATE_NORMAL, &color );
		if ( rate == 2 ) {
			color = color_enable;
		}
		else {
			color = color_disable;
		}
		gtk_widget_modify_bg ( _rate_data->rd_2, GTK_STATE_NORMAL, &color );
		if ( rate > 2 && rate <= 6 ) {
			color = color_enable;
		}
		else {
			color = color_disable;
		}
		gtk_widget_modify_bg ( _rate_data->rd_5, GTK_STATE_NORMAL, &color );
		if ( rate > 6 && rate <= 11 ) {
			color = color_enable;
		}
		else {
			color = color_disable;
		}
		gtk_widget_modify_bg ( _rate_data->rd_11, GTK_STATE_NORMAL, &color );
		if ( rate >= 22 ) {
			color = color_enable;
		}
		else {
			color = color_disable;
		}
		gtk_widget_modify_bg ( _rate_data->rd_22, GTK_STATE_NORMAL, &color );
	}
}

/***************************************************************************/

void gacx_rate_data_update_rates ( gint rates )
{
	GtkStyle* style  = NULL;
	if ( _rate_data ) {
		if ( _rate_data->rd_rates == 0 && _rate_data->rd_1 ) {
			style = gtk_widget_get_style ( _rate_data->rd_1 );
			if ( style ) {
				_rate_data->rd_color_enable  = style->bg [ GTK_STATE_PRELIGHT ];
				_rate_data->rd_color_disable = style->bg [ GTK_STATE_SELECTED ];
			}
		}
		if ( _rate_data->rd_rates != rates ) {
			_rate_data->rd_rates = rates;
			if ( acx_rate_supported ( acx_rate_1, rates ) ) {
				gtk_widget_show ( _rate_data->rd_f1 );
			}
			else {
				gtk_widget_hide ( _rate_data->rd_f1 );
			}
			if ( acx_rate_supported ( acx_rate_2, rates ) ) {
				gtk_widget_show ( _rate_data->rd_f2 );
			}
			else {
				gtk_widget_hide ( _rate_data->rd_f2 );
			}
			if ( acx_rate_supported ( acx_rate_5, rates ) ) {
				gtk_widget_show ( _rate_data->rd_f5 );
			}
			else {
				gtk_widget_hide ( _rate_data->rd_f5 );
			}
			if ( acx_rate_supported ( acx_rate_11, rates ) ) {
				gtk_widget_show ( _rate_data->rd_f11 );
			}
			else {
				gtk_widget_hide ( _rate_data->rd_f11 );
			}
			if ( acx_rate_supported ( acx_rate_22, rates ) ) {
				gtk_widget_show ( _rate_data->rd_f22 );
			}
			else {
				gtk_widget_hide ( _rate_data->rd_f22 );
			}
		}
	}
}

/***************************************************************************/

void gacx_rate_data_update ( gint rates )
{
	gacx_rate_data_update_rates ( rates );
	gacx_rate_data_update_current ();
}

/***************************************************************************/

