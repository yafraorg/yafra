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
static char rcsid[]="$Id: int-language.c,v 1.2 2004-03-05 14:23:33 mwn Exp $";

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

GtkWidget *create_tdb_langwin(void)
{
    GtkWidget *tdb_langwin;
    GtkWidget *vbox_lang;
    GtkWidget *f_lang_mand;
    GtkWidget *hbox_lang_mand;
    GtkWidget *table_lang_mand;
    GtkWidget *l_lang;
    GtkWidget *l_lang_code;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *b_lang_sel;
    GtkWidget *image2;
    GtkWidget *l_lang_mandatory;
    GtkWidget *f_lang_opt;
    GtkWidget *table_lang_opt;
    GtkWidget *l_lang_diaolog;
    GtkWidget *c_lang_out;
    GtkWidget *c_lang_labs;
    GtkWidget *c_lang_dialog;
    GtkWidget *alignment3;
    GtkWidget *hbox6;
    GtkWidget *image4;
    GtkWidget *label11;
    GtkWidget *l_lang_opt;
    GtkWidget *f_lang_menu;
    GtkWidget *hbox_lang_menu;
    GtkWidget *b_lang_OK;
    GtkWidget *alignment1;
    GtkWidget *hbox4;
    GtkWidget *image1;
    GtkWidget *label9;
    GtkWidget *b_lang_new;
    GtkWidget *alignment4;
    GtkWidget *hbox7;
    GtkWidget *image5;
    GtkWidget *label12;
    GtkWidget *b_lang_del;
    GtkWidget *alignment5;
    GtkWidget *hbox8;
    GtkWidget *image6;
    GtkWidget *label13;
    GtkWidget *b_lang_clr;
    GtkWidget *alignment6;
    GtkWidget *hbox9;
    GtkWidget *image7;
    GtkWidget *label14;
    GtkWidget *b_lang_close;
    GtkWidget *alignment2;
    GtkWidget *hbox5;
    GtkWidget *image3;
    GtkWidget *label10;
    GtkWidget *label3;
    GtkWidget *sb_lang;

    tdb_langwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(tdb_langwin), _("Languages"));

    vbox_lang = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(vbox_lang);
    gtk_container_add(GTK_CONTAINER(tdb_langwin), vbox_lang);

    f_lang_mand = gtk_frame_new(NULL);
    gtk_widget_show(f_lang_mand);
    gtk_box_pack_start(GTK_BOX(vbox_lang), f_lang_mand, TRUE, TRUE, 0);

    hbox_lang_mand = gtk_hbox_new(FALSE, 0);
    gtk_widget_show(hbox_lang_mand);
    gtk_container_add(GTK_CONTAINER(f_lang_mand), hbox_lang_mand);

    table_lang_mand = gtk_table_new(2, 2, FALSE);
    gtk_widget_show(table_lang_mand);
    gtk_box_pack_start(GTK_BOX(hbox_lang_mand), table_lang_mand, TRUE, TRUE, 0);

    l_lang = gtk_label_new(_("Language:"));
    gtk_widget_show(l_lang);
    gtk_table_attach(GTK_TABLE(table_lang_mand), l_lang, 0, 1, 0, 1,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_misc_set_alignment(GTK_MISC(l_lang), 0, 0.5);
    gtk_misc_set_padding(GTK_MISC(l_lang), 3, 3);

    l_lang_code = gtk_label_new(_("System code:"));
    gtk_widget_show(l_lang_code);
    gtk_table_attach(GTK_TABLE(table_lang_mand), l_lang_code, 0, 1, 1, 2,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_misc_set_alignment(GTK_MISC(l_lang_code), 0, 0.5);
    gtk_misc_set_padding(GTK_MISC(l_lang_code), 3, 3);

    entry1 = gtk_entry_new();
    gtk_widget_show(entry1);
    gtk_table_attach(GTK_TABLE(table_lang_mand), entry1, 1, 2, 0, 1,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);

    entry2 = gtk_entry_new();
    gtk_widget_show(entry2);
    gtk_table_attach(GTK_TABLE(table_lang_mand), entry2, 1, 2, 1, 2,
                     (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                     (GtkAttachOptions) (0), 0, 0);

    b_lang_sel = gtk_button_new();
    gtk_widget_show(b_lang_sel);
    gtk_box_pack_start(GTK_BOX(hbox_lang_mand), b_lang_sel, FALSE, FALSE, 0);

    image2 = gtk_image_new_from_stock("gtk-open", GTK_ICON_SIZE_BUTTON);
    gtk_widget_show(image2);
    gtk_container_add(GTK_CONTAINER(b_lang_sel), image2);

    l_lang_mandatory = gtk_label_new(_("mandatory data"));
    gtk_widget_show(l_lang_mandatory);
    gtk_frame_set_label_widget(GTK_FRAME(f_lang_mand), l_lang_mandatory);
    gtk_misc_set_alignment(GTK_MISC(l_lang_mandatory), 0.52, 0.5);

    f_lang_opt = gtk_frame_new(NULL);
    gtk_widget_show(f_lang_opt);
    gtk_box_pack_start(GTK_BOX(vbox_lang), f_lang_opt, TRUE, TRUE, 0);

    table_lang_opt = gtk_table_new(3, 2, FALSE);
    gtk_widget_show(table_lang_opt);
    gtk_container_add(GTK_CONTAINER(f_lang_opt), table_lang_opt);

    l_lang_diaolog = gtk_label_new(_("Dialogue language ?"));
    gtk_widget_show(l_lang_diaolog);
    gtk_table_attach(GTK_TABLE(table_lang_opt), l_lang_diaolog, 0, 1, 0, 1,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);
    gtk_misc_set_alignment(GTK_MISC(l_lang_diaolog), 0, 0.5);
    gtk_misc_set_padding(GTK_MISC(l_lang_diaolog), 3, 3);

    c_lang_out = gtk_check_button_new_with_mnemonic(_("Output language ?"));
    gtk_widget_show(c_lang_out);
    gtk_table_attach(GTK_TABLE(table_lang_opt), c_lang_out, 0, 1, 1, 2,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);

    c_lang_labs = gtk_check_button_new_with_mnemonic(_("Labels ?"));
    gtk_widget_show(c_lang_labs);
    gtk_table_attach(GTK_TABLE(table_lang_opt), c_lang_labs, 0, 1, 2, 3,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);

    c_lang_dialog = gtk_toggle_button_new();
    gtk_widget_show(c_lang_dialog);
    gtk_table_attach(GTK_TABLE(table_lang_opt), c_lang_dialog, 1, 2, 0, 1,
                     (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0,
                     0);

    alignment3 = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_widget_show(alignment3);
    gtk_container_add(GTK_CONTAINER(c_lang_dialog), alignment3);

    hbox6 = gtk_hbox_new(FALSE, 2);
    gtk_widget_show(hbox6);
    gtk_container_add(GTK_CONTAINER(alignment3), hbox6);

    image4 = gtk_image_new_from_stock("gtk-apply", GTK_ICON_SIZE_BUTTON);
    gtk_widget_show(image4);
    gtk_box_pack_start(GTK_BOX(hbox6), image4, FALSE, FALSE, 0);

    label11 = gtk_label_new_with_mnemonic(_("Yes / No"));
    gtk_widget_show(label11);
    gtk_box_pack_start(GTK_BOX(hbox6), label11, FALSE, FALSE, 0);

    l_lang_opt = gtk_label_new(_("optional data"));
    gtk_widget_show(l_lang_opt);
    gtk_frame_set_label_widget(GTK_FRAME(f_lang_opt), l_lang_opt);

    f_lang_menu = gtk_frame_new(NULL);
    gtk_widget_show(f_lang_menu);
    gtk_box_pack_start(GTK_BOX(vbox_lang), f_lang_menu, TRUE, TRUE, 0);

    hbox_lang_menu = gtk_hbox_new(FALSE, 3);
    gtk_widget_show(hbox_lang_menu);
    gtk_container_add(GTK_CONTAINER(f_lang_menu), hbox_lang_menu);
    gtk_container_set_border_width(GTK_CONTAINER(hbox_lang_menu), 5);

    b_lang_OK = gtk_button_new();
    gtk_widget_show(b_lang_OK);
    gtk_box_pack_start(GTK_BOX(hbox_lang_menu), b_lang_OK, FALSE, FALSE, 0);

    alignment1 = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_widget_show(alignment1);
    gtk_container_add(GTK_CONTAINER(b_lang_OK), alignment1);

    hbox4 = gtk_hbox_new(FALSE, 2);
    gtk_widget_show(hbox4);
    gtk_container_add(GTK_CONTAINER(alignment1), hbox4);

    image1 = gtk_image_new_from_stock("gtk-save", GTK_ICON_SIZE_BUTTON);
    gtk_widget_show(image1);
    gtk_box_pack_start(GTK_BOX(hbox4), image1, FALSE, FALSE, 0);

    label9 = gtk_label_new_with_mnemonic(_("Save"));
    gtk_widget_show(label9);
    gtk_box_pack_start(GTK_BOX(hbox4), label9, FALSE, FALSE, 0);

    b_lang_new = gtk_button_new();
    gtk_widget_show(b_lang_new);
    gtk_box_pack_start(GTK_BOX(hbox_lang_menu), b_lang_new, FALSE, FALSE, 0);

    alignment4 = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_widget_show(alignment4);
    gtk_container_add(GTK_CONTAINER(b_lang_new), alignment4);

    hbox7 = gtk_hbox_new(FALSE, 2);
    gtk_widget_show(hbox7);
    gtk_container_add(GTK_CONTAINER(alignment4), hbox7);

    image5 = gtk_image_new_from_stock("gtk-new", GTK_ICON_SIZE_BUTTON);
    gtk_widget_show(image5);
    gtk_box_pack_start(GTK_BOX(hbox7), image5, FALSE, FALSE, 0);

    label12 = gtk_label_new_with_mnemonic(_("New"));
    gtk_widget_show(label12);
    gtk_box_pack_start(GTK_BOX(hbox7), label12, FALSE, FALSE, 0);

    b_lang_del = gtk_button_new();
    gtk_widget_show(b_lang_del);
    gtk_box_pack_start(GTK_BOX(hbox_lang_menu), b_lang_del, FALSE, FALSE, 0);

    alignment5 = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_widget_show(alignment5);
    gtk_container_add(GTK_CONTAINER(b_lang_del), alignment5);

    hbox8 = gtk_hbox_new(FALSE, 2);
    gtk_widget_show(hbox8);
    gtk_container_add(GTK_CONTAINER(alignment5), hbox8);

    image6 = gtk_image_new_from_stock("gtk-delete", GTK_ICON_SIZE_BUTTON);
    gtk_widget_show(image6);
    gtk_box_pack_start(GTK_BOX(hbox8), image6, FALSE, FALSE, 0);

    label13 = gtk_label_new_with_mnemonic(_("Delete"));
    gtk_widget_show(label13);
    gtk_box_pack_start(GTK_BOX(hbox8), label13, FALSE, FALSE, 0);

    b_lang_clr = gtk_button_new();
    gtk_widget_show(b_lang_clr);
    gtk_box_pack_start(GTK_BOX(hbox_lang_menu), b_lang_clr, FALSE, FALSE, 0);

    alignment6 = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_widget_show(alignment6);
    gtk_container_add(GTK_CONTAINER(b_lang_clr), alignment6);

    hbox9 = gtk_hbox_new(FALSE, 2);
    gtk_widget_show(hbox9);
    gtk_container_add(GTK_CONTAINER(alignment6), hbox9);

    image7 = gtk_image_new_from_stock("gtk-clear", GTK_ICON_SIZE_BUTTON);
    gtk_widget_show(image7);
    gtk_box_pack_start(GTK_BOX(hbox9), image7, FALSE, FALSE, 0);

    label14 = gtk_label_new_with_mnemonic(_("Clear"));
    gtk_widget_show(label14);
    gtk_box_pack_start(GTK_BOX(hbox9), label14, FALSE, FALSE, 0);

    b_lang_close = gtk_button_new();
    gtk_widget_show(b_lang_close);
    gtk_box_pack_start(GTK_BOX(hbox_lang_menu), b_lang_close, FALSE, FALSE, 0);

    alignment2 = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_widget_show(alignment2);
    gtk_container_add(GTK_CONTAINER(b_lang_close), alignment2);

    hbox5 = gtk_hbox_new(FALSE, 2);
    gtk_widget_show(hbox5);
    gtk_container_add(GTK_CONTAINER(alignment2), hbox5);

    image3 = gtk_image_new_from_stock("gtk-close", GTK_ICON_SIZE_BUTTON);
    gtk_widget_show(image3);
    gtk_box_pack_start(GTK_BOX(hbox5), image3, FALSE, FALSE, 0);

    label10 = gtk_label_new_with_mnemonic(_("Close"));
    gtk_widget_show(label10);
    gtk_box_pack_start(GTK_BOX(hbox5), label10, FALSE, FALSE, 0);

    label3 = gtk_label_new(_("label3"));
    gtk_widget_show(label3);
    gtk_frame_set_label_widget(GTK_FRAME(f_lang_menu), label3);

    sb_lang = gtk_statusbar_new();
    gtk_widget_show(sb_lang);
    gtk_box_pack_start(GTK_BOX(vbox_lang), sb_lang, FALSE, FALSE, 0);

    g_signal_connect((gpointer) b_lang_sel, "clicked",
                     G_CALLBACK(on_b_lang_sel_clicked), NULL);
    g_signal_connect((gpointer) b_lang_OK, "clicked",
                     G_CALLBACK(on_b_lang_OK_clicked), NULL);
    g_signal_connect((gpointer) b_lang_new, "clicked",
                     G_CALLBACK(on_b_lang_new_clicked), NULL);
    g_signal_connect((gpointer) b_lang_del, "clicked",
                     G_CALLBACK(on_b_lang_del_clicked), NULL);
    g_signal_connect((gpointer) b_lang_clr, "clicked",
                     G_CALLBACK(on_b_lang_clr_clicked), NULL);
    g_signal_connect((gpointer) b_lang_close, "clicked",
                     G_CALLBACK(on_b_lang_close_clicked), NULL);

    /* Store pointers to all widgets, for use by lookup_widget(). */
    GLADE_HOOKUP_OBJECT_NO_REF(tdb_langwin, tdb_langwin, "tdb_langwin");
    GLADE_HOOKUP_OBJECT(tdb_langwin, vbox_lang, "vbox_lang");
    GLADE_HOOKUP_OBJECT(tdb_langwin, f_lang_mand, "f_lang_mand");
    GLADE_HOOKUP_OBJECT(tdb_langwin, hbox_lang_mand, "hbox_lang_mand");
    GLADE_HOOKUP_OBJECT(tdb_langwin, table_lang_mand, "table_lang_mand");
    GLADE_HOOKUP_OBJECT(tdb_langwin, l_lang, "l_lang");
    GLADE_HOOKUP_OBJECT(tdb_langwin, l_lang_code, "l_lang_code");
    GLADE_HOOKUP_OBJECT(tdb_langwin, entry1, "entry1");
    GLADE_HOOKUP_OBJECT(tdb_langwin, entry2, "entry2");
    GLADE_HOOKUP_OBJECT(tdb_langwin, b_lang_sel, "b_lang_sel");
    GLADE_HOOKUP_OBJECT(tdb_langwin, image2, "image2");
    GLADE_HOOKUP_OBJECT(tdb_langwin, l_lang_mandatory, "l_lang_mandatory");
    GLADE_HOOKUP_OBJECT(tdb_langwin, f_lang_opt, "f_lang_opt");
    GLADE_HOOKUP_OBJECT(tdb_langwin, table_lang_opt, "table_lang_opt");
    GLADE_HOOKUP_OBJECT(tdb_langwin, l_lang_diaolog, "l_lang_diaolog");
    GLADE_HOOKUP_OBJECT(tdb_langwin, c_lang_out, "c_lang_out");
    GLADE_HOOKUP_OBJECT(tdb_langwin, c_lang_labs, "c_lang_labs");
    GLADE_HOOKUP_OBJECT(tdb_langwin, c_lang_dialog, "c_lang_dialog");
    GLADE_HOOKUP_OBJECT(tdb_langwin, alignment3, "alignment3");
    GLADE_HOOKUP_OBJECT(tdb_langwin, hbox6, "hbox6");
    GLADE_HOOKUP_OBJECT(tdb_langwin, image4, "image4");
    GLADE_HOOKUP_OBJECT(tdb_langwin, label11, "label11");
    GLADE_HOOKUP_OBJECT(tdb_langwin, l_lang_opt, "l_lang_opt");
    GLADE_HOOKUP_OBJECT(tdb_langwin, f_lang_menu, "f_lang_menu");
    GLADE_HOOKUP_OBJECT(tdb_langwin, hbox_lang_menu, "hbox_lang_menu");
    GLADE_HOOKUP_OBJECT(tdb_langwin, b_lang_OK, "b_lang_OK");
    GLADE_HOOKUP_OBJECT(tdb_langwin, alignment1, "alignment1");
    GLADE_HOOKUP_OBJECT(tdb_langwin, hbox4, "hbox4");
    GLADE_HOOKUP_OBJECT(tdb_langwin, image1, "image1");
    GLADE_HOOKUP_OBJECT(tdb_langwin, label9, "label9");
    GLADE_HOOKUP_OBJECT(tdb_langwin, b_lang_new, "b_lang_new");
    GLADE_HOOKUP_OBJECT(tdb_langwin, alignment4, "alignment4");
    GLADE_HOOKUP_OBJECT(tdb_langwin, hbox7, "hbox7");
    GLADE_HOOKUP_OBJECT(tdb_langwin, image5, "image5");
    GLADE_HOOKUP_OBJECT(tdb_langwin, label12, "label12");
    GLADE_HOOKUP_OBJECT(tdb_langwin, b_lang_del, "b_lang_del");
    GLADE_HOOKUP_OBJECT(tdb_langwin, alignment5, "alignment5");
    GLADE_HOOKUP_OBJECT(tdb_langwin, hbox8, "hbox8");
    GLADE_HOOKUP_OBJECT(tdb_langwin, image6, "image6");
    GLADE_HOOKUP_OBJECT(tdb_langwin, label13, "label13");
    GLADE_HOOKUP_OBJECT(tdb_langwin, b_lang_clr, "b_lang_clr");
    GLADE_HOOKUP_OBJECT(tdb_langwin, alignment6, "alignment6");
    GLADE_HOOKUP_OBJECT(tdb_langwin, hbox9, "hbox9");
    GLADE_HOOKUP_OBJECT(tdb_langwin, image7, "image7");
    GLADE_HOOKUP_OBJECT(tdb_langwin, label14, "label14");
    GLADE_HOOKUP_OBJECT(tdb_langwin, b_lang_close, "b_lang_close");
    GLADE_HOOKUP_OBJECT(tdb_langwin, alignment2, "alignment2");
    GLADE_HOOKUP_OBJECT(tdb_langwin, hbox5, "hbox5");
    GLADE_HOOKUP_OBJECT(tdb_langwin, image3, "image3");
    GLADE_HOOKUP_OBJECT(tdb_langwin, label10, "label10");
    GLADE_HOOKUP_OBJECT(tdb_langwin, label3, "label3");
    GLADE_HOOKUP_OBJECT(tdb_langwin, sb_lang, "sb_lang");

    return tdb_langwin;
}
