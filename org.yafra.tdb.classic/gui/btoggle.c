/*D************************************************************
 * Modul:     GUI - BM dialog        btoggle.c 
 *            
 *            Create DB mode toggles for BM menus
 *                                                            
 * Functions:
 * Callbacks: 
 *            
 *            
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/btoggle.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";



/*------------------------ PROTOTYPES -------------------------------------*/
XtCallbackProc	xBMtoggle(Widget w, XtPointer whichtoggle, XtPointer wdata);
 


/*F--------------------------------------------------------------------------
 *  Function:	xBMcreatetoggle ()
 *					-create DB operation toggles  
 *					-
 *  In:			-the parent widget, current BM menu 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMcreatetoggle( Widget parent, BOOKMENU *b  )
{
	extern OBJCOLORS boardcol;		       /* Board matrix Colorset */
	extern char			*xbmLabelTable[][XBMLABMAXTEXTS];		/* xbm !*/  
	extern char			*xuiLabelTable[][XUILABMAXTEXTS];
	extern unsigned char		actiontoggle;
	extern XtTranslations	softkeytrans;

	Widget		radiobox, child[3];
	char			bez[_CHAR30+1] ;
	Arg 			args[10];
	int			ac, i;
	Boolean		state;
	XmString		xmStr; 	

	/*--- inits ---*/
	(void)sprintf(bez, "%s%d", RADIOBOX, _BMDLNNR);
	ac = 0;
	XtSetArg(args[ac], XmNpacking, XmPACK_COLUMN); ac++;
	XtSetArg(args[ac], XmNnumColumns, 1); ac++;
	XtSetArg(args[ac], XmNorientation, XmHORIZONTAL); ac++;
	radiobox = XmCreateRadioBox( parent, bez, args, ac);	
	XtManageChild( radiobox);

	ac = 0;
	(void)sprintf(bez, "%s%d", TOGGLEINSERT, _BMDLNNR);
	xmStr = XmStringCreateSimple(LABEL_INSERTMODE);
	XtSetArg(args[ac], XmNlabelString, xmStr); ac++;
	state = (actiontoggle == INSERT)? True : False ; 
	XtSetArg(args[ac], XmNset, state); ac++;
	XtSetArg(args[ac], XmNselectColor, boardcol.select ); ac++;
	child[0] = XmCreateToggleButton( radiobox, bez, args, ac);
	XmStringFree( xmStr);
	b->Wgtoggleinsert = child[0] ;
	XtAddCallback( child[0], XmNvalueChangedCallback, (XtCallbackProc)xBMtoggle,
													             (XtPointer)INSERT);
	ac = 0;
	(void)sprintf(bez, "%s%d", TOGGLEUPDATE, _BMDLNNR);
	xmStr = XmStringCreateSimple(LABEL_UPDATEMODE);
	XtSetArg(args[ac], XmNlabelString, xmStr); ac++;
	state = (actiontoggle == UPDATE)? True : False ; 
	XtSetArg(args[ac], XmNset, state); ac++;
	XtSetArg(args[ac], XmNselectColor, boardcol.select ); ac++;
	child[1] = XmCreateToggleButton( radiobox, bez, args, ac);
	XmStringFree( xmStr);
	b->Wgtogglesearch = child[1] ;
	XtAddCallback( child[1], XmNvalueChangedCallback, (XtCallbackProc)xBMtoggle,
	          												    (XtPointer)UPDATE);
	ac = 0;
	(void)sprintf(bez, "%s%d", TOGGLEDELETE, _BMDLNNR);
	xmStr = XmStringCreateSimple(LABEL_DELETEMODE) ;
	XtSetArg(args[ac], XmNlabelString, xmStr ); ac++;
	state = (actiontoggle == MPDELETE)? True : False ;
	XtSetArg(args[ac], XmNset, state); ac++;
	XtSetArg(args[ac], XmNselectColor, boardcol.select ); ac++;
	child[2] = XmCreateToggleButton( radiobox, bez, args, ac);
	b->Wgtoggledelete = child[2];
	XmStringFree( xmStr); 
	XtAddCallback( child[2], XmNvalueChangedCallback, (XtCallbackProc)xBMtoggle,
	            												 (XtPointer)MPDELETE);

	for (i=0; i<3; i++)
		XtOverrideTranslations( child[i], softkeytrans);
	XtManageChildren( child, 3);
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMtoggle ()
 *					-create DB operation toggles  
 *					-
 *  In:			-std cb parameters 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMtoggle(Widget w, XtPointer whichtoggle, XtPointer wdata)
{
	extern unsigned char	actiontoggle;
	extern BOOKMENU			bm_menu[];
	extern int					bm_ix;
	extern int				holdfield;
	extern OBJCOLORS		orgcol, keycol;

	BOOKMENU			*b;
	register			int	i, j;
	XmToggleButtonCallbackStruct *state = (XmToggleButtonCallbackStruct *)wdata;

	/*---- look for which menu ----------*/
	b = &bm_menu[bm_ix]; 

/*	holdfield = -1;	*/
	if ((actiontoggle == (unsigned char)whichtoggle) && (wdata != NULL))
		return;
	else if (wdata == NULL)
		{
		actiontoggle = (unsigned char)whichtoggle;
		switch (actiontoggle)
			{
			case INSERT:
				XtVaSetValues(b->Wgtoggleinsert, XmNset, True, NULL);
				XtVaSetValues(b->Wgtogglesearch, XmNset, False, NULL);
				XtVaSetValues(b->Wgtoggledelete, XmNset, False, NULL);
				break;
			case UPDATE:
				XtVaSetValues(b->Wgtoggleinsert, XmNset, False, NULL);
				XtVaSetValues(b->Wgtogglesearch, XmNset, True, NULL);
				XtVaSetValues(b->Wgtoggledelete, XmNset, False, NULL);
				break;
			case MPDELETE:
				XtVaSetValues(b->Wgtoggleinsert, XmNset, False, NULL);
				XtVaSetValues(b->Wgtogglesearch, XmNset, False, NULL);
				XtVaSetValues(b->Wgtoggledelete, XmNset, True, NULL);
				break;
			}
		}
	else
		actiontoggle = (unsigned char)whichtoggle;

	/*--- change color of SELECTFIELD pushbuttons fields ----------*/
	switch (actiontoggle)
	{
		case INSERT:
			for (i = 0; i < b->nbitems ; i++)
				if (b->suchfields[i] == TRUE)
					xUIsetwidgetcolor( b->Wgbuttons[i], &orgcol );
			break;
		case UPDATE:
		case MPDELETE:
			for (i = 0; i < b->nbitems; i++)
				if (b->suchfields[i] == TRUE)
					xUIsetwidgetcolor( b->Wgbuttons[i], &keycol );
			break;
	}
}



/***************************** STATIC FUNCTIONS *****************************/
