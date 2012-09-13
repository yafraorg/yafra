/*D************************************************************ 
 * Modul:     GUI - dialog					uframelb.c                                   
 *                                                           
 *            Make a frame with a label on it               
 *                                                           
 * Functions: uframelb                                 
 *                                                          
 * Copyright: yafra.org, Basel, Switzerland   
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/uframelb.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: uframelb.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:57  ja
 general version

 * Revision 1.5  94/02/18  10:44:12  10:44:12  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.4  93/08/21  00:27:45  00:27:45  ja (Jean-Marc Adam)
 * update
 * 
 * Revision 1.3  93/04/08  12:51:59  12:51:59  ja (Jean-Marc Adam)
 * "Deallocate XmCreateString... stuff"
 * 
 * Revision 1.2  93/01/03  21:44:23  21:44:23  mw ()
 * "Update"
 * 
 * Revision 1.1  92/08/31  17:21:25  17:21:25  mw ()
 * Initial revisionaaaag
 * 
*/

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uframelb.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


Widget xUIframelabel(
	Widget parent,		/* parent widget */
	Widget *top,      /* top widget of this function */
	char *res_name,	/* name of widget to be created */
	char *namelabel	/* name of label widget */
)

{
	Widget		form;
	Widget		*formptr;
	Widget		label;
	Widget		frame;
	char			bez[_CHAR30+1];
	int			n;
	Arg			wargs[8];
	Dimension	height, width;
	XmString		xmStr; 	


	if (top == NULL)
		formptr = &form;
	else
		formptr = top;

	(void)sprintf(bez, "%s", res_name);
	*formptr  = XmCreateForm(parent, bez, 0, 0);
	XtManageChild(*formptr);

	n = 0;
	(void)sprintf(bez, "%sLABEL", res_name);
	xmStr = XmStringCreateLtoR( namelabel, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(wargs[n], XmNlabelString, xmStr ); n++;
	XtSetArg(wargs[n], XmNlabelType, XmSTRING); n++;
	XtSetArg(wargs[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg(wargs[n], XmNleftOffset,                10); n++;
	label = XmCreateLabel(*formptr, bez, wargs, n);
	XmStringFree( xmStr); 
	XtManageChild(label);

	n = 0;
	XtSetArg(wargs[n], XmNheight, &height); n++;
	XtSetArg(wargs[n], XmNwidth,   &width); n++;
	XtGetValues(label, wargs, n);

	n = 0;
	(void)sprintf(bez, "%sFRAME", res_name);
	XtSetArg(wargs[n], XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET); n++;
	XtSetArg(wargs[n], XmNtopWidget,                        label); n++;
	XtSetArg(wargs[n], XmNtopOffset,             height/2); n++;
	XtSetArg(wargs[n], XmNleftAttachment,   XmATTACH_FORM); n++;
	XtSetArg(wargs[n], XmNrightAttachment,  XmATTACH_FORM); n++;
	XtSetArg(wargs[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	XtSetArg(wargs[n], XmNmarginHeight,          height/2); n++;
	XtSetArg(wargs[n], XmNmarginWidth,           height/2); n++;
	frame = XmCreateFrame(*formptr, bez, wargs, n);
	XtManageChild(frame);

	if (XtIsRealized(label))
		XRaiseWindow(XtDisplay(label), XtWindow(label));

	return(frame);  /* last widget in this function */
}




