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
 * $Id: gacxstatus.h,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#ifndef __GACXSTATUS_H__
#define __GACXSTATUS_H__

/***************************************************************************/

#include <gtk/gtk.h>

/***************************************************************************/

void gacx_status_update_main   ( GtkWidget* status_bar );
void gacx_status_update_device ( GtkWidget* status_bar );
void gacx_status_update_user   ( GtkWidget* status_bar );

/***************************************************************************/

#endif /* __GACXSTATUS_H__ */
