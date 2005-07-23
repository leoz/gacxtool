/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * ACX Library
 *
 * $Id: acxlib.h,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#ifndef __ACXLIB_H__
#define __ACXLIB_H__

/***************************************************************************/

#define ACX_NO_ERROR            0
#define ACX_IFACE_OPEN_ERROR    1
#define ACX_IOCTL_ERROR         2

typedef enum acx_rate {
	acx_rate_1 = 0,
	acx_rate_2,
	acx_rate_5,
	acx_rate_11,
	acx_rate_22
} acx_rate;

typedef struct acx_interface_stat {
	int  is_strength;
	int  is_strength_avg;
	int  is_strength_max;
	int  is_noise;
	int  is_noise_avg;
	int  is_noise_max;
	long is_bytes_received; /* total */
	long is_bytes_sent;     /* total */
	int  is_rates;          /* supported rates */
} acx_interface_stat;

char* acx_interface_default  ();
int   acx_interface_open     ( const char* name );
int   acx_interface_close    ();
int   acx_interface_get_stat ( acx_interface_stat* stat );
int   acx_rate_supported     ( acx_rate rate, int rates );
int   acx_user_level         ( int rawlevel );

char* net_wi_get_bssid   ();
char* net_wi_get_status  ( const char* bssid );
int   net_wi_get_txrate  ();
int   net_wi_get_channel ();

char* net_80211_get_ssid ();

char* net_get_media_status ();

/***************************************************************************/

int acx_get_starts_fast ();
int acx_get_scan_period ();
int acx_get_threshold   ();
int acx_get_min_time    ();
int acx_get_max_time    ();

void acx_set_starts_fast ( int value );
void acx_set_scan_period ( int value );
void acx_set_threshold   ( int value );
void acx_set_min_time    ( int value );
void acx_set_max_time    ( int value );

/***************************************************************************/

#endif /* __ACXLIB_H__ */
