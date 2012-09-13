/*D***********************************************************
 * copyright: yafra.org, Switzerland, 2004
 *
 * modul:     travelDB GTK user interface
 * GTK func:  create window
 * describe:  MAIN window
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.2 $
 **************************************************************/
static char rcsid[]="$Id: int-options.c,v 1.2 2004-03-05 14:23:34 mwn Exp $";

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
extern MP_GLOBALPROFIL globprof;

// local functions for reading login

//--------------------------------------------------------------
// create main window
// - give current db and user as string
//--------------------------------------------------------------

GtkWidget *create_tdb_opts(void)
{
    GtkWidget *tdb_opts;
    GtkWidget *dialog_vbox1;
    GtkWidget *notebook1;
    GtkWidget *vbox1;
    GtkWidget *cb_opts_debug;
    GtkWidget *cb_opts_log;
    GtkWidget *checkbutton3;
    GtkWidget *checkbutton4;
    GtkWidget *checkbutton5;
    GtkWidget *nl_opts_settings;
    GtkWidget *table1;
    GtkWidget *label20;
    GtkWidget *label21;
    GtkWidget *label22;
    GtkWidget *combo1;
    GtkWidget *combo_opts_lang;
    GtkWidget *combo2;
    GtkWidget *combo_entry2;
    GtkWidget *combo3;
    GtkWidget *combo_entry3;
    GtkWidget *nl_opts_prof;
    GtkWidget *scrolledwindow1;
    GtkWidget *tree_opts_users;
    GtkWidget *nl_opts_users;
    GtkWidget *label19;
    GtkWidget *nl_opts_admin;
    GtkWidget *dialog_action_area1;
    GtkWidget *b_opts_cancel;
    GtkWidget *b_opts_apply;
    GtkWidget *b_opts_ok;

    tdb_opts = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(tdb_opts), _("travelDB options"));

    dialog_vbox1 = GTK_DIALOG(tdb_opts)->vbox;
    gtk_widget_show(dialog_vbox1);

    notebook1 = gtk_notebook_new();
    gtk_widget_show(notebook1);
    gtk_box_pack_start(GTK_BOX(dialog_vbox1), notebook1, TRUE, TRUE, 0);

    vbox1 = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(vbox1);
    gtk_container_add(GTK_CONTAINER(notebook1), vbox1);

    cb_opts_debug = gtk_check_button_new_with_mnemonic(_("Debugging On/Off"));
    gtk_widget_show(cb_opts_debug);
    gtk_box_pack_start(GTK_BOX(vbox1), cb_opts_debug, FALSE, FALSE, 0);

    cb_opts_log = gtk_check_button_new_with_mnemonic(_("Logging On/Off"));
    gtk_widget_show(cb_opts_log);
    gtk_box_pack_start(GTK_BOX(vbox1), cb_opts_log, FALSE, FALSE, 0);

    checkbutton3 = gtk_check_button_new_with_mnemonic(_("checkbutton3"));
    gtk_widget_show(checkbutton3);
    gtk_box_pack_start(GTK_BOX(vbox1), checkbutton3, FALSE, FALSE, 0);

    checkbutton4 = gtk_check_button_new_with_mnemonic(_("checkbutton4"));
    gtk_widget_show(checkbutton4);
    gtk_box_pack_start(GTK_BOX(vbox1), checkbutton4, FALSE, FALSE, 0);

    checkbutton5 = gtk_check_button_new_with_mnemonic(_("checkbutton5"));
    gtk_widget_show(checkbutton5);
    gtk_box_pack_start(GTK_BOX(vbox1), checkbutton5, FALSE, FALSE, 0);

    nl_opts_settings = gtk_label_new(_("Settings"));
    gtk_widget_show(nl_opts_settings);
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook1),
                               gtk_notebook_get_nth_page(GTK_NOTEBOOK
                                                         (notebook1), 0),
                               nl_opts_settings);

    table1 = gtk_table_new(3, 2, FALSE);
    gtk_widget_show(table1);
    gtk_container_add(GTK_CONTAINER(notebook1), table1);

    label20 = gtk_label_new(_("label20"));
    gtk_widget_show(label20);
    gtk_table_attach(GTK_TABLE(table1), label20, 0, 1, 0, 1,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_misc_set_alignment(GTK_MISC(label20), 0, 0.5);

    label21 = gtk_label_new(_("label21"));
    gtk_widget_show(label21);
    gtk_table_attach(GTK_TABLE(table1), label21, 0, 1, 1, 2,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_misc_set_alignment(GTK_MISC(label21), 0, 0.5);

    label22 = gtk_label_new(_("label22"));
    gtk_widget_show(label22);
    gtk_table_attach(GTK_TABLE(table1), label22, 0, 1, 2, 3,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_misc_set_alignment(GTK_MISC(label22), 0, 0.5);

    combo1 = gtk_combo_new();
    g_object_set_data(G_OBJECT(GTK_COMBO(combo1)->popwin), "GladeParentKey",
                      combo1);
    gtk_widget_show(combo1);
    gtk_table_attach(GTK_TABLE(table1), combo1, 1, 2, 0, 1,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);

    combo_opts_lang = GTK_COMBO(combo1)->entry;
    gtk_widget_show(combo_opts_lang);
    gtk_editable_set_editable(GTK_EDITABLE(combo_opts_lang), FALSE);
    gtk_entry_set_text(GTK_ENTRY(combo_opts_lang), _("Lang"));

    combo2 = gtk_combo_new();
    g_object_set_data(G_OBJECT(GTK_COMBO(combo2)->popwin), "GladeParentKey",
                      combo2);
    gtk_widget_show(combo2);
    gtk_table_attach(GTK_TABLE(table1), combo2, 1, 2, 1, 2,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);

    combo_entry2 = GTK_COMBO(combo2)->entry;
    gtk_widget_show(combo_entry2);
    gtk_editable_set_editable(GTK_EDITABLE(combo_entry2), FALSE);
    gtk_entry_set_text(GTK_ENTRY(combo_entry2), _("Test"));

    combo3 = gtk_combo_new();
    g_object_set_data(G_OBJECT(GTK_COMBO(combo3)->popwin), "GladeParentKey",
                      combo3);
    gtk_widget_show(combo3);
    gtk_table_attach(GTK_TABLE(table1), combo3, 1, 2, 2, 3,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);

    combo_entry3 = GTK_COMBO(combo3)->entry;
    gtk_widget_show(combo_entry3);

    nl_opts_prof = gtk_label_new(_("Profile"));
    gtk_widget_show(nl_opts_prof);
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook1),
                               gtk_notebook_get_nth_page(GTK_NOTEBOOK
                                                         (notebook1), 1),
                               nl_opts_prof);

    scrolledwindow1 = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_show(scrolledwindow1);
    gtk_container_add(GTK_CONTAINER(notebook1), scrolledwindow1);

    tree_opts_users = gtk_tree_view_new();
    gtk_widget_show(tree_opts_users);
    gtk_container_add(GTK_CONTAINER(scrolledwindow1), tree_opts_users);

    nl_opts_users = gtk_label_new(_("Users"));
    gtk_widget_show(nl_opts_users);
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook1),
                               gtk_notebook_get_nth_page(GTK_NOTEBOOK
                                                         (notebook1), 2),
                               nl_opts_users);

    label19 = gtk_label_new(_("label19"));
    gtk_widget_show(label19);
    gtk_container_add(GTK_CONTAINER(notebook1), label19);

    nl_opts_admin = gtk_label_new(_("Administration"));
    gtk_widget_show(nl_opts_admin);
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook1),
                               gtk_notebook_get_nth_page(GTK_NOTEBOOK
                                                         (notebook1), 3),
                               nl_opts_admin);

    dialog_action_area1 = GTK_DIALOG(tdb_opts)->action_area;
    gtk_widget_show(dialog_action_area1);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(dialog_action_area1),
                              GTK_BUTTONBOX_END);

    b_opts_cancel = gtk_button_new_from_stock("gtk-cancel");
    gtk_widget_show(b_opts_cancel);
    gtk_dialog_add_action_widget(GTK_DIALOG(tdb_opts), b_opts_cancel,
                                 GTK_RESPONSE_CANCEL);
    GTK_WIDGET_SET_FLAGS(b_opts_cancel, GTK_CAN_DEFAULT);

    b_opts_apply = gtk_button_new_from_stock("gtk-apply");
    gtk_widget_show(b_opts_apply);
    gtk_dialog_add_action_widget(GTK_DIALOG(tdb_opts), b_opts_apply,
                                 GTK_RESPONSE_APPLY);
    GTK_WIDGET_SET_FLAGS(b_opts_apply, GTK_CAN_DEFAULT);

    b_opts_ok = gtk_button_new_from_stock("gtk-ok");
    gtk_widget_show(b_opts_ok);
    gtk_dialog_add_action_widget(GTK_DIALOG(tdb_opts), b_opts_ok,
                                 GTK_RESPONSE_OK);
    GTK_WIDGET_SET_FLAGS(b_opts_ok, GTK_CAN_DEFAULT);

    /* Store pointers to all widgets, for use by lookup_widget(). */
    GLADE_HOOKUP_OBJECT_NO_REF(tdb_opts, tdb_opts, "tdb_opts");
    GLADE_HOOKUP_OBJECT_NO_REF(tdb_opts, dialog_vbox1, "dialog_vbox1");
    GLADE_HOOKUP_OBJECT(tdb_opts, notebook1, "notebook1");
    GLADE_HOOKUP_OBJECT(tdb_opts, vbox1, "vbox1");
    GLADE_HOOKUP_OBJECT(tdb_opts, cb_opts_debug, "cb_opts_debug");
    GLADE_HOOKUP_OBJECT(tdb_opts, cb_opts_log, "cb_opts_log");
    GLADE_HOOKUP_OBJECT(tdb_opts, checkbutton3, "checkbutton3");
    GLADE_HOOKUP_OBJECT(tdb_opts, checkbutton4, "checkbutton4");
    GLADE_HOOKUP_OBJECT(tdb_opts, checkbutton5, "checkbutton5");
    GLADE_HOOKUP_OBJECT(tdb_opts, nl_opts_settings, "nl_opts_settings");
    GLADE_HOOKUP_OBJECT(tdb_opts, table1, "table1");
    GLADE_HOOKUP_OBJECT(tdb_opts, label20, "label20");
    GLADE_HOOKUP_OBJECT(tdb_opts, label21, "label21");
    GLADE_HOOKUP_OBJECT(tdb_opts, label22, "label22");
    GLADE_HOOKUP_OBJECT(tdb_opts, combo1, "combo1");
    GLADE_HOOKUP_OBJECT(tdb_opts, combo_opts_lang, "combo_opts_lang");
    GLADE_HOOKUP_OBJECT(tdb_opts, combo2, "combo2");
    GLADE_HOOKUP_OBJECT(tdb_opts, combo_entry2, "combo_entry2");
    GLADE_HOOKUP_OBJECT(tdb_opts, combo3, "combo3");
    GLADE_HOOKUP_OBJECT(tdb_opts, combo_entry3, "combo_entry3");
    GLADE_HOOKUP_OBJECT(tdb_opts, nl_opts_prof, "nl_opts_prof");
    GLADE_HOOKUP_OBJECT(tdb_opts, scrolledwindow1, "scrolledwindow1");
    GLADE_HOOKUP_OBJECT(tdb_opts, tree_opts_users, "tree_opts_users");
    GLADE_HOOKUP_OBJECT(tdb_opts, nl_opts_users, "nl_opts_users");
    GLADE_HOOKUP_OBJECT(tdb_opts, label19, "label19");
    GLADE_HOOKUP_OBJECT(tdb_opts, nl_opts_admin, "nl_opts_admin");
    GLADE_HOOKUP_OBJECT_NO_REF(tdb_opts, dialog_action_area1,
                               "dialog_action_area1");
    GLADE_HOOKUP_OBJECT(tdb_opts, b_opts_cancel, "b_opts_cancel");
    GLADE_HOOKUP_OBJECT(tdb_opts, b_opts_apply, "b_opts_apply");
    GLADE_HOOKUP_OBJECT(tdb_opts, b_opts_ok, "b_opts_ok");

    return tdb_opts;
}
