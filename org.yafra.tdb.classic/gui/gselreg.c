/*D************************************************************
 * Modul:		GRAPHIC							gselreg.c
 *
 *					User chooses a region in select list	
 *					Let it define the regionpoints
 *					when closed create a colored region polygon
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gselreg.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: gselreg.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:05  ja
 general version

 * Revision 1.5  94/02/18  10:38:29  10:38:29  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.4  93/10/23  11:02:57  11:02:57  ja (Jean-Marc Adam)
 * no entry
 * 
 * Revision 1.3  93/08/21  00:26:07  00:26:07  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gselreg.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";



void xGRselect_region(XtPointer Info, int tog)
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
   extern char			*xuiLabelTable[][XUILABMAXTEXTS];
	extern Display *display;
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB graglob;
	extern REGOBJ  *regObj;
	extern XPoint   punkt[];

	static REGOBJ  *aktregion;
	static long		aktnummer;
	static XPoint	lastpunkt;
	
	XmAnyCallbackStruct  *any;
	static XmListCallbackStruct *list;
	
	XEvent			*event;
	REGIONPOINT    regpkt;
	int				typ, nr, i;
	Boolean			ok, ende, exists;
	char				*str, *end;
	long				*ind;
	long				anzchildren;
	
	typ = graglob.eingabe;
	nr = typ-1;
   if (typ == 0)
	{
		list = (XmListCallbackStruct *)Info;
		exists = False;
		/*--- is item already selected ? --------------------*/
		for (i=0;  i < list->selected_item_count;  i++) {
			if (XmStringCompare(list->item, list->selected_items[i])) {
				exists = True;
			}
		}
		/*--- Find region index --------------*/
		XmStringGetLtoR(list->item, XmSTRING_DEFAULT_CHARSET, &str);
		end = strstr(str, TRENNER);
		if (end)
			*end = 0;
		aktnummer = xGRfind_region_name(str);           /*find index*/
		if (aktnummer == NOVATER) {
			XmListDeselectItem(grawidgets.select, list->item);
			XtFree((void *)str);
			xUIfehler(XGRREGIONNOTDEFINED, grawidgets.shell);
			return;
		}

		aktregion = &regObj[aktnummer];
		/*--- a selected item has been deselected by user, delete it */
		if (!exists)
		{
			XmListSelectPos(grawidgets.select, aktnummer+1, False);
			XtFree((void *)str);
			XmTextSetString(grawidgets.frage, "");
			XmTextSetString(grawidgets.antwort, "");
			graglob.eingabe = 0;
			graglob.aktbox = BUTTONNONE;
			graglob.akttog = BUTTONNONE;
			anzchildren = xGRfind_regionchildren(aktregion, &ind, REGDEF);
			free((void *)ind);
			if (anzchildren > 0) {
				xUIfehler(XGRREGIONHASCHILDREN, grawidgets.shell);
				return;
			}
			xUIdeffrage(LABEL_YES, LABEL_NO, LABEL_DELETEENTRY,
							(XtCallbackProc)xGRdelete_region, (XtPointer)aktregion,
							grawidgets.shell);
			return;
		}
		/*--- Region will be defined in next steps ------------*/
		XmListDeselectItem(grawidgets.select, list->item);
		graglob.antwort = (char *)malloc(strlen(aktregion->Regionname)+1);
		strcpy(graglob.antwort, aktregion->Regionname);
		if (aktregion->anzEckpunkte >= 1) 
			aktregion->Eckpunktnum[1] = 0;      /*allow retry closure after 'ende' */
		aktregion->anzEckpunkte = 0;
		XmTextSetString(grawidgets.frage, FRAGE_REGION0);
		graglob.eingabe = 1;
		XtFree((void *)str);
	}

	else if (typ > 0 && typ<MAXREGPOINTS)
	{
		any = (XmAnyCallbackStruct *)Info;
		event = (XEvent *)any->event;
		/*--- Coordinates must be valid ----------------*/
		ok = xGRget_koord(event, &punkt[0]);
		if (!ok) {
			if (nr > 0) {
				punkt[0].x = lastpunkt.x;
				punkt[0].y = lastpunkt.y;
			}
			xUIfehler(XGRNOPOINTFOUND, grawidgets.shell);
			return;
		}

		/*--- Coordinates must be a regionpoint --------*/
		regpkt.p.x = punkt[0].x;
		regpkt.p.y = punkt[0].y;
		regpkt.n = 0;
		xGRfind_regionpoint(&regpkt, MODE_KOR);
		if (regpkt.n <= 0){
			if (nr > 0) {
				punkt[0].x = lastpunkt.x;
				punkt[0].y = lastpunkt.y;
			}
			xUIfehler(XGRNOREGIONPOINTFOUND, grawidgets.shell);
			return;
		}

		/*--- Regionpoint must have parent or be father -*/
		ok = False;
		if (aktregion->indVater != NOVATER &&
			 regObj[aktregion->indVater].region) {
			if (XPointInRegion(regObj[aktregion->indVater].region,
									 event->xbutton.x, event->xbutton.y))
				ok=True;
		} else if (aktregion-regObj == 0) {
			ok = True;
		}
		if (!ok) {
			if (nr > 0) {
				punkt[0].x = lastpunkt.x;
				punkt[0].y = lastpunkt.y;
			}
			xUIfehler(XGRNOTINVATERREGION, grawidgets.shell);
			return;
		}

		/*--- Regionpoint must have parent or be father -*/
		ende = False;
		if (typ != 1) {
			/*--- Point must be different from previous points ---*/
			ok = True;
			for (i=2;  i<typ-1;  i++) {
				if (aktregion->Eckpunktnum[i] == regpkt.n)
					ok = False;
			}
			if (!ok) {
				if (nr > 0) {
					punkt[0].x = lastpunkt.x;
					punkt[0].y = lastpunkt.y;
				}
				xUIfehler(XGRNOREGION, grawidgets.shell);
				return;
			}
			/*--- Have we closed the region (tolerate new start) -------------*/
			if (aktregion->Eckpunktnum[1] == regpkt.n) {
				if (aktregion->anzEckpunkte < 4)  {
					if (nr > 0) {
						punkt[0].x = lastpunkt.x;
						punkt[0].y = lastpunkt.y;
					}
					xUIfehler(XGRNOTAREGION, grawidgets.shell);
					return;
				} else {
					ende = True;                        /* OK region qualified */
				}
			}
		}
		/*--- It's a valid region point --------------*/
		aktregion->Eckpunkte =
					(XPoint *)realloc(aktregion->Eckpunkte, typ*sizeof(XPoint));
		aktregion->Eckpunktnum =
					(PKTNR *)realloc(aktregion->Eckpunktnum, typ*sizeof(PKTNR));
		aktregion->Eckpunkte[nr].x = regpkt.p.x;
		aktregion->Eckpunkte[nr].y = regpkt.p.y;
		aktregion->Eckpunktnum[nr] = regpkt.n;
		aktregion->anzEckpunkte++;

		if (ende) {
			/*--- Ok region completed --------------*/
			xGRcreate_region(aktregion);
			XmTextSetString(grawidgets.frage, "");
			XmTextSetString(grawidgets.antwort, "");
			graglob.eingabe = 0;
			graglob.aktbox = BUTTONNONE;
			graglob.akttog = BUTTONNONE;
			XmListSelectPos(grawidgets.select, aktnummer+1, False);
			XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
		} else {
			/*--- continue to capture points --------*/
			lastpunkt.x = punkt[0].x;
			lastpunkt.y = punkt[0].y;
			XmTextSetString(grawidgets.frage, FRAGE_REGION1);
			graglob.eingabe++;
		}
	}
}
