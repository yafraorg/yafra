/*D***********************************************************
 * Modul:		GUI - dialog				useldown.c                                    
 *                                                            
 *					For both Global and other menus:                                               
 *					cancel the selection, popdown the window
 *                                                            
 *	Functions:	xUIselectpopdown                                                           
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/useldown.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: useldown.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:04:30  ja
 general version

 * Revision 1.8  94/02/18  10:44:46  10:44:46  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.7  93/11/17  09:25:24  09:25:24  ja (Jean-Marc Adam)
 * Common function xUIchoosedown for Global and normal menus
 * 
 * Revision 1.6  93/11/10  08:31:24  08:31:24  ja (Jean-Marc Adam)
 * rcsid
 * 
 * Revision 1.5  93/08/21  00:28:38  00:28:38  ja (Jean-Marc Adam)
 * update
 * 
 * Revision 1.4  93/05/04  18:13:58  18:13:58  ja (Jean-Marc Adam)
 * "rev"
 * 
 * Revision 1.3  93/03/04  09:56:51  09:56:51  mw ()
 * Work
 * 
 * Revision 1.2  92/12/03  00:46:53  00:46:53  mw ()
 * "new xUIselectdown handling"
 * 
*/

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/useldown.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";



/*F---------------------------------------------------------------------
 *	Function:	xUIselectpopdown 
 *					-cancel selection process, (right mouse key), clear selections
 *					-re-enable menu sensitivity
 *	In:			-std XtActionProc params
 *					-
 *-----------------------------------------------------------------------
 */
XtActionProc xUIselectpopdown( Widget w, XEvent* event, String* s, Cardinal* m)
{
	extern Boolean		chosenflag;
	extern XtPointer  para;
	extern GLOBDATA   globdata;
	extern MENU       menu[];
	extern MENU       glob;
	extern Widget     selectpopup;
	extern int        aktmenuz;
	extern int        aktmenu[];
	extern int        aktmenuobj[];
	extern int        aktfield[];
	extern int        globfield;
	extern unsigned char actiontoggle;

	MENU		*a;
	int		f, n;
	char		*ptr;
	char		*text;

	/*--- For who is Cancelling ? -------------------*/
	if ((MENUNR == _GLOBALMENU) || (globfield != -1))
	{
		/*--- clear field and go LIKE normal choose ----*/
		f = globfield;
		XmTextSetString( glob.field[f], "");
	}
	else                  /* normal UI MENU */
	{
		n = aktmenu[aktmenuz];
		f = aktfield[aktmenuz];
		a = &menu[n];
		XmTextSetString( a->field[f], "");
	}

	/*-- close selection and update DB is necessary ----*/
	xUIchoosedown( w, 0, 0); 
}

