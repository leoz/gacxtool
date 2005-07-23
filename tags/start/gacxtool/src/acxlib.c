/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * ACX Library
 *
 * $Id: acxlib.c,v 1.1.1.1 2005-07-23 23:16:11 zoleo Exp $
 ***************************************************************************/

#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_media.h>
#include <net80211/ieee80211.h>
#include <net80211/ieee80211_ioctl.h>
#include <dev/wi/if_wavelan_ieee.h>
#include <acx/if_acxioctl.h>
#include "acxlib.h"

#define ACX_IFACE_NAME    "acx0"

char* _acx_iface_name = NULL;
int   _acx_iface_sock = -1;

char* acx_interface_default ()
{
	/* FIX ME ! */
	return ACX_IFACE_NAME;
}

int acx_interface_open ( const char* name )
{
	if ( ! _acx_iface_name && name ) {
		_acx_iface_name = malloc ( sizeof ( char ) * IFNAMSIZ );
		bzero ( _acx_iface_name, sizeof ( char ) * IFNAMSIZ );
		memcpy ( _acx_iface_name, name, sizeof ( name ) );
	}
	if ( _acx_iface_sock == -1 ) {
		_acx_iface_sock = socket ( AF_INET, SOCK_DGRAM, 0 );
	}
	if ( _acx_iface_name && _acx_iface_sock > -1 ) {
		return ACX_NO_ERROR;
	}
	return ACX_IFACE_OPEN_ERROR;
}

int acx_interface_close ()
{
	if ( _acx_iface_name ) {
		free ( _acx_iface_name );
		_acx_iface_name = NULL;
	}
	if ( _acx_iface_sock > -1 ) {
		close ( _acx_iface_sock );
		_acx_iface_sock = -1;
	}
	return ACX_NO_ERROR;
}

/*
 * Set/Get
 */
int acx_sgioc ( u_int16_t i_type, void *i_data )
{
    struct ieee80211req	ireq;      
    bzero ( &ireq, sizeof ( ireq ) );
    strncpy ( ireq.i_name, _acx_iface_name, IFNAMSIZ );

    ireq.i_data = (void *)    i_data;
    ireq.i_type = (u_int16_t) i_type;
    ireq.i_val  = (int16_t)   0;
    ireq.i_len  = (int16_t)   0;

    if ( ioctl ( _acx_iface_sock, ACX_IOCTL_SGIOC, &ireq ) < 0 ) {
        return ACX_IOCTL_ERROR;
    }
    return ACX_NO_ERROR;
}

/*
 * Get
 */
int net_wi_gioc ( struct wi_req *wreq )
{
	struct ifreq ifr;
    bzero ( &ifr, sizeof ( ifr ) );
    strncpy ( ifr.ifr_name, _acx_iface_name, IFNAMSIZ );

	ifr.ifr_data = ( caddr_t ) wreq;

    if ( ioctl ( _acx_iface_sock, SIOCGWAVELAN, &ifr ) < 0 ) {
        return ACX_IOCTL_ERROR;
    }
    return ACX_NO_ERROR;
}

/*
 * Calculate level as windows driver (feb 2003)
 */
int acx_user_level ( int rawlevel )
{
	int winlevel= ( int ) ( 0.5 + 0.625 * rawlevel );
	if ( winlevel > 100 ) {
		winlevel = 100;
	}
	return winlevel;
}

int acx_interface_get_stat ( acx_interface_stat* stat )
{
    int result = ACX_NO_ERROR;
    struct acx_ioctl_stats stats;
    bzero ( &stats, sizeof ( stats ) );
	if ( stat ) {
	    bzero ( stat, sizeof ( acx_interface_stat ) );
	    result = acx_sgioc ( ACX_IOCTL_GET_STATS, &stats );
		if ( result == ACX_NO_ERROR ) {
			stat->is_strength       = stats.rx_levelcurrent;
			stat->is_strength_avg   = stats.rx_level / stats.rx_count;
			stat->is_strength_max   = stats.rx_levelmax;
			stat->is_noise          = stats.rx_snrcurrent;
			stat->is_noise_avg      = stats.rx_snr   / stats.rx_count;
			stat->is_noise_max      = stats.rx_snrmax;
			stat->is_bytes_received = stats.rx_bytes;
			stat->is_bytes_sent     = stats.tx_bytes;
			stat->is_rates          = stats.tx_rates;
		}
	}
	return result;
}

int acx_rate_supported ( acx_rate rate, int rates )
{
	int result = 0;
	switch ( rate ) {
	case acx_rate_1:
		result = ( ( rates & ACX_IOCTL_1MBPS ) == ACX_IOCTL_1MBPS );
		break;
	case acx_rate_2:
		result = ( ( rates & ACX_IOCTL_2MBPS ) == ACX_IOCTL_2MBPS );
		break;
	case acx_rate_5:
		result = ( ( rates & ACX_IOCTL_5MBPS ) == ACX_IOCTL_5MBPS );
		break;
	case acx_rate_11:
		result = ( ( rates & ACX_IOCTL_11MBPS ) == ACX_IOCTL_11MBPS );
		break;
	case acx_rate_22:
		result = ( ( rates & ACX_IOCTL_22MBPS ) == ACX_IOCTL_22MBPS );
		break;
	default:
		break;
	}
	return result;
}

#define ACX_BSSID_LEN 20

char* net_wi_get_bssid ()
{
	int i = 0;

    static char bssid [ ACX_BSSID_LEN + 1 ];
    static char buff  [ ACX_BSSID_LEN + 1 ];
	static unsigned char* c = NULL;

    struct wi_req wreq;
    bzero ( &wreq, sizeof ( wreq ) );
	wreq.wi_len  = WI_MAX_DATALEN;
	wreq.wi_type = WI_RID_CURRENT_BSSID;

    bzero ( bssid, sizeof ( bssid ) );

	if ( net_wi_gioc ( &wreq ) == ACX_NO_ERROR ) {
		c = ( unsigned char* ) &wreq.wi_val;

		for ( i = 0; i < (wreq.wi_len - 1) * 2; i++ ) {
		    bzero   ( buff, sizeof ( buff ) );
			sprintf ( buff, "%02X", c [ i ] );
			strcat ( bssid, buff );
			if ( i < ( ( wreq.wi_len - 1 ) * 2 ) - 1 ) {
				strcat ( bssid, ":" );
			}
		}
	}

	return bssid;
}

#define ACX_BSSID_EMPTY "00:00:00:00:00:00"

char* net_wi_get_status ( const char* bssid )
{
	if ( strcmp ( bssid, ACX_BSSID_EMPTY ) != 0 ) {
		return "Associated";
	}
	return "Not Associated";
}

#define ACX_BUFF_LEN 10

int net_wi_words_to_int ( struct wi_req *wreq )
{
	int i = 0;

	static char buff_res [ ACX_BUFF_LEN ];
	static char buff_tmp [ ACX_BUFF_LEN ];
	bzero ( buff_res, sizeof ( buff_res ) );

	for ( i = 0; i < wreq->wi_len - 1; i++) {
		bzero ( buff_tmp, sizeof ( buff_tmp ) );
		sprintf ( buff_tmp, "%d", wreq->wi_val [ i ] );
		strcat  ( buff_res, buff_tmp );
	}
	return strtoimax ( buff_res, NULL, 10 );
}

int net_wi_get_txrate ()
{
    struct wi_req wreq;
    bzero ( &wreq, sizeof ( wreq ) );
	wreq.wi_len  = WI_MAX_DATALEN;
	wreq.wi_type = WI_RID_CUR_TX_RATE;

	if ( net_wi_gioc ( &wreq ) == ACX_NO_ERROR ) {
		return net_wi_words_to_int ( &wreq );
	}

	return 0;
}

int net_wi_get_channel ()
{
    struct wi_req wreq;
    bzero ( &wreq, sizeof ( wreq ) );
	wreq.wi_len  = WI_MAX_DATALEN;
	wreq.wi_type = WI_RID_CURRENT_CHAN;

	if ( net_wi_gioc ( &wreq ) == ACX_NO_ERROR ) {
		return net_wi_words_to_int ( &wreq );
	}

	return 0;
}

char* net_80211_get_ssid ()
{
    static char ssid [ IEEE80211_NWID_LEN + 1 ];

    struct ieee80211req	ireq;      
    bzero ( &ireq, sizeof ( ireq ) );
    strncpy ( ireq.i_name, _acx_iface_name, IFNAMSIZ );

    bzero ( ssid, sizeof ( ssid ) );

    ireq.i_data = &ssid;                /* buffer for SSID */
    ireq.i_type = IEEE80211_IOC_SSID;   /* request SSID */
    ireq.i_val  = -1;                   /* require active SSID */
    if ( ioctl ( _acx_iface_sock, SIOCG80211, &ireq ) < 0 ) {
		/* Error */
	    return ssid;
	}
    ssid [ ireq.i_len ] = '\0';
    return ssid;
}

/***************************************************************************/

char* net_get_media_status ()
{
	struct ifmediareq ireq;
    bzero ( &ireq, sizeof ( ireq ) );
    strncpy ( ireq.ifm_name, _acx_iface_name, IFNAMSIZ );

    if ( ioctl ( _acx_iface_sock, SIOCGIFMEDIA, &ireq ) < 0)
        return "Error";

    if ( ! ( ireq.ifm_status & IFM_AVALID ) )
        return "Invalid";

    if ( ! ( ireq.ifm_status & IFM_ACTIVE ) )
        return "Inactive";

    return "Active";
}

/***************************************************************************/

int acx_get_clockrate ()
{
	u_int16_t value = 0;
	size_t    len   = sizeof ( value );
	sysctlbyname ( "kern.clockrate",
                   (void *) &value, &len , NULL, 0 );
	return value;
}

/***************************************************************************/

typedef enum acx_sysctl {
	acx_sysctl_starts_fast = 0,
	acx_sysctl_scan_period,
	acx_sysctl_threshold,
	acx_sysctl_min_time,
	acx_sysctl_max_time
} acx_sysctl;

/***************************************************************************/

const char* _acx_sysctl_name [] = {
	"hw.acx.starts_fast",
	"hw.acx.scan_period",
	"hw.acx.threshold"  ,
	"hw.acx.min_time"   ,
	"hw.acx.max_time"
};

/***************************************************************************/

int acx_get_starts_fast ()
{
	int    value = 0;
	size_t len   = sizeof ( value );
	sysctlbyname ( _acx_sysctl_name [ acx_sysctl_starts_fast ],
                   (void *) &value, &len , NULL, 0 );
	return value;
}

int acx_get_scan_period ()
{
	int    rate  = acx_get_clockrate ();
	int    value = 0;
	size_t len   = sizeof ( value );
	sysctlbyname ( _acx_sysctl_name [ acx_sysctl_scan_period ],
                   (void *) &value, &len , NULL, 0 );
	if ( rate != 0 ) {
		/* convert to milliseconds */
		value = ( value * 1000 ) / rate;
	}
	return value;
}

int acx_get_threshold ()
{
	int    value = 0;
	size_t len   = sizeof ( value );
	sysctlbyname ( _acx_sysctl_name [ acx_sysctl_threshold ],
                   (void *) &value, &len , NULL, 0 );
	return value;
}

int acx_get_min_time ()
{
	int    value = 0;
	size_t len   = sizeof ( value );
	sysctlbyname ( _acx_sysctl_name [ acx_sysctl_min_time ],
                   (void *) &value, &len , NULL, 0 );
	return value;
}

int acx_get_max_time ()
{
	int    value = 0;
	size_t len   = sizeof ( value );
	sysctlbyname ( _acx_sysctl_name [ acx_sysctl_max_time ],
                   (void *) &value, &len , NULL, 0 );
	return value;
}

/***************************************************************************/

void acx_set_starts_fast ( int value )
{
	size_t len = sizeof ( value );
	sysctlbyname ( _acx_sysctl_name [ acx_sysctl_starts_fast ],
                   NULL, NULL, &value, len );
}

void acx_set_scan_period ( int value )
{
	int    rate  = acx_get_clockrate ();
	size_t len   = sizeof ( value );
	/* convert from milliseconds */
	value = ( value * rate ) / 1000;
	sysctlbyname ( _acx_sysctl_name [ acx_sysctl_scan_period ],
                   NULL, NULL, &value, len );
}

void acx_set_threshold ( int value )
{
	size_t len = sizeof ( value );
	sysctlbyname ( _acx_sysctl_name [ acx_sysctl_threshold ],
                   NULL, NULL, &value, len );
}

void acx_set_min_time ( int value )
{
	size_t len = sizeof ( value );
	sysctlbyname ( _acx_sysctl_name [ acx_sysctl_min_time ],
                   NULL, NULL, &value, len );
}

void acx_set_max_time ( int value )
{
	size_t len = sizeof ( value );
	sysctlbyname ( _acx_sysctl_name [ acx_sysctl_max_time ],
                   NULL, NULL, &value, len );
}

/***************************************************************************/
