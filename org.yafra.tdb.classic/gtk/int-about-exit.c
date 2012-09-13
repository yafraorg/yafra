/*D***********************************************************
 * copyright: yafra.org, Switzerland, 2004
 *
 * modul:     travelDB GTK user interface
 * GTK func:  create general dialogs
 * describe:  exit confirmation, about dialog
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.5 $
 **************************************************************/
/* RCS static ID */
static char rcsid[]="$Id: int-about-exit.c,v 1.5 2008-11-23 15:44:38 mwn Exp $";
static char tagid[]="$Name:  $";

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
#include "int-defines.h"
#include <mpgtk.h>
#include <mplizenz.h>

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

GtkWidget *create_tdb_about(void)
{
	GtkWidget *tdb_about;
	GtkWidget *vbox_about;
	GtkWidget *hbox_about_text;
	GtkWidget *img_about;
	GtkWidget *l_about_about;
	GtkWidget *dialog_action_about;
	GtkWidget *b_about_close;

	// set license text
	gchar license[200];
	sprintf(license, "%s %s", LIZMESS, tagid);

	tdb_about = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(tdb_about), _("About"));

	//vbox_about = GTK_DIALOG(tdb_about)->vbox;
	//gtk_widget_show(vbox_about);

	hbox_about_text = gtk_hbox_new(FALSE, 0);
	gtk_widget_show(hbox_about_text);
	gtk_box_pack_start(GTK_BOX(vbox_about), hbox_about_text, TRUE, TRUE, 0);

	img_about = create_pixmap(tdb_about, NULL);
	gtk_widget_show(img_about);
	gtk_box_pack_start(GTK_BOX(hbox_about_text), img_about, TRUE, TRUE, 0);

	l_about_about = gtk_label_new(_(license));
	gtk_widget_show(l_about_about);
	gtk_box_pack_start(GTK_BOX(hbox_about_text), l_about_about, FALSE, FALSE,
						  0);

	dialog_action_about = GTK_DIALOG(tdb_about)->action_area;
	gtk_widget_show(dialog_action_about);
	gtk_button_box_set_layout(GTK_BUTTON_BOX(dialog_action_about),
									GTK_BUTTONBOX_END);

	b_about_close = gtk_button_new_from_stock("gtk-close");
	gtk_widget_show(b_about_close);
	gtk_dialog_add_action_widget(GTK_DIALOG(tdb_about), b_about_close,
										GTK_RESPONSE_CLOSE);
	GTK_WIDGET_SET_FLAGS(b_about_close, GTK_CAN_DEFAULT);

	g_signal_connect((gpointer) b_about_close, "clicked",
						G_CALLBACK(on_b_about_close_clicked), NULL);

	/* Store pointers to all widgets, for use by lookup_widget(). */
	GLADE_HOOKUP_OBJECT_NO_REF(tdb_about, tdb_about, "tdb_about");
	GLADE_HOOKUP_OBJECT_NO_REF(tdb_about, vbox_about, "vbox_about");
	GLADE_HOOKUP_OBJECT(tdb_about, hbox_about_text, "hbox_about_text");
	GLADE_HOOKUP_OBJECT(tdb_about, img_about, "img_about");
	GLADE_HOOKUP_OBJECT(tdb_about, l_about_about, "l_about_about");
	GLADE_HOOKUP_OBJECT_NO_REF(tdb_about, dialog_action_about,
									 "dialog_action_about");
	GLADE_HOOKUP_OBJECT(tdb_about, b_about_close, "b_about_close");

	return tdb_about;
}

GtkWidget *create_tdb_exit(void)
{
	GtkWidget *tdb_exit;
	GtkWidget *vbox_exit;
	GtkWidget *l_exit_q;
	GtkWidget *dialog_action_exit;
	GtkWidget *b_exit_cancel;
	GtkWidget *b_exit_ok;

	tdb_exit = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(tdb_exit), _("Exit"));

	vbox_exit = GTK_DIALOG(tdb_exit)->vbox;
	gtk_widget_show(vbox_exit);

	l_exit_q =
	  gtk_label_new(_
						 ("Do you really want to exit and close any open work ?"));
	gtk_widget_show(l_exit_q);
	gtk_box_pack_start(GTK_BOX(vbox_exit), l_exit_q, TRUE, FALSE, 0);
	gtk_misc_set_padding(GTK_MISC(l_exit_q), 0, 15);

	dialog_action_exit = GTK_DIALOG(tdb_exit)->action_area;
	gtk_widget_show(dialog_action_exit);
	gtk_button_box_set_layout(GTK_BUTTON_BOX(dialog_action_exit),
									GTK_BUTTONBOX_END);

	b_exit_cancel = gtk_button_new_from_stock("gtk-cancel");
	gtk_widget_show(b_exit_cancel);
	gtk_dialog_add_action_widget(GTK_DIALOG(tdb_exit), b_exit_cancel,
										GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS(b_exit_cancel, GTK_CAN_DEFAULT);

	b_exit_ok = gtk_button_new_from_stock("gtk-ok");
	gtk_widget_show(b_exit_ok);
	gtk_dialog_add_action_widget(GTK_DIALOG(tdb_exit), b_exit_ok,
										GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS(b_exit_ok, GTK_CAN_DEFAULT);

	g_signal_connect((gpointer) b_exit_cancel, "clicked",
						G_CALLBACK(on_b_exit_cancel_clicked), NULL);
	g_signal_connect((gpointer) b_exit_ok, "clicked",
						G_CALLBACK(on_b_exit_ok_clicked), NULL);

	/* Store pointers to all widgets, for use by lookup_widget(). */
	GLADE_HOOKUP_OBJECT_NO_REF(tdb_exit, tdb_exit, "tdb_exit");
	GLADE_HOOKUP_OBJECT_NO_REF(tdb_exit, vbox_exit, "vbox_exit");
	GLADE_HOOKUP_OBJECT(tdb_exit, l_exit_q, "l_exit_q");
	GLADE_HOOKUP_OBJECT_NO_REF(tdb_exit, dialog_action_exit,
									 "dialog_action_exit");
	GLADE_HOOKUP_OBJECT(tdb_exit, b_exit_cancel, "b_exit_cancel");
	GLADE_HOOKUP_OBJECT(tdb_exit, b_exit_ok, "b_exit_ok");

	return tdb_exit;
}
