/*D***********************************************************
 * Modul:     DBI - read next Region                           
              Liest die n�chsten REGION-Eintr�ge aus dem
				  Buffer 'buffer' und gibt die n�chste Adresse
				  in **ptr zur�ck, sowie die Anzahl der Region-Punkte.
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/GRnextRegion.c,v 1.2 2008-11-02 19:55:39 mwn Exp $

 Log Information:
 $Log: GRnextRegion.c,v $
 Revision 1.2  2008-11-02 19:55:39  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:33:29  mw
 update to new DB release 2.0

 * Revision 1.4  94/02/16  15:59:04  15:59:04  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.3  93/10/23  14:11:34  14:11:34  pi (Administrator)
 * CHANGEMENTS for Rel 1.00    TTW 93
 * 
 * Revision 1.2  93/07/08  18:31:29  18:31:29  mw (Administrator)
 * "update"
 * 
 * Revision 1.1  93/07/06  18:35:53  18:35:53  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

#define DEZ 10

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/GRnextRegion.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

int GRnextRegion(char **ptr, char *buffer, REGIONS **regions)
{
	extern GRAPHIK gra;

	static void *oldptr;
	static size_t aktsize;
	static size_t memchunk = (size_t)10*sizeof(REGIONS);
	static size_t newsize;

	DIENST_TRAEGER dlt;
	char *cptr, *nptr;
	char bezeichnung[RECLAENGE];
	int anzahl = (int)0;
	int AnzRegPkte;
	int intvalue;
	int status = (int)MPOK;

	if ( *regions == (REGIONS *)NULL )
		{
		/* Wenn noch kein regions Buffer er�ffnet aktsize Null setzen */
		/**************************************************************/
		aktsize = (size_t)0;
		}

	cptr = *ptr;

	while ( *cptr != NULL && *cptr != '\n' )
		{
		/* Das n�chste Linefeed NULL setzen f�r strcpy */
		/***********************************************/
		cptr++;
		}
	*cptr = (char)NULL;
	cptr++;

	AnzRegPkte = strtol(cptr, &nptr, DEZ);
	if (*nptr == '\n' && AnzRegPkte >=0 ) {
		cptr = nptr+1;
	} else {
		/* Error */
		while (*cptr && *cptr != '\n') cptr++;
		AnzRegPkte = 0;
	}

	if (AnzRegPkte > (int)0)
		{
		(void)strcpy ( bezeichnung, *ptr );
		dlt.host_id = gra.dlt_id;

		if ((strstr(bezeichnung, TRENNER)) == NULL)
			dlt.stufe = 1; /* Eintrag ist von der obersten Stufe */
		else
			dlt.stufe = 0; /* Eintrag ist unterhalb der obersten Stufe */
		status = MPAPIselectEntry((int)_DIENST_TRAEGER, bezeichnung, (char *)&dlt,
		                  sizeof(dlt), sizeof(dlt.dlt_id));
		if (status != (int)_UNDEF)
			{
			for ( anzahl=(int)0; anzahl < AnzRegPkte; anzahl++ )
				{
				newsize =  (size_t)((anzahl+(int)1)*sizeof(REGIONS));
				*regions = (REGIONS *)MPalloc((void *)*regions, (unsigned long *)&aktsize,
				    (long)memchunk, (unsigned long)newsize, (long)sizeof(char));
				(*regions)[anzahl].folge = (int)anzahl;
				intvalue = strtol(cptr, &nptr, DEZ);
				if (*nptr == '\n' && intvalue >=0 ) {
					cptr = nptr+1;
				} else {
					/* Error */
					while (*cptr && *cptr != '\n') cptr++;
				}
				(*regions)[anzahl].nummer = (int)intvalue;
				(*regions)[anzahl].host_id = dlt.host_id;
				(*regions)[anzahl].h_dlt_id = dlt.h_dlt_id;
				(*regions)[anzahl].dlt_id = dlt.dlt_id;
				(*regions)[anzahl].stufe = dlt.stufe;
				}
			}
		else
			{
			for (anzahl=0; anzahl<AnzRegPkte; anzahl++) {
				while (*cptr != '\n') cptr++;
				cptr++;
			}
			anzahl = (int)0;
			}
		}

	*ptr = cptr;

	return(anzahl);
}
