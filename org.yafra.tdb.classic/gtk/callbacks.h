#include <gtk/gtk.h>


void on_mb_save_activate(GtkMenuItem * menuitem,
                         gpointer user_data);

void on_mb_print_activate(GtkMenuItem * menuitem,
                          gpointer user_data);

void on_mb_exit_activate(GtkMenuItem * menuitem,
                         gpointer user_data);

void on_mb_copy_activate(GtkMenuItem * menuitem,
                         gpointer user_data);

void on_mp_cut_activate(GtkMenuItem * menuitem,
                        gpointer user_data);

void on_mb_past_activate(GtkMenuItem * menuitem,
                         gpointer user_data);

void on_mb_opts_activate(GtkMenuItem * menuitem,
                         gpointer user_data);

void on_mb_package_activate(GtkMenuItem * menuitem,
                            gpointer user_data);

void on_mb_service_activate(GtkMenuItem * menuitem,
                            gpointer user_data);

void on_mb_reservation_activate(GtkMenuItem * menuitem,
                                gpointer user_data);

void on_mb_flight_activate(GtkMenuItem * menuitem,
                           gpointer user_data);

void on_mb_lang_activate(GtkMenuItem * menuitem,
                         gpointer user_data);

void on_mb_about_activate(GtkMenuItem * menuitem,
                          gpointer user_data);

void on_logon_clicked(GtkButton * button,
                      gpointer user_data);

void on_logon_cancel_clicked(GtkButton * button,
                             gpointer user_data);

void on_b_lang_sel_clicked(GtkButton * button,
                           gpointer user_data);

void on_b_lang_OK_clicked(GtkButton * button,
                          gpointer user_data);

void on_b_lang_new_clicked(GtkButton * button,
                           gpointer user_data);

void on_b_lang_del_clicked(GtkButton * button,
                           gpointer user_data);

void on_b_lang_clr_clicked(GtkButton * button,
                           gpointer user_data);

void on_b_lang_close_clicked(GtkButton * button,
                             gpointer user_data);

void on_b_about_close_clicked(GtkButton * button,
                              gpointer user_data);

void on_b_exit_cancel_clicked(GtkButton * button,
                              gpointer user_data);

void on_b_exit_ok_clicked(GtkButton * button,
                          gpointer user_data);

void on_tree_select_row_activated(GtkTreeView * treeview,
                                  GtkTreePath * path,
                                  GtkTreeViewColumn * column,
                                  gpointer user_data);

void on_tree_select_row_collapsed(GtkTreeView * treeview,
                                  GtkTreeIter * iter,
                                  GtkTreePath * path,
                                  gpointer user_data);

void on_tree_select_row_expanded(GtkTreeView * treeview,
                                 GtkTreeIter * iter,
                                 GtkTreePath * path,
                                 gpointer user_data);

void on_b_select_cancel_clicked(GtkButton * button,
                                gpointer user_data);

void on_b_select_ok_clicked(GtkButton * button,
                            gpointer user_data);
