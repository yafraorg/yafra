/*D***********************************************************
 * Modul:     DBI - database info                           
 *            Dienstleistungsangebots Liste
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xDLAinfo.c,v 1.2 2008-11-02 19:55:41 mwn Exp $

 Log Information:
 $Log: xDLAinfo.c,v $
 Revision 1.2  2008-11-02 19:55:41  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:35:02  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  16:34:35  16:34:35  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/09/08  15:10:32  15:10:32  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLAinfo.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int DLAinfo(char *buffer)
{
	extern MEMOBJ sqlmem;
	extern char glob_bez_dla[];
	extern int sprache;
	extern ORT ort;

	DIENST_ANGEBOT dla;
	DLA_VIEW *dienst_angebot;
	struct tm DateTime;
	char query[RECLAENGE];
	char message[RECLAENGE];
	char tmp_buffer[RECLAENGE];
	char bezeichnung[RECLAENGE];
	char *ptr;
	int status=(int)MPOK;
	int i, anzahl, anzchar;
	int id;

	/* Check auf glob_bez_dtg ob vorhanden */
	if (*glob_bez_dla == NULL)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Kopfzeile mit DLA */
	dla.dla_id = MPAPIselectEntry((int)_DIENST_ANGEBOT, glob_bez_dla,
		(char *)&dla, sizeof(DIENST_ANGEBOT), sizeof(dla.dla_id));
	if (dla.dla_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NODLA, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (dla.h_dla_id == (int)_UNDEF)
		(void)sprintf(query, _SEL_BEZ_DLA_ID, dla.dla_id, dla.dla_id, (int)sprache );
	else
		(void)sprintf( query, _SEL_BEZ_DLA_ID, dla.h_dla_id, dla.h_dla_id, (int)sprache );
	status = MPAPIdb_sqlquery( (int)_DLA_VIEW, &sqlmem.buffer, query,
                          &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	dienst_angebot = (DLA_VIEW *)sqlmem.buffer;
	if (status != (int)MPOK || anzahl == (int)0)
		{
		UtilMsg((int)MPE_NODLA, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Titel */
	(void)copyTextTo(buffer, (char *)dienst_angebot[0].bez, (int)_CHAR30);
	(void)WriteTime(&DateTime, (time_t *)&dienst_angebot[0].dau, bezeichnung);
	(void)strcat(buffer, "  ");
	(void)strcat(buffer, bezeichnung);
	anzchar = (int)strlen(buffer);
	ptr = &buffer[anzchar];
	*ptr++ = '\n';
	for (i=0; i<anzchar; i++)
		*ptr++ = '=';
	*ptr++ = '\n';
	*ptr++ = '\n';
	*ptr = NULL;

	/* Einzelne DLA's auflisten
	 *	Start bei Index 1 da auf 0 das �bergeordnete DLA steht
	 */
	for (i=(int)1; i < anzahl; i++)
		{
		/* Ordnungsnummer mit DLA Bezeichnung */
		(void)sprintf(tmp_buffer, "%-4d", dienst_angebot[i].ord);
		(void)strcat(buffer, tmp_buffer);
		(void)copyTextTo(bezeichnung, (char *)dienst_angebot[i].bez, (int)_CHAR30);
		(void)sprintf(tmp_buffer, "%-30s ", bezeichnung);
		(void)strcat(buffer, tmp_buffer);

		/* Von Destination */
		id = MPAPIselectOneId((int)_ORT, dienst_angebot[i].von, (char *)&ort);
		if (id == (int)_UNDEF || SelectBez((int)_ORT, sprache, ort.bez_id,
							bezeichnung) == (int)_UNDEF)
			*bezeichnung = NULL;
		(void)sprintf(tmp_buffer, "%-30s ", bezeichnung);
		(void)strcat(buffer, tmp_buffer);

		/* Nach Destination */
		id = MPAPIselectOneId((int)_ORT, dienst_angebot[i].nach, (char *)&ort);
		if(id == (int)_UNDEF || SelectBez((int)_ORT, sprache, ort.bez_id,
							bezeichnung) == (int)_UNDEF)
			*bezeichnung = NULL;
		(void)sprintf(tmp_buffer, "%-30s    ", bezeichnung);
		(void)strcat(buffer, tmp_buffer);

		/* Dauer */
		if (dienst_angebot[i].dau != (int)_UNDEF)
			{
			(void)WriteTime(&DateTime, (time_t *)&dienst_angebot[i].dau, tmp_buffer);
			(void)strcat(buffer, tmp_buffer);
			}
		(void)strcat( buffer, "\n" );
		}

	return(status);
}
