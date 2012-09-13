/* Written by Dan Heller and Paula Ferguson.  
 * Copyright 1994, O'Reilly & Associates, Inc.
 * Permission to use, copy, and modify this program without
 * restriction is hereby granted, as long as this copyright
 * notice appears in each copy of the program source code.
 * This program is freely distributable without licensing fees and
 * is provided without guarantee or warrantee expressed or implied.
 * This program is -not- in the public domain.
 */

/* hello.c -- initialize the toolkit using an application context and a 
 * toplevel shell widget, then create a pushbutton that says Hello using
 * the varargs interface.
 */

#include <pssys.h>

#include <Xm/PushB.h>

#ifdef ps_win
/* #include <locale.h> */
#include <stdlib.h>
#include <X11/XlibXtra.h>
#endif


main(argc, argv)
int argc;
char *argv[];
{
    Widget        toplevel, help, sendmail, readmail, news;
    XtAppContext  app;
    void          help_pushed();
    void          news_pushed();
    XmString 	  label;

#ifdef ps_win
	HCLXmInit();
	/* (void)setlocale(LC_ALL, "English"); */
#endif

    XtSetLanguageProc (NULL, NULL, NULL);

    toplevel = XtVaAppInitialize (&app, "PSSYS Help Tests", NULL, 0,
        &argc, argv, NULL, NULL);

    label = XmStringCreateLocalized ("Push here to start WWW URL"); 
    help = XtVaCreateManagedWidget ("help",
        xmPushButtonWidgetClass, toplevel,
        XmNlabelString, label,
        NULL);
    XmStringFree (label);
    XtAddCallback (help, XmNactivateCallback, help_pushed, NULL);

    label = XmStringCreateLocalized ("Push here to start read mail"); 
    readmail = XtVaCreateManagedWidget ("readmail",
        xmPushButtonWidgetClass, toplevel,
        XmNlabelString, label,
        NULL);
    XmStringFree (label);
    XtAddCallback (readmail, XmNactivateCallback, readmail_pushed, NULL);

    label = XmStringCreateLocalized ("Push here to sendmail to administrator@yafra.org"); 
    sendmail = XtVaCreateManagedWidget ("sendmail",
        xmPushButtonWidgetClass, toplevel,
        XmNlabelString, label,
        NULL);
    XmStringFree (label);
    XtAddCallback (sendmail, XmNactivateCallback, sendmail_pushed, NULL);

    label = XmStringCreateLocalized ("Push here to news"); 
    news = XtVaCreateManagedWidget ("news",
        xmPushButtonWidgetClass, toplevel,
        XmNlabelString, label,
        NULL);
    XmStringFree (label);
    XtAddCallback (news, XmNactivateCallback, news_pushed, NULL);

    XtRealizeWidget (toplevel);
    XtAppMainLoop (app);
}

void help_pushed(Widget widget, XtPointer client_data, XtPointer call_data)
{
    PSSYShelp("http://intwww.yafra.org/pswww-extern/users/mw/");
}

void readmail_pushed(Widget widget, XtPointer client_data, XtPointer call_data)
{
    PSSYSmail(NULL, 1, 0);
}

void sendmail_pushed(Widget widget, XtPointer client_data, XtPointer call_data)
{
    PSSYSsendmail("administrator@yafra.org", "Testmailsubject", "Testmail body", 1, 0);
}

void news_pushed(Widget widget, XtPointer client_data, XtPointer call_data)
{
    PSSYSnews("news.yafra.org", 1);
}
