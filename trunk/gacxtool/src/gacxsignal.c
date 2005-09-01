/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Signal widgets.
 *
 * $Id: gacxsignal.c,v 1.2 2005-09-01 23:07:15 zoleo Exp $
 ***************************************************************************/

#include "gacxopt.h"
#include "gacxbox.h"
#include "gacxsignal.h"

/***************************************************************************/

void gacx_update_bar_percent ( GtkWidget* bar, gint percent )
{
	gchar*  text = NULL;
	gdouble val  = 0.0;
	if ( percent > 100 ) {
		percent = 100;
	}
	else if ( percent < 0 ) {
		percent = 0;
	}
	val = percent * 0.01;
	gtk_progress_bar_set_fraction ( GTK_PROGRESS_BAR ( bar ), val );
	text = g_strdup_printf ( "%d%%", percent );
    gtk_progress_bar_set_text ( GTK_PROGRESS_BAR ( bar ), text );
	g_free  ( text );
}

/***************************************************************************/

void gacx_delay_gui_proc_signal ( gacx_timer_data*    data,
                                  acx_interface_stat* stat )
{
	gint val_quality  = _val_quality  / _gacx_options.o_delay;
	gint val_strength = _val_strength / _gacx_options.o_delay;
	gint val_noise    = _val_noise    / _gacx_options.o_delay;

	gacx_update_bar_percent ( data->td_bar_quality , val_quality  );
	gacx_update_bar_percent ( data->td_bar_strength, val_strength );
	gacx_update_bar_percent ( data->td_bar_noise   , val_noise    );

	gacx_signal_databox_data_set ( val_quality, val_strength, val_noise );

	gacx_update_entry ( data->td_ent_strength    , stat->is_strength     );
	gacx_update_entry ( data->td_ent_strength_avg, stat->is_strength_avg );
	gacx_update_entry ( data->td_ent_strength_max, stat->is_strength_max );

	gacx_update_entry ( data->td_ent_noise       , stat->is_noise        );
	gacx_update_entry ( data->td_ent_noise_avg   , stat->is_noise_avg    );
	gacx_update_entry ( data->td_ent_noise_max   , stat->is_noise_max    );
}

/***************************************************************************/
