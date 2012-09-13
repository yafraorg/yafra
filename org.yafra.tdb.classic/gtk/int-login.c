/*D***********************************************************
 * copyright: yafra.org, Switzerland, 2004
 *
 * modul:     travelDB GTK user interface
 * GTK func:  create login window
 * describe:  logon window OK/CANCEL cb
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.2 $
 **************************************************************/
static char rcsid[]="$Id: int-login.c,v 1.2 2004-03-05 14:23:34 mwn Exp $";

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

GtkWidget *create_tdb_login(void)
{
    GtkWidget *tdb_login;
    GtkWidget *vbox_login;
    GtkWidget *l_logon_title;
    GtkWidget *table_login;
    GtkWidget *l_logon_db;
    GtkWidget *l_logon_user;
    GtkWidget *l_logon_pw;
    GtkWidget *e_logon_db;
    GtkWidget *e_logon_user;
    GtkWidget *e_logon_pw;
    GtkWidget *l_logon_host;
    GtkWidget *e_logon_host;
    GtkWidget *hbox_login;
    GtkWidget *b_logon_ok;
    GtkWidget *b_logon_cancel;

    tdb_login = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(tdb_login), _("travelDB logon"));

    vbox_login = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(vbox_login);
    gtk_container_add(GTK_CONTAINER(tdb_login), vbox_login);

    l_logon_title = gtk_label_new(_("Login Dialog"));
    gtk_widget_show(l_logon_title);
    gtk_box_pack_start(GTK_BOX(vbox_login), l_logon_title, FALSE, FALSE, 0);
    gtk_label_set_justify(GTK_LABEL(l_logon_title), GTK_JUSTIFY_CENTER);

    table_login = gtk_table_new(4, 2, FALSE);
    gtk_widget_show(table_login);
    gtk_box_pack_start(GTK_BOX(vbox_login), table_login, TRUE, TRUE, 0);

    l_logon_db = gtk_label_new(_("Databasename:"));
    gtk_widget_show(l_logon_db);
    gtk_table_attach(GTK_TABLE(table_login), l_logon_db, 0, 1, 0, 1,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_label_set_justify(GTK_LABEL(l_logon_db), GTK_JUSTIFY_CENTER);
    gtk_misc_set_alignment(GTK_MISC(l_logon_db), 0, 0.5);

    l_logon_user = gtk_label_new(_("User"));
    gtk_widget_show(l_logon_user);
    gtk_table_attach(GTK_TABLE(table_login), l_logon_user, 0, 1, 2, 3,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_label_set_justify(GTK_LABEL(l_logon_user), GTK_JUSTIFY_CENTER);
    gtk_misc_set_alignment(GTK_MISC(l_logon_user), 0, 0.5);

    l_logon_pw = gtk_label_new(_("Password"));
    gtk_widget_show(l_logon_pw);
    gtk_table_attach(GTK_TABLE(table_login), l_logon_pw, 0, 1, 3, 4,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_label_set_justify(GTK_LABEL(l_logon_pw), GTK_JUSTIFY_CENTER);
    gtk_misc_set_alignment(GTK_MISC(l_logon_pw), 0, 0.5);

    e_logon_db = gtk_entry_new();
    gtk_widget_show(e_logon_db);
    gtk_table_attach(GTK_TABLE(table_login), e_logon_db, 1, 2, 0, 1,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);
    gtk_entry_set_text(GTK_ENTRY(e_logon_db), _("traveldb"));

    e_logon_user = gtk_entry_new();
    gtk_widget_show(e_logon_user);
    gtk_table_attach(GTK_TABLE(table_login), e_logon_user, 1, 2, 2, 3,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);

    e_logon_pw = gtk_entry_new();
    gtk_widget_show(e_logon_pw);
    gtk_table_attach(GTK_TABLE(table_login), e_logon_pw, 1, 2, 3, 4,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);
    gtk_entry_set_visibility(GTK_ENTRY(e_logon_pw), FALSE);

    l_logon_host = gtk_label_new(_("Hostname"));
    gtk_widget_show(l_logon_host);
    gtk_table_attach(GTK_TABLE(table_login), l_logon_host, 0, 1, 1, 2,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_label_set_justify(GTK_LABEL(l_logon_host), GTK_JUSTIFY_CENTER);
    gtk_misc_set_alignment(GTK_MISC(l_logon_host), 0, 0.5);

    e_logon_host = gtk_entry_new();
    gtk_widget_show(e_logon_host);
    gtk_table_attach(GTK_TABLE(table_login), e_logon_host, 1, 2, 1, 2,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);
    gtk_entry_set_text(GTK_ENTRY(e_logon_host), _("localhost"));

    hbox_login = gtk_hbox_new(TRUE, 0);
    gtk_widget_show(hbox_login);
    gtk_box_pack_start(GTK_BOX(vbox_login), hbox_login, TRUE, TRUE, 0);

    b_logon_ok = gtk_button_new_with_mnemonic(_("Logon"));
    gtk_widget_show(b_logon_ok);
    gtk_box_pack_start(GTK_BOX(hbox_login), b_logon_ok, FALSE, FALSE, 0);

    b_logon_cancel = gtk_button_new_with_mnemonic(_("Cancel"));
    gtk_widget_show(b_logon_cancel);
    gtk_box_pack_start(GTK_BOX(hbox_login), b_logon_cancel, FALSE, FALSE, 0);

    g_signal_connect((gpointer) b_logon_ok, "clicked",
                     G_CALLBACK(on_logon_clicked), NULL);
    g_signal_connect((gpointer) b_logon_cancel, "clicked",
                     G_CALLBACK(on_logon_cancel_clicked), NULL);

    /* Store pointers to all widgets, for use by lookup_widget(). */
    GLADE_HOOKUP_OBJECT_NO_REF(tdb_login, tdb_login, "tdb_login");
    GLADE_HOOKUP_OBJECT(tdb_login, vbox_login, "vbox_login");
    GLADE_HOOKUP_OBJECT(tdb_login, l_logon_title, "l_logon_title");
    GLADE_HOOKUP_OBJECT(tdb_login, table_login, "table_login");
    GLADE_HOOKUP_OBJECT(tdb_login, l_logon_db, "l_logon_db");
    GLADE_HOOKUP_OBJECT(tdb_login, l_logon_user, "l_logon_user");
    GLADE_HOOKUP_OBJECT(tdb_login, l_logon_pw, "l_logon_pw");
    GLADE_HOOKUP_OBJECT(tdb_login, e_logon_db, "e_logon_db");
    GLADE_HOOKUP_OBJECT(tdb_login, e_logon_user, "e_logon_user");
    GLADE_HOOKUP_OBJECT(tdb_login, e_logon_pw, "e_logon_pw");
    GLADE_HOOKUP_OBJECT(tdb_login, l_logon_host, "l_logon_host");
    GLADE_HOOKUP_OBJECT(tdb_login, e_logon_host, "e_logon_host");
    GLADE_HOOKUP_OBJECT(tdb_login, hbox_login, "hbox_login");
    GLADE_HOOKUP_OBJECT(tdb_login, b_logon_ok, "b_logon_ok");
    GLADE_HOOKUP_OBJECT(tdb_login, b_logon_cancel, "b_logon_cancel");

    return tdb_login;
}
