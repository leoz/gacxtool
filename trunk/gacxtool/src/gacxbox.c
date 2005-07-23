/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Data Box.
 *
 * $Id: gacxbox.c,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#include "gacxbox.h"
#include "gacxopt.h"

/***************************************************************************/

#define GACX_POINTS        200
#define GACX_POINTS_Y      100
#define GACX_DOT_SIZE_GRID 0
#define GACX_STEP_GRID     20

/****************************************************************************
 *                                 Common.                                  *
 ***************************************************************************/

GdkColor gacx_get_widget_color_by_state ( GtkWidget* parent,
                                          const gchar* widget_name,
                                          int state )
{
	GdkColor   color  = { 0, 0, 0 };
	GtkWidget* widget = GTK_WIDGET ( lookup_widget ( parent, widget_name ) );
	GtkStyle*  style  = NULL;
	if ( widget ) {
		style = gtk_widget_get_style ( widget );
		if ( style ) {
			color = style->bg [ state ];
		}
	}
	return color;
}

/***************************************************************************/

GdkColor gacx_get_widget_color ( GtkWidget* parent, const gchar* widget_name )
{
	return gacx_get_widget_color_by_state ( parent,
                                            widget_name,
                                            GTK_STATE_PRELIGHT );
}

/****************************************************************************
 *                             Signal Data Box.                             *
 ***************************************************************************/

#define GACX_SIGNAL_DOT_SIZE 2

static gacx_signal_databox_data* _d_sig = NULL;

void gacx_signal_databox_data_create ( GtkWidget* box )
{
	gint i = 0;

	g_signal_connect ( GTK_OBJECT (box), "destroy",
		               GTK_SIGNAL_FUNC (gtk_databox_data_destroy_all), NULL );

	_d_sig = g_malloc ( sizeof ( gacx_signal_databox_data ) );

	_d_sig->sdd_state      = GACX_CREATED;
	_d_sig->sdd_box        = box;
	_d_sig->sdd_X          = g_new0 (gfloat, GACX_POINTS);
	_d_sig->sdd_Y_quality  = g_new0 (gfloat, GACX_POINTS);
	_d_sig->sdd_Y_strength = g_new0 (gfloat, GACX_POINTS);
	_d_sig->sdd_Y_noise    = g_new0 (gfloat, GACX_POINTS);

	for ( i = 0; i < GACX_POINTS; i++ ) {
		_d_sig->sdd_X          [ i ] = i;
		_d_sig->sdd_Y_quality  [ i ] = 0;
		_d_sig->sdd_Y_strength [ i ] = 0;
		_d_sig->sdd_Y_noise    [ i ] = 0;
	}
}

/***************************************************************************/

void gacx_signal_databox_data_init ()
{
	GdkColor        color   = { 0, 0, 0 };
	GtkDataboxValue val_min = { 0, 0 };
	GtkDataboxValue val_max = { GACX_POINTS, GACX_POINTS_Y };
	int             index   = 0;

	if ( _d_sig && _d_sig->sdd_state == GACX_CREATED ) {

		_d_sig->sdd_state = GACX_INITIALIZED;

		color = gacx_get_widget_color ( _d_sig->sdd_box,
                                        "signal_databox" );
		gtk_databox_set_background_color ( GTK_DATABOX (_d_sig->sdd_box),
                                           color );

		color = gacx_get_widget_color ( _d_sig->sdd_box,
                                        "quality_progressbar" );
		gtk_databox_data_add_x_y ( GTK_DATABOX (_d_sig->sdd_box),
	                               GACX_POINTS,
				                   _d_sig->sdd_X,
	                               _d_sig->sdd_Y_quality,
	                               color, GTK_DATABOX_LINES, GACX_SIGNAL_DOT_SIZE );

		color = gacx_get_widget_color ( _d_sig->sdd_box,
                                        "strength_progressbar" );
		gtk_databox_data_add_y   ( GTK_DATABOX (_d_sig->sdd_box),
	                               GACX_POINTS,
	                               _d_sig->sdd_Y_strength,
	                               0, color, GTK_DATABOX_LINES, GACX_SIGNAL_DOT_SIZE );

		color = gacx_get_widget_color ( _d_sig->sdd_box,
                                        "noise_progressbar" );
		gtk_databox_data_add_y   ( GTK_DATABOX (_d_sig->sdd_box),
	                               GACX_POINTS,
	                               _d_sig->sdd_Y_noise,
	                               0, color, GTK_DATABOX_LINES, GACX_SIGNAL_DOT_SIZE );

		color = gacx_get_widget_color_by_state ( _d_sig->sdd_box,
                                                 "signal_databox",
                                                 GTK_STATE_SELECTED );
		index = gtk_databox_data_add_y ( GTK_DATABOX (_d_sig->sdd_box),
                                         GACX_POINTS,
				                         _d_sig->sdd_Y_noise,
                                         index, color,
                                         GTK_DATABOX_GRID, GACX_DOT_SIZE_GRID );

		gtk_databox_data_set_grid_config ( GTK_DATABOX (_d_sig->sdd_box),
                                           index,
                                           GACX_POINTS_Y / GACX_STEP_GRID - 1,
                                           GACX_POINTS   / GACX_STEP_GRID - 1 );

		gtk_databox_rescale_with_values ( GTK_DATABOX (_d_sig->sdd_box),
					                      val_min,
					                      val_max );
	}
}

/***************************************************************************/

void gacx_signal_databox_data_set ( gint val_quality,
                                    gint val_strength,
                                    gint val_noise )
{
	gint i = 0;

	gacx_signal_databox_data_init ();

	for ( i = 0; i < GACX_POINTS; i++ ) {
		if ( i < GACX_POINTS - 1 ) {
			_d_sig->sdd_Y_quality  [ i ] = _d_sig->sdd_Y_quality  [ i + 1 ];
			_d_sig->sdd_Y_strength [ i ] = _d_sig->sdd_Y_strength [ i + 1 ];
			_d_sig->sdd_Y_noise    [ i ] = _d_sig->sdd_Y_noise    [ i + 1 ];
		}
		else {
			_d_sig->sdd_Y_quality  [ i ] = val_quality;
			_d_sig->sdd_Y_strength [ i ] = val_strength;
			_d_sig->sdd_Y_noise    [ i ] = val_noise;
		}
	}

	gtk_databox_redraw  (GTK_DATABOX (_d_sig->sdd_box));
}

/***************************************************************************/

void gacx_signal_databox_data_destroy ()
{
	g_free ( _d_sig );
}

/****************************************************************************
 *                            Traffic Data Box.                             *
 ***************************************************************************/

#define GACX_TRAFFIC_DOT_SIZE 1
#define GACX_TRAFFIC_GRID     4

static gacx_traffic_databox_data* _d_trf = NULL;

void gacx_traffic_databox_data_create ( GtkWidget* box )
{
	gint i = 0;

	g_signal_connect ( GTK_OBJECT (box), "destroy",
		               GTK_SIGNAL_FUNC (gtk_databox_data_destroy_all), NULL );

	_d_trf = g_malloc ( sizeof ( gacx_traffic_databox_data ) );

	_d_trf->tdd_max_rate   = _gacx_options.o_bandwidth;
	_d_trf->tdd_state      = GACX_CREATED;
	_d_trf->tdd_box        = box;
	_d_trf->tdd_X          = g_new0 (gfloat, _d_trf->tdd_max_rate);
	_d_trf->tdd_Y_transmit = g_new0 (gfloat, _d_trf->tdd_max_rate);
	_d_trf->tdd_Y_receive  = g_new0 (gfloat, _d_trf->tdd_max_rate);

	for ( i = 0; i < _d_trf->tdd_max_rate; i++ ) {
		_d_trf->tdd_X          [ i ] = i;
		_d_trf->tdd_Y_transmit [ i ] = 0;
		_d_trf->tdd_Y_receive  [ i ] = 0;
	}
}

/***************************************************************************/

void gacx_traffic_databox_data_init ()
{
	GdkColor        color   = { 0, 0, 0 };
	GtkDataboxValue val_min = { 0, 0 };
	GtkDataboxValue val_max = { GACX_POINTS, _d_trf->tdd_max_rate };
	int             index   = 0;

	if ( _d_trf && _d_trf->tdd_state == GACX_CREATED ) {

		_d_trf->tdd_state = GACX_INITIALIZED;

		color = gacx_get_widget_color ( _d_trf->tdd_box,
                                        "traffic_databox" );
		gtk_databox_set_background_color ( GTK_DATABOX (_d_trf->tdd_box),
                                           color );

		color = gacx_get_widget_color ( _d_trf->tdd_box,
                                        "transmit_progressbar" );
		gtk_databox_data_add_x_y ( GTK_DATABOX (_d_trf->tdd_box),
	                               _d_trf->tdd_max_rate,
				                   _d_trf->tdd_X,
	                               _d_trf->tdd_Y_transmit,
	                               color, GTK_DATABOX_LINES, GACX_TRAFFIC_DOT_SIZE );

		color = gacx_get_widget_color ( _d_trf->tdd_box,
                                        "receive_progressbar" );
		gtk_databox_data_add_y   ( GTK_DATABOX (_d_trf->tdd_box),
	                               _d_trf->tdd_max_rate,
	                               _d_trf->tdd_Y_receive,
	                               0, color, GTK_DATABOX_LINES, GACX_TRAFFIC_DOT_SIZE );

		color = gacx_get_widget_color_by_state ( _d_trf->tdd_box,
                                                 "traffic_databox",
                                                 GTK_STATE_SELECTED );
		index = gtk_databox_data_add_y ( GTK_DATABOX (_d_trf->tdd_box),
                                         _d_trf->tdd_max_rate,
				                         _d_trf->tdd_Y_receive,
                                         index, color,
                                         GTK_DATABOX_GRID, GACX_DOT_SIZE_GRID );

		gtk_databox_data_set_grid_config ( GTK_DATABOX (_d_trf->tdd_box),
                                           index,
                                           GACX_TRAFFIC_GRID,
                                           _d_trf->tdd_max_rate / GACX_STEP_GRID - 1 );

		gtk_databox_set_selection_enable ( GTK_DATABOX (_d_trf->tdd_box),
                                           FALSE );
		gtk_databox_rescale_with_values ( GTK_DATABOX (_d_trf->tdd_box),
					                      val_min,
					                      val_max );
	}
}

/***************************************************************************/

void gacx_traffic_databox_data_set ( gint val_transmit,
                                     gint val_receive,
                                     gint max_rate )
{
	gint i = 0;

	gdouble val = (gdouble) _d_trf->tdd_max_rate / (gdouble) max_rate;

	gacx_traffic_databox_data_init ();

	for ( i = 0; i < _d_trf->tdd_max_rate; i++ ) {
		if ( i < _d_trf->tdd_max_rate - 1 ) {
			_d_trf->tdd_Y_transmit [ i ] = _d_trf->tdd_Y_transmit [ i + 1 ];
			_d_trf->tdd_Y_receive  [ i ] = _d_trf->tdd_Y_receive  [ i + 1 ];
		}
		else {
			_d_trf->tdd_Y_transmit [ i ] = val_transmit * val;
			_d_trf->tdd_Y_receive  [ i ] = val_receive  * val;
		}
	}

	gtk_databox_rescale (GTK_DATABOX (_d_trf->tdd_box));
	gtk_databox_redraw  (GTK_DATABOX (_d_trf->tdd_box));
}

void gacx_traffic_databox_data_destroy ()
{
	g_free ( _d_trf );
}

/***************************************************************************/

gint gacx_get_max_rate ( gdouble kbps,
                         gint    max_rate )
{
	gdouble val  = kbps / max_rate;
	if ( val > 1.0 ) {
		max_rate = max_rate * 2;
	}
	return max_rate;
}

/***************************************************************************/
