/*D************************************************************
 * Modul: GUI - GRAPHIC
 *        send booking infos to DBI
 *
 *        Send a booking to the DBI with DLT-BEZ	
 *        in the comm.buffer
 *
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************/
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gsend.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";

XtCallbackProc xGRsend(Widget w, XtPointer Input, XtPointer Output)
{
	extern int aktmenuz;
	extern int aktmenu[];
	extern int aktmenuobj[];
	extern int aktfield[];
	extern char *outcomm;
	extern unsigned char actiontoggle;
	extern GRAWIDGETS grawidgets;
	extern long			anzregObj;
	extern REGOBJ		*regObj;
	extern GRAGLOB		graglob;

	BOOKMENU		*b; 
	int				count, j, len;
	long				i;
	XmStringTable	xm;
	String			string;
	char				*ptr;
	Arg				args[2];
	XmString			xmstring;
	Boolean			found; 
	REGOBJ			*region;

	/*--- inits ----*/
	ptr = outcomm;
	*ptr = '\0';

	/*--- Check mode of booking -----------------------------*/
	if (graglob.bookingMode == XGRBOOK_MANY)
		{
		/*---- get table of regions xmstrings ------*/
		XtSetArg(args[0], XmNitemCount, &count);
		XtSetArg(args[1], XmNitems,     &xm);
		XtGetValues(grawidgets.booking, args, 2);

		/*--- check nb of chosen items -------------*/
		if (count == 0)
			return; 										      /* >>>>>>> nothing booked !*/
		if (count > 1)     /*????? remove limit after DB acceptance */
			{
			xUIfehler(XGRTOOMUCHBOOKED, grawidgets.shell);
			return;
			}

		/*---- get all selections -----------------*/
		for (j=0;  j<count;  j++)
			{
			if (j>0)
				{
				strcpy(ptr, "\n");
				ptr++;
				}
			XmStringGetLtoR(xm[j], XmSTRING_DEFAULT_CHARSET, &string);
			(void)strcpy(ptr, string);
			ptr += strlen(string);
			XtFree((void *)string);
			}
		}
	else /* single booking */
		{
		/*--- find THE region ---*/
		for (i=0, found=False;  (i<anzregObj) && (found==False);  i++)
			{
			region = &regObj[i];
			if (region->temp == True)
				{
				xmstring = xGRregion_name( region, 0);
				XmStringGetLtoR( xmstring, XmSTRING_DEFAULT_CHARSET, &string);
				strcpy(ptr, string);
				XtFree((void *)string);
				found = True; 
				}
			}
		}

	/*--- get BM menu ----*/
	b = xBMmenuActive();
	if (b)
		MENUNR = (unsigned char) _RESERVATION;   /* bm_ix is _BMCATIX */
	else
		MENUNR = (unsigned char)aktmenuobj[aktmenuz];

	/*--- Send to DB --------------*/
	len = strlen(outcomm);
	COMMTYP   = GRACHOOSE;
	ACTIONTYP = actiontoggle;
	FELDNR    = (unsigned char)aktfield[aktmenuz];
	(void)xUItalkto(SEND, outcomm, len);
}
