/*
 * Copyright(c) 1992 Bell Communications Research, Inc. (Bellcore)
 *                        All rights reserved
 * Permission to use, copy, modify and distribute this material for
 * any purpose and without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies, and that the name of Bellcore not be used in advertising
 * or publicity pertaining to this material without the specific,
 * prior written permission of an authorized representative of
 * Bellcore.
 *
 * BELLCORE MAKES NO REPRESENTATIONS AND EXTENDS NO WARRANTIES, EX-
 * PRESS OR IMPLIED, WITH RESPECT TO THE SOFTWARE, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR ANY PARTICULAR PURPOSE, AND THE WARRANTY AGAINST IN-
 * FRINGEMENT OF PATENTS OR OTHER INTELLECTUAL PROPERTY RIGHTS.  THE
 * SOFTWARE IS PROVIDED "AS IS", AND IN NO EVENT SHALL BELLCORE OR
 * ANY OF ITS AFFILIATES BE LIABLE FOR ANY DAMAGES, INCLUDING ANY
 * LOST PROFITS OR OTHER INCIDENTAL OR CONSEQUENTIAL DAMAGES RELAT-
 * ING TO THE SOFTWARE.
 *
 * MatrixWidget Author: Andrew Wason, Bellcore, aw@bae.bellcore.com
 */

#include <Xm/Xm.h>
#include <Xbae/MatrixP.h>
#include <Xbae/Actions.h>
#include <Xbae/Utils.h>
#include <Xbae/Clip.h>

/*
 * Public.c created by Andrew Lister (7 August, 1995)
 */

/*
 * Public interface to set_cell method
 */
void
XbaeMatrixSetCell(w, row, column, value )
Widget w;
int row;
int column;
const String value;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the set_cell method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.set_cell)
	((XbaeMatrixWidget) w, row, column, value, True);
}


/*
 * Public interface to edit_cell method
 */
void
XbaeMatrixEditCell(w, row, column)
Widget w;
int row, column;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the edit_cell method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.edit_cell)
	((XbaeMatrixWidget) w, row, column);

    XmProcessTraversal(TextChild(((XbaeMatrixWidget) w)), XmTRAVERSE_CURRENT);
}

/*
 * Public interface to select_cell method
 */
void
XbaeMatrixSelectCell(w, row, column)
Widget w;
int row, column;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the select_cell method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.select_cell)
	((XbaeMatrixWidget) w, row, column);
}

/*
 * Public interface to select_row method
 */
void
XbaeMatrixSelectRow(w, row)
Widget w;
int row;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the select_row method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.select_row)
	((XbaeMatrixWidget) w, row);
}

/*
 * Public interface to select_column method
 */
void
XbaeMatrixSelectColumn(w, column)
Widget w;
int column;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the select_column method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.select_column)
	((XbaeMatrixWidget) w, column);
}

/*
 * Public interface to deselect_all method
 */
void
XbaeMatrixDeselectAll(w)
Widget w;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
     * Call the deselect_all method
     */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.deselect_all)
	((XbaeMatrixWidget) w);
}

/*
 * Public interface to deselect_cell method
 */
void
XbaeMatrixDeselectCell(w, row, column)
Widget w;
int row;
int column;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
     * Call the deselect_cell method
     */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.deselect_cell)
	((XbaeMatrixWidget) w, row, column);
}

/*
 * Public interface to deselect_row method
 */
void
XbaeMatrixDeselectRow(w, row)
Widget w;
int row;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the deselect_row method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.deselect_row)
	((XbaeMatrixWidget) w, row);
}

/*
 * Public interface to deselect_column method
 */
void
XbaeMatrixDeselectColumn(w, column)
Widget w;
int column;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the deselect_column method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.deselect_column)
	((XbaeMatrixWidget) w, column);
}

/*
 * Public interface to get_cell method
 */
String
XbaeMatrixGetCell(w, row, column)
Widget w;
int row, column;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the get_cell method
   */
    return (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.get_cell)
	((XbaeMatrixWidget) w, row, column);
}

/*
 * Public interface to commit_edit method
 */
Boolean
#if NeedFunctionPrototypes
XbaeMatrixCommitEdit(Widget w, Boolean unmap)
#else
XbaeMatrixCommitEdit(w, unmap)
Widget w;
Boolean unmap;
#endif
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the commit_edit method
   */
    return (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.commit_edit)
	((XbaeMatrixWidget) w, unmap);
}

/*
 * Public interface to cancel_edit method
 */
void
#if NeedFunctionPrototypes
XbaeMatrixCancelEdit(Widget w, Boolean unmap)
#else
XbaeMatrixCancelEdit(w, unmap)
Widget w;
Boolean unmap;
#endif
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the cancel_edit method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.cancel_edit)
	((XbaeMatrixWidget) w, unmap);
}

/*
 * Public interface to add_rows method
 */
void
XbaeMatrixAddRows(w, position, rows, labels, colors, num_rows)
Widget w;
int position;
String *rows;
String *labels;
Pixel *colors;
int num_rows;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the add_rows method
   */
    ( *( ( XbaeMatrixWidgetClass )XtClass( w ) )->matrix_class.add_rows )
	( ( XbaeMatrixWidget ) w, position, rows, labels, colors, NULL,
	  num_rows );
}

/*
 * Public interface to delete_rows method
 */
void
XbaeMatrixDeleteRows(w, position, num_rows)
Widget w;
int position;
int num_rows;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
     * Call the delete_rows method
     */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.delete_rows)
	((XbaeMatrixWidget) w, position, num_rows);
}

/*
 * Public interface to add_columns method
 */
void
XbaeMatrixAddColumns(w, position, columns, labels, widths, max_lengths,
		     alignments, label_alignments, colors, num_columns)
Widget w;
int position;
String *columns;
String *labels;
short *widths;
int *max_lengths;
unsigned char *alignments;
unsigned char *label_alignments;
Pixel *colors;
int num_columns;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the add_columns method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.add_columns)
	((XbaeMatrixWidget) w, position, columns, labels, widths,
	 max_lengths, alignments, label_alignments, colors, NULL, num_columns);
}

/*
 * Public interface to delete_columns method
 */
void
XbaeMatrixDeleteColumns(w, position, num_columns)
Widget w;
int position;
int num_columns;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
     * Call the delete_columns method
     */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.delete_columns)
	((XbaeMatrixWidget) w, position, num_columns);
}

/*
 * Public interface to set_row_colors method
 */
void
XbaeMatrixSetRowColors(w, position, colors, num_colors)
Widget w;
int position;
Pixel *colors;
int num_colors;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the set_row_colors method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.set_row_colors)
	((XbaeMatrixWidget) w, position, colors, num_colors, False);
}

/*
 * Public interface to set_column_colors method
 */
void
XbaeMatrixSetColumnColors(w, position, colors, num_colors)
Widget w;
int position;
Pixel *colors;
int num_colors;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the set_column_colors method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.set_column_colors)
	((XbaeMatrixWidget) w, position, colors, num_colors, False);
}

/*
 * Public interface to set_cell_color method
 */
void
XbaeMatrixSetCellColor(w, row, column, color)
Widget w;
int row;
int column;
Pixel color;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the set_cell_color method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.set_cell_color)
	((XbaeMatrixWidget) w, row, column, color, False);
}

/*
 * Public interface to set_row_colors method
 */
void
XbaeMatrixSetRowBackgrounds(w, position, colors, num_colors)
Widget w;
int position;
Pixel *colors;
int num_colors;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the set_row_colors method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.set_row_colors)
	((XbaeMatrixWidget) w, position, colors, num_colors, True);
}

/*
 * Public interface to set_column_colors method
 */
void
XbaeMatrixSetColumnBackgrounds(w, position, colors, num_colors)
Widget w;
int position;
Pixel *colors;
int num_colors;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the set_column_colors method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.set_column_colors)
	((XbaeMatrixWidget) w, position, colors, num_colors, True);
}

/*
 * Public interface to set_cell_color method
 */
void
XbaeMatrixSetCellBackground(w, row, column, color)
Widget w;
int row;
int column;
Pixel color;
{
    /*
     * Make sure w is a Matrix or a subclass
     */
    XtCheckSubclass(w, xbaeMatrixWidgetClass, NULL);

    /*
   * Call the set_cell_color method
   */
    (*((XbaeMatrixWidgetClass) XtClass(w))->matrix_class.set_cell_color)
	((XbaeMatrixWidget) w, row, column, color, True);
}

/*
 * Help the user know what row & column he is in given an x & y (via an event).
 * Return True on success, False on failure.
 */
int
XbaeMatrixGetEventRowColumn(w, event, row, column)
Widget w;
XEvent * event;
int *row;
int *column;
{
    XbaeMatrixWidget mw;
    int x, y;
    CellType cell;

    if (!XtIsSubclass(w, xbaeMatrixWidgetClass))
	return (False);

    /* Convert the event to the correct XY for the matrix widget. */
    mw = (XbaeMatrixWidget) w;
    if (!xbaeEventToXY(mw, event, &x, &y, &cell))
	return (False);

    /* Convert the point to a row,column. If it does not pick a valid cell, then return. */
    if (!xbaeXYToRowCol(mw, &x, &y, row, column, cell))
	return (False);

    return (True);
}


/*
 * Help the programmer to know what row & column we are currently at.
 * Set the row & column to -1 if bad widget.  Maybe the program will core. :)
 */
void
XbaeMatrixGetCurrentCell(w, row, column)
Widget w;
int *row;
int *column;
{
    XbaeMatrixWidget mw;

    if (!XtIsSubclass(w, xbaeMatrixWidgetClass))
	*row = *column = -1;
    else
    {
	mw = (XbaeMatrixWidget)w;
	*row = mw->matrix.current_row;
	*column = mw->matrix.current_column;
    }
}


/*
 * Allow the programmer to call the Expose method directly if he feels
 * that it is really needed.
 */
void
XbaeMatrixRefresh(w)
Widget w;
{
    XbaeMatrixWidget mw = ( XbaeMatrixWidget )w;

    if (XtIsSubclass(w, xbaeMatrixWidgetClass) && XtIsRealized((Widget)mw))
    {
	/*
	 * Generate expose events on Matrix and Clip to force the redrawing.
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   0, 0,
		   0 /*Full Width*/, 0 /*Full Height*/,
		   True);
	XbaeClipRedraw(ClipChild(mw));
    }
}

/*
 *  XbaeMatrixVisibleRows()
 *
 *  This routine returns the number of rows that are visible in the matrix.
 *
 *  D. Craig Wilson  5-MAY-1995
 *      - Cloned from the local "xbaeAdjustTopRow(mw)" routine.
 */
int
XbaeMatrixVisibleRows( w )
Widget w;
{
    XbaeMatrixWidget    matrix = ( XbaeMatrixWidget ) w;

    int rows_visible = VISIBLE_HEIGHT(matrix) / ROW_HEIGHT(matrix);

    /*
     *  If we have less than one full row visible, then count it as a full row.
     */
    if ( rows_visible == 0 )
        rows_visible = 1;

    /*
     *  rows_visible might be inaccurate since Clip may not have been resized.
     *  Test this routine and see if we need to call XbaeMatrixRefresh() to
     *  ensure accuracy.
     */
    else if ( rows_visible > matrix->matrix.rows )
        rows_visible = matrix->matrix.rows;

    return ( rows_visible );

} /* XbaeMatrixVisibleRows */



/*
 *  XbaeMatrixVisibleColumns()
 *
 *  This routine returns the number of columns that are visible in the matrix.
 *
 *  D. Craig Wilson  5-MAY-1995
 *      - Cloned from the local "xbaeAdjustTopRow(mw)" routine.
 */
int
XbaeMatrixVisibleColumns ( w )
Widget w;
{
    XbaeMatrixWidget    matrix = ( XbaeMatrixWidget )w;

    int left_column;
    int right_column;

    xbaeGetVisibleColumns(matrix, &left_column, &right_column);

    return ( right_column - left_column + 1 );

} /* XbaeMatrixVisibleColumns */
