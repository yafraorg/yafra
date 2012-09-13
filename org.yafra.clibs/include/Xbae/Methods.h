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

#ifndef _Xbae_Methods_h
#define _Xbae_Methods_h

#include <Xbae/Macros.h>
/*
 * Methods.h created by Andrew Lister (7 August, 1995)
 */

void xbaeResize P(( XbaeMatrixWidget mw ));

/*
 * New Matrix methods
 */
void xbaeSetCell P(( XbaeMatrixWidget mw, int row, int column,
		     const String value, Boolean update_text ));
void xbaeEditCell P(( XbaeMatrixWidget mw, int row, int column ));
void xbaeSelectCell P(( XbaeMatrixWidget mw, int row, int column ));
void xbaeSelectRow P(( XbaeMatrixWidget mw, int row ));
void xbaeSelectColumn P(( XbaeMatrixWidget mw, int column ));
void xbaeDeselectAll P(( XbaeMatrixWidget mw ));
void xbaeDeselectCell P(( XbaeMatrixWidget, int row, int column ));
void xbaeDeselectRow P(( XbaeMatrixWidget mw, int row ));
void xbaeDeselectColumn P(( XbaeMatrixWidget mw, int column ));
String xbaeGetCell P(( XbaeMatrixWidget, int row, int column ));
Boolean xbaeCommitEdit P(( XbaeMatrixWidget mw, Boolean unmap ));
void xbaeCancelEdit P(( XbaeMatrixWidget mw, Boolean unmap ));
void xbaeAddRows P((XbaeMatrixWidget mw, int position, String *rows,
		    String *labels, Pixel *colors, Pixel *backgrounds,
		    int num_rows ));
void xbaeDeleteRows P(( XbaeMatrixWidget mw, int position, int num_rows ));
void xbaeAddColumns P(( XbaeMatrixWidget mw, int position, String *columns,
			String *labels, short *widths, int *max_lengths,
			unsigned char *alignments,
			unsigned char *label_alignments, Pixel *colors,
			Pixel *backgrounds, int num_columns ));
void xbaeDeleteColumns P(( XbaeMatrixWidget mw, int position,
			   int num_columns ));
void xbaeSetRowColors P(( XbaeMatrixWidget mw, int position, Pixel *colors,
			  int num_colors, Boolean bg ));
void xbaeSetColumnColors P(( XbaeMatrixWidget mw, int position,
			     Pixel *colors, int num_colors, Boolean bg ));
void xbaeSetCellColor P(( XbaeMatrixWidget mw, int row, int column,
			  Pixel color, Boolean bg ));

#endif
