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

#ifndef _Xbae_ScrollMgr_h
#define _Xbae_ScrollMgr_h

#include <Xbae/Macros.h>
/*
 * ScrollMgr.h created by Andrew Lister (6 August, 1995)
 */

/*
 * ScrollMgr implementation
 */

SmScrollMgr xbaeSmCreateScrollMgr P(( void ));
void xbaeSmDestroyScrollMgr P(( SmScrollMgr scrollMgr )); 
void xbaeSmAddScroll P(( SmScrollMgr scrollMgr, int delta_x, int delta_y ));
void xbaeSmRemoveScroll P(( SmScrollMgr scrollMgr ));
void xbaeSmScrollEvent P(( SmScrollMgr scrollMgr, XEvent *event ));

/*
 * Scrollbar callbacks
 */
void xbaeScrollVertCB P(( Widget w, XtPointer client_data,
		      XmScrollBarCallbackStruct *call_data ));
void xbaeScrollHorizCB P(( Widget w, XtPointer client_data,
		       XmScrollBarCallbackStruct *call_data ));

void xbaeRedrawCells P(( XbaeMatrixWidget mw, XBAERectangle *expose ));
void xbaeRedrawLabelsAndFixed P(( XbaeMatrixWidget mw, XBAERectangle *expose ));

void xbaeDrawGridShadows P(( XbaeMatrixWidget mw, unsigned int redraw_reason ));
void xbaeDrawRowShadow P(( XbaeMatrixWidget mw, int row, unsigned int redraw_reason ));
void xbaeDrawColumnShadow P(( XbaeMatrixWidget mw, int column, unsigned int redraw_reason ));

#endif
