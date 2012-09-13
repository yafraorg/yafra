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

#ifndef _Xbae_Actions_h
#define _Xbae_Actions_h

#include <Xbae/Macros.h>

/*
 * Actions.h created by Andrew Lister (6 August, 1995)
 */

/*
 * Actions
 */

void xbaeEditCellACT P(( Widget w, XEvent *event, String *params,
			 Cardinal *nparams ));
void xbaeCancelEditACT P(( Widget w, XEvent *event, String *params,
			   Cardinal *nparams ));
void xbaeCommitEditACT P(( Widget w, XEvent *event, String *params,
			   Cardinal *nparams ));
void xbaeSelectCellACT P(( Widget w, XEvent *event, String *params,
			   Cardinal *nparams ));
void xbaeDefaultActionACT P(( Widget w, XEvent *event, String *params,
			      Cardinal *nparams ));
void xbaeTraverseNextACT P(( Widget w, XEvent *event, String *params,
			     Cardinal *nparams ));
void xbaeTraversePrevACT P(( Widget w, XEvent *event, String *params,
			     Cardinal *nparams ));
Boolean xbaeEventToXY P(( XbaeMatrixWidget mw, XEvent *event, int *x, int *y,
			  CellType *cell ));
Boolean xbaeXYToRowCol P(( XbaeMatrixWidget mw, int *x, int *y, int *row,
			   int *column, CellType cell ));
void xbaeHandleClick P(( Widget w, XbaeMatrixWidget mw, XEvent *event,
			 Boolean *cont ));

void xbaeDrawCell P((XbaeMatrixWidget mw, int row, int column ));
void xbaeDrawCellString P(( XbaeMatrixWidget mw, int row, int column,
			    String string, Pixel bg, Pixel fg ));
void xbaeDrawCellPixmap P(( XbaeMatrixWidget mw, int row, int column,
			    Pixmap pixmap ));
void xbaeDrawString P(( XbaeMatrixWidget mw, Window win, String string,
			int length, int x, int y, int maxlen,
			unsigned char alignment, Boolean highlight,
			Boolean bold, Boolean clip, Boolean rowLabel,
			Boolean colLabel, Pixel color ));
XbaeCellType xbaeGetDrawCellValue P(( XbaeMatrixWidget mw, int row,
				      int column, String *string,
				      Pixmap *pixmap, Pixel *bg, Pixel *fg ));
int xbaeXtoCol P(( XbaeMatrixWidget mw, int x ));
void xbaeRowColToXY P(( XbaeMatrixWidget mw, int row, int column, int *x,
			int *y ));
#endif
