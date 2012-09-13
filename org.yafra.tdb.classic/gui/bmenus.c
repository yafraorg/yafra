/*D************************************************************
 * Modul:		GUI - BM dialog		bmenus.c
 *
 *					Contains the BM menu declarations 
 *					plus common functions to all BM menus
 *
 * Functions:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>


static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bmenus.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";



/*E------------------------ EXTERNAL  ---------------------------------------*/


/*P------------------------ PROTOTYPES --------------------------------------*/


/*G------------------------ GLOBAL VARIABLES --------------------------------*/
int	bm_ix =  -1 ;						/* active menu index in array   */
int	bm_aktfield;						/* current field index          */ 
int	bm_aktmenuz = -1 ;				/* number of active bm_menus    */
int	bm_aktmenu[ANZ_BMMENU];			/* active menus                 */


/*--- DLN menu -----------------------------------------------*/
int IDENTtype[] = { SEDITFIELD, SEDITFIELD, SEDITFIELD, MEDITFIELD, MEDITFIELD, SELECTFIELD }; 
int IDENTupdt[] = {  True,       False,      False,      False,      False,      False      };
int IDENTinpt[] = {  True,       True,       True,       True,       True,       True       };
int IDENTline[] = {  1,          1,          1,          2,          2,          1          };
int IDENTcols[] = {  30,         30,         10,         70,         70,         30         };

	/*-- 7 inits must be null ---*/
MENUAREA 	sexArea = 		{ 0, 0, 0, 0, 0, 0, 0 };
MENUAREA 	reduc1Area =	{ 0, 0, 0, 0, 0, 0, 0 };
MENUAREA 	reduc2Area =	{ 0, 0, 0, 0, 0, 0, 0 };
MENUAREA 	typeArea =		{ 0, 0, 0, 0, 0, 0, 0 };



/*--- BOOK-CAT -----------------------------------------------*/
int CATEtype[] = { SELECTFIELD, SELECTFIELD,	SELECTGRAFIELD, SELECTFIELD, TWINSELFIELD, SEDITFIELD, SEDITFIELD, SELECTFIELD, MEDITFIELD	};
int CATEupdt[] = {  False    	, False			, False       , False       , False       , False     , False     , False      , False};
int CATEinpt[] = {  False     , True			, False       , True        , True        , True      , True      , False      , False};
int CATEline[] = {  1         , 1				, 1           , 1           , 1           , 1         , 1         , 1          , 3    };
int CATEcols[] = {  50    		, 30     		, 50          , 30     		 , 50          , 30        , 30        , 30         , 60   };

	/*-- 7 inits must be null ---*/
MENUAREA 	recallArea = 		{ 0, 0, 0, 0, 0, 0, 0 };
MENUAREA 	extraArea = 		{ 0, 0, 0, 0, 0, 0, 0 };

	/*-- 12 inits must be null ---*/
SCROLLAREA 	scrollArea = 		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };




/*--- DLT (CABINE) -------------------------------------------*/
int DLTRtype[] = { SELECTFIELD	};
int DLTRupdt[] = {  True     		};
int DLTRinpt[] = {  True    		};
int DLTRline[] = {  1       		};
int DLTRcols[] = {  30    			};

MENUAREA 	dltRecallArea = 		{ 0, 0, 0, 0, 0, 0 };
SCROLLAREA 	dltBestofArea = 		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };



/*----------------- BM menus array ------------------------------------*/
/* xBMinclude.h describes the menu structure */

BOOKMENU 		bm_menu[ANZ_BMMENU] =
{
	{ 0, xBMmenuAction, xUIhelp, 0, 0, 0, IDENTtype, IDENTupdt, IDENTinpt, IDENTline, IDENTcols,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0,  
     False, True, False, False, True },
	{ 0, xBMmenuAction, xUIhelp, 0, 0, 0, CATEtype, CATEupdt, CATEinpt, CATEline, CATEcols,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0,  
     False, True, False, False, True },
	{ 0, xBMmenuAction, xUIhelp, 0, 0, 0, DLTRtype, DLTRupdt, DLTRinpt, DLTRline, DLTRcols,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0,  
     False, True, False, False, True }
};




/*F--------------------------------------------------------------------------
 *  Function:	xBMmenuActiveAdd ()
 *					-Add a newly opened menu to world if it is not already done
 *  In:			-the menu index
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMmenuActiveAdd( int menuIndex)
{
	MENU		*a;

	/*--- update struct if different -----*/
	if (bm_ix != menuIndex)
	{  
		bm_aktmenuz++ ;
		bm_aktmenu[bm_aktmenuz] = menuIndex;  
	}

	/*--- set current index --------------*/
	bm_ix = menuIndex;

	/*--- Active field -------------------*/
	bm_aktfield = -1;

	/*--- Disable UI pulldown menus ------*/
	xUIpulldownSensitive( False); 
	xUIglobmenuSensitive( False); 

	/*--- Enable UI menu if present ------*/
	if ( a = xUImenuActive() )
	{
		a->enter = FALSE;
		a->editfeld = FALSE;
		a->alreadywrite = TRUE;
		xUImenufeld(a, NULL, FALSE, FALSE, FALSE, FALSE);
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMmenuActiveRemove ()
 *					-remove a menu from world
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMmenuActiveRemove()
{
	MENU		*a;

	/*--- remove and update struct ------*/
	bm_aktmenuz-- ;

	/*--- reset if last ------*/
	if (bm_aktmenuz == -1) 
		bm_ix = -1;
	else
		bm_ix = bm_aktmenu[bm_aktmenuz];

	/*--- Enable UI pulldown menus ------*/
	xUIpulldownSensitive( True); 
	xUIglobmenuSensitive( True); 


	/*--- Enable UI menu if present ------*/
	a = xUImenuActive();
	if (a)
	{ 
		a->editfeld = TRUE;
		a->alreadywrite = FALSE;
		xUImenufeld(a, NULL, TRUE, TRUE, FALSE, TRUE);
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMmenuActive ()
 *					-return current active menu
 *  In:			-
 *  out:			-
 *  Return:		-a ptr to menu
 *---------------------------------------------------------------------------
 */
BOOKMENU * xBMmenuActive()
{
	if (bm_aktmenuz >= 0) 
		return( &bm_menu[bm_ix]);
	else
		return(0); 
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMmenuAction ()
 *					from "commit work" button, ask for delete or update entry
 *									
 *  In:			standard callback parameters (closure = menu) 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMmenuAction(Widget w, XtPointer closure, XtPointer data)
{
   extern char *			xuiLabelTable[][XUILABMAXTEXTS];  
	extern unsigned char	actiontoggle;

	BOOKMENU	*b;

	b = (BOOKMENU *)closure;
	xBMmenuCommit(w, closure, 0);
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMmenuCommit ()
 *					from xUIcomm
 *
 *  In:			standard callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMmenuCommit( Widget w, XtPointer x, XtPointer y)
{
	extern char		*outcomm;
	extern int		aktmenuobj[];
	extern unsigned char	actiontoggle;

	int	len;

	/*--- Eah menu has proper action -------*/
	switch (bm_ix)
	{
		case _BMDLNIX : 							/* Dln menu  */ 
			len = xBMdlnGetResults(); 
			COMMTYP   = ACTION;
			MENUNR    = (unsigned char)_BMDLN ;
			break; 

		case _BMCATIX : 							/* Cat menu  */
			len = xBMcatGetResults(); 
			COMMTYP   = ACTION;
			MENUNR    = (unsigned char)_RESERVATION;
			break; 
	}

	/*--- Kommunikation fuer INPUT, UPDATE oder DELETE in SQL-DB */
	ACTIONTYP = actiontoggle;
	FELDNR    = NULL;
	(void)xUItalkto(SEND, outcomm, len);
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMpopdown ()
 *					-ask for question if necessery, bring menu down
 *					-
 *  In:			-Standard callback parameters, closure = dln menu
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMpopdown(Widget w, XtPointer closure, XtPointer wdata)
{ 
   extern char *		xuiLabelTable[][XUILABMAXTEXTS];  

	BOOKMENU		*b;

	b = (BOOKMENU *)closure;

	/*--- question ---------*/
	if (b->enter == FALSE || w == NULL)
		xUIdeffrage (LABEL_YES, LABEL_NO, LABEL_MENUEND,
		            (XtCallbackProc)xBMmenudown, closure, b->Wgpopup);
	else
		xBMmenudown( w, closure, 0);

}


/*F--------------------------------------------------------------------------
 *  Function:	xBMmenudown ()
 *					-pop down current bm menu, but NO destruction 
 *					-Nothing is performed for OTHER menus !
 *  In:			-Standard callback parameters, closure = bm menu
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMmenudown(Widget w, XtPointer closure, XtPointer data)
{
	extern TWINLIST	*twinList;

	BOOKMENU	*b;

	/*-- inits --------------*/
	b = (BOOKMENU *)closure;

	/*-- popdown ------------*/
	XtPopdown(b->Wgpopup);
	b->enter = TRUE;
	b->editfeld = TRUE;
	b->openedmenu = FALSE;
	b->alreadywrite = FALSE;

	/*--- free Twin select widget ---*/
	xUICtwinDestroy( twinList);
	twinList = 0;

	/*--- update world ------*/
	xBMmenuActiveRemove();
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMscan ()
 *					-get string with included blanks till delimiter
 *					-
 *  In:			-delimiter character
 *  out:			-ad of source, destination
 *  Return:		-nb of characters INCLUSIVE delim (no need to skip delim!)
 *---------------------------------------------------------------------------
 */
int  xBMscan (char *ps, char *pd, char delim )
{
	int	i;
 
	/*-- copy till delim ------- */
	for ( i=0; *ps != delim; i++ )  
		*pd++ = *ps++ ;
	*pd ='\0';
	i++; 					/* skip delim */
	return (i); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMmenuDestroy ()
 *					-remove all allocations for an menu Area class
 *					-
 *  In:			-area to delete
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMmenuDestroy ( BOOKMENU *b )
{
	int		i; 

	/*--- Destroy popup  --------*/
	if (b->Wgpopup)
	{
		XtDestroyWidget(b->Wgpopup);
		/*--- free memory --------*/
		XtFree((void *)b->Wgbuttons); 
		XtFree((void *)b->Wgfields); 
		/*---- reset labels allocations ------ */
		for (i=0; i< b->nbitems; i++ )
			XtFree((void *)b->labels[i]);
		XtFree((void *)b->labels);

		b->nbitems = 0;
		b->olditems = 0;
		b->Wglink = NULL;
		b->Wgpopup = NULL;	
		b->Wgbuttons = NULL;
		b->Wgfields = NULL;
		b->Wgtoggleinsert = NULL;
		b->Wgtogglesearch = NULL;
		b->Wgtoggledelete = NULL;	
		b->Wgbuttonhelp = NULL;
		b->Wgbuttonmenu = NULL;
		b->Wgbuttonact = NULL;
		b->Wgbuttonquit = NULL;
		b->openedmenu = FALSE;
	}
}




