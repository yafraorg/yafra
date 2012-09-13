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

#ifndef _Xbae_Macros_h
#define _Xbae_Macros_h
/*
 * Macros.h created by Andrew Lister (6 August, 1995)
 */

/*
 * Prototype wrapper
 */
#ifndef P
#if defined(__STDC__)
#define P(x)		x
#else
#define P(x)		()
#define const
#define volatile
#endif
#endif

#include <Xm/DrawP.h>

#if XmVersion <= 1001
#	define DRAW_SHADOW(dpy, draw, tgc, bgc, sz, x, y, w, h)	\
		_XmDrawShadow(dpy, draw, tgc, bgc, sz, x, y, w, h)
#else
#	define DRAW_SHADOW(dpy, draw, tgc, bgc, sz, x, y, w, h, type)	\
	    _XmDrawShadows(dpy, draw, tgc, bgc, x, y, w, h, sz, type)
#endif

/*
 * Macros to retrieve our children.  Children must be created in this order.
 */
#define HorizScrollChild(mw)	(mw->composite.children[0])
#define VertScrollChild(mw)	(mw->composite.children[1])
#define ClipChild(mw)		(mw->composite.children[2])
#define TextChild(mw)		(mw->composite.children[3])

#define VERT_ORIGIN(mw)		(mw->matrix.top_row)
#define HORIZ_ORIGIN(mw)	(mw->matrix.horiz_origin)

#define VISIBLE_WIDTH(mw)	((int)ClipChild(mw)->core.width)
#define VISIBLE_HEIGHT(mw)	((int)ClipChild(mw)->core.height)

#define TRAILING_VERT_ORIGIN(mw) (mw->matrix.rows - \
				  (int)mw->matrix.trailing_fixed_rows)
#define TRAILING_HORIZ_ORIGIN(mw) (mw->matrix.columns - \
				   (int)mw->matrix.trailing_fixed_columns)

/*
 * Macros
 */
/*
 * Intersect rectangles r1 and r2, place the result in res.
 * Result will be in r1's coord system.
 * Max and Min are defined in Xm/XmP.h in 1.1, they are deprecated in 1.2
 */
#if XmVersion >= 1002
#define Max(x, y)       (((x) > (y)) ? (x) : (y))
#define Min(x, y)       (((x) < (y)) ? (x) : (y))
#endif

#define FONT_WIDTH(mw)		((mw->matrix.font->max_bounds.width + \
				 mw->matrix.font->min_bounds.width) /2 )
#define LABEL_WIDTH(mw)		((mw->matrix.label_font->max_bounds.width + \
				 mw->matrix.label_font->min_bounds.width) / 2 )
#define LABEL_MAX_WIDTH(mw)	(mw->matrix.label_font->max_bounds.width)
#define TEXT_WIDTH_OFFSET(mw)	(mw->matrix.cell_margin_width +\
				 mw->matrix.cell_shadow_thickness + \
				 mw->matrix.cell_highlight_thickness )
#define TEXT_HEIGHT_OFFSET(mw)	(mw->matrix.cell_margin_height +\
				 mw->matrix.cell_shadow_thickness + \
				 mw->matrix.cell_highlight_thickness )
#define COLUMN_WIDTH(mw, col)	((mw->matrix.column_widths[col] * \
				  FONT_WIDTH(mw)) + \
				 ((int)TEXT_WIDTH_OFFSET(mw) * 2))
#define FONT_HEIGHT(mw)		(mw->matrix.font->max_bounds.descent + \
				 mw->matrix.font->max_bounds.ascent)
#define LABEL_HEIGHT(mw)	(mw->matrix.label_font->max_bounds.descent + \
				 mw->matrix.label_font->max_bounds.ascent)
/*
 * The text height defines the row height.  It needs to be the biggest
 * we can expect from both font and label font
 */
#define TEXT_HEIGHT(mw)		(Max( FONT_HEIGHT(mw), LABEL_HEIGHT(mw)))

#define ROW_HEIGHT(mw)		(int)((TEXT_HEIGHT_OFFSET(mw) * 2) + \
				      TEXT_HEIGHT(mw))

#define TEXT_X_OFFSET(mw)	(int)(TEXT_WIDTH_OFFSET(mw))
#define TEXT_Y_OFFSET(mw)	(int)(mw->matrix.text_baseline)
#define LABEL_Y_OFFSET(mw)	(int)(mw->matrix.label_baseline)
#define ROW_LABEL_WIDTH(mw)	(mw->matrix.row_labels \
				 ? (mw->matrix.row_label_width * \
				    LABEL_MAX_WIDTH(mw)) + \
				 (int)TEXT_WIDTH_OFFSET(mw) * 2 : 0)
#define COLUMN_LABEL_HEIGHT(mw) (mw->matrix.column_labels \
				 ? (int)TEXT_HEIGHT_OFFSET(mw) * 2 + \
				 mw->matrix.column_label_maxlines * \
				 LABEL_HEIGHT(mw) \
				 : 0)

#define COLUMN_POSITION(mw, column) mw->matrix.column_positions[column]
 
#define FIXED_COLUMN_WIDTH(mw)	COLUMN_POSITION(mw, mw->matrix.fixed_columns)
#define TRAILING_FIXED_COLUMN_WIDTH(mw) \
		(mw->matrix.trailing_fixed_columns ? \
		 (COLUMN_POSITION(mw, mw->matrix.columns-1) + \
		  COLUMN_WIDTH(mw, mw->matrix.columns-1) - \
		  COLUMN_POSITION(mw, TRAILING_HORIZ_ORIGIN(mw))) : 0)

#define COLUMN_LABEL_OFFSET(mw)	(ROW_LABEL_WIDTH(mw) + \
				 mw->manager.shadow_thickness)
#define FIXED_COLUMN_LABEL_OFFSET(mw) (COLUMN_LABEL_OFFSET(mw) + \
				       FIXED_COLUMN_WIDTH(mw))
#define TRAILING_FIXED_COLUMN_LABEL_OFFSET(mw) (FIXED_COLUMN_LABEL_OFFSET(mw) + VISIBLE_WIDTH(mw))

#define FIXED_ROW_HEIGHT(mw)	(mw->matrix.fixed_rows * ROW_HEIGHT(mw))
#define TRAILING_FIXED_ROW_HEIGHT(mw)	(mw->matrix.trailing_fixed_rows * \
					 ROW_HEIGHT(mw))
#define ROW_LABEL_OFFSET(mw)	(COLUMN_LABEL_HEIGHT(mw) + \
				 mw->manager.shadow_thickness)
#define FIXED_ROW_LABEL_OFFSET(mw) (ROW_LABEL_OFFSET(mw) + \
				    FIXED_ROW_HEIGHT(mw))
#define TRAILING_FIXED_ROW_LABEL_OFFSET(mw) (FIXED_ROW_LABEL_OFFSET(mw) + \
					     VISIBLE_HEIGHT(mw))

#define CELL_TOTAL_WIDTH(mw)	mw->matrix.cell_total_width
#define CELL_TOTAL_HEIGHT(mw)	((mw->matrix.rows - \
				  (int) mw->matrix.fixed_rows - \
				  (int) mw->matrix.trailing_fixed_rows) \
				 * ROW_HEIGHT(mw))

#define VSCROLL_WIDTH(mw)	(VertScrollChild(mw)->core.width + \
				 2 * VertScrollChild(mw)->core.border_width +\
				 mw->matrix.space)
#define VSCROLL_HEIGHT(mw)	(VertScrollChild(mw)->core.height + \
				 2 * VertScrollChild(mw)->core.border_width)
#define HSCROLL_WIDTH(mw)	(HorizScrollChild(mw)->core.width + \
				 2 * HorizScrollChild(mw)->core.border_width)
#define HSCROLL_HEIGHT(mw)	(HorizScrollChild(mw)->core.height + \
				 2 * HorizScrollChild(mw)->core.border_width+\
				 mw->matrix.space)

#define IS_FIXED(mw, row, column) ((row < (int)mw->matrix.fixed_rows) || \
				   (column < (int)mw->matrix.fixed_columns) || \
				   (row >= TRAILING_VERT_ORIGIN(mw)) || \
				   (column >= TRAILING_HORIZ_ORIGIN(mw)))

#define CELL_WINDOW(mw, row, column) \
	(IS_FIXED(mw, row, column) ? XtWindow(mw) : XtWindow(ClipChild(mw)))

/* Inline functions */
#define FreeColumnWidths(mw)		XtFree((XtPointer) \
					       mw->matrix.column_widths)
#define FreeColumnMaxLengths(mw)	XtFree((XtPointer) \
					       mw->matrix.column_max_lengths)
#define FreeColumnPositions(mw)		XtFree((XtPointer) \
					       mw->matrix.column_positions)
#define FreeColumnAlignments(mw)	XtFree((XtPointer) \
					       mw->matrix.column_alignments)
#define FreeColumnLabelAlignments(mw)	XtFree((XtPointer) \
					       mw->matrix.\
					       column_label_alignments)
#define CreateColumnPositions(mw)	(int *) XtMalloc(mw->matrix.columns * \
							 sizeof(int))
#define YtoRow(mw, y)			((y) / (ROW_HEIGHT(mw)))


/*
 * Evaluates to 1 if two Rectangles overlap, 0 if no overlap
 */
#define OVERLAP(r1, r2) ((r1).x2 > (r2).x1 && \
			 (r1).x1 < (r2).x2 && \
			 (r1).y2 > (r2).y1 && \
			 (r1).y1 < (r2).y2)

#define X_INTERSECT(r1, r2, res) { (res).x1 = Max((r1).x1, (r2).x1) - (r1).x1;\
    (res).x2 = Min((r1).x2, (r2).x2) - (r1).x1;}
#define Y_INTERSECT(r1, r2, res) { (res).y1 = Max((r1).y1, (r2).y1) - (r1).y1;\
    (res).y2 = Min((r1).y2, (r2).y2) - (r1).y1;}
#define INTERSECT(r1, r2, res)	{ X_INTERSECT(r1, r2, res); \
    Y_INTERSECT(r1, r2, res); }

/*
 * Evaluates to 1 if the point is in the Rectangle, 0 if not
 */
#define INBOX(r, x, y)		( ( ((r).x2 >= x)) && \
				  ( ((r).x1 <= x)) && \
				  ( ((r).y2 >= y)) && \
				  ( ((r).y1 <= y)) )

/*
 * Macros used for Rectangle calculations.  A Rectangle is defined by it's
 * upper left and lower right corners.
 */

/*
 * Set a Rectangle. (x1,y1) is upper left corner, (x2,y2) is lower right corner
 */
#define SETRECT(r, X1, Y1, X2, Y2) { (r).x1 = X1; (r).y1 = Y1; \
    (r).x2 = X2; (r).y2 = Y2; }

#ifdef NEED_WCHAR
# define TWO_BYTE_FONT(mw)	(mw->matrix.font->max_byte1 != 0)
#endif

#ifdef NEED_24BIT_VISUAL
# define GC_PARENT_WINDOW(w)	XtWindow(get_shell_ancestor((Widget)w))
#else
# define GC_PARENT_WINDOW(w)	RootWindowOfScreen(XtScreen(w))
#endif

/*
 * End of array flags for the array type converters
 */
#define BAD_WIDTH	0
#define BAD_MAXLENGTH	0
#define BAD_ALIGNMENT	3	/* see Xm.h */


/*
 * SetClipMask flags for indicating clip areas
 */
#define CLIP_NONE			0x0000
#define CLIP_FIXED_COLUMNS		0x0001
#define CLIP_FIXED_ROWS			0x0002
#define CLIP_TRAILING_FIXED_COLUMNS	0x0004
#define CLIP_TRAILING_FIXED_ROWS	0x0008
#define CLIP_BETWEEN_FIXED_ROWS		0x0010
#define CLIP_VISIBLE_HEIGHT		0x0020

/*
 * Row and Column grid shadow redraw reasons
 */
#define GRID_REDRAW_EXPOSE		0x0000
#define GRID_REDRAW_SCROLL_VERT		0x0001
#define GRID_REDRAW_SCROLL_HORIZ	0x0002
#define GRID_REDRAW_EDIT		(GRID_REDRAW_SCROLL_VERT|GRID_REDRAW_SCROLL_HORIZ)

#endif /* _Xbae_Macros_h */
