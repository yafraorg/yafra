/*D***********************************************************
 * Modul:		GUI - dialog			uwidgets.c
 *
 *					Count number of realized and managed(mapped) widgets 
 *					(assumes the flag mappedWhenManaged is true)
 *					Build an array with those widgets
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/uwidgets.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: uwidgets.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:04:49  ja
 general version

 * Revision 1.7  94/02/18  10:45:00  10:45:00  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.6  93/10/23  11:08:31  11:08:31  ja (Jean-Marc Adam)
 * no entry
 * 
 * Revision 1.5  93/08/21  00:29:08  00:29:08  ja (Jean-Marc Adam)
 * update
 * 
 * Revision 1.4  93/05/04  18:14:56  18:14:56  ja (Jean-Marc Adam)
 * "rev"
 * 
 * Revision 1.3  93/03/05  07:39:38  07:39:38  ja ()
 * "Header description"
 * 
 * Revision 1.2  93/01/03  21:54:00  21:54:00  mw ()
 * "Update"
 * 
*/
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uwidgets.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";



int xUIwidgets( Widget *wid)
{
	extern Widget		toplevel;
	extern Widget		selectpopup;
	extern GRAWIDGETS grawidgets;
	extern GRAGLOB		graglob;
	extern MENU			menu[];
	extern BOOKMENU	bm_menu[];
	extern SELECTLIST	*selectList ;
	extern TWINLIST	*twinList ;
	extern Widget		Woption;		
	extern Boolean		openedoption;		
	extern MENU			glob;

	Widget	aWidget ;
	int		i;
	int		anzwidgets = 0;


	/*---- Toplevel --------------------*/
	if (toplevel && glob.openedmenu) {
		wid[anzwidgets++] = toplevel;
	}

	/*---- Graphics --------------------*/
	if (grawidgets.shell && graglob.openedshell) {
		wid[anzwidgets++] = grawidgets.shell;
	}
	if (grawidgets.palette && graglob.openedpalette) {
		wid[anzwidgets++] = grawidgets.palette;
	}
	if (grawidgets.bookmain && graglob.openedbookmain) {
		wid[anzwidgets++] = grawidgets.bookmain;
	}

	/*---- Option ----------------------*/
	if (Woption && openedoption) {
		wid[anzwidgets++] = Woption;
	}

	/*---- Menus -----------------------*/
	for (i=0; i<ANZ_MENU; i++)
	{
		if (menu[i].popup && menu[i].openedmenu )
			wid[anzwidgets++] = menu[i].popup;
	}

	/*---- Booking menus ---------------*/
	for (i=0; i<ANZ_BMMENU; i++)
	{
		if (bm_menu[i].Wgpopup && bm_menu[i].openedmenu)
			wid[anzwidgets++] = bm_menu[i].Wgpopup;
	}

#ifdef COMPILE
	/*---- SelectList ------------------*/
	if (selectpopup && XtIsRealized(selectpopup) && XtIsManaged(selectpopup)) {
		wid[anzwidgets++] = selectpopup;
	}

	/*---- Twin-list -------------------*/
	if (twinList)
		aWidget = twinList->Wgpopup;
		if ( aWidget && XtIsRealized(aWidget) && XtIsManaged(aWidget) ) 
			wid[anzwidgets++] = aWidget;

	/*---- Select-list -----------------*/
	if (selectList)
		aWidget = selectList->Wgpopup;
		if ( aWidget && XtIsRealized(aWidget) && XtIsManaged(aWidget) ) 
			wid[anzwidgets++] = aWidget ;
#endif


	return(anzwidgets);
}
