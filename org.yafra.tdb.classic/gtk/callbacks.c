#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"


/* travelDB GTK GUI includes (includes mpnet.h with libXML as well) */
#include <mpgtk.h>


void on_tree_select_row_activated(GtkTreeView * treeview,
                                  GtkTreePath * path,
                                  GtkTreeViewColumn * column,
                                  gpointer user_data)
{

}


void on_tree_select_row_collapsed(GtkTreeView * treeview,
                                  GtkTreeIter * iter,
                                  GtkTreePath * path,
                                  gpointer user_data)
{

}


void on_tree_select_row_expanded(GtkTreeView * treeview,
                                 GtkTreeIter * iter,
                                 GtkTreePath * path,
                                 gpointer user_data)
{

}


void on_b_select_cancel_clicked(GtkButton * button,
                                gpointer user_data)
{
	extern int DebugFlag;
	GtkWidget *sel;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "close and hide selection dialog");

	sel = lookup_widget( GTK_WIDGET(button), "tdb_select");
	gtk_widget_hide(sel);
	/*	gtk_widget_destroy(sel); */

}


void on_b_select_ok_clicked(GtkButton * button,
                            gpointer user_data)
{

}
