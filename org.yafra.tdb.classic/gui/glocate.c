/*D************************************************************
 * Modul:		GRAPHIC							glocate.c
 *
 *	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/glocate.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: glocate.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:55  ja
 general version

 * Revision 1.3  94/02/18  10:38:18  10:38:18  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:50  00:25:50  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/glocate.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


void xGRlocate(
Widget w,
int t,
int l,
int r,
int b
)

{
	int n;
	Arg args[8];

	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_POSITION); n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_POSITION); n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_POSITION); n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_POSITION); n++;
	XtSetArg(args[n], XmNtopPosition,      t);                 n++;
	XtSetArg(args[n], XmNleftPosition,     l);                 n++;
	XtSetArg(args[n], XmNrightPosition,    r);                 n++;
	XtSetArg(args[n], XmNbottomPosition,   b);                 n++;
	XtSetValues(w, args, n);
}
