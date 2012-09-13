/*D***********************************************************
 * Modul:     GUI - dialog                             uinfo.c
 *
 *            Ask DB to send informations for info window
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uinfo.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";



/*F--------------------------------------------------------------------------
 *  Function:	xUIinfo ()
 *					Info has been selected with softkey or in action bar
 *					Send a trigger to DB 
 *  In:			standard callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIinfo( Widget w, XtPointer closure, XtPointer wdata)
{
	extern unsigned char actiontoggle;
	extern int     		bm_ix;
	extern int  aktmenuz;
	extern int  aktmenuobj[];
	extern int	aktmenu[];
	extern MENU	menu[];
	extern char *outcomm;

	BOOKMENU		*b;
	MENU			*a;
	int			len;
	
	MENUNR  = NULL;
	/*--- Find MENU number ------------------*/
	b = xBMmenuActive();
	if (b)  {
		/*--- get menu-field strings ---*/
		len = xBMmenustr(b);

		if (bm_ix == _BMCATIX)
			MENUNR  = (unsigned char) _RESERVATION  ;
		else if (bm_ix == _BMDLNIX)
			MENUNR  = (unsigned char) _BMDLN  ;
		else
			MENUNR  = NULL ;
	}
	else
	{
		/*--- get menu-field strings ---*/
		if (aktmenuz < ANZ_MENU+1 && aktmenuz > -1)
			{
			a = &menu[aktmenu[aktmenuz]];
			if (a->typ > _UNDEF)
				{
				len = xUImenustr(a);
				MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
				}
			}
	}

	COMMTYP   = INFO;
	ACTIONTYP = actiontoggle;
	FELDNR    = NULL;
	(void)xUItalkto( SEND, outcomm, len);
}

