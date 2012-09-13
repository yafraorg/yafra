/**************************************************************/
/* Modul:     Erstelle Rahmen inkl. Titel um ein user widget  */
/*            like NEXT Step                                  */
/*                                                            */
/* Uebergabe: Toplevel Widget                                 */
/*            Bitmap File / Bitmap Buffer                     */
/*            Vorder- und Hintergrund als Pixel               */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/*                                                            */
/* History:   June 1992 mw Erstellung                         */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psgui/source/frame.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";


/* INCLUDES */
#include <X11/Xlib.h>        /* Xlib header */
#include <X11/Intrinsic.h>   /* X Toolkit prototypes */
#include <Xm/Xm.h>           /* OSF/Motif Resources */
#include <Xm/Form.h>         /* Formwidget header */
#include <Xm/Separator.h>    /* Separator header */
#include <Xm/Label.h>        /* Labelwidget header */
#include <Xm/Frame.h>        /* Framewidget header */

#include <psgui.h>          /* Prototypes of Utilities */

#define LOC_SEPARATOR    "separator"
#define LOC_FRAME        "frame"
#define LOC_FORM         "form"

Widget OSFCreateLabelFrame(
	Widget parent,		  /* parent widget                                    */
	char *name,		     /* name of widget to be created                     */
	Arg args[],		     /* resource argument list                           */
	int numargs,		  /* number of resource arguments                     */
	Widget (*create)(), /* convenience function for working widget creation */
	char *namelabel,	  /* name of label widget                             */
	Widget *form		  /* form widget for eventually attachments           */
)

{
	Widget label;
	Widget frame;
	Widget work;
	Widget anchor;
	int n;
	Arg wargs[8];
	Dimension height, width;

	*form  = XmCreateForm(parent, LOC_FORM, 0, 0);
	XtManageChild(*form);

	n = 0;
	XtSetArg(wargs[n], XmNseparatorType,          XmNO_LINE); n++;
	XtSetArg(wargs[n], XmNleftAttachment, XmATTACH_POSITION); n++;
	XtSetArg(wargs[n], XmNleftPosition,                  50); n++;
	XtSetArg(wargs[n], XmNtopAttachment,      XmATTACH_FORM); n++;
	anchor = XmCreateSeparator(*form, LOC_SEPARATOR, wargs, n);
	XtManageChild(anchor);

	label = XmCreateLabel(*form, namelabel, 0, 0);
	XtManageChild(label);

	n = 0;
	XtSetArg(wargs[n], XmNheight,                 &height); n++;
	XtSetArg(wargs[n], XmNwidth,                   &width); n++;
	XtGetValues(label, wargs, n);

	n = 0;
	XtSetArg(wargs[n], XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET); n++;
	XtSetArg(wargs[n], XmNleftWidget,                       anchor); n++;
	XtSetArg(wargs[n], XmNleftOffset,                     -width/2); n++;
	XtSetValues(label, wargs, n);

	n = 0;
	XtSetArg(wargs[n], XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET); n++;
	XtSetArg(wargs[n], XmNtopWidget,                        label); n++;
	XtSetArg(wargs[n], XmNtopOffset,             height/2); n++;
	XtSetArg(wargs[n], XmNleftAttachment,   XmATTACH_FORM); n++;
	XtSetArg(wargs[n], XmNrightAttachment,  XmATTACH_FORM); n++;
	XtSetArg(wargs[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	XtSetArg(wargs[n], XmNmarginHeight,          height/2); n++;
	XtSetArg(wargs[n], XmNmarginWidth,           height/2); n++;
	frame = XmCreateFrame(*form, LOC_FRAME, wargs, n);
	XtManageChild(frame);

	work = create(frame, name, args, numargs);
	XtManageChild(work);
	
	if (XtIsRealized(label))
		XRaiseWindow(XtDisplay(label), XtWindow(label));

	return(work);
}
