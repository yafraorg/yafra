/*D************************************************************
 * Modul:		GRAPHIC							grdreg.c
 *
 *					Read regions from DB and create regionObjects
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/grdreg.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: grdreg.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:02  ja
 general version

 * Revision 1.6  94/02/18  10:38:23  10:38:23  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.5  93/10/23  11:02:49  11:02:49  ja (Jean-Marc Adam)
 * no entry
 * 
 * Revision 1.4  93/09/28  17:45:07  17:45:07  pi (Administrator)
 * Ascii transmission DBI to GUI
 * 
 * Revision 1.3  93/08/21  00:26:00  00:26:00  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/grdreg.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";



#define ITEMCHUNK 500
#define DEZ 10

Boolean xGRread_regions(char *regions)
{
	extern long       anzregObj;
	extern REGOBJ     *regObj;
	extern GRAWIDGETS grawidgets;
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAGLOB		graglob;

	REGOBJ	regobj, *aktregion;
	char		*ptr, *anf, *buf, *nam, *psel, *nptr;
	long		i, j;
	int		k, len, n;
	XmString *eintrag;
	XmString *seleintrag;
	int		itemCount, selitemCount;
	long		itemAllocated, selitemAllocated;
	char		selbuf[512];
	Arg		args[4];


   /* initialisieren */
	itemCount = 0;
	selitemCount = 0;
	itemAllocated = 0;
	selitemAllocated = 0;
	anzregObj = 0;
	eintrag = NULL;
	seleintrag = NULL;

	/* Region einlesen */
	for (ptr=regions, i=0; *ptr!=0; i++) {
		anf = ptr;
		psel = selbuf;
		/*-- copy complete Dlt text ---*/
		while (*ptr != '\n' && *ptr != 0)
			 *psel++ = *ptr++;
		if (*ptr == '\n') {
			*psel = 0;
			*ptr = 0;
			ptr++;
		}
		else {
			xUIfehler( XGRGRAFORMAT, grawidgets.shell);
			return(False);
		}


		/*--- check if trenner and cut before trenner -----*/
		nam = strstr(anf, TRENNER);
		if (nam != NULL)
		{
			*nam = 0;
			nam += TRENNERLEN;
		}  
		len = strlen(anf);
		buf = (char *)malloc(len+1);
		if (!buf) {
			xUIfehler(XUINOMEMORY, grawidgets.shell);
			return(False);
		}
		strcpy(buf, anf);
		regobj.Regionname = buf;
		regobj.region = 0;
		regobj.indVater = xGRfind_region_name(nam);
		regobj.temp = False;
		regobj.zustand = 0;
		regobj.color = (unsigned char)strtol(ptr, &nptr, DEZ);
		if (*nptr == '\n' && k >= 0) {
			/* ptr shall show to the character after the \n */
			ptr = nptr+1;
		} else {
			/* An Error occurred */
			regobj.color = 0;
			while (*ptr && *ptr != '\n') ptr++;
			if (*ptr == '\n') ptr++;
		}
		/* Number of Points delimited by \n */
		k = strtol(ptr, &nptr, DEZ);
		if (*nptr == '\n' && k >= 0) {
			/* ptr shall show to the character after the \n */
			ptr = nptr+1;
		} else {
			/* An Error occurred */
			k = 0;
			while (*ptr && *ptr != '\n') ptr++;
			if (*ptr == '\n') ptr++;
		}
		regobj.anzEckpunkte = k;
		if (k > 0) {
			regobj.Eckpunkte = (XPoint *)malloc(k*sizeof(XPoint));
			regobj.Eckpunktnum = (PKTNR *)malloc(k*sizeof(PKTNR));
			if (!regobj.Eckpunkte || !regobj.Eckpunktnum) {
				xUIfehler(XUINOMEMORY, grawidgets.shell);
				return(False);
			}
		} else {
			regobj.Eckpunkte = 0;
			regobj.Eckpunktnum = 0;
		}

		/*--- num will be used as key to find coords of regionPoints */
		for (j=0; j<regobj.anzEckpunkte; j++) {
			regobj.Eckpunktnum[j] = strtol(ptr, &nptr, DEZ);
			if (*nptr == '\n' && regobj.Eckpunktnum[j] >= 0) {
				/* ptr shall show to the character after the \n */
				ptr = nptr+1;
			} else {
				/* An Error occurred */
				/* What shall I do ?? */
				while (*ptr && *ptr != '\n') ptr++;
				if (*ptr == '\n') ptr++;
			}
		}

		/*--- create and add a region object -----------------*/
		xGRcreate_regobj(&regobj);
		aktregion = &regObj[anzregObj-1];
		/*--- create X region polygon ----*/
		if (k >= 4) 
			xGRcreate_region(aktregion);

		/*--- create select list in palette ----------------*/
		if (graglob.mode == XGRINPGRAFIC)
		{
			/*--- add to select list -------------*/
			eintrag = (XmString *)xUIalloc(eintrag, &itemAllocated, ITEMCHUNK, itemCount+1, sizeof(XmString));
			eintrag[itemCount] = XmStringCreateSimple(selbuf);
			itemCount++;
			if (k >= 4) {
				/*--- selected means defined -----*/
				seleintrag = (XmString *)xUIalloc(seleintrag, &selitemAllocated, ITEMCHUNK, selitemCount+1, sizeof(XmString));
				seleintrag[selitemCount] = XmStringCreateSimple(selbuf);
				selitemCount++;
			}
		}
	}

	if (graglob.mode == XGRINPGRAFIC)
	{
		/*--- Set items in select Region list ------*/
		n = 0;
		XtSetArg(args[n], XmNitemCount,       itemCount); n++;
		if (itemCount > 0) {
			XtSetArg(args[n], XmNitems,             eintrag); n++;
		}
		XtSetArg(args[n], XmNselectedItemCount, selitemCount); n++;
		if (selitemCount > 0) {
			XtSetArg(args[n], XmNselectedItems,      seleintrag); n++;
		}
		XtSetValues(grawidgets.select, args, n);

		/*--- Freeing Memory -----------------------*/
		for (n=0; n<itemCount; n++) {
			XmStringFree(eintrag[n]);
		}
		if (itemCount > 0) {
			XtFree((void *)eintrag);
		}
		for (n=0; n<selitemCount; n++) {
			XmStringFree(seleintrag[n]);
		}
		if (selitemCount > 0) {
			XtFree((void *)seleintrag);
		}
	}

	XtSetArg(args[0], XmNtitle, regObj[0].Regionname);
	XtSetValues(grawidgets.shell, args, 1);
	return(True);
}
