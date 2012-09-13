/**************************************************************
 * Modul:     GUI - dialog						  ucomm.c
 * 
 *            Actions performed when commit (weiter) is pressed 
 *            The menu proper action is defined in menu[]
 * 
 * Functions: ucomm   from "commit work" button 
 *            xUIact    send action (INS/DEL/UPD) to DBI
 *   
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ucomm.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


/*P------------------------ PROTOTYPES -------------------------------------*/
static XtCallbackProc xUIact(Widget, XtPointer, XtPointer);



/*F--------------------------------------------------------------------------
 *  Function:	xUIcomm ()
 *					from "commit work" button, ask for delete or update entry
 *									
 *  In:			standard callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIcomm(Widget w, XtPointer closure, XtPointer c2)
{
	extern unsigned char actiontoggle;
   extern char *			xuiLabelTable[][XUILABMAXTEXTS];  

	MENU *a;

	a = (MENU *)closure;

	/*--- No question for output menu ----*/
	if (a->typ == _OUTPUT)
	{
		xUIact(w, closure, 0);
		return; 
	}


	/*-- Sicherheitsabfrage vor Mutationen --------------------*/
	if (actiontoggle == MPDELETE)
		xUIdeffrage (LABEL_YES, LABEL_NO, LABEL_DELETEENTRY,
		            (XtCallbackProc)xUIact, closure, a->popup);

	else if (actiontoggle == UPDATE)
		xUIdeffrage (LABEL_YES, LABEL_NO, LABEL_UPDATEENTRY,
		            (XtCallbackProc)xUIact, closure, a->popup);

	else
		xUIact(w, closure, 0);          /* execute commit action */
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIact ()
 *					from xUIcomm
 *					get user results out of menu fields and send to DBI
 *					Clear the twin lists which were considered as part of the menu
 *  In:			standard callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static XtCallbackProc xUIact(Widget w, XtPointer x, XtPointer y)
{
	extern unsigned char actiontoggle;
	extern int  aktmenuz;
	extern int	aktmenu[];
	extern int  aktmenuobj[];
	extern MENU	menu[];
	extern char *outcomm;
	extern TWINLIST	*twinList;

	MENU	*a;
	int	len;
	
	/*--- get menu field strings for DBI ------------------------*/
	a = &menu[aktmenu[aktmenuz]];
	len = xUImenustr(a);

	/*--- Kommunikation fuer INPUT, UPDATE oder DELETE in SQL-DB */
	COMMTYP   = ACTION;
	ACTIONTYP = actiontoggle;
	MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
	FELDNR    = NULL;
	(void)xUItalkto(SEND, outcomm, len);

	/*--- Clear the lists after sending to DataBank -------------*/
	xUICtwinDeleteItems( twinList);
}
