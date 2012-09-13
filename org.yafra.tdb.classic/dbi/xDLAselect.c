/*D***********************************************************
 * Modul:     DBI - database select
 *            DLA - Dienstleistungsangebot - Angebot auf einem Tr�ger
 *
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLAselect.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int DLAselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern char sqlquery[];
	extern DIENST_TRAEGER globDLT;
	extern DIENST_TRAEGER dlt;
	extern DIENSTLEISTUNG dtg;
	extern ANGEBOTS_TYP globDLAT;
	extern ANGEBOTS_TYP dlat;
	extern int sprache;
	extern int *NewLevel[];
	extern int dla_selected;


	extern char glob_dlt_bch[];
	extern char glob_dl_bch[];

	DLA_VIEW *Pdlav;
	int i;
	int id;
	int bufferlen;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char *to_buffers[MAX_MENU_ITEMS];
	char sqlhoststring[_QUERYLEN];
	size_t buffersize;

	/* init of sqlquery string */
	sqlquery[0] = NULL;
	(void)strcpy(sqlhoststring, _DLA_ONLYHOSTS);

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	switch (MENUNR)
		{
		case (unsigned char)_DIENST_ANGEBOT:
			if (FELDNR != (unsigned char)MDLA_DLAHOST)
				(void)strcpy(sqlhoststring, _DLA_ALL);

			/* look if in the menu is something other then in the global */
			if (*to_buffers[MDLA_DLT] != NULL)
				{
				dlt.stufe = (int)1;  /* only HOSTS ! */
				id = MPAPIselectEntry(_DIENST_TRAEGER, to_buffers[MDLA_DLT], (char *)&dlt,
				                     sizeof(dlt), sizeof(dlt.dlt_id));
				if (id == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					break;
					}
				(void)sprintf(sqlquery, _SEL_DLAVIEW_DLT, sqlhoststring, sprache, dlt.dlt_id);
				}
			else if (*to_buffers[MDLA_DLAT])
				{
				id = MPAPIselectEntry(_ANGEBOTS_TYP, to_buffers[MDLA_DLAT], (char *)&dlat,
				                     sizeof(dlat), sizeof(dlat.art_id));
				if (id == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					break;
					}
				(void)sprintf(sqlquery, _SEL_DLAVIEW_DLAT, sqlhoststring, sprache, dlat.art_id);
				}
			break;

		/* all entries */
		case (unsigned char)_DLG_PART:
			(void)strcpy(sqlhoststring, _DLA_ALL);
			break;

		case (unsigned char)_BUCHUNG:
			if (dla_selected == (int)FALSE)
				{
				if (*to_buffers[MBCH_DL] != NULL)
					{
					id = MPAPIselectEntry(_DIENSTLEISTUNG, to_buffers[MBCH_DL], (char *)&dtg,
					                     sizeof(dtg), sizeof(dtg.dlg_id));
					if (id == (int)_UNDEF)
						{
						UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
						status = (int)MPERROR;
						break;
						}
					(void)strcpy(sqlhoststring, _DLA_ALL);
					(void)sprintf(sqlquery, _SEL_DLAVIEW_DL, sqlhoststring, dtg.dlg_id, sprache);
					}
				else if (*to_buffers[MBCH_DLT] != NULL)
					{
					dlt.stufe = (int)1;  /* only HOSTS ! */
					id = MPAPIselectEntry(_DIENST_TRAEGER, to_buffers[MBCH_DLT], (char *)&dlt,
					                     sizeof(dlt), sizeof(dlt.dlt_id));
					if (id == (int)_UNDEF)
						{
						UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
						status = (int)MPERROR;
						break;
						}
					(void)sprintf(sqlquery, _SEL_DLAVIEW_DLT, sqlhoststring, sprache, dlt.dlt_id);
					}
				}
			else
				{
				UtilSplitFreeMenubuffer(to_buffers);
				dla_selected = (int)FALSE;
				bufferlen = (int)*len;
				status = MXshowsend(bufferlen, buffer);
				return(status);
				}
			break;

		default:
			/* do nothing and set the default sqlquery later */
			break;
		}

	/* free up menu buffers */
	UtilSplitFreeMenubuffer(to_buffers);

	/* check status */
	if (status != (int)MPOK)
		return(status);

	/* set default if sqlquery is NULL */
	if (*sqlquery == NULL)
		{
		if (globDLT.dlt_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DLAVIEW_DLT, sqlhoststring, sprache, globDLT.dlt_id);
		else if (globDLAT.art_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DLAVIEW_DLAT, sqlhoststring, sprache, globDLAT.art_id);
		else
			(void)sprintf(sqlquery, _SEL_DLAVIEW, sqlhoststring, sprache);
		}


	/* get the data and put it to the SELECT protocol */
	status=MPAPIdb_sqlquery((int)_DLA_VIEW, &sqlmem.buffer, sqlquery,
	                         anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if (*anzahl > (int)0 )
			{
			*len = (int)0;
			if (sqlmem.alloclen > comm.alloclen)
				{
				comm.buffer = (char *)MPalloc((void *)comm.buffer, &comm.alloclen,
		                    DEFMEMCHUNK, sqlmem.alloclen, sizeof(char));
				buffer = comm.buffer; /* da buffer nur ein -> auf comm.buffer ist */
				}
			for ( i=0, buffer_ptr = buffer; i < *anzahl; i++ )
				{
				Pdlav = (DLA_VIEW *)&sqlmem.buffer[i*sizeof(DLA_VIEW)];
				(void)copyTextTo(tmp_buffer, (char *)Pdlav->bez, (int)_BEZLEN);
				buffersize = strlen( tmp_buffer );
				(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				(void)memset( (void *)buffer_ptr, '\n', sizeof( char ) );
				buffer_ptr++;

				(void)memset( (void *)buffer_ptr, NULL, sizeof( char ) );
				}
			}
		else
			{
			*buffer = NULL;
			if (MENUNR == NewLevel[MENUNR][FELDNR])
				{
				UtilMsg((int)MPE_NOCHOOSE, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			}
		}
	else
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}

	*len = (int)strlen( buffer );
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return( status );
}

/*F***********************************************************
 * Function:  Choose                                         
 *************************************************************/
int DLAchoose(int table, char *buffer)
{
	extern int sprache;
	extern DIENST_ANGEBOT		dla;
	extern AKTIONEN				akt;
	extern ANGEBOTS_TYP			dlat;
	extern ORT                 ort;
	extern char glob_bez_dla[];

	DIENST_ANGEBOT					hdla;
	DLT_VIEW                   dltv;
	struct tm DateTime;
	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char	message[RECLAENGE];
	int	id;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MDLA_BEZ:
			(void)strcpy(glob_bez_dla, buffer);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* DIENST_ANGEBOT  Teil-Dienstleistungsangebot */	
	if(MPAPIselectEntry(table, buffer, (char *)&dla, sizeof(dla),
						sizeof(dla.dla_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* DIENST_ANGEBOT  oberste Einheit der obigen Teil-DLA Gruppe */
	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, dla.h_dla_id, (char *)&hdla);
	if(id != (int)_UNDEF && SelectBez((int)_DIENST_ANGEBOT, sprache, hdla.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Reihenfolge  an welcher Stelle kommt das Teil-DLA in der Gruppe */ 
	if (dla.ord != (int)_UNDEF)
		{
		(void)sprintf(bezeichnung, "%d", dla.ord);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* DIENST_TRAEGER */
	id = MPAPIselectOneId((int)_DLT_VIEW, dla.dlt_id, (char *)&dltv);
	if (id != (int)_UNDEF)
		{
		(void)copyTextTo(bezeichnung, dltv.bez, (int)_BEZLEN);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* AKTIONEN */
	akt.akt_id=dla.akt_id;
	id = MPAPIselectOneId((int)_AKTIONEN, (int)dla.akt_id, (char *)&akt);
	if(id != (int)_UNDEF && SelectBez((int)_AKTIONEN, sprache, akt.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Ort */
	(void)copyTextTo(bezeichnung, dla.ort, (int)_CHAR30);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* ANGEBOTS_TYP */
	id = MPAPIselectOneId((int)_ANGEBOTS_TYP, (int)dla.art_id, (char *)&dlat);
	if(id != (int)_UNDEF && SelectBez((int)_ANGEBOTS_TYP, sprache, dlat.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF Dauer */
	if ( dla.dau > 0 )
		{
		(void)WriteTime(&DateTime, (time_t *)&dla.dau, bezeichnung);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* TEXTE */
	id = SelFromTxt(dla.textid,sprache,(int)_DIENST_ANGEBOT, buffer1);
	if (id != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* ORT  von Destination */
	id = MPAPIselectOneId((int)_ORT, dla.von, (char *)&ort);
	if (id != (int)_UNDEF && SelectBez((int)_ORT, sprache, ort.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* ORT  nach Destination */
	id = MPAPIselectOneId((int)_ORT, dla.nach, (char *)&ort);
	if(id != (int)_UNDEF && SelectBez((int)_ORT, sprache, ort.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Code */
	(void)copyTextTo(bezeichnung, dla.code, (int)_KRZLLEN);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
