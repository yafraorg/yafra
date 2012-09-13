/*D************************************************************ 
 * Modul:     GUI - dialog						uchoose.c                                   
 *                                                         
 *            Choose an item from the select popup        
 *            Send selected text to DBI
 *                                                         
 * Functions: uchooseitem()  xUIchoosedown()                                
 *                                                           
 * Copyright: yafra.org, Basel, Switzerland  
 **************************************************************/

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/uchoose.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: uchoose.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:36  ja
 general version

 * Revision 1.9  94/02/18  10:40:11  10:40:11  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.8  93/11/17  09:27:40  09:27:40  ja (Jean-Marc Adam)
 * Cancel button (xUIchoosedown) is like a choose with 
 * choosenflag false.
 * 
 * Revision 1.7  93/11/11  16:36:53  16:36:53  ja (Jean-Marc Adam)
 * xUIchoosedown: general popdown of select list
 * global menu re-enables the fields
 * global selection sends the text to update db 
 * 
 * Revision 1.6  93/11/10  08:28:24  08:28:24  ja (Jean-Marc Adam)
 * rcsid
 * 
 * Revision 1.5  93/08/21  00:27:19  00:27:19  ja (Jean-Marc Adam)
 * update
 * 
 * Revision 1.4  93/06/22  16:47:44  16:47:44  mw (Administrator)
 * work.
 * 
 * Revision 1.3  92/12/03  00:46:31  00:46:31  mw ()
 * "new xUIselectpopdown handling"
 * 
 * Revision 1.2  92/08/24  17:03:20  17:03:20  mw ()
 * "talkto bei chooseitem ueberfluessig !
 * -> xUItalkto wird nicht mehr ausgefuehrt"
 * 
*/
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uchoose.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";



/*F---------------------------------------------------------------------
 *	Function:	xUIchooseitem 
 *					-User has selected an item, 
 *					-
 *	In:			-std callback params
 *					-
 *-----------------------------------------------------------------------
 */
XtCallbackProc xUIchooseitem(Widget w, XtPointer closure, XtPointer call_data)
{
	extern Boolean		chosenflag;
	extern XtPointer	para;
	extern int			aktmenuz;
	extern int			aktmenu[];
	extern int			aktfield[];
	extern char			rec[];
	extern int			globfield;
	extern MENU			glob, menu[];

	XmListCallbackStruct *cb = (XmListCallbackStruct *)call_data;
	char		*str;
	Arg		wargs[5];

	/*--- Get text -----------------------*/
	XmStringGetLtoR(cb->item, XmSTRING_DEFAULT_CHARSET, &str);
	if (strlen(str) < RECLAENGE)
		(void)sprintf( rec, "%s", str);
	else
		rec[0] = 0;
	XtFree((void *)str);

	/*--- Update text in fields ----------*/
	XtSetArg(wargs[0], XmNvalue, rec);
	if (globfield == -1 )
		XtSetValues(menu[aktmenu[aktmenuz]].field[aktfield[aktmenuz]], wargs, 1);
	else
		XtSetValues(glob.field[globfield], wargs ,1);

	/*--- set for later check ---*/
	chosenflag = TRUE ; 
}



/*F---------------------------------------------------------------------
 *	Function:	xUIchoosedown 
 *					-default action, return or double click in select list
 *					-re-enable menu sensitivity
 *					-for global, the selectpopup list is handled by xUIinput
 *	In:			-std callback params
 *					-
 *-----------------------------------------------------------------------
 */
XtCallbackProc xUIchoosedown( Widget w, XtPointer closure, XtPointer call_data)
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


	/*--- close the selection list -----------------------*/
	XtPopdown( selectpopup);

	/*--- For who is result? -----------------------------*/
	if ((MENUNR == _GLOBALMENU) || (globfield != -1))
	{
		/*--- save selection in global data ---------*/
		f = globfield;
		text = XmTextGetString(glob.field[f]);
		ptr = xUIglobmember(f);
		(void)sprintf(ptr, "%s", text);       /* cp from private area to member*/
		XtFree((void *)text);
		xUImenufeld( &glob, glob.field[globfield], TRUE, TRUE, FALSE, TRUE);

		/*--- send always item to Databankprocess */
		chosenflag = FALSE;
		COMMTYP   = GLOBAL;
		ACTIONTYP = GLOBSEND;
		MENUNR    = (unsigned char)_GLOBALMENU;
		FELDNR    = (unsigned char)f;
		(void)xUItalkto(SEND, (char *)&globdata, sizeof(globdata));
	}
	else                  /* popdown on the normal UI MENU */
	{
		n = aktmenu[aktmenuz];
		f = aktfield[aktmenuz];
		a = &menu[n];
		a->editfeld = TRUE;
		a->alreadywrite = FALSE;
		xUImenufeld( a, a->field[f], TRUE, TRUE, FALSE, TRUE);
		globfield = -1;

		/*--- sende den gewaehlten Eintrag an Datenbankprozess */
		if (chosenflag)
		{
			/*--- get choice which was buffered in field ---*/
			text = XmTextGetString(a->field[f]);
			chosenflag = FALSE;
			COMMTYP   = CHOOSE;
			ACTIONTYP = actiontoggle;
			MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
			FELDNR    = (unsigned char)f;
			(void)xUItalkto(SEND, text, strlen(text));
			XtFree((void *)text);
		}
	}

}


/*F---------------------------------------------------------------------
 *	Function:	xUIchoosecancel 
 *					-button cancel is pressed, keep field text  
 *					-
 *	In:			-std callback params
 *					-
 *-----------------------------------------------------------------------
 */
XtCallbackProc xUIchoosecancel( Widget w, XtPointer closure, XtPointer call_data)
{

	/*--- Keep field text and go out ----*/
	xUIchoosedown( w, 0, 0); 
}

