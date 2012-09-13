/*D************************************************************
 * Modul:		GUI - BM dialog                       bbutfild.c
 *
 *					Create butfields: buttons + field couples 
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bbutfild.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";



/*E------------------------ EXTERNALS ---------------------------------------*/

/*P------------------------ PROTOTYPES --------------------------------------*/
static void  xBMpadButtonLabels( int nbItems, int labelIndex);

/*G------------------------ GLOBAL VARIABLES --------------------------------*/


/*F--------------------------------------------------------------------------
 *  Function:	xBMbutfieldCreate
 *					-create total HARD defined number of pushbuttons and fields !
 *					-Button position must match Field
 *					-override BMxxxx translations
 *					-labels are read from labeltable
 *  In:			-parent widget, a menu    
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xBMbutfieldCreate( Widget parent, BOOKMENU *b, int nbItems, int labelIndex )
{
	extern XtTranslations	BMfielddelete, BMedit, BMtransnoedit, softkeytrans;
	extern char					*xbmLabelTable[][XBMLABMAXTEXTS];		/* xbm */  
	extern OBJCOLORS			orgcol, keycol, gracol, nextmenucol;
	extern unsigned char		actiontoggle;

	Widget		rowcolmenu;
	Widget		rowcolbutton ;
	Widget		rowcolfield ;
	char			bez[_CHAR30+1], fez[_CHAR30+1];
	char			*defwert ;
	Arg			arglist[10];
	int			ac;
	int			i, nr;
	XmString		xmStr; 	
	Position		ypos, *yposptr;
	Dimension	marginheight, marginwidth;
	short			space;
	XtTranslations	translat;
	Dimension	width, maxwidth;


	/*---- inits ------*/
	nr = _BMCATNR ; 
	b->nbitems = nbItems;

	/*---- create row/column ------------------------------------------------*/
	ac = 0;
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT); ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	rowcolmenu = XtCreateManagedWidget( ROWCOLBUTFIELD, xmRowColumnWidgetClass,
														parent, arglist, ac);

	ac = 0;
	XtSetArg(arglist[ac], XmNpacking, XmPACK_NONE); ac++;
	rowcolbutton = XtCreateManagedWidget( ROWCOLBUTFIELD, xmRowColumnWidgetClass,
													 rowcolmenu, arglist, ac);
	ac = 0;
	XtSetArg(arglist[ac], XmNpacking, XmPACK_NONE); ac++;
	rowcolfield = XtCreateManagedWidget( ROWCOLBUTFIELD, xmRowColumnWidgetClass,
													 rowcolmenu, arglist, ac);

	/*---- Get dimensions for button<->field correspondance ------------------*/
	ac = 0;
	XtSetArg(arglist[ac], XmNspacing, &space); ac++;
	XtSetArg(arglist[ac], XmNmarginHeight, &marginheight); ac++;
	XtSetArg(arglist[ac], XmNmarginWidth, &marginwidth); ac++;
	XtGetValues( rowcolbutton, arglist, ac);
	if (space <= 0)
	{	space = 2;
		XtSetArg(arglist[0], XmNspacing, space);
		XtSetValues(rowcolbutton, arglist, 1);
		XtSetValues(rowcolfield,  arglist, 1);
	}

	/*----- LEVEL 5 create ALL total PushButtons -------------*/
	b->Wgbuttons = (Widget *)XtMalloc( nbItems * sizeof(Widget));
	b->Wgfields  = (Widget *)XtMalloc( nbItems * sizeof(Widget));
	xBMpadButtonLabels( nbItems, labelIndex);
	ypos = marginheight;
	yposptr = &ypos;
	maxwidth = 0;
	for (i= 0; i<nbItems; i++ )
	{
		/*------ Create Pushbutton ------------- */
		(void)sprintf(fez, "%s%s%d", ROWCOLBUTFIELD, PUSHBUTTON, i);
		ac = 0;
		xmStr = XmStringCreateLtoR( xbmLabelTable[labelIndex][i], XmSTRING_DEFAULT_CHARSET);
		XtSetArg(arglist[ac], XmNlabelString, xmStr); ac++;
		XtSetArg(arglist[ac], XmNy, *yposptr);			ac++;
		XtSetArg(arglist[ac], XmNx, marginwidth);		ac++;
		XtSetArg(arglist[ac], XmNrecomputeSize, False);		ac++;
		b->Wgbuttons[i] = XmCreatePushButton( rowcolbutton, bez, arglist, ac);
		XmStringFree( xmStr); 
		ac = 0;
		XtSetArg(arglist[ac], XmNwidth, &width); ac++;
		XtGetValues(b->Wgbuttons[i], arglist, ac);
		if (width > maxwidth) maxwidth = width;

		/*--- Button color ---*/
		xUIinitcolors (b->Wgbuttons[i]);
		if ((actiontoggle != INSERT) && (b->suchfields[i] == TRUE))
			xUIsetwidgetcolor( b->Wgbuttons[i], &keycol );
		else if ((b->fieldtype[i] == INPNEWLEVEL) || (b->fieldtype[i] == SELMENUFIELD))
			xUIsetwidgetcolor( b->Wgbuttons[i], &nextmenucol );
		else if (b->fieldtype[i] == SELECTGRAFIELD  ||
				b->fieldtype[i] == SHOWGRAFIELD  ||
				b->fieldtype[i] == INPUTGRAFIELD)
			xUIsetwidgetcolor( b->Wgbuttons[i], &gracol );


		/*--- Create Edit field in same row/col ------------------------- */
		(void)sprintf(fez, "%s%s%d", ROWCOLBUTFIELD, FIELD, i);
		defwert = (char *)0;
		if (b->fieldtype[i] == SELMENUFIELD)
			translat = BMtransnoedit;
		else
			translat = BMedit;
		b->Wgfields[i] = xUIeditor( fez, rowcolfield, b->lines[i], b->columns[i],
		                       		 defwert, yposptr, space, translat);
		/*---- set callback on the pushbutton with selected field as parameter */
		XtAddCallback( b->Wgbuttons[i], XmNactivateCallback,
		              (XtCallbackProc)xBMmenubutton, (XtPointer) b->Wgfields[i] );
	}

	/*--- manage buttons and visible fields -------------*/
	XtManageChildren(b->Wgbuttons, nbItems );
	for (i=0;  i<nbItems;  i++ )
	{
		ac = 0;
		XtSetArg(arglist[ac], XmNwidth, maxwidth); ac++;
		XtSetValues(b->Wgbuttons[i], arglist, ac);
		XtOverrideTranslations(b->Wgbuttons[i], BMfielddelete);
		XtOverrideTranslations(b->Wgbuttons[i], softkeytrans);
		XtOverrideTranslations(b->Wgfields[i],  softkeytrans);
		if (b->fieldtype[i] != INPNEWLEVEL)
			XtManageChild(b->Wgfields[i] );
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMbutfieldClear
 *					-update fields texts already build
 *					-
 *  In:			- ptr to  BOOKMENU   
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMbutfieldClear( BOOKMENU *b )
{
	int			i, nbItems ;

	/*---- inits ------*/
	nbItems = b->nbitems; 	
 
	/*---- delete field text ------------*/
	for (i= 0; i<nbItems; i++ )
		XmTextSetString( b->Wgfields[i], "" );

	b->olditems = nbItems;
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMbutfieldGetText ()
 *					-get menu strings out of fields (tabs in strings are filtered) 
 *					-each field text is ended with \t
 *  In:			-the menu, a buffer where to write
 *  out:			-
 *  Return:		-number of chars read 
 *---------------------------------------------------------------------------
 */
long xBMbutfieldGetText( BOOKMENU *b, char *buffer)
{
	int			i, j;
	long			totlen = 0;
	int			len;
	char			*pstr, *dest;
	char			*ptext;

	dest = buffer; 
	for ( i=0 ; i < b->nbitems; i++ )
	{
		ptext = XmTextGetString( b->Wgfields[i] );
		len = strlen( ptext );
		if (len < RECLAENGE)
		{
			for (j=0, pstr=ptext; j<len; j++)
			{
#ifdef COMPILE
				if ((*pstr =='\t') || (*pstr =='\n'))		/* filter out \t, \n */
					*dest++ = ' ';
				else
#endif
					*dest++ = *pstr;
				pstr++;
			}
			*dest++ = _MPSYMB_TAB;					/* field-string tab separator */
			totlen += (len+1); 
		}
		else
			return(0);
		XtFree((void *)ptext);
	}
	return( totlen );
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMbutfieldDestroy ()
 *					-remove all allocations for an menu Area class
 *					-
 *  In:			-area to delete
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMbutfieldDestroy ( BOOKMENU *b )
{
	/*---- it's an instance of BOOKMENU ----*/
	xBMmenuDestroy ( b );
}


/*S------------------------ STATIC FUNCTIONS ------------------------------*/

/*F--------------------------------------------------------------------------
 *  Function:	xBMpadButtonLabels ()
 *					-pad blanks to align button labels strings  
 *					-
 *  In:			- nb of labels, label index in label struct
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static void  xBMpadButtonLabels( int nbItems, int labix)
{
	extern char			*xbmLabelTable[][XBMLABMAXTEXTS];		/* xbm */  

	int	i, j, k, labelchars;

	/*---- find longest label ------------------*/
	for (j=0, labelchars=0; j < nbItems; j++)
	{
		k = strlen( xbmLabelTable[labix][j]);
		labelchars = labelchars > k ? labelchars : k ;     /* keep longest */
	}
	/*--- space padding till longest label size ----*/
	for (j=0; j<nbItems; j++)
	{
		for (k=strlen( xbmLabelTable[labix][j]); k<labelchars; k++)
		{
			xbmLabelTable[labix][j][k] = ' ';
		}
		xbmLabelTable[labix][j][labelchars] = (char)0;
	}
}

