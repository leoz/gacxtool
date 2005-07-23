/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Status.
 *
 * $Id: gacxstatus.c,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#include "gacxstatus.h"
#include "gacxopt.h"
#include "acxlib.h"

/***************************************************************************/

void gacx_status_update_main ( GtkWidget* status_bar )
{
	gchar* buff = NULL;
	buff = g_strdup_printf ( "Interface status: %s", net_get_media_status () );
	gtk_statusbar_push ( GTK_STATUSBAR ( status_bar ), 0, buff );
	g_free ( buff );
}

/***************************************************************************/

void gacx_status_update_device ( GtkWidget* status_bar )
{
	gchar* buff = NULL;
	buff = g_strdup_printf ( "Device: %s", _gacx_options.o_iface_name );
	gtk_statusbar_push ( GTK_STATUSBAR ( status_bar ), 0, buff );
	g_free ( buff );
}

/***************************************************************************/

void gacx_status_update_user ( GtkWidget* status_bar )
{
	gchar* buff = NULL;
	buff = g_strdup_printf ( "User: %s (%s)", g_get_user_name (), g_get_real_name () );
	gtk_statusbar_push ( GTK_STATUSBAR ( status_bar ), 0, buff );
	g_free ( buff );
}

/***************************************************************************/
