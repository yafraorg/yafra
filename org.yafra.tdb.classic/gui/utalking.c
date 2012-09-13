/*D*************************************************************************
 * Modul:			GUI - dialog           utalking.c
 *            
 * Description: 	Prevent user actions while GUI is talking to DB
 * 					Create a glas-window onto each visible window on screen
 *						Attach a cursor symbol to these glas-windows
 *					
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/utalking.c,v 1.3 2008-11-02 19:55:46 mwn Exp $";

/*E------------------------ EXTERNALS ---------------------------------------*/

/*P------------------------ PROTOTYPES --------------------------------------*/

/*G------------------------ GLOBAL VARIABLES --------------------------------*/
Window					glasWindow[ANZ_MENU + 20];
XSetWindowAttributes	setWinAttrib[ANZ_MENU + 20];


/*F--------------------------------------------------------------------------
 *  Function:	xUItalkingModalityOn ()
 *					Set application modality to prevent input
 *					Glas-windows are mapped onto the windows
 *					Waiting cursor is added to show talking
 *
 *  In:			-ptr to Widgets,  nb of widgets
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUItalkingModalityOn( Widget *wid, int nbWidgets )
{
	extern Display *display;
	extern Cursor	cursorwait;

	Position			xpos, ypos;
	Dimension		height, width;
	Window			rootWin, parentWin, realParentWin, *childrenWin;
	unsigned	int	nchildren; 
	Status			status;
	XWindowAttributes		winAttrib;
	int				i;

	/*---- Set glas-windows for all toplevel widgets ------*/
	for (i=0; i<nbWidgets; i++)
	{
		/*----- get parent window of widget parameter -----*/
		childrenWin = (Window *)NULL;
		status = XQueryTree( display, XtWindow(wid[i]), &rootWin, &parentWin,
								 &childrenWin, &nchildren); 
		if (status == (Status)0)
			return;
		XtFree ( (void*)childrenWin); 

		childrenWin = (Window *)NULL;
		status = XQueryTree( display, parentWin, &rootWin, &realParentWin,
								 &childrenWin, &nchildren); 
		if (status == (Status)0)
			return;
		XtFree ( (void*)childrenWin); 

/*! XGetWindowAttributes caused a X11 crash don't know why so just uncommented.
		/*--- Get dimension + position ---------------*/
//		height = width = 0;
//		XGetWindowAttributes( display, realParentWin, &winAttrib);
//		xpos = winAttrib.x;
//		ypos = winAttrib.y;
//		height = winAttrib.height;
//		width = winAttrib.width;
//		if ( width && height)
//		{
			/*----- Make the input screen window ---------*/	    
//			setWinAttrib[i].event_mask = ButtonPressMask;
//			setWinAttrib[i].override_redirect = True;
//			setWinAttrib[i].cursor = cursorwait;
//			glasWindow[i] = XCreateWindow( display, rootWin, xpos, ypos,
//			       width, height, 0, 0, InputOnly, CopyFromParent,
//			       CWEventMask | CWOverrideRedirect | CWCursor,
//			       &setWinAttrib[i]);
//			XMapRaised( display, glasWindow[i]);    
// 		}
//		else
//		{
//			glasWindow[i] = 0;
//		}
	}   
}/**/




/*F--------------------------------------------------------------------------
 *  Function:	xUItalkingModalityOff ()
 *					Remove the modality to allow further selections
 *					Unmap the glas-windows used to prevent input
 *					Waiting cursor is removed with window
 *
 *  In:			-The number of widgets may have glas-windows
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUItalkingModalityOff( int nbWidgets)
{
	extern Display *display;
	int		i; 

	for (i=0; i<nbWidgets; i++)
	{
		if (glasWindow[i])
		{ 
			/*---- Unmap the window, cursor is automatically cleared --*/
			XUnmapWindow( display, glasWindow[i]);
		}
	}
}/**/





/*************************** TEST ***************************************/
/*FT-----------------------------------------------------------------TEST----
 *  Function:	xUItalkTest ()
 *					-test talking glas-window features 
 *					-cb function is called from TEST menu
 *  In:			-std callback parameters
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUItalkTest( Widget w, XtPointer b, XtPointer wdata)
{
	int			state;
	Widget		wid[ANZ_MENU + 20];
	static int	nbWidgets; 			/* remember for toggle  */

	nbWidgets = xUIwidgets(wid);
 
	/*--- get toggle state and set modality -----*/
	state = ((XmToggleButtonCallbackStruct *)wdata)->set;
	if (state == True)
		xUItalkingModalityOn( wid, nbWidgets);
	else
		xUItalkingModalityOff( nbWidgets);
}
