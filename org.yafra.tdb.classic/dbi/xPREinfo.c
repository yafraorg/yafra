/*D***********************************************************
 * Modul:     DBI - database info                           
 *            PREIS
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPREinfo.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

int PREinfo(char *buffer )
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];

	extern WAEHRUNG whr;

	PREIS preis;
	PREIS *pre;
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
	char outbuf3[_RECORDLEN];

	struct tm DateTime;

	int old_dlaid = (int)_UNDEF;
	int old_dlaglt = (int)_UNDEF;

	int old_dlid = (int)_UNDEF;
	int old_dlglt = (int)_UNDEF;

	int exists=0;
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

	(void)strcpy(sqlquery, "SELECT * FROM TDBADMIN.PREIS WHERE");

	for(i=0; i < MAX_MENU_ITEMS; i++)
		{
		switch(i)
			{
			case MPRE_KAR:
				if (*to_buffers[MPRE_KAR] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MPRE_KAR]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					preis.kar_id=MPAPIselectEntry((int)_KOSTEN_ART, dbbuffer,
					      (char *)&kar, sizeof(KOSTEN_ART), sizeof(preis.kar_id));
					if (preis.kar_id != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " KAR_ID = %d", preis.kar_id);
						(void)strcat(sqlquery, tmp_buffer);
						(void)strcat(sqlquery, " AND");
						exists++;
						}
					}
				break;

			case MPRE_KAT:
				if (*to_buffers[MPRE_KAT] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MPRE_KAT]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					preis.kat_id=MPAPIselectEntry((int)_KATEGORIE, dbbuffer,
					      (char *)&kat, sizeof(KATEGORIE), sizeof(preis.kat_id));
					if (preis.kat_id != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " KAT_ID = %d", preis.kat_id);
						(void)strcat(sqlquery, tmp_buffer);
						(void)strcat(sqlquery, " AND");
						exists++;
						}
					}
				break;

			case MPRE_KON:
				if (*to_buffers[MPRE_KON] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MPRE_KON]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					preis.kont_id=MPAPIselectEntry((int)_KONTINGENT, dbbuffer,
					(char *)&kon, sizeof(KONTINGENT), sizeof(preis.kont_id));
					if (preis.kont_id != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " KONT_ID = %d", preis.kont_id);
						(void)strcat(sqlquery, tmp_buffer);
						(void)strcat(sqlquery, " AND");
						exists++;
						}
					}
				break;

			case MPRE_DLA:
				if (*to_buffers[MPRE_DLA] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MPRE_DLA]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					preis.dla_id=MPAPIselectEntry((int)_DIENST_ANGEBOT, dbbuffer,
					(char *)&dla, sizeof(DIENST_ANGEBOT), sizeof(preis.dla_id));
					if (preis.dla_id != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " DLA_ID = %d", preis.dla_id);
						(void)strcat(sqlquery, tmp_buffer);
						(void)strcat(sqlquery, " AND");
						exists++;
						}
					}
				break;

			case MPRE_DL:
				if (*to_buffers[MPRE_DL] != NULL)
					{
					strcpy(dbbuffer, to_buffers[MPRE_DL]);
					(void)ConvertSpecialChar(dbbuffer, NULL);
					preis.dl_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, dbbuffer,
					   (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(preis.dl_id));
					if (preis.dl_id != (int)_UNDEF)
						{
						(void)sprintf(tmp_buffer, " DL_ID = %d", preis.dl_id);
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

	(void)sprintf(&sqlquery[strlen(sqlquery)-4], " ORDER BY DL_ID, DLA_ID, GLT, KAR_ID, KAT_ID, DLTT_ID, RKR_ID;");
	status=MPAPIdb_sqlquery((int)_PREIS, &sqlmem.buffer, sqlquery,
	                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	pre = (PREIS *)sqlmem.buffer;
	if (anzahl > (int)0 && status == (int)MPOK)
		{
		*buffer = NULL;

		/* table header */
		(void)strcpy(buffer, "\n\n Preisinfo:\n ----------\n\n\n");
		(void)strcpy(outbuf1, "ID   Kostenart             Kategorie             Traegertyp      DLN-Typ              Whr       AP        EP        VP    von      bis\n");
		(void)strcat(buffer, outbuf1);

		for (i=0; i<anzahl; i++)
			{
			if (pre[i].dla_id != (int)_UNDEF && (pre[i].dla_id != old_dlaid ||
			    (pre[i].dla_id == old_dlaid && pre[i].glt != old_dlaglt)) )
				{
				preis.dla_id=(int)MPAPIselectOneId((int)_DLA_VIEW, (int)pre[i].dla_id, (char *)&angebot);
				if (preis.dla_id == (int)_UNDEF ) 
					(void)strcpy(angebot.bez, "FEHLER: DLA NICHT GEFUNDEN");
				(void)strcpy(outbuf2, "Kein Datum");
				if (pre[i].glt != (int)_UNDEF)
					{
					(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
					DateTime.tm_mday=(int)_UNDEF;
					DateTime.tm_mon =(int)_UNDEF;
					DateTime.tm_year=(int)_UNDEF;
					DateTime.tm_hour=(int)_UNDEF;
					DateTime.tm_min =(int)_UNDEF;
					(void)WriteDate(&DateTime, (time_t *)&pre[i].glt, outbuf2);
					}
				(void)sprintf(outbuf1, "\nAngebot: %30.30s\nGueltig ab: %s\n",
				              angebot.bez, outbuf2);
				(void)strcat(buffer, outbuf1);

				/* set old values */
				old_dlaid = pre[i].dla_id;
				old_dlaglt = pre[i].glt;
				}
			else if (pre[i].dl_id != (int)_UNDEF && (pre[i].dl_id != old_dlid ||
			         (pre[i].dl_id == old_dlid && pre[i].glt != old_dlglt)) )
				{
				preis.dl_id=(int)MPAPIselectOneId((int)_DTG_VIEW, (int)pre[i].dl_id, (char *)&Vdl);
				if (preis.dl_id == (int)_UNDEF ) 
					(void)strcpy(Vdl.bez, "FEHLER: DL NICHT GEFUNDEN");
				if (pre[i].glt != (int)_UNDEF)
					{
					(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
					DateTime.tm_mday=(int)_UNDEF;
					DateTime.tm_mon =(int)_UNDEF;
					DateTime.tm_year=(int)_UNDEF;
					DateTime.tm_hour=(int)_UNDEF;
					DateTime.tm_min =(int)_UNDEF;
					(void)WriteDate(&DateTime, (time_t *)&pre[i].glt, outbuf2);
					}
				if (Vdl.a_zeit != (int)_UNDEF)
					{
					(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
					DateTime.tm_mday=(int)_UNDEF;
					DateTime.tm_mon =(int)_UNDEF;
					DateTime.tm_year=(int)_UNDEF;
					DateTime.tm_hour=(int)_UNDEF;
					DateTime.tm_min =(int)_UNDEF;
					(void)WriteDate(&DateTime, (time_t *)&Vdl.a_zeit, outbuf3);
					}
				else
					(void)strcpy(outbuf3, "-");

				(void)sprintf(outbuf1, "\nDienstleistung: %30.30s %15.15s\nGueltig ab: %s\n",
				              Vdl.bez, outbuf3, outbuf2);
				(void)strcat(buffer, outbuf1);

				/* set old values */
				old_dlid = pre[i].dl_id;
				old_dlglt = pre[i].glt;
				}

			/* KOSTEN_ART */
			preis.kar_id=(int)MPAPIselectOneId((int)_KAR_VIEW, (int)pre[i].kar_id, (char *)&kostenart);
			if (preis.kar_id == (int)_UNDEF ) 
				(void)strcpy(kostenart.bez, " ");
			/* KATEGORIE */
			preis.kat_id=(int)MPAPIselectOneId((int)_KAT_VIEW, (int)pre[i].kat_id, (char *)&kategorie);
			if (preis.kat_id == (int)_UNDEF ) 
				(void)strcpy(kategorie.bez, " ");
			/* TRAEGER_TYP */
			preis.dltt_id=(int)MPAPIselectOneId((int)_TTYP_VIEW, (int)pre[i].dltt_id, (char *)&dltt);
			if (preis.dltt_id == (int)_UNDEF ) 
				(void)strcpy(dltt.bez, " ");
			/* DLN TYP */
			preis.rkr_id=(int)MPAPIselectOneId((int)_RKR_VIEW, (int)pre[i].rkr_id, (char *)&reisender_typ);
			if (preis.rkr_id == (int)_UNDEF ) 
				(void)strcpy(reisender_typ.bez, " ");
			/* WAEHRUNG */
			preis.whr_id=(int)MPAPIselectOneId((int)_WAEHRUNG, (int)pre[i].whr_id, (char *)&whr);
			if (preis.whr_id == (int)_UNDEF )
				(void)strcpy(whr.krzl, " ");
			/* DL VONDAT */
			if (pre[i].dl_vondat != (int)_UNDEF)
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&pre[i].dl_vondat, outbuf2);
				}
			else
				(void)strcpy(outbuf2, " ");
			/* DL BISDAT */
			if (pre[i].dl_bisdat != (int)_UNDEF)
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&pre[i].dl_bisdat, outbuf3);
				}
			else
				(void)strcpy(outbuf3, " ");


			(void)sprintf(tmp_buffer, "%-4.0d %-20.20s  %-20.20s  %-15.15s %-20.20s %-5.5s: %8.2f  %8.2f  %8.2f %-8.8s %-8.8s\n",
			      pre[i].pre_id, kostenart.bez, kategorie.bez, dltt.bez, reisender_typ.bez,
			      whr.krzl, pre[i].apr, pre[i].epr, pre[i].vpr, outbuf2, outbuf3);
			(void)strcat(buffer, tmp_buffer);
			}
		}
	else
		{
		UtilMsg((int)MPE_NOPRE, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}

	return(status);
}

