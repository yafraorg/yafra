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
#include <Xbae/Macros.h>
#include <Xbae/Utils.h>
#include <Xbae/Actions.h>
#include <Xm/ScrollBar.h>
/*
 * Utils.c created by Andrew Lister (7 August, 1995)
 */

/*
 * Return the top and bottom-most visible non-fixed row
 */
void
xbaeGetVisibleRows(mw, top_row, bottom_row)
XbaeMatrixWidget mw;
int *top_row, *bottom_row;
{
    *top_row = VERT_ORIGIN(mw) + mw->matrix.fixed_rows;
    *bottom_row = *top_row + VISIBLE_HEIGHT(mw) / ROW_HEIGHT(mw);
}

/*
 * Return the left and right-most visible non-fixed column
 */
void
xbaeGetVisibleColumns(mw, left_column, right_column)
XbaeMatrixWidget mw;
int *left_column, *right_column;
{
    *left_column = xbaeXtoCol(mw, FIXED_COLUMN_WIDTH(mw) + HORIZ_ORIGIN(mw));
    *right_column = xbaeXtoCol(mw, FIXED_COLUMN_WIDTH(mw) + HORIZ_ORIGIN(mw) +
			   VISIBLE_WIDTH(mw) - 1);
}

/*
 * Return the top and bottom row and left and right column of
 * the visible non-fixed cells
 */
void
xbaeGetVisibleCells(mw, top_row, bottom_row, left_column, right_column)
XbaeMatrixWidget mw;
int *top_row, *bottom_row, *left_column, *right_column;
{
    xbaeGetVisibleRows(mw, top_row, bottom_row);
    xbaeGetVisibleColumns(mw, left_column, right_column);
}

/*
 * Try to make the column specified by the leftColumn resource
 * be the left column. The column is relative to fixed_columns - so 0 would
 * be the first non-fixed column.
 * If we can't make leftColumn the left column, make it as close as possible.
 */
void
xbaeAdjustLeftColumn(mw)
XbaeMatrixWidget mw;
{
    int columns_visible = XbaeMatrixVisibleColumns((Widget)mw);
    int y;
  
    /*
     * If we have less than one full column visible,
     * then count it as a full row
     */
    if (columns_visible == 0)
	columns_visible = 1;
    /*
     * columns_visible might be inaccurate since Clip may not have been resized
     */
    else if (columns_visible > mw->matrix.columns)
	columns_visible = mw->matrix.columns;
    if (mw->matrix.left_column > (mw->matrix.columns -
				  (columns_visible + mw->matrix.fixed_columns +
				   mw->matrix.trailing_fixed_columns)))
	mw->matrix.left_column = mw->matrix.columns -
	    (columns_visible + mw->matrix.fixed_columns + mw->matrix.trailing_fixed_columns);
    else if (mw->matrix.left_column < 0)
	mw->matrix.left_column = 0;
  
    HORIZ_ORIGIN(mw) = 0;
  
    xbaeRowColToXY(mw, 0, mw->matrix.left_column,
		   &mw->matrix.horiz_origin, &y );
}

/*
 * Try to make the row specified by the topRow resource (VERT_ORIGIN)
 * be the top row. The row is relative to fixed_rows - so 0 would
 * be the first non-fixed row.
 * If we can't make topRow the top row, make it as close as possible.
 */
void
xbaeAdjustTopRow(mw)
XbaeMatrixWidget mw;
{
    int rows_visible = VISIBLE_HEIGHT(mw) / ROW_HEIGHT(mw);

    /*
     * If we have less than one full row visible, then count it as a full row
     */
    if (rows_visible == 0)
	rows_visible = 1;
    /*
     * rows_visible might be inaccurate since Clip may not have been resized
     */
    else if (rows_visible > mw->matrix.rows)
	rows_visible = mw->matrix.rows;

    if (VERT_ORIGIN(mw) > (mw->matrix.rows - (rows_visible +
					      (int)mw->matrix.fixed_rows)))
	VERT_ORIGIN(mw) = mw->matrix.rows - (rows_visible +
					     mw->matrix.fixed_rows);
    else if (VERT_ORIGIN(mw) < 0)
	VERT_ORIGIN(mw) = 0;
}

/*
 * Utility function to clear a cell so we can draw something new in it.
 * Does not generate expose events on the cell.
 * Does not check if the cell is actually visible before clearing it.
 */
void
xbaeClearCell(mw, row, column)
XbaeMatrixWidget mw;
int row, column;
{
    int x, y;
    Window win = CELL_WINDOW(mw, row, column);

    if (!win)
	return;

    xbaeRowColToXY(mw, row, column, &x, &y);

    XClearArea(XtDisplay(mw), win,
	       x, y,
	       COLUMN_WIDTH(mw, column),
	       ROW_HEIGHT(mw),
	       False);
}

/*
 * Return True if a row is visible on the screen (not scrolled totally off)
 */
Boolean
xbaeIsRowVisible(mw, row)
XbaeMatrixWidget mw;
int row;
{
    /*
     * If we are not in a fixed row or trailing fixed row,
     * see if we are on the screen vertically
     * (fixed rows are always on the screen)
     */
    if ((row >= (int)mw->matrix.fixed_rows) ||
	(row < TRAILING_VERT_ORIGIN(mw)))
    {
	row -= mw->matrix.fixed_rows;
	if (row >= VERT_ORIGIN(mw) &&
	    row <
	    (int)(ClipChild(mw)->core.height) / ROW_HEIGHT(mw) + VERT_ORIGIN(mw))
	    return True;
    }
    else
	return True;

    return False;
}

/*
 * Return True if a column is visible on the screen (not scrolled totally off)
 */
Boolean
xbaeIsColumnVisible(mw, column)
XbaeMatrixWidget mw;
int column;
{
    /*
     * If we are not in a fixed column, see if we are on the screen
     * horizontally (fixed columns are always on the screen)
     */
    if ((column >= (int)mw->matrix.fixed_columns) ||
	(column < TRAILING_HORIZ_ORIGIN(mw)))
    {
	int x;

	/*
	 * Calculate the x endpoints of this column
	 */
	x = COLUMN_POSITION(mw, column) -
	    COLUMN_POSITION(mw, mw->matrix.fixed_columns);

	/*
	 * Check if we are visible horizontally
	 */
	if (x + COLUMN_WIDTH(mw, column) > HORIZ_ORIGIN(mw) &&
	    x < (int)(ClipChild(mw)->core.width) + HORIZ_ORIGIN(mw))
	    return True;
    }
    else
	return True;

    return False;
}

/*
 * Return True if a cell is visible on the screen (not scrolled totally off)
 */
Boolean
xbaeIsCellVisible(mw, row, column)
XbaeMatrixWidget mw;
int row, column;
{
    return xbaeIsRowVisible(mw, row) && xbaeIsColumnVisible(mw, column);
}

/*
 * Scroll a row so it is visible on the screen.
 */
void
xbaeMakeRowVisible(mw, row)
XbaeMatrixWidget mw;
int row;
{
    int rows_visible;
    int value, slider_size, increment, page_increment, vert_value;

    /*
     * If we are in a fixed row, we are already visible.
     */
    if ((row < (int)mw->matrix.fixed_rows) ||
	(row >= TRAILING_VERT_ORIGIN(mw)))
	return;

    /*
     * Take into account fixed_rows.
     * Calculate the number of rows visible. If less than one full
     * row is visible, use one full row.
     */
    row -= mw->matrix.fixed_rows;
    rows_visible = VISIBLE_HEIGHT(mw) / ROW_HEIGHT(mw);
    if (rows_visible == 0)
	rows_visible = 1;

    /*
     * Figure out the new value of the VSB to scroll this cell
     * onto the screen (the VSB uses row coordinates instead of pixels)
     */
    if (row < VERT_ORIGIN(mw))
	vert_value = row;
    else if (row >= rows_visible + VERT_ORIGIN(mw))
	vert_value = row - rows_visible + 1;
    else
	vert_value = VERT_ORIGIN(mw);

    /*
     * Give the VSB the new value and pass a flag to make it call
     * our scroll callbacks
     */
    if (vert_value != VERT_ORIGIN(mw))
    {
	XmScrollBarGetValues(VertScrollChild(mw), &value,
			     &slider_size, &increment, &page_increment);
	XmScrollBarSetValues(VertScrollChild(mw), vert_value,
			     slider_size, increment, page_increment, True);
    }
}

/*
 * Scroll a column so it is visible on the screen.
 */
void
xbaeMakeColumnVisible(mw, column)
XbaeMatrixWidget mw;
int column;
{
    int value, slider_size, increment, page_increment, x, horiz_value;

    /*
     * If we are in a fixed column, we are already visible.
     */
    if ((column < (int)mw->matrix.fixed_columns) ||
	(column >= TRAILING_HORIZ_ORIGIN(mw)))
	return;

    /*
     * Calculate the x position of this column
     */
    x = COLUMN_POSITION(mw, column) -
	COLUMN_POSITION(mw, mw->matrix.fixed_columns);

    /*
     * Figure out the new value of the HSB to scroll this cell
     * onto the screen. If the whole cell won't fit, scroll so its
     * left edge is visible.
     */
    if (x < HORIZ_ORIGIN(mw))
	horiz_value = x;
    else if (x + COLUMN_WIDTH(mw, column) >
	     VISIBLE_WIDTH(mw) + HORIZ_ORIGIN(mw))
    {
	int off = (x + COLUMN_WIDTH(mw, column)) - (VISIBLE_WIDTH(mw) +
						    HORIZ_ORIGIN(mw));

	if (x - off < HORIZ_ORIGIN(mw))
	    horiz_value = x;
	else
	    horiz_value = HORIZ_ORIGIN(mw) + off;
    }
    else
	horiz_value = HORIZ_ORIGIN(mw);

    /*
     * Give the HSB the new value and pass a flag to make it
     * call our scroll callbacks
     */
    if (horiz_value != HORIZ_ORIGIN(mw))
    {
	XmScrollBarGetValues(HorizScrollChild(mw), &value,
			     &slider_size, &increment, &page_increment);
	XmScrollBarSetValues(HorizScrollChild(mw), horiz_value,
			     slider_size, increment, page_increment, True);
    }
}

/*
 * Scrolls a fixed or non-fixed cell so it is visible on the screen.
 */
void
xbaeMakeCellVisible(mw, row, column)
XbaeMatrixWidget mw;
int row, column;
{
    if (mw->matrix.scroll_select || !xbaeIsRowVisible(mw, row ))
	xbaeMakeRowVisible(mw, row);
    if (mw->matrix.scroll_select || !xbaeIsColumnVisible(mw, column ))
	xbaeMakeColumnVisible(mw, column);
}

void
xbaeCopyBackground( widget, offset, value )
Widget widget;
int offset;
XrmValue *value;
{
    value->addr = (XtPointer)&(widget->core.background_pixel);
}


void
xbaeCopyForeground( widget, offset, value )
Widget widget;
int offset;
XrmValue *value;
{
    value->addr = (XtPointer)&(((XmManagerWidget)widget)->manager.foreground);
}

void
xbaeCopyDoubleClick( widget, offset, value )
Widget widget;
int offset;
XrmValue *value;
{
    static int interval;
  
    interval = XtGetMultiClickTime(XtDisplay(widget));
    value->addr = (XtPointer)&interval;
}

void
xbaeCopyCells(mw)
XbaeMatrixWidget mw;
{
    String **copy;
    int i, j;

    /*
     * Malloc an array of row pointers
     */
    copy = (String **) XtMalloc(mw->matrix.rows * sizeof(String *));

    /*
     * Malloc an array of Strings for each row pointer
     */
    for (i = 0; i < mw->matrix.rows; i++)
	copy[i] = (String *) XtMalloc(mw->matrix.columns * sizeof(String));

    /*
     * Create a bunch of "" cells if cells was NULL
     */
    if (!mw->matrix.cells)
    {
	for (i = 0; i < mw->matrix.rows; i++)
	    for (j = 0; j < mw->matrix.columns; j++)
		copy[i][j] = XtNewString("");
    }

    /*
     * Otherwise copy the table passed in
     */
    else
    {
	for (i = 0; i < mw->matrix.rows; i++)
	    for (j = 0; j < mw->matrix.columns; j++)
	    {
		if (!mw->matrix.cells[i][j])
		{
		    XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
				    "copyCells", "badValue", "XbaeMatrix",
				    "XbaeMatrix: NULL entry found in cell table",
				    NULL, 0);
		    copy[i][j] = XtNewString("");
		}
		else
		    copy[i][j] = XtNewString(mw->matrix.cells[i][j]);
	    }
    }

    mw->matrix.cells = copy;
}

void
xbaeCopyRowLabels(mw)
XbaeMatrixWidget mw;
{
    String *copy;
    int i;

    copy = (String *) XtMalloc(mw->matrix.rows * sizeof(String));

    for (i = 0; i < mw->matrix.rows; i++)
	if (!mw->matrix.row_labels[i])
	{
	    XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			    "copyRowLabels", "badValue", "XbaeMatrix",
			    "XbaeMatrix: NULL entry found in rowLabels array",
			    NULL, 0);
	    copy[i] = XtNewString("");
	}
	else
	    copy[i] = XtNewString(mw->matrix.row_labels[i]);

    mw->matrix.row_labels = copy;
}

void
xbaeCopyColumnLabels(mw)
XbaeMatrixWidget mw;
{
    String *copy;
    int i;

    copy = (String *) XtMalloc(mw->matrix.columns * sizeof(String));

    mw->matrix.column_label_lines = (ColumnLabelLines)
	XtMalloc(mw->matrix.columns * sizeof(ColumnLabelLinesRec));

    for (i = 0; i < mw->matrix.columns; i++)
	if (!mw->matrix.column_labels[i])
	{
	    XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			    "copyColumnLabels", "badValue", "XbaeMatrix",
			    "XbaeMatrix: NULL entry found in columnLabels array",
			    NULL, 0);
	    copy[i] = XtNewString("");
	    xbaeParseColumnLabel(copy[i], &mw->matrix.column_label_lines[i]);
	}
	else
	{
	    copy[i] = XtNewString(mw->matrix.column_labels[i]);
	    xbaeParseColumnLabel(mw->matrix.column_labels[i],
			     &mw->matrix.column_label_lines[i]);
	}

    /*
     * Determine max number of lines in column labels
     */
    mw->matrix.column_label_maxlines = mw->matrix.column_label_lines[0].lines;
    for (i = 1; i < mw->matrix.columns; i++)
	if (mw->matrix.column_label_lines[i].lines >
	    mw->matrix.column_label_maxlines)
	    mw->matrix.column_label_maxlines =
		mw->matrix.column_label_lines[i].lines;

    mw->matrix.column_labels = copy;
}

void
xbaeCopyColumnWidths(mw)
XbaeMatrixWidget mw;
{
    short *copy;
    int i;
    Boolean bad = False;

    copy = (short *) XtMalloc(mw->matrix.columns * sizeof(short));

    for (i = 0; i < mw->matrix.columns; i++)
    {
	if (!bad && mw->matrix.column_widths[i] == BAD_WIDTH)
	{
	    bad = True;
	    XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			    "copyColumnWidths", "tooShort", "XbaeMatrix",
			    "XbaeMatrix: Column widths array is too short",
			    NULL, 0);
	    copy[i] = 1;
	}
	else if (bad)
	    copy[i] = 1;
	else
	    copy[i] = mw->matrix.column_widths[i];
    }

    mw->matrix.column_widths = copy;
}

void
xbaeCopyColumnMaxLengths(mw)
XbaeMatrixWidget mw;
{
    int *copy;
    int i;
    Boolean bad = False;

    copy = (int *) XtMalloc(mw->matrix.columns * sizeof(int));

    for (i = 0; i < mw->matrix.columns; i++)
    {
	if (!bad && mw->matrix.column_max_lengths[i] == BAD_MAXLENGTH)
	{
	    bad = True;
	    XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			    "copyColumnMaxLengths", "tooShort", "XbaeMatrix",
			    "XbaeMatrix: Column max lengths array is too short",
			    NULL, 0);
	    copy[i] = 1;
	}
	else if (bad)
	    copy[i] = 1;
	else
	    copy[i] = mw->matrix.column_max_lengths[i];
    }

    mw->matrix.column_max_lengths = copy;
}

void
xbaeCopyColumnAlignments(mw)
XbaeMatrixWidget mw;
{
    unsigned char *copy;
    int i;
    Boolean bad = False;

    copy = (unsigned char *) XtMalloc(mw->matrix.columns *
				      sizeof(unsigned char));

    for (i = 0; i < mw->matrix.columns; i++)
    {
	if (!bad && mw->matrix.column_alignments[i] == BAD_ALIGNMENT)
	{
	    bad = True;
	    XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			    "copyColumnAlignments", "tooShort", "XbaeMatrix",
			    "XbaeMatrix: Column alignments array is too short",
			    NULL, 0);
	    copy[i] = XmALIGNMENT_BEGINNING;
	}
	else if (bad)
	    copy[i] = XmALIGNMENT_BEGINNING;
	else
	    copy[i] = mw->matrix.column_alignments[i];
    }

    mw->matrix.column_alignments = copy;
}

void
xbaeCopyColumnLabelAlignments(mw)
XbaeMatrixWidget mw;
{
    unsigned char *copy;
    int i;
    Boolean bad = False;

    copy = (unsigned char *) XtMalloc(mw->matrix.columns *
				      sizeof(unsigned char));

    for (i = 0; i < mw->matrix.columns; i++)
    {
	if (!bad &&
	    mw->matrix.column_label_alignments[i] == BAD_ALIGNMENT)
	{
	    bad = True;
	    XtAppWarningMsg(XtWidgetToApplicationContext((Widget) mw),
			    "copyColumnLabelAlignments", "tooShort",
			    "XbaeMatrix",
			    "XbaeMatrix: Column label alignments array is too short",
			    NULL, 0);
	    copy[i] = XmALIGNMENT_BEGINNING;
	}
	else if (bad)
	    copy[i] = XmALIGNMENT_BEGINNING;
	else
	    copy[i] = mw->matrix.column_label_alignments[i];
    }

    mw->matrix.column_label_alignments = copy;
}

void
xbaeCopyColors(mw)
XbaeMatrixWidget mw;
{
    Pixel **copy;
    int i, j;

    /*
     * Malloc an array of row pointers
     */
    copy = (Pixel **) XtMalloc(mw->matrix.rows * sizeof(Pixel *));

    /*
     * Malloc an array of Pixels for each row pointer
     */
    for (i = 0; i < mw->matrix.rows; i++)
	copy[i] = (Pixel *) XtMalloc(mw->matrix.columns * sizeof(Pixel));

    for (i = 0; i < mw->matrix.rows; i++)
	for (j = 0; j < mw->matrix.columns; j++)
	    copy[i][j] = mw->matrix.colors[i][j];

    mw->matrix.colors = copy;
}

void
xbaeCopyBackgrounds(mw)
XbaeMatrixWidget mw;
{
    Pixel **copy;
    int i, j;

    /*
     * Malloc an array of row pointers
     */
    copy = (Pixel **) XtMalloc(mw->matrix.rows * sizeof(Pixel *));

    /*
     * Malloc an array of Pixels for each row pointer
     */
    for (i = 0; i < mw->matrix.rows; i++)
	copy[i] = (Pixel *) XtMalloc(mw->matrix.columns * sizeof(Pixel));

    for (i = 0; i < mw->matrix.rows; i++)
	for (j = 0; j < mw->matrix.columns; j++)
	    copy[i][j] = mw->matrix.cell_background[i][j];

    mw->matrix.cell_background = copy;
}

/*
 * Copy the selectedCells resource. Create a 2D array of Booleans to
 * represent selected cells if it is NULL.
 */
void
xbaeCopySelectedCells(mw)
XbaeMatrixWidget mw;
{
    Boolean **copy;
    int i, j;

    /*
     * Malloc an array of row pointers
     */
    copy = (Boolean **) XtMalloc(mw->matrix.rows * sizeof(Boolean *));

    /*
     * Malloc an array of Booleans for each row pointer
     */
    for (i = 0; i < mw->matrix.rows; i++)
	copy[i] = (Boolean *) XtCalloc(mw->matrix.columns, sizeof(Boolean));

    /*
     * If selected_cells is not NULL, copy the table passed in
     */
    if (mw->matrix.selected_cells)
	for (i = 0; i < mw->matrix.rows; i++)
	    for (j = 0; j < mw->matrix.columns; j++)
		copy[i][j] = mw->matrix.selected_cells[i][j];

    mw->matrix.selected_cells = copy;
}

/*
 * Create a matrix of Pixels
 */
void
xbaeCreateColors(mw)
XbaeMatrixWidget mw;
{
    int i;

    /*
     * Malloc an array of row pointers
     */
    mw->matrix.colors = (Pixel **) XtMalloc(mw->matrix.rows * sizeof(Pixel *));

    /*
     * Malloc an array of Pixels for each row pointer
     */
    for (i = 0; i < mw->matrix.rows; i++)
	mw->matrix.colors[i] = (Pixel *) XtMalloc(mw->matrix.columns *
						  sizeof(Pixel));
}

/*
 * Create a matrix of Pixels
 */
void
xbaeCreateBackgrounds(mw)
XbaeMatrixWidget mw;
{
    int i;

    /*
     * Malloc an array of row pointers
     */
    mw->matrix.cell_background =
	(Pixel **) XtMalloc(mw->matrix.rows * sizeof(Pixel *));

    /*
     * Malloc an array of Pixels for each row pointer
     */
    for (i = 0; i < mw->matrix.rows; i++)
	mw->matrix.cell_background[i] = (Pixel *) XtMalloc(mw->matrix.columns *
							   sizeof(Pixel));
}


void
xbaeCreateGridLineGC(mw)
XbaeMatrixWidget mw;
{
    XGCValues values;
    XtGCMask mask = GCForeground | GCBackground;

    values.foreground = mw->matrix.grid_line_color;
    values.background = mw->manager.foreground;
    
    /*
     * GC for drawing grid lines
     */
    mw->matrix.grid_line_gc = XtGetGC((Widget) mw, mask, &values);
    
    /*
     * GC for drawing grid lines with clipping
     */
    mw->matrix.cell_grid_line_gc = XCreateGC(XtDisplay(mw),
					     GC_PARENT_WINDOW(mw),
					     mask, &values);
}

void
xbaeCreateDrawGC(mw)
XbaeMatrixWidget mw;
{
    XGCValues values;
    unsigned long mask = GCForeground | GCFont;

    /*
     * GC for drawing cells. We create it instead of using a cached one,
     * since the foreground may change frequently.
     */
    values.foreground = mw->manager.foreground;
    values.font = mw->matrix.font->fid;
    mw->matrix.draw_gc = XCreateGC(XtDisplay(mw),
				   GC_PARENT_WINDOW(mw),
				   mask, &values);
}

void
xbaeCreateDrawClipGC(mw)
XbaeMatrixWidget mw;
{
    XGCValues values;
    unsigned long mask = GCForeground | GCFont;

    /*
     * GC for drawing cells with clipping.
     */
    values.foreground = mw->manager.foreground;
    values.font = mw->matrix.font->fid;
    mw->matrix.draw_clip_gc = XCreateGC(XtDisplay(mw),
					GC_PARENT_WINDOW(mw),
					mask, &values);
}

void
xbaeCreateLabelGC(mw)
XbaeMatrixWidget mw;
{
    XGCValues values;
    unsigned long mask = GCForeground | GCFont;

    /*
     * GC for drawing labels
     */
    values.foreground = mw->manager.foreground;
    values.font = mw->matrix.label_font->fid;
    mw->matrix.label_gc = XCreateGC(XtDisplay(mw),
				    GC_PARENT_WINDOW(mw),
				    mask, &values);
}

void
xbaeCreateLabelClipGC(mw)
XbaeMatrixWidget mw;
{
    XGCValues values;
    unsigned long mask = GCForeground | GCFont;

    /*
     * GC for drawing labels with clipping.
     */
    values.foreground = mw->manager.foreground;
    values.font = mw->matrix.label_font->fid;
    mw->matrix.label_clip_gc = XCreateGC(XtDisplay(mw),
					 GC_PARENT_WINDOW(mw),
					 mask, &values);
}

void
xbaeCreateInverseClipGC(mw)
XbaeMatrixWidget mw;
{
    XGCValues values;

    /*
     * GC for drawing selected cells with clipping.
     */
    values.foreground = mw->core.background_pixel;
    values.font = mw->matrix.font->fid;

}

void
xbaeCreateTopShadowClipGC(mw)
XbaeMatrixWidget mw;
{
    XGCValues values;
    XtGCMask mask = GCForeground | GCBackground;

    /*
     * GC for drawing top shadow inside cells with clipping.
     */
    values.foreground = mw->manager.top_shadow_color;
    values.background = mw->manager.foreground;

    if (mw->manager.top_shadow_pixmap != XmUNSPECIFIED_PIXMAP)
    {
	mask |= GCFillStyle | GCTile;
	values.fill_style = FillTiled;
	values.tile = mw->manager.top_shadow_pixmap;
    }
    mw->matrix.cell_top_shadow_clip_gc =
	XCreateGC(XtDisplay(mw),
		  GC_PARENT_WINDOW(mw),
		  mask, &values);
}

void
xbaeCreateBottomShadowClipGC(mw)
XbaeMatrixWidget mw;
{
    XGCValues values;
    XtGCMask mask = GCForeground | GCBackground;

    /*
     * GC for drawing bottom shadow inside cells with clipping.
     */
    values.foreground = mw->manager.bottom_shadow_color;
    values.background = mw->manager.foreground;

    if (mw->manager.bottom_shadow_pixmap != XmUNSPECIFIED_PIXMAP)
    {
	mask |= GCFillStyle | GCTile;
	values.fill_style = FillTiled;
	values.tile = mw->manager.bottom_shadow_pixmap;
    }
    mw->matrix.cell_bottom_shadow_clip_gc =
	XCreateGC(XtDisplay(mw),
		  GC_PARENT_WINDOW(mw),
		  mask, &values);
}

/*
 * Set the clip_mask in our draw and shadow GCs.  This is necessary for
 * drawing non-fixed column labels and fixed rows.
 */
void
xbaeSetClipMask(mw, clip_reason)
XbaeMatrixWidget mw;
unsigned int clip_reason;
{
    XRectangle r;

    /*
     * XRectangle enclosing column labels and fixed rows
     */
    if ((CLIP_FIXED_COLUMNS & clip_reason) && mw->matrix.fixed_columns)
    {
	r.x = COLUMN_LABEL_OFFSET(mw);
	r.width = FIXED_COLUMN_WIDTH(mw);
    }
    else if ((CLIP_TRAILING_FIXED_COLUMNS & clip_reason) &&
	     mw->matrix.trailing_fixed_columns)
    {
	r.x = TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw);
	r.width = TRAILING_FIXED_COLUMN_WIDTH(mw);
    }
    else
    {
	r.x = FIXED_COLUMN_LABEL_OFFSET(mw);
	r.width = ClipChild(mw)->core.width;
    }


    if ((CLIP_TRAILING_FIXED_ROWS & clip_reason) &&
	mw->matrix.trailing_fixed_rows)
    {
	r.y = TRAILING_FIXED_ROW_LABEL_OFFSET(mw);
	r.height = TRAILING_FIXED_ROW_HEIGHT(mw);
    }
    else if (CLIP_VISIBLE_HEIGHT & clip_reason)
    {
	r.y = ROW_LABEL_OFFSET(mw);
	r.height = ClipChild(mw)->core.height +
	    FIXED_ROW_HEIGHT(mw) + TRAILING_FIXED_ROW_HEIGHT(mw);
    }
    else if (CLIP_BETWEEN_FIXED_ROWS & clip_reason)
    {
	r.y = FIXED_ROW_LABEL_OFFSET(mw);
	r.height = ClipChild(mw)->core.height;
    }
    else
    {
	r.y = 0;
	r.height = FIXED_ROW_LABEL_OFFSET(mw);
    }  

    /*
     * Reset the clip_mask in our clipping GCs
     */
    XSetClipRectangles(XtDisplay(mw), mw->matrix.draw_clip_gc,
		       0, 0, &r, 1, Unsorted);
/* xq    XSetClipRectangles(XtDisplay(mw), mw->matrix.inverse_clip_gc,
		       0, 0, &r, 1, Unsorted); */
    XSetClipRectangles(XtDisplay(mw), mw->matrix.cell_grid_line_gc,
			   0, 0, &r, 1, Unsorted);
    XSetClipRectangles(XtDisplay(mw), mw->matrix.cell_top_shadow_clip_gc,
		       0, 0, &r, 1, Unsorted);
    XSetClipRectangles(XtDisplay(mw), mw->matrix.cell_bottom_shadow_clip_gc,
		       0, 0, &r, 1, Unsorted);
    XSetClipRectangles(XtDisplay(mw), mw->matrix.label_clip_gc,
		       0, 0, &r, 1, Unsorted);
}

void
xbaeNewFont(mw)
XbaeMatrixWidget mw;
{
    XmFontContext context;
    XmStringCharSet charset;
    XFontStruct *font;

    /*
     * Make a private copy of the FontList
     */
    mw->matrix.font_list = XmFontListCopy(mw->matrix.font_list);

    /*
     * Get XFontStruct from FontList
     */
    if (!XmFontListInitFontContext(&context, mw->matrix.font_list))
	XtAppErrorMsg(XtWidgetToApplicationContext((Widget) mw),
		      "newFont", "badFont", "XbaeMatrix",
		      "XbaeMatrix: XmFontListInitFontContext failed, bad fontList",
		      NULL, 0);

    if (!XmFontListGetNextFont(context, &charset, &font))
	XtAppErrorMsg(XtWidgetToApplicationContext((Widget) mw),
		      "newFont", "badFont", "XbaeMatrix",
		      "XbaeMatrix: XmFontListGetNextFont failed, cannot get font from fontList",
		      NULL, 0);

    XtFree(charset);
    XmFontListFreeFontContext(context);

    mw->matrix.font = font;
}

void
xbaeNewLabelFont(mw)
XbaeMatrixWidget mw;
{
    XmFontContext context;
    XmStringCharSet charset;
    XFontStruct *font;

    /*
     * Make a private copy of the FontList
     */
    mw->matrix.label_font_list = XmFontListCopy(mw->matrix.label_font_list);

    /*
     * Get XFontStruct from FontList
     */
    if (!XmFontListInitFontContext(&context, mw->matrix.label_font_list))
	XtAppErrorMsg(XtWidgetToApplicationContext((Widget) mw),
		      "newFont", "badLabelFont", "XbaeMatrix",
		      "XbaeMatrix: XmFontListInitFontContext failed, bad labelFontList",
		      NULL, 0);

    if (!XmFontListGetNextFont(context, &charset, &font))
	XtAppErrorMsg(XtWidgetToApplicationContext((Widget) mw),
		      "newFont", "badLabelFont", "XbaeMatrix",
		      "XbaeMatrix: XmFontListGetNextFont failed, cannot get font from labelFontList",
		      NULL, 0);

    XtFree(charset);
    XmFontListFreeFontContext(context);

    mw->matrix.label_font = font;
}

/*
 * Get the total pixel width of the non-fixed cell area
 */
void
xbaeGetCellTotalWidth(mw)
XbaeMatrixWidget mw;
{
    int i, columns;

    /*
     * Calculate width of non-fixed cell area.
     */
    columns = TRAILING_HORIZ_ORIGIN(mw);
    for (i = mw->matrix.fixed_columns, mw->matrix.cell_total_width = 0;
	 i < columns;
	 i++)
	mw->matrix.cell_total_width += COLUMN_WIDTH(mw, i);
}

/*
 * Cache the pixel position of each column
 */
void
xbaeGetColumnPositions(mw)
XbaeMatrixWidget mw;
{
    int i, x;

    for (i = 0, x = 0;
	 i < mw->matrix.columns;
	 x += COLUMN_WIDTH(mw, i), i++)
	COLUMN_POSITION(mw, i) = x;
}

void
#if NeedFunctionPrototypes
xbaeComputeSize(XbaeMatrixWidget mw, Boolean compute_width,
		Boolean compute_height)
#else
xbaeComputeSize(mw, compute_width, compute_height)
XbaeMatrixWidget mw;
Boolean compute_width;
Boolean compute_height;
#endif
{
    unsigned long full_width = CELL_TOTAL_WIDTH(mw) +
	FIXED_COLUMN_WIDTH(mw) + TRAILING_FIXED_COLUMN_WIDTH(mw) +
	ROW_LABEL_WIDTH(mw) + 2 * mw->manager.shadow_thickness;
    unsigned long full_height = CELL_TOTAL_HEIGHT(mw) +
	FIXED_ROW_HEIGHT(mw) + TRAILING_FIXED_ROW_HEIGHT(mw) +
	COLUMN_LABEL_HEIGHT(mw) + 2 * mw->manager.shadow_thickness;
    unsigned long width, height;

    /*
     * Calculate our width.
     * If visible_columns is set, then base it on that.
     * Otherwise, if the compute_width flag is set, then we are full width.
     * Otherwise we keep whatever width we are.
     */
    if (mw->matrix.visible_columns)
	width = ROW_LABEL_WIDTH(mw) + 2 * mw->manager.shadow_thickness +
	    COLUMN_WIDTH(mw, (mw->matrix.visible_columns +
			      mw->matrix.fixed_columns) - 1) +
	    COLUMN_POSITION(mw, mw->matrix.fixed_columns +
			    mw->matrix.visible_columns - 1) +
	    TRAILING_FIXED_COLUMN_WIDTH(mw);
    else if (compute_width)
	width = full_width;
    else
	width = mw->core.width;

    /*
     * Calculate our height.
     * If visible_rows is set, then base it on that.
     * Otherwise, if the compute_height flag is set, then we are full height.
     * Otherwise we keep whatever height we are.
     */
    if (mw->matrix.visible_rows)
	height = mw->matrix.visible_rows * ROW_HEIGHT(mw) +
	    TRAILING_FIXED_ROW_HEIGHT(mw) + FIXED_ROW_HEIGHT(mw) +
	    COLUMN_LABEL_HEIGHT(mw) + 2 * mw->manager.shadow_thickness;
    else if (compute_height)
	height = full_height;
    else
	height = mw->core.height;

    /*
     * Store our calculated size.
     */
    mw->core.width = width;
    mw->core.height = height;

    /*
     * If we are less than full width, then we need an HSB, so increment
     * our height by the size of the HSB (if we are allowed to modify our
     * height).
     */
    if (width < full_width)
	if (compute_height || mw->matrix.visible_rows)
	    mw->core.height += HSCROLL_HEIGHT(mw);

    /*
     * If we are less than full height, then we need a VSB, so increment
     * our width by the size of the VSB (if we are allowed to modify our
     * width).
     */
    if (height < full_height)
	if (compute_width || mw->matrix.visible_columns)
	    mw->core.width += VSCROLL_WIDTH(mw);

    /*
     * Save our calculated size for use in our query_geometry method.
     * This is the size we really want to be (not necessarily the size
     * we will end up being).
     */
    mw->matrix.desired_width = mw->core.width;
    mw->matrix.desired_height = mw->core.height;
}

/*
 * Return the length of the longest row label
 */
short
xbaeMaxRowLabel(mw)
XbaeMatrixWidget mw;
{
    int i;
    short max = 0, len;

    /*
     * Determine the length of the longest row label
     */
    for (i = 0; i < mw->matrix.rows; i++)
    {
	len = strlen(mw->matrix.row_labels[i]);
	if (len > max)
	    max = len;
    }
    return max;
}

void
xbaeParseColumnLabel(label, lines)
String label;
ColumnLabelLines lines;
{
    char *nl;

    /*
     * First count the number of lines in the label
     */
    lines->lines = 1;
    nl = label;
    while ((nl = strchr(nl, '\n')) != NULL)
    {
	nl++;
	lines->lines++;
    }

    /*
     * Now malloc a lengths array of the correct size.
     */
    lines->lengths = (int *) XtMalloc(lines->lines * sizeof(int));

    /*
     * An entry in the lengths array is the length of that line (substring).
     */

    /*
     * Handle the case of one line (no strchr() needed)
     */
    if (lines->lines == 1)
	lines->lengths[0] = strlen(label);
    else
    {
	int i;

	nl = label;
	i = 0;
	while ((nl = strchr(nl, '\n')) != NULL)
	{
	    lines->lengths[i] = nl - label;
	    nl++;
	    label = nl;
	    i++;
	}
	lines->lengths[i] = strlen(label);
    }
}

void
xbaeFreeCells(mw)
XbaeMatrixWidget mw;
{
    int i, j;

    if (!mw->matrix.cells)
	return;

    /*
     * Free each cell in a row, then free the row and go to the next one
     */
    for (i = 0; i < mw->matrix.rows; i++)
    {
	for (j = 0; j < mw->matrix.columns; j++)
	    XtFree((XtPointer) mw->matrix.cells[i][j]);
	XtFree((XtPointer) mw->matrix.cells[i]);
    }

    /*
     * Free the array of row pointers
     */
    XtFree((XtPointer) mw->matrix.cells);
}

void
xbaeFreeRowLabels(mw)
XbaeMatrixWidget mw;
{
    int i;

    if (!mw->matrix.row_labels)
	return;

    for (i = 0; i < mw->matrix.rows; i++)
	XtFree((XtPointer) mw->matrix.row_labels[i]);

    XtFree((XtPointer) mw->matrix.row_labels);
}

void
xbaeFreeColumnLabels(mw)
XbaeMatrixWidget mw;
{
    int i;

    if (!mw->matrix.column_labels)
	return;

    for (i = 0; i < mw->matrix.columns; i++)
    {
	XtFree((XtPointer) mw->matrix.column_labels[i]);
	XtFree((XtPointer) mw->matrix.column_label_lines[i].lengths);
    }

    XtFree((XtPointer) mw->matrix.column_label_lines);
    XtFree((XtPointer) mw->matrix.column_labels);
}


void
xbaeFreeColors(mw)
XbaeMatrixWidget mw;
{
    int i;

    if (!mw->matrix.colors)
	return;

    /*
     * Free each row of Pixels
     */
    for (i = 0; i < mw->matrix.rows; i++)
	XtFree((XtPointer) mw->matrix.colors[i]);

    /*
     * Free the array of row pointers
     */
    XtFree((XtPointer) mw->matrix.colors);
}

void
xbaeFreeBackgrounds(mw)
XbaeMatrixWidget mw;
{
    int i;

    if (!mw->matrix.cell_background)
	return;

    /*
     * Free each row of Pixels
     */
    for (i = 0; i < mw->matrix.rows; i++)
	XtFree((XtPointer) mw->matrix.cell_background[i]);

    /*
     * Free the array of row pointers
     */
    XtFree((XtPointer) mw->matrix.cell_background);
}

void
xbaeFreeSelectedCells(mw)
XbaeMatrixWidget mw;
{
    int i;

    /*
     * Free each row of Booleans
     */
    for (i = 0; i < mw->matrix.rows; i++)
	XtFree((XtPointer) mw->matrix.selected_cells[i]);

    /*
     * Free the array of row pointers
     */
    XtFree((XtPointer) mw->matrix.selected_cells);
}

