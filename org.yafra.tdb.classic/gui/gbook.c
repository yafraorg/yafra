/*D************************************************************
 * Modul:		GRAPHIC							gbook.c
 *
 *					Booking operations: book many DLTs, book one DLT	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gbook.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";

void xGRbook(XEvent *event, int tog)
{
	extern Display		*display;
	extern GRAWIDGETS	grawidgets;
	extern GRAWINDOWS	grawindows;
	extern long			anzregObj;
	extern REGOBJ		*regObj;
	extern GRAGLOB		graglob;

	REGOBJ	*region, *reg;
	XmString	eintrag;
	long		aktnummer, i, oldnum;
	int		x, y;
	unsigned int width, height;
	unsigned int dummy;
	Window	root;
	Arg		args[2];

	/*--- Check if booking is possible ---------*/
	aktnummer = xGRfind_region_koord(event->xbutton.x, event->xbutton.y);
	if (aktnummer == NOVATER)
		{
		xUIbeep(grawidgets.shell, 0, 0, 0); 
		return; 
		}

	/*--- Find aktuelle Pointerregion -----*/
	region = &regObj[aktnummer];
	if (graglob.bookingMode == XGRBOOK_MANY)
		{
		/*--- many in list booking ---------------------------------------*/
		eintrag = xGRregion_name( region, 0);
		if (!XmListItemExists(grawidgets.booking, eintrag)) {
			XGetGeometry(display, XtWindow(grawidgets.scrolledgraphik), &root,
						 &x, &y, &width, &height, &dummy, &dummy);
			XtSetArg(args[0], XmNwidth,  width);
			XtSetArg(args[1], XmNheight, height);
			XtSetValues(grawidgets.scrolledgraphik, args, 2);
			/*--- list ---*/
			XmListAddItem(grawidgets.booking, eintrag, 0);
			}
		XmStringFree(eintrag);
		region->temp = True;
		}
	else    /*------ single booking -------------------------------------*/
		{
		/*--- Reset all booked regions ---*/
		xGRbook_temp_reset();
		/*--- book new -------------------*/
		region->temp = True;
		}

	XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
}


void xGRshowbook(XEvent *event, int tog)
{
	extern Display		*display;
	extern GRAWIDGETS	grawidgets;
	extern GRAWINDOWS	grawindows;
	extern long			anzregObj;
	extern REGOBJ		*regObj;
	extern GRAGLOB		graglob;
	extern char *outcomm;
	extern int aktmenuz;
	extern int aktmenuobj[];
	extern int aktfield[];

	BOOKMENU		*b; 
	REGOBJ	*region, *reg;
	XmString	eintrag;
	XmString			xmstring;
	String			string;
	char				*ptr;
	long		aktnummer, i, oldnum;
	int		x, y;
	int len;
	unsigned int width, height;
	unsigned int dummy;
	Window	root;
	Arg		args[2];

	/*--- Check if booking is possible ---------*/
	aktnummer = xGRfind_region_koord(event->xbutton.x, event->xbutton.y);
	if (aktnummer == NOVATER)
		{
		xUIbeep(grawidgets.shell, 0, 0, 0); 
		return; 
		}

	/*--- inits ----*/
	ptr = outcomm;
	*ptr = '\0';

	/*--- Find aktuelle Pointerregion -----*/
	region = &regObj[aktnummer];

	/*--- Reset all booked regions ---*/
	xGRbook_temp_reset();

	/*--- book new -------------------*/
	region->temp = True;

	XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);

	xmstring = xGRregion_name( region, 0);
	XmStringGetLtoR( xmstring, XmSTRING_DEFAULT_CHARSET, &string);
	strcpy(ptr, string);
	XtFree((void *)string);

	/*--- get BM menu ----*/
	b = xBMmenuActive();
	if (b)
		MENUNR = (unsigned char) _RESERVATION;   /* bm_ix is _BMCATIX */
	else
		MENUNR = (unsigned char)aktmenuobj[aktmenuz];

	/*--- Send to DB --------------*/
	len = strlen(outcomm);
	COMMTYP   = GRACHOOSE;
	ACTIONTYP = GRASHOWINFO;
	FELDNR    = (unsigned char)aktfield[aktmenuz];
	(void)xUItalkto(SEND, outcomm, len);
}



/*F--------------------------------------------------------------------------
 *  Function:	xGRbook_one ()
 *					-call specialized function for booking 
 *					-
 *	
 *---------------------------------------------------------------------------
 */
XtActionProc xGRbook_one( Widget w, XEvent* event, String* s, Cardinal* m)
{
	extern GRAGLOB		graglob;
	extern Boolean zoomingflag;

	/*--- Inhibit during zooming operations ---*/
	if (zoomingflag)
		return; 

	if (graglob.mode == XGRSELGRAFIC)
		xGRbook(event, 0);
	else if (graglob.mode == XGRSHOWGRAFIC)
		xGRshowbook(event, 0);
}


/*F--------------------------------------------------------------------------
 *  Function:	xGRbook_andquit ()
 *					-single booking is done in one shot: select and quit
 *					-(First click has already selected the region)
 *	
 *---------------------------------------------------------------------------
 */
XtActionProc xGRbook_andquit( Widget w, XEvent* event, String* s, Cardinal* m)
{
	extern GRAWIDGETS grawidgets;
	extern GRAGLOB		graglob;
	extern Boolean zoomingflag;

	/*--- Inhibit during zooming operations ---*/
	if (zoomingflag)
		return; 

	if (graglob.mode == XGRSELGRAFIC)
		xGRquit( grawidgets.shell, 0, 0);
}



/*F--------------------------------------------------------------------------
 *  Function:	xGRbook_clear ()
 *					-reset and forget the booked regions 
 *					-
 *	
 *---------------------------------------------------------------------------
 */
XtActionProc xGRbook_clear( Widget w, XEvent* event, String* s, Cardinal* m)
{
	extern Display		*display;
	extern GRAWINDOWS	grawindows;
	extern GRAGLOB		graglob;
	extern Boolean zoomingflag;

	/*--- Inhibit during zooming operations ---*/
	if (zoomingflag)
		return; 

	if ((graglob.bookingMode == XGRBOOK_ONE) && (graglob.mode == XGRSELGRAFIC))
		{
		xGRbook_temp_reset();
		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
		}
}




/*F--------------------------------------------------------------------------
 *  Function:	xGRbook_temp_reset ()
 *					-clear temporary-booked flag of all regions 
 *					-
 *	
 *---------------------------------------------------------------------------
 */
void xGRbook_temp_reset()
{
	extern long			anzregObj;
	extern REGOBJ		*regObj;

	REGOBJ	*reg;
	long		i;

	/*--- Reset all booked regions and keep index ---*/
	for (i=0;  i<anzregObj;  i++)
		{		
		reg = &regObj[i];
		reg->temp = False; 
		}
}

