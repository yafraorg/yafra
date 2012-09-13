/*D************************************************************
 * Modul:		GUI - BM dialog		bcatrcal.c
 *
 *					Create category recall labels of current booking 
 *
 * Functions:	
 * Callbacks:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/bcatrcal.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: bcatrcal.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:01:55  ja
 general version

 * Revision 1.6  94/02/18  10:34:32  10:34:32  ja (Jean-Marc Adam)
 * Name conversion to DOS
 * 
 * Revision 1.5  93/12/22  15:39:54  15:39:54  ja (Jean-Marc Adam)
 * olditems keeps the previous max items
 * 
 * Revision 1.4  93/10/23  11:00:11  11:00:11  ja (Jean-Marc Adam)
 * no entry
 * 
 * Revision 1.3  93/08/20  23:53:35  23:53:35  ja (Jean-Marc Adam)
 * update
 * 
 * Revision 1.2  93/05/04  18:02:24  18:02:24  ja (Jean-Marc Adam)
 * "rev"
 * 
 * Revision 1.1  93/03/11  16:49:58  16:49:58  ja ()
 * Initial revision
 * 
 * 
*/

#include <uinclude.h>


static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bcatrcal.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


/*E------------------------ EXTERNALS --------------------------------------*/
extern char			*xbmLabelTable[][XBMLABMAXTEXTS];
extern OBJCOLORS orgcol;		       /* Original Colorset */

/*P------------------------ PROTOTYPES -------------------------------------*/

/*G------------------------ GLOBAL VARIABLES -------------------------------*/




/*F--------------------------------------------------------------------------
 *  Function:	xBMcatRecallSize ()
 *					-at parsing of buffer allocate mem and copy labeltable text 
 *					-buttons are here only label widgets
 *  In:			-nb of items, area to work on 
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
int xBMcatRecallSize (int nb, MENUAREA *anArea )
{
	int	i, nbItems ;

	/*--- Limit by construction -------*/
	if (nb > _CAT_NBRECALL)
		return(_NOTOK); 
	else
		nbItems = nb ; 
	/*--- Check if more allocations -------*/
	if (anArea->nbitems < nbItems)
	{
		anArea->Wgbuttons = (Widget *)XtRealloc((char *)anArea->Wgbuttons, nbItems * sizeof(Widget));
		anArea->labels = (char **)XtRealloc((char *)anArea->labels, nbItems * sizeof(char *));
	}
	/*--- init defaults labels from table --------------*/
	for (i=0; i< nbItems; i++ ) 
	{
		anArea->labels[i] = (char *)XtMalloc(_BMLABELLEN+1);
		strcpy (anArea->labels[i], xbmLabelTable[_CAT_RECALL][i] ); 
	}
	anArea->nbitems = nbItems;
	return (_OK); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMcatRecallCreate ()
 *					-create row/col parent for following widgets:
 *					-2labels and 2 buttons
 *  In:			-parent, area to work on 
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
void xBMcatRecallCreate ( Widget parent, MENUAREA *anArea )
{
	Widget		mainrowcol, rowcol1, rowcol2; 
	char			bez[_CHAR30+1];
	Arg			arglist[10];
	int			ac;

	/*--- create row/col -----------------*/
	(void)sprintf(bez, "%s%d", ROWCOLMENU, _BMCATNR);
	ac = 0;
	XtSetArg(arglist[ac], XmNpacking,     XmPACK_TIGHT);   ac++;
	XtSetArg(arglist[ac], XmNorientation, XmVERTICAL);    ac++;
	mainrowcol = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, parent, arglist, ac);
	XtManageChild( mainrowcol);

	/*--- create row/col -----------------*/
	(void)sprintf(bez, "%s%d", ROWCOLMENU, _BMCATNR);
	ac = 0;
	XtSetArg(arglist[ac], XmNpacking,     XmPACK_TIGHT);   ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL);    ac++;
	rowcol1 = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, mainrowcol, arglist, ac);
	XtManageChild(rowcol1);
	anArea->Wglink = rowcol1 ;
/******* if too much items for a line ***************
	rowcol2 = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, mainrowcol, arglist, ac);
	XtManageChild(rowcol2);
	anArea->Wglink2 = rowcol2 ;
*****************************************************/
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMcatRecallUpdate ()
 *					-update labels for recall area
 *					-Wgbuttons are here only labels !
 *  In:			-area where to find values    
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMcatRecallUpdate (MENUAREA *anArea)
{
	Widget		rowcolumn ;
	char			bez[_CHAR30+1];
	Arg			arglist[10];
	int			ac;
	int			i, nr, nbItems ;
	XmString		xmStr; 	

	/*---- inits ----------------*/
	nr = _BMCATNR ; 
	nbItems = anArea->nbitems;
	/*--- remove oldies ------------------*/
/*	XtUnmanageChildren(anArea->Wgbuttons, anArea->olditems);  */

	/*--- enough existent widgets? -------------*/
	if ( anArea->olditems < nbItems)
	{
		(void)sprintf(bez, "%s%d", LABEL, _BMCATNR);
		for (i=anArea->olditems; i < nbItems; i++ )
		{
			/*-- Wraparound in second link if no place ----*/
/*			rowcolumn = (i < _CAT_COLUMNSIZE)? anArea->Wglink: anArea->Wglink2 ; */ 
			rowcolumn = anArea->Wglink; 

			/*-- build label and change background for ODD labels ----*/
			anArea->Wgbuttons[i] = XmCreateLabel( rowcolumn, bez, 0, 0);
			if ((i % 2)==1)
				XtVaSetValues( anArea->Wgbuttons[i], XmNbackground, orgcol.bottom, NULL);
			XtManageChild( anArea->Wgbuttons[i]);  
		}
	}
	/*--- for all items, set new values  ------------------*/
	for (i= 0; i < anArea->nbitems; i++ )
	{
		ac = 0;
		xmStr = XmStringCreateSimple(anArea->labels[i]);
		XtSetArg(arglist[ac], XmNlabelString,   xmStr ); ac++;
		XtSetValues( anArea->Wgbuttons[i], arglist, ac);	
		XmStringFree( xmStr);
	}
	/*--- run for new values  ------------------*/
/*	XtManageChildren(anArea->Wgbuttons, anArea->nbitems);   */

	/*--- keep maximum of values ---------------------------------*/
	if (anArea->olditems < nbItems )
	 	anArea->olditems = nbItems;
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMcatRecallDestroy ()
 *					-remove all allocations for an Area
 *					-
 *  In:			-area to delete
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMcatRecallDestroy ( MENUAREA *anArea )
{
	int		i; 

	/*--- free memory --------*/
	XtFree((void *)anArea->Wgbuttons); 
	/*---- reset labels allocations ------ */
	for (i=0; i< anArea->nbitems; i++ )
	{ 
		XtFree((void *)anArea->labels[i]);
	}
	XtFree((void *)anArea->labels);
	anArea->Wglink = 0;
	anArea->nbitems = 0;
	anArea->olditems = 0;
}

