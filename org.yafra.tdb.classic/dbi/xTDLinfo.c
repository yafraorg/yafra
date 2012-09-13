/*D***********************************************************
 * Modul:     DBI - database info                           
 *            Liste aller Teildienstleistungen einer
 *            �bergeordneten Teildienstleistung
 *            -> Was macht der Dienstleistungstr�ger Uebersicht
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xTDLinfo.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

#define MSG1 88

int DLGinfo(char *buffer)
{
	extern MEMOBJ sqlmem;
	extern char sqlquery[];
	extern int sprache;

	struct tm DateTime;

	DLG_VIEW *dlg_part;
	DLG_PART dlg;

	char tmp_buffer[_RECORDLEN];
	char tdlbez[_RECORDLEN];
	char *to_buffers[MAX_MENU_ITEMS];

	int status=(int)MPOK;
	int i, anzahl, anzchar;

	/* set to only text info */
	ACTIONTYP = INFOTXT;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (*to_buffers[MTDL_BEZ] != NULL)
		{
		(void)sprintf(tdlbez, "%s %s %s", to_buffers[MTDL_BEZ], TRENNER,
		       to_buffers[MTDL_ADAT]);

		dlg.dl_id = MPAPIselectEntry((int)_DLG_PART, tdlbez,
		           (char *)&dlg, sizeof(DLG_PART), sizeof(dlg.dl_id));
		if (dlg.h_dl_id == (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_BEZ_DLG_DLG, dlg.dl_id, dlg.dl_id, (int)sprache);
		else
			(void)sprintf(sqlquery, _SEL_BEZ_DLG_DLG, dlg.h_dl_id, dlg.h_dl_id, (int)sprache);
		}
	else
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NODLG, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* get all TDL's with HOST as first entry */
	status=MPAPIdb_sqlquery((int)_DLG_VIEW, &sqlmem.buffer, sqlquery, &anzahl,
		                         &sqlmem.datalen, &sqlmem.alloclen);
	dlg_part = (DLG_VIEW *)sqlmem.buffer;
	if ( status != (int)MPOK || anzahl == (int)0 )
		{
		UtilMsg((int)MPE_NODLG, MSGTYP_ERROR, NULL);
		}
	else
		{
		/* TITEL */
		(void)copyTextTo(tmp_buffer, (char *)dlg_part[0].bez, (int)_BEZLEN);
		(void)strcpy(buffer, tmp_buffer);
		if ( dlg_part[0].a_zeit != (int)_UNDEF )
			{
			(void)memset( (void *)&DateTime, NULL, sizeof(DateTime) );
			DateTime.tm_mday = (int)_UNDEF;
			DateTime.tm_mon  = (int)_UNDEF;
			DateTime.tm_year = (int)_UNDEF;
			DateTime.tm_hour = (int)_UNDEF;
			DateTime.tm_min  = (int)_UNDEF;
			(void)WriteDate(&DateTime, (time_t *)&dlg_part[0].a_zeit, tmp_buffer );
			(void)strcat(buffer, TRENNER);
			(void)strcat(buffer, tmp_buffer);
			}
		anzchar=(int)strlen(buffer);
		(void)strcat( buffer, "\n" );
		for ( i=0; i<anzchar; i++ )
			strcat( buffer, "=" );
		(void)strcat( buffer, "\n\n" );

		/* DETAIL */
		/* Start mit Index 1 da auf 0 �bergeordnete DLG steht	*/
		for ( i=(int)1; i<anzahl; i++ )
			{
			(void)sprintf( tmp_buffer, "%-4d : ", dlg_part[i].ord );
			(void)strcat( buffer, tmp_buffer );

			dlg_part[i].bez[_BEZLEN] = (char)NULL;
			(void)strcat( buffer, dlg_part[i].bez );

			if (dlg_part[i].a_zeit != (int)_UNDEF)
				{
				(void)memset( (void *)&DateTime, NULL, sizeof(DateTime) );
				DateTime.tm_mday = (int)_UNDEF;
				DateTime.tm_mon  = (int)_UNDEF;
				DateTime.tm_year = (int)_UNDEF;
				DateTime.tm_hour = (int)_UNDEF;
				DateTime.tm_min  = (int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&dlg_part[i].a_zeit, tmp_buffer);
				(void)strcat( buffer, " | ");
				(void)strcat( buffer, tmp_buffer);
				}
			if (dlg_part[i].e_zeit != (int)_UNDEF)
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_mday = (int)_UNDEF;
				DateTime.tm_mon  = (int)_UNDEF;
				DateTime.tm_year = (int)_UNDEF;
				DateTime.tm_hour = (int)_UNDEF;
				DateTime.tm_min  = (int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&dlg_part[i].e_zeit, tmp_buffer);
				(void)strcat(buffer, " | ");
				(void)strcat(buffer, tmp_buffer);
				}
			(void)strcat( buffer, "\n" );
			}
		}

	UtilSplitFreeMenubuffer(to_buffers);

	return( status );
}
