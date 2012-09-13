/*D************************************************************
 * Modul:		GRAPHIC							gchange.c
 *
 *					Wrapping of graphic, checks type of mode	
 *					Show, book or input(draw)
 *					Enable/disable some menu accesses
 *					create graphic objects
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gchange.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";

#ifdef DEBUG_REGION
/*!!! debugging info ******************/
void xGRdebug_db_dump(char * entries );
FILE			*rpfile;
#endif

void xGRchangetyp(int typ)
{
	extern Display		*display;
	extern char *entries;
	extern char *aktgraphikfile;
	extern GRAWINDOWS grawindows;
	extern GRAWIDGETS grawidgets;
	extern GRAGLOB		graglob;
	extern long			anzgrafObj;
	extern GRAFOBJ		*grafObj;
	extern unsigned long anzregionPoints;
	extern REGIONPOINT	*regionPoints;
	extern long				anzregObj;
	extern XtAppContext	mpx_appcontext;

	char			*ptr, *regions;
	Boolean		ok;
	Arg			args[2];
	int			i, j;
	long			len; 

#ifdef DEBUG_REGION
	/*?????******** debugging SCO graphic problem  */
	rpfile = fopen( "regionlogic", _P_WRITE_);
	if (!rpfile)
		printf( " error opening debug file ");
#endif

	/*-- inits ---------------*/
	graglob.mode = typ;
	graglob.pickbox.x = 10;
	graglob.pickbox.y = 10;
	graglob.openedshell = False;
	graglob.openedpalette = False;
	graglob.openedbookmain = False;

	/*--- Graphic area is always present -----------------*/
	XtPopup(grawidgets.shell, XtGrabNone);
	graglob.openedshell = True;
	grawindows.graphik = XtWindow(grawidgets.graphik);
	XDefineCursor(display, grawindows.graphik, graglob.wait);     /*clock*/
	XClearArea( display, grawindows.graphik, 0, 0, 0, 0, True);
	XFlush(display);

	/*--- Graphic already present? -----------------------*/
	if (comm.datalen > 0)
	{
		/*--- Clear it will be replaced -------------*/
		XmListDeleteAllItems(grawidgets.booking);
		xGRdeleteall( grawidgets.shell, 0, 0);    
		xGRinit_factors(); 

#ifdef DEBUG_REGION
		/*??? PC-SCO GRAPHIC BUG !!! TRACING */
		xGRdebug_db_dump( entries );
#endif

		/*--- Graphic data read  or use default ---------------*/
		ptr = entries;
		if (*ptr != '0')
		{
			len = xGRread_graphikdata( entries);
			/*--- check format --------*/
			if (len == 0)
			{
				xUIfehler( XGRGRAFORMAT, grawidgets.shell);
				return;                                  /* >>>>>>>>>>> exit >>>*/       
			} 
			regions = entries + len; 
		}
		else
		{
			xGRread_graphikdata_default();    /* regionPoints 1,...4 created */
			regions = entries +2; 
		}

		/*--- Regions must always be sent ---------------------*/
		if (*regions != 0)
			ok = xGRread_regions(regions);
		else
		{
			xUIfehler( XGRGRAFORMAT, grawidgets.shell);
			return;                                     /* >>>>>>>>>>> exit >>>*/        
		} 
	}

#ifdef DEBUG_REGION
fclose(rpfile);
printf( " \n anzgrafObj: %ld   anzregionPoints: %ld   anzregObj: %ld \n ",
				anzgrafObj, anzregionPoints, anzregObj );
#endif

	/*--- Popup widgets -----------------------------------*/
	switch (typ)
	{
		case  XGRINPGRAFIC:
			XtPopup( grawidgets.palette, XtGrabNone);
			graglob.openedpalette = True;
			break;
		case XGRSELGRAFIC:
/*!!!		XtPopup( grawidgets.bookmain, XtGrabNone);       */
/*!!!		graglob.openedbookmain = True;                   */
			break;
		case XGRSHOWGRAFIC:
			break;
	}

	/*--- Update display of region and coordinates -------*/
	xGRwidget_status_clear();

	/*--- Set menu bar sensitivity according mode --------*/
	/*!!!	xGRwidget_menubar_sensitive(); ??? not mandatory since separate menubars */

	/*---- Zoom and drawing area limits --------------------------*/
	xGRzoom_reset();                     /* 0 - limits */
	xGRwidget_graphik_resize( True);     /* true = adjust also scrolledwindow */	   


	/*--- Cursor-Event-Handler aktivieren ----------------------*/
	XtAddEventHandler( grawidgets.graphik,
					PointerMotionMask|EnterWindowMask|LeaveWindowMask, False,
					(XtEventHandler)xGRupdate_cursor, (XtPointer)grawidgets.koord);

	/*--- 1. Mal Zeit bestimmen und ev. Zustand bestimmen ------*/
	if (typ != XGRINPGRAFIC) {
		/*-- wait a second before updating booking status ! ---*/
		graglob.timer = XtAppAddTimeOut(mpx_appcontext, 1*1000, (XtTimerCallbackProc)xGRread_booking, 0);
/*		xGRread_booking(0);  !! immediate update triggers an Xerror!! */
	}

}

#ifdef DEBUG_REGION
void xGRdebug_db_dump(char * entries )
{
	extern GRAWIDGETS grawidgets;
	FILE			*fp;

	/*--- Open file to write ----------*/
	fp = fopen( "regionpoints_db", "w");
	if (!fp) {
		xUIfehler(XGRGRAFILEOPEN, grawidgets.shell);
		return;
	}

	/*--- look for matching x,y -------*/
	fprintf(fp, "%s", entries);
	  
	/*--- close file  ----------*/
	fclose(fp);
}
#endif
