/*D***********************************************************
 * Modul:	GRAPHIC									gfile.c
 *                                                            
 *          Read a file
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gfile.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";

void xGRfile(XEvent *event, int n)
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
   extern char			*xuiLabelTable[][XUILABMAXTEXTS];  
	extern XtPointer	adrptr;
	extern XtCallbackProc (*funcquestion)();
	extern char			*aktgraphikfile;
	extern GRAWIDGETS grawidgets;

	static int load = BUTTONFILE_LOAD;
	static int save = BUTTONFILE_SAVEAS;

	switch (n) {
		case BUTTONFILE_LOAD:
			adrptr = (XtPointer)&load;
			funcquestion = xGRfile_handling;
			XtManageChild( grawidgets.filebox);
			break;

		case BUTTONFILE_SAVE:
			xGRwrite_graphik( aktgraphikfile);
			break;

		case BUTTONFILE_SAVEAS:
			adrptr = (XtPointer)&save;
			funcquestion = xGRfile_handling;
			XtManageChild( grawidgets.filebox);
			break;

		case BUTTONFILE_DELETEALL:
			xUIdeffrage( LABEL_YES, LABEL_NO, LABEL_DELETEALL, 
							(XtCallbackProc)xGRdeleteall, 0, grawidgets.shell);
			break;

		case BUTTONFILE_CANCEL:
			xUIdeffrage( LABEL_YES, LABEL_NO, LABEL_QUIT, 
							(XtCallbackProc)xGRquit_graphic, 0, grawidgets.shell);
			break;

		case BUTTONFILE_QUIT:
			xGRquit(grawidgets.shell, 0, 0); 
			break;
	}
}
