/****************************************************************************
 * Copyright (C) 2004 Leonid Zolotarev
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * GTK ACX Tool.
 *
 * Main.
 *
 * $Id: main.c,v 1.2 2005-09-01 23:07:15 zoleo Exp $
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <unistd.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"
#include "gacxopt.h"
#include "gacxmain.h"
#include "gacxtimer.h"
#include "acxlib.h"

/***************************************************************************/

static char* _id = "$Id: main.c,v 1.2 2005-09-01 23:07:15 zoleo Exp $";

/***************************************************************************/

void gacx_main_initialize ( GtkWidget* parent )
{
	GtkWidget* widget = GTK_WIDGET ( lookup_widget ( parent,
                                     "label_about_title" ) );
	gchar* text = NULL;
	text = g_strdup_printf (
           "<span size=\"x-large\"><b>GTK ACX Tool %d.%d.%d</b></span>",
           GACXTOOL_MAJOR, GACXTOOL_MINOR, GACXTOOL_MICRO );
    gtk_label_set_markup ( GTK_LABEL ( widget ), text );
	g_free  ( text );
}

/***************************************************************************/

void gacx_main_usage ()
{
	g_printf ( "usage: gacxtool\n" );
	g_printf ( "       gacxtool interface\n" );
	g_printf ( "       gacxtool -i interface\n" );
	g_printf ( "       gacxtool -b bandwidth\n" );
	g_printf ( "       gacxtool -d delay\n" );
	g_printf ( "       gacxtool -h\n" );
	g_printf ( "       gacxtool -r\n" );
	g_printf ( "       gacxtool -v\n" );
	g_printf ( "       gacxtool -t timeout\n" );
}

/***************************************************************************/

int main (int argc, char *argv[])
{
	GtkWidget* main_window = NULL;
	int        ch          = 0;
	/* Options. */
	gacx_options_initialize ();
	/* Get the interface name. */
	opterr = 0;
	ch = getopt ( argc, argv, "i:" );
	if ( ch == 'i' ) {
		_gacx_options.o_iface_name = optarg;
	} else {
		if ( argc > 1 && *argv [ 1 ] != '-' ) {
			_gacx_options.o_iface_name = argv [ 1 ];
			optind = 2; 
		} else {
			optind = 1;
		}
		#ifndef __linux__
		optreset = 1;
		#endif /* __linux__ */
	}
	/* Input parameters setup. */
	while ( ( ch = getopt (argc, argv, "b:d:hrvt:" ) ) != -1 ) {
    	switch ( ch ) {
    	case 'b':
         	_gacx_options.o_bandwidth = atoi ( optarg );
    		break;
    	case 'd':
        	_gacx_options.o_delay     = atoi ( optarg );
        	break;
        case 'r':
        	_gacx_options.o_rawdata   = GACX_FLAG_OFF;
        	break;
        case 'v':
        	_gacx_options.o_verbose   = GACX_FLAG_ON;
        	break;
        case 't':
        	_gacx_options.o_timeout   = atoi ( optarg );
        	break;
        case '?':
        	if ( isprint ( optopt ) ) {
          		fprintf ( stderr,
          		          "Unknown option '-%c'.\n", optopt );
			}
        	else {
          		fprintf ( stderr,
          		          "Unknown option character '\\x%x'.\n", optopt );
			}
		case 'h':
		default:
			gacx_main_usage ();
        	return 1;
		}
	}
	/* Correct options. */
	gacx_options_correct ();
	/* Gettext setup. */
	#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
	#endif /* ENABLE_NLS */
	/* Theme setup. */
	gtk_rc_parse (PACKAGE_DATA_DIR "/" PACKAGE "/themes/default/default.gtkrc");
	/* Locale setup. */
	gtk_set_locale ();
	gtk_init (&argc, &argv);
	add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/icons");
	/* Set default interface. */
	if ( ! _gacx_options.o_iface_name ) {
		_gacx_options.o_iface_name = acx_interface_default ();
	}
	/* Print out options. */
	gacx_options_trace ();
	/*
	 * The following code was added by Glade to create one of each component
	 * (except popup menus), just so that you see something after building
	 * the project. Delete any components that you don't want shown initially.
	 */
	main_window = create_main_window ();
	gacx_timer_data_create  ( main_window );
	gacx_main_initialize    ( main_window );
	gtk_widget_show         ( main_window );
	gtk_main ();
	/* Options. */
	gacx_options_finalize ();
	return 0;
}

/***************************************************************************/
