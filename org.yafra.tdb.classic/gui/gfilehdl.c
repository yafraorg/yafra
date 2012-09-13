/*D************************************************************
 * Modul:		GRAPHIC							gfilehdl.c
 *
 *					File handling action when file is chosen 	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gfilehdl.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: gfilehdl.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:47  ja
 general version

 * Revision 1.4  94/02/18  10:38:09  10:38:09  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.3  93/09/07  18:25:06  18:25:06  mw (Administrator)
 * *** empty log message ***
 * 
 * Revision 1.2  93/08/21  00:16:29  00:16:29  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gfilehdl.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";



XtCallbackProc xGRfile_handling(
Widget w,
XtPointer Input,
XtPointer Output
)

{
	extern char   *aktgraphikfile;
	extern GRAGLOB graglob;
	extern GRAWIDGETS grawidgets;
	extern GRAFOBJ		*grafObj;
	extern long			anzgrafObj;
	extern unsigned long anzregionPoints;

	Boolean	ok;
	FILE		*fp;
	int		*n;
	long		i; 

	n = (int *)Input;
	switch (*n) {
		case BUTTONFILE_LOAD:
			if (graglob.fileselected) {
				/*--- clear before importing --------------*/
				for (i=anzgrafObj-1; i>=1; i--)					 
				{
					xGRdelete_grafobj(&grafObj[i]);
				}
				anzregionPoints = 0;
				XmListDeselectAllItems( grawidgets.select);
				/*--- Read new ----------------------------*/
				ok = xGRread_graphik( graglob.fileselected);
			}
			break;

		case BUTTONFILE_SAVEAS:
			if (graglob.fileselected) {
				fp = fopen(graglob.fileselected, "r");
				if (fp) {
					xUIfehler(XGRSCHONDATEI, grawidgets.shell);
					fclose(fp);
					return;
				}
				ok = xGRwrite_graphik(graglob.fileselected);
			}
			break;
	}
}
