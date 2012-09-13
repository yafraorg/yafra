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
 */

#include <Xm/Xm.h>
#include <Xbae/MatrixP.h>
#include <Xbae/Actions.h>
#include <Xbae/ScrollMgr.h>
#include <Xbae/Utils.h>
#include <Xm/ScrollBar.h>

static void DrawColumnLabel P(( XbaeMatrixWidget mw, int column ));
static void DrawRowLabel P(( XbaeMatrixWidget mw, int row ));
static void DrawRowShadows P(( XbaeMatrixWidget mw, unsigned int redraw_reason ));
static void DrawColumnShadows P(( XbaeMatrixWidget mw, unsigned int redraw_reason ));


/*
 * ScrollMgr implementation.
 * When we scroll using XCopyArea, occluding windows will cause GraphicsExpose
 * events to be generated, if there are no occluding windows then NoExpose
 * events will be generated. The removal of occluding windows will cause Expose
 * events.  If a number of scrolls (XCopyAreas) occur in quick succession,
 * the events will contain obsolete x/y information since our internal
 * coordinates have been scrolled to a new location.  The ScrollMgr
 * keeps track of scrolls and offsets required to relocate the events to the
 * current coordinate system.
 *
 * The Matrix widget has two ScrollMgrs, one for the Matrixs window
 * and one for the Clip widgets window.
 *
 * Each widgets compress_exposures field should be XtExposeCompressSeries
 * or XtExposeNoCompress.
 *
 * The idea behind this code is based on the PanHandler posted by Chuck Ocheret
 * (chuck@fid.morgan.com)
 */


/*
 * Create and initialize a ScrollMgr
 */
SmScrollMgr
xbaeSmCreateScrollMgr()
{
    SmScrollMgr scrollMgr = XtNew(SmScrollMgrRec);

    scrollMgr->offset_x = 0;
    scrollMgr->offset_y = 0;
    scrollMgr->scroll_count = 0;
    scrollMgr->scroll_queue = NULL;
    scrollMgr->scrolling = False;

    return scrollMgr;
}

/*
 * Destroy a ScrollMgr, including any queued scrolls
 */
void
xbaeSmDestroyScrollMgr(scrollMgr)
SmScrollMgr scrollMgr;
{
    if (scrollMgr->scroll_queue)
    {
	SmScrollNode node = scrollMgr->scroll_queue->next;

	while (node != scrollMgr->scroll_queue)
	{
	    SmScrollNode d = node;

	    node = node->next;
	    XtFree((XtPointer) d);
	}
	XtFree((XtPointer) node);
    }

    XtFree((XtPointer) scrollMgr);
}

/*
 * Record a new scroll request in the ScrollMgr
 */
void
xbaeSmAddScroll(scrollMgr, delta_x, delta_y)
SmScrollMgr scrollMgr;
int delta_x;
int delta_y;
{
    SmScrollNode node = XtNew(SmScrollNodeRec);

    node->x = delta_x;
    node->y = delta_y;

    scrollMgr->offset_x += delta_x;
    scrollMgr->offset_y += delta_y;
    scrollMgr->scroll_count++;

    /*
     * Insert the node at the end of the queue
     */
    if (!scrollMgr->scroll_queue)
    {
	scrollMgr->scroll_queue = node;
	node->next = node;
	node->prev = node;
    }
    else
    {
	SmScrollNode last = scrollMgr->scroll_queue->prev;

	last->next = node;
	node->next = scrollMgr->scroll_queue;
	node->prev = last;
	scrollMgr->scroll_queue->prev = node;
    }
}

/*
 * Remove a scroll from the ScrollMgr queue
 */
void
xbaeSmRemoveScroll(scrollMgr)
SmScrollMgr scrollMgr;
{
    if (scrollMgr->scroll_count)
    {
	SmScrollNode node = scrollMgr->scroll_queue;

	scrollMgr->offset_x -= node->x;
	scrollMgr->offset_y -= node->y;

	/*
	 * Remove node from head of queue
	 */
	if (node->next == node)
	    scrollMgr->scroll_queue = NULL;
	else
	{
	    scrollMgr->scroll_queue = node->next;
	    node->next->prev = node->prev;
	    node->prev->next = node->next;
	}
	XtFree((XtPointer) node);

	scrollMgr->scroll_count--;
    }
}

/*
 * Handle an expose event
 */
void
xbaeSmScrollEvent(scrollMgr, event)
SmScrollMgr scrollMgr;
XEvent *event;
{
    switch (event->type)
    {

    case Expose:

	/*
	 * Normal Expose event, translate it into our scrolled
	 * coordinate system.
	 */
	event->xexpose.x += scrollMgr->offset_x;
	event->xexpose.y += scrollMgr->offset_y;
	break;

    case GraphicsExpose:

	/*
	 * If we are not scrolling, then this must be the first
	 * GraphicsExpose event.  Remove the corresponding scroll from the
	 * queue, and if we have more GraphicsExposes to come, set scrolling
	 * to True.
	 */
	if (scrollMgr->scrolling == False)
	{
	    xbaeSmRemoveScroll(scrollMgr);
	    if (event->xgraphicsexpose.count != 0)
		scrollMgr->scrolling = True;
	}

	/*
	 * This is the last GraphicsExpose so set scrolling to False.
	 */
	else if (event->xgraphicsexpose.count == 0)
	    scrollMgr->scrolling = False;

	/*
	 * Translate the event into our scrolled coordinate system.
	 */
	event->xgraphicsexpose.x += scrollMgr->offset_x;
	event->xgraphicsexpose.y += scrollMgr->offset_y;
	break;

    case NoExpose:

	/*
	 * A NoExpose event means we won't be getting any GraphicsExpose
	 * events, so remove the scroll from the queue and set scrolling
	 * to False.
	 */
	xbaeSmRemoveScroll(scrollMgr);
	scrollMgr->scrolling = False;
	break;

    default:
	break;
    }
}

/*
 * Callback for vertical scrollbar
 */
/* ARGSUSED */
void
xbaeScrollVertCB(w, client_data, call_data)
Widget w;
XtPointer client_data;
XmScrollBarCallbackStruct *call_data;
{
    XbaeMatrixWidget mw = (XbaeMatrixWidget) XtParent(w);
    int src_y, dest_y, height;
    XBAERectangle fixed, nonfixed;
    
    /*
     * Didn't scroll
     */
    if (call_data->value == VERT_ORIGIN(mw))
	return;

    /*
     * Scrolled forward. We want to copy a chunk starting at src_y up
     * to the top (dest_y=0)
     */
    else if (call_data->value > VERT_ORIGIN(mw))
    {
	dest_y = 0;
	src_y = (call_data->value - VERT_ORIGIN(mw)) * ROW_HEIGHT(mw);
	height = ClipChild(mw)->core.height - src_y;
    }

    /*
     * Scrolled backward. We want to copy a chunk starting at the top
     * (src_y=0) down to dest_y.
     */
    else
    {
	dest_y = (VERT_ORIGIN(mw) - call_data->value) * ROW_HEIGHT(mw);
	src_y = 0;
	height = ClipChild(mw)->core.height - dest_y;
    }

    /*
     * The textField needs to scroll along with the cells.
     */
    if (XtIsManaged(TextChild(mw)))
	XtMoveWidget(TextChild(mw),
		     TextChild(mw)->core.x,
		     TextChild(mw)->core.y +
		     (VERT_ORIGIN(mw) - call_data->value) * ROW_HEIGHT(mw));

    /*
     * Now we can adjust our vertical origin
     */
    VERT_ORIGIN(mw) = call_data->value;

    if (!XtIsRealized((Widget)mw))
	return;

    /*
     * If we scrolled more than a screenful, just clear and
     * redraw the whole thing
     */
    if (height <= 0)
    {
	/*
	 * Clear the whole clip window.
	 */
	XClearArea(XtDisplay(mw), XtWindow(ClipChild(mw)),
		   0, 0,
		   0 /*Full Width*/, 0 /*Full Height*/,
		   False);

	/*
	 * Redraw all the non-fixed cells in the clip window
	 */
	SETRECT(nonfixed,
		0, 0,
		ClipChild(mw)->core.width - 1,
		ClipChild(mw)->core.height - 1);

	/*
	 * Clear the non-fixed row labels and the cells in fixed columns
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   0, FIXED_ROW_LABEL_OFFSET(mw),
		   FIXED_COLUMN_LABEL_OFFSET(mw) - 1,
		   VISIBLE_HEIGHT(mw) - 1,
		   False);

	/*
	 * Clear the cells in trailing fixed columns
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw),
		   FIXED_ROW_LABEL_OFFSET(mw),
		   TRAILING_FIXED_COLUMN_WIDTH(mw) - 1,
		   VISIBLE_HEIGHT(mw) - 1,
		   False);

	/*
	 * Redraw non-fixed row labels and cells in fixed columns
	 */
	SETRECT(fixed,
		0, FIXED_ROW_LABEL_OFFSET(mw),
		TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) +
		TRAILING_FIXED_COLUMN_WIDTH(mw) - 1,
		TRAILING_FIXED_ROW_LABEL_OFFSET(mw) - 1);
    }

    /*
     * If we scrolled less than a screenful, we want to copy as many
     * pixels as we can and then clear and redraw the newly scrolled data.
     */
    else
    {
	int y_clear = src_y > dest_y ? height : 0;

	/*
	 * Queue this scroll with the ScrollMgr
	 */
	xbaeSmAddScroll(mw->matrix.clip_scroll_mgr, 0, dest_y - src_y);

	/*
	 * Copy the non-fixed cells in the clip widget
	 */
	XCopyArea(XtDisplay(mw),
		  XtWindow(ClipChild(mw)), XtWindow(ClipChild(mw)),
		  mw->matrix.draw_gc,
		  0, src_y,
		  ClipChild(mw)->core.width, height,
		  0, dest_y);

	/*
	 * Clear the newly scrolled chunk of the clip widget
	 */
	XClearArea(XtDisplay(mw), XtWindow(ClipChild(mw)),
		   0, y_clear,
		   0 /*Full Width*/, ClipChild(mw)->core.height - height,
		   False);

	/*
	 * Redraw the non-fixed cells into the new chunk
	 */
	SETRECT(nonfixed,
		0, y_clear,
		ClipChild(mw)->core.width - 1,
		(y_clear + (ClipChild(mw)->core.height - height)) - 1);

	/*
	 * Translate coordinates for fixed columns and row labels.
	 */
	src_y += FIXED_ROW_LABEL_OFFSET(mw);
	dest_y += FIXED_ROW_LABEL_OFFSET(mw);
	y_clear += FIXED_ROW_LABEL_OFFSET(mw);

	/*
	 * Queue this scroll with the ScrollMgr
	 */
	xbaeSmAddScroll(mw->matrix.matrix_scroll_mgr, 0, dest_y - src_y);

	/*
	 * Copy the fixed columns and row labels
	 */
	XCopyArea(XtDisplay(mw),
		  XtWindow(mw), XtWindow(mw),
		  mw->matrix.draw_gc,
		  0, src_y,
		  FIXED_COLUMN_LABEL_OFFSET(mw), height,
		  0, dest_y);

	/*
	 * Copy trailing fixed columns
	 */
	XCopyArea(XtDisplay(mw),
		  XtWindow(mw), XtWindow(mw),
		  mw->matrix.draw_gc,
		  TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw), src_y,
		  TRAILING_FIXED_COLUMN_WIDTH(mw), height,
		  TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw), dest_y);

	/*
	 * Clear the newly scrolled chunk of fixed columns and row labels
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   0, y_clear,
		   FIXED_COLUMN_LABEL_OFFSET(mw),
		   ClipChild(mw)->core.height - height,
		   False);

	/*
	 * Clear the newly scrolled chunk of trailing fixed columns
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw), y_clear,
		   TRAILING_FIXED_COLUMN_WIDTH(mw),
		   ClipChild(mw)->core.height - height,
		   False);

	/*
	 * Redraw the new chunk of fixed columns and row labels
	 */
	SETRECT(fixed,
		0, y_clear,
		TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) +
		TRAILING_FIXED_COLUMN_WIDTH(mw) - 1,
		(y_clear + (ClipChild(mw)->core.height - height)) - 1);
    }
    
    /*
     * Perform the actual redraw. The call to draw the grid shadows
     * must be done after any XClearAreas() to ensure we don't redraw
     * more than we have to; that is, we could put the call in the
     * redraw cells routine, but we would end up occasionally redrawing
     * more than once.
     */
    xbaeRedrawLabelsAndFixed(mw, &fixed);
    xbaeRedrawCells(mw, &nonfixed);
    xbaeDrawGridShadows(mw, GRID_REDRAW_SCROLL_VERT);
}

/*
 * Callback for horizontal scrollbar
 */
/* ARGSUSED */
void
xbaeScrollHorizCB(w, client_data, call_data)
Widget w;
XtPointer client_data;
XmScrollBarCallbackStruct *call_data;
{
    XbaeMatrixWidget mw = (XbaeMatrixWidget) XtParent(w);
    int src_x, dest_x, width;
    XBAERectangle fixed, nonfixed;

    /*
     * Didn't scroll
     */
    if (call_data->value == HORIZ_ORIGIN(mw))
	return;

    /*
     * Scrolled right. We want to copy a chunk starting at src_x over to
     * the left (dest_x=0)
     */
    else if (call_data->value > HORIZ_ORIGIN(mw))
    {
	dest_x = 0;
	src_x = call_data->value - HORIZ_ORIGIN(mw);
	width = ClipChild(mw)->core.width - src_x;
    }

    /*
     * Scrolled left. We want to copy a chunk starting at the left (src_x=0)
     * over to the right to dest_x
     */
    else
    {
	dest_x = HORIZ_ORIGIN(mw) - call_data->value;
	src_x = 0;
	width = ClipChild(mw)->core.width - dest_x;
    }

    /*
     * The textField needs to scroll along with the cells.
     */
    if (XtIsManaged(TextChild(mw)))
	XtMoveWidget(TextChild(mw),
		     TextChild(mw)->core.x + (HORIZ_ORIGIN(mw) -
					      call_data->value),
		     TextChild(mw)->core.y);

    /*
     * Now we can adjust our horizontal origin
     */
    HORIZ_ORIGIN(mw) = call_data->value;

    if (!XtIsRealized((Widget)mw))
	return;

    /*
     * If we scrolled more than a screenful, just clear and
     * redraw the whole thing
     */
    if (width <= 0)
    {
	/*
	 * Clear the whole clip window
	 */
	XClearArea(XtDisplay(mw), XtWindow(ClipChild(mw)),
		   0, 0,
		   ClipChild(mw)->core.width - 1,
		   ClipChild(mw)->core.height - 1,
		   False);

	/*
	 * Redraw all the non-fixed cells in the clip window
	 */
	SETRECT(nonfixed,
		0, 0,
		ClipChild(mw)->core.width - 1,
		ClipChild(mw)->core.height - 1);

	/*
	 * Clear the non-fixed column labels and the cells in fixed rows
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   FIXED_COLUMN_LABEL_OFFSET(mw), 0,
		   VISIBLE_WIDTH(mw) - 1,
		   FIXED_ROW_LABEL_OFFSET(mw) - 1, False);

	/*
	 * Clear the cells in the trailing fixed rows
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   FIXED_COLUMN_LABEL_OFFSET(mw),
		   TRAILING_FIXED_ROW_LABEL_OFFSET(mw),
		   VISIBLE_WIDTH(mw) - 1,
		   TRAILING_FIXED_ROW_HEIGHT(mw) - 1, False);

	/*
	 * Redraw non-fixed column labels and cells in fixed rows
	 */
	SETRECT(fixed,
		FIXED_COLUMN_LABEL_OFFSET(mw), 0,
		TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) - 1,
		TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
		TRAILING_FIXED_ROW_HEIGHT(mw) - 1);
    }

    /*
     * If we scrolled less than a screenful, we want to copy as many
     * pixels as we can and then clear and redraw the newly scrolled data.
     */
    else
    {
	int x_clear = src_x > dest_x ? width : 0;

	/*
	 * Queue this scroll with the ScrollMgr
	 */
	xbaeSmAddScroll(mw->matrix.clip_scroll_mgr, dest_x - src_x, 0);

	/*
	 * Copy the non-fixed cells in the clip widget
	 */
	XCopyArea(XtDisplay(mw),
		  XtWindow(ClipChild(mw)), XtWindow(ClipChild(mw)),
		  mw->matrix.draw_gc,
		  src_x, 0,
		  width, ClipChild(mw)->core.height,
		  dest_x, 0);

	/*
	 * Clear the newly scrolled chunk of the clip widget
	 */
	XClearArea(XtDisplay(mw), XtWindow(ClipChild(mw)),
		   x_clear, 0,
		   ClipChild(mw)->core.width - width, 0 /*Full Height*/,
		   False);

	/*
	 * Redraw the non-fixed cells into the new chunk
	 */
	SETRECT(nonfixed,
		x_clear, 0,
		(x_clear + (ClipChild(mw)->core.width - width)) - 1,
		ClipChild(mw)->core.height - 1);

	/*
	 * Translate coordinates for fixed rows and column labels.
	 */
	src_x += FIXED_COLUMN_LABEL_OFFSET(mw);
	dest_x += FIXED_COLUMN_LABEL_OFFSET(mw);
	x_clear += FIXED_COLUMN_LABEL_OFFSET(mw);

	/*
	 * Queue this scroll with the ScrollMgr
	 */
	xbaeSmAddScroll(mw->matrix.matrix_scroll_mgr, dest_x - src_x, 0);

	/*
	 * Copy the fixed rows and column labels
	 */
	XCopyArea(XtDisplay(mw),
		  XtWindow(mw), XtWindow(mw),
		  mw->matrix.draw_gc,
		  src_x, 0,
		  width, FIXED_ROW_LABEL_OFFSET(mw),
		  dest_x, 0);

	/*
	 * Copy the trailing fixed rows
	 */
	XCopyArea(XtDisplay(mw),
		  XtWindow(mw), XtWindow(mw),
		  mw->matrix.draw_gc,
		  src_x, TRAILING_FIXED_ROW_LABEL_OFFSET(mw),
		  width, TRAILING_FIXED_ROW_HEIGHT(mw),
		  dest_x, TRAILING_FIXED_ROW_LABEL_OFFSET(mw));

	/*
	 * Clear the newly scrolled chunk of fixed rows and column labels
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   x_clear, 0,
		   ClipChild(mw)->core.width - width,
		   FIXED_ROW_LABEL_OFFSET(mw),
		   False);

	/*
	 * Clear the newly scrolled chunk of trailing fixed rows
	 */
	XClearArea(XtDisplay(mw), XtWindow(mw),
		   x_clear, TRAILING_FIXED_ROW_LABEL_OFFSET(mw),
		   ClipChild(mw)->core.width - width,
		   TRAILING_FIXED_ROW_HEIGHT(mw),
		   False);

	/*
	 * Redraw the new chunk of fixed rows and column labels
	 */
	SETRECT(fixed,
		x_clear, 0,
		(x_clear + (ClipChild(mw)->core.width - width)) - 1,
		TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
		TRAILING_FIXED_ROW_HEIGHT(mw) - 1);
    }

    /*
     * Perform the actual redraw. The call to draw the grid shadows
     * must be done after any XClearAreas() to ensure we don't redraw
     * more than we have to; that is, we could put the call in the
     * redraw cells routine, but we would end up occasionally redrawing
     * more than once.
     */
    xbaeRedrawLabelsAndFixed(mw, &fixed);
    xbaeRedrawCells(mw, &nonfixed);
    xbaeDrawGridShadows(mw, GRID_REDRAW_SCROLL_HORIZ);
}

/*
 * Draw the column label for the specified column.  Handles labels in
 * fixed and non-fixed columns.
 */
static void
DrawColumnLabel(mw, column)
XbaeMatrixWidget mw;
int column;
{
    String label;
    int x, y, i;

    if (mw->matrix.column_labels[column][0] == '\0')
	return;

    /*
     * If the column label is in a fixed column, we don't need to account
     * for the horiz_origin
     */
    if (column < (int)mw->matrix.fixed_columns)
	x = COLUMN_LABEL_OFFSET(mw) + COLUMN_POSITION(mw, column) +
	    TEXT_X_OFFSET(mw);
    else if (column >= TRAILING_HORIZ_ORIGIN(mw))
	x = TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) +
	    COLUMN_POSITION(mw, column) -
	    COLUMN_POSITION(mw, TRAILING_HORIZ_ORIGIN(mw)) +
	    TEXT_X_OFFSET(mw);
    else
	x = COLUMN_LABEL_OFFSET(mw) + (COLUMN_POSITION(mw, column) -
				       HORIZ_ORIGIN(mw)) + TEXT_X_OFFSET(mw);

    /*
     * Set our y to the baseline of the first line in this column
     */
/*
  y = TEXT_Y_OFFSET(mw) +
	(mw->matrix.column_label_maxlines -
	 mw->matrix.column_label_lines[column].lines) * LABEL_HEIGHT(mw);
	 */
    y = mw->matrix.label_font->max_bounds.ascent +
	mw->matrix.cell_shadow_thickness +
	mw->matrix.cell_highlight_thickness +
	mw->matrix.cell_margin_height +
	(mw->matrix.column_label_maxlines -
	 mw->matrix.column_label_lines[column].lines) * LABEL_HEIGHT(mw);

    label = mw->matrix.column_labels[column];
    for (i = 0; i < mw->matrix.column_label_lines[column].lines; i++)
    {
	xbaeDrawString(mw, XtWindow(mw),
		       label, mw->matrix.column_label_lines[column].lengths[i],
		       x, y, mw->matrix.column_widths[column],
		       mw->matrix.column_label_alignments ?
		       mw->matrix.column_label_alignments[column] :
		       XmALIGNMENT_BEGINNING, False, mw->matrix.bold_labels,
		       (column >= (int)mw->matrix.fixed_columns) &&
		       (column < TRAILING_HORIZ_ORIGIN(mw)), False, True,
		       mw->manager.foreground);
	y += LABEL_HEIGHT(mw);
	label += mw->matrix.column_label_lines[column].lengths[i] + 1;
    }
}

/*
 * Draw the row label for the specified row. Handles labels in fixed and
 * non-fixed rows.
 */
static void
DrawRowLabel(mw, row)
XbaeMatrixWidget mw;
int row;
{
    int y;

    if (mw->matrix.row_labels[row][0] == '\0')
	return;

    /*
     * If the row label is in a fixed row we don't need to account
     * for the vert_origin
     */
    if (row < (int)mw->matrix.fixed_rows)
	y = ROW_LABEL_OFFSET(mw) + ROW_HEIGHT(mw) * row + TEXT_Y_OFFSET(mw);
    else if (row >= TRAILING_VERT_ORIGIN(mw))
	y = TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
	    ROW_HEIGHT(mw) * (row - TRAILING_VERT_ORIGIN(mw)) + TEXT_Y_OFFSET(mw);
    else
	y = ROW_LABEL_OFFSET(mw) + ROW_HEIGHT(mw) * (row - VERT_ORIGIN(mw)) +
	    LABEL_Y_OFFSET(mw);

    xbaeDrawString(mw, XtWindow(mw),
		   mw->matrix.row_labels[row],
		   strlen(mw->matrix.row_labels[row]),
		   TEXT_X_OFFSET(mw), y, mw->matrix.row_label_width,
		   mw->matrix.row_label_alignment, False,
		   mw->matrix.bold_labels, False, True, False,
		   mw->manager.foreground);
}

/*
 * Redraw all cells in the clip widget damaged by the passed Rectangle.
 * The Rectangle must be within the bounds of the cells. These are the
 * non-fixed cells.
 */
void
xbaeRedrawCells(mw, expose)
XbaeMatrixWidget mw;
XBAERectangle *expose;
{
    int startCol, endCol, startRow, endRow, i, j;
    XBAERectangle rect;

    /*
     * Translate the 'expose' Rectangle to take into account the
     * fixed rows or columns.
     */
    SETRECT(rect,
	    expose->x1 + FIXED_COLUMN_WIDTH(mw),
	    expose->y1 + FIXED_ROW_HEIGHT(mw),
	    expose->x2 + FIXED_COLUMN_WIDTH(mw),
	    expose->y2 + FIXED_ROW_HEIGHT(mw));

    /*
     * Calculate the starting and ending rows/columns of the cells
     * which must be redrawn.
     */
    startCol = xbaeXtoCol(mw, rect.x1 + HORIZ_ORIGIN(mw));
    endCol = xbaeXtoCol(mw, rect.x2 + HORIZ_ORIGIN(mw));
    startRow = YtoRow(mw, rect.y1) + VERT_ORIGIN(mw);
    endRow = YtoRow(mw, rect.y2) + VERT_ORIGIN(mw);

    /*
     * Redraw all cells which were exposed.
     */
    for (i = startRow; i <= endRow; i++)
	for (j = startCol; j <= endCol; j++)
	    xbaeDrawCell(mw, i, j);
}

/*
 * Redraw the row and column labels and the cells in fixed rows/columns
 * that are overlapped by the Rectangle argument.
 */
void
xbaeRedrawLabelsAndFixed(mw, expose)
XbaeMatrixWidget mw;
XBAERectangle *expose;
{
    /*
     * Handle the row labels that are in fixed rows
     */
    if (mw->matrix.fixed_rows && mw->matrix.row_labels)
    {
	XBAERectangle rect;
	
	/*
	 * Get the Rectangle enclosing the fixed row labels
	 */
	SETRECT(rect, 0, ROW_LABEL_OFFSET(mw),
		ROW_LABEL_WIDTH(mw) - 1, FIXED_ROW_LABEL_OFFSET(mw) - 1);
	
	/*
	 * If the expose Rectangle overlaps, then some labels must be redrawn
	 */
	if (OVERLAP(*expose, rect))
	{
	    XBAERectangle intersect;
	    int endRow, i;

	    /*
	     * Intersect the fixed-row-labels Rectangle with the expose
	     * Rectangle along the Y axis.  The resulting Rectangle will
	     * be in 'rect's coordinate system.
	     */
	    Y_INTERSECT(rect, *expose, intersect);

	    /*
	     * Redraw each label that was intersected
	     */
	    endRow = YtoRow(mw, intersect.y2);
	    for (i = YtoRow(mw, intersect.y1); i <= endRow; i++)
		DrawRowLabel(mw, i);
	}
    }

    /*
     * Handle the row labels that are in trailing fixed rows
     */
    if (mw->matrix.trailing_fixed_rows && mw->matrix.row_labels)
    {
	XBAERectangle rect;

	/*
	 * Get the Rectangle enclosing the fixed row labels
	 */
	SETRECT(rect, 0, TRAILING_FIXED_ROW_LABEL_OFFSET(mw),
		ROW_LABEL_WIDTH(mw) - 1,
		TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
		TRAILING_FIXED_ROW_HEIGHT(mw) - 1);

	/*
	 * If the expose Rectangle overlaps, then some labels must be redrawn
	 */
	if (OVERLAP(*expose, rect))
	{
	    XBAERectangle intersect;
	    int endRow, i;

	    /*
	     * Intersect the fixed-row-labels Rectangle with the expose
	     * Rectangle along the Y axis.  The resulting Rectangle will
	     * be in 'rect's coordinate system.
	     */
	    Y_INTERSECT(rect, *expose, intersect);

	    /*
	     * Redraw each label that was intersected
	     */
	    endRow = YtoRow(mw, intersect.y2) + TRAILING_VERT_ORIGIN(mw);
	    for (i = YtoRow(mw, intersect.y1) + TRAILING_VERT_ORIGIN(mw);
		 i <= endRow; i++)
		DrawRowLabel(mw, i);
	}
    }

    /*
     * Handle row labels that aren't in fixed rows
     */
    if (mw->matrix.row_labels)
    {
	XBAERectangle rect;

	/*
	 * Get the Rectangle enclosing the non-fixed row labels
	 */
	SETRECT(rect, 0, FIXED_ROW_LABEL_OFFSET(mw),
		ROW_LABEL_WIDTH(mw) - 1,
		FIXED_ROW_LABEL_OFFSET(mw) + VISIBLE_HEIGHT(mw) - 1);

	/*
	 * If the expose Rectangle overlaps, then some labels must be redrawn
	 */
	if (OVERLAP(*expose, rect))
	{
	    XBAERectangle intersect;
	    int endRow, i;

	    /*
	     * Intersect the fixed-row-labels Rectangle with the expose
	     * Rectangle along the Y axis.  The resulting Rectangle will
	     * be in 'rect's coordinate system.
	     */
	    Y_INTERSECT(rect, *expose, intersect);

	    /*
	     * Translate 'intersect' to take into account any fixed rows.
	     * This gets it back into the coord system expected by YtoRow().
	     */
	    intersect.y1 += FIXED_ROW_HEIGHT(mw);
	    intersect.y2 += FIXED_ROW_HEIGHT(mw);

	    /*
	     * Redraw each label that was intersected
	     */
	    endRow = YtoRow(mw, intersect.y2) + VERT_ORIGIN(mw);
	    for (i = YtoRow(mw, intersect.y1) + VERT_ORIGIN(mw); i <= endRow;
		 i++)
		DrawRowLabel(mw, i);
	}
    }

    /*
     * Handle the column labels that are in fixed columns
     */
    if (mw->matrix.fixed_columns && mw->matrix.column_labels)
    {
	XBAERectangle rect;

	/*
	 * Get the Rectangle enclosing the portion of the column labels
	 * that are in fixed columns
	 */
	SETRECT(rect,
		COLUMN_LABEL_OFFSET(mw), 0,
		FIXED_COLUMN_LABEL_OFFSET(mw) - 1,
		COLUMN_LABEL_HEIGHT(mw) - 1);

	/*
	 * If the expose Rectangle overlaps, then some labels must be redrawn
	 */
	if (OVERLAP(*expose, rect))
	{
	    XBAERectangle intersect;
	    int endCol, i;

	    /*
	     * Intersect the fixed-column-labels Rectangle with the expose
	     * Rectangle along the X axis.  The resulting Rectangle will
	     * be in 'rect's coordinate system.
	     */
	    X_INTERSECT(rect, *expose, intersect);

	    /*
	     * Redraw each label that was intersected
	     */
	    endCol = xbaeXtoCol(mw, intersect.x2);
	    for (i = xbaeXtoCol(mw, intersect.x1); i <= endCol; i++)
		DrawColumnLabel(mw, i);
	}
    }

    /*
     * Handle the column labels that are in trailing fixed columns
     */
    if (mw->matrix.trailing_fixed_columns && mw->matrix.column_labels)
    {
	XBAERectangle rect;

	/*
	 * Get the Rectangle enclosing the portion of the column labels
	 * that are in fixed columns
	 */
	SETRECT(rect,
		TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw), 0,
		TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) +
		TRAILING_FIXED_COLUMN_WIDTH(mw) - 1,
		COLUMN_LABEL_HEIGHT(mw) - 1);

	/*
	 * If the expose Rectangle overlaps, then some labels must be redrawn
	 */
	if (OVERLAP(*expose, rect))
	{
	    XBAERectangle intersect;
	    int endCol, i;

	    /*
	     * Intersect the fixed-column-labels Rectangle with the expose
	     * Rectangle along the X axis.  The resulting Rectangle will
	     * be in 'rect's coordinate system.
	     */
	    X_INTERSECT(rect, *expose, intersect);

	    /*
	     * Redraw each label that was intersected
	     */
	    endCol = xbaeXtoCol(mw, intersect.x2) + TRAILING_HORIZ_ORIGIN(mw);
	    for (i = xbaeXtoCol(mw, intersect.x1) + TRAILING_HORIZ_ORIGIN(mw);
		 i <= endCol; i++)
		DrawColumnLabel(mw, i);
	}
    }

    /*
     * Handle column labels that aren't in fixed columns
     */
    if (mw->matrix.column_labels)
    {
	XBAERectangle rect;

	/*
	 * Get the Rectangle enclosing the non-fixed column labels
	 */
	SETRECT(rect,
		FIXED_COLUMN_LABEL_OFFSET(mw), 0,
		FIXED_COLUMN_LABEL_OFFSET(mw) + VISIBLE_WIDTH(mw) - 1,
		COLUMN_LABEL_HEIGHT(mw) - 1);

	/*
	 * If the expose Rectangle overlaps, then some labels must be redrawn
	 */
	if (OVERLAP(*expose, rect))
	{
	    XBAERectangle intersect;
	    int endCol, i;

	    /*
	     * Intersect the non-fixed-column-labels Rectangle with the expose
	     * Rectangle along the X axis.  The resulting Rectangle will
	     * be in 'rect's coordinate system.
	     */
	    X_INTERSECT(rect, *expose, intersect);

	    /*
	     * Translate 'intersect' to take into account any fixed columns.
	     * This gets it back into the coord system expected by XtoCol().
	     */
	    intersect.x1 += FIXED_COLUMN_WIDTH(mw);
	    intersect.x2 += FIXED_COLUMN_WIDTH(mw);

	    /*
	     * Redraw each label that was intersected
	     */
	    endCol = xbaeXtoCol(mw, intersect.x2 + HORIZ_ORIGIN(mw));
	    for (i = xbaeXtoCol(mw, intersect.x1 + HORIZ_ORIGIN(mw));
		 i <= endCol;
		 i++)
		DrawColumnLabel(mw, i);
	}
    }

    /*
     * Handle cells in fixed rows except those also in fixed columns
     */
    if (mw->matrix.fixed_rows)
    {
	XBAERectangle rect;

	/*
	 * Get the Rectangle enclosing the cells in fixed rows
	 */
	SETRECT(rect,
		FIXED_COLUMN_LABEL_OFFSET(mw), ROW_LABEL_OFFSET(mw),
		FIXED_COLUMN_LABEL_OFFSET(mw) + VISIBLE_WIDTH(mw) - 1,
		FIXED_ROW_LABEL_OFFSET(mw) - 1);

	/*
	 * If the expose Rectangle overlaps, then some cells must be redrawn
	 */
	if (OVERLAP(*expose, rect))
	{
	    XBAERectangle intersect;
	    int startCol, endCol, startRow, endRow, i, j;

	    /*
	     * Intersect the fixed-cells Rectangle with the expose
	     * Rectangle along the X and Y axis.  The resulting Rectangle will
	     * be in 'rect's coordinate system.
	     */
	    INTERSECT(rect, *expose, intersect);

	    intersect.x1 += FIXED_COLUMN_WIDTH(mw);
	    intersect.x2 += FIXED_COLUMN_WIDTH(mw);

	    /*
	     * Get starting and ending rows/columns. Always take into
	     * account the scrolling origins for the columns; for rows
	     * only if we are fixed in that dimension.
	     */
	    startCol = xbaeXtoCol(mw, intersect.x1 + HORIZ_ORIGIN(mw));
	    endCol = xbaeXtoCol(mw, intersect.x2 + HORIZ_ORIGIN(mw));

	    startRow = YtoRow(mw, intersect.y1) +
		(mw->matrix.fixed_rows
		 ? 0
		 : VERT_ORIGIN(mw));
	    endRow = YtoRow(mw, intersect.y2) +
		(mw->matrix.fixed_rows
		 ? 0
		 : VERT_ORIGIN(mw));

	    /*
	     * Redraw each cell that was intersected
	     */
	    for (i = startRow; i <= endRow; i++)
		for (j = startCol; j <= endCol; j++)
		    xbaeDrawCell(mw, i, j);
	}
    }

    /*
     * Handle cells in trailing fixed rows except those also in fixed columns
     */
    if (mw->matrix.trailing_fixed_rows)
    {
	XBAERectangle rect;

	/*
	 * Get the Rectangle enclosing the cells in fixed rows
	 */
	SETRECT(rect,
		FIXED_COLUMN_LABEL_OFFSET(mw), TRAILING_FIXED_ROW_LABEL_OFFSET(mw),
		FIXED_COLUMN_LABEL_OFFSET(mw) + VISIBLE_WIDTH(mw) - 1,
		TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
		TRAILING_FIXED_ROW_HEIGHT(mw) - 1);

	/*
	 * If the expose Rectangle overlaps, then some cells must be redrawn
	 */
	if (OVERLAP(*expose, rect))
	{
	    XBAERectangle intersect;
	    int startCol, endCol, startRow, endRow, i, j;

	    /*
	     * Intersect the fixed-cells Rectangle with the expose
	     * Rectangle along the X and Y axis.  The resulting Rectangle will
	     * be in 'rect's coordinate system.
	     */
	    INTERSECT(rect, *expose, intersect);

	    intersect.x1 += FIXED_COLUMN_WIDTH(mw);
	    intersect.x2 += FIXED_COLUMN_WIDTH(mw);

	    /*
	     * Get starting and ending rows/columns. Always take into
	     * account the scrolling origins for the columns and never
	     * for the rows.
	     */
	    startCol = xbaeXtoCol(mw, intersect.x1 + HORIZ_ORIGIN(mw));
	    endCol = xbaeXtoCol(mw, intersect.x2 + HORIZ_ORIGIN(mw));

	    startRow = YtoRow(mw, intersect.y1) + TRAILING_VERT_ORIGIN(mw);
	    endRow = YtoRow(mw, intersect.y2) + TRAILING_VERT_ORIGIN(mw);

	    /*
	     * Redraw each cell that was intersected
	     */
	    xbaeSetClipMask(mw, CLIP_TRAILING_FIXED_ROWS);
	    for (i = startRow; i <= endRow; i++)
		for (j = startCol; j <= endCol; j++)
		    xbaeDrawCell(mw, i, j);
	    xbaeSetClipMask(mw, CLIP_NONE);
	}
    }

    /*
     * Handle cells in fixed columns
     */
    if (mw->matrix.fixed_columns)
    {
	XBAERectangle rect;

	/*
	 * Get the Rectangle enclosing the cells in fixed columns
	 */
	SETRECT(rect,
		COLUMN_LABEL_OFFSET(mw), ROW_LABEL_OFFSET(mw),
		FIXED_COLUMN_LABEL_OFFSET(mw) - 1,
		TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
		TRAILING_FIXED_ROW_HEIGHT(mw) - 1);

	/*
	 * If the expose Rectangle overlaps, then some cells must be redrawn
	 */
	if (OVERLAP(*expose, rect))
	{
	    XBAERectangle intersect;
	    int startCol, endCol, startRow, endRow, skipRow = -1, i, j;
	    Boolean redrawFixedRows, redrawTrailingFixedRows, setMask;

	    /*
	     * Intersect the fixed-cells Rectangle with the expose
	     * Rectangle along the X and Y axis.  The resulting Rectangle will
	     * be in 'rect's coordinate system.
	     */
	    INTERSECT(rect, *expose, intersect);

	    /*
	     * If we have any fixed rows, we might need to redraw the cells
	     * located in the intersection of the fixed rows and columns.
	     * These cells may force use to be different than our current VERT_ORIGIN.
	     */
	    setMask = redrawFixedRows = redrawTrailingFixedRows = False;
	    if (mw->matrix.fixed_rows)
	    {
		setMask = True;

		SETRECT(rect,
			COLUMN_LABEL_OFFSET(mw), ROW_LABEL_OFFSET(mw),
			FIXED_COLUMN_LABEL_OFFSET(mw) - 1,
			FIXED_ROW_LABEL_OFFSET(mw) - 1);

		if (OVERLAP(*expose, rect))
		    redrawFixedRows = True;
	    }

	    if (mw->matrix.trailing_fixed_rows)
	    {
		setMask = True;

		SETRECT(rect,
			COLUMN_LABEL_OFFSET(mw),
			TRAILING_FIXED_ROW_LABEL_OFFSET(mw),
			FIXED_COLUMN_LABEL_OFFSET(mw) - 1,
			TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
			TRAILING_FIXED_ROW_HEIGHT(mw) - 1);

		if (OVERLAP(*expose, rect))
		    redrawTrailingFixedRows = True;
	    }

	    /*
	     * Get starting and ending rows/columns. Never take into
	     * account the scrolling origins for the rows; for columns
	     * only if we are fixed in that dimension.
	     */
	    startCol = xbaeXtoCol(mw, intersect.x1 +
			      (mw->matrix.fixed_columns
			       ? 0
			       : HORIZ_ORIGIN(mw)));
	    endCol = xbaeXtoCol(mw, intersect.x2 +
			    (mw->matrix.fixed_columns
			     ? 0
			     : HORIZ_ORIGIN(mw)));

	    startRow = redrawFixedRows ? 0 : YtoRow(mw, intersect.y1) + VERT_ORIGIN(mw);
	    if (redrawTrailingFixedRows)
	    {
		skipRow = YtoRow(mw, intersect.y2) + VERT_ORIGIN(mw) -
		    mw->matrix.fixed_rows + 1;
		endRow = mw->matrix.rows - 1;
	    }
	    else
		endRow = YtoRow(mw, intersect.y2) + VERT_ORIGIN(mw);

	    if (setMask)
		xbaeSetClipMask(mw, CLIP_FIXED_COLUMNS);

	    /*
	     * Redraw each cell that was intersected
	     */
	    for (i = startRow; i <= endRow; i++)
		for (j = startCol; j <= endCol; j++)
		{
		    /*
		     * If we had to redraw cells located in both fixed rows
		     * and columns, when we are done redrawing those cells,
		     * we need to skip to the correct non-fixed row to draw,
		     * or alternatively, jump to the trailing fixed row
		     * to draw.
		     */
		    if (redrawFixedRows && (i == mw->matrix.fixed_rows))
			i += VERT_ORIGIN(mw);

		    if (redrawTrailingFixedRows && (i == skipRow) &&
			(endRow > skipRow))
			i = TRAILING_VERT_ORIGIN(mw);

		    xbaeDrawCell(mw, i, j);
		}

	    if (setMask)
		xbaeSetClipMask(mw, CLIP_NONE);
	}
    }

    /*
     * Handle cells in trailing fixed columns
     */
    if (mw->matrix.trailing_fixed_columns)
    {
	XBAERectangle rect;

	/*
	 * Get the Rectangle enclosing the cells in trailing fixed columns
	 */
	SETRECT(rect,
		TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw), ROW_LABEL_OFFSET(mw),
		TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) +
		TRAILING_FIXED_COLUMN_WIDTH(mw) - 1,
		TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
		TRAILING_FIXED_ROW_HEIGHT(mw) - 1);

	/*
	 * If the expose Rectangle overlaps, then some cells must be redrawn
	 */
	if (OVERLAP(*expose, rect))
	{
	    XBAERectangle intersect;
	    int startCol, endCol, startRow, endRow, skipRow = -1, i, j;
	    Boolean redrawFixedRows, redrawTrailingFixedRows, setMask;

	    /*
	     * Intersect the fixed-cells Rectangle with the expose
	     * Rectangle along the X and Y axis.  The resulting Rectangle will
	     * be in 'rect's coordinate system.
	     */
	    INTERSECT(rect, *expose, intersect);

	    /*
	     * If we have any fixed rows, we might need to redraw the cells
	     * located in the intersection of the fixed rows and columns.
	     * These cells may force us to be different than our current
	     * VERT_ORIGIN.
	     */
	    setMask = redrawFixedRows = redrawTrailingFixedRows = False;
	    if (mw->matrix.fixed_rows)
	    {
		setMask = True;

		SETRECT(rect, TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw),
			ROW_LABEL_OFFSET(mw),
			TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) +
			TRAILING_FIXED_COLUMN_WIDTH(mw) - 1,
			FIXED_ROW_LABEL_OFFSET(mw) - 1);

		if (OVERLAP(*expose, rect))
		    redrawFixedRows = True;
	    }

	    if (mw->matrix.trailing_fixed_rows)
	    {
		setMask = True;

		SETRECT(rect, TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw),
			TRAILING_FIXED_ROW_LABEL_OFFSET(mw),
			TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) +
			TRAILING_FIXED_COLUMN_WIDTH(mw) - 1,
			TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
			TRAILING_FIXED_ROW_HEIGHT(mw) - 1);

		if (OVERLAP(*expose, rect))
		    redrawTrailingFixedRows = True;
	    }

	    /*
	     * Get starting and ending rows/columns. Never take into
	     * account the scrolling origins for the rows; for columns
	     * only if we are fixed in that dimension.
	     */
	    startCol = xbaeXtoCol(mw, intersect.x1) +
		TRAILING_HORIZ_ORIGIN(mw);
	    endCol = xbaeXtoCol(mw, intersect.x2) + TRAILING_HORIZ_ORIGIN(mw);

	    startRow = redrawFixedRows ? 0 : YtoRow(mw, intersect.y1) +
		VERT_ORIGIN(mw);

	    if (redrawTrailingFixedRows)
	    {
		skipRow = YtoRow(mw, intersect.y2) + VERT_ORIGIN(mw) -
		    mw->matrix.fixed_rows + 1;
		endRow = mw->matrix.rows - 1;
	    }
	    else
		endRow = YtoRow(mw, intersect.y2) + VERT_ORIGIN(mw);

	    if (setMask)
		xbaeSetClipMask(mw, CLIP_FIXED_COLUMNS);

	    /*
	     * Redraw each cell that was intersected
	     */
	    for (i = startRow; i <= endRow; i++)
		for (j = startCol; j <= endCol; j++)
		{
		    /*
		     * If we had to redraw cells located in both fixed rows
		     * and columns, when we are done redrawing those cells,
		     * we need to skip to the correct non-fixed row to draw
		     */		    
		    if (redrawFixedRows && (i == mw->matrix.fixed_rows))
			i += VERT_ORIGIN(mw);

		    if (redrawTrailingFixedRows && (i == skipRow) &&
			(endRow > skipRow))
			i = TRAILING_VERT_ORIGIN(mw);
		    
		    xbaeDrawCell(mw, i, j);
		}

	    if (setMask)
		xbaeSetClipMask(mw, CLIP_NONE);
	}
    }

    /*
     * Draw a shadow just inside row/column labels and around outer edge
     * of clip widget.	We can't use height of clip widget because it is
     * truncated to nearest row.  We use cell_visible_height instead.
     */
    if (mw->manager.shadow_thickness)
	DRAW_SHADOW(XtDisplay(mw), XtWindow(mw),
		    mw->manager.bottom_shadow_GC,
		    mw->manager.top_shadow_GC,
		    mw->manager.shadow_thickness,
		    ROW_LABEL_WIDTH(mw),
		    COLUMN_LABEL_HEIGHT(mw),
		    ClipChild(mw)->core.width + FIXED_COLUMN_WIDTH(mw) +
		    TRAILING_FIXED_COLUMN_WIDTH(mw) +
		    2 * mw->manager.shadow_thickness,
		    mw->matrix.cell_visible_height + FIXED_ROW_HEIGHT(mw) +
		    TRAILING_FIXED_ROW_HEIGHT(mw) +
		    2 * mw->manager.shadow_thickness,
		    mw->matrix.shadow_type);
}


void
xbaeDrawRowShadow(mw, row, redraw_reason)
XbaeMatrixWidget mw;
int row;
unsigned int redraw_reason;
{
    int x, y;
    Dimension width, height;
    unsigned int clip_reason;
    Window win = XtWindow(mw);
    Display *display = XtDisplay(mw);
    Boolean set_mask = False;

    /*
     * Get the width and height for drawing the shadow around each
     * row. The width used is a bit long to prevent any overlapping
     * at the edges if there are any (trailing) fixed columns, and
     * the actual drawing position is offset the same amount for the
     * the same reason.
     */
    width = CELL_TOTAL_WIDTH(mw) +
	(mw->matrix.fixed_columns * mw->matrix.cell_shadow_thickness) +
	(mw->matrix.trailing_fixed_columns * mw->matrix.cell_shadow_thickness);
    height = ROW_HEIGHT(mw);

    /*
     * Get the location at which to draw our shadow
     */
    xbaeRowColToXY(mw, row, mw->matrix.fixed_columns, &x, &y);
    x -= (mw->matrix.fixed_columns * mw->matrix.cell_shadow_thickness);

    /*
     * Draw the shadow around the portion of the row in
     * the non-fixed columns
     */
    if ((row < mw->matrix.fixed_rows) || (row >= TRAILING_VERT_ORIGIN(mw)))
    {
	if (row > mw->matrix.fixed_rows)
	{
	    clip_reason = CLIP_TRAILING_FIXED_ROWS;
	    xbaeSetClipMask(mw, clip_reason);
	    set_mask = True;
	}
	else
	    clip_reason = CLIP_NONE;
	
	DRAW_SHADOW(display, win,
		    mw->matrix.cell_top_shadow_clip_gc,
		    mw->matrix.cell_bottom_shadow_clip_gc,
		    mw->matrix.cell_shadow_thickness, x, y,
		    width, height, mw->matrix.cell_shadow_type);
    }
    else
    {
	clip_reason = CLIP_BETWEEN_FIXED_ROWS;
	DRAW_SHADOW(display, XtWindow(ClipChild(mw)),
		    mw->manager.top_shadow_GC,
		    mw->manager.bottom_shadow_GC,
		    mw->matrix.cell_shadow_thickness, x, y,
		    width, height, mw->matrix.cell_shadow_type);

	/*
	 * In this case, 'y' is relative to the clip window origin
	 * because this is a nonfixed row. So we need to make it
	 * relative to the matrix window origin for drawing the
	 * shadows in any (trailing) fixed columns
	 */
	y += FIXED_ROW_LABEL_OFFSET(mw);
    }

    /*
     * If only redrawing the portion of the shadow in the
     * non-fixed columns, then leave
     */
    if (GRID_REDRAW_SCROLL_HORIZ & redraw_reason)
    {
	/*
	 * Reset clipping mask if necessary
	 */
	if (set_mask)
	    xbaeSetClipMask(mw, CLIP_NONE);

	return;
    }

    /*
     * Draw the shadow around the portion of the row in
     * the fixed columns
     */
    if (mw->matrix.fixed_columns)
    {
	xbaeSetClipMask(mw, CLIP_FIXED_COLUMNS | clip_reason);
	set_mask = True;

	/*
	 * Adjust 'x' such that the leading edge of the
	 * shadow is always drawn. Nicer visually.
	 */
	x = COLUMN_LABEL_OFFSET(mw);
	DRAW_SHADOW(display, win,
		    mw->matrix.cell_top_shadow_clip_gc,
		    mw->matrix.cell_bottom_shadow_clip_gc,
		    mw->matrix.cell_shadow_thickness, x, y,
		    FIXED_COLUMN_WIDTH(mw) +
		    2*mw->matrix.cell_shadow_thickness,
		    height, mw->matrix.cell_shadow_type);
    }
    
    /*
     * Draw the shadow around the portion of the row in
     * the trailing fixed columns
     */
    if (mw->matrix.trailing_fixed_columns)
    {
	xbaeSetClipMask(mw, CLIP_TRAILING_FIXED_COLUMNS | clip_reason);
	set_mask = True;

	/*
	 * Adjust 'x' such that the trailing edge of the
	 * shadow is always drawn. Nicer visually.
	 */
	x = TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) -
	    2*mw->matrix.cell_shadow_thickness;
	DRAW_SHADOW(display, win,
		    mw->matrix.cell_top_shadow_clip_gc,
		    mw->matrix.cell_bottom_shadow_clip_gc,
		    mw->matrix.cell_shadow_thickness,
		    x, y, TRAILING_FIXED_COLUMN_WIDTH(mw) +
		    2*mw->matrix.cell_shadow_thickness,
		    height, mw->matrix.cell_shadow_type);
    }

    /*
     * Reset clipping mask if necessary
     */
    if (set_mask)
	xbaeSetClipMask(mw, CLIP_NONE);
}


void
xbaeDrawColumnShadow(mw, column, redraw_reason)
XbaeMatrixWidget mw;
int column;
unsigned int redraw_reason;
{
    int x, y;
    Dimension width, height;
    unsigned int clip_reason;
    Window win = XtWindow(mw);
    Display *display = XtDisplay(mw);
    Boolean set_mask = False;

    /*
     * Get the width and height for drawing the shadow around each
     * column. The height used is a bit long to prevent any overlapping
     * at the edges if there are any (trailing) fixed rows, and
     * the actual drawing position is offset the same amount for the
     * the same reason.
     */
    width = COLUMN_WIDTH(mw, column);
    height = CELL_TOTAL_HEIGHT(mw) +
	(mw->matrix.fixed_rows * mw->matrix.cell_shadow_thickness) +
	(mw->matrix.trailing_fixed_rows * mw->matrix.cell_shadow_thickness);
    
    /*
     * Get the location at which to draw our shadow
     */
    xbaeRowColToXY(mw, mw->matrix.fixed_rows, column, &x, &y);
    y -= (mw->matrix.fixed_rows * mw->matrix.cell_shadow_thickness);

    /*
     * Draw the shadow around the portion of the column in
     * the non-fixed rows
     */
    if ((column < mw->matrix.fixed_columns) || (column >= TRAILING_HORIZ_ORIGIN(mw)))
    {
	Dimension column_height, visible_height;

	/*
	 * If only redrawing the portion of the shadow in the
	 * non-fixed rows, then leave
	 */
	if (GRID_REDRAW_SCROLL_HORIZ & redraw_reason)
	    return;

	/*
	 * In this case, we've got to draw the entire shadow at once
	 * and don't get the benefit of the clip window enabling
	 * clipping to occur :(. So, we have to do a bit of extra work
	 * to get the proper visual to occur.
	 */
	if (column > mw->matrix.fixed_columns)
	    clip_reason = CLIP_TRAILING_FIXED_COLUMNS;
	else
	    clip_reason = CLIP_FIXED_COLUMNS;
	xbaeSetClipMask(mw, clip_reason | CLIP_VISIBLE_HEIGHT);
	set_mask = True;

	visible_height = ClipChild(mw)->core.height +
	    FIXED_ROW_HEIGHT(mw) + TRAILING_FIXED_ROW_HEIGHT(mw);
	
	if ((mw->matrix.fixed_rows && mw->matrix.trailing_fixed_rows) ||
	    ((! mw->matrix.fixed_rows) && mw->matrix.trailing_fixed_rows &&
	     (0 == VERT_ORIGIN(mw))) ||
	    (mw->matrix.fixed_rows && (! mw->matrix.trailing_fixed_rows) &&
	     ((mw->matrix.rows - (visible_height/ROW_HEIGHT(mw))) == VERT_ORIGIN(mw))))
	{
	    /*
	     * If we've got both fixed and trailing fixed rows,
	     * or we've got only trailing fixed rows and the top
	     * row is the first row, or we've got only fixed rows
	     * and the bottom row is the last row, then both the
	     * top and bottom edges need to be displayed
	     */
	    column_height = visible_height;
	    y = ROW_LABEL_OFFSET(mw);
	}
	else
	{
	    column_height = height + FIXED_ROW_HEIGHT(mw) +
		TRAILING_FIXED_ROW_HEIGHT(mw) -
		(mw->matrix.fixed_rows * mw->matrix.cell_shadow_thickness);

	    /*
	     * If we have fixed rows, we need to always display the top edge.
	     */
	    if (mw->matrix.fixed_rows)
		y = ROW_LABEL_OFFSET(mw);
	    else
		y -= FIXED_ROW_HEIGHT(mw) -
		    (mw->matrix.fixed_rows * mw->matrix.cell_shadow_thickness);
	}

	DRAW_SHADOW(display, win,
		    mw->matrix.cell_top_shadow_clip_gc,
		    mw->matrix.cell_bottom_shadow_clip_gc,
		    mw->matrix.cell_shadow_thickness, x, y,
		    width, column_height,
		    mw->matrix.cell_shadow_type);
    }
    else
    {
	DRAW_SHADOW(display, XtWindow(ClipChild(mw)),
		    mw->manager.top_shadow_GC,
		    mw->manager.bottom_shadow_GC,
		    mw->matrix.cell_shadow_thickness, x, y,
		    width, height, mw->matrix.cell_shadow_type);

	/*
	 * In this case, 'x' is relative to the clip window origin
	 * because this is a nonfixed row. So we need to make it
	 * relative to the matrix window origin for drawing the
	 * shadows in any (trailing) fixed columns
	 */
	x += FIXED_COLUMN_LABEL_OFFSET(mw);
    }

    /*
     * Draw the shadow around the portion of the column in
     * the fixed rows
     */
    if (mw->matrix.fixed_rows)
    {
	/*
	 * Adjust 'y' such that the leading edge of the
	 * shadow is always drawn. Nicer visually.
	 */
	y = ROW_LABEL_OFFSET(mw);
	DRAW_SHADOW(display, win,
		    mw->matrix.cell_top_shadow_clip_gc,
		    mw->matrix.cell_bottom_shadow_clip_gc,
		    mw->matrix.cell_shadow_thickness, x, y,
		    width, height, mw->matrix.cell_shadow_type);
    }

    /*
     * Draw the shadow around the portion of the column in
     * the trailing fixed rows
     */
    if (mw->matrix.trailing_fixed_rows)
    {
	xbaeSetClipMask(mw, CLIP_TRAILING_FIXED_ROWS);
	set_mask = True;

	/*
	 * Adjust 'y' such that the trailing edge of the
	 * shadow is always drawn. Nicer visually.
	 */
	y = TRAILING_FIXED_ROW_LABEL_OFFSET(mw) -
	    2*mw->matrix.cell_shadow_thickness;
	DRAW_SHADOW(display, win,
		    mw->matrix.cell_top_shadow_clip_gc,
		    mw->matrix.cell_bottom_shadow_clip_gc,
		    mw->matrix.cell_shadow_thickness,
		    x, y, width,
		    TRAILING_FIXED_ROW_HEIGHT(mw) +
		    2*mw->matrix.cell_shadow_thickness,
		    mw->matrix.cell_shadow_type);
    }

    /*
     * Reset clipping mask if necessary
     */
    if (set_mask)
	xbaeSetClipMask(mw, CLIP_NONE);
}


static void
DrawRowShadows(mw, redraw_reason)
XbaeMatrixWidget mw;
unsigned int redraw_reason;
{
    int m, end;

    /*
     * Draw the shadow around the non-fixed rows.
     */
    xbaeGetVisibleRows(mw, &m, &end);
    for (; m < end; m++)
	xbaeDrawRowShadow(mw, m, redraw_reason);

    /*
     * If we're scrolling vertically, don't need to
     * redraw any fixed rows, so leave.
     */
    if (GRID_REDRAW_SCROLL_VERT & redraw_reason)
	return;

    /*
     * Draw the shadow around the fixed rows.
     */
    if (mw->matrix.fixed_rows)
	for (m = 0; m < mw->matrix.fixed_rows; m++)
	    xbaeDrawRowShadow(mw, m, redraw_reason);

    /*
     * Draw the shadow around the trailing fixed rows.
     */
    if (mw->matrix.trailing_fixed_rows)
	for (m = TRAILING_VERT_ORIGIN(mw); m < mw->matrix.rows; m++)
	    xbaeDrawRowShadow(mw, m, redraw_reason);
}



static void
DrawColumnShadows(mw, redraw_reason)
XbaeMatrixWidget mw;
unsigned int redraw_reason;
{
    int m, end;

    /*
     * Draw the shadow around the non-fixed columns.
     */
    xbaeGetVisibleColumns(mw, &m, &end);
    for (; m <= end; m++)
	xbaeDrawColumnShadow(mw, m, redraw_reason);

    /*
     * If we're scrolling horizontally, don't need to
     * redraw any fixed columns, so leave.
     */
    if (GRID_REDRAW_SCROLL_HORIZ & redraw_reason)
	return;
    
    /*
     * Draw the shadow around the fixed columns.
     */
    if (mw->matrix.fixed_columns)
	for (m = 0; m < mw->matrix.fixed_columns; m++)
	    xbaeDrawColumnShadow(mw, m, redraw_reason);

    /*
     * Draw the shadow around the trailing fixed columns.
     */
    if (mw->matrix.trailing_fixed_columns)
	for (m = TRAILING_HORIZ_ORIGIN(mw); m < mw->matrix.columns; m++)
	    xbaeDrawColumnShadow(mw, m, redraw_reason);
}


void
xbaeDrawGridShadows(mw, redraw_reason)
XbaeMatrixWidget mw;
unsigned int redraw_reason;
{
    if (mw->matrix.cell_shadow_thickness)
    {
	if (XmGRID_ROW_SHADOW == mw->matrix.grid_type)
	    DrawRowShadows(mw, redraw_reason);
	else if (XmGRID_COLUMN_SHADOW == mw->matrix.grid_type)
	    DrawColumnShadows(mw, redraw_reason);
    }
}

