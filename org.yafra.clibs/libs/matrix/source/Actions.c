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
#include <Xm/XmP.h>
#include <Xbae/MatrixP.h>
#include <Xbae/Actions.h>

static int DoubleClick P(( XbaeMatrixWidget mw, XEvent *event, int row,
			   int column ));


/* ARGSUSED */
void
xbaeDefaultActionACT(w, event, params, nparams)
Widget w;
XEvent *event;
String *params;
Cardinal *nparams;
{
    XbaeMatrixWidget mw;
    int x, y;
    int row, column;
    CellType cell;

    /*
     * Get Matrix widget and make sure it is a Matrix subclass.
     * w could be Matrix, or the Clip or textField children of Matrix
     */
    if (XtIsSubclass(w, xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) w;
    else if (XtIsSubclass(XtParent(w), xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) XtParent(w);
    else {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"defaultActionACT", "badWidget", "XbaeMatrix",
			"XbaeMatrix: Bad widget passed to DefaultAction action",
			NULL, 0);
	return;
    }

    if( !mw->matrix.default_action_callback )
	return;

    if (!xbaeEventToXY(mw, event, &x, &y, &cell))
	return;

    if (!xbaeXYToRowCol(mw, &x, &y, &row, &column, cell))
	return;

    if( DoubleClick( mw, event, row, column ) )
    {
	XbaeMatrixDefaultActionCallbackStruct call_data;

	call_data.reason = XbaeDefaultActionReason;
	call_data.row = row;
	call_data.column = column;
	call_data.event = event;

	XtCallCallbackList((Widget)mw, mw->matrix.default_action_callback,
			   (XtPointer) &call_data);
      
    }
}


/*
 * Action to edit a non-fixed cell.
 */
/* ARGSUSED */
void
xbaeEditCellACT(w, event, params, nparams)
Widget w;
XEvent *event;
String *params;
Cardinal *nparams;
{
    XbaeMatrixWidget mw;
    int row, column;
    XrmQuark q;
    static XrmQuark QPointer, QLeft, QRight, QUp, QDown;
    static Boolean haveQuarks = False;

    /*
     * Get static quarks for the parms we understand
     */
    if (!haveQuarks)
    {
	QPointer = XrmPermStringToQuark("Pointer");
	QLeft = XrmPermStringToQuark("Left");
	QRight = XrmPermStringToQuark("Right");
	QUp = XrmPermStringToQuark("Up");
	QDown = XrmPermStringToQuark("Down");
	haveQuarks = True;
    }

    /*
     * Get Matrix widget and make sure it is a Matrix subclass.
     * w could be Matrix, or the Clip or textField children of Matrix
     */
    if (XtIsSubclass(w, xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) w;
    else if (XtIsSubclass(XtParent(w), xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) XtParent(w);
    else
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"editCellACT", "badWidget", "XbaeMatrix",
			"XbaeMatrix: Bad widget passed to EditCell action",
			NULL, 0);
	return;
    }

    /*
     * Make sure we have a single parm
     */
    if (*nparams != 1)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"editCellACT", "badParms", "XbaeMatrix",
			"XbaeMatrix: Wrong number of parameters passed to EditCell action, needs 1",
			NULL, 0);
	return;
    }

    /*
     * Initialize row/column to the current position
     */
    row = mw->matrix.current_row;
    column = mw->matrix.current_column;

    /*
     * Quarkify the string param
     */
    q = XrmStringToQuark(params[0]);

    /*
     * If we aren't currently editing, then the only kind of traversal that
     * makes sense is pointer.
     */
    if (!XtIsManaged(TextChild(mw)) && q != QPointer)
	return;

    if (q == QPointer)
    {
	int x, y;

	/*
	 * Get the x,y point coordinate relative to the Clip window.
	 * Return if this event did not occur in the Clip subwindow
	 * (since we can only edit non-fixed cells).
	 */
	switch (event->type)
	{
	case ButtonPress:
	case ButtonRelease:
	    x = event->xbutton.x;
	    y = event->xbutton.y;
	    break;
	case KeyPress:
	case KeyRelease:
	    x = event->xkey.x;
	    y = event->xkey.y;
	    break;
	case MotionNotify:
	    x = event->xmotion.x;
	    y = event->xmotion.y;
	    break;
	default:
	    return;
	}

	if (event->xbutton.subwindow == XtWindow(ClipChild(mw)))
	{
	    x -= FIXED_COLUMN_LABEL_OFFSET(mw);
	    y -= FIXED_ROW_LABEL_OFFSET(mw);
	}
	else if (event->xbutton.window != XtWindow(ClipChild(mw)))
	    return;

	/*
	 * Convert the point to a row,column. If it does not pick a valid
	 * cell, then return.
	 */
	if (!xbaeXYToRowCol(mw, &x, &y, &row, &column, NonFixedCell))
	    return;
    }
    else if (q == QRight)
    {
	/*
	 * If we are in the lower right corner, stay there.
	 * Otherwise move over a column, if we move off the right edge,
	 * then move down a row and back to the first non-fixed column.
	 */
	if (mw->matrix.current_row != TRAILING_VERT_ORIGIN(mw) - 1 ||
	    mw->matrix.current_column != TRAILING_HORIZ_ORIGIN(mw) - 1)
	{

	    column++;

	    if (column >= TRAILING_HORIZ_ORIGIN(mw))
	    {
		column = mw->matrix.fixed_columns;
		row++;
	    }
	}
    }
    else if (q == QLeft)
    {
	/*
	 * If we are in the upper left corner, stay there.
	 * Otherwise move back a column, if we move before the fixed columns,
	 * then move up a row and over to the last column.
	 */
	if (mw->matrix.current_row != mw->matrix.fixed_rows ||
	    mw->matrix.current_column !=
	    mw->matrix.fixed_columns)
	{

	    column--;

	    if (column < (int) mw->matrix.fixed_columns)
	    {
		column = TRAILING_HORIZ_ORIGIN(mw) - 1;
		row--;
	    }
	}
    }
    else if (q == QDown)
    {
	row++;

	if (row >= TRAILING_VERT_ORIGIN(mw))
	    row = mw->matrix.fixed_rows;
    }
    else if (q == QUp)
    {
	row--;

	if (row < (int) mw->matrix.fixed_rows)
	    row = TRAILING_VERT_ORIGIN(mw) - 1;
    }

    /*
     * Call the traverseCellCallback to allow the application to
     * perform custom traversal.
     */
    if (mw->matrix.traverse_cell_callback)
    {
	XbaeMatrixTraverseCellCallbackStruct call_data;

	call_data.reason = XbaeTraverseCellReason;
	call_data.row = mw->matrix.current_row;
	call_data.column = mw->matrix.current_column;
	call_data.next_row = row;
	call_data.next_column = column;
	call_data.fixed_rows = mw->matrix.fixed_rows;
	call_data.fixed_columns = mw->matrix.fixed_columns;
	call_data.trailing_fixed_rows = mw->matrix.trailing_fixed_rows;
	call_data.trailing_fixed_columns = mw->matrix.trailing_fixed_columns;
	call_data.num_rows = mw->matrix.rows;
	call_data.num_columns = mw->matrix.columns;
	call_data.param = params[0];
	call_data.qparam = q;

	XtCallCallbackList((Widget) mw, mw->matrix.traverse_cell_callback,
			   (XtPointer) & call_data);

	row = call_data.next_row;
	column = call_data.next_column;
    }

    /*
     * Attempt to edit the new cell using the edit_cell method.
     * If we are editing a cell based on pointer position, we always
     * call edit_cell.	Otherwise, we must be editing a new cell to
     * call edit_cell.
     */
    if (q == QPointer || (row != mw->matrix.current_row ||
			  column != mw->matrix.current_column))
	(*((XbaeMatrixWidgetClass) XtClass(mw))->matrix_class.edit_cell)
	    (mw, row, column);

    /*
     * Traverse to the textField
     */
    ( void )XmProcessTraversal(TextChild(mw), XmTRAVERSE_CURRENT);
}

/*
 * Action to unmap the textField and discard any edits made
 */
/* ARGSUSED */
void
xbaeCancelEditACT(w, event, params, nparams)
Widget w;
XEvent *event;
String *params;
Cardinal *nparams;
{
    XbaeMatrixWidget mw;
    Boolean unmap;

    /*
     * Get Matrix widget and make sure it is a Matrix subclass.
     * w could be Matrix, or the Clip or textField children of Matrix
     */
    if (XtIsSubclass(w, xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) w;
    else if (XtIsSubclass(XtParent(w), xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) XtParent(w);
    else
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"cancelEditACT", "badWidget", "XbaeMatrix",
			"XbaeMatrix: Bad widget passed to CancelEdit action",
			NULL, 0);
	return;
    }

    /*
     * Make sure we have a single param
     */
    if (*nparams != 1)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"cancelEditACT", "badParms", "XbaeMatrix",
			"XbaeMatrix: Wrong number of parameters passed to CancelEdit action, needs 1",
			NULL, 0);
	return;
    }

    /*
     * Validate our param
     */
    if (!strcmp(params[0], "True"))
	unmap = True;
    else if (!strcmp(params[0], "False"))
	unmap = False;
    else
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"cancelEditACT", "badParm", "XbaeMatrix",
			"XbaeMatrix: Invalid parameter passed to CancelEdit action, must be True or False",
			NULL, 0);
	return;
    }
    /*
     * Call the cancel_edit method
     */
    (*((XbaeMatrixWidgetClass) XtClass(mw))->matrix_class.cancel_edit)
	(mw, unmap);
}

/*
 * Action save any edits made and unmap the textField if params[0] is True
 */
/* ARGSUSED */
void
xbaeCommitEditACT(w, event, params, nparams)
Widget w;
XEvent *event;
String *params;
Cardinal *nparams;
{
    XbaeMatrixWidget mw;
    Boolean unmap;

    /*
     * Get Matrix widget and make sure it is a Matrix subclass.
     * w could be Matrix, or the Clip or textField children of Matrix
     */
    if (XtIsSubclass(w, xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) w;
    else if (XtIsSubclass(XtParent(w), xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) XtParent(w);
    else
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"commitEditACT", "badWidget", "XbaeMatrix",
			"XbaeMatrix: Bad widget passed to CommitEdit action",
			NULL, 0);
	return;
    }

    /*
     * Make sure we have a single param
     */
    if (*nparams != 1)
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"commitEditACT", "badParms", "XbaeMatrix",
			"XbaeMatrix: Wrong number of parameters passed to CommitEdit action, needs 1",
			NULL, 0);
	return;
    }

    /*
     * Validate our param
     */
    if (!strcmp(params[0], "True"))
	unmap = True;
    else if (!strcmp(params[0], "False"))
	unmap = False;
    else
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"commitEditACT", "badParm", "XbaeMatrix",
			"XbaeMatrix: Invalid parameter passed to CommitEdit action, must be True or False",
			NULL, 0);
	return;
    }

    (void) (*((XbaeMatrixWidgetClass) XtClass(mw))->matrix_class.commit_edit)
	(mw, unmap);
}

/*
 * Convert the coordinates in an event to be relative to the Clip
 * window or the Matrix window.  Set the cell to indicate which one.
 * Used by some actions.
 */
/* ARGSUSED */
Boolean
xbaeEventToXY(mw, event, x, y, cell)
XbaeMatrixWidget mw;
XEvent *event;
int *x, *y;
CellType *cell;
{
    switch (event->type)
    {
    case ButtonPress:
    case ButtonRelease:
	*x = event->xbutton.x;
	*y = event->xbutton.y;
	break;
    case KeyPress:
    case KeyRelease:
	*x = event->xkey.x;
	*y = event->xkey.y;
	break;
    case MotionNotify:
	*x = event->xmotion.x;
	*y = event->xmotion.y;
	break;
    default:
	return False;
    }

    if (event->xbutton.subwindow == XtWindow(ClipChild(mw)))
    {
	*cell = NonFixedCell;
	*x -= FIXED_COLUMN_LABEL_OFFSET(mw);
	*y -= FIXED_ROW_LABEL_OFFSET(mw);
    }
    else if (event->xbutton.window == XtWindow(mw))
	*cell = FixedCell;
    else if (event->xbutton.window == XtWindow(ClipChild(mw)))
	*cell = NonFixedCell;
    else if (event->xbutton.window == XtWindow(TextChild(mw)))
    {
	Position tx, ty;

	*cell = NonFixedCell;
	XtVaGetValues(TextChild(mw),
		      XmNx, &tx,
		      XmNy, &ty,
		      NULL);
	*x += tx;
	*y += ty;
    }
    else
	return False;

    return True;
}

static int
DoubleClick(mw, event, row, column)
XbaeMatrixWidget mw;
XEvent *event;
int row;
int column;
{
    /* A double click in this instance is two clicks in the
       same cell in a time period < double_click_interval */
    Time current_time;
    unsigned long delta;
    static int ret = 0;

    if (event->type == ButtonRelease)
    {
	/* If the button is released, store the current location and time -
	   next time through, if it's a button press event, we check for
	   double click */
	mw->matrix.last_row = row;
	mw->matrix.last_column = column;
	if( ret )		/* just had a double click */
	    mw->matrix.last_click_time = ( Time )0;
	else
	    mw->matrix.last_click_time = event->xbutton.time;
	ret = 0;
	return ret;
    }

    current_time = event->xbutton.time;
    delta = current_time - mw->matrix.last_click_time;

    if (row == mw->matrix.last_row && column == mw->matrix.last_column &&
	delta < ( unsigned long )mw->matrix.double_click_interval )
	ret = 1;
    else
	ret = 0;

    return ret;
}

/*ARGSUSED*/
void
xbaeHandleClick(w, mw, event, cont)
Widget w;
XbaeMatrixWidget mw;
XEvent *event;
Boolean *cont;
{
    /* if we have a double click and a callback - break out! */
    if (event->type != ButtonPress && event->type != ButtonRelease )
	return;
    if (mw->matrix.default_action_callback &&
	DoubleClick(mw, event, mw->matrix.current_row,
		    mw->matrix.current_column))
    {
	XbaeMatrixDefaultActionCallbackStruct call_data;

	call_data.reason = XbaeDefaultActionReason;
	call_data.row = mw->matrix.current_row;
	call_data.column = mw->matrix.current_column;
	call_data.event = event;

	XtCallCallbackList((Widget)mw, mw->matrix.default_action_callback,
			   (XtPointer) &call_data);
      
      
    }
}

/* ARGSUSED */
void
xbaeSelectCellACT(w, event, params, nparams)
Widget w;
XEvent *event;
String *params;
Cardinal *nparams;
{
    XbaeMatrixWidget mw;
    int x, y;
    int row, column;
    CellType cell;
    XbaeMatrixSelectCellCallbackStruct call_data;

    /*
     * Get Matrix widget and make sure it is a Matrix subclass.
     * w could be Matrix, or the Clip or textField children of Matrix
     */
    if (XtIsSubclass(w, xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) w;
    else if (XtIsSubclass(XtParent(w), xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) XtParent(w);
    else
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"xbaeSelectCellACT", "badWidget", "XbaeMatrix",
			"XbaeMatrix: Bad widget passed to SelectCell action",
			NULL, 0);
	return;
    }

    /*
     * If we don't have a selectCellCallback, then return now
     */
    if (!mw->matrix.select_cell_callback)
	return;

    if (!xbaeEventToXY(mw, event, &x, &y, &cell))
	return;

    /*
     * Convert the point to a row,column. If it does not pick a valid
     * cell, then return.
     */
    if (!xbaeXYToRowCol(mw, &x, &y, &row, &column, cell))
	return;

    /*
     * Call our select_cell callbacks
     */
    call_data.reason = XbaeSelectCellReason;
    call_data.row = row;
    call_data.column = column;
    call_data.selected_cells = mw->matrix.selected_cells;
    call_data.cells = mw->matrix.cells;
    call_data.num_params = *nparams;
    call_data.params = params;
    call_data.event = event;

    XtCallCallbackList((Widget) mw, mw->matrix.select_cell_callback,
		       (XtPointer) & call_data);
}


/* ARGSUSED */
void
xbaeTraverseNextACT(w, event, params, nparams)
Widget w;
XEvent *event;
String *params;
Cardinal *nparams;
{
    XbaeMatrixWidget mw;

    /*
     * Get Matrix widget and make sure it is a Matrix subclass.
     * w should be the textField widget.
     */
    if (XtIsSubclass(XtParent(w), xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) XtParent(w);
    else
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"traverseNextACT", "badWidget", "XbaeMatrix",
			"XbaeMatrix: Bad widget passed to TraverseNext action",
			NULL, 0);
	return;
    }

    /*
     * Set the traversing direction flag.  XmProcessTraversal may traverse
     * to the Clip widget. If it does, then we will see this flag in
     * the Clip focusCallback, TraverseInCB, and we will continue to traverse
     * on out of the mw.  yuck!
     */
    mw->matrix.traversing = XmTRAVERSE_NEXT_TAB_GROUP;
    ( void )XmProcessTraversal(TextChild(mw), XmTRAVERSE_NEXT_TAB_GROUP);
    mw->matrix.traversing = NOT_TRAVERSING;
}

/* ARGSUSED */
void
xbaeTraversePrevACT(w, event, params, nparams)
Widget w;
XEvent *event;
String *params;
Cardinal *nparams;
{
    XbaeMatrixWidget mw;

    /*
     * Get Matrix widget and make sure it is a Matrix subclass.
     * w should be the textField widget.
     */
    if (XtIsSubclass(XtParent(w), xbaeMatrixWidgetClass))
	mw = (XbaeMatrixWidget) XtParent(w);
    else
    {
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			"traversePrevACT", "badWidget", "XbaeMatrix",
			"XbaeMatrix: Bad widget passed to TraversePrev action",
			NULL, 0);
	return;
    }

    /*
     * Set the traversing direction flag.  XmProcessTraversal may traverse
     * to the Clip widget. If it does, then we will see this flag in
     * the Clip focusCallback, TraverseInCB, and we will continue to traverse
     * on out of the mw.  yuck!
     */
    mw->matrix.traversing = ( int )XmTRAVERSE_PREV_TAB_GROUP;
    ( void )XmProcessTraversal(TextChild(mw), XmTRAVERSE_PREV_TAB_GROUP);
    mw->matrix.traversing = NOT_TRAVERSING;
}

/*
 * Convert an x/y pixel position to the row/column cell position it picks.
 * 'cell' specifies whether the x/y coord is relative to the fixed cells
 * window or the non-fixed cells window.
 * The coords x,y are adjusted so they are relative to the origin of the
 * picked cell.
 * If we are "out of bounds" on the ``low'' side, go ahead and return False
 * to show an error, but also set the row/column to -1 to indicate this could
 * be a row/column header.  This is currently undocumented behaviour, but
 * may be useful nevertheless.
 */
Boolean
xbaeXYToRowCol(mw, x, y, row, column, cell)
XbaeMatrixWidget mw;
int *x, *y;
int *row, *column;
CellType cell;
{
    XBAERectangle rect;
    Boolean inBox = False;

    switch (cell)
    {

    case FixedCell:

	/*
	 * Get the Rectangle enclosing the cells in fixed rows or columns.
	 * If we don't have fixed rows or columns, then we didn't hit a cell.
	 */
	if (mw->matrix.fixed_columns)
	{
	    SETRECT(rect,
		    COLUMN_LABEL_OFFSET(mw), ROW_LABEL_OFFSET(mw),
		    FIXED_COLUMN_LABEL_OFFSET(mw) - 1,
		    TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
		    TRAILING_FIXED_ROW_HEIGHT(mw) - 1);

	    if (INBOX(rect, *x, *y)) inBox = True;
	}

	if (!inBox && mw->matrix.fixed_rows)
	{
	    SETRECT(rect,
		    COLUMN_LABEL_OFFSET(mw), ROW_LABEL_OFFSET(mw),
		    TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) +
		    TRAILING_FIXED_COLUMN_WIDTH(mw) - 1,
		    FIXED_ROW_LABEL_OFFSET(mw) - 1);

	    if (INBOX(rect, *x, *y)) inBox = True;
	}

	if (!inBox && mw->matrix.trailing_fixed_columns)
	{
	    SETRECT(rect,
		    TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw),
		    ROW_LABEL_OFFSET(mw),
		    TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) +
		    TRAILING_FIXED_COLUMN_WIDTH(mw) - 1,
		    TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
		    TRAILING_FIXED_ROW_HEIGHT(mw) - 1);

	    if (INBOX(rect, *x, *y)) inBox = True;
	}

	if (!inBox && mw->matrix.trailing_fixed_rows)
	{
	    SETRECT(rect,
		    COLUMN_LABEL_OFFSET(mw),
		    TRAILING_FIXED_ROW_LABEL_OFFSET(mw),
		    TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) +
		    TRAILING_FIXED_COLUMN_WIDTH(mw) - 1,
		    TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
		    TRAILING_FIXED_ROW_HEIGHT(mw) - 1);

	    if (INBOX(rect, *x, *y)) inBox = True;
	}

	
	if (!inBox && !mw->matrix.fixed_columns &&
	    !mw->matrix.fixed_rows &&  !mw->matrix.trailing_fixed_rows &&
	    !mw->matrix.trailing_fixed_columns)
	{
	    if (*x < ROW_LABEL_WIDTH(mw))
                *row = -1;
	    else
                *column = xbaeXtoCol(mw, *x + (mw->matrix.fixed_columns
                                           ? 0
                                           : HORIZ_ORIGIN(mw)));
	    if (*y < COLUMN_LABEL_HEIGHT(mw))
                *column = -1;
	    else
                *row = YtoRow(mw, *y) + (mw->matrix.fixed_rows
                                         ? 0
                                         : VERT_ORIGIN(mw));
	    return False;
	}

	/*
	 * If the point is in this rectangle, calculate the row/column
	 * it hits. Otherwise we didn't hit a cell.
	 */
	if (inBox)
	{

	    /*
	     * Translate the point to rect's coord system
	     */
	    *x -= rect.x1;
	    *y -= rect.y1;

	    /*
	     * Convert this point to a row/column. We only take into
	     * account the scrolling origins if we are not fixed in that
	     * dimension.
	     */
	    *row = YtoRow(mw, *y) + (mw->matrix.fixed_rows
				     ? 0
				     : VERT_ORIGIN(mw));
	    *column = xbaeXtoCol(mw, *x + (mw->matrix.fixed_columns
					   ? 0
					   : HORIZ_ORIGIN(mw)));
	    
	    /*
	     * Sanity check the result
	     */
	    if ( ( (*row < 0) || (*column < 0) ) ||
		 ( mw->matrix.fixed_rows && (*row >= (int)mw->matrix.fixed_rows) &&
		   ( !mw->matrix.trailing_fixed_rows ||
		    ( mw->matrix.trailing_fixed_rows && (*row < TRAILING_VERT_ORIGIN(mw))))) ||
		 ( mw->matrix.fixed_columns && (*column >= (int)mw->matrix.fixed_columns) &&
		   ( !mw->matrix.trailing_fixed_columns ||
		     ( mw->matrix.trailing_fixed_columns && (*column < TRAILING_HORIZ_ORIGIN(mw))))) )
		return False;
	    
	    /*
	     * Adjust x,y so they are relative to this cells origin.
	     */
	    *x -= COLUMN_POSITION(mw, *column) -
		(mw->matrix.fixed_columns
		 ? 0
		 : HORIZ_ORIGIN(mw));
	    *y %= ROW_HEIGHT(mw);

	    return True;
	}
	else
	    return False;

	/* NOTREACHED */
	break;

    case NonFixedCell:

	/*
	 * Translate the point to take into account fixed rows or columns.
	 */
	*x += FIXED_COLUMN_WIDTH(mw);
	*y += FIXED_ROW_HEIGHT(mw);

	/*
	 * Convert the new point to a row/column position
	 */
	*row = YtoRow(mw, *y) + VERT_ORIGIN(mw);
	*column = xbaeXtoCol(mw, *x + HORIZ_ORIGIN(mw));

	/*
	 * Sanity check the result
	 */
	if (*row >= TRAILING_VERT_ORIGIN(mw) ||
	    *column >= TRAILING_HORIZ_ORIGIN(mw) ||
	    *row < 0 || *column < 0)
	    return False;

	/*
	 * Adjust x,y so they are relative to this cells origin.
	 */
	*x -= COLUMN_POSITION(mw, *column) - HORIZ_ORIGIN(mw);
	*y %= ROW_HEIGHT(mw);

	return True;

	/* NOTREACHED */
	break;

    default:
	return False;
    }
}

/*
 * Convert a pixel position to the column it is contained in.
 */
int
xbaeXtoCol(mw, x)
XbaeMatrixWidget mw;
int x;
{
    int i;

    for (i = 1; i < mw->matrix.columns; i++)
	if (COLUMN_POSITION(mw, i) > x)
	    return i - 1;

    return i - 1;
}

/*
 * Draw a fixed or non-fixed cell. The coordinates are calculated relative
 * to the correct window and pixmap is copied to that window.
 */
void
xbaeDrawCellPixmap(mw, row, column, pixmap)
XbaeMatrixWidget mw;
int row;
int column;
Pixmap pixmap;
{
    int x, y;
    Window win = CELL_WINDOW(mw, row, column);

    if (!win)
	return;

    /*
     * Convert the row/column to the coordinates relative to the correct
     * window
     */
    xbaeRowColToXY(mw, row, column, &x, &y);

    /*
     * Draw the pixmap.
     gc_mask.background = None;
     gc_mask.function
     gc_mask.planemask
     gc_mask.subwindow_mode
     gc_mask.graphics_exposeures
     gc_mask.clip_x_origin
     gc_mask.clip_y_origin
     gc_mask.clip_mask
     gc = XtGetGC((clipped ? ClipChild(mw) : (Widget)mw), gc_mask, &gc_values);
     XtReleaseGC((clipped ? ClipChild(mw) : (Widget)mw), gc);
     */

    XCopyArea(XtDisplay(mw), pixmap, win, mw->matrix.draw_gc, 0, 0, COLUMN_WIDTH(mw, column), ROW_HEIGHT(mw), 0, 0);
/*
  DefaultGC(dpy, DefaultScreen(dpy))
  */
	      

    /* XXX Do I really want to do this?
     * Surround the cell with a shadow.
     if (mw->matrix.cell_shadow_thickness)
     {
     if (clipped)
     DRAW_SHADOW(XtDisplay(mw), win,
     mw->matrix.cell_bottom_shadow_clip_gc,
     mw->matrix.cell_top_shadow_clip_gc,
     mw->matrix.cell_shadow_thickness,
     x + (int) mw->matrix.cell_highlight_thickness,
     y + (int) mw->matrix.cell_highlight_thickness,
     COLUMN_WIDTH(mw, column) -
     2 * mw->matrix.cell_highlight_thickness,
     ROW_HEIGHT(mw) -
     2 * mw->matrix.cell_highlight_thickness,
     mw->matrix.shadow_type);
     else
     DRAW_SHADOW(XtDisplay(mw), win,
     mw->manager.bottom_shadow_GC,
     mw->manager.top_shadow_GC,
     mw->matrix.cell_shadow_thickness,
     x + (int) mw->matrix.cell_highlight_thickness,
     y + (int) mw->matrix.cell_highlight_thickness,
     COLUMN_WIDTH(mw, column) -
     2 * mw->matrix.cell_highlight_thickness,
     ROW_HEIGHT(mw) -
     2 * mw->matrix.cell_highlight_thickness,
     mw->matrix.shadow_type);
     }
     */

}

/*
 * Draw a fixed or non-fixed cell. The coordinates are calculated relative
 * to the correct window and the cell is drawn in that window.
 */
void
xbaeDrawCellString(mw, row, column, string, bg, fg)
XbaeMatrixWidget mw;
int row, column;
String string;
Pixel bg, fg;
{
    int x, y;
    GC gc;
    Window win = CELL_WINDOW(mw, row, column);
    Boolean clipped = ((row < (int)mw->matrix.fixed_rows) ||
		       (row >= TRAILING_VERT_ORIGIN(mw))) &&
	(column >= (int)mw->matrix.fixed_columns) &&
	(column < TRAILING_HORIZ_ORIGIN(mw));

    if (!win)
	return;

    /*
     * Convert the row/column to the coordinates relative to the correct
     * window
     */
    xbaeRowColToXY(mw, row, column, &x, &y);

    gc = (clipped ? mw->matrix.draw_clip_gc : mw->matrix.draw_gc);
    XSetForeground(XtDisplay(mw), gc, bg);
    XFillRectangle( XtDisplay(mw), win, gc, x, y,
		    COLUMN_WIDTH(mw, column), ROW_HEIGHT(mw) );

    /*
     * Draw the string in the cell.
     */
    if (*string != '\0')
    {
	xbaeDrawString(mw, win, string, strlen(string),
		       x + TEXT_X_OFFSET(mw), y + TEXT_Y_OFFSET(mw),
		       mw->matrix.column_widths[column],
		       mw->matrix.column_alignments ?
			  mw->matrix.column_alignments[column] :
			  XmALIGNMENT_BEGINNING,
		       mw->matrix.selected_cells[row][column],
		       False, clipped, False, False, fg);
    }

    /*
     * Surround the cell with a shadow.
     */
    if (mw->matrix.cell_shadow_thickness)
    {
	if (clipped)
	{
	    switch (mw->matrix.grid_type)
	    {
	    case XmGRID_NONE:
	    case XmGRID_ROW_SHADOW:
	    case XmGRID_COLUMN_SHADOW:
		break;
	    case XmGRID_LINE:
		DRAW_SHADOW(XtDisplay(mw), win,
			      mw->matrix.cell_grid_line_gc,
			      mw->matrix.cell_grid_line_gc,
			      mw->matrix.cell_shadow_thickness, x, y,
			      COLUMN_WIDTH(mw, column), ROW_HEIGHT(mw),
			      mw->matrix.cell_shadow_type);
		break;
	    case XmGRID_SHADOW_OUT:
		DRAW_SHADOW(XtDisplay(mw), win,
			      mw->matrix.cell_bottom_shadow_clip_gc,
			      mw->matrix.cell_top_shadow_clip_gc,
			      mw->matrix.cell_shadow_thickness, x, y,
			      COLUMN_WIDTH(mw, column), ROW_HEIGHT(mw),
			      mw->matrix.cell_shadow_type);
		break;
	    case XmGRID_SHADOW_IN:
		DRAW_SHADOW(XtDisplay(mw), win,
			      mw->matrix.cell_top_shadow_clip_gc,
			      mw->matrix.cell_bottom_shadow_clip_gc,
			      mw->matrix.cell_shadow_thickness, x, y,
			      COLUMN_WIDTH(mw, column), ROW_HEIGHT(mw),
			      mw->matrix.cell_shadow_type);
		break;
	    }
	}
	else
	{
	    switch (mw->matrix.grid_type)
	    {
	    case XmGRID_ROW_SHADOW:
	    case XmGRID_COLUMN_SHADOW:
	    case XmGRID_NONE:
		break;
	    case XmGRID_LINE:
		DRAW_SHADOW(XtDisplay(mw), win,
			      mw->matrix.grid_line_gc,
			      mw->matrix.grid_line_gc,
			      mw->matrix.cell_shadow_thickness,
			      x, y,
			      COLUMN_WIDTH(mw, column),
			      ROW_HEIGHT(mw),
			      mw->matrix.cell_shadow_type);
		break;
	    case XmGRID_SHADOW_OUT:
		DRAW_SHADOW(XtDisplay(mw), win,
			      mw->manager.bottom_shadow_GC,
			      mw->manager.top_shadow_GC,
			      mw->matrix.cell_shadow_thickness,
			      x, y,
			      COLUMN_WIDTH(mw, column),
			      ROW_HEIGHT(mw),
			      mw->matrix.cell_shadow_type);
		break;
	    case XmGRID_SHADOW_IN:
		DRAW_SHADOW(XtDisplay(mw), win,
			      mw->manager.top_shadow_GC,
			      mw->manager.bottom_shadow_GC,
			      mw->matrix.cell_shadow_thickness,
			      x, y,
			      COLUMN_WIDTH(mw, column),
			      ROW_HEIGHT(mw),
			      mw->matrix.cell_shadow_type);
		break;
	    }
	}    
    }
}

/*
 * Width in pixels of a character in a given font
 */
#define charWidth(fs,c) ((fs)->per_char\
                         ? (fs)->per_char[(unsigned char)(c) -\
					 (fs)->min_char_or_byte2].width\
                         : (fs)->min_bounds.width)


/*
 * Draw a string with specified attributes. We want to avoid having to
 * use a GC clip_mask, so we clip by characters. This complicates the code.
 */
void
#if NeedFunctionPrototypes
xbaeDrawString( XbaeMatrixWidget mw, Window win, String string, int length,
		int x, int y, int maxlen, unsigned char alignment,
		Boolean highlight, Boolean bold, Boolean clip,
		Boolean rowLabel, Boolean colLabel,
		Pixel color )
#else
xbaeDrawString( mw, win, string, length, x, y, maxlen, alignment, highlight,
		bold, clip, rowLabel, colLabel, color )
XbaeMatrixWidget mw;
Window win;
String string;
int length;
int x;
int y;
int maxlen;
unsigned char alignment;
Boolean highlight;
Boolean bold;
Boolean clip;
Boolean rowLabel;
Boolean colLabel;
Pixel color;
#endif
{
    int start, width, maxwidth;
    GC gc;
    XFontStruct	*font;

    if( rowLabel || colLabel )
	font = mw->matrix.label_font;
    else
	font = mw->matrix.font;
    /*
     * Initialize starting character in string
     */
    start = 0;

    /*
     * Calculate max width in pixels and actual pixel width of string.
     * XXX XTextWidth only sums the width of each char.	 A char could
     * have an rbearing greater than the width.	 So we might not clip
     * a char which really should be.
     */
    if( !rowLabel )
	maxwidth = maxlen * FONT_WIDTH(mw);
    else
	maxwidth = maxlen * LABEL_MAX_WIDTH(mw);

    width = XTextWidth(font, string, length);

    /*
     * If the width of the string is greater than the width of this cell,
     * we need to clip. We don't want to use the server to clip because
     * it is slow, so we truncate characters if we exceed a cells pixel width.
     */
    if (width > maxwidth)
    {
	switch (alignment)
	{

	case XmALIGNMENT_CENTER:
	{
	    int startx = x;
	    int endx = x + maxwidth - 1;
	    int newendx;

	    /*
	     * Figure out our x for the centered string.  Then loop and chop
	     * characters off the front until we are within the cell.
	     * Adjust x, the starting character and the length of the string
	     * for each char.
	     */
	    x += maxwidth / 2 - width / 2;
	    while (x < startx)
	    {
		int cw = charWidth(font, string[start]);

		x += cw;
		width -= cw;
		length--;
		start++;
	    }

	    /*
	     * Now figure out the end x of the string.  Then loop and chop
	     * characters off the end until we are within the cell.
	     */
	    newendx = x + width - 1;
	    while (newendx > endx)
	    {
		newendx -= charWidth(font, string[start + length - 1]);
		length--;
	    }

	    break;
	}

	case XmALIGNMENT_END:
	{

	    /*
	     * Figure out our x for the right justified string.
	     * Then loop and chop characters off the front until we fit.
	     * Adjust x for each char lopped off. Also adjust the starting
	     * character and length of the string for each char.
	     */
	    x += maxwidth - width;
	    while (width > maxwidth)
	    {
		int cw = charWidth(font, string[start]);

		width -= cw;
		x += cw;
		length--;
		start++;
	    }
	    break;
	}

	case XmALIGNMENT_BEGINNING:
	default:
	    /*
	     * Leave x alone, but chop characters off the end until we fit
	     */
	    while (width > maxwidth)
	    {
		width -= charWidth(font, string[length - 1]);
		length--;
	    }
	    break;
	}
    }

    /*
     * We fit inside our cell, so just compute the x of the start of our string
     */
    else
    {
	switch (alignment)
	{

	case XmALIGNMENT_CENTER:
	    x += maxwidth / 2 - width / 2;
	    break;

	case XmALIGNMENT_END:
	    x += maxwidth - width;
	    break;

	case XmALIGNMENT_BEGINNING:
	default:
	    /*
	     * Leave x alone
	     */
	    break;
	}
    }

    /*
     * Figure out which GC to use
     */
    if(!rowLabel && !colLabel)
	if(!clip)
	    gc = mw->matrix.draw_gc;
	else
	    gc = mw->matrix.draw_clip_gc;
    else
	if (!clip)
	    gc = mw->matrix.label_gc;
	else
	    gc = mw->matrix.label_clip_gc;

    /*
     * Don't worry, XSetForeground is smart about avoiding unnecessary
     * protocol requests.
     */
    XSetForeground(XtDisplay(mw), gc, color);

    /*
     * Now draw the string at x starting at char 'start' and of length 'length'
     */
#ifdef NEED_WCHAR
    if (TWO_BYTE_FONT(mw))
	XDrawString16(XtDisplay(mw), win, gc, x, y, &string[start], length);
    else
#endif
	XDrawString(XtDisplay(mw), win, gc, x, y, &string[start], length);

    /*
     * If bold is on, draw the string again offset by 1 pixel (overstrike)
     */
    if (bold)
#ifdef NEED_WCHAR
	if (TWO_BYTE_FONT(mw))
	    XDrawString16(XtDisplay(mw), win, gc, x - 1, y, &string[start], length);
	else
#endif
	    XDrawString(XtDisplay(mw), win, gc, x - 1, y, &string[start], length);
}

void
xbaeDrawCell(mw, row, column)
XbaeMatrixWidget mw;
int row, column;
{
    Pixel bg, fg;
    Boolean alt;


    alt = (mw->matrix.alt_row_count && row >= (int)mw->matrix.fixed_rows)
	? (((row - (int)mw->matrix.fixed_rows) / mw->matrix.alt_row_count) % 2)
	: False;

    /*
     * Compute the background and foreground colours of the cell
     */
    if (mw->matrix.selected_cells[row][column])
	if( mw->matrix.reverse_select )
	    if( mw->matrix.colors && mw->matrix.colors[ row ][ column ])
		bg = mw->matrix.colors[ row ][ column ];
	    else
		bg = mw->manager.foreground;
	else
	    bg = mw->matrix.selected_background;
    else if (mw->matrix.cell_background && 
	     mw->matrix.cell_background[row][column] !=
	     mw->core.background_pixel)
	bg = mw->matrix.cell_background[row][column];
    else
    {
	if (alt)
	    bg = mw->matrix.odd_row_background;
	else
	    bg = mw->matrix.even_row_background;
    }

    if (mw->matrix.selected_cells[row][column])
	if( mw->matrix.reverse_select )
	    if (mw->matrix.cell_background && 
		mw->matrix.cell_background[row][column])
		fg = mw->matrix.cell_background[row][column];
	    else
		fg = mw->core.background_pixel;
	else
	    fg = mw->matrix.selected_foreground;
    else if( mw->matrix.colors && mw->matrix.colors[ row ][ column ] !=
	     mw->manager.foreground )
	fg = mw->matrix.colors[ row ][ column ];
    else
	fg = mw->manager.foreground;    

    if (mw->matrix.draw_cell_callback == NULL)
	xbaeDrawCellString(mw, row, column, mw->matrix.cells[row][column],
			   bg, fg);
    else
    {
	String string;
	Pixmap pixmap;

	if (xbaeGetDrawCellValue( mw, row, column, &string, &pixmap,
				  &bg, &fg) == XbaeString)
	    xbaeDrawCellString(mw, row, column, string, bg, fg);
	else
	    xbaeDrawCellPixmap(mw, row, column, pixmap);
    }
}

XbaeCellType
xbaeGetDrawCellValue(mw, row, column, string, pixmap, bg, fg)
XbaeMatrixWidget mw;
int row;
int column;
String *string;
Pixmap *pixmap;
Pixel *bg, *fg;
{
    XbaeMatrixDrawCellCallbackStruct cbd;

    cbd.reason = XbaeDrawCellReason;
    cbd.row = row;
    cbd.column = column;
    cbd.width = COLUMN_WIDTH(mw, column);
    cbd.height = ROW_HEIGHT(mw);
    cbd.type = XbaeString;
    cbd.string = "";
    cbd.pixmap = (Pixmap)NULL;
    cbd.foreground = *fg;
    cbd.background = *bg;
    XtCallCallbackList((Widget)mw, mw->matrix.draw_cell_callback, (XtPointer) &cbd);

    /*
     * Try a "little" error checking, there's not much we can do.
     if ((cbd.type == XbaePixmap) &&
     ((cbd.pixmap == XmUNSPECIFIED_PIXMAP) || (cbd.pixmap == BadPixmap)))
     {
     cbd.string = "";
     cbd.type = XbaeString;
     }
     */

    *pixmap = cbd.pixmap;
    *string = cbd.string;
    *fg = cbd.foreground;
    *bg = cbd.background;

    /* temporarily turn pixmaps off */
    if (cbd.type == XbaePixmap)
    {
	cbd.string = "";
	cbd.type = XbaeString;
    }

    return (cbd.type);
}

/*
 * Convert a row/column cell position to the x/y of its upper left corner
 * wrt the window it will be drawn in (either the matrix window for
 * fixed cells, or the clip window for non-fixed).
 */
void
xbaeRowColToXY(mw, row, column, x, y )
XbaeMatrixWidget mw;
int row;
int column;
int *x;
int *y;
{
    /*
     * If we are in a fixed cell, calculate x/y relative to Matrixs
     * window (take into account labels etc)
     */
    if (IS_FIXED(mw, row, column))
    {
	/*
	 * Ignore horiz_origin if we are in a fixed column
	 */
	if (column < (int)mw->matrix.fixed_columns)
	    *x = COLUMN_LABEL_OFFSET(mw) + COLUMN_POSITION(mw, column);
	else if (column >= TRAILING_HORIZ_ORIGIN(mw))
	{
	    int m;
	    *x = TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw);
	    for (m = TRAILING_HORIZ_ORIGIN(mw); m < column; m++)
		*x += COLUMN_WIDTH(mw, m);
	}
	else
	    *x = COLUMN_LABEL_OFFSET(mw) +
		COLUMN_POSITION(mw, column) - HORIZ_ORIGIN(mw);

	/*
	 * Ignore vert_origin if we are in a fixed row
	 */
	if (row < (int)mw->matrix.fixed_rows)
	    *y = ROW_LABEL_OFFSET(mw) + ROW_HEIGHT(mw) * row;
	else if (row >= TRAILING_VERT_ORIGIN(mw))
	{
	    int m;
	    *y = TRAILING_FIXED_ROW_LABEL_OFFSET(mw);
	    for (m = TRAILING_VERT_ORIGIN(mw); m < row; m++)
		*y += ROW_HEIGHT(mw);
	}
	else
	    *y = ROW_LABEL_OFFSET(mw) + ROW_HEIGHT(mw) *
		(row - VERT_ORIGIN(mw));
    }

    /*
     * If we are not fixed we must account for fixed rows/columns
     * and scrolling origins.
     */
    else
    {
	*x = (COLUMN_POSITION(mw, column) -
	      COLUMN_POSITION(mw, mw->matrix.fixed_columns)) -
	    HORIZ_ORIGIN(mw);
	*y = ROW_HEIGHT(mw) * ((row - (int) mw->matrix.fixed_rows) -
			       VERT_ORIGIN(mw));
    }
}

