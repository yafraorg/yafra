/*D************************************************************
 * Modul:		GRAPHIC							gwaitfor.c
 *
 *					Ask for DB booking status 
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwaitfor.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";



void xGRwait_for_zustand()
{
	extern MENU	    menu[];
	extern int      aktmenuz;
	extern int      aktmenu[];
	extern int      aktmenuobj[];
	extern int      holdfield;
	extern char     *outcomm;
	extern unsigned char actiontoggle;

	MENU			*a;
	BOOKMENU		*b; 
	long			len;

	/*--- get BM menu ----*/
	b = xBMmenuActive();

	if (b)
	{
		len = xBMmenustr(b);
		MENUNR  = (unsigned char) _RESERVATION;          /* bm_ix is _BMCATIX */
	}
	else
	{ 
		/*--- Auswahl von bereits vorhandenen Items verlangen */
		a = &menu[aktmenu[aktmenuz]];
		len = xUImenustr(a);
		MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
	}

	COMMTYP   = GRAREFRESH ;
	ACTIONTYP = actiontoggle;
	FELDNR    = NULL;
	(void)xUItalkto(SEND, outcomm, len);
}
