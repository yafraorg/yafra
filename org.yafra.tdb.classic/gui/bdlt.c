/*D************************************************************
 * Modul:		GUI - BM dialog						bdlt.c
 *
 *					Create, update DLT menu 
 *
 *
 * Functions:
 *				
 * Statics:
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */



#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bdlt.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";


/*E------------------------ EXTERNAL  --------------------------------------*/
extern int	xBMscan( char *ps, char *pd, char delim );
extern char dltTestBuffer[_BMBUFFERMAX];
extern	int				bm_aktfield;
extern	int				bm_aktmenuz ;
extern	int				bm_aktmenu[] ;
extern	int			bm_ix;								/* active menu index */
extern	BOOKMENU 	bm_menu[]; 
extern	MENUAREA 	dltRecallArea;
extern	SCROLLAREA 	dltBestofArea ;


/*P------------------------ PROTOTYPES --------------------------------------*/
static int					xBMdltParse(char *buffer); 


/*G------------------------ GLOBAL VARIABLES --------------------------------*/



/*F--------------------------------------------------------------------------
 *  Function:	xBMdltPopup ()
 *					-called by BMmain to create a cat popup
 *  In:			-the parent widget 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void  xBMdltPopup(Widget parent)
{
	extern unsigned char	actiontoggle;

	Widget		Wcat;
	BOOKMENU		*b; 

	/*---- inits ------*/ 
	b = &bm_menu[_BMDLTIX];
	actiontoggle = INSERT ;

	xBMmenuActiveAdd( _BMDLTIX);
 
	/*---- check presence ------*/ 
	if ( ! b->Wgpopup )
	{
		/*--- first create one ----------*/
		Wcat = xBMdltPopupCreate(parent);
		if (Wcat == NULL)
			return ; 
		else
		{
			b->Wgpopup = Wcat; 
			/*---- update labels with DBI-parsed parameters --*/
			xBMdltPopupUpdate();
		} 
	} else 
	{	 
		/*--- update only with new values in hide mode --*/
		XtUnmapWidget(b->Wgpopup);
		xBMdltPopupUpdate();
		XtMapWidget(b->Wgpopup);
	}
	/*--- popup existent menu, set current objects and numbers ------*/
	b->openedmenu = TRUE;
	XtPopup(b->Wgpopup, XtGrabNone);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdltPopupCreate ()
 *					-create shell, bulletinboard, frames, titles
 *					-create pushbuttons and fields 
 *					-
 *  In:			-parent
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
Widget xBMdltPopupCreate( Widget parent)
{
	extern char			*xbmLabelTable[][XBMLABMAXTEXTS];
	extern char			*xuiLabelTable[][XUILABMAXTEXTS];

	Widget		popup;									/* main widget */
	Widget		board, framemgr, rowcolmgr;
	Widget		radiobox, rowcolbutton ;
	Widget		wexitframe;
	Widget		frame[_DLT_AREAS];
	char			bez[_CHAR30+1] ;
	Arg			args[10];
	int			ac;
	int			i, j, g, state, nbItems, status ;
	XmString		xmStr; 
	BOOKMENU		*b; 

	/*---- inits ------*/ 
	b = &bm_menu[_BMDLTIX];

	/*--- LEVEL 0 create a Shell ---------------------------------------------*/ 
	ac = 0;
	XtSetArg(args[ac], XmNtitle,            LABEL_DLTTITLE ); ac++;
	XtSetArg(args[ac], XmNallowShellResize, TRUE );           ac++;
	XtSetArg(args[ac], XmNmwmFunctions,     MWM_FUNC_MOVE );  ac++;
	XtSetArg(args[ac], XmNmwmDecorations, MWM_DECOR_BORDER|MWM_DECOR_TITLE|MWM_DECOR_MENU); ac++;
	popup = XtCreatePopupShell(OPTIONSHELL, topLevelShellWidgetClass, parent, args, ac);
	/*---LEVEL 1 create a Bulletinboard --------------*/
	(void)sprintf(bez, "%s%d", BOARD, _BMDLTNR);
	board = XtCreateManagedWidget(bez, xmBulletinBoardWidgetClass, popup, 0, 0);
	/*--- LEVEL 2 create general Frame with parts ----*/
	(void)sprintf(bez, "%s%d", FRAMEMGR, _BMDLTNR);
	framemgr = XtCreateManagedWidget(bez, xmFrameWidgetClass, board, 0, 0);
	(void)sprintf(bez, "%s%d", ROWCOLMGR, _BMDLTNR);
	rowcolmgr = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, framemgr, 0, 0);

	/*--- LEVEL 3 create all frames -----------------------*/
	(void)sprintf(bez, "%s%d", FRAMEMENU, _BMDLTNR);
	for (i=0 ; i < _DLT_AREAS; i++ )
	{
		frame[i] = xUIframelabel( rowcolmgr, NULL, bez, xbmLabelTable[_DLT_FRAME][i+1] );
	}

	/*---- create areas structures -------------------------*/ 
	xBMscrollerCreate(frame[0], &dltBestofArea, False );   
	xBMbutfieldCreate( frame[1], &bm_menu[_BMDLTIX],  _DLT_NBBUTTONS, _DLT_MENU );    

	/*--- OK and Cancel buttons ---------*/
	wexitframe = xUIexitBar( rowcolmgr, 
					LABEL_OK,     (XtCallbackProc)xBMdltok,     (XtPointer)0,
					LABEL_CANCEL, (XtCallbackProc)xBMdltCancel, (XtPointer)0  );

	return(popup);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdltPopupUpdate ()
 *					-parse buffer from DB which updates nb of items
 *					-update labels for buttons, toggles, radiobuttons...
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdltPopupUpdate ()
{
	int		status ;
	BOOKMENU	*b;

	/*-- inits -------------*/
	b = &bm_menu[_BMDLTIX] ;

	/*---- Get menu format from DB buffer ------------------------------------*/ 
	status = xBMdltParse ( comm.buffer );
	if (status != 0)
		perror("\nxBMdlt: Invalid DB comm buffer or no memory allocated  \n");
	else 
	{
		/*--- update area's items -------*/
		xBMscrollerUpdate (&dltBestofArea);     
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdltPopupDestroy ()
 *					-remove all constructed stuff of menu and areas
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdltPopupDestroy()
{
	/*---- free all stuff ---------------*/ 
	if (bm_menu[_BMDLTIX].Wgpopup)
	{
		xBMscrollerDestroy (&dltBestofArea );       
		xBMbutfieldDestroy( &bm_menu[_BMDLTIX] ); 
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdltClearSlection ()
 *					-remove the user selection in dlt list 
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdltClearSlection()
{
	int	i; 

	/*---- free all stuff ---------------*/ 
	if (bm_menu[_BMDLTIX].Wgpopup)
	{
		for ( i=0; i< dltBestofArea.nbitems ; i++)  
			dltBestofArea.select[i] = 0;
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdltok ()
 *					ok has been pressed, end selection of dlt
 *
 *  In:			standard callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMdltok( Widget w, XtPointer x, XtPointer y)
{
	extern	char dltId[]; 

	int		i, len;
	char		*ptext;
	BOOKMENU	*b, *c;

	/*-- inits -------------*/
	b = &bm_menu[_BMDLTIX] ;
	c = &bm_menu[_BMCATIX] ;

	/*--- get index of selection  -------*/
	for ( i=0; i< dltBestofArea.nbitems ; i++)  
		if (dltBestofArea.select[i] == 1)
		  break; 

	if (i < dltBestofArea.nbitems)  
	{
		/*--- Bez -----*/
		if (c)
			XmTextSetString( c->Wgfields[_DLT_FIELD_DLT], dltBestofArea.labels[i] );
	}
	else
	{
		/*--- copy from dlt field ------*/
		ptext = XmTextGetString( b->Wgfields[0] );
		XmTextSetString( bm_menu[_BMCATIX].Wgfields[_DLT_FIELD_DLT], ptext );
		XtFree( (void *)ptext); 
	}

	/*-- popdown ------------*/
	XtPopdown(b->Wgpopup);
	b->enter = TRUE;
	b->editfeld = TRUE;
	b->openedmenu = FALSE;
	b->alreadywrite = FALSE;

	/*--- update world ------*/
	xBMmenuActiveRemove();
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdltCancel ()
 *					-pop down dlt menu, but NO destruction 
 *					-Nothing is performed for OTHER menus !
 *  In:			-Standard callback parameters
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMdltCancel( Widget w, XtPointer closure, XtPointer data)
{
	extern TWINLIST	*twinList;

	BOOKMENU	*b;

	/*-- inits -------------*/
	b = &bm_menu[_BMDLTIX] ;

	xBMdltClearSlection(); 

	/*-- popdown ------------*/
	XtPopdown(b->Wgpopup);
	b->enter = TRUE;
	b->editfeld = TRUE;
	b->openedmenu = FALSE;
	b->alreadywrite = FALSE;

	/*--- update world ------*/
	xBMmenuActiveRemove();
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdltParse ()
 *					-get the menu format for category
 *					-areaNb \n  itemNb \n label \t label \n
 *					-
 *  In:			-the buffer to parse
 *  out:			-
 *  Return:		-status code
 *---------------------------------------------------------------------------
 */
static int  xBMdltParse (char *buffer)
{
	int		i, j, nb, nbItems ;
	char	   labeltext[_LABELLEN+1] ; 
   int 	   ret, f2;                    /* fields */
	char	   *pBuf, *labelPtr ;
	char		rec[_CHAR200];
	char		trash[_CHAR200];

	/*---- scan buffer for CAT formatting -----------*/
	pBuf = buffer ;
	ret = _OK; 
	while (*pBuf != '\0' )  
	{
		/*---- get area id ------------- */
		pBuf += xBMscan (pBuf, rec, '\n' );
		nb = atoi (rec);
		if (nb == 0)
			return (_NOTOK); 

		switch (nb)
		{
			case _DLT_RECALLAB :								/* ???? must be removed!! */
				pBuf += xBMscan (pBuf, rec, '\n' );
				f2 = atoi (rec);
				/*--- DBI texts for ODD labels only -----------*/  
				for ( i=0; i<f2 ; i++)
					pBuf += xBMscan (pBuf, trash, '\t');
				pBuf++;		/* skip /n */
				break;

			case _DLT_BESTOF :
				pBuf += xBMscan (pBuf, rec, '\n' );
				f2 = atoi (rec);								/* f2=nb of scrolled buttons */
				ret = xBMscrollerSize (f2, &dltBestofArea );   
				if (ret == _NOTOK)
					return (_NOTOK); 
				for ( i=0; i<f2 ; i++)
				{  
					pBuf += xBMscan (pBuf, dltBestofArea.catid[i], '\t' );
					strcpy( dltBestofArea.colors[i], _DLT_COLOR );
					pBuf += xBMscan (pBuf, dltBestofArea.labels[i], '\n' );
				}
				/*-------- Buf++ NO skip /n ! ---*/
				break;
 
			default : 
				return (_NOTOK);

		}/*switch*/
	}
	return (NULL); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdltGetResults()
 *					-get user choices out of areas
 *					-areaNb \n  item  \t .... \n
 *					-
 *  In:			-
 *  out:			-
 *  Return:		-nb of char in buffer
 *---------------------------------------------------------------------------
 */
int  xBMdltGetResults ()
{
	extern ApplicationData app_data;
	extern long		maxoutcomm;
	extern char		*outcomm;

	int		i, k, len, totlen ;
	char	   *pBuf ;

	/*---- check for buffer size -----------------------------*/
	totlen = _BMBUFFERMAX ;
	outcomm = (char *)xUIalloc( (void *)outcomm, &maxoutcomm,
										 app_data.maxdataout, totlen, sizeof(char) );
   pBuf = outcomm ; 

	/*---- DL bezeichnung ------*/
	*pBuf++ = '1';
	*pBuf++ = '\n' ;
/*	strcpy( pBuf, dltRecallArea.labels[1]);    */
/*	pBuf += strlen( dltRecallArea.labels[1]);  */
	*pBuf++ = '\n' ;
  
	/*---- Dlt id --------------*/
	*pBuf++ = '2';
	*pBuf++ = '\n' ;
	for ( i=0; i< dltBestofArea.nbitems ; i++)  
		if (dltBestofArea.select[i] == 1)  break; 		/* find index */
	if (i<dltBestofArea.nbitems)  
	{
		/*--- Id --------------*/
		len = strlen(dltBestofArea.catid[i]); 				/* get id */
		for (k=0;  k<len; k++)
			*pBuf++ = dltBestofArea.catid[i][k];
		*pBuf++ = '\t' ;										/* no selection */
		/*--- Bez --------------*/
		len = strlen(dltBestofArea.labels[i]); 			/* get bez */
		for (k=0;  k<len; k++)
			*pBuf++ = dltBestofArea.labels[i][k];
	} else 
	{
		*pBuf++ = '\t' ;										/* no selection */
	}

	*pBuf++ = '\n' ;
	*pBuf++ = '\0' ;
	return( strlen(outcomm)); 
}








