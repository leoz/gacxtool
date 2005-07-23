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
 * $Id: gacxtraffic.h,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#ifndef __GACXTRAFFIC_H__
#define __GACXTRAFFIC_H__

/***************************************************************************/

#include "acxlib.h"
#include "gacxtimer.h"

/***************************************************************************/

void gacx_delay_gui_proc_traffic ( gacx_timer_data*    data,
                                   acx_interface_stat* stat );

/***************************************************************************/

#endif /* __GACXTRAFFIC_H__ */
