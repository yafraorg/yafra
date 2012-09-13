/*D************************************************************
 * Modul:		GRAPHIC							gsetfile.c
 *
 *					Set filename in menu that triggered graphic	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gsetfile.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: gsetfile.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:07  ja
 general version

 * Revision 1.3  94/02/18  10:38:31  10:38:31  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:26:10  00:26:10  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gsetfile.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";



Boolean xGRset_filename(
char *graphikfile
)

{
	extern GRAWIDGETS grawidgets;
	extern char *aktgraphikfile;
	extern MENU menu[];
	extern int aktmenuz;
	extern int aktmenu[];
	extern int aktfield[];

	Arg args[2];
	int menunr;
	int feldnr;
	int n;
	XmString label;
	char name[XGRFILENAMELEN+1];

	menunr = aktmenu[aktmenuz];
	feldnr = aktfield[aktmenuz];

	/*--- clear old name and copy new  ----------------------*/
	if (aktgraphikfile) {
		XtFree((void *)aktgraphikfile);
	}
	aktgraphikfile = (char *)malloc((strlen(graphikfile)+1)*sizeof(char));
	if (!aktgraphikfile) {
		xUIfehler(XUINOMEMORY, grawidgets.shell);
		return(False);
	}
	strcpy(aktgraphikfile, graphikfile);

	/*--- update only name (not path) in graphic menu -------*/
	for (n=strlen(graphikfile); n>=0 && graphikfile[n] != '/'; n--);
	n += 1;
	strncpy(name, &graphikfile[n], XGRFILENAMELEN);
	xGRstringpos(name, XGRFILENAMELEN, XGRLEFT);
	label = XmStringCreateSimple(name);
	XtSetArg(args[0], XmNlabelString, label);
	XtSetValues(grawidgets.dateiname, args, 1);

	/*--- update in xUI menu --------------------------------*/
	XtSetArg(args[0], XmNvalue, graphikfile);
	XtSetValues(menu[menunr].field[feldnr], args, 1);
	XmStringFree(label);

	return(True);
}
