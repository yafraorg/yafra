/**************************************************************/
/* Modul:     DBI - database select                           */
/*            Kategorie                                       */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKATselect.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

int KATselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern TRAEGER_TYP globDLTT;
	extern KATEGORIE kat;
	extern DIENST_TRAEGER globDLT;
	extern DIENST_TRAEGER dlt;
	extern DIENST_ANGEBOT dla;
	extern DLG_PART dlg;
	extern DIENSTLEISTUNG dtg;
	extern HOST_KONT hkon;
	extern KONTINGENT kon;
	extern int *NewLevel[];
	extern char sqlquery[];
	extern char glob_kon_res[];
	extern char glob_dtg_res[];

   BEZEICHNUNG *bez_ptr;
   TRAEGER_TYP dltt;
   KONT_DETAIL *k_d;
	int i, loop, id;
	int status = (int)MPOK;
	int founddl = (int)_UNDEF;
	int value;
	char *str, *cptr, *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char buff_1[5], buff_2[5];
	char *to_buffers[MAX_MENU_ITEMS];
	size_t buffersize;
	KAT_VIEW *kv = NULL;
	unsigned long dlen = 0;
	unsigned long alen = 0;

	/* init of sqlquery string */
	sqlquery[0] = NULL;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL );
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kat.kat_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	switch (MENUNR)
		{
		case (unsigned char)_DIENST_TRAEGER:
			if (*to_buffers[MDLT_DLTT] != (char)NULL)
				{
				if (MPAPIselectEntry((int)_TRAEGER_TYP, to_buffers[MDLT_DLTT], (char *)&dltt,
				    sizeof(TRAEGER_TYP), sizeof( dltt.typ_id ) ) != (int)_UNDEF)
					(void)sprintf(sqlquery, _SEL_BEZ_KAT_TYP, dltt.typ_id, sprache, (int)_KATEGORIE);
				}
			break;

		case (unsigned char)_KONT_DETAIL:
			if (*to_buffers[MKOND_HKON] != NULL &&
			    *to_buffers[MKOND_KON] == NULL)
				{
				if (MPAPIselectEntry((int)_HOST_KONT, to_buffers[MKOND_HKON],
				    (char *)&hkon, sizeof(HOST_KONT), sizeof(hkon.hostkont_id)) != (int)_UNDEF)
					{
					if (ACTIONTYP == (unsigned char)INSERT)
						{
						status = MPAPIselectDLT(hkon.dla_id, (int)_UNDEF, hkon.dl_id, &dlt);
						if (status != (int)MPOK)
							break;
						(void)sprintf(sqlquery, _SEL_BEZ_KAT_DLT, dlt.dlt_id, sprache,
			                (int)_KATEGORIE);
						}
					else
						(void)sprintf(sqlquery, _SEL_BEZ_KAT_KOND_HKON,
						              hkon.hostkont_id, sprache, (int)_KATEGORIE);
					}
				}
			else if (*to_buffers[MKOND_KON] != NULL &&
			    *to_buffers[MKOND_HKON] == NULL)
				{
				if (MPAPIselectEntry((int)_KONTINGENT, to_buffers[MKOND_KON], (char *)&kon,
				    sizeof(KONTINGENT), sizeof(kon.kont_id)) != (int)_UNDEF)
					{
					if (ACTIONTYP == (unsigned char)INSERT)
						{
						id = MPAPIselectOneId((int)_HOST_KONT, kon.hostkont_id, (char *)&hkon);
						if (id == (int)_UNDEF)
							break;
						(void)sprintf(sqlquery, _SEL_BEZ_KAT_KOND_HKON,
						              hkon.hostkont_id, sprache, (int)_KATEGORIE);
						}
					else
						(void)sprintf(sqlquery, _SEL_BEZ_KAT_KOND_KON,
						              kon.kont_id, sprache, (int)_KATEGORIE);
					}
				}
			break;

		case (unsigned char)_PREIS:
			dla.dla_id = (int)_UNDEF;
			dtg.dlg_id = (int)_UNDEF;
			if (*to_buffers[MPRE_DLA] != NULL)
				{
				id = MPAPIselectEntry((int)_DIENST_ANGEBOT, to_buffers[MPRE_DLA],
				     (char *)&dla, sizeof(DIENST_ANGEBOT), sizeof(dla.dla_id));
				}
			if (*to_buffers[MPRE_DL] != NULL)
				{
				id = MPAPIselectEntry((int)_DIENSTLEISTUNG, to_buffers[MPRE_DL],
				     (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
				}
			status = MPAPIselectDLT(dla.dla_id, (int)_UNDEF, dtg.dlg_id, &dlt);
			if (status != (int)MPOK)
				{
				status = (int)MPOK; /* set ok to make default selects later */
				break;
				}
			(void)sprintf(sqlquery, _SEL_BEZ_KAT_DLT, dla.dlt_id, sprache,
				                     (int)_KATEGORIE);
			break;

		case (unsigned char)_KOMMISSION:
			dla.dla_id = (int)_UNDEF;
			dtg.dlg_id = (int)_UNDEF;
			if (*to_buffers[MKOM_DLA] != NULL)
				{
				id = MPAPIselectEntry((int)_DIENST_ANGEBOT, to_buffers[MKOM_DLA],
				     (char *)&dla, sizeof(DIENST_ANGEBOT), sizeof(dla.dla_id));
				}
			if (*to_buffers[MKOM_DL] != NULL)
				{
				id = MPAPIselectEntry((int)_DIENSTLEISTUNG, to_buffers[MKOM_DL],
				     (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
				}
			status = MPAPIselectDLT(dla.dla_id, (int)_UNDEF, dtg.dlg_id, &dlt);
			if (status != (int)MPOK)
				{
				status = (int)MPOK; /* set ok to make default selects later */
				break;
				}
			(void)sprintf(sqlquery, _SEL_BEZ_KAT_DLT, dla.dlt_id, sprache,
				                     (int)_KATEGORIE);
			break;

		default:
			/* do nothing and set the default sqlquery later */
			break;
		}

	UtilSplitFreeMenubuffer(to_buffers);

	if (status != (int)MPOK)
		return(status);

	/* set default if sqlquery is NULL */
	if (*sqlquery == NULL)
		{
		if (globDLT.dlt_id != (int)_UNDEF && globDLT.stufe == (int)1)
			(void)sprintf(sqlquery, _SEL_BEZ_KAT_DLT, globDLT.dlt_id, sprache,
		                (int)_KATEGORIE);
		else if (globDLTT.typ_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_BEZ_KAT_TYP, (int)globDLTT.typ_id,
			              sprache, (int)_KATEGORIE);
		else
			(void)sprintf(sqlquery, _SEL_BEZ_KAT, sprache, (int)_KATEGORIE);
		}

	/* get the data and put it to the SELECT protocol */
	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, sqlquery, anzahl,
	                         &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if ( *anzahl > (int)0 )
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
				bez_ptr = (BEZEICHNUNG *)&sqlmem.buffer[i*sizeof(BEZEICHNUNG)];
				(void)copyTextTo(tmp_buffer, (char *)bez_ptr->bez, (int)_BEZLEN);
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
			if ( MENUNR == (int)_RESERVATION )
				{
				UtilMsg((int)MPE_NOKATFORRES, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			else if ( MENUNR == NewLevel[MENUNR][FELDNR] )
				{
				UtilMsg((int)MPE_NOCHOOSE, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			else
				*buffer = (char)NULL;
			}
		}
	else
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		status = (int)MPERROR;
		}

	*len = (int)strlen( buffer );
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return( status );
}


int KATchoose(int table, char *buffer)
{
	extern int sprache;
	extern KATEGORIE		kat;
	extern TTYP_VIEW		ttyp;
	extern STATUS_WERTE	sta;

	KATEGORIE				hkat;
	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char dbbuffer[RECLAENGE];
	int	id;
	int   state;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	switch(FELDNR)
		{
		case MKAT_BEZ:
			break;
		default:
			return(MPOK);
			break;
		}

	/* KATEGORIE */
	strcpy(dbbuffer, buffer);
	(void)ConvertSpecialChar(dbbuffer, NULL);
	state = MPAPIselectEntry(table, dbbuffer, (char *)&kat, sizeof(kat),
	                    sizeof(kat.kat_id));
	if (state == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcpy(buffer, buffer);
	(void)strcat(buffer, "\t");

	/* TRAEGER_TYP */
	id = MPAPIselectOneId((int)_TTYP_VIEW, (int)kat.typ_id, (char *)&ttyp);
	if (id != (int)_UNDEF)
		{
		(void)copyTextTo(bezeichnung, ttyp.bez, (int)_BEZLEN);
		(void)strcat(buffer, bezeichnung);
		(void)strcat(buffer, TRENNER);
		(void)copyTextTo(bezeichnung, ttyp.hbez, (int)_BEZLEN);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* KATEGORIE  �bergeordnete Kategorie */
	id = MPAPIselectOneId((int)_KATEGORIE, (int)kat.h_kat_id, (char *)&hkat);
	state = SelectBez((int)_KATEGORIE, sprache, hkat.bez_id,	bezeichnung);
	if (id != (int)_UNDEF && state != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  grafisches Attribut */
	sta.typ=(int)_GA;
	id = MPAPIselectOneId((int)_STATUS_WERTE, kat.ga, (char *)&sta);
	state =SelectBez((int)_GA, sprache, sta.bez_id, bezeichnung);
	if (id != (int)_UNDEF && state != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	state = SelFromTxt(kat.textid, sprache, (int)_KATEGORIE, buffer1);
	if (state != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}

