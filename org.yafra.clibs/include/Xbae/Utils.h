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

#ifndef _Xbae_Utils_h
#define _Xbae_Utils_h

/*
 * Actions.h created by Andrew Lister (6 August, 1995)
 */
void xbaeGetVisibleRows P(( XbaeMatrixWidget mw, int *top_row, int *bottom_row ));
void xbaeGetVisibleColumns P(( XbaeMatrixWidget mw, int *left_column,
			   int *right_column ));
void xbaeGetVisibleCells P(( XbaeMatrixWidget mw, int *top_row,
			 int *bottom_row, int *left_column,
			 int *right_column ));
void xbaeClearCell P(( XbaeMatrixWidget mw, int row, int column ));
void xbaeMakeRowVisible P(( XbaeMatrixWidget mw, int row ));
void xbaeMakeColumnVisible P(( XbaeMatrixWidget mw, int column ));
void xbaeMakeCellVisible P(( XbaeMatrixWidget mw, int row, int column ));
void xbaeAdjustTopRow P(( XbaeMatrixWidget mw ));
void xbaeAdjustLeftColumn P(( XbaeMatrixWidget mw ));
Boolean xbaeIsRowVisible P(( XbaeMatrixWidget mw, int row ));
Boolean xbaeIsColumnVisible P(( XbaeMatrixWidget mw, int column ));
Boolean xbaeIsCellVisible P(( XbaeMatrixWidget mw, int row, int column ));

void xbaeCopyBackground P(( Widget widget, int offset, XrmValue *value ));
void xbaeCopyForeground P(( Widget widget, int offset, XrmValue *value ));
void xbaeCopyDoubleClick P(( Widget widget, int offset, XrmValue *value ));

void xbaeCopySelectedCells P(( XbaeMatrixWidget mw ));
void xbaeCopyRowLabels P(( XbaeMatrixWidget mw ));
void xbaeCopyColumnLabels P(( XbaeMatrixWidget mw ));
void xbaeCopyCells P(( XbaeMatrixWidget mw ));
void xbaeCopyColumnWidths  P(( XbaeMatrixWidget mw ));
void xbaeCopyColumnMaxLengths P(( XbaeMatrixWidget mw ));
void xbaeCopyBackgrounds P(( XbaeMatrixWidget mw ));
void xbaeCopyColumnAlignments P(( XbaeMatrixWidget mw ));
void xbaeCopyColumnLabelAlignments P(( XbaeMatrixWidget mw ));
void xbaeCopyColors P(( XbaeMatrixWidget mw ));

void xbaeCreateDrawGC P(( XbaeMatrixWidget mw ));
void xbaeCreateLabelGC P(( XbaeMatrixWidget mw ));
void xbaeCreateLabelClipGC P(( XbaeMatrixWidget mw ));
void xbaeCreateGridLineGC P(( XbaeMatrixWidget mw ));
void xbaeCreateDrawClipGC P(( XbaeMatrixWidget mw ));
void xbaeCreateInverseClipGC P(( XbaeMatrixWidget mw ));
void xbaeCreateTopShadowClipGC P(( XbaeMatrixWidget mw ));
void xbaeCreateBottomShadowClipGC P(( XbaeMatrixWidget mw ));
void xbaeSetClipMask P(( XbaeMatrixWidget mw, unsigned int clip_reason ));
void xbaeNewFont P(( XbaeMatrixWidget mw ));
void xbaeNewLabelFont P(( XbaeMatrixWidget mw ));
void xbaeGetCellTotalWidth P(( XbaeMatrixWidget mw ));
void xbaeGetColumnPositions P(( XbaeMatrixWidget mw ));
void xbaeComputeSize P(( XbaeMatrixWidget mw, Boolean compute_width,
			 Boolean compute_height ));
void xbaeFreeCells P(( XbaeMatrixWidget mw ));
void xbaeFreeRowLabels P(( XbaeMatrixWidget mw ));
void xbaeFreeColumnLabels P(( XbaeMatrixWidget mw ));
void xbaeFreeColors P(( XbaeMatrixWidget mw ));
void xbaeFreeBackgrounds P(( XbaeMatrixWidget mw ));
void xbaeFreeSelectedCells P(( XbaeMatrixWidget mw ));
void xbaeCreateColors P(( XbaeMatrixWidget mw ));
void xbaeCreateBackgrounds P(( XbaeMatrixWidget mw ));
short xbaeMaxRowLabel P(( XbaeMatrixWidget mw ));
void xbaeParseColumnLabel P(( String label, ColumnLabelLines lines ));

#endif
