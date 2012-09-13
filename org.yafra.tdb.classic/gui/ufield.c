/*D*************************************************************************
 * Modul:		GUI - Dialog                                        ufield.c 
 *            
 * 				Field object functions like: find number, next, last ...
 *						
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ufield.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";


static int xUIfieldMove( int diff, MENU *a);


/*F--------------------------------------------------------------------------
 *  Function:	xUIfieldnr ()
 *					Find Edit-Field number by comparing field widget
 *  In:			-std CB parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
int xUIfieldnr( MENU *a, Widget field)
{
	int     i;

	for (i=0; i<a->anz; i++) {
		if (a->field[i] == field) return(i);
	}
	return(-1);
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIfieldnext ()
 *					go to the next field of the menu 
 *  In:			-std CB parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIfieldnext( Widget w, XtPointer closure, XtPointer wdata)
{
	MENU *a;
	int   feld;

	a = (MENU *)closure;
	xUIeditend( w, closure, 0);
	feld = xUIfieldMove( 1, a);
	xUIeditnext( a, feld);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIfieldlast ()
 *					go to the last(previous) field of the menu 
 *  In:			-std CB parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIfieldlast( Widget w, XtPointer closure, XtPointer wdata)
{
	MENU		*a;
	int		feld, art;

	a = (MENU *)closure;
	art = -1;
	xUIeditend( w, closure, 0);
	feld = xUIfieldMove( art, a);
	xUIeditnext( a, feld);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIfielddel ()
 *					delete a menu field, for normal and global menus 
 *  In:			-std action proc params 
 *---------------------------------------------------------------------------
 */
XtActionProc xUIfielddel( Widget w, XEvent* event, String* s, Cardinal* n)
{
	extern MENU    menu[];
	extern MENU    glob;
	extern XtPointer  para;
	extern GLOBDATA   globdata;
	extern int     aktmenu[];
	extern int     aktmenuobj[];
	extern int     aktfield[];
	extern int     aktmenuz;
	extern int     globfield;
	extern int     holdfield;
	extern unsigned char actiontoggle;

	MENU		*a, *b;
	int		i, j;
	int		feldnr;
	Boolean	global;
	char		*ptr;

	/*-- inits ------*/
	global = FALSE;
	j = -1;

	/*--- check if global menu ------*/
	a = &glob;
	for ( i=0; j < 0 && i < a->anz; i++ )
		{
		if ( w == a->pushbutton[i] )
			{
			j = i;
			b = a;
			global = TRUE;
			}
		}

	/*--- check if normal menu ------*/
	a = &menu[aktmenu[aktmenuz]];
	for ( i=0; j < 0 && i < a->anz; i++ )
		{
		if ( w == a->pushbutton[i] )
			{
			j = i;
			b = a;
			}
		}

	/*--- Clear and update DB process if field ok -------------*/
	if ( j >= 0 )
		{
		XmTextSetString( b->field[j], "" );    /* clear menu field */
		if ( global )
			{
			globfield = j;
			/*--- clear also in global member --*/
			ptr = xUIglobmember(j);
			(void)sprintf( ptr, "" );

			/*--- send to  Databankprocess -----*/
			COMMTYP   = GLOBAL;
			ACTIONTYP = GLOBSEND;
			MENUNR    = (unsigned char)_GLOBALMENU;
			FELDNR    = (unsigned char)globfield;
			(void)xUItalkto(SEND, (char *)&globdata, sizeof(globdata));
			}
		else              /*---- normal GUI menu ---------*/
			{
			feldnr = j;
			COMMTYP   = DELETEFIELD;
			ACTIONTYP = actiontoggle;
			MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
			FELDNR    = (unsigned char)feldnr;
			(void)xUItalkto(SEND, 0, 0);
			}
		}
	else
		xUIbeep( w, 0, 0, 0 );
}



/*F---------------------------------------------------------------------
 *	Function:	xUIfieldDeleteAll 
 *					Delete all fields of a menu 
 *					
 *	In:			-std CB parameters 
 *					-
 *-----------------------------------------------------------------------
 */
XtCallbackProc xUIfieldDeleteAll( Widget w, XtPointer closure, XtPointer wdata)
{
	extern MENU		glob;
	extern int     aktmenu[];
	extern int     aktmenuobj[];
	extern int     aktmenuz;
	extern int 		globfield;
	extern unsigned char actiontoggle;
	extern TWINLIST	*twinList;

	MENU		*a;
	int		i;
	char		*ptr;
	char		*ptext;

	a = (MENU *)closure;
	/*--- clear all menu fields --------------------*/
	for ( i = 0; i < a->anz; i++ )
	{
		XmTextSetString( a->field[i], "" );
	}

	if ( a == &glob )
	{
		/*--- Error if occurs ---*/
		perror( "\n mpgui (xUIdelmenu.c): illegal delete in global menu");
	}
	else
	{
		COMMTYP   = DELETEMENU;
		ACTIONTYP = actiontoggle;
		MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
		FELDNR    = NULL;
		(void)xUItalkto(SEND, 0, 0);
	}

	/*--- Clear the lists after sending to DataBank -------------*/
	xUICtwinDeleteItems( twinList);
}



/************************** STATIC FUNCTIONS *********************************/

/*F--------------------------------------------------------------------------
 *  Function:	xUIfieldMove ()
 *					Find next edit field in the menu 
 *  In:			-diff forward+1 or backward-1 , a menu
 *  out:			-
 *  Return:		-field number
 *---------------------------------------------------------------------------
 */
static int xUIfieldMove( int diff, MENU *a)
{
	extern int         holdfield;

	int                feld;

	if (holdfield != -1) {
		feld = holdfield;
		feld += diff;
		if (feld < 0) {
			feld = a->anz-1;
		} else if (feld >= a->anz) {
			feld = 0;
		}
	} else {
		if (diff > 0) {
			feld = 0;
		} else {
			feld = a->anz-1;
		}
	}
	return(feld);
}

