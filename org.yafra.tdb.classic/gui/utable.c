/*D*************************************************************************
 * Modul:			GUI - Dialog		   utable.c 
 *            
 * Description:	Large String form DBI is decomposed in x single items 
 *						to build a table (for a select scrolled list)
 *
 * Functions:		xUItostrtable()
 * Use:				xUIlines()
 * 
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */

/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/utable.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

   Log Information:
   $Log: utable.c,v $
   Revision 1.2  2008-11-02 19:55:46  mwn
   re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

   Revision 1.1.1.1  2002-10-26 21:10:43  mwn
   inital release

   Revision 3.1  1997/04/02 06:50:03  mw
   NT 4.0 release und WWW Teil

   Revision 2.1  1994/03/28 11:04:43  ja
   general version

 * Revision 1.4  94/02/18  10:44:54  10:44:54  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.3  93/05/18  13:57:06  13:57:06  ja (Jean-Marc Adam)
 * "work"
 * 
 * Revision 1.2  93/05/04  18:14:17  18:14:17  ja ()
 * "rev"
 * 
 * 
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/utable.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";



void xUItostrtable(char *items, Widget list)
{
	extern XmString	*tab ;
	extern long			maxtablist;
	extern ApplicationData app_data;
	extern Widget     selectpopup;

	int	totlines, i, lines, breite;
	char  *ptr, *anf;
	Arg	args[10];

	/*--- get text dimension and alloc space ----*/
	totlines = xUIlines(items, &lines, &breite);
	tab = (XmString *)xUIalloc((void *)tab, &maxtablist, app_data.maxtablist,
                              totlines, sizeof(XmString));

	/*--- split in NULL-terminated units ---------*/
	for (i=0, ptr=items; i<totlines; i++) {
		anf = ptr;
		while (*ptr != '\n' && *ptr != 0)			/* move ptr to end of line */
			ptr++;

		if (*ptr == '\n') {
			*ptr = 0;
			ptr++;
		}
		tab[i] = XmStringCreateSimple(anf);
	}

	/*--- update list (not scrolled-window) parameters -------*/
	XtSetArg(args[0], XmNvisibleItemCount, lines );
	XtSetArg(args[1], XmNitems,            tab );
	XtSetArg(args[2], XmNitemCount,        totlines );
	XtSetValues(list, args, 3);

	/*---- free all compound strings ------------*/
	for (i=0; i<totlines; i++)
		XmStringFree(tab[i]);

}



