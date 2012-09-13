/*D***********************************************************
 * copyright: yafra.org, Switzerland, 2004
 *
 * modul:     travelDB GTK user interface
 * GTK func:  callback
 * describe:  pressed OK and CANCEL
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.4 $
 **************************************************************/
static char rcsid[]="$Id: cb-mainwin.c,v 1.4 2004-03-05 14:23:33 mwn Exp $";

#include <gtk/gtk.h>
#include <stdio.h>

#ifdef ps_unix
#ifndef ps_cygwin
#include <unistd.h>
#endif
#include <sys/types.h>
#include <pwd.h>
#endif

#include "callbacks.h"
#include "interface.h"
#include "support.h"

/* travelDB GTK GUI includes */
#include <mpgtk.h>

#define CHK_CONNECT_OK 0
#define CHK_CONNECT_ERROR 1
#define SERVBUFSIZE 1024

/* global variables */
// extern int errno;
// extern char *sys_errlist[];
extern int dialogsprache;
extern int outputsprache;
extern int sprache;
extern char sqlquery[];
extern int aktuellesprache;
extern char   argbuffer[2*_RECORDLEN];
extern char   messageBuffer[8*_RECORDLEN];
extern unsigned char bm_obj;
extern PSmemobj outputmem;

void on_mb_save_activate(GtkMenuItem * menuitem,
                         gpointer user_data)
{

}


void on_mb_print_activate(GtkMenuItem * menuitem,
                          gpointer user_data)
{

}


void on_mb_exit_activate(GtkMenuItem * menuitem,
                         gpointer user_data)
{
	extern int DebugFlag;
	GtkWidget *exit;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "menu exit pressed");

	/* create main user interface */
	exit = create_tdb_exit();
	gtk_widget_show(exit);
}


void on_mb_copy_activate(GtkMenuItem * menuitem,
                         gpointer user_data)
{

}


void on_mp_cut_activate(GtkMenuItem * menuitem,
                        gpointer user_data)
{

}


void on_mb_past_activate(GtkMenuItem * menuitem,
                         gpointer user_data)
{

}


void on_mb_opts_activate(GtkMenuItem * menuitem,
                         gpointer user_data)
{
	extern int DebugFlag;
	GtkWidget *opts;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "menu options pressed");

	/* create main user interface */
	opts = create_tdb_opts();
	gtk_widget_show(opts);

}


void on_mb_package_activate(GtkMenuItem * menuitem,
                            gpointer user_data)
{

}


void on_mb_service_activate(GtkMenuItem * menuitem,
                            gpointer user_data)
{

}


void on_mb_reservation_activate(GtkMenuItem * menuitem,
                                gpointer user_data)
{

}


void on_mb_flight_activate(GtkMenuItem * menuitem,
                           gpointer user_data)
{

}


void on_mb_lang_activate(GtkMenuItem * menuitem,
                         gpointer user_data)
{
	extern int DebugFlag;
	GtkWidget *lang;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "menu lang pressed");

	/* create main user interface */
	lang = create_tdb_langwin();
	gtk_widget_show(lang);

}


void on_mb_about_activate(GtkMenuItem * menuitem,
                          gpointer user_data)
{
	extern int DebugFlag;
	GtkWidget *about;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "menu about pressed");

	/* create main user interface */
	about = create_tdb_about();
	gtk_widget_show(about);
}
