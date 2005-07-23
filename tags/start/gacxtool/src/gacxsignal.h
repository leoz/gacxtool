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
 * $Id: gacxsignal.h,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#ifndef __GACXSIGNAL_H__
#define __GACXSIGNAL_H__

/***************************************************************************/

#include "acxlib.h"
#include "gacxtimer.h"

/***************************************************************************/

void gacx_delay_gui_proc_signal ( gacx_timer_data*    data,
                                  acx_interface_stat* stat );

/***************************************************************************/

#endif /* __GACXSIGNAL_H__ */
