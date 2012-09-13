/*D************************************************************ 
 * Modul:     GUI - dialog					uexitbar.c                                   
 *                                                           
 *            Create an exit bar (frame + 2 buttons)
 *            Calling function gives labels and callbacks
 *                                                          
 *                                                          
 * Copyright: yafra.org, Basel, Switzerland   
 **************************************************************/
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uexitbar.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


/*F---------------------------------------------------------------------
 *	Function:	xUIexitBar 
 *					-creates a exit bar with labelled buttons 
 *					-
 *	In:			parent widget
 *					button 1 label , callback
 * Out:
 *	Ret:			the frame widget
 *-----------------------------------------------------------------------
 */
Widget xUIexitBar( Widget parent, 
							char * label_1, XtCallbackProc cb_1, XtPointer clos_1,
							char * label_2, XtCallbackProc cb_2, XtPointer clos_2 )
{
	extern char		*xuiLabelTable[][XUILABMAXTEXTS];

	Widget		form;
	Widget		frame;
	Widget		wcancel, wbuttonok; 
	int			ac;
	Arg			args[8];
	Dimension	height, width;
	XmString		xmStr; 	


	/*--- top Frame -------*/
	ac=0;
	frame = XmCreateFrame(parent, FRAMEEXIT, args, ac);
	XtManageChild(frame);

	ac=0;
	XtSetArg(args[ac], XmNfractionBase,       8 ); ac++;	
	form  = XmCreateForm(frame, "formexit", args, ac);
	XtManageChild( form);

	/*--- OK button ---------*/
	ac = 0;
	xmStr = XmStringCreateSimple( label_1);
	XtSetArg(args[ac], XmNlabelString,    xmStr ); ac++;
/*	XtSetArg(args[ac], XmNshowAsDefault,  True);   ac++;   */
	wbuttonok = XmCreatePushButton( form, PUSHBUTTON, args, ac);
	XmStringFree( xmStr); 
	XtManageChild( wbuttonok);
	XtAddCallback( wbuttonok, XmNactivateCallback,
								 (XtCallbackProc)cb_1, (XtPointer)clos_1 );
	/*--- CANCEL button -----*/
	ac = 0;
	xmStr = XmStringCreateSimple( label_2);
	XtSetArg(args[ac], XmNlabelString,    xmStr ); ac++;
	wcancel = XmCreatePushButton( form, PUSHBUTTON, args, ac);
	XmStringFree( xmStr); 
	XtManageChild( wcancel);
	XtAddCallback( wcancel, XmNactivateCallback,
								 (XtCallbackProc)cb_2, (XtPointer)clos_2 );

	/*--- Constraints ------*/
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_NONE); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_POSITION); ac++;
	XtSetArg(args[ac], XmNrightPosition,    3); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetValues( wbuttonok, args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_POSITION); ac++;
	XtSetArg(args[ac], XmNleftPosition,     5); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_NONE); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetValues( wcancel, args, ac);

	return( frame);
}

