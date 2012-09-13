/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Preis
 *                                                            
 * Copyright: yafra.org, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>        /* Prototypes f�r ANSI-C */
#include <mpsqlsel.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPREselect.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";


/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int PREselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];
	extern char sqlquery[];
	extern DIENST_ANGEBOT	dla;
	extern DIENSTLEISTUNG	dtg;
	extern KOSTEN_ART			kar;
	extern KATEGORIE			kat;
	extern REISENDER_TYP		dlnt;
	extern KONTINGENT			kon;

	PREIS *Ppre;
	int i;
	int id1, id2;
	int olddl, olddla;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	size_t buffersize;
	char dlbez[_RECORDLEN];
	char dlntbez[_RECORDLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	struct tm DateTime;

	/* init of sqlquery string */
	sqlquery[0] = NULL;
	olddla = olddl = (int)-2;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (*to_buffers[MPRE_KAR] != NULL)
		{
		if (MPAPIselectEntry((int)_KOSTEN_ART, to_buffers[MPRE_KAR],
			 (char *)&kar, sizeof(KOSTEN_ART), sizeof(kar.kar_id)) != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_PRE_KAR, kar.kar_id);
		}
	else if (*to_buffers[MPRE_KAT] != NULL)
		{
		if (MPAPIselectEntry((int)_KATEGORIE, to_buffers[MPRE_KAT],
			 (char *)&kat, sizeof(KATEGORIE), sizeof(kat.kat_id)) != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_PRE_KAT, kat.kat_id);
		}
	else if (*to_buffers[MPRE_DLNT] != NULL)
		{
		if (MPAPIselectEntry((int)_REISENDER_TYP, to_buffers[MPRE_DLNT],
			 (char *)&dlnt, sizeof(REISENDER_TYP), sizeof(dlnt.rkr_id)) != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_PRE_DLNT, dlnt.rkr_id);
		}
	else if (*to_buffers[MPRE_DLA] != NULL)
		{
		if (MPAPIselectEntry((int)_DIENST_ANGEBOT, to_buffers[MPRE_DLA],
			 (char *)&dla, sizeof(DIENST_ANGEBOT), sizeof(dla.dla_id)) != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_PRE_DLA, dla.dla_id);
		}
	else if (*to_buffers[MPRE_DL] != NULL)
		{
		if (MPAPIselectEntry((int)_DIENSTLEISTUNG, to_buffers[MPRE_DL],
			 (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id)) != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_PRE_DL, dtg.dlg_id);
		}
	else if (*to_buffers[MPRE_KON] != NULL)
		{
		if (MPAPIselectEntry((int)_KONTINGENT, to_buffers[MPRE_KON],
			 (char *)&kon, sizeof(KONTINGENT), sizeof(kon.kont_id)) != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_PRE_KON, kon.kont_id);
		}

	UtilSplitFreeMenubuffer(to_buffers);

	/* set default if sqlquery is NULL */
	if (*sqlquery == NULL)
		(void)sprintf(sqlquery, _SEL_PRE);

	status=MPAPIdb_sqlquery((int)_PREIS, &sqlmem.buffer, sqlquery, anzahl,
		                         &sqlmem.datalen, &sqlmem.alloclen);
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
				Ppre=(PREIS *)&sqlmem.buffer[i*sizeof(PREIS)];

				(void)sprintf(tmp_buffer, "%5d%s%8.2f", Ppre->pre_id, TRENNERNORM,
				              Ppre->vpr);
				buffersize = strlen(tmp_buffer);
				(void)memcpy((void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				if (Ppre->dla_id != (int)_UNDEF)
					{
					if (olddla != Ppre->dla_id)
						{
						id1 = MPAPIselectOneId((int)_DIENST_ANGEBOT, Ppre->dla_id, (char *)&dla);
						id2 = SelectBez((int)_DIENST_ANGEBOT, sprache, dla.bez_id, dlbez);
						olddla = Ppre->dla_id;
						}
					}
				else
					{
					if (olddl != Ppre->dl_id)
						{
						id1 = MPAPIselectOneId((int)_DIENSTLEISTUNG, Ppre->dl_id, (char *)&dtg);
						id2 = SelectBez((int)_DIENSTLEISTUNG, sprache, dtg.bez_id, dlbez);
						olddl = Ppre->dl_id;
						}
					}
				(void)sprintf(tmp_buffer, "%s%s", TRENNERNORM, dlbez);
				buffersize = strlen(tmp_buffer);
				(void)memcpy((void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				(void)memset( (void *)buffer_ptr, '\n', sizeof( char ) );
				buffer_ptr++;
				(void)memset( (void *)buffer_ptr, NULL, sizeof( char ) );
				}
			}
		else
			{
			*buffer = NULL;
			if (MENUNR == NewLevel[MENUNR][FELDNR] )
				{
				UtilMsg((int)MPE_NOCHOOSE, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
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

/*F***********************************************************
 * Function:  Choose                                          
 *************************************************************/
int PREchoose(int table, char *buffer)
{
	extern int sprache;
	extern KOSTEN_ART			kar;
	extern PREIS				pre;
	extern PREIS				pre_old;
	extern DIENST_ANGEBOT	dla;
	extern DIENSTLEISTUNG	dtg;
	extern TRAEGER_TYP      dltt;
	extern KATEGORIE			kat;
	extern KONT_DETAIL		k_d;
	extern KONTINGENT			kon;
	extern KOLLEKTIV			kol;
	extern REISENDER_TYP		reit;
	extern KOMMISSION			kom;
	extern SAISON				sai;
	extern STATUS_WERTE		sta;
	extern WAEHRUNG			whr;
	extern BUCHUNG				bch;
	extern ARRANGEMENT	arr;

	struct tm DateTime;
	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char	message[RECLAENGE];
	char dbbuffer[RECLAENGE];
	int	id;
   int state;
	int status = (int)MPOK;
	int   chooseflag = FALSE;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MPRE_NR:
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */
	/* hole PREIS mit PRE_ID f�r alle weiteren Aktionen */
	if (MPAPIselectEntry((int)_PREIS, buffer, (char *)&pre, sizeof(pre),
						sizeof(pre.pre_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	sprintf(buffer, "%d\t", pre.pre_id);

	/* WAEHRUNG */
	id = MPAPIselectOneId((int)_WAEHRUNG, pre.whr_id, (char *)&whr);
	if (id != (int)_UNDEF && SelectBez((int)_WAEHRUNG, sprache, whr.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Ankaufspreis */
	(void)sprintf(bezeichnung, "%8.2f", pre.apr);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Einstandspreis */
	(void)sprintf(bezeichnung, "%8.2f", pre.epr);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Verkaufspreis */
	(void)sprintf(bezeichnung, "%8.2f", pre.vpr);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* DATUM  G�ltig ab Datum */
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	(void)WriteDate(&DateTime, (time_t *)&pre.glt, bezeichnung);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* KUNDEN  Buchungsstelle */
	id = KUNmkbez(pre.kbst, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* KOSTEN_ART */
	id = MPAPIselectOneId((int)_KOSTEN_ART, pre.kar_id, (char *)&kar);
	if (id != (int)_UNDEF && SelectBez((int)_KOSTEN_ART, sprache,
	    kar.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TRAEGER_TYP */
	id = MPAPIselectOneId((int)_TRAEGER_TYP, pre.dltt_id, (char *)&dltt);
	if (id != (int)_UNDEF && SelectBez((int)_TRAEGER_TYP, sprache,
	    dltt.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* KATEGORIE */
	id = MPAPIselectOneId((int)_KATEGORIE, pre.kat_id, (char *)&kat);
	if (id != (int)_UNDEF && SelectBez((int)_KATEGORIE, sprache,
	    kat.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* REINSENDER_TYP */
	id = MPAPIselectOneId((int)_REISENDER_TYP, pre.rkr_id, (char *)&reit);
	if (id != (int)_UNDEF && SelectBez((int)_REISENDER_TYP, sprache,
	    reit.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* DIENST_ANGEBOT */
	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, pre.dla_id, (char *)&dla);
	if (id != (int)_UNDEF && SelectBez((int)_DIENST_ANGEBOT, sprache,
	    dla.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* DIENSTLEISTUNG */
	status = MPAPIselectDLbez(pre.dl_id, sprache, bezeichnung, (int)_RECORDLEN);
	if (status == (int)MPOK)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF: DL VONDAT */
	if (pre.dl_vondat != (int)_UNDEF)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		(void)WriteDate(&DateTime, (time_t *)&pre.dl_vondat, bezeichnung);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF: DL BISDAT */
	if (pre.dl_bisdat != (int)_UNDEF)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		(void)WriteDate(&DateTime, (time_t *)&pre.dl_bisdat, bezeichnung);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* KONTINGENT */
	id = MPAPIselectOneId((int)_KONTINGENT, pre.kont_id, (char *)&kon);
	if (id != (int)_UNDEF && SelectBez((int)_KONTINGENT, sprache,
	    kon.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE Kommissionen erlaubt oder nicht */
	sta.typ = (int)_PREISSTA;
	id = MPAPIselectOneId((int)_STATUS_WERTE, pre.sta_id, (char *)&sta);
	state=SelectBez((int)_STA_ORT, sprache, sta.bez_id, bezeichnung);
	if (id != (int)_UNDEF && state != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	if ( SelFromTxt(pre.textid, sprache, (int)_PREIS, buffer1) != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* ARRANGEMENT */
	id = MPAPIselectOneId((int)_ARRANGEMENT, (int)pre.arr_id, (char *)&arr);
	if (id != (int)_UNDEF && SelectBez((int)_ARRANGEMENT, sprache, arr.bez_id, bezeichnung) != (int)_UNDEF)
		{
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		(void)strcat(buffer, bezeichnung);
		(void)strcat(buffer, " => ");
		(void)WriteDate(&DateTime, (time_t *)&arr.a_dat, bezeichnung);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE Unittyp */
	sta.typ = (int)_STA_UNIT;
	id = MPAPIselectOneId((int)_STATUS_WERTE, pre.unit_typ, (char *)&sta);
	state=SelectBez((int)_STA_ORT, sprache, sta.bez_id, bezeichnung);
	if (id != (int)_UNDEF && state != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Max. Anzahl Personen auf Einheit*/
	if (pre.unit_von > (int)0)
		{
		sprintf(bezeichnung, "%d", pre.unit_von);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  Max. Anzahl Personen auf Einheit*/
	if (pre.unit_bis > (int)0)
		{
		sprintf(bezeichnung, "%d", pre.unit_bis);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
