/*D***********************************************************
 * Modul:		GUI - dialog			udialog.c
 *
 *					Create a dialog widget class
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/udialog.c,v 1.3 2008-11-23 15:44:39 mwn Exp $

 Log Information:
 $Log: udialog.c,v $
 Revision 1.3  2008-11-23 15:44:39  mwn
 error corrections - updated TODO tasks for Eclipse

 Revision 1.2  2008-11-02 19:55:45  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:50  ja
 general version

 * Revision 1.5  94/02/18  10:43:45  10:43:45  ja (Jean-Marc Adam)
 * Name change for DOS
 *
 * Revision 1.4  93/04/07  16:41:59  16:41:59  ja (Jean-Marc Adam)
 * "Application modality"
 *
 * Revision 1.3  93/01/11  09:04:41  09:04:41  ja ()
 * "Dialog selection Title "
 *
 * Revision 1.2  93/01/03  21:50:40  21:50:40  mw ()
 * "Update"
 *
*/

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/udialog.c,v 1.3 2008-11-23 15:44:39 mwn Exp $";

Widget xUIdialog( unsigned char typ, Widget parent, char *title, char *name,
						XtCallbackProc okproc, XtPointer okclosure,
						XtCallbackProc notokproc, XtPointer notokclosure)
{
	int i;
	Arg w[5];
	Widget work;

	i=0;
	XtSetArg(w[i], XmNtitle,             (XtArgVal)title); i++;
	//TODO check modality XtSetArg(w[i], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL); i++;
	XtSetArg(w[i], XmNdialogStyle, XmDIALOG_MODELESS); i++;
	switch (typ) {
		case XmDIALOG_INFORMATION:
			work = XmCreateInformationDialog(parent, name, w, i);
			break;
		case XmDIALOG_ERROR:
			work = XmCreateErrorDialog(parent, name, w, i);
			break;
		case XmDIALOG_QUESTION:
			work = XmCreateQuestionDialog(parent, name, w, i);
			break;
		case XmDIALOG_WARNING:
			work = XmCreateWarningDialog(parent, name, w, i);
			break;
		case XUIDIALOG_SELECTION:
			work = XmCreateFileSelectionDialog(parent, name, w, i);
			XtSetArg(w[0], XmNtitle, (XtArgVal)title);
			XtSetValues(XtParent(work), w, 1);
			break;
		}
	if (typ != XUIDIALOG_SELECTION)
		{
		XtUnmanageChild(XmMessageBoxGetChild(work, XmDIALOG_HELP_BUTTON));
		if (okproc)
			XtAddCallback(work, XmNokCallback, okproc, okclosure);
		else
			XtUnmanageChild(XmMessageBoxGetChild(work, XmDIALOG_OK_BUTTON));

		if (notokproc)
			XtAddCallback(work, XmNcancelCallback, notokproc, notokclosure);
		else
			XtUnmanageChild(XmMessageBoxGetChild(work, XmDIALOG_CANCEL_BUTTON));

		}
	else
		{
		XtUnmanageChild(XmFileSelectionBoxGetChild(work, XmDIALOG_HELP_BUTTON));
/*		XtUnmanageChild(XmFileSelectionBoxGetChild(work, XmDIALOG_APPLY_BUTTON)); */
		if (okproc)
			XtAddCallback(work, XmNokCallback, okproc, okclosure);
		else
			XtUnmanageChild(XmFileSelectionBoxGetChild(work, XmDIALOG_OK_BUTTON));

		if (notokproc)
			XtAddCallback(work, XmNcancelCallback, notokproc, notokclosure);
		else
			XtUnmanageChild(XmFileSelectionBoxGetChild(work, XmDIALOG_CANCEL_BUTTON));
		}
	return(work);
}
