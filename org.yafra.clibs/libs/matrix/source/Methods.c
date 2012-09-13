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
 */

/*
 * Methods.c created by Andrew Lister (7 August, 1995)
 */
#include <Xm/Xm.h>
#include <X11/Intrinsic.h>
#include <Xbae/MatrixP.h>
#include <Xbae/Methods.h>
#include <Xbae/Actions.h>
#include <Xbae/ScrollMgr.h>
#include <Xbae/Utils.h>
#include <Xbae/ClipP.h>
#include <Xm/XmP.h>
#include <Xm/TextF.h>

/* #if !defined(XBAE_NEED_BCOPY) && defined(SVR4) */
#define bcopy(src, dest, n)	memmove(dest, src, n)
/* #endif */

static void AddRowsToTable P(( XbaeMatrixWidget mw, int position,
			       String *rows, String *labels, Pixel *colors,
			       Pixel *backgrounds, int num_rows ));
static void DeleteRowsFromTable P(( XbaeMatrixWidget mw, int position,
				    int num_rows ));
static void AddColumnsToTable P(( XbaeMatrixWidget mw, int position,
				  String *columns, String *labels,
				  short *widths, int *max_lengths,
				  unsigned char *alignments,
				  unsigned char *label_alignments,
				  Pixel *colors, Pixel *backgrounds,
				  int num_columns ));
static void DeleteColumnsFromTable P(( XbaeMatrixWidget mw, int position,
				       int num_columns ));
static Boolean DoCommitEdit P(( XbaeMatrixWidget mw ));

/*
 * Add rows to the internal cells data structure.
 * If rows or labels is NULL, add empty rows.
 */
static void
AddRowsToTable(mw, position, rows, labels, colors, backgrounds, num_rows)
XbaeMatrixWidget mw;
int position;
String *rows;
String *labels;
Pixel *colors;
Pixel *backgrounds;
int num_rows;
{
    int i, j;

    /*
     * Realloc a larger array of row pointers and a larger label array
     */
    mw->matrix.cells = (String **) XtRealloc((char *) mw->matrix.cells,
					     (mw->matrix.rows + num_rows) *
					     sizeof(String *));
    if (mw->matrix.row_labels)
	mw->matrix.row_labels =
	    (String *) XtRealloc((char *) mw->matrix.row_labels,
				 (mw->matrix.rows + num_rows) *
				 sizeof(String));
    if (mw->matrix.colors)
	mw->matrix.colors = (Pixel **) XtRealloc((char *) mw->matrix.colors,
						 (mw->matrix.rows + num_rows) *
						 sizeof(Pixel *));

    if (mw->matrix.cell_background)
	mw->matrix.colors =
	    (Pixel **) XtRealloc((char *) mw->matrix.cell_background,
				 (mw->matrix.rows + num_rows) *
				 sizeof(Pixel *));

    mw->matrix.selected_cells =
	(Boolean **) XtRealloc((char *) mw->matrix.selected_cells,
			       (mw->matrix.rows + num_rows) *
			       sizeof(Boolean *));

    /*
     * If we are inserting rows into the middle, we need to make room.
     * XXX we are assuming bcopy can handle overlapping moves.
     */
    if (position < mw->matrix.rows)
    {
	bcopy(&mw->matrix.cells[position],
	      &mw->matrix.cells[position + num_rows],
	      (mw->matrix.rows - position) * sizeof(String *));
	if (mw->matrix.row_labels)
	    bcopy(&mw->matrix.row_labels[position],
		  &mw->matrix.row_labels[position + num_rows],
		  (mw->matrix.rows - position) * sizeof(String));
	if (mw->matrix.colors)
	    bcopy(&mw->matrix.colors[position],
		  &mw->matrix.colors[position + num_rows],
		  (mw->matrix.rows - position) * sizeof(Pixel *));
	if (mw->matrix.cell_background)
	    bcopy(&mw->matrix.cell_background[position],
		  &mw->matrix.cell_background[position + num_rows],
		  (mw->matrix.rows - position) * sizeof(Pixel *));
	bcopy(&mw->matrix.selected_cells[position],
	      &mw->matrix.selected_cells[position + num_rows],
	      (mw->matrix.rows - position) * sizeof(Boolean *));
    }

    /*
     * Malloc a new row array for each new row. Copy the label for each row.
     * If no label was passed in, use a NULL String. Malloc a new Pixel
     * and Boolean row array for each new row.
     */
    for (i = 0; i < num_rows; i++)
    {
	mw->matrix.cells[i + position] =
	    (String *) XtMalloc(mw->matrix.columns * sizeof(String));
	if (mw->matrix.row_labels)
	    mw->matrix.row_labels[i + position] =
		labels ? XtNewString(labels[i]) : XtNewString("");
	if (mw->matrix.colors)
	    mw->matrix.colors[i + position] =
		(Pixel *) XtMalloc(mw->matrix.columns * sizeof(Pixel));
	if (mw->matrix.cell_background)
	    mw->matrix.cell_background[i + position] =
		(Pixel *) XtMalloc(mw->matrix.columns * sizeof(Pixel));
	mw->matrix.selected_cells[i + position] =
	    (Boolean *) XtMalloc(mw->matrix.columns * sizeof(Boolean));
    }

    /*
     * Copy the rows arrays passed in into each new row, or if NULL
     * was passed in initialize each row to NULL Strings. Copy the colors
     * arrays passed in into each new row, if NULL was passed use foreground.
     */
    for (i = 0; i < num_rows; i++)
	for (j = 0; j < mw->matrix.columns; j++)
	{
	    mw->matrix.cells[i + position][j] =
		rows
		? XtNewString(rows[i * mw->matrix.columns + j])
		: XtNewString("");
	    if (mw->matrix.colors)
		mw->matrix.colors[i + position][j] =
		    colors ? colors[i] : mw->manager.foreground;
	    if (mw->matrix.cell_background)
		mw->matrix.cell_background[i + position][j] =
		    backgrounds ? backgrounds[i] : mw->core.background_pixel;
	    mw->matrix.selected_cells[i + position][j] = False;
	}

    mw->matrix.rows += num_rows;
}

/*
 * Delete rows from the internal cells data structure.
 */
static void
DeleteRowsFromTable(mw, position, num_rows)
XbaeMatrixWidget mw;
int position;
int num_rows;
{
    int i, j;

    /*
     * We don't bother to realloc, we will just have some wasted space.
     * XXX is this a problem?
     */

    /*
     * Free all the cells in the rows being deleted and the rows themselves.
     * Also free the String row labels.  Free the color arrays for the rows
     * being deleted.
     */
    for (i = position; i < position + num_rows; i++)
    {
	for (j = 0; j < mw->matrix.columns; j++)
	    XtFree((XtPointer) mw->matrix.cells[i][j]);
	XtFree((XtPointer) mw->matrix.cells[i]);
	if (mw->matrix.row_labels)
	    XtFree((XtPointer) mw->matrix.row_labels[i]);
	if (mw->matrix.colors)
	    XtFree((XtPointer) mw->matrix.colors[i]);
	if (mw->matrix.cell_background)
	    XtFree((XtPointer) mw->matrix.cell_background[i]);
	XtFree((XtPointer) mw->matrix.selected_cells[i]);
    }

    /*
     * Copy those rows which are below the ones deleted, up.
     * (unless we deleted rows from the bottom).
     * XXX we assume bcopy can handle overlapping moves
     */
    if (position + num_rows < mw->matrix.rows)
    {
	bcopy(&mw->matrix.cells[position + num_rows],
	      &mw->matrix.cells[position],
	      (mw->matrix.rows - position - num_rows) * sizeof(String *));
	if (mw->matrix.row_labels)
	    bcopy(&mw->matrix.row_labels[position + num_rows],
		  &mw->matrix.row_labels[position],
		  (mw->matrix.rows - position - num_rows) * sizeof(String));
	if (mw->matrix.colors)
	    bcopy(&mw->matrix.colors[position + num_rows],
		  &mw->matrix.colors[position],
		  (mw->matrix.rows - position - num_rows) * sizeof(Pixel *));
	if (mw->matrix.cell_background)
	    bcopy(&mw->matrix.cell_background[position + num_rows],
		  &mw->matrix.cell_background[position],
		  (mw->matrix.rows - position - num_rows) * sizeof(Pixel *));
	bcopy(&mw->matrix.selected_cells[position + num_rows],
	      &mw->matrix.selected_cells[position],
	      (mw->matrix.rows - position - num_rows) * sizeof(Boolean *));
    }

    mw->matrix.rows -= num_rows;
}

/*
 * Add columns to the internal cells data structure.
 * If columns or labels is NULL, add empty columns.
 * If max_lengths is NULL, widths will be used.
 * If alignments is NULL, use XmALIGNMENT_BEGINNING.
 * If label_alignments is NULL, use alignments, or if it is NULL
 *   XmALIGNMENT_BEGINNING.
 * widths must not be NULL.
 */
static void
AddColumnsToTable(mw, position, columns, labels, widths, max_lengths,
		  alignments, label_alignments, colors, backgrounds,
		  num_columns)
XbaeMatrixWidget mw;
int position;
String *columns;
String *labels;
short *widths;
int *max_lengths;
unsigned char *alignments;
unsigned char *label_alignments;
Pixel *colors;
Pixel *backgrounds;
int num_columns;
{
    int i, j;

    /*
     * Realloc larger cells, widths, max_lengths, alignments,
     * colors, selected_cells, labels and label lines arrays.
     */

    for (i = 0; i < mw->matrix.rows; i++)
    {
	mw->matrix.cells[i] =
	    (String *) XtRealloc((char *) mw->matrix.cells[i],
				 (mw->matrix.columns + num_columns) *
				 sizeof(String));
	if (mw->matrix.colors)
	    mw->matrix.colors[i] =
		(Pixel *) XtRealloc((char *) mw->matrix.colors[i],
				    (mw->matrix.columns + num_columns) *
				    sizeof(Pixel));
	if (mw->matrix.cell_background)
	    mw->matrix.cell_background[i] =
		(Pixel *) XtRealloc((char *) mw->matrix.cell_background[i],
				    (mw->matrix.columns + num_columns) *
				    sizeof(Pixel));
	mw->matrix.selected_cells[i] =
	    (Boolean *) XtRealloc((char *) mw->matrix.selected_cells[i],
				  (mw->matrix.columns + num_columns) *
				  sizeof(Boolean));
    }

    mw->matrix.column_widths =
	(short *) XtRealloc((char *) mw->matrix.column_widths,
			    (mw->matrix.columns + num_columns) *
			    sizeof(short));

    if (mw->matrix.column_max_lengths)
	mw->matrix.column_max_lengths =
	    (int *) XtRealloc((char *) mw->matrix.column_max_lengths,
			      (mw->matrix.columns + num_columns) *
			      sizeof(int));

    if (mw->matrix.column_alignments)
	mw->matrix.column_alignments =
	    (unsigned char *)
	    XtRealloc((char *) mw->matrix.column_alignments,
		      (mw->matrix.columns + num_columns) *
		      sizeof(unsigned char));

    if (mw->matrix.column_label_alignments)
	mw->matrix.column_label_alignments =
	    (unsigned char *) XtRealloc((char *) mw->matrix.
					column_label_alignments,
					(mw->matrix.columns + num_columns) *
					sizeof(unsigned char));

    if (mw->matrix.column_labels)
    {
	mw->matrix.column_labels =
	    (String *) XtRealloc((char *) mw->matrix.column_labels,
				 (mw->matrix.columns + num_columns) *
				 sizeof(String));
	mw->matrix.column_label_lines =
	    (ColumnLabelLines) XtRealloc((char *) mw->matrix.column_label_lines,
					 (mw->matrix.columns + num_columns) *
					 sizeof(ColumnLabelLinesRec));
    }

    /*
     * If we are inserting columns into the middle, we need to make room.
     * XXX we are assuming bcopy can handle overlapping moves.
     */
    if (position < mw->matrix.columns)
    {
	bcopy(&mw->matrix.column_widths[position],
	      &mw->matrix.column_widths[position + num_columns],
	      (mw->matrix.columns - position) * sizeof(short));

	if (mw->matrix.column_max_lengths)
	    bcopy(&mw->matrix.column_max_lengths[position],
		  &mw->matrix.column_max_lengths[position + num_columns],
		  (mw->matrix.columns - position) * sizeof(int));

	if (mw->matrix.column_alignments)
	    bcopy(&mw->matrix.column_alignments[position],
		  &mw->matrix.column_alignments[position + num_columns],
		  (mw->matrix.columns - position) * sizeof(unsigned char));

	if (mw->matrix.column_label_alignments)
	    bcopy(&mw->matrix.column_label_alignments[position],
		  &mw->matrix.column_label_alignments[position + num_columns],
		  (mw->matrix.columns - position) * sizeof(unsigned char));

	if (mw->matrix.column_labels)
	{
	    bcopy(&mw->matrix.column_labels[position],
		  &mw->matrix.column_labels[position + num_columns],
		  (mw->matrix.columns - position) * sizeof(String));
	    bcopy(&mw->matrix.column_label_lines[position],
		  &mw->matrix.column_label_lines[position + num_columns],
		  (mw->matrix.columns - position) *
		  sizeof(ColumnLabelLinesRec));
	}

	/*
	 * Shift the columns in each row.
	 */
	for (i = 0; i < mw->matrix.rows; i++)
	{
	    bcopy(&mw->matrix.cells[i][position],
		  &mw->matrix.cells[i][position + num_columns],
		  (mw->matrix.columns - position) * sizeof(String));
	    if (mw->matrix.colors)
		bcopy(&mw->matrix.colors[i][position],
		      &mw->matrix.colors[i][position + num_columns],
		      (mw->matrix.columns - position) * sizeof(Pixel));
	    if (mw->matrix.cell_background)
		bcopy(&mw->matrix.cell_background[i][position],
		      &mw->matrix.cell_background[i][position + num_columns],
		      (mw->matrix.columns - position) * sizeof(Pixel));
	    bcopy(&mw->matrix.selected_cells[i][position],
		  &mw->matrix.selected_cells[i][position + num_columns],
		  (mw->matrix.columns - position) * sizeof(Boolean));
	}
    }

    /*
     * Copy all of the passed in info into each new column
     * (except column_positions which will be recalculated below).
     * If columns or labels is NULL, add empty columns.
     * If max_lengths is NULL, widths will be used.
     * If alignments is NULL, use XmALIGNMENT_BEGINNING.
     * If label_alignments is NULL, use XmALIGNMENT_BEGINNING
     * If labels is NULL, use NULL strings.
     * If colors is NULL, use foreground.
     */
    for (j = 0; j < num_columns; j++)
    {
	mw->matrix.column_widths[j + position] = widths[j];

	if (mw->matrix.column_max_lengths)
	    mw->matrix.column_max_lengths[j + position] =
		max_lengths ? max_lengths[j] : (int) widths[j];

	if (mw->matrix.column_alignments)
	    mw->matrix.column_alignments[j + position] =
		alignments ? alignments[j] : XmALIGNMENT_BEGINNING;

	if (mw->matrix.column_label_alignments)
	    mw->matrix.column_label_alignments[j + position] =
		label_alignments ? label_alignments[j] : XmALIGNMENT_BEGINNING;

	if (mw->matrix.column_labels)
	{
	    mw->matrix.column_labels[j + position] =
		labels ? XtNewString(labels[j]) : XtNewString("");
	    xbaeParseColumnLabel(mw->matrix.column_labels[j + position],
			     &mw->matrix.column_label_lines[j + position]);
	}

	/*
	 * Add this new column to each row.
	 */
	for (i = 0; i < mw->matrix.rows; i++)
	{
	    mw->matrix.cells[i][j + position] =
		columns ? XtNewString(columns[i * num_columns + j]) :
		XtNewString("");
	    if (mw->matrix.colors)
		mw->matrix.colors[i][j + position] =
		    colors ? colors[j] : mw->manager.foreground;
	    if (mw->matrix.cell_background)
		mw->matrix.cell_background[i][j + position] =
		    backgrounds ? backgrounds[j] : mw->core.background_pixel;
	    mw->matrix.selected_cells[i][j + position] = False;
	}
    }

    mw->matrix.columns += num_columns;
    xbaeGetCellTotalWidth(mw);

    /*
     * See if the max number of column label lines changed
     */
    if (mw->matrix.column_labels)
    {
	int end;

	end = position + num_columns;
	for (i = position; i < end; i++)
	    if (mw->matrix.column_label_lines[i].lines >
		mw->matrix.column_label_maxlines)
		mw->matrix.column_label_maxlines =
		    mw->matrix.column_label_lines[i].lines;
    }

    /*
     * Recalculate the column positions
     */
    FreeColumnPositions(mw);
    mw->matrix.column_positions = CreateColumnPositions(mw);
    xbaeGetColumnPositions(mw);
}

/*
 * Delete columns from the internal cells data structure.
 */
static void
DeleteColumnsFromTable(mw, position, num_columns)
XbaeMatrixWidget mw;
int position;
int num_columns;
{
    int i, j;

    /*
     * Free all the cells in the columns being deleted.
     * Also free the String column labels and the associated ColumnLabelLines
     * lengths arrays.
     */
    for (j = position; j < position + num_columns; j++)
    {
	for (i = 0; i < mw->matrix.rows; i++)
	    XtFree((XtPointer) mw->matrix.cells[i][j]);
	if (mw->matrix.column_labels)
	{
	    XtFree((XtPointer) mw->matrix.column_labels[j]);
	    XtFree((XtPointer) mw->matrix.column_label_lines[j].lengths);
	}
    }

    /*
     * Shift those columns after the ones being deleted, left.
     * (unless we deleted columns from the right).
     * XXX we assume bcopy can handle overlapping moves
     */
    if (position + num_columns < mw->matrix.columns)
    {
	bcopy(&mw->matrix.column_widths[position + num_columns],
	      &mw->matrix.column_widths[position],
	      (mw->matrix.columns - position - num_columns) * sizeof(short));

	if (mw->matrix.column_max_lengths)
	    bcopy(&mw->matrix.column_max_lengths[position + num_columns],
		  &mw->matrix.column_max_lengths[position],
		  (mw->matrix.columns - position - num_columns) * sizeof(int));

	if (mw->matrix.column_alignments)
	    bcopy(&mw->matrix.column_alignments[position + num_columns],
		  &mw->matrix.column_alignments[position],
		  (mw->matrix.columns - position - num_columns) *
		  sizeof(unsigned char));

	if (mw->matrix.column_label_alignments)
	    bcopy(&mw->matrix.column_label_alignments[position + num_columns],
		  &mw->matrix.column_label_alignments[position],
		  (mw->matrix.columns - position - num_columns) *
		  sizeof(unsigned char));

	if (mw->matrix.column_labels)
	{
	    bcopy(&mw->matrix.column_labels[position + num_columns],
		  &mw->matrix.column_labels[position],
		  (mw->matrix.columns - position - num_columns) *
		  sizeof(String));
	    bcopy(&mw->matrix.column_label_lines[position + num_columns],
		  &mw->matrix.column_label_lines[position],
		  (mw->matrix.columns - position - num_columns) *
		  sizeof(ColumnLabelLinesRec));
	}

	/*
	 * Shift the columns in each row.
	 */
	for (i = 0; i < mw->matrix.rows; i++)
	{
	    bcopy(&mw->matrix.cells[i][position + num_columns],
		  &mw->matrix.cells[i][position],
		  (mw->matrix.columns - position - num_columns) *
		  sizeof(String));
	    if (mw->matrix.colors)
		bcopy(&mw->matrix.colors[i][position + num_columns],
		      &mw->matrix.colors[i][position],
		      (mw->matrix.columns - position - num_columns) *
		      sizeof(Pixel));
	    if (mw->matrix.cell_background)
		bcopy(&mw->matrix.cell_background[i][position + num_columns],
		      &mw->matrix.cell_background[i][position],
		      (mw->matrix.columns - position - num_columns) *
		      sizeof(Pixel));
	    bcopy(&mw->matrix.selected_cells[i][position + num_columns],
		  &mw->matrix.selected_cells[i][position],
		  (mw->matrix.columns - position - num_columns) *
		  sizeof(Boolean));
	}
    }

    mw->matrix.columns -= num_columns;
    xbaeGetCellTotalWidth(mw);

    /*
     * See if the max number of column label lines changed
     */
    if (mw->matrix.column_labels)
    {
	mw->matrix.column_label_maxlines =
	    mw->matrix.column_label_lines[0].lines;
	for (i = 1; i < mw->matrix.columns; i++)
	    if (mw->matrix.column_label_lines[i].lines >
		mw->matrix.column_label_maxlines)
		mw->matrix.column_label_maxlines =
		    mw->matrix.column_label_lines[i].lines;
    }

    /*
     * Recalculate the column positions
     */
    FreeColumnPositions(mw);
    mw->matrix.column_positions = CreateColumnPositions(mw);
    xbaeGetColumnPositions(mw);
}

/*
 * Matrix set_cell method
 */
void
#if NeedFunctionPrototypes
xbaeSetCell(XbaeMatrixWidget mw, int row, int column, const String value,
	Boolean update_text)
#else
xbaeSetCell(mw, row, column, value, update_text)
XbaeMatrixWidget mw;
int row;
int column;
const String value;
Boolean update_text;
#endif
{
    if (row >= mw->matrix.rows || row < 0 ||
	column >= mw->matrix.columns || column < 0)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"xbaeSetCell", "badIndex", "XbaeMatrix",
			"XbaeMatrix: Row or column parameter out of bounds for xbaeSetCell.",
			NULL, 0);
	return;
    }

    /*
     * Store the new value in the cell.
     */
    XtFree((XtPointer) mw->matrix.cells[row][column]);
    mw->matrix.cells[row][column] = XtNewString(value);

    /*
     * Draw the cell.
     */
    if (xbaeIsCellVisible(mw, row, column))
    {
	xbaeClearCell(mw, row, column);
	xbaeDrawCell(mw, row, column);

	if (mw->matrix.cell_shadow_thickness)
	{
	    if (XmGRID_ROW_SHADOW == mw->matrix.grid_type)
		xbaeDrawRowShadow(mw, row, GRID_REDRAW_EDIT);
	    else if (XmGRID_COLUMN_SHADOW == mw->matrix.grid_type)
		xbaeDrawColumnShadow(mw, column, GRID_REDRAW_EDIT);
	}
    }

    /*
     * If we are editing this cell, load the textField too if update_text set.
     * XXX there is a bug in XmTextFieldSetString in Motif 1.1.3
     *     it doesn't handle "" strings well.  Use SetValues instead.
     */
    if (update_text && XtIsManaged(TextChild(mw)) &&
	mw->matrix.current_row == row && mw->matrix.current_column == column)
    {
	if (value[0] == '\0')
	    XtVaSetValues(TextChild(mw),
			  XmNvalue, value,
			  NULL);
	else
	    XmTextFieldSetString(TextChild(mw), value);
    }
}

static Boolean
DoCommitEdit(mw)
XbaeMatrixWidget mw;
{
    String cell;

    if (!XtIsManaged(TextChild(mw)))
	return True;

    /*
     * Get the value the user entered in the textField (this is a copy)
     */
    cell = XmTextFieldGetString(TextChild(mw));

    /*
     * Call the leaveCellCallback to see if we can leave the current cell.
     */
    if (mw->matrix.leave_cell_callback)
    {
	XbaeMatrixLeaveCellCallbackStruct call_data;

	call_data.reason = XbaeLeaveCellReason;
	call_data.row = mw->matrix.current_row;
	call_data.column = mw->matrix.current_column;
	call_data.value = cell;
	call_data.doit = True;

	XtCallCallbackList((Widget) mw, mw->matrix.leave_cell_callback,
			   (XtPointer) & call_data);

	/*
	 * Application doesn't want to leave this cell. Make the cell visible
	 * and traverse to it so the user can see where they screwed up.
	 */
	if (!call_data.doit)
	{
	    xbaeMakeCellVisible(mw,
			    mw->matrix.current_row, mw->matrix.current_column);
	    XmProcessTraversal(TextChild(mw), XmTRAVERSE_CURRENT);
	    XtFree((XtPointer) cell);
	    return False;
	}

	/*
	 * Use the applications value if it is different.
	 * If the application modified the string inplace, we will pick that
	 * up automatically.
	 */
	if (call_data.value != cell)
	{
	    XtFree((XtPointer) cell);
	    cell = call_data.value;
	}
    }

    /*
     * Call the set_cell method to store the new value in the cell and redraw.
     */
    (*((XbaeMatrixWidgetClass) XtClass(mw))->matrix_class.set_cell)
	(mw, mw->matrix.current_row, mw->matrix.current_column, cell, False);

    XtFree((XtPointer) cell);

    return True;
}

/*
 * Position and size the scrollbars and clip widget for our new size.
 */
void
xbaeResize(mw)
XbaeMatrixWidget mw;
{
    int cell_width, cell_height, rows_visible;
    Boolean has_horiz, has_vert;
    int width = mw->core.width;
    int height = mw->core.height;

    /*
     * Full size of widget (no SBs needed) - may be very large
     */
    long int full_width = CELL_TOTAL_WIDTH(mw) + FIXED_COLUMN_WIDTH(mw) +
	TRAILING_FIXED_COLUMN_WIDTH(mw) + ROW_LABEL_WIDTH(mw) +
	2 * mw->manager.shadow_thickness;
    long int full_height = CELL_TOTAL_HEIGHT(mw) + FIXED_ROW_HEIGHT(mw) +
	TRAILING_FIXED_ROW_HEIGHT(mw) + COLUMN_LABEL_HEIGHT(mw) +
	2 * mw->manager.shadow_thickness;

    /*
     * Portion of cells which are visible in clip widget
     */
    int horiz_visible = CELL_TOTAL_WIDTH(mw) - HORIZ_ORIGIN(mw);
    int vert_visible = CELL_TOTAL_HEIGHT(mw) -
	VERT_ORIGIN(mw) * ROW_HEIGHT(mw);


    /*
     * If matrix is bigger in both dimensions, then we don't need either
     * SB. If both dimensions are smaller than matrix, then we need both
     * SBs. Otherwise, only one or the other dimension must be too small:
     *	- Get the dimensions assuming both SBs are mapped (subtract size
     *	  of SBs)
     *	- Flag both SBs as mapped
     *	- If the full_width is small enough that we won't need a HSB even
     *	  if the VSB is mapped, then unflag the HSB and reset the height
     *	- Next compare the full_height to the height just computed and decide
     *	  if we need a VSB (if we didn't need a HSB above, then we had reset
     *	  the height to not count the HSB)
     *
     * The whole point is, if we map one SB then we may need to map the
     * other one because of the space taken by the first one
     */
    if ((long)mw->core.width >= full_width && (long)mw->core.height >= full_height)
	has_horiz = has_vert = False;
    else if ((long)mw->core.width < full_width && (long)mw->core.height < full_height)
	has_horiz = has_vert = True;
    else
    {
	height -= HSCROLL_HEIGHT(mw);
	width -= VSCROLL_WIDTH(mw);

	has_horiz = has_vert = True;
	if (full_width <= width)
	{
	    height = mw->core.height;
	    has_horiz = False;
	}
	if (full_height <= height)
	    has_vert = False;
    }


    /*
     * If widget is smaller than full size, move/resize the scrollbar and
     * set sliderSize, also if cell_width/cell_height is greater than
     * the amount of cell area visible, then we need to drag the cells
     * back into the visible part of the clip widget and set the
     * scrollbar value.
     *
     * Otherwise, the widget is larger than full size, so set
     * cell_width/cell_height to size of cells and set origin to 0
     * to force full cell area to be displayed
     *
     * We also need to move the textField correspondingly
     */

    /*
     * We were resized smaller than our max width.
     */
    if (width < full_width)
    {

	/*
	 * Calculate the width of the non-fixed visible cells.
	 */
	cell_width = mw->core.width - (FIXED_COLUMN_WIDTH(mw) +
	     TRAILING_FIXED_COLUMN_WIDTH(mw) + ROW_LABEL_WIDTH(mw) +
	     2 * mw->manager.shadow_thickness);

	/*
	 * Subtract the VSB if we have one.
	 */
	if (has_vert)
	    cell_width -= VSCROLL_WIDTH(mw);

	if (cell_width <= 0)
	    cell_width = 1;

	/*
	 * If the window is not full height, then place the HSB at the edge
	 * of the window.  Is the window is larger than full height, then
	 * place the HSB immediately below the cell region.
	 */
	XtConfigureWidget(HorizScrollChild(mw),
			  FIXED_COLUMN_LABEL_OFFSET(mw),
			  height < full_height
			  ? (Position) (mw->core.height -
					(HorizScrollChild(mw)->core.height +
					 2 * HorizScrollChild(mw)->
					 core.border_width))
			  : (Position) (full_height + mw->matrix.space),
			  cell_width,
			  HorizScrollChild(mw)->core.height,
			  HorizScrollChild(mw)->core.border_width);

	/*
	 * If the cells are scrolled off to the left, then drag them
	 * back onto the screen.
	 */
	if (cell_width > horiz_visible)
	{
	    HORIZ_ORIGIN(mw) -= (cell_width - horiz_visible);

	    if (XtIsManaged(TextChild(mw)))
		XtMoveWidget(TextChild(mw),
			     TextChild(mw)->core.x +
			     (cell_width - horiz_visible),
			     TextChild(mw)->core.y);
	}

	/*
	 * Setup the HSB to reflect our new size.
	 */
	XtVaSetValues(HorizScrollChild(mw),
		      XmNpageIncrement, cell_width,
		      XmNsliderSize, cell_width,
		      XmNvalue, HORIZ_ORIGIN(mw),
		      NULL);
    }

    /*
     * We were resized larger than the our max width.  Drag the cells back
     * onto the screen if they were scrolled off to the left.
     */
    else
    {
	if (XtIsManaged(TextChild(mw)))
	    XtMoveWidget(TextChild(mw),
			 TextChild(mw)->core.x + HORIZ_ORIGIN(mw),
			 TextChild(mw)->core.y);

	cell_width = CELL_TOTAL_WIDTH(mw);
	HORIZ_ORIGIN(mw) = 0;
    }

    /*
     * We were resized smaller than our max height.
     */
    if (height < full_height)
    {

	/*
	 * Calculate the height of the non-fixed visible cells.
	 */
	cell_height = mw->core.height - (FIXED_ROW_HEIGHT(mw) + 
	     TRAILING_FIXED_ROW_HEIGHT(mw) + COLUMN_LABEL_HEIGHT(mw) +
	     2 * mw->manager.shadow_thickness);

	/*
	 * Subtract the HSB if we have one.
	 */
	if (has_horiz)
	    cell_height -= HSCROLL_HEIGHT(mw);

	if (cell_height <= 0)
	    cell_height = 1;

	/*
	 * If the window is not full width, then place the VSB at the edge
	 * of the window.  Is the window is larger than full width, then
	 * place the VSB immediately to the right of the cell region.
	 */
	XtConfigureWidget(VertScrollChild(mw),
			  width < full_width
			  ? (Position) (mw->core.width -
					(VertScrollChild(mw)->core.width +
					 2 * VertScrollChild(mw)->
					 core.border_width))
			  : (Position) full_width + mw->matrix.space,
			  FIXED_ROW_LABEL_OFFSET(mw),
			  VertScrollChild(mw)->core.width,
			  cell_height,
			  VertScrollChild(mw)->core.border_width);

	/*
	 * If the cells are scrolled off the top, then drag them
	 * back onto the screen.
	 */
	if (cell_height > vert_visible)
	{
	    int rows = (cell_height - vert_visible) / ROW_HEIGHT(mw);

	    VERT_ORIGIN(mw) -= rows;

	    if (XtIsManaged(TextChild(mw)))
		XtMoveWidget(TextChild(mw),
			     TextChild(mw)->core.x,
			     TextChild(mw)->core.y + rows * ROW_HEIGHT(mw));
	}

	/*
	 * Setup the VSB to reflect our new size.
	 */
	rows_visible = cell_height / ROW_HEIGHT(mw);
	XtVaSetValues(VertScrollChild(mw),
		      XmNpageIncrement, rows_visible <= 0 ? 1 : rows_visible,
		      XmNsliderSize, rows_visible <= 0 ? 1 : rows_visible,
		      XmNvalue, VERT_ORIGIN(mw),
		      NULL);
    }

    /*
     * We were resized larger than the our max height.	Drag the cells back
     * onto the screen if they were scrolled off the top.
     */
    else
    {
	if (XtIsManaged(TextChild(mw)))
	    XtMoveWidget(TextChild(mw),
			 TextChild(mw)->core.x,
			 TextChild(mw)->core.y +
			 VERT_ORIGIN(mw) * ROW_HEIGHT(mw));

	cell_height = CELL_TOTAL_HEIGHT(mw);
	rows_visible = mw->matrix.rows - mw->matrix.fixed_rows -
	    mw->matrix.trailing_fixed_rows;
	VERT_ORIGIN(mw) = 0;
    }

    /*
     * Map/unmap scrollbars based on flags set above
     */
    if (has_horiz)
	XtManageChild(HorizScrollChild(mw));
    else
	XtUnmanageChild(HorizScrollChild(mw));

    if (has_vert)
	XtManageChild(VertScrollChild(mw));
    else
	XtUnmanageChild(VertScrollChild(mw));

    /*
     * Now that we have cell_width & cell_height,
     * make the clip widget this size.	Height is truncated to the
     * nearest row.
     */
    XtConfigureWidget(ClipChild(mw),
		      FIXED_COLUMN_LABEL_OFFSET(mw),
		      FIXED_ROW_LABEL_OFFSET(mw),
		      cell_width,
		      rows_visible <= 0
		      ? cell_height
		      : rows_visible * ROW_HEIGHT(mw),
		      0);

    /*
     * Save the non-truncated height.  We need this so we can draw
     * the shadow correctly.
     */
    mw->matrix.cell_visible_height = cell_height;

    /*
     * Set the clip_mask in our clipping GCs.  This function relies on
     * the Clip widget being the correct size (above).
     */
    if (XtIsRealized((Widget)mw))
	xbaeSetClipMask(mw, CLIP_NONE);
}

/*
 * Matrix edit_cell method
 */
void
xbaeEditCell(mw, row, column)
XbaeMatrixWidget mw;
int row, column;
{
    Boolean edit = True;
    int x, y;
    Pixel fgcolor, bgcolor;
    Boolean alt;
    String string;
    Pixmap pixmap;
    
    if (row >= mw->matrix.rows || row < 0 ||
	column >= mw->matrix.columns || column < 0)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"editCell", "badIndex", "XbaeMatrix",
			"XbaeMatrix: Row or column parameter out of bounds for EditCell.",
			NULL, 0);
	return;
    }

    /*
     * Attempt to commit the edit in the current cell. Return if we fail.
     */
    if (!DoCommitEdit(mw))
	return;

    /*
     * Scroll the cell onto the screen
     */
    xbaeMakeCellVisible(mw, row, column);

    /*
     * Fixed cells are not editable
     */
    if (IS_FIXED(mw, row, column))
	return;

    /*
     * If we have an enterCellCallback, call it to see if the cell is
     * editable.
     */
    if (mw->matrix.enter_cell_callback)
    {
	XbaeMatrixEnterCellCallbackStruct call_data;

	call_data.reason = XbaeEnterCellReason;
	call_data.row = row;
	call_data.column = column;
	call_data.doit = True;
	XtCallCallbackList((Widget) mw, mw->matrix.enter_cell_callback,
			   (XtPointer) & call_data);

	edit = call_data.doit;
    }

    mw->matrix.current_row = row;
    mw->matrix.current_column = column;

    /*
     * Unmap the textField to avoid flashing.
     */
    if (XtIsManaged(TextChild(mw)) && XtIsRealized(TextChild(mw)))
	XtUnmapWidget(TextChild(mw));

    /*
     * Convert the row/column to an xy position and move the textField
     * to this position. (the xy position will be relative to the Clip
     * widget because only non-fixed cells are editable)
     */
    xbaeRowColToXY(mw, row, column, &x, &y);

    XtMoveWidget(TextChild(mw), 
 		 x + mw->matrix.cell_shadow_thickness,
 		 y + mw->matrix.cell_shadow_thickness);
    
    alt = (mw->matrix.alt_row_count && row >= (int)mw->matrix.fixed_rows)
        ? (((row - (int)mw->matrix.fixed_rows) / mw->matrix.alt_row_count) % 2)
        : False;
    if (mw->matrix.colors)
	fgcolor = mw->matrix.colors[row][column];
    else
	fgcolor = mw->manager.foreground;

    if (mw->matrix.text_background != mw->core.background_pixel)
	bgcolor = mw->matrix.text_background;
    else if (mw->matrix.cell_background && 
 	mw->matrix.cell_background[row][column] != mw->core.background_pixel )
	bgcolor = mw->matrix.cell_background[row][column];
    else
    {
	if (alt)
	    bgcolor = mw->matrix.odd_row_background;
	else
	    bgcolor = mw->matrix.even_row_background;
    }
    /*
     * If we're doing a drawCell, go ask the app what to put there.
     */
    if (mw->matrix.draw_cell_callback)
    {
	if (xbaeGetDrawCellValue(mw, row, column, &string, &pixmap, &bgcolor,
				 &fgcolor) == XbaePixmap)
      {
          /*
           * If we're showing a pixmap, we don't need the TextField.
           return;
           */

          /* temporarily turn pixmaps off */
          string = "";
      }
    }
    else
      string = mw->matrix.cells[row][column];


    /*
     * Setup the textField for the new cell. If the modifyVerify CB
     * rejects the new value, then it is the applications fault for
     * loading the cell with a bad value to begin with.
     */
    XtVaSetValues(TextChild(mw),
		  XmNvalue, string,
		  XmNwidth, COLUMN_WIDTH(mw, column) -
			mw->matrix.cell_shadow_thickness * 2,
		  XmNheight, ROW_HEIGHT(mw)
			- mw->matrix.cell_shadow_thickness * 2,
		  XmNmaxLength, mw->matrix.column_max_lengths ?
			mw->matrix.column_max_lengths[column] :
			(int) mw->matrix.column_widths[column],
		  XmNeditable, edit,
		  XmNcursorPositionVisible, edit,
		  XmNbackground, bgcolor,
		  XmNforeground, fgcolor,
		  NULL);

    /*
     * We need this to work around an XmTextField problem with
     * the I-beam and caret
     */
    if (edit)
	XmTextFieldSetInsertionPosition(TextChild(mw), strlen(string));

    /*
     * Manage and map the textField
     */
    XtManageChild(TextChild(mw));
    if (XtIsRealized(TextChild(mw)))
	XtMapWidget(TextChild(mw));
}

/*
 * Matrix select_cell method
 */
void
xbaeSelectCell(mw, row, column)
XbaeMatrixWidget mw;
int row, column;
{
    if (row >= mw->matrix.rows || row < 0 ||
	column >= mw->matrix.columns || column < 0)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"selectCell", "badIndex", "XbaeMatrix",
			"XbaeMatrix: Row or column parameter out of bounds for SelectCell.",
			NULL, 0);
	return;
    }

    /*
     * Scroll the cell onto the screen
     */
    if (mw->matrix.scroll_select)
	xbaeMakeCellVisible(mw, row, column);

    /*
     * If the cell is not already selected, select it and redraw it
     */
    if (!mw->matrix.selected_cells[row][column])
    {
	mw->matrix.selected_cells[row][column] = True;
	if (mw->matrix.scroll_select || xbaeIsCellVisible(mw, row, column))
	    xbaeDrawCell(mw, row, column);
    }
}

/*
 * Matrix select_row method
 */
void
xbaeSelectRow(mw, row)
XbaeMatrixWidget mw;
int row;
{
    int j, lc, rc;

    if (row >= mw->matrix.rows || row < 0)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"selectRow", "badIndex", "XbaeMatrix",
			"XbaeMatrix: Row out of bounds for SelectRow.",
			NULL, 0);
	return;
    }

    /*
     * Scroll the row onto the screen
     */
    if (mw->matrix.scroll_select)
	xbaeMakeRowVisible(mw, row);

    /*
     * If the row is not visible, there's no need to redraw
     */
    if( !mw->matrix.scroll_select && !xbaeIsRowVisible(mw, row) )
	return;
    /*
     * For each cell in the row, if the cell is not already selected,
     * select it and redraw it
     */
    xbaeGetVisibleColumns(mw, &lc, &rc);
    for (j = 0; j < mw->matrix.columns; j++)
    {
	if (!mw->matrix.selected_cells[row][j])
	{
	    mw->matrix.selected_cells[row][j] = True;
	    if ((j >= lc && j <= rc) || j < (int)mw->matrix.fixed_columns)
	    {
		xbaeClearCell(mw, row, j);
		xbaeDrawCell(mw, row, j);
	    }
	}
    }
}

/*
 * Matrix select_column method
 */
void
xbaeSelectColumn(mw, column)
XbaeMatrixWidget mw;
int column;
{
    int i, tr, br;

    if (column >= mw->matrix.columns || column < 0)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"selectColumn", "badIndex", "XbaeMatrix",
			"XbaeMatrix: Column out of bounds for SelectColumn.",
			NULL, 0);
	return;
    }

    /*
     * Scroll the column onto the screen
     */
    if (mw->matrix.scroll_select)
	xbaeMakeColumnVisible(mw, column);

    /*
     * No need to redraw unless the column is visible
     */
    if( !mw->matrix.scroll_select && !xbaeIsColumnVisible(mw, column) )
	return;

    /*
     * For each cell in the column, if the cell is not already selected,
     * select it and redraw it
     */
    xbaeGetVisibleRows(mw, &tr, &br);
    for (i = 0; i < mw->matrix.rows; i++)
    {
	if (!mw->matrix.selected_cells[i][column])
	{
	    mw->matrix.selected_cells[i][column] = True;
	    if ((i >= tr && i <= br) || i < (int)mw->matrix.fixed_rows)
	    {
		xbaeClearCell(mw, i, column);
		xbaeDrawCell(mw, i, column);
	    }
	}
    }
}

/*
 * Matrix deselect_all method
 */
void
xbaeDeselectAll(mw)
XbaeMatrixWidget mw;
{
    int i, j;
    int tr, br, lc, rc;

    xbaeGetVisibleCells(mw, &tr, &br, &lc, &rc);
    for (i = 0; i < mw->matrix.rows; i++)
	for (j = 0; j < mw->matrix.columns; j++)
	{
	    if (mw->matrix.selected_cells[i][j])
	    {
		mw->matrix.selected_cells[i][j] = False;
		if ((i >= tr && i <= br && j >= lc && j <= rc) ||
		    (i < (int)mw->matrix.fixed_rows && j >= lc && j <= rc) ||
		    (j < (int)mw->matrix.fixed_columns && i >= tr && i <= br))
		{
		    xbaeClearCell(mw, i, j);
		    xbaeDrawCell(mw, i, j);
		}
	    }
	}
}

/*
 * Matrix deselect_cell method
 */
void
xbaeDeselectCell(mw, row, column)
XbaeMatrixWidget mw;
int row;
int column;
{
    if (row >= mw->matrix.rows || row < 0 ||
	column > mw->matrix.columns - 1 || column < 0)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"deselectCell", "badIndex", "XbaeMatrix",
			"XbaeMatrix: Row or column parameter out of bounds for DeselectCell.",
			NULL, 0);
	return;
    }

    if (mw->matrix.selected_cells[row][column])
    {
	mw->matrix.selected_cells[row][column] = False;
	if (xbaeIsCellVisible(mw, row, column))
	{
	    xbaeClearCell(mw, row, column);
	    xbaeDrawCell(mw, row, column);
	}
    }
}

/*
 * Matrix deselect_row method
 */
void
xbaeDeselectRow(mw, row)
XbaeMatrixWidget mw;
int row;
{
    int j, lc, rc;

    if (row >= mw->matrix.rows || row < 0)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"deselectRow", "badIndex", "XbaeMatrix",
			"XbaeMatrix: Row parameter out of bounds for DeselectRow.",
			NULL, 0);
	return;
    }

    /*
     * For each cell in the row, if the cell is selected,
     * deselect it and redraw it
     */
    xbaeGetVisibleColumns(mw, &lc, &rc);
    for (j = 0; j < mw->matrix.columns; j++)
    {
	if (mw->matrix.selected_cells[row][j])
	{
	    mw->matrix.selected_cells[row][j] = False;
	    if ((j >= lc && j <= rc) || j < (int)mw->matrix.fixed_columns)
	    {
		xbaeClearCell(mw, row, j);
		xbaeDrawCell(mw, row, j);
	    }
	}
    }
}

/*
 * Matrix deselect_column method
 */
void
xbaeDeselectColumn(mw, column)
XbaeMatrixWidget mw;
int column;
{
    int i, tr, br;

    if (column >= mw->matrix.columns || column < 0)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"deselectColumn", "badIndex", "XbaeMatrix",
			"XbaeMatrix: Column parameter out of bounds for DeselectColumn.",
			NULL, 0);
	return;
    }

    /*
     * For each cell in the column, if the cell is selected,
     * deselect it and redraw it
     */
    xbaeGetVisibleRows(mw, &tr, &br);
    for (i = 0; i < mw->matrix.rows; i++)
    {
	if (mw->matrix.selected_cells[i][column])
	{
	    mw->matrix.selected_cells[i][column] = False;
	    if ((i >= tr && i <= br) || i < (int)mw->matrix.fixed_rows)
	    {
		xbaeClearCell(mw, i, column);
		xbaeDrawCell(mw, i, column);
	    }
	}
    }
}

/*
 * Matrix get_cell method
 */
String
xbaeGetCell(mw, row, column)
XbaeMatrixWidget mw;
int row, column;
{
    if (row >= mw->matrix.rows || row < 0 ||
	column > mw->matrix.columns - 1 || column < 0)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"getCell", "badIndex", "XbaeMatrix",
			"XbaeMatrix: Row or column parameter out of bounds for GetCell.",
			NULL, 0);
	return (NULL);
    }

    return mw->matrix.cells[row][column];
}

/*
 * Matrix commit_edit method
 */
Boolean
#if NeedFunctionPrototypes
xbaeCommitEdit(XbaeMatrixWidget mw, Boolean unmap)
#else
xbaeCommitEdit(mw, unmap)
XbaeMatrixWidget mw;
Boolean unmap;
#endif
{
    Boolean commit;

    if (!XtIsManaged(TextChild(mw)))
	return True;

    /*
     * Attempt to commit the edit
     */
    commit = DoCommitEdit(mw);

    /*
     * If the commit succeeded and we are supposed to unmap the textField,
     * then hide the textField and traverse out
     */
    if (commit && unmap)
    {
	XtUnmanageChild(TextChild(mw));
	XmProcessTraversal(TextChild(mw), XmTRAVERSE_RIGHT);
    }

    return commit;
}

/*
 * Matrix cancel_edit method
 */
void
#if NeedFunctionPrototypes
xbaeCancelEdit(XbaeMatrixWidget mw, Boolean unmap)
#else
xbaeCancelEdit(mw, unmap)
XbaeMatrixWidget mw;
Boolean unmap;
#endif
{
    if (!XtIsManaged(TextChild(mw)))
	return;

    /*
     * If unmap is set, hide the textField and traverse out.
     */
    if (unmap)
    {
	XtUnmanageChild(TextChild(mw));
	XmProcessTraversal(TextChild(mw), XmTRAVERSE_RIGHT);
    }

    /*
     * Don't unmap, just restore original contents
     */
    else
    {
	XtVaSetValues(TextChild(mw),
		      XmNvalue, mw->matrix.cells[mw->matrix.current_row]
		      [mw->matrix.current_column],
		      NULL);
    }
}

/*
 * Matrix add_rows method
 */
void
xbaeAddRows(mw, position, rows, labels, colors, backgrounds, num_rows)
XbaeMatrixWidget mw;
int position;
String *rows;
String *labels;
Pixel *colors;
Pixel *backgrounds;
int num_rows;
{
    /*
     * Do some error checking.
     */
    if (num_rows <= 0)
	return;
    if (position < 0 || position > mw->matrix.rows)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"addRows", "badPosition", "XbaeMatrix",
			"XbaeMatrix: Position out of bounds in AddRows.",
			NULL, 0);
	return;
    }
    
    /*
     * Add the new rows into the internal cells/labels data structure.
     */
    AddRowsToTable(mw, position, rows, labels, colors, backgrounds, num_rows);

    /*
     * Reconfig the VSB maximum.
     */
    XtVaSetValues(VertScrollChild(mw),
		  XmNmaximum, (mw->matrix.rows - (int) mw->matrix.fixed_rows),
		  NULL);

    /*
     * Relayout.
     */
    xbaeResize(mw);

    /*
     * Call our cancel_edit method since the rows shifted underneath us
     */
    (*((XbaeMatrixWidgetClass) XtClass(mw))->matrix_class.cancel_edit)
	(mw, True);

    if (XtIsRealized((Widget)mw))
    {
	/*
	 * Generate expose events on Matrix and Clip to force the
	 * new rows to be drawn.
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   0, 0,
		   0 /*Full Width*/, 0 /*Full Height*/,
		   True);
	XbaeClipRedraw(ClipChild(mw));
    }
}

/*
 * Matrix delete_rows method
 */
void
xbaeDeleteRows(mw, position, num_rows)
XbaeMatrixWidget mw;
int position;
int num_rows;
{
    /*
     * Do some error checking.
     */
    if (num_rows <= 0)
	return;
    if (position < 0 || position + num_rows > mw->matrix.rows)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"deleteRows", "badPosition", "XbaeMatrix",
			"XbaeMatrix: Position out of bounds in DeleteRows.",
			NULL, 0);
	return;
    }
    if (num_rows >= mw->matrix.rows - (int)mw->matrix.fixed_rows)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"deleteRows", "tooMany", "XbaeMatrix",
			"XbaeMatrix: Attempting to delete too many rows in DeleteRows.",
			NULL, 0);
	return;
    }

    /*
     * Delete the new rows from the internal cells/labels data structure.
     */
    DeleteRowsFromTable(mw, position, num_rows);

    /*
     * Reconfig the VSB maximum. Reset the sliderSize to avoid warnings.
     */
    XtVaSetValues(VertScrollChild(mw),
		  XmNmaximum, (mw->matrix.rows -
			       (int) mw->matrix.fixed_rows),
		  XmNsliderSize, 1,
		  NULL);

    /*
     * Relayout.
     */
    xbaeResize(mw);

    /*
     * Call our cancel_edit method since the rows shifted underneath us
     */
    (*((XbaeMatrixWidgetClass) XtClass(mw))->matrix_class.cancel_edit)
	(mw, True);

    if (XtIsRealized((Widget)mw))
    {
	/*
	 * Generate expose events on Matrix and Clip to force the
	 * rows to be redrawn.
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   0, 0,
		   0 /*Full Width*/, 0 /*Full Height*/,
		   True);
	XbaeClipRedraw(ClipChild(mw));
    }
}

/*
 * Matrix add_columns method.
 */
void
xbaeAddColumns(mw, position, columns, labels, widths, max_lengths,
	   alignments, label_alignments, colors, backgrounds, num_columns)
XbaeMatrixWidget mw;
int position;
String *columns;
String *labels;
short *widths;
int *max_lengths;
unsigned char *alignments;
unsigned char *label_alignments;
Pixel *colors;
Pixel *backgrounds;
int num_columns;
{
    /*
     * Do some error checking.
     */
    if (num_columns <= 0)
	return;
    if (position < 0 || position > mw->matrix.columns)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"addColumns", "badPosition", "XbaeMatrix",
			"XbaeMatrix: Position out of bounds in AddColumns.",
			NULL, 0);
	return;
    }
    if (!widths)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"addColumns", "noWidths", "XbaeMatrix",
			"XbaeMatrix: Must specify column widths in AddColumns.",
			NULL, 0);
	return;
    }

    /*
   * Add the new rows into the internal cells/labels data structure.
   */
    AddColumnsToTable(mw, position, columns, labels, widths, max_lengths,
		      alignments, label_alignments, colors, backgrounds,
		      num_columns);

    /*
   * Reconfig the HSB maximum.
   */
    XtVaSetValues(HorizScrollChild(mw),
		  XmNmaximum, CELL_TOTAL_WIDTH(mw),
		  NULL);

    /*
   * Relayout.
   */
    xbaeResize(mw);

    /*
   * Call our cancel_edit method since the columns shifted underneath us
   */
    (*((XbaeMatrixWidgetClass) XtClass(mw))->matrix_class.cancel_edit)
	(mw, True);

    if (XtIsRealized((Widget)mw))
    {
	/*
	 * Generate expose events on Matrix and Clip to force the
	 * new columns to be drawn.
     */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   0, 0,
		   0 /*Full Width*/, 0 /*Full Height*/,
		   True);
	XbaeClipRedraw(ClipChild(mw));
    }
}

/*
 * Matrix delete_columns method
 */
void
xbaeDeleteColumns(mw, position, num_columns)
XbaeMatrixWidget mw;
int position;
int num_columns;
{
    /*
     * Do some error checking.
     */
    if (num_columns <= 0)
	return;
    if (position < 0 || position + num_columns > mw->matrix.columns)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"deleteColumns", "badPosition", "XbaeMatrix",
			"XbaeMatrix: Position out of bounds in DeleteColumns.",
			NULL, 0);
	return;
    }
    if (num_columns >= mw->matrix.columns - (int)mw->matrix.fixed_columns)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"deleteColumns", "tooMany", "XbaeMatrix",
			"XbaeMatrix: Attempting to delete too many columns in DeleteColumns.",
			NULL, 0);
	return;
    }

    /*
     * Delete the new columns from the internal cells/labels data structure.
     */
    DeleteColumnsFromTable(mw, position, num_columns);

    /*
     * Reconfig the HSB maximum. Reset the sliderSize to avoid warnings.
     */
    XtVaSetValues(HorizScrollChild(mw),
		  XmNmaximum, CELL_TOTAL_WIDTH(mw),
		  XmNsliderSize, 1,
		  NULL);

    /*
     * Relayout.
     */
    xbaeResize(mw);

    /*
     * Call our cancel_edit method since the columns shifted underneath us
     */
    (*((XbaeMatrixWidgetClass) XtClass(mw))->matrix_class.cancel_edit)
	(mw, True);

    if (XtIsRealized((Widget)mw))
    {
	/*
	 * Generate expose events on Matrix and Clip to force the
	 * columns to be redrawn.
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   0, 0,
		   0 /*Full Width*/, 0 /*Full Height*/,
		   True);
	XbaeClipRedraw(ClipChild(mw));
    }
}

/*
 * Matrix set_row_colors method
 */
void
#if NeedFunctionPrototypes
xbaeSetRowColors(XbaeMatrixWidget mw, int position, Pixel *colors,
		 int num_colors, Boolean bg)
#else
xbaeSetRowColors(mw, position, colors, num_colors, bg)
XbaeMatrixWidget mw;
int position;
Pixel *colors;
int num_colors;
Boolean bg;
#endif
{
    XBAERectangle rect;
    int i, j;
    Pixel **set;
    Pixel pixel;
    
    /*
     * Do some error checking.
     */
    if (num_colors <= 0)
	return;
    if (position < 0 || position + num_colors > mw->matrix.rows)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"setRowColors", "badPosition", "XbaeMatrix",
			"XbaeMatrix: Position out of bounds or too many colors in SetRowColors.",
			NULL, 0);
	return;
    }

    /*
     * If we don't have any colors yet, malloc them, and initialize
     * unused entries to the appropriate color
     */
    if( ( !bg && !mw->matrix.colors ) ||
	( bg && !mw->matrix.cell_background ) )
    {
	if( !bg )
	{
	    xbaeCreateColors(mw);
	    set = &mw->matrix.colors[ 0 ];
	    pixel = mw->manager.foreground;
	}
	else
	{
	    xbaeCreateBackgrounds(mw);
	    set = &mw->matrix.cell_background[ 0 ];
	    pixel = mw->core.background_pixel;
	}
	for (i = 0; i < position; i++)
	    for (j = 0; j < mw->matrix.columns; j++)
		set[i][j] = pixel;
	for (i = position + num_colors; i < mw->matrix.rows; i++)
	    for (j = 0; j < mw->matrix.columns; j++)
		set[i][j] = pixel;
    }
    
    if( !bg )
	set = &mw->matrix.colors[ 0 ];
    else
	set = &mw->matrix.cell_background[ 0 ];

    /*
     * Set each row to the appropriate color
     */
    for (i = 0; i < num_colors; i++)
	for (j = 0; j < mw->matrix.columns; j++)
	    set[i + position][j] = colors[i];
	
    if (XtIsRealized((Widget)mw))
    {
	/*
	 * Redraw all the visible non-fixed cells. We don't need to clear first
	 * since only the color changed.
	 */
	SETRECT(rect,
		0, 0,
		ClipChild(mw)->core.width - 1, ClipChild(mw)->core.height - 1);
	xbaeRedrawCells(mw, &rect);

	/*
	 * Redraw all the visible fixed cells (but not the labels).
	 * We don't need to clear first since only the color changed.
	 */
	SETRECT(rect,
		ROW_LABEL_WIDTH(mw), COLUMN_LABEL_HEIGHT(mw),
		mw->core.width - 1, mw->core.height - 1);
	xbaeRedrawLabelsAndFixed(mw, &rect);
	
	xbaeDrawGridShadows(mw, GRID_REDRAW_EXPOSE);
    }
    if (position <= mw->matrix.current_row && 
	position + num_colors > mw->matrix.current_row &&
	XtIsRealized(TextChild(mw)))
	if( bg )
	    XtVaSetValues(TextChild(mw), XmNbackground, 
			  mw->matrix.cell_background[mw->matrix.current_row]
			  [mw->matrix.current_column],
			  NULL);
	else
	    XtVaSetValues(TextChild(mw), XmNforeground, 
			  mw->matrix.colors[mw->matrix.current_row]
			  [mw->matrix.current_column],
			  NULL);	    
}

/*
 * Matrix set_column_colors method
 */
void
#if NeedFunctionPrototypes
xbaeSetColumnColors(XbaeMatrixWidget mw, int position, Pixel *colors,
		int num_colors, Boolean bg)
#else
xbaeSetColumnColors(mw, position, colors, num_colors, bg)
XbaeMatrixWidget mw;
int position;
Pixel *colors;
int num_colors;
Boolean bg;
#endif
{
    XBAERectangle rect;
    int i, j;
    Pixel **set;
    Pixel pixel;
    
    /*
     * Do some error checking.
     */
    if (num_colors <= 0)
	return;
    if (position < 0 || position + num_colors > mw->matrix.columns)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"setColumnColors", "badPosition", "XbaeMatrix",
			"XbaeMatrix: Position out of bounds or too many colors in SetColumnColors.",
			NULL, 0);
	return;
    }

    /*
     * If we don't have any colors yet, malloc them, and initialize
     * unused entries to foreground
     */
    if( ( !bg && !mw->matrix.colors ) ||
	( bg && !mw->matrix.cell_background ) )
    {
	if( !bg )
	{
	    xbaeCreateColors(mw);
	    set = &mw->matrix.colors[ 0 ];
	    pixel = mw->manager.foreground;
	}
	else
	{
	    xbaeCreateBackgrounds(mw);
	    set = &mw->matrix.cell_background[ 0 ];
	    pixel = mw->core.background_pixel;
	}
	for (i = 0; i < mw->matrix.rows; i++)
	    for (j = 0; j < position; j++)
		set[i][j] = pixel;
	for (i = 0; i < mw->matrix.rows; i++)
	    for (j = position + num_colors; j < mw->matrix.columns; j++)
		set[i][j] = pixel;
    }

    if( !bg )
	set = &mw->matrix.colors[ 0 ];
    else
	set = &mw->matrix.cell_background[ 0 ];

    /*
     * Set each column to the appropriate color
     */
    for (i = 0; i < mw->matrix.rows; i++)
	for (j = 0; j < num_colors; j++)
	    set[i][j + position] = colors[j];

    if (XtIsRealized((Widget)mw))
    {
	/*
	 * Redraw all the visible non-fixed cells. We don't need to clear first
	 * since only the color changed.
	 */
	SETRECT(rect,
		0, 0,
		ClipChild(mw)->core.width - 1, ClipChild(mw)->core.height - 1);
	xbaeRedrawCells(mw, &rect);

	/*
	 * Redraw all the visible fixed cells (but not the labels).
	 * We don't need to clear first since only the color changed.
	 */
	SETRECT(rect,
		ROW_LABEL_WIDTH(mw), COLUMN_LABEL_HEIGHT(mw),
		mw->core.width - 1, mw->core.height - 1);
	xbaeRedrawLabelsAndFixed(mw, &rect);
	
	xbaeDrawGridShadows(mw, GRID_REDRAW_EXPOSE);
    }
    if (position <= mw->matrix.current_column && 
	position + num_colors > mw->matrix.current_column &&
	XtIsRealized(TextChild(mw)))
	if( bg )
	    XtVaSetValues(TextChild(mw), XmNbackground, 
			  mw->matrix.cell_background[mw->matrix.current_row]
			  [mw->matrix.current_column],
			  NULL);
	else
	    XtVaSetValues(TextChild(mw), XmNforeground, 
			  mw->matrix.colors[mw->matrix.current_row]
			  [mw->matrix.current_column],
			  NULL);	
}

/*
 * Matrix set_cell_color method
 */
void
#if NeedFunctionPrototypes
xbaeSetCellColor(XbaeMatrixWidget mw, int row, int column, Pixel color, Boolean bg)
#else
xbaeSetCellColor(mw, row, column, color, bg)
XbaeMatrixWidget mw;
int row;
int column;
Pixel color;
Boolean bg;
#endif
{
    int i, j;
    Pixel **set;
    Pixel pixel;
    
    /*
     * Do some error checking.
     */
    if (row >= mw->matrix.rows || row < 0 ||
	column >= mw->matrix.columns || column < 0)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			"xbaeSetCellColor", "badIndex", "XbaeMatrix",
			"XbaeMatrix: Row or column parameter out of bounds for xbaeSetCellColor.",
			NULL, 0);
	return;
    }

    /*
     * If we don't have any colors yet, malloc them and initialize them
     */
    if( ( !bg && !mw->matrix.colors ) ||
	( bg && !mw->matrix.cell_background ) )
    {
	if( !bg )
	{
	    xbaeCreateColors(mw);
	    set = &mw->matrix.colors[ 0 ];
	    pixel = mw->manager.foreground;
	}
	else
	{
	    xbaeCreateBackgrounds(mw);
	    set = &mw->matrix.cell_background[ 0 ];
	    pixel = mw->core.background_pixel;
	}
	for (i = 0; i < mw->matrix.rows; i++)
	    for (j = 0; j < mw->matrix.columns; j++)
		set[i][j] = pixel;
    }

    if( !bg )
	set = &mw->matrix.colors[ 0 ];
    else
	set = &mw->matrix.cell_background[ 0 ];

    /*
     * Set the cell's color
     */
    set[row][column] = color;

    if (XtIsRealized((Widget)mw))
    {
	/*
	 * Redraw the cell if it is visible
	 */
	if (xbaeIsCellVisible(mw, row, column))
	    xbaeDrawCell(mw, row, column);
    }
    if (row == mw->matrix.current_row && column == mw->matrix.current_column &&
	XtIsRealized(TextChild(mw)))
	if( bg )
	    XtVaSetValues(TextChild(mw), XmNbackground, 
			  mw->matrix.cell_background[mw->matrix.current_row]
			  [mw->matrix.current_column],
			  NULL);
	else
	    XtVaSetValues(TextChild(mw), XmNforeground, 
			  mw->matrix.colors[mw->matrix.current_row]
			  [mw->matrix.current_column],
			  NULL);
}

