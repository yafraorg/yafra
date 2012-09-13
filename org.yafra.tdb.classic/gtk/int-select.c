/*D***********************************************************
 * copyright: yafra.org, Switzerland, 2004
 *
 * modul:     travelDB GTK user interface
 * GTK func:  create selection dialog
 * describe:  present a selection of values to choose
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.2 $
 **************************************************************/
static char rcsid[]="$Id: int-select.c,v 1.2 2004-03-05 14:23:34 mwn Exp $";

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

GtkWidget *create_tdb_select(void)
{
    GtkWidget *tdb_select;
    GtkWidget *vbox_select;
    GtkWidget *sw_select;
    GtkWidget *tree_select;
    GtkWidget *dialog_action_select;
    GtkWidget *b_select_cancel;
    GtkWidget *b_select_ok;

    tdb_select = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(tdb_select), _("Lookup"));

    vbox_select = GTK_DIALOG(tdb_select)->vbox;
    gtk_widget_show(vbox_select);

    sw_select = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_show(sw_select);
    gtk_box_pack_start(GTK_BOX(vbox_select), sw_select, TRUE, TRUE, 0);

    tree_select = gtk_tree_view_new();
    gtk_widget_show(tree_select);
    gtk_container_add(GTK_CONTAINER(sw_select), tree_select);

    dialog_action_select = GTK_DIALOG(tdb_select)->action_area;
    gtk_widget_show(dialog_action_select);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(dialog_action_select),
                              GTK_BUTTONBOX_END);

    b_select_cancel = gtk_button_new_from_stock("gtk-cancel");
    gtk_widget_show(b_select_cancel);
    gtk_dialog_add_action_widget(GTK_DIALOG(tdb_select), b_select_cancel,
                                 GTK_RESPONSE_CANCEL);
    GTK_WIDGET_SET_FLAGS(b_select_cancel, GTK_CAN_DEFAULT);

    b_select_ok = gtk_button_new_from_stock("gtk-ok");
    gtk_widget_show(b_select_ok);
    gtk_dialog_add_action_widget(GTK_DIALOG(tdb_select), b_select_ok,
                                 GTK_RESPONSE_OK);
    GTK_WIDGET_SET_FLAGS(b_select_ok, GTK_CAN_DEFAULT);

    g_signal_connect((gpointer) tree_select, "row_activated",
                     G_CALLBACK(on_tree_select_row_activated), NULL);
    g_signal_connect((gpointer) tree_select, "row_collapsed",
                     G_CALLBACK(on_tree_select_row_collapsed), NULL);
    g_signal_connect((gpointer) tree_select, "row_expanded",
                     G_CALLBACK(on_tree_select_row_expanded), NULL);
    g_signal_connect((gpointer) b_select_cancel, "clicked",
                     G_CALLBACK(on_b_select_cancel_clicked), NULL);
    g_signal_connect((gpointer) b_select_ok, "clicked",
                     G_CALLBACK(on_b_select_ok_clicked), NULL);

    /* Store pointers to all widgets, for use by lookup_widget(). */
    GLADE_HOOKUP_OBJECT_NO_REF(tdb_select, tdb_select, "tdb_select");
    GLADE_HOOKUP_OBJECT_NO_REF(tdb_select, vbox_select, "vbox_select");
    GLADE_HOOKUP_OBJECT(tdb_select, sw_select, "sw_select");
    GLADE_HOOKUP_OBJECT(tdb_select, tree_select, "tree_select");
    GLADE_HOOKUP_OBJECT_NO_REF(tdb_select, dialog_action_select,
                               "dialog_action_select");
    GLADE_HOOKUP_OBJECT(tdb_select, b_select_cancel, "b_select_cancel");
    GLADE_HOOKUP_OBJECT(tdb_select, b_select_ok, "b_select_ok");

    return tdb_select;
}
