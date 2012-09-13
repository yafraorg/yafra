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
 *
 */

#ifndef _Xbae_Matrix_h
#define _Xbae_Matrix_h

/*
 * Matrix Widget public include file
 */

#include <Xm/Xm.h>
#include <X11/Core.h>


/* Resources:
 * Name			Class			RepType		Default Value
 * ----			-----			-------		-------------
 * altRowCount		AltRowCount		int		1
 * boldLabels		BoldLabels		Boolean		False
 * cellBackgrounds	Colors			PixelTable	NULL ***
 * cellHighlightThickness HighlightThickness	HorizontalDimension 2
 * cellMarginHeight	MarginHeight		VerticalDimension   5
 * cellMarginWidth	MarginWidth		HorizontalDimension 5
 * cells		Cells			StringTable	NULL
 * cellShadowThickness	ShadowThickness		HorizontalDimension 2
 * cellShadowType	ShadowType		unsigned char	SHADOW_OUT
 * colors		Colors			PixelTable	NULL
 * columnAlignments	Alignments		AlignmentArray	dynamic
 * columnLabelAlignments Alignments		AlignmentArray	dynamic
 * columnLabels		Labels			StringArray	NULL
 * columnMaxLengths	ColumnMaxLengths	MaxLengthArray	NULL
 * columnWidths		ColumnWidths		WidthArray	NULL
 * columns		Columns			int		0
 * defaultActionCallback Callback               Callback        NULL
 * doubleClickInterval  Interval                int             dynamic
 * drawCellCallback	Callback		Callback	NULL
 * enterCellCallback	Callback		Callback	NULL
 * evenRowBackground	Background		Pixel		dynamic
 * fixedColumns		FixedColumns		Dimension	0
 * fixedRows		FixedRows		Dimension	0
 * fontList		FontList		FontList	fixed
 * labelFont		FontList		FontList	fixed
 * gridLineColor	Color			Pixel		dynamic
 * gridType		GridType		GridType	XmGRID_LINE
 * horizonalScrollBar	HorizonalScrollBar	Window		NULL (get only)
 * leaveCellCallback	Callback		Callback	NULL
 * leftColumn           LeftColumn              int             0
 * modifyVerifyCallback	Callback		Callback	NULL
 * oddRowBackground	Background		Pixel		NULL
 * reverseSelect	reverseSelect		Boolean		False
 * rowLabelAlignment	Alignment		Alignment	XmALIGNMENT_END
 * rowLabelWidth	RowLabelWidth		Short		dynamic
 * rowLabels		Labels			StringArray	NULL
 * rows			Rows			int		0
 * selectCellCallback	Callback		Callback	NULL
 * selectedBackground	Color			Pixel		dynamic
 * selectedCells	SelectedCells		BooleanTable	dynamic
 * selectedForeground	Color			Pixel		dynamic
 * selectScrollVisible	SelectScrollVisible	Boolean		True
 * space		Space			Dimension	6
 * shadowType		ShadowType		unsigned char	SHADOW_OUT
 * textBackground	Backgound		Pixel   	dynamic
 * textTranslations	Translations		TranslationTable dynamic
 * topRow		TopRow			int		0
 * trailingFixedColumns	TrailingFixedColumns	Dimension	0
 * trailingFixedRows	TrailingFixedRows	Dimension	0
 * traverseCellCallback	Callback		Callback	NULL
 * verticalScrollBar	VerticalScrollBar	Window		NULL (get only)
 * visibleColumns	VisibleColumns		Dimension	0
 * visibleRows		VisibleRows		Dimension	0
 */

#define XmNaltRowCount			"altRowCount"
#define XmNboldLabels			"boldLabels"
#define XmNcellBackgrounds		"cellBackgrounds"
#define XmNcellHighlightThickness	"cellHighlightThickness"
#define XmNcellMarginHeight		"cellMarginHeight"
#define XmNcellMarginWidth		"cellMarginWidth"
#define XmNcellShadowType		"cellShadowType"
#define XmNcellShadowThickness		"cellShadowThickness"
#define XmNcells			"cells"
#define XmNcolors			"colors"
#define XmNcolumnAlignments		"columnAlignments"
#define XmNcolumnLabelAlignments	"columnLabelAlignments"
#define XmNcolumnLabels			"columnLabels"
#define XmNcolumnMaxLengths		"columnMaxLengths"
#define XmNcolumnWidths			"columnWidths"
#define XmNeditVerifyCallback		"editVerifyCallback"
#define XmNdrawCellCallback		"drawCellCallback"
#define XmNenterCellCallback		"enterCellCallback"
#define XmNevenRowBackground		"evenRowBackground"
#define XmNfixedColumns			"fixedColumns"
#define XmNfixedRows			"fixedRows"
#define XmNgridLineColor		"gridLineColor"
#define XmNgridType			"gridType"
#define XmNlabelFont			"labelFont"
#define XmNleaveCellCallback		"leaveCellCallback"
#define XmNoddRowBackground		"oddRowBackground"
#define XmNreverseSelect		"reverseSelect"
#define XmNrowLabelAlignment		"rowLabelAlignment"
#define XmNrowLabelWidth		"rowLabelWidth"
#define XmNrowLabels			"rowLabels"
#define XmNselectedCells		"selectedCells"
#define XmNselectedBackground		"selectedBackground"
#define XmNselectCellCallback		"selectCellCallback"
#define XmNselectedForeground		"selectedForeground"
#define XmNselectScrollVisible		"selectScrollVisible"
#define XmNtextBackground		"textBackground"
#define XmNtopRow			"topRow"
#define XmNtrailingFixedColumns		"trailingFixedColumns"
#define XmNtrailingFixedRows		"trailingFixedRows"
#define XmNleftColumn			"leftColumn"
#define XmNtraverseCellCallback		"traverseCellCallback"
#define XmNvisibleColumns		"visibleColumns"
#define XmNvisibleRows			"visibleRows"

#define XmCAlignments			"Alignments"
#define XmCAltRowCount			"AltRowCount"
#define XmCBoldLabels			"BoldLabels"
#define XmCCells			"Cells"
#define XmCColors			"Colors"
#define XmCColumnMaxLengths		"ColumnMaxLengths"
#define XmCColumnWidths			"ColumnWidths"
#define XmCFixedColumns			"FixedColumns"
#define XmCFixedRows			"FixedRows"
#define XmCGridType			"GridType"
#define XmCLabels			"Labels"
#define XmCReverseSelect		"ReverseSelect"
#define XmCRowLabelWidth		"RowLabelWidth"
#define XmCSelectedCells		"SelectedCells"
#define XmCSelectScrollVisible		"SelectScrollVisible"
#define XmCTextBackground		"TextBackground"
#define XmCTopRow			"TopRow"
#define XmCTrailingFixedColumns		"TrailingFixedColumns"
#define XmCTrailingFixedRows		"TrailingFixedRows"
#define XmCLeftColumn			"LeftColumn"
#define XmCVisibleColumns		"VisibleColumns"
#define XmCVisibleRows			"VisibleRows"

#if XmVersion == 1001
#define XmRStringArray			"StringArray"
#endif

#define XmRCellTable			"CellTable"
#define XmRWidthArray			"WidthArray"
#define XmRMaxLengthArray		"MaxLengthArray"
#define XmRAlignmentArray		"AlignmentArray"
#define XmRPixelTable			"PixelTable"
#define XmRBooleanTable			"BooleanTable"
#define XmRGridType			"GridType"

/* Class record constants */

externalref WidgetClass xbaeMatrixWidgetClass;

typedef struct _XbaeMatrixClassRec *XbaeMatrixWidgetClass;
typedef struct _XbaeMatrixRec *XbaeMatrixWidget;

/*
 * A few definitions we like to use, but those with R4 won't have.
 * From Xfuncproto.h.
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

#ifndef XlibSpecificationRelease
# ifndef _XFUNCPROTOBEGIN
#   ifdef __cplusplus                      /* for C++ V2.0 */
#     define _XFUNCPROTOBEGIN extern "C" {   /* do not leave open across includes */
#     define _XFUNCPROTOEND }
#   else
#     define _XFUNCPROTOBEGIN
#     define _XFUNCPROTOEND
#   endif
# endif /* _XFUNCPROTOBEGIN */
#else
#include <X11/Xfuncproto.h>
#endif

/*
 * External interfaces to class methods
 */
_XFUNCPROTOBEGIN

extern void XbaeMatrixSetCell P(( Widget w, int row, int column,
				  const String value ));
extern void XbaeMatrixEditCell P(( Widget w, int row, int column ));
extern void XbaeMatrixSelectCell P(( Widget w, int row, int column ));
extern void XbaeMatrixSelectRow P(( Widget w, int row ));
extern void XbaeMatrixSelectColumn P(( Widget w, int column ));
extern void XbaeMatrixDeselectAll P(( Widget w ));
extern void XbaeMatrixDeselectCell P(( Widget w, int row, int column ));
extern void XbaeMatrixDeselectRow P(( Widget w, int row ));
extern void XbaeMatrixDeselectColumn P(( Widget w, int column ));
extern String XbaeMatrixGetCell P(( Widget w, int row, int column ));
extern Boolean XbaeMatrixCommitEdit P(( Widget w, Boolean unmap ));
extern void XbaeMatrixCancelEdit P(( Widget w, Boolean unmap ));
extern void XbaeMatrixAddRows P(( Widget w, int position, String *rows,
				  String *labels, Pixel *colors,
				  int num_rows ));
extern void XbaeMatrixDeleteRows P(( Widget w, int position, int num_rows ));
extern void XbaeMatrixAddColumns P(( Widget w, int position, String *columns,
				     String *labels, short *widths,
				     int *max_lengths,
				     unsigned char *alignments,
				     unsigned char *label_alignments,
				     Pixel *colors, int num_columns ));
extern void XbaeMatrixDeleteColumns P(( Widget w, int position,
					int num_columns ));
extern void XbaeMatrixSetRowColors P(( Widget w, int position,
				       Pixel *colors, int num_colors ));
extern void XbaeMatrixSetColumnColors P(( Widget w, int position,
					  Pixel *colors, int num_colors ));
extern void XbaeMatrixSetCellColor P(( Widget w, int row, int column,
				       Pixel color ));
extern void XbaeMatrixSetRowBackgrounds P(( Widget w, int position,
					    Pixel *colors, int num_colors ));
extern void XbaeMatrixSetColumnBackgrounds P(( Widget w, int position,
					       Pixel *colors,
					       int num_colors ));
extern void XbaeMatrixSetCellBackground P(( Widget w, int row, int column,
					    Pixel color ));
extern int XbaeMatrixGetEventRowColumn P(( Widget w, XEvent *event,
					   int *row, int *column ));
extern void XbaeMatrixGetCurrentCell P(( Widget	w, int *row, int *column ));
extern void XbaeMatrixRefresh P(( Widget w ));
extern int XbaeMatrixVisibleColumns P(( Widget w ));
extern int XbaeMatrixVisibleRows P(( Widget w ));

_XFUNCPROTOEND

#ifndef XBAE_NO_EXTRA_TYPES
typedef unsigned char	Alignment;
typedef Alignment *	AlignmentArray;
typedef String *	StringTable;
typedef short 		Width;
typedef Width *		WidthArray;
typedef int 		MaxLength;
typedef MaxLength *	MaxLengthArray;
#endif

/*
 * cell shadow types
 */
 
enum
{
    XmGRID_NONE,
    XmGRID_LINE,
    XmGRID_SHADOW_IN,
    XmGRID_SHADOW_OUT,
    XmGRID_ROW_SHADOW,
    XmGRID_COLUMN_SHADOW
};

/*
 * Enumeration for type of a cell
 */
typedef enum { FixedCell, NonFixedCell } CellType;

/*
 * Callback reasons.  Try to stay out of range of the Motif XmCR_* reasons.
 */
typedef enum _XbaeReasonType
{
    XbaeModifyVerifyReason = 102,
    XbaeEnterCellReason,
    XbaeLeaveCellReason,
    XbaeTraverseCellReason,
    XbaeSelectCellReason,
    XbaeDrawCellReason,
    XbaeDefaultActionReason
}
XbaeReasonType;

/*
 * DrawCell types.
 */
typedef enum
{
    XbaeString=1,
    XbaePixmap
}
XbaeCellType;

/*
 * Struct passed to modifyVerifyCallback
 */
typedef struct _XbaeMatrixModifyVerifyCallbackStruct
{
    XbaeReasonType reason;
    int row, column;
    XmTextVerifyCallbackStruct *verify;
    const char *prev_text;
}
XbaeMatrixModifyVerifyCallbackStruct;

/*
 * Struct passed to enterCellCallback
 */
typedef struct _XbaeMatrixEnterCellCallbackStruct
{
    XbaeReasonType reason;
    int row, column;
    Boolean doit;
}
XbaeMatrixEnterCellCallbackStruct;

/*
 * Struct passed to leaveCellCallback
 */
typedef struct _XbaeMatrixLeaveCellCallbackStruct
{
    XbaeReasonType reason;
    int row, column;
    String value;
    Boolean doit;
}
XbaeMatrixLeaveCellCallbackStruct;

/*
 * Struct passed to traverseCellCallback
 */
typedef struct _XbaeMatrixTraverseCellCallbackStruct
{
    XbaeReasonType reason;
    int row, column;
    int next_row, next_column;
    int fixed_rows, fixed_columns;
    int leading_fixed_rows, leading_fixed_columns;
    int trailing_fixed_rows, trailing_fixed_columns;
    int num_rows, num_columns;
    String param;
    XrmQuark qparam;
}
XbaeMatrixTraverseCellCallbackStruct;

/*
 * Struct passed to selectCellCallback
 */
typedef struct _XbaeMatrixSelectCellCallbackStruct
{
    XbaeReasonType reason;
    int row, column;
    Boolean **selected_cells;
    String **cells;
    Cardinal num_params;
    String *params;
    XEvent *event;
}
XbaeMatrixSelectCellCallbackStruct;

/*
 * Struct passed to drawCellCallback
 */
typedef struct
{
    XbaeReasonType reason;
    int row, column;
    int width, height;
    XbaeCellType type;
    String string;
    Pixmap pixmap;
    Pixel foreground, background;
}
XbaeMatrixDrawCellCallbackStruct;


/*
 * Struct passed to defaultActionCallback
 */
typedef struct _XbaeMatrixDefaultActionCallbackStruct
{
    XbaeReasonType reason;
    int row, column;
    XEvent *event;
}
XbaeMatrixDefaultActionCallbackStruct;

/* provide clean-up for those with R4 */
#ifndef XlibSpecificationRelease
# undef _Xconst
# undef _XFUNCPROTOBEGIN
# undef _XFUNCPROTOEND
#endif

#undef P

#endif /* _Xbae_Matrix_h */
/* DON'T ADD STUFF AFTER THIS #endif */
