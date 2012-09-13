/*D***********************************************************
 * Modul:     DBI - database info                           
 *            KOMMISSION
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOMinfo.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

int KOMinfo(char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];
	extern WAEHRUNG whr;
	extern STATUS_WERTE sta;
	extern int DebugFlag;

	KOMMISSION kom;
	KOMMISSION *Pkom;

	REISENDER_TYP reit;
	KOSTEN_ART kar;
	KATEGORIE kat;
	KONTINGENT kon;
	KOLLEKTIV kol;
	DIENST_ANGEBOT dla;
	DIENSTLEISTUNG dtg;

	KAR_VIEW kostenart;
	KAT_VIEW kategorie;
	TTYP_VIEW dltt;
	RKR_VIEW reisender_typ;
	DLA_VIEW angebot;
	DTG_VIEW Vdl;

	char tmp_buffer[RECLAENGE];
	char dbbuffer[RECLAENGE];
	char *to_buffers[MAX_MENU_ITEMS];
	char outbuf1[_RECORDLEN];
	char outbuf2[_RECORDLEN];
	char kombez[_BEZLEN+1];
	char komtypbez[_BEZLEN+1];
	char satztypbez[_BEZLEN+1];

	struct tm DateTime;

	int old_kommtyp = (int)_UNDEF;
	int old_dlaid = (int)_UNDEF;
	int old_dlid = (int)_UNDEF;
	int exists=0;
	int status=(int)MPOK;
	int i, anzahl, anzchar, last_id=(int)_UNDEF;
	int id, state;

	/* set to only text info */
	ACTIONTYP = INFOTXT;

	/* read strings from menu */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* build SQL SELECT */
	(void)strcpy(sqlquery, "SELECT * FROM TDBADMIN.KOMMISSION WHERE");
	for(i=0; i < MAX_MENU_ITEMS; i++)
		{
		switch(i)
			{
			case MKOM_TYP:
				if (*to_buffers[MKOM_TYP] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MKOM_TYP]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					sta.typ = (int)_KOMMTYP;
					if (getAttribut((int)_KOMMTYP, dbbuffer) != (int)MPOK)
						{
						UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
						UtilSplitFreeMenubuffer(to_buffers);
						return((int)MPERROR);
						}
					kom.komm_typ = sta.sta_id;
					if (kom.komm_typ != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " KOMM_TYP = %d", kom.komm_typ);
						(void)strcat(sqlquery, tmp_buffer);
						(void)strcat(sqlquery, " AND");
						exists++;
						}
					}
				break;

			case MKOM_KAR:
				if (*to_buffers[MKOM_KAR] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MKOM_KAR]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					kom.kar_id=MPAPIselectEntry((int)_KOSTEN_ART, dbbuffer,
					      (char *)&kar, sizeof(KOSTEN_ART), sizeof(kom.kar_id));
					if (kom.kar_id != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " KAR_ID = %d", kom.kar_id);
						(void)strcat(sqlquery, tmp_buffer);
						(void)strcat(sqlquery, " AND");
						exists++;
						}
					}
				break;

			case MKOM_KAT:
				if (*to_buffers[MKOM_KAT] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MKOM_KAT]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					kom.kat_id=MPAPIselectEntry((int)_KATEGORIE, dbbuffer,
					      (char *)&kat, sizeof(KATEGORIE), sizeof(kom.kat_id));
					if (kom.kat_id != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " KAT_ID = %d", kom.kat_id);
						(void)strcat(sqlquery, tmp_buffer);
						(void)strcat(sqlquery, " AND");
						exists++;
						}
					}
				break;

			case MKOM_KON:
				if (*to_buffers[MKOM_KON] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MKOM_KON]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					kom.kont_id=MPAPIselectEntry((int)_KONTINGENT, dbbuffer,
					(char *)&kon, sizeof(KONTINGENT), sizeof(kom.kont_id));
					if (kom.kont_id != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " KONT_ID = %d", kom.kont_id);
						(void)strcat(sqlquery, tmp_buffer);
						(void)strcat(sqlquery, " AND");
						exists++;
						}
					}
				break;

			case MKOM_DLA:
				if (*to_buffers[MKOM_DLA] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MKOM_DLA]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					kom.dla_id=MPAPIselectEntry((int)_DIENST_ANGEBOT, dbbuffer,
					(char *)&dla, sizeof(DIENST_ANGEBOT), sizeof(kom.dla_id));
					if (kom.dla_id != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " DLA_ID = %d", kom.dla_id);
						(void)strcat(sqlquery, tmp_buffer);
						(void)strcat(sqlquery, " AND");
						exists++;
						}
					}
				break;

			case MKOM_DL:
				if (*to_buffers[MKOM_DL] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MKOM_DL]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					kom.dl_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, dbbuffer,
					   (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(kom.dl_id));
					if (kom.dl_id != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " DL_ID = %d", kom.dl_id);
						(void)strcat(sqlquery, tmp_buffer);
						(void)strcat(sqlquery, " AND");
						exists++;
						}
					}
				break;

			default:
				break;
			}
		}
	UtilSplitFreeMenubuffer(to_buffers);
	if (exists == (int)0)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	(void)sprintf(&sqlquery[strlen(sqlquery)-4], " ORDER BY KOMM_TYP, DL_ID, DLA_ID, KAR_ID, KAT_ID, DLTT_ID, RKR_ID;");
	status=MPAPIdb_sqlquery((int)_KOMMISSION, &sqlmem.buffer, sqlquery,
	                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	Pkom = (KOMMISSION *)sqlmem.buffer;
	if (anzahl < (int)1 || status != (int)MPOK)
		{
		UtilMsg((int)MPE_NOKOMM, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		return(status);
		}

	*buffer = NULL;

	/* table header */
	(void)strcpy(outbuf1, "\n\n Kommissionsinfo:\n ----------------\n\n\n");
	(void)strcat(buffer, outbuf1);
	(void)strcpy(outbuf1, "Kommission            Kostenart        Kategorie        Traegertyp       Reisendertyp   Satz\n\n");
	(void)strcat(buffer, outbuf1);

	for (i=0; i<anzahl; i++)
		{
		if (Pkom[i].komm_typ != old_kommtyp && Pkom[i].komm_typ != (int)_UNDEF)
			{
			/* STATUS_WERTE  _KOMMTYP */
			sta.typ = (int)_KOMMTYP;
			id = MPAPIselectOneId((int)_STATUS_WERTE, Pkom[i].komm_typ, (char *)&sta);
			state =SelectBez((int)_KOMMTYP, sprache, sta.bez_id, komtypbez);
			if (id == (int)_UNDEF || state == (int)_UNDEF)
				(void)strcpy(komtypbez, "-");
			(void)sprintf(outbuf1, "\n\n==============================================\n");
			(void)strcat(buffer, outbuf1);
			(void)sprintf(outbuf1, "Kommissionstyp: %30.30s\n", komtypbez);
			(void)strcat(buffer, outbuf1);
			(void)sprintf(outbuf1, "==============================================\n\n");
			(void)strcat(buffer, outbuf1);
			/* set old values */
			old_kommtyp = Pkom[i].komm_typ;
			}

		if ((Pkom[i].dla_id != old_dlaid && Pkom[i].dla_id != (int)_UNDEF))
			{
			kom.dla_id=(int)MPAPIselectOneId((int)_DLA_VIEW, (int)Pkom[i].dla_id, (char *)&angebot);
			if (kom.dla_id == (int)_UNDEF ) 
				(void)strcpy(angebot.bez, "FEHLER: Kein DLA gefunden");
			(void)sprintf(outbuf1, "\nAngebot: %30.30s\n", angebot.bez);
			/* set old values */
			old_dlaid = Pkom[i].dla_id;
			(void)strcat(buffer, outbuf1);
			}
		else if ((Pkom[i].dl_id != old_dlid && Pkom[i].dl_id != (int)_UNDEF))
			{
			kom.dl_id=(int)MPAPIselectOneId((int)_DTG_VIEW, (int)Pkom[i].dl_id, (char *)&Vdl);
			if (kom.dl_id == (int)_UNDEF) 
				(void)strcpy(Vdl.bez, "FEHLER: Kein DL gefunden");
			if (Vdl.a_zeit != (int)_UNDEF)
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&Vdl.a_zeit, outbuf2);
				}
			else
				(void)strcpy(outbuf2, "-");
			(void)sprintf(outbuf1, "\nDienstleistung: %30.30s %15.15s\n",
			              Vdl.bez, outbuf2);
			/* set old values */
			old_dlid = Pkom[i].dl_id;
			(void)strcat(buffer, outbuf1);
			}

		/* KOMMISSION bezeichnung */
		id = SelectBez((int)_KOMMISSION, sprache, Pkom[i].bez_id, kombez);
		if (id == (int)_UNDEF)
			(void)strcpy(kombez, "-");
		/* STATUS_WERTE  _SATZTYP */
		sta.typ = (int)_SATZTYP;
		id = MPAPIselectOneId((int)_STATUS_WERTE, Pkom[i].satz_art, (char *)&sta);
		state =SelectBez((int)_SATZTYP, sprache, sta.bez_id, satztypbez);
		if (id == (int)_UNDEF || state == (int)_UNDEF)
			(void)strcpy(satztypbez, "-");

		/* KOSTEN_ART */
		kom.kar_id=(int)MPAPIselectOneId((int)_KAR_VIEW, (int)Pkom[i].kar_id, (char *)&kostenart);
		if (kom.kar_id == (int)_UNDEF )
			(void)strcpy(kostenart.bez, "-");
		/* KATEGORIE */
		kom.kat_id=(int)MPAPIselectOneId((int)_KAT_VIEW, (int)Pkom[i].kat_id, (char *)&kategorie);
		if (kom.kat_id == (int)_UNDEF )
			(void)strcpy(kategorie.bez, "-");
		/* TRAEGER_TYP */
		kom.dltt_id=(int)MPAPIselectOneId((int)_TTYP_VIEW, (int)Pkom[i].dltt_id, (char *)&dltt);
		if (kom.dltt_id == (int)_UNDEF )
			(void)strcpy(dltt.bez, "-");
		/* DLN TYP */
		kom.rkr_id=(int)MPAPIselectOneId((int)_RKR_VIEW, (int)Pkom[i].rkr_id, (char *)&reisender_typ);
		if (kom.rkr_id == (int)_UNDEF ) 
			(void)strcpy(reisender_typ.bez, "-");

		if (DebugFlag)
			(void)sprintf(tmp_buffer, "(DEBUG ID: %-4.0d) %-20.20s  %-15.15s  %-15.15s  %-15.15s  %-15.15s %-10.10s %8.2f\n",
		      Pkom[i].komm_id, kombez, kostenart.bez, kategorie.bez,
		      dltt.bez, reisender_typ.bez, satztypbez, Pkom[i].satz);
		else
			(void)sprintf(tmp_buffer, "%-20.20s  %-15.15s  %-15.15s  %-15.15s  %-15.15s %-10.10s %8.2f\n",
		      kombez, kostenart.bez, kategorie.bez, dltt.bez, reisender_typ.bez, satztypbez, Pkom[i].satz);
		(void)strcat(buffer, tmp_buffer);
		}

	return(status);
}

