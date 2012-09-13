/*D************************************************************
 * Modul:    GUI - BM dialog      bboard.c
 *
 *             Contains the BM board
 *
 * Functions:  
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */
#include <uinclude.h>
#include <psmatrix.h>

static char rcsid[] = "$Header: /yafra/cvsroot/mapo/source/gui/bboard.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";

/*E------------------------ EXTERNAL  -------------------------------------- */
extern Widget toplevel;
extern Display *display;
extern char *xbmLabelTable[][XBMLABMAXTEXTS];


/*P------------------------ PROTOTYPES -------------------------------------- */
static void xBMboardCreate(unsigned char, int, int, int *, int *, char *title);
static Widget xBMboardMenubarCreate(Widget, int);
static XtCallbackProc xBMboardMenubarAction(Widget, XtPointer, XtPointer);
static XtCallbackProc xBMboardSelectAction(Widget, XtPointer, XtPointer);



/*G------------------------ GLOBAL VARIABLES -------------------------------- */
/*--- Callback Qualifier --------------------*/
#define BOARD_BUTTON_QUIT		0
#define BOARD_BUTTON_HELP		1
#define _NB_BOARD_BUTTONS_		2
#define _VISIBLE_ROWS_			10
#define _VISIBLE_COLS_			5
#define _DEF_COLUMN_WIDTH_		8

/* we can manage 3 boards */
#define MPMX_LELVELS          3
#define MPMX_LEVEL1           0
#define MPMX_LEVEL2           1
#define MPMX_LEVEL3           2

/* default highlight color */
#define MPMX_DEFCOLOR			"SteelBlue"

typedef struct
{
	int board;
	int menuix;
} MPMX_CALLBACK;

MPMX_CALLBACK boardCallback[MPMX_LELVELS][_NB_BOARD_BUTTONS_] =
{
	{0, BOARD_BUTTON_QUIT, 0, BOARD_BUTTON_HELP},
	{1, BOARD_BUTTON_QUIT, 1, BOARD_BUTTON_HELP},
	{2, BOARD_BUTTON_QUIT, 2, BOARD_BUTTON_HELP}
};

typedef struct
{
	Widget matrix;
	Widget popup;
	int rows;
	int cols;
	int *rowbuf;
	int *colbuf;
} MPMX_WIDGET;

MPMX_WIDGET Wmatrix[MPMX_LELVELS] =
{
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0}
};

/*F-------------------------------------------------------------------------
 *  Function:   xBMboardPopup ()
 *             Popup a matrix board of specified mode
 *             -
 *  In:        -the mode of board, the description to scan, the title 
 *  out:       -
 *  Return:    -
 *---------------------------------------------------------------------------
 */
void xBMboardPopup(unsigned char mode, char *inputstring, char *title)
{
	Widget shell;

	int pos;
	int i, j, z, s;
	int numcolumns, numrows, numfields, m, visiblerows, visiblecols;
	char **col, **row, ***cell;
	int *rowbuf, *colbuf;
	Pixel **pix;
	char bchtxt[_RECORDLEN];						/*!!! dangerous - check with DBI */
	char bchcol[_RECORDLEN], bez[_RECORDLEN];	/*!!! DANGEROUS */
	char *ptr;
	short *columnWidths = (short *) 0;
	short maxlen, len;

	Colormap cmap;
	XColor col_scrn, col_rgb;
	Pixel blackpix, defaultbg, cellbg;

	/* init */
	visiblerows = 0;
	visiblecols = 0;
	cmap = XDefaultColormap(display, XDefaultScreen (display));
	blackpix = BlackPixel(display, XDefaultScreen (display));

	/* check inputstring if NULL do nothing */
	if (*inputstring == NULL)
		{
		xUIbeep(toplevel, 0, 0, 0);
		return;
		}

	/*--- Scan the Input String --------------*/
	for (ptr = inputstring, pos = 0; *ptr;)
		{
		*bez = '\0';
		(void)sscanf(ptr, "%[^\t]", bez);
		ptr += strlen (bez);
		if (pos < 3)
			{
			switch (pos)
				{
				case 0:	  /* NUM OF FIELDS */
					numfields = atoi(bez);
					if (numfields == 0)
						{
						perror("\nMPGUI: Invalid DB buffer, zero fields of matrix\n");
						return;
						}
					break;
				case 1:	  /* NUM OF COLUMNS */
					numcolumns = atoi (bez);
					if (numcolumns == 0)
						{
						perror("\nMPGUI: Invalid DB buffer, zero cols of matrix\n");
						return;
						}
					visiblecols = (numcolumns > _VISIBLE_COLS_) ? _VISIBLE_COLS_ : numcolumns;
					col = (char **)XtMalloc(numfields * numcolumns * sizeof (char *));
					colbuf = (int *)XtMalloc(numfields * numcolumns * sizeof (int));
					break;
				case 2:	  /* NUM OF ROWS */
					numrows = atoi(bez);
					if (numrows == 0)
						{
						perror("\nMPGUI: Invalid DB buffer, zero rows of matrix\n");
						return;
						}
					visiblerows = (numrows > _VISIBLE_ROWS_) ? _VISIBLE_ROWS_ : numrows;
					row = (char **)XtMalloc(numrows * sizeof(char *));
					rowbuf = (int *)XtMalloc(numrows * sizeof(int));
					cell = (char ***)XtMalloc(numrows * sizeof(char **));
					pix = (Pixel **)XtMalloc(numrows * sizeof(Pixel *));
					for (i = 0; i < numrows; i++)
						{
						cell[i] = (char **)XtMalloc(numfields * numcolumns * sizeof(char *));
						pix[i] = (Pixel *)XtMalloc(numfields * numcolumns * sizeof(Pixel));
						}
					break;
				}
			}
		else
			{
			if (pos - 3 < 2 * numcolumns)
				{
				j = (pos - 3) / 2;
				if ((pos - 3) % 2 == 0)
					{
					/* Column Label */
					col[j * numfields] = (char *)XtMalloc((strlen (bez) + 1) * sizeof (char));
					for (i = 1; i < numfields; i++)
						col[j * numfields + i] = NULL;
					(void)sprintf (col[j], "%s", bez);
					}
				else
					{
					/* Column ID */
					colbuf[j * numfields] = atoi (bez);
					for (i = 1; i < numfields; i++)
						colbuf[j * numfields + i] = colbuf[j * numfields];
					}
				}
			else if (pos - 3 - 2 * numcolumns < 2 * numrows)
				{
				j = (pos - 3 - 2 * numcolumns) / 2;
				if ((pos - 3 - 2 * numcolumns) % 2 == 0)
					{
					/* Row Label */
					row[j] = (char *)XtMalloc((strlen (bez) + 1) * sizeof(char));
					(void)sprintf(row[j], "%s", bez);
					}
				else
					rowbuf[j] = atoi(bez);
				}
			else if (pos - 3 - 2 * numcolumns - 2 * numrows < numfields * numrows * numcolumns)
				{
				/* Matrix Cell */
				i = pos - 3 - 2 * numcolumns - 2 * numrows;
				z = i / numcolumns;
				s = i % numcolumns;
				cell[z][s] = (char *)XtMalloc((strlen(bez) + 1) * sizeof(char));
				(void)sprintf(cell[z][s], "%s", bez);
				}
			}
		if (*ptr == '\t')
			{
			pos++;
			ptr++;
			}
		}

	/*--- Create the Matrix Widget ----------------*/
	xBMboardCreate(mode, numrows, numcolumns * numfields, rowbuf, colbuf, title);

	/* get color for standard background */
	if (XAllocNamedColor(display, cmap, MPMX_DEFCOLOR, &col_scrn, &col_rgb) != 0)
		cellbg = col_scrn.pixel;
	else
		cellbg = blackpix;

	columnWidths = (short *)XtMalloc(numcolumns * numfields * sizeof(short));

	/*--- Set all resources, depending on the MODE */
	switch (mode)
		{
		case MATRIXSHOW:
			m = MPMX_LEVEL1;
			for (i = 0; i < numcolumns * numfields; i++)
				{
				maxlen = 1;
				len = strlen (col[i]);
				maxlen = maxlen > len ? maxlen : len;
				for (j = 0; j < numrows; j++)
					{
					if (cell[j][i] == NULL)
						len = 0;
					else
						len = strlen(cell[j][i]);
					maxlen = maxlen > len ? maxlen : len;
					}
				columnWidths[i] = maxlen;
				}

			XtVaSetValues (Wmatrix[m].matrix,
			  XmNboldLabels, True,
			  XmNcells, cell,
			  XmNcellShadowType, XmSHADOW_IN,
			  XmNcolumnLabels, col,
			  XmNcolumnWidths, columnWidths,
			  XmNevenRowBackground, cellbg,
			  XmNgridType, XmGRID_SHADOW_IN,
			  XmNrowLabels, row,
			  XmNtraversalOn, False,
			  XmNvisibleRows, visiblerows,
			  XmNvisibleColumns, visiblecols * numfields,
			  NULL);
			break;

		case MATRIXBINARY:
			m = MPMX_LEVEL2;
			XtVaGetValues(Wmatrix[m].matrix, XmNbackground, &defaultbg, NULL);

			/* set length of fields */
			for (i = 0; i < numcolumns * numfields; i++)
				{
				maxlen = 1;
				len = strlen(col[i]);
				maxlen = maxlen > len ? maxlen : len;
				for (j = 0; j < numrows; j++)
					{
					if (cell[j][i] == NULL)
						len = 0;
					else
						len = strlen(cell[j][i]);
					maxlen = maxlen > len ? maxlen : len;
					}
				columnWidths[i] = maxlen;
				}

			/* set bg colors and context of cells */
			for (i = 0; i < numrows; i++)
				{
				for (j = 0; j < numcolumns * numfields; j++)
					{
					*bchtxt = *bchcol = '\0';
					ptr = cell[i][j];
					(void)sscanf(cell[i][j], "%[^\n]", bchtxt);
					ptr += (strlen(bchtxt) + 1);
					(void)sscanf(ptr, "%[^\n]", bchcol);
					if (*bchcol)
						{
						/* it's used - set color */
						if (XAllocNamedColor(display, cmap, bchcol, &col_scrn, &col_rgb) != 0)
							pix[i][j] = col_scrn.pixel;
						else
							pix[i][j] = blackpix;

						/* delete color name in cell and print only text from DBI */
						(void)strcpy(cell[i][j], bchtxt);
						}
					else
						{
						/* it's free */
						*cell[i][j] = '\0';
						pix[i][j] = defaultbg;
						}
					}
				}
			XtVaSetValues (Wmatrix[m].matrix,
			  XmNcells, cell,
			  XmNcellBackgrounds, pix,
			  XmNcellShadowType, XmSHADOW_OUT,
			  XmNcolumnLabels, col,
			  XmNcolumnWidths, columnWidths,
			  XmNgridType, XmGRID_SHADOW_OUT,
			  XmNrowLabels, row,
			  XmNtraversalOn, False,
			  XmNvisibleRows, visiblerows,
			  XmNvisibleColumns, visiblecols * numfields,
			  NULL);
			break;

		case MATRIXEDIT:
			m = MPMX_LEVEL3;
			for (i = 0; i < numcolumns * numfields; i++)
				{
				maxlen = 1;
				len = strlen (col[i]);
				maxlen = maxlen > len ? maxlen : len;
				for (j = 0; j < numrows; j++)
					{
					len = strlen (cell[j][i]);
					maxlen = maxlen > len ? maxlen : len;
					}
				columnWidths[i] = maxlen;
				}
			XtVaSetValues (Wmatrix[m].matrix,
			  XmNcells, cell,
			  XmNrowLabels, row,
			  XmNcolumnLabels, col,
			  XmNcolumnWidths, columnWidths,
			  XmNvisibleRows, visiblerows,
			  XmNvisibleColumns, numcolumns * numfields,
			  NULL);
			break;
		}

	/*--- free memory ---------------*/
	for (i = 0; i < numrows; i++)
		{
		for (j = 0; j < numcolumns * numfields; j++)
			XtFree((void *)cell[i][j]);
		XtFree((void *)cell[i]);
		XtFree((void *)pix[i]);
		XtFree((void *)row[i]);
		}

	XtFree((void *)cell);
	XtFree((void *)pix);
	XtFree((void *)row);
	for (i = 0; i < numcolumns; i++)
		XtFree((void *)col[i]);
	XtFree((void *)col);
	XtFree((void *)columnWidths);

	/* Popup the Matrix Widget */
	for (shell = Wmatrix[m].matrix; !XtIsShell (shell); shell = XtParent (shell));
	XtPopup (shell, XtGrabNone);
}



/*F-------------------------------------------------------------------------
 *  Function:   xBMboardCreate ()
 *             create or update the matrix board
 *             -
 *  In:        -the mode of board, board dimensions 
 *  out:       -
 *  Return:    -
 *---------------------------------------------------------------------------
 */
static void xBMboardCreate(unsigned char mode, int rows, int columns, int *rowbuf,
									int *colbuf, char *title)
{
	Widget popup, manager, menubar;
	Arg arglist[4];
	int ac, d, f, i, diff, m;
	short *columnWidths = (short *) 0;
	char bez[_CHAR200];
	char shellname[_RECORDLEN];
	XtTranslations trans;
	static String select_cell = "#override\n\
		<Btn1Down>:	SelectCell(cell)";

	columnWidths = (short *)XtMalloc(columns * sizeof(short));
	for (i = 0; i < columns; i++)
		columnWidths[i] = 1;

	switch (mode)
		{
		case MATRIXSHOW:
			m = MPMX_LEVEL1;
			break;
		case MATRIXBINARY:
			m = MPMX_LEVEL2;
			break;
		case MATRIXEDIT:
			m = MPMX_LEVEL3;
			break;
		}
	if (!Wmatrix[m].matrix)
		{
		/*--- LEVEL 0  Shell kreieren -----------------------------*/
		(void)sprintf(shellname, "%s%d", BOARDSHELL, m);
		d = MWM_DECOR_BORDER | MWM_DECOR_TITLE | MWM_DECOR_MENU | MWM_DECOR_MINIMIZE;
		f = MWM_FUNC_MOVE | MWM_FUNC_MINIMIZE;
		ac = 0;
		XtSetArg(arglist[ac], XmNallowShellResize, TRUE); ac++;
		XtSetArg(arglist[ac], XmNmwmDecorations, d); ac++;
		XtSetArg(arglist[ac], XmNmwmFunctions, f); ac++;
		popup = XtCreatePopupShell(shellname, topLevelShellWidgetClass,
		                           toplevel, arglist, ac);
		Wmatrix[m].popup = popup;

		/*--- LEVEL 1  manager --------*/
		(void)sprintf(bez, "%s%d", ROWCOLMGR, m);
		manager = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, popup, 0, 0);
		XtManageChild(manager);

		/*--- LEVEL 2  Mini menu ------*/
		menubar = xBMboardMenubarCreate(manager, m);
		XtManageChild(menubar);

		/*--- LEVEL 2  Matrix ---------*/
		(void)sprintf(shellname, "%s%d", BOARDMATRIX, m);
		ac = 0;
		switch (mode)
			{
			case MATRIXSHOW:
				trans = XtParseTranslationTable(select_cell);
				XtSetArg(arglist[ac], XmNtranslations, trans); ac++;
				break;
			case MATRIXBINARY:
				trans = XtParseTranslationTable(select_cell);
				XtSetArg(arglist[ac], XmNtranslations, trans); ac++;
				break;
			case MATRIXEDIT:
				break;
			}
		XtSetArg(arglist[ac], XmNrows, rows); ac++;
		XtSetArg(arglist[ac], XmNcolumns, columns); ac++;
		XtSetArg(arglist[ac], XmNcolumnWidths, columnWidths);	ac++;
		Wmatrix[m].matrix = XtCreateManagedWidget(shellname,
		  xbaeMatrixWidgetClass, manager, arglist, ac);
		XtAddCallback(Wmatrix[m].matrix, XmNselectCellCallback,
		  (XtCallbackProc) xBMboardSelectAction, (XtPointer) mode);
		}
	else
		{
		/*--- look, if we have to delete or add rows, resp. columns ----------*/
		diff = rows - Wmatrix[m].rows;
		if (diff > 0)
			XbaeMatrixAddRows(Wmatrix[m].matrix, Wmatrix[m].rows, NULL, NULL, NULL, diff);
		else if (diff < 0)
			XbaeMatrixDeleteRows(Wmatrix[m].matrix, Wmatrix[m].rows + diff, -diff);

		diff = columns - Wmatrix[m].cols;
		if (diff > 0)
			XbaeMatrixAddColumns(Wmatrix[m].matrix, Wmatrix[m].cols, NULL, NULL, columnWidths, NULL, NULL, NULL, NULL, diff);
		else if (diff < 0)
			XbaeMatrixDeleteColumns(Wmatrix[m].matrix, Wmatrix[m].cols + diff, -diff);
		}

	/*--- Update the title in all cases  -----------------------------*/
	if (strlen(title))
		(void)sprintf(bez, "%s", title);
	else
		(void)sprintf(bez, "%s", LABEL_BOARDTITLE);
	ac = 0;
	XtSetArg(arglist[ac], XmNtitle, bez); ac++;
	XtSetValues(Wmatrix[m].popup, arglist, ac);

	/*--- Update local struct --*/
	Wmatrix[m].rows = rows;
	Wmatrix[m].cols = columns;

	if (Wmatrix[m].rowbuf)
		XtFree((void *)Wmatrix[m].rowbuf);
	Wmatrix[m].rowbuf = rowbuf;

	if (Wmatrix[m].colbuf)
		XtFree((void *)Wmatrix[m].colbuf);
	Wmatrix[m].colbuf = colbuf;

	XtFree((void *)columnWidths);
}



/*F-------------------------------------------------------------------------
 *  Function:   xBMboardMenubarCreate ()
 *             menu buttons in Matrix board window
 *             -
 *  In:        -parent widget, board index 
 *  out:       -
 *  Return:    -
 *---------------------------------------------------------------------------
 */
static Widget xBMboardMenubarCreate(Widget parent, int boardIx)
{
	Widget minimenu, pulldown[8], pullbutton[8], cascadebutton[8];
	Arg args[6];
	int i, n, ac;
	XmString xmstr;

	/*--- Number of menubar items -------*/
	n = XtNumber(boardCallback[0]);

	/*---- menubar --------*/
	minimenu = XmCreateMenuBar(parent, BOARDMENUBAR, 0, 0);

	/*---- build an ONE line menu -----------------------------------------*/
	for (i = 0; i < n; i++)
		{
		/*--- pulldown ----*/
		xmstr = XmStringCreateSimple(xbmLabelTable[_BOARD_MENU][i + 1]);

		/*-- menubar cascade button -----*/
		ac = 0;
		XtSetArg (args[ac], XmNlabelString, xmstr); ac++;
		XtSetArg (args[ac], XmNmnemonic, ' '); ac++;
		cascadebutton[i] = XmCreateCascadeButton(minimenu, BOARDMENUBUTTON, args, ac);
		XtManageChild(cascadebutton[i]);
		XtAddCallback(cascadebutton[i], XmNactivateCallback,
		              (XtCallbackProc)xBMboardMenubarAction,
                    (XtPointer) & boardCallback[boardIx][i]);
		XmStringFree(xmstr);
		}

	/*---- Help right justified ---------*/
	ac = 0;
	XtSetArg(args[ac], XmNmenuHelpWidget, cascadebutton[n - 1]); ac++;
	XtSetValues(minimenu, args, ac);

	/* and return widget pointer */
	return(minimenu);
}



/*F-------------------------------------------------------------------------
 *  Function:   xBMboardSelectAction ()
 *             attached callback when user selects a cell
 *             -
 *  In:        -std callback functions
 *  out:       -
 *  Return:    -
 *---------------------------------------------------------------------------
 */
static XtCallbackProc xBMboardSelectAction(Widget w, XtPointer cdata, XtPointer wdata)
{
	extern Widget toplevel;
	extern long maxoutcomm;
	extern char *outcomm;

	Widget shell;
	int *buf;
	int row, col, m;
	char state[_RECORDLEN];
	String cell;
	XbaeMatrixSelectCellCallbackStruct *cbs = (XbaeMatrixSelectCellCallbackStruct *)wdata;

	row = cbs->row;
	col = cbs->column;
	ACTIONTYP = (unsigned char)cdata;
	switch (ACTIONTYP)
		{
		case MATRIXSHOW:
			m = MPMX_LEVEL1;
			COMMTYP = MATRIXSELECT;
			*state = '\0';
			break;

		case MATRIXBINARY:
			m = MPMX_LEVEL2;
			COMMTYP = MATRIXACTION;
			cell = XbaeMatrixGetCell(w, row, col);
			if (cell != NULL)
				(void)sprintf(state, "%s\t", cell);

#ifdef POPDOWN_FOR_TEST
			/*---- Popdown the Matrix Widget */
			for (shell = Wmatrix[MPMX_LEVEL2].matrix; !XtIsShell(shell); shell = XtParent(shell))
				;
			XtPopdown(shell);
			for (shell = Wmatrix[MPMX_LEVEL1].matrix; !XtIsShell(shell); shell = XtParent (shell))
				;
			XtPopdown(shell);
#endif
			break;
		}

	/*--- send the selected cell */
	sprintf(outcomm, "%d\t%d\t%s", Wmatrix[m].colbuf[col], Wmatrix[m].rowbuf[row], state);
	xUItalkto(SEND, outcomm, strlen(outcomm));
}



/*F-------------------------------------------------------------------------
 *  Function:   xBMboardMenubarAction ()
 *             menu buttons callback
 *             Only quit is used for the moment
 *  In:        -std callback params 
 *  out:       -
 *  Return:    -
 *---------------------------------------------------------------------------
 */
static XtCallbackProc xBMboardMenubarAction(Widget w, XtPointer Input, XtPointer Output)
{
	Widget shell;
	int bd;
	MPMX_CALLBACK *actcallback;
	XmAnyCallbackStruct *any;
	XEvent *event;

	/*--- Callback Qualifier --------------------------*/
	actcallback = (MPMX_CALLBACK *)Input;		/*closure */
	any = (XmAnyCallbackStruct *)Output;
	event = (XEvent *)any->event;

	if (event->type == ButtonPressMask)
		return;
	bd = actcallback->board;

	/*--- Callback actions ----------------------------*/
	switch(actcallback->menuix)
		{
		case BOARD_BUTTON_QUIT:
			/*--- Popdown myself ---*/
			for (shell = Wmatrix[bd].matrix; !XtIsShell(shell); shell = XtParent(shell))
				;
			XtPopdown(shell);

			/*--- Popdown always the other board if available ---*/
			if ((bd == MPMX_LEVEL1) && (Wmatrix[MPMX_LEVEL2].matrix))
				{
				for (shell = Wmatrix[MPMX_LEVEL2].matrix; !XtIsShell(shell); shell = XtParent(shell))
					;
				/* kill shell and free up second board */
				XtPopdown(shell);
				XtDestroyWidget(Wmatrix[MPMX_LEVEL2].popup);
				XtDestroyWidget(Wmatrix[MPMX_LEVEL2].matrix);
				XtFree((void *)Wmatrix[MPMX_LEVEL2].rowbuf);
				XtFree((void *)Wmatrix[MPMX_LEVEL2].colbuf);
				Wmatrix[MPMX_LEVEL2].rows = 0;
				Wmatrix[MPMX_LEVEL2].cols = 0;
				Wmatrix[MPMX_LEVEL2].rowbuf = NULL;
				Wmatrix[MPMX_LEVEL2].colbuf = NULL;
				Wmatrix[MPMX_LEVEL2].popup = NULL;
				Wmatrix[MPMX_LEVEL2].matrix = NULL;
				}

			/*--- delete myself ---*/
			XtDestroyWidget(Wmatrix[bd].popup);
			XtDestroyWidget(Wmatrix[bd].matrix);
			XtFree((void *)Wmatrix[bd].rowbuf);
			XtFree((void *)Wmatrix[bd].colbuf);
			Wmatrix[bd].rows = 0;
			Wmatrix[bd].cols = 0;
			Wmatrix[bd].rowbuf = NULL;
			Wmatrix[bd].colbuf = NULL;
			Wmatrix[bd].popup = NULL;
			Wmatrix[bd].matrix = NULL;
			break;

		case BOARD_BUTTON_HELP:
			break;

		default:
			break;
		}
}
