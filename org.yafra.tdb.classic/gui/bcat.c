/*D************************************************************
 * Modul:		GUI - BM dialog		bcat.c
 *
 *					Booking action is performed by choosing a category.
 *					This module creates a category menu with prices 
 *					and free places.
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bcat.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


/*E------------------------ EXTERNAL  --------------------------------------*/
extern int	xBMscan(char *ps, char *pd, char delim );
extern char catTestBuffer[_BMBUFFERMAX];


/*P------------------------ PROTOTYPES --------------------------------------*/
static int					xBMcatParse( char *buffer); 


/*G------------------------ GLOBAL VARIABLES --------------------------------*/



/*F--------------------------------------------------------------------------
 *  Function:	xBMcatPopup 
 *					-called by BMmain to create a cat popup
 *  In:			-the parent widget 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMcatPopup(Widget parent)
{
	extern unsigned char	actiontoggle;
	extern	BOOKMENU 	bm_menu[]; 

	Widget		Wcat;
	BOOKMENU		*b; 

	/*--- inits -----------------------------*/ 
	b = &bm_menu[_BMCATIX];

 	/*--- add menu --------------------------*/
	xBMmenuActiveAdd( _BMCATIX);

	/*--- check presence ------*/ 
	if ( ! b->Wgpopup )
		{
		/*--- first create one ----------*/
		Wcat = xBMcatPopupCreate(parent);
		if (Wcat == NULL)
			return ; 
		else
			{
			b->Wgpopup = Wcat; 
			/*--- update labels with DBI-parsed parameters --*/
			xBMcatPopupUpdate();
			} 
		}
	else 
		{
		/*--- update only with new values in hide mode --*/
		XtUnmapWidget(b->Wgpopup);
		xBMcatPopupUpdate();
		XtMapWidget(b->Wgpopup);
		}
	/***** there are no toggles defined *******/

	/*--- popup existent menu, set current objects and numbers ------*/
	b->openedmenu = TRUE;
	XtPopup(b->Wgpopup, XtGrabNone);
}
 


/*F--------------------------------------------------------------------------
 *  Function:	xBMcatPopupCreate 
 *					-create shell, bulletinboard, frames, titles
 *					-create pushbuttons and fields 
 *					-
 *  In:			-parent can be toplevel or BM menu, a menu struct  
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
Widget xBMcatPopupCreate (Widget parent)
{
	extern char			*xbmLabelTable[][XBMLABMAXTEXTS];		/* xbm !*/  
	extern	MENUAREA 	recallArea;
	extern	SCROLLAREA 	scrollArea ;
	extern	BOOKMENU 	bm_menu[]; 

	Widget	popup;									/* main widget */
	Widget	board, framemgr, rowcolmgr;
	Widget	radiobox, rowcolbutton ;
	Widget	rowcolact;
	Widget	frame[_CAT_AREAS];
	char		bez[_CHAR30+1] ;
	Arg		arglist[10];
	int		ac;
	int		i, j, g, state, nbItems, status ;


	/*--- LEVEL 0 create a Shell ---------------------------------------------*/ 
	ac = 0;
	XtSetArg(arglist[ac], XmNtitle, LABEL_CATTITLE ); ac++;
	XtSetArg(arglist[ac], XmNallowShellResize, TRUE); ac++;
	XtSetArg(arglist[ac], XmNmwmFunctions, MWM_FUNC_MOVE); ac++;
	XtSetArg(arglist[ac], XmNmwmDecorations, MWM_DECOR_BORDER|MWM_DECOR_TITLE|MWM_DECOR_MENU); ac++;
	popup = XtCreatePopupShell(OPTIONSHELL, topLevelShellWidgetClass, parent, arglist, ac);
	/*---LEVEL 1 create a Bulletinboard --------------*/
	(void)sprintf(bez, "%s%d", BOARD, _BMCATNR);
	board = XtCreateManagedWidget(bez, xmBulletinBoardWidgetClass, popup, 0, 0);
	/*--- LEVEL 2 create general Frame with parts ----*/
	(void)sprintf(bez, "%s%d", FRAMEMGR, _BMCATNR);
	framemgr = XtCreateManagedWidget(bez, xmFrameWidgetClass, board, 0, 0);
	(void)sprintf(bez, "%s%d", ROWCOLMGR, _BMCATNR);
	rowcolmgr = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, framemgr, 0, 0);

	/*--- Frames -------------------------------------*/
	(void)sprintf(bez, "%s%d", FRAMEMENU, _BMCATNR);

	/*--- Recall area ------*/ 
	frame[0] = xUIframelabel(rowcolmgr, NULL, bez, xbmLabelTable[_CAT_FRAME][1]);
	xBMcatRecallCreate(frame[0], &recallArea );
	recallArea.Wglink2 = frame[0];

	/*--- Scroll Area ------*/
	frame[1] = xUIframelabel(rowcolmgr, NULL, bez, xbmLabelTable[_CAT_FRAME][2]);
	xBMscrollerCreate(frame[1], &scrollArea, True );  

	/*--- Button-field -----*/
	frame[2] = xUIframelabel(rowcolmgr, NULL, bez, xbmLabelTable[_CAT_FRAME][3]);
	xBMbutfieldCreate( frame[2], &bm_menu[_BMCATIX], _CAT_NBBUTTONS, _CAT_MENU );    
	bm_menu[_BMCATIX].Wglink = frame[2];

	/*----Action bar, and DB mode toggle -------------*/
	frame[3] = xUIframelabel(rowcolmgr, NULL, bez, xbmLabelTable[_CAT_FRAME][4]);
	rowcolact = xBMactionbar(frame[3], &bm_menu[_BMCATIX] );
	return(popup);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMcatPopupUpdate 
 *					-parse buffer from DB which updates nb of items
 *					-update labels for buttons, toggles, radiobuttons...
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMcatPopupUpdate ()
{
	extern	BOOKMENU 	bm_menu[]; 
	extern	MENUAREA 	recallArea;
	extern	SCROLLAREA 	scrollArea ;

	int		status ;
	BOOKMENU	*b;

	/*-- inits -------------*/
	b = &bm_menu[_BMCATIX] ;

	/*---- Get menu format from DB buffer ------------------------------------*/ 
	status = xBMcatParse ( comm.buffer );
	if (status != 0)
		perror("\nxBMcat: Invalid DB comm buffer or no memory allocated  \n");
	else 
	{
		/*--- update area's items -------*/
		xBMcatRecallUpdate (&recallArea);
		xBMscrollerUpdate (&scrollArea);
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMcatSelectionReset 
 *					-parse buffer from DB which updates nb of items
 *					-update labels for buttons, toggles, radiobuttons...
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMcatSelectionReset ()
{
	extern	SCROLLAREA 	scrollArea ;

	/*---- Get menu format from DB buffer ------------------------------------*/ 
	xBMscrollerReset (&scrollArea);     
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMcatPopupDestroy 
 *					-remove all constructed stuff of menu and areas
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMcatPopupDestroy ()
{
	extern	BOOKMENU 	bm_menu[]; 
	extern	MENUAREA 	recallArea;
	extern	SCROLLAREA 	scrollArea ;

	/*---- free area stuff ---------------*/ 
	if (bm_menu[_BMCATIX].Wgpopup)
	{
		xBMcatRecallDestroy (&recallArea );
		xBMscrollerDestroy (&scrollArea );

		/*---- free bm_menu[_BMCATIX] stuff ------------*/ 
		xBMbutfieldDestroy( &bm_menu[_BMCATIX] ); 
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMcatGetResults
 *					-get user choices out of areas
 *					-areaNb \n  item  \t .... \n
 *					-
 *  In:			-
 *  out:			-
 *  Return:		-nb of char in buffer
 *---------------------------------------------------------------------------
 */
int xBMcatGetResults(void)
{
	extern ApplicationData app_data;
	extern long		maxoutcomm;
	extern char		*outcomm;
	extern	MENUAREA 	recallArea;
	extern	SCROLLAREA 	scrollArea ;
	extern	BOOKMENU 	bm_menu[]; 

	int		i, k, len, totlen ;
	char	   *pBuf, *ptext ;
	BOOKMENU *b;

	b = &bm_menu[_BMCATIX];

	/*---- check for buffer size -----------------------------*/
	totlen = _BMBUFFERMAX ;
	outcomm = (char *)xUIalloc( (void *)outcomm, &maxoutcomm, app_data.maxdataout, totlen, sizeof(char) );
   pBuf = outcomm ; 

/*!!! find a better solution for Number of fields !!!*/

	/*---- Number of fields [13] -------------------------*/
	*pBuf++ = '1';                     
	*pBuf++ = '3';
	*pBuf++ = _MPSYMB_CR ;

 	/*---- DL bezeichnung -------------------------*/
	strcpy (pBuf, recallArea.labels[1]); 
	pBuf += strlen(recallArea.labels[1]);
	*pBuf++ = _MPSYMB_TAB ;
 	/*---- Buchungs id ----------------------------*/
	strcpy (pBuf, recallArea.labels[3]); 
	pBuf += strlen(recallArea.labels[3]);
	*pBuf++ = _MPSYMB_TAB ;
 	/*---- buchung ref ----------------------------*/
	strcpy (pBuf, recallArea.labels[5]); 
	pBuf += strlen(recallArea.labels[5]);
	*pBuf++ = _MPSYMB_TAB ;

	/*---- Cat id from scrolled list --------------*/
	for ( i=0; i< scrollArea.nbitems ; i++)  
		if (scrollArea.select[i] == 1)  break; 		/* find index */
	if (i<scrollArea.nbitems)  
		{
		len = strlen(scrollArea.catid[i]); 				/* get id */
		for (k=0;  k<len; k++)
			*pBuf++ = scrollArea.catid[i][k];
		}  
	*pBuf++ = _MPSYMB_TAB ;

	/*---- DLN  --------------------------------*/
	ptext = XmTextGetString( b->Wgfields[0] );
	strcpy( pBuf, ptext ); 
	pBuf += strlen( ptext);
	XtFree( (void *)ptext); 
	*pBuf++ = _MPSYMB_TAB ;

	/*---- Res status --------------------------*/
	ptext = XmTextGetString( b->Wgfields[1] );
	strcpy( pBuf, ptext ); 
	pBuf += strlen( ptext);
	XtFree( (void *)ptext); 
	*pBuf++ = _MPSYMB_TAB ;

	/*---- DLT ---------------------------------*/
	ptext = XmTextGetString( b->Wgfields[2] );
	strcpy( pBuf, ptext ); 
	pBuf += strlen( ptext);
	XtFree( (void *)ptext); 
	*pBuf++ = _MPSYMB_TAB ;

	/*---- DLTT type----------------------------*/
	ptext = XmTextGetString( b->Wgfields[3] );
	strcpy( pBuf, ptext ); 
	pBuf += strlen( ptext);
	XtFree( (void *)ptext); 
	*pBuf++ = _MPSYMB_TAB ;

	/*---- DLG parts (twin!) -------------------*/
	ptext = XmTextGetString( b->Wgfields[4] );
	if ((len = strlen(ptext)) > 0)                 /* only if something */
		pBuf += xUICtwinGetItems( pBuf);            /* special twin      */
	XtFree( (void *)ptext); 
	*pBuf++ = _MPSYMB_TAB ;

	/*---- Start date --------------------------*/
	ptext = XmTextGetString( b->Wgfields[5] );
	strcpy( pBuf, ptext ); 
	pBuf += strlen( ptext);
	XtFree( (void *)ptext); 
	*pBuf++ = _MPSYMB_TAB ;

	/*---- End date ----------------------------*/
	ptext = XmTextGetString( b->Wgfields[6] );
	strcpy( pBuf, ptext ); 
	pBuf += strlen( ptext);
	XtFree( (void *)ptext); 
	*pBuf++ = _MPSYMB_TAB ;

	/*---- Contigent/Allotment -----------------*/
	ptext = XmTextGetString( b->Wgfields[7] );
	strcpy( pBuf, ptext ); 
	pBuf += strlen( ptext);
	XtFree( (void *)ptext); 
	*pBuf++ = _MPSYMB_TAB ;

	/*---- Requests text -----------------------*/
	ptext = XmTextGetString( b->Wgfields[8] );
	strcpy( pBuf, ptext ); 
	pBuf += strlen( ptext);
	XtFree( (void *)ptext); 
	*pBuf++ = _MPSYMB_TAB ;

	*pBuf++ = '\0' ;
	return( strlen(outcomm)); 
}




/*S********************* STATIC FUNCTIONS **********************************/

/*F--------------------------------------------------------------------------
 *  Function:	xBMcatParse 
 *					-get the menu format for category
 *					-areaNb \n  itemNb \n label \t label \n
 *					-
 *  In:			-the buffer to parse
 *  out:			-
 *  Return:		-status code
 *---------------------------------------------------------------------------
 */
static int  xBMcatParse (char *buffer)
{
	extern	BOOKMENU 	bm_menu[]; 
	extern	MENUAREA 	recallArea;
	extern	SCROLLAREA 	scrollArea ;

	int		i, j, nb, nbItems ;
	char	   fieldtext[_CHAR200] ; 			/* menu field transit */
   int 	   ret, f2;								/* scan fields */
	char	   *pBuf, *labelPtr ;
	char		rec[_CHAR200];
	char		temp[_CHAR200];
	BOOKMENU	*b;

	/*-- inits -------------*/
	b = &bm_menu[_BMCATIX] ;

	/*---- scan buffer for CAT formatting -----------*/
	pBuf = buffer ;
	while (*pBuf != '\0' )  
	{
		/*---- get area id ------------- */
		pBuf += xBMscan (pBuf, rec, '\n' );
		nb = atoi (rec);
		if (nb == 0)
			return (_NOTOK); 

		switch (nb)
		{
			case _CAT_RECALLAB :
				pBuf += xBMscan (pBuf, rec, '\n' );
				f2 = atoi (rec);
				/*---- effective nb is double of DBI ----------*/
				ret = xBMcatRecallSize (f2 * 2,  &recallArea );
				if (ret == _NOTOK)
					return (_NOTOK); 
				/*--- DBI texts for ODD labels only -----------*/  
				for ( i=0; i<f2 ; i++)
					pBuf += xBMscan (pBuf, recallArea.labels[(i*2)+1], '\t');
				break;

			case _CAT_SCROLL :
				/*--- Header title -----------------*/  
				pBuf += xBMscan (pBuf, scrollArea.headlabel, '\n');
				/*--- Choices  !number can't exceed _BMCATNR !---*/  
				pBuf += xBMscan (pBuf, rec, '\n' );
				f2 = atoi (rec);								/* f2=nb of scrolled buttons */
				ret = xBMscrollerSize (f2, &scrollArea );
				if (ret == _NOTOK)
					return (_NOTOK); 
				for ( i=0; i<f2 ; i++)
				{  
					pBuf += xBMscan (pBuf, scrollArea.catid[i],  '\t' );
					pBuf += xBMscan (pBuf, scrollArea.colors[i], '\t' );
					pBuf += xBMscan (pBuf, scrollArea.labels[i], '\t' );
					pBuf += xBMscan (pBuf, temp, '\n' );
					scrollArea.select[i] = (temp[0] == '0')? 0: 1;      /*ascii2bin*/
				}
				/*-------- Buf++ NO skip /n ! ---*/
				break;

			case _CAT_FIELDS :
				/*--- number of buttons ------------------*/  
				pBuf += xBMscan (pBuf, rec, '\n' );
				f2 = atoi (rec);								/* f2=nb of scrolled buttons */
				for ( i=0; i<f2 ; i++)
				{
					pBuf += xBMscan (pBuf, fieldtext, '\t' );
					XmTextSetString( b->Wgfields[i], fieldtext );
				}
				break;

			default : 
				return (_NOTOK);
		}/*switch*/
	}
	return (NULL); 
}


