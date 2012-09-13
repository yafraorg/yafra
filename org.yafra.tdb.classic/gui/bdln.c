/*D************************************************************
 * Modul:		GUI - BM dialog		bdln.c
 *
 *					Create a dln-user menu (Dienstleistungsnehmer)
 *					to capture identity and such informations
 *
 * Functions:	
 * Callbacks:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bdln.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";


/*E------------------------ EXTERNAL  --------------------------------------*/
extern int			xBMscan(char *ps, char *pd, char delim );
extern char			dlnTestBuffer[_BMBUFFERMAX];

	extern MENUAREA 	sexArea ;
	extern MENUAREA 	reduc1Area ;
	extern MENUAREA 	reduc2Area ;
	extern MENUAREA 	typeArea ;



/*P------------------------ PROTOTYPES --------------------------------------*/
static int			xBMdlnParse(char *buffer); 
static void 		xBMdlnKeeptextSet();
static void 		xBMdlnKeeptextGet();


/*G------------------------ GLOBAL VARIABLES --------------------------------*/
Boolean	keepDlnFlag = False; 
char		keepDlnBuffer[2048] = {'\0'} ;



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnPopup ()
 *					-called by BMmain to create a dln popup
 *  In:			-the parent widget 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void  xBMdlnPopup(Widget parent)
{
	extern unsigned char	actiontoggle;
	extern BOOKMENU 	bm_menu[]; 

	Widget		Wdln;
	BOOKMENU		*b; 

	/*--- inits --------------------*/ 
	b = &bm_menu[_BMDLNIX];

	/*--- add it -------------------*/
	xBMmenuActiveAdd( _BMDLNIX);

	/*--- check presence -----------*/ 
	if ( ! b->Wgpopup )
	{
		/*--- first create one ------*/
		Wdln = xBMdlnPopupCreate(parent);
		if (Wdln == NULL)
			return ; 
		else
		{
			b->Wgpopup = Wdln; 
			/*--- fill with DBI data --------------*/
			keepDlnFlag = False;
			xBMdlnPopupUpdate();
		} 
	}
	else 
	{	 
		/*--- update with new values --------------------------------*/
/*		XtUnmapWidget(b->Wgpopup);   */
		xBMdlnPopupUpdate();
/*		XtMapWidget(b->Wgpopup);     */
	}

	xBMtoggle( b->Wgpopup, (XtPointer) actiontoggle, NULL);
	/*--- popup existent menu, set current objects and numbers ------*/
	b->openedmenu = TRUE;
	XtPopup(b->Wgpopup, XtGrabNone);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnPopupCreate ()
 *					-create shell, bulletinboard, frames, titles
 *					-create pushbuttons and fields 
 *					-
 *  In:			-parent can be toplevel or BM menu, a menu struct  
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
Widget xBMdlnPopupCreate (Widget parent)
{
	extern char			*xbmLabelTable[][XBMLABMAXTEXTS];		/* xbm !*/  
	extern BOOKMENU 	bm_menu[]; 
	extern MENUAREA 	sexArea ;
	extern MENUAREA 	reduc1Area ;
	extern MENUAREA 	reduc2Area ;
	extern MENUAREA 	typeArea ;

	Widget	popup;									/* main widget */
	Widget	board, framemgr, rowcolmgr;
	Widget	rowcolact ;
	Widget	frame[_DLN_AREAS];
	char		bez[_CHAR30+1] ;
	Arg		arglist[10];
	int		ac;
	int		i, j, g, state, nbItems, status ;

	/*--- Shell --------------------------------------*/ 
	ac = 0;
	XtSetArg(arglist[ac], XmNtitle, LABEL_DLNTITLE ); ac++;
	XtSetArg(arglist[ac], XmNallowShellResize, TRUE); ac++;
	XtSetArg(arglist[ac], XmNmwmFunctions, MWM_FUNC_MOVE); ac++;
	XtSetArg(arglist[ac], XmNmwmDecorations, MWM_DECOR_BORDER|MWM_DECOR_TITLE|MWM_DECOR_MENU); ac++;
	popup = XtCreatePopupShell(OPTIONSHELL, topLevelShellWidgetClass, parent, arglist, ac);

	/*--- Bulletinboard ------------------------------*/
	(void)sprintf(bez, "%s%d", BOARD, _BMDLNNR);
	board = XtCreateManagedWidget(bez, xmBulletinBoardWidgetClass, popup, 0, 0);
	/*--- General Frame with parts -------------------*/
	(void)sprintf(bez, "%s%d", FRAMEMGR, _BMDLNNR);
	framemgr = XtCreateManagedWidget(bez, xmFrameWidgetClass, board, 0, 0);
	(void)sprintf(bez, "%s%d", ROWCOLMGR, _BMDLNNR);
	rowcolmgr = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, framemgr, 0, 0);

	/*--- Frames and areas creation ------------------*/
	(void)sprintf(bez, "%s%d", FRAMEMENU, _BMDLNNR);

	/*--- Sex Area ---------*/
	frame[0] = xUIframelabel(rowcolmgr, NULL, bez, xbmLabelTable[_DLN_FRAME][1]);
	xBMdlnSexCreate(   frame[0], &sexArea );
	sexArea.Wglink2 = frame[0];

	/*--- Button-fields ----*/
	frame[1] = xUIframelabel(rowcolmgr, NULL, bez, xbmLabelTable[_DLN_FRAME][2]);
	xBMbutfieldCreate( frame[1], &bm_menu[_BMDLNIX], _DLN_NBBUTTONS, _DLN_MENU );    
	bm_menu[_BMDLNIX].Wglink = frame[1];

	/*--- Reduction --------*/
	frame[2] = xUIframelabel(rowcolmgr, NULL, bez, xbmLabelTable[_DLN_FRAME][3]);
	xBMdlnReducCreate( frame[2], &reduc1Area );
	sexArea.Wglink2 = frame[2];

	/*--- Dln type ---------*/
	frame[3] = xUIframelabel(rowcolmgr, NULL, bez, xbmLabelTable[_DLN_FRAME][4]);
	xBMdlnTypeCreate(  frame[3], &typeArea );
	typeArea.Wglink2 = frame[3];

	/*--- Action bar, and DB mode toggle -------------*/
	frame[4] = xUIframelabel(rowcolmgr, NULL, bez, xbmLabelTable[_DLN_FRAME][5]);
	rowcolact = xBMactionbar( frame[4], &bm_menu[_BMDLNIX] );

	/*--- action toggle -DB mode  --------------------*/
	frame[5] = xUIframelabel(rowcolmgr, NULL, bez, xbmLabelTable[_DLN_FRAME][6]);
	xBMcreatetoggle(frame[5], &bm_menu[_BMDLNIX]);

	return(popup);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnPopupUpdate ()
 *					-parse buffer from DB
 *					-update number of items (buttons, toggles, radiobuttons...)
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnPopupUpdate ()
{
	extern unsigned char	actiontoggle;
	extern BOOKMENU 	bm_menu[]; 
	extern MENUAREA 	sexArea ;
	extern MENUAREA 	reduc1Area ;
	extern MENUAREA 	reduc2Area ;
	extern MENUAREA 	typeArea ;

	int		status ;
	BOOKMENU	*b;

	/*-- inits -------------*/
	b = &bm_menu[_BMDLNIX] ;

	/*---- Get menu format from DB buffer ------------------------------------*/ 
	status = xBMdlnParse ( comm.buffer );              /* new one from db */
	if (status != 0)
		perror("\nxBMdln: Invalid DB comm buffer or no memory allocated  \n");
	else 
	{
		/*--- update area's items ---------*/
		xBMdlnSexUpdate( &sexArea );
		xBMdlnTypeUpdate( &typeArea );
		xBMdlnReduc1Update( &reduc1Area );
	}

	/*--- Restore the text for Dln name --*/ 
	if ((keepDlnFlag) && (actiontoggle == INSERT))
		xBMdlnKeeptextSet();
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnSelectionReset ()
 *					-reset / clear all selected parameters 
 *					-
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnSelectionReset ()
{
	extern MENUAREA 	sexArea ;
	extern MENUAREA 	reduc1Area ;
	extern MENUAREA 	reduc2Area ;
	extern MENUAREA 	typeArea ;

	/*---- Get menu format from DB buffer ------------------------------------*/ 
	xBMdlnSexReset( &sexArea );
	xBMdlnReduc1Reset( &reduc1Area );
/*	xBMdlnTypeReset( &typeArea );    */        /***** not necessary to reset */

	keepDlnFlag = False;
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnPopupDestroy ()
 *					-remove all constructed stuff of menu and areas
 *
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnPopupDestroy ()
{
	extern BOOKMENU 	bm_menu[]; 
	extern MENUAREA 	sexArea ;
	extern MENUAREA 	reduc1Area ;
	extern MENUAREA 	reduc2Area ;
	extern MENUAREA 	typeArea ;

	/*---- free area stuff ---------------*/ 
	if (bm_menu[_BMDLNIX].Wgpopup)
	{
		xBMdlnSexDestroy( &sexArea );
		xBMdlnTypeDestroy( &typeArea );
		xBMdlnReduc1Destroy( &reduc1Area );
		/*---- free dln menu stuff ------------*/ 
		xBMbutfieldDestroy( &bm_menu[_BMDLNIX] ); 
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnGetResults()
 *					-get user choices out of areas
 *					-areaNb \n  item_string_label  \n
 *					-
 *  In:			-
 *  out:			-
 *  Return:		-nb of char in buffer
 *---------------------------------------------------------------------------
 */
int xBMdlnGetResults(void)
{
	extern ApplicationData app_data;
	extern long		maxoutcomm;
	extern char		*outcomm;
	extern BOOKMENU 	bm_menu[]; 
	extern MENUAREA 	sexArea ;
	extern MENUAREA 	reduc1Area ;
	extern MENUAREA 	reduc2Area ;
	extern MENUAREA 	typeArea ;

	int		i, len, totlen, nbreduc ;
	int      found;
	char	   *pBuf ;
	char		conv[10];
	BOOKMENU	*b;

	/*--- inits -------------*/
	b = &bm_menu[_BMDLNIX] ;

	/*--- check for buffer size -----------------------------*/
	totlen = _BMBUFFERMAX ;
	outcomm = (char *)xUIalloc( (void *)outcomm, &maxoutcomm,
										 app_data.maxdataout, totlen, sizeof(char) );
	pBuf = outcomm ; 

	/*--- Number of areas and button-fields --*/
	i = (_DLN_AREAS - 3) +  b->nbitems ;           /* minus butfield, actionbar, toggles */  
	len = sprintf(pBuf, "%d", i);
	pBuf += len; 
	*pBuf++ = _MPSYMB_CR ;

	/*--- Sex _DLN_SEX -----------------------*/
	found = FALSE;
	for ( i=0; i< sexArea.nbitems ; i++)  
		{
		if (sexArea.select[i] == 1 )
			{
			found = TRUE;
			break; 
			}
		}
	if (found == TRUE)
		{
		len = strlen(sexArea.labels[i]);
		if (len > 0)
			{
			strncpy(pBuf, sexArea.labels[i], len);
			pBuf += len;
			}
		}
	*pBuf++ = _MPSYMB_TAB ;

	/*--- butfi _DLN_BUTTONS -----------------*/
	pBuf += xBMbutfieldGetText( b, pBuf);   
	xBMdlnKeeptextGet();                     /* keep the texts for next dln */


	/* ---- reduction1  _DLN_REDUC1 ----------*/
	nbreduc = 0;
	for ( i=0; i< reduc1Area.nbitems ; i++)  
		{
		if (reduc1Area.select[i] == 1)
			{
			nbreduc++ ;
			len = strlen(reduc1Area.labels[i]);
			if (len > 0)
				{
				strncpy (pBuf, reduc1Area.labels[i], len);
				pBuf += len;
				}
			*pBuf++ = _MPSYMB_CR ;
			}
		}
	if (nbreduc > 0)                              /* no \t at end of reduc */
		pBuf--;
	*pBuf++ = _MPSYMB_TAB ;


	/*---- dln type  _DLN_TYPE (one-of) ------------*/
	found = FALSE;
	for ( i=0; i< typeArea.nbitems ; i++)  
		{
		if (typeArea.select[i] == 1 )
			{
			found = TRUE;
			break; 
			}
		}
	if (found == TRUE)
		{
		len = strlen(typeArea.labels[i]);
		if (len > 0)
			{
			strncpy(pBuf, typeArea.labels[i], len);
			pBuf += len;
			}
		}
	*pBuf++ = _MPSYMB_TAB ;


	*pBuf++ = _MPSYMB_NULL ;
	return( strlen(outcomm)); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnKeeptextReset()
 *					-reset the flag and the buffer 
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void 	xBMdlnKeeptextReset()
{

	keepDlnBuffer[0] = 0;
	keepDlnFlag = False; 
}



/*************************** STATIC FUNCTIONS *******************************/

/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnParse ()
 *					-get the menu format for DLN, prepare structs for update
 *					-areaNb \n  itemNb \n label \t label \n
 *					-
 *  In:			-the buffer to parse
 *  out:			-
 *  Return:		-status code
 *---------------------------------------------------------------------------
 */
static int  xBMdlnParse (char *buffer)
{
	extern BOOKMENU 	bm_menu[]; 
	extern MENUAREA 	sexArea ;
	extern MENUAREA 	reduc1Area ;
	extern MENUAREA 	reduc2Area ;
	extern MENUAREA 	typeArea ;

	int		i, j, nb, nbItems ;
	char	   fieldtext[_CHAR200] ; 			/* menu field transit */
   int 	   ret, f2;                    /* fields */
	char	   *pBuf, *labelPtr ;
	char		rec[_CHAR80];
	char		temp[_CHAR80];
	BOOKMENU	*b;

	/*-- inits -------------*/
	b = &bm_menu[_BMDLNIX] ;

	/*---- scan buffer for DLN formatting -----------*/
	ret = 0 ; 
	pBuf = buffer ;
	while (*pBuf != '\0' )  
	{
		/*---- get area id ------------- */
		pBuf += xBMscan (pBuf, rec, '\n' );
		nb = atoi (rec);
		if (nb == 0)
			return (_NOTOK); 
		switch (nb)					/*--- read all labels '\0'added */
		{
			case _DLN_SEX :
				pBuf += xBMscan (pBuf, rec, '\n' );
				f2 = atoi (rec);
				ret = xBMdlnSexSize(f2, &sexArea);
				if (ret == _NOTOK)
					return (_NOTOK); 
				for ( i=0; i<f2 ; i++)
				{  
					pBuf += xBMscan (pBuf, sexArea.labels[i], '\t' );
					pBuf += xBMscan (pBuf, temp,              '\t' );
					sexArea.select[i] = (temp[0] == '0')? 0: 1;       /*ascii2bin*/
				}
				break;
 
			case _DLN_BUTTONS : 
				/*--- number of buttons ------------------*/  
				pBuf += xBMscan (pBuf, rec, '\n' );
				f2 = atoi (rec);								/* f2=nb of scrolled buttons */
				for ( i=0; i<f2 ; i++)
				{
					pBuf += xBMscan (pBuf, fieldtext, '\t' );
					XmTextSetString( b->Wgfields[i], fieldtext );
				}
				break;
 
			case _DLN_REDUC1 :
				pBuf += xBMscan (pBuf, rec, '\n' );
				f2 = atoi (rec);
				ret = xBMdlnReducSize( f2, &reduc1Area );
				if (ret == _NOTOK)
					return (_NOTOK); 
				for ( i=0; i<f2 ; i++)
				{  
					pBuf += xBMscan (pBuf, reduc1Area.labels[i], '\t' );
					pBuf += xBMscan (pBuf, temp,                 '\t' );
					reduc1Area.select[i] = (temp[0] == '0')? 0: 1;       /*ascii2bin*/
				}
				break;
 
			case _DLN_TYPE :
				pBuf += xBMscan (pBuf, rec, '\n' );
				f2 = atoi (rec);
				ret = xBMdlnTypeSize(f2, &typeArea);					/* init menu area */
				if (ret == _NOTOK)
					return (_NOTOK); 
				for ( i=0; i<f2 ; i++)  
				{  
					pBuf += xBMscan (pBuf, typeArea.labels[i], '\t' ); 
					pBuf += xBMscan (pBuf, temp,               '\t' );
					typeArea.select[i] = (temp[0] == '0')? 0: 1;       /*ascii2bin*/
				}
				break;
 
			default : 
				return (_NOTOK);
		}/*switch*/
	}
	return (NULL); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnKeeptextGet()
 *					-get user button text 
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static void 	xBMdlnKeeptextGet()
{
	extern BOOKMENU 	bm_menu[]; 

	BOOKMENU	*b;
	int		len; 

	/*-- inits ---------------*/
	b = &bm_menu[_BMDLNIX] ;

	/*-- get field texts -----*/
	len = xBMbutfieldGetText( b, keepDlnBuffer);   
	keepDlnBuffer[len] = 0;
	keepDlnFlag = True; 
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnKeeptextSet()
 *					-Set user button text, only ONE is restaured 
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static void 	xBMdlnKeeptextSet()
{
	extern BOOKMENU 	bm_menu[]; 

	int		i;
	char 		*pBuf; 
	char	   fieldtext[_CHAR200] ; 			/* menu field transit */
	BOOKMENU	*b;

	/*-- inits -------------*/
	b = &bm_menu[_BMDLNIX] ;

	/*-- fill ONLY first, not all _DLN_NBBUTTONS ---------*/
	pBuf = keepDlnBuffer;
	for ( i=0;  i<1  ; i++)
	{
		pBuf += xBMscan (pBuf, fieldtext, '\t' );
		XmTextSetString( b->Wgfields[i], fieldtext );
	}
}



