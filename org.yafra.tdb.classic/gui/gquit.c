/************************************************************** 
 * Modul:		GRAPHIC							gquit.c
 *
 *					Close the GRAPHIC Modul of MarcoPolo  
 *					Cancelling or normal quitting is possible
 *                                               
 *                                                      
 * Copyright: yafra.org, Basel, Switzerland  
 * Autor:     Administrator, yafra          
 **************************************************************/
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gquit.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xGRquit ()
 *					Normal graphic quitting procedure
 *					Save all stuff 
 *  In:			-std CB params 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xGRquit( Widget w, XtPointer Input, XtPointer Output)
{
	extern long		anzgrafObj;
	extern GRAWIDGETS grawidgets;
	extern GRAGLOB graglob;
	extern MENU menu[];
	extern REGOBJ *regObj;
	extern long anzregObj;
	extern int aktmenu[];
	extern int aktmenuobj[];
	extern int aktfield[];
	extern int aktmenuz;
	extern char *outcomm;
	extern long maxoutcomm;
	extern ApplicationData app_data;
	extern unsigned char actiontoggle;

	Boolean	ok;
	MENU		*a;
	int		f, n;
	long		i, gralen, regionlen, totlen;
	REGOBJ	*reg;
	char		*regionbegin; 

	if (graglob.mode == XGRINPGRAFIC)
	{
		/*--- alloc for BOTH graphic and regions -------------*/
		totlen = XGR_LINE_LEN * (anzgrafObj +1);
		regionlen = xGRwrite_regions_len();
		totlen += regionlen;
		outcomm = (char *)xUIalloc( (void *)outcomm, &maxoutcomm,
											app_data.maxdataout, totlen, sizeof(char));

		/*--- save all ----------------------*/
		gralen = xGRwrite_graphikdata();
		regionbegin = outcomm + gralen; 
		ok = xGRwrite_regions( regionbegin);			/* end in xUIinput */

		/*--- send to DB --------------------*/
		COMMTYP   = GRASEND;
		ACTIONTYP = actiontoggle;
		MENUNR    = (unsigned char)aktmenuobj[aktmenuz];      /*not from BM menu*/
		FELDNR    = (unsigned char)aktfield[aktmenuz];
		(void)xUItalkto(SEND, outcomm, gralen + regionlen);
	}

	else  /*-------- (select or show mode) quit immediate ------------*/
	{
		/*--- send booked regions to DB process ---*/
		if (graglob.mode == XGRSELGRAFIC)  
			xGRsend( 0, 0, 0);              

		/*--- quit graphic menus ----*/
		xGRquit_graphic();
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xGRquit_graphic ()
 *					Close all graphic windows 
 *					Re-enable menu who called graphic 
 *  In:			- 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void  xGRquit_graphic()
{ 
	extern Display		*display;
	extern GRAGLOB graglob;
	extern int aktmenu[];
	extern int aktfield[];
	extern int aktmenuz;
	extern MENU menu[];
	extern GRAWIDGETS grawidgets;
	extern int     		bm_aktfield;

	MENU			*a;
	BOOKMENU		*b; 
	int		f, n;


	/*--- select or show mode additional clear --*/
	if (graglob.mode != XGRINPGRAFIC)
	{
		if ( graglob.timer)
			XtRemoveTimeOut( graglob.timer);
		xGRbook_temp_reset();              
	}

	/*--- Enable previous menu and field --------*/
	b = xBMmenuActive();
	if (b)
	{
		/*--- re-enable current BM menu */
		b->editfeld = TRUE;
		b->alreadywrite = FALSE;
		xBMmenufeld( b, b->Wgfields[bm_aktfield], TRUE, TRUE, FALSE, TRUE);
	}
	else if (aktmenuz != -1)
	{
		n = aktmenu[aktmenuz];
		a = &menu[n];
		a->editfeld = TRUE;
		a->alreadywrite = FALSE;
		f = aktfield[aktmenuz];
		xUImenufeld( a, a->field[f], TRUE, TRUE, FALSE, TRUE);     
	}

	XFlush(display);

#ifdef DEBUG_REGION
/*????  debugging PC-SCO diffs  in graphic   */
xGRcreate_regionpoint_file(); 
xGRcreate_regobj_file();
#endif

	/*--- close windows -------------------------*/
	graglob.openedshell = False;
	graglob.openedpalette = False;
	graglob.openedbookmain = False;
	if (graglob.mode == XGRINPGRAFIC)    
		XtPopdown( grawidgets.palette);     
	XtPopdown( grawidgets.shell);    
}
