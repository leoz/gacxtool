/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Options.
 *
 * $Id: gacxopt.c,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#include "gacxopt.h"
#include "gacxmain.h"

/***************************************************************************/

gacx_options _gacx_options = {};

/***************************************************************************/

void gacx_options_initialize ()
{
	_gacx_options.o_bandwidth   = GACX_DEFAULT_MAX_RATE;
	_gacx_options.o_delay       = GACX_DELAY_MIN;
	_gacx_options.o_rawdata     = GACX_FLAG_ON;
	_gacx_options.o_timeout     = GACX_DEFAULT_TIMEOUT;
	_gacx_options.o_verbose     = GACX_FLAG_OFF;
	_gacx_options.o_iface_name  = NULL;
}

/***************************************************************************/

void gacx_options_finalize ()
{
	/* TBD */
}

/***************************************************************************/

void gacx_options_correct ()
{
	/* Correct delay. */
	if ( _gacx_options.o_delay < GACX_DELAY_MIN ) {
		_gacx_options.o_delay = GACX_DELAY_MIN;
	}
	if ( _gacx_options.o_delay > GACX_DELAY_MAX ) {
		_gacx_options.o_delay = GACX_DELAY_MAX;
	}
}

/***************************************************************************/

void gacx_options_trace ()
{
	if ( _gacx_options.o_verbose == GACX_FLAG_ON ) {
		g_printf ( "Starting for interface %s with delay %d and timeout %d.\n",
		           _gacx_options.o_iface_name,
		           _gacx_options.o_delay,
		           _gacx_options.o_timeout );
		g_printf ( "Initial bandwidth is %d and raw values are%s shown.\n",
		           _gacx_options.o_bandwidth,
		           _gacx_options.o_rawdata == GACX_FLAG_ON ? "" : " not" );
	}
}

/***************************************************************************/
