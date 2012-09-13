/*D***********************************************************
 * copyright: yafra.org, Switzerland, 2004
 *
 * modul:     travelDB GTK user interface
 * GTK func:  callback
 * describe:  pressed OK and CANCEL
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.3 $
 **************************************************************/
static char rcsid[]="$Id: cb-language.c,v 1.3 2004-03-05 14:23:33 mwn Exp $";

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

/* travelDB GTK includes */
#include <mpgtk.h>

#define CHK_CONNECT_OK 0
#define CHK_CONNECT_ERROR 1
#define SERVBUFSIZE 1024

void on_b_lang_sel_clicked(GtkButton * button,
                           gpointer user_data)
{
	extern int DebugFlag;
	GtkWidget *sel;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "selection pressed");

	/* create main user interface */
	sel = create_tdb_select();
	gtk_widget_show(sel);

}


void on_b_lang_OK_clicked(GtkButton * button,
                          gpointer user_data)
{

}


void on_b_lang_new_clicked(GtkButton * button,
                           gpointer user_data)
{

}


void on_b_lang_del_clicked(GtkButton * button,
                           gpointer user_data)
{

}


void on_b_lang_clr_clicked(GtkButton * button,
                           gpointer user_data)
{

}


void on_b_lang_close_clicked(GtkButton * button,
                             gpointer user_data)
{
	extern int DebugFlag;
	GtkWidget *langwin;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "close and hide language window");

	langwin = lookup_widget( GTK_WIDGET(button), "tdb_langwin");
	gtk_widget_hide(langwin);
	/*	gtk_widget_destroy(langwin); */


}



