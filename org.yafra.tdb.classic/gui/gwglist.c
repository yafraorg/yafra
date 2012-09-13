/*D*********************************************************
 * Modul:	GRAPHIC							gwglist.c
 *            
 *				Create region selection widget             
 *				
 *            
 * Copyright: yafra.org, Basel, Switzerland
 ***********************************************************/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwglist.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";

#include <uinclude.h>
#include <ginclude.h>

#define OBEN      0
#define MITTE    50
#define UNTEN   100
#define OBEN      0
#define MITTE    50
#define UNTEN   100
#define ANF1      0
#define ANF2     18
#define ANF3     34
#define ANF4     42
#define ANF5     58
#define ANF6     66
#define ANF7     82
#define ANF8    100


Widget xGRwidget_listregion(Widget parent)
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAWIDGETS grawidgets;

	Widget		listregion;  /* Form f�r Listregion */
	Widget		trenn1, trenn2;
	Widget		labelledFrame, autoform, control;
	Arg			args[6];
	int			n;
	XmString		leer, dp, leerdat;


	/*--- prepare strings ------*/
	leerdat = XmStringCreateSimple("              ");
	leer    = XmStringCreateSimple("  ");
	dp      = XmStringCreateSimple(":");

	/*---- Ret widget ------*/
	XtSetArg(args[0], XmNresizable, True);
	listregion = XmCreateForm(parent, GRAPHIKLISTREGION, args, 1);

	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_FORM);      n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_FORM);      n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_FORM);      n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_NONE);      n++;
	grawidgets.clock = XmCreateForm(listregion, GRAPHIKCLOCK, args, n);
	XtManageChild(grawidgets.clock);

	n=0;
	XtSetArg(args[n], XmNlabelString, leerdat);  n++;
	grawidgets.datum = XmCreateLabelGadget(grawidgets.clock, GRAPHIKDATUM, args, n);
	XtManageChild(grawidgets.datum);

	n=0;
	XtSetArg(args[n], XmNlabelString, leer);  n++;
	grawidgets.stunde = 	XmCreateLabelGadget(grawidgets.clock, GRAPHIKSTUNDE, args, n);
	XtManageChild(grawidgets.stunde);

	n=0;
	XtSetArg(args[0], XmNlabelString, dp); n++;
	trenn1 = XmCreateLabelGadget(grawidgets.clock, GRAPHIKTRENN, args, n);
	XtManageChild(trenn1);

	n=0;
	XtSetArg(args[n], XmNlabelString, leer);  n++;
	grawidgets.minute = XmCreateLabelGadget(grawidgets.clock, GRAPHIKMINUTE, args, n);
	XtManageChild(grawidgets.minute);

	n=0;
	XtSetArg(args[0], XmNlabelString, dp); n++;
	trenn2 = XmCreateLabelGadget(grawidgets.clock, GRAPHIKTRENN, args, n);
	XtManageChild(trenn2);

	n=0;
	XtSetArg(args[n], XmNlabelString, leer);  n++;
	grawidgets.sekunde = XmCreateLabelGadget(grawidgets.clock, GRAPHIKMINUTE, args, n);
	XtManageChild(grawidgets.sekunde);

	xGRlocate(grawidgets.datum,    OBEN, ANF1, ANF8, MITTE);
	xGRlocate(grawidgets.stunde,  MITTE, ANF2, ANF3, UNTEN);
	xGRlocate(trenn1,             MITTE, ANF3, ANF4, UNTEN);
	xGRlocate(grawidgets.minute,  MITTE, ANF4, ANF5, UNTEN);
	xGRlocate(trenn2,             MITTE, ANF5, ANF6, UNTEN);
	xGRlocate(grawidgets.sekunde, MITTE, ANF6, ANF7, UNTEN);


#ifdef COMPILE /*!!! check out */
	/*--- List of regions ------*/
	n=0;
	XtSetArg(args[n], XmNtopAttachment,     XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget,         grawidgets.clock);n++;
	XtSetArg(args[n], XmNleftAttachment,    XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNrightAttachment,   XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNbottomAttachment,  XmATTACH_NONE);   n++;
	XtSetArg(args[n], XmNlabelString,
									XmStringCreateSimple(LABEL_GRAPHIKLISTLABEL));  n++;
	grawidgets.listlabel = XmCreateLabelGadget(listregion, GRAPHIKLISTLABEL, args, n);
	XtManageChild(grawidgets.listlabel);
#endif

	/*--- Labelled Frame and child ------*/
	labelledFrame = xUIframelabel(listregion, &autoform, GRAPHIKLISTLABEL, LABEL_GRAPHIKLISTLABEL );
	control = XmCreateForm(labelledFrame, GRAPHIKFORM, 0, 0);
	XtManageChild(control);

	n=0;
	XtSetArg(args[n], XmNtopAttachment,     XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget,         grawidgets.clock);n++;
	XtSetArg(args[n], XmNleftAttachment,    XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNrightAttachment,   XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNbottomAttachment,  XmATTACH_NONE);   n++;
	XtSetValues(autoform, args, n);

	/*--- Control list -----*/
	n=0;
	XtSetArg(args[n], XmNlistSizePolicy,         XmVARIABLE);      n++;
	XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);        n++;
	XtSetArg(args[n], XmNselectionPolicy,        XmSINGLE_SELECT); n++;
	XtSetArg(args[n], XmNscrollBarPlacement,     XmBOTTOM_RIGHT);  n++;
	XtSetArg(args[n], XmNvisibleItemCount,       4);               n++;
	grawidgets.booking = XmCreateScrolledList( control, GRAPHIKBOOKING, args, n);
	XtManageChild(grawidgets.booking);
	XtAddCallback(grawidgets.booking, XmNsingleSelectionCallback,
	              (XtCallbackProc)xGRunbook, (XtPointer)0);

	/*--- Go book button -----*/
	n=0;
	XtSetArg(args[n], XmNlabelString, XmStringCreateSimple(LABEL_GO)); n++;
	grawidgets.go = XmCreatePushButton(control, GRAPHIKGO, args, n);
	XtManageChild(grawidgets.go);
	XtAddCallback(grawidgets.go, XmNactivateCallback,
	              (XtCallbackProc)xGRsend, (XtPointer)0);

	/*--- Constraints ---------*/
	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_FORM);        n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_FORM);        n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_FORM);        n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_WIDGET);      n++;
	XtSetArg(args[n], XmNbottomWidget,     grawidgets.go);        n++;
	XtSetValues(XtParent(grawidgets.booking), args, n);
	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_NONE);        n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_FORM);        n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_FORM);        n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);        n++;
	XtSetValues(grawidgets.go, args, n);

	XmStringFree(leer);
	XmStringFree(leerdat);
	XmStringFree(dp);

	return(listregion);
}
