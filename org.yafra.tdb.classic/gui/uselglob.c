/************************************************************** 
 * Modul:     GUI - dialog                           uselglob.c                        
 *                                        
 *            After press on a button of global menu:
 *            Read strings from Global menu and 
 *            Ask DBI process to bring items for user choice
 *                                        
 *                                                          
 * Copyright: yafra.org, Basel, Switzerland   
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uselglob.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xUIselglob 
 *            After press on a button of global menu:
 *            Read strings from Global menu and 
 *            Ask DBI process to bring items for user to choose 
 *  In:			-std cb params
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIselglob( Widget w, XtPointer closure, XtPointer data)
{
	extern MENU		glob;
	extern int		globfield;

	/*--- set global field, will be used later as switcher ---*/
	globfield = xUIfieldnr(&glob, (Widget)closure);

	/*--- Auswahl von bereits vorhandenen Items verlangen */
	COMMTYP   = SELECT;
	ACTIONTYP = GLOBAL;
	MENUNR    = (unsigned char)_GLOBALMENU;
	FELDNR    = (unsigned char)globfield ;
	(void)xUItalkto(SEND, 0, 0);
}
