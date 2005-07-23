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
 * $Id: gacxbox.h,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#ifndef __GACXBOX_H__
#define __GACXBOX_H__

/***************************************************************************/

#include <gtk/gtk.h>
#include <gtkdatabox.h>
#include "gacxmain.h"

/***************************************************************************/

#define GACX_CREATED        0
#define GACX_INITIALIZED    1
#define GACX_FINALIZED     -1

/***************************************************************************/

typedef struct gacx_signal_databox_data {
	gint       sdd_state;
	GtkWidget* sdd_box;
	gfloat*    sdd_X;
	gfloat*    sdd_Y_quality;
	gfloat*    sdd_Y_strength;
	gfloat*    sdd_Y_noise;
} gacx_signal_databox_data;

/***************************************************************************/

typedef struct gacx_traffic_databox_data {
	gint       tdd_state;
	GtkWidget* tdd_box;
	gfloat*    tdd_X;
	gfloat*    tdd_Y_transmit;
	gfloat*    tdd_Y_receive;
	gint       tdd_max_rate;
} gacx_traffic_databox_data;

/***************************************************************************/

void gacx_signal_databox_data_create  ( GtkWidget* databox );
void gacx_signal_databox_data_init    ();
void gacx_signal_databox_data_set     ( gint val_quality,
                                        gint val_strength,
                                        gint val_noise );
void gacx_signal_databox_data_destroy ();

/***************************************************************************/

void gacx_traffic_databox_data_create  ( GtkWidget* databox );
void gacx_traffic_databox_data_init    ();
void gacx_traffic_databox_data_set     ( gint val_transmit,
                                         gint val_receive,
                                         gint max_rate );
void gacx_traffic_databox_data_destroy ();

/***************************************************************************/

gint gacx_get_max_rate ( gdouble kbps,
                         gint    max_rate );

/***************************************************************************/

#endif /* __GACXBOX_H__ */
