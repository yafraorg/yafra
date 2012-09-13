/*D***********************************************************
 * copyright: yafra.org, Switzerland, 2004
 *
 * modul:     travelDB GTK user interface
 * GTK func:  create window
 * describe:  MAIN window
 *
 * menubar consists of:
 * File(Open, Save, Save as..., Print, Exit)
 * Edit (Undo, Cut, Copy, Paste)
 * Reservations (Manage, List)
 * Book (Plan, Package, Service)
 * Plan (Journey [means ad hoc package], Package [pre defined], Flight, Hotel, Car, Cruise, Tour, Bus, Train
 * Settings (Profile, Options)
 * Help (Index, Forums, Website, Check for update, About)
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.6 $
 **************************************************************/
static char rcsid[]="$Id: int-mainwin.c,v 1.6 2008-11-23 15:44:38 mwn Exp $";

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
extern MP_GLOBALPROFIL globprof;

// local functions for reading login
static int init_main(char *lang, char *sai, char *prg, char *bst);

//--------------------------------------------------------------
// create main window
// - give current db and user as string
//--------------------------------------------------------------
GtkWidget *create_tdb_main(void)
{
    GtkWidget *tdb_main;
    GtkWidget *vbox_main;
    GtkWidget *mb_main;
    GtkWidget *mb_file;
    GtkWidget *mb_file_menu;
    GtkWidget *mb_save;
    GtkWidget *mb_print;
    GtkWidget *mb_exit;
    GtkWidget *mb_edit;
    GtkWidget *mb_edit_menu;
    GtkWidget *mb_copy;
    GtkWidget *mp_cut;
    GtkWidget *mb_past;
    GtkWidget *mb_separator1;
    GtkWidget *mb_opts;
    GtkWidget *mb_book;
    GtkWidget *mb_book_menu;
    GtkWidget *mb_package;
    GtkWidget *mb_reservation;
    GtkWidget *mb_service;
    GtkWidget *mb_service_menu;
    GtkWidget *mb_flight;
    GtkWidget *mb_geo;
    GtkWidget *mb_geo_menu;
    GtkWidget *mb_lang;
    GtkWidget *mb_help;
    GtkWidget *mb_help_menu;
    GtkWidget *mb_about;
    GtkWidget *table_main;
    GtkWidget *l_main_db;
    GtkWidget *l_main_user;
    GtkWidget *l_main_lang;
    GtkWidget *l_main_sai;
    GtkWidget *e_main_db;
    GtkWidget *e_main_user;
    GtkWidget *e_main_lang;
    GtkWidget *e_main_sai;
    GtkWidget *l_main_prg;
    GtkWidget *l_main_bchst;
    GtkWidget *e_main_prg;
    GtkWidget *e_main_bst;
    GtkWidget *sb_main;
    GtkTooltips *tooltips;

	// read login stream and init main windows
	guint mainctx;
	guint msgid;
	char lang[_CHARMAXLEN];
	char sai[_CHARMAXLEN];
	char prg[_CHARMAXLEN];
	char bst[_CHARMAXLEN];
	int cret;
	cret = init_main(lang, sai, prg, bst);

    tooltips = gtk_tooltips_new();

    tdb_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(tdb_main), _("travelDB GTK"));

    vbox_main = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(vbox_main);
    gtk_container_add(GTK_CONTAINER(tdb_main), vbox_main);

    mb_main = gtk_menu_bar_new();
    gtk_widget_show(mb_main);
    gtk_box_pack_start(GTK_BOX(vbox_main), mb_main, FALSE, FALSE, 0);

    mb_file = gtk_menu_item_new_with_mnemonic(_("File"));
    gtk_widget_show(mb_file);
    gtk_container_add(GTK_CONTAINER(mb_main), mb_file);

    mb_file_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mb_file), mb_file_menu);

    mb_save = gtk_menu_item_new_with_mnemonic(_("Save"));
    gtk_widget_show(mb_save);
    gtk_container_add(GTK_CONTAINER(mb_file_menu), mb_save);
    gtk_tooltips_set_tip(tooltips, mb_save, _("Save configs"), NULL);

    mb_print = gtk_menu_item_new_with_mnemonic(_("Print"));
    gtk_widget_show(mb_print);
    gtk_container_add(GTK_CONTAINER(mb_file_menu), mb_print);
    gtk_tooltips_set_tip(tooltips, mb_print, _("Print your reports"), NULL);

    mb_exit = gtk_menu_item_new_with_mnemonic(_("Exit"));
    gtk_widget_show(mb_exit);
    gtk_container_add(GTK_CONTAINER(mb_file_menu), mb_exit);
    gtk_tooltips_set_tip(tooltips, mb_exit, _("Exit application"), NULL);

    mb_edit = gtk_menu_item_new_with_mnemonic(_("Edit"));
    gtk_widget_show(mb_edit);
    gtk_container_add(GTK_CONTAINER(mb_main), mb_edit);

    mb_edit_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mb_edit), mb_edit_menu);

    mb_copy = gtk_menu_item_new_with_mnemonic(_("Copy"));
    gtk_widget_show(mb_copy);
    gtk_container_add(GTK_CONTAINER(mb_edit_menu), mb_copy);

    mp_cut = gtk_menu_item_new_with_mnemonic(_("Cut"));
    gtk_widget_show(mp_cut);
    gtk_container_add(GTK_CONTAINER(mb_edit_menu), mp_cut);

    mb_past = gtk_menu_item_new_with_mnemonic(_("Paste"));
    gtk_widget_show(mb_past);
    gtk_container_add(GTK_CONTAINER(mb_edit_menu), mb_past);

    mb_separator1 = gtk_menu_item_new();
    gtk_widget_show(mb_separator1);
    gtk_container_add(GTK_CONTAINER(mb_edit_menu), mb_separator1);
    gtk_widget_set_sensitive(mb_separator1, FALSE);

    mb_opts = gtk_menu_item_new_with_mnemonic(_("Options"));
    gtk_widget_show(mb_opts);
    gtk_container_add(GTK_CONTAINER(mb_edit_menu), mb_opts);
    gtk_tooltips_set_tip(tooltips, mb_opts, _("Set application options"), NULL);

    mb_book = gtk_menu_item_new_with_mnemonic(_("Book"));
    gtk_widget_show(mb_book);
    gtk_container_add(GTK_CONTAINER(mb_main), mb_book);

    mb_book_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mb_book), mb_book_menu);

    mb_package = gtk_menu_item_new_with_mnemonic(_("Package"));
    gtk_widget_show(mb_package);
    gtk_container_add(GTK_CONTAINER(mb_book_menu), mb_package);

    mb_service = gtk_menu_item_new_with_mnemonic(_("Service"));
    gtk_widget_show(mb_service);
    gtk_container_add(GTK_CONTAINER(mb_book_menu), mb_service);

    mb_reservation = gtk_menu_item_new_with_mnemonic(_("Reservation"));
    gtk_widget_show(mb_reservation);
    gtk_container_add(GTK_CONTAINER(mb_book_menu), mb_reservation);

    mb_service = gtk_menu_item_new_with_mnemonic(_("Services"));
    gtk_widget_show(mb_service);
    gtk_container_add(GTK_CONTAINER(mb_main), mb_service);

    mb_service_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mb_service), mb_service_menu);

    mb_flight = gtk_menu_item_new_with_mnemonic(_("Flight"));
    gtk_widget_show(mb_flight);
    gtk_container_add(GTK_CONTAINER(mb_service_menu), mb_flight);

    mb_geo = gtk_menu_item_new_with_mnemonic(_("Geo"));
    gtk_widget_show(mb_geo);
    gtk_container_add(GTK_CONTAINER(mb_main), mb_geo);

    mb_geo_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mb_geo), mb_geo_menu);

    mb_lang = gtk_menu_item_new_with_mnemonic(_("Sprache"));
    gtk_widget_show(mb_lang);
    gtk_container_add(GTK_CONTAINER(mb_geo_menu), mb_lang);

    mb_help = gtk_menu_item_new_with_mnemonic(_("Help"));
    gtk_widget_show(mb_help);
    gtk_container_add(GTK_CONTAINER(mb_main), mb_help);

    mb_help_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mb_help), mb_help_menu);

    mb_about = gtk_menu_item_new_with_mnemonic(_("About"));
    gtk_widget_show(mb_about);
    gtk_container_add(GTK_CONTAINER(mb_help_menu), mb_about);

    table_main = gtk_table_new(6, 2, FALSE);
    gtk_widget_show(table_main);
    gtk_box_pack_start(GTK_BOX(vbox_main), table_main, TRUE, TRUE, 0);

    l_main_db = gtk_label_new(_("Databasename"));
    gtk_widget_show(l_main_db);
    gtk_table_attach(GTK_TABLE(table_main), l_main_db, 0, 1, 0, 1,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_label_set_justify(GTK_LABEL(l_main_db), GTK_JUSTIFY_CENTER);
    gtk_misc_set_alignment(GTK_MISC(l_main_db), 0, 0.5);

    l_main_user = gtk_label_new(_("User"));
    gtk_widget_show(l_main_user);
    gtk_table_attach(GTK_TABLE(table_main), l_main_user, 0, 1, 1, 2,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_label_set_justify(GTK_LABEL(l_main_user), GTK_JUSTIFY_CENTER);
    gtk_misc_set_alignment(GTK_MISC(l_main_user), 0, 0.5);

    l_main_lang = gtk_label_new(_("Language"));
    gtk_widget_show(l_main_lang);
    gtk_table_attach(GTK_TABLE(table_main), l_main_lang, 0, 1, 2, 3,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_label_set_justify(GTK_LABEL(l_main_lang), GTK_JUSTIFY_CENTER);
    gtk_misc_set_alignment(GTK_MISC(l_main_lang), 0, 0.5);

    l_main_sai = gtk_label_new(_("Saison"));
    gtk_widget_show(l_main_sai);
    gtk_table_attach(GTK_TABLE(table_main), l_main_sai, 0, 1, 3, 4,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_label_set_justify(GTK_LABEL(l_main_sai), GTK_JUSTIFY_CENTER);
    gtk_misc_set_alignment(GTK_MISC(l_main_sai), 0, 0.5);

    e_main_db = gtk_entry_new();
    gtk_widget_show(e_main_db);
    gtk_table_attach(GTK_TABLE(table_main), e_main_db, 1, 2, 0, 1,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);
    gtk_editable_set_editable(GTK_EDITABLE(e_main_db), FALSE);
  gtk_entry_set_text (GTK_ENTRY (e_main_db), globprof.database);

    e_main_user = gtk_entry_new();
    gtk_widget_show(e_main_user);
    gtk_table_attach(GTK_TABLE(table_main), e_main_user, 1, 2, 1, 2,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);
    gtk_editable_set_editable(GTK_EDITABLE(e_main_user), FALSE);
	gtk_entry_set_text (GTK_ENTRY (e_main_user), globprof.user);

    e_main_lang = gtk_entry_new();
    gtk_widget_show(e_main_lang);
    gtk_table_attach(GTK_TABLE(table_main), e_main_lang, 1, 2, 2, 3,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);
	gtk_entry_set_text(GTK_ENTRY(e_main_lang), lang);

    e_main_sai = gtk_entry_new();
    gtk_widget_show(e_main_sai);
    gtk_table_attach(GTK_TABLE(table_main), e_main_sai, 1, 2, 3, 4,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);
	gtk_entry_set_text(GTK_ENTRY(e_main_sai), sai);

    l_main_prg = gtk_label_new(_("Catalog"));
    gtk_widget_show(l_main_prg);
    gtk_table_attach(GTK_TABLE(table_main), l_main_prg, 0, 1, 4, 5,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_misc_set_alignment(GTK_MISC(l_main_prg), 0, 0.5);

    l_main_bchst = gtk_label_new(_("Booking Center"));
    gtk_widget_show(l_main_bchst);
    gtk_table_attach(GTK_TABLE(table_main), l_main_bchst, 0, 1, 5, 6,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_misc_set_alignment(GTK_MISC(l_main_bchst), 0, 0.5);

    e_main_prg = gtk_entry_new();
    gtk_widget_show(e_main_prg);
    gtk_table_attach(GTK_TABLE(table_main), e_main_prg, 1, 2, 4, 5,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);
	gtk_entry_set_text(GTK_ENTRY(e_main_prg), prg);

    e_main_bst = gtk_entry_new();
    gtk_widget_show(e_main_bst);
    gtk_table_attach(GTK_TABLE(table_main), e_main_bst, 1, 2, 5, 6,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);
	gtk_entry_set_text(GTK_ENTRY(e_main_bst), bst);

    sb_main = gtk_statusbar_new();
	mainctx = gtk_statusbar_get_context_id(GTK_STATUSBAR(sb_main), "tdb_main");
	msgid = gtk_statusbar_push(GTK_STATUSBAR(sb_main), mainctx, "Connected - Ready");
    gtk_widget_show(sb_main);
    gtk_box_pack_start(GTK_BOX(vbox_main), sb_main, FALSE, FALSE, 0);

    g_signal_connect((gpointer) mb_save, "activate",
                     G_CALLBACK(on_mb_save_activate), NULL);
    g_signal_connect((gpointer) mb_print, "activate",
                     G_CALLBACK(on_mb_print_activate), NULL);
    g_signal_connect((gpointer) mb_exit, "activate",
                     G_CALLBACK(on_mb_exit_activate), NULL);
    g_signal_connect((gpointer) mb_copy, "activate",
                     G_CALLBACK(on_mb_copy_activate), NULL);
    g_signal_connect((gpointer) mp_cut, "activate",
                     G_CALLBACK(on_mp_cut_activate), NULL);
    g_signal_connect((gpointer) mb_past, "activate",
                     G_CALLBACK(on_mb_past_activate), NULL);
    g_signal_connect((gpointer) mb_opts, "activate",
                     G_CALLBACK(on_mb_opts_activate), NULL);
    g_signal_connect((gpointer) mb_package, "activate",
                     G_CALLBACK(on_mb_package_activate), NULL);
    g_signal_connect((gpointer) mb_service, "activate",
                     G_CALLBACK(on_mb_service_activate), NULL);
    g_signal_connect((gpointer) mb_reservation, "activate",
                     G_CALLBACK(on_mb_reservation_activate), NULL);
    g_signal_connect((gpointer) mb_flight, "activate",
                     G_CALLBACK(on_mb_flight_activate), NULL);
    g_signal_connect((gpointer) mb_lang, "activate",
                     G_CALLBACK(on_mb_lang_activate), NULL);
    g_signal_connect((gpointer) mb_about, "activate",
                     G_CALLBACK(on_mb_about_activate), NULL);

    /* Store pointers to all widgets, for use by lookup_widget(). */
    GLADE_HOOKUP_OBJECT_NO_REF(tdb_main, tdb_main, "tdb_main");
    GLADE_HOOKUP_OBJECT(tdb_main, vbox_main, "vbox_main");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_main, "mb_main");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_file, "mb_file");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_file_menu, "mb_file_menu");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_save, "mb_save");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_print, "mb_print");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_exit, "mb_exit");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_edit, "mb_edit");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_edit_menu, "mb_edit_menu");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_copy, "mb_copy");
    GLADE_HOOKUP_OBJECT(tdb_main, mp_cut, "mp_cut");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_past, "mb_past");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_separator1, "mb_separator1");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_opts, "mb_opts");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_book, "mb_book");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_book_menu, "mb_book_menu");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_package, "mb_package");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_service, "mb_service");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_reservation, "mb_reservation");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_service, "mb_service");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_service_menu, "mb_service_menu");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_flight, "mb_flight");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_geo, "mb_geo");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_geo_menu, "mb_geo_menu");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_lang, "mb_lang");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_help, "mb_help");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_help_menu, "mb_help_menu");
    GLADE_HOOKUP_OBJECT(tdb_main, mb_about, "mb_about");
    GLADE_HOOKUP_OBJECT(tdb_main, table_main, "table_main");
    GLADE_HOOKUP_OBJECT(tdb_main, l_main_db, "l_main_db");
    GLADE_HOOKUP_OBJECT(tdb_main, l_main_user, "l_main_user");
    GLADE_HOOKUP_OBJECT(tdb_main, l_main_lang, "l_main_lang");
    GLADE_HOOKUP_OBJECT(tdb_main, l_main_sai, "l_main_sai");
    GLADE_HOOKUP_OBJECT(tdb_main, e_main_db, "e_main_db");
    GLADE_HOOKUP_OBJECT(tdb_main, e_main_user, "e_main_user");
    GLADE_HOOKUP_OBJECT(tdb_main, e_main_lang, "e_main_lang");
    GLADE_HOOKUP_OBJECT(tdb_main, e_main_sai, "e_main_sai");
    GLADE_HOOKUP_OBJECT(tdb_main, l_main_prg, "l_main_prg");
    GLADE_HOOKUP_OBJECT(tdb_main, l_main_bchst, "l_main_bchst");
    GLADE_HOOKUP_OBJECT(tdb_main, e_main_prg, "e_main_prg");
    GLADE_HOOKUP_OBJECT(tdb_main, e_main_bst, "e_main_bst");
    GLADE_HOOKUP_OBJECT(tdb_main, sb_main, "sb_main");
    GLADE_HOOKUP_OBJECT_NO_REF(tdb_main, tooltips, "tooltips");

    return tdb_main;
}

static int init_main(char *lang, char *sai, char *prg, char *bst)
{
	extern int DebugFlag;
	extern int MPNETstate;

	int cret = MPOK;
	int len;
	xmlChar tmp[_CHARMAXLEN];

	// RECEIVE login request feedback
	cret = MPXMLread(STARTMEMCHUNK);
	if (cret != MPOK)
		MPGTKexit(MPE_GTKXMLERROR);

	MPNETstate = MPOK;
	cret = MPXMLgetElement("FLAG", tmp);
	len = xmlStrlen(tmp);
	if (len > _CHAR200)
		len = _CHAR200;
	MPNETstate = atoi(tmp);
	if (MPNETstate != MPOK)
		MPGTKexit(MPE_GTKXMLERROR);

	cret = MPXMLgetElement("LANG", tmp);
	len = xmlStrlen(tmp);
	if (len > _CHAR200)
		len = _CHAR200;
	(void)strncpy(lang, tmp, len);

	cret = MPXMLgetElement("SAI", tmp);
	len = xmlStrlen(tmp);
	if (len > _USERLEN)
		len = _USERLEN;
	(void)strncpy(sai, tmp, len);

	cret = MPXMLgetElement("PRG", tmp);
	len = xmlStrlen(tmp);
	if (len > _PWDLEN)
		len = _PWDLEN;
	(void)strncpy(prg, tmp, len);

	cret = MPXMLgetElement("BCHST", tmp);
	len = xmlStrlen(tmp);
	if (len > _CHAR200)
		len = _CHAR200;
	(void)strncpy(bst, tmp, len);
	if (cret == MPOK)
		cret = MPXMLreadEnd();
	if (cret != MPOK)
		MPGTKexit(MPE_GTKXMLERROR);

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, MPGTK_PRGNAME, "got init from %s with MPNETstate %d and cret %d", globprof.hostname, MPNETstate, cret);
	return(cret);
}
