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
static char rcsid[]="$Id: cb-about-exit.c,v 1.4 2004-03-05 14:23:33 mwn Exp $";

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

/* MARCO POLO GTK GUI includes */
#include <mpgtk.h>


void on_b_about_close_clicked(GtkButton * button,
                              gpointer user_data)
{
	extern int DebugFlag;
	GtkWidget *about;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "about close and hide dialog");

	about = lookup_widget( GTK_WIDGET(button), "tdb_about");
	gtk_widget_hide(about);
	/*	gtk_widget_destroy(about); */


}


void on_b_exit_cancel_clicked(GtkButton * button,
                              gpointer user_data)
{
	extern int DebugFlag;
	GtkWidget *exit;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "exit cancel and hide dialog");

	exit = lookup_widget( GTK_WIDGET(button), "tdb_exit");
	gtk_widget_hide(exit);
	/*	gtk_widget_destroy(exit); */

}


void on_b_exit_ok_clicked(GtkButton * button,
                          gpointer user_data)
{
	/* finish */
	MPGTKexit(MPOK);
}


