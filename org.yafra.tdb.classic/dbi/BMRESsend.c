/*D***********************************************************
 * Modul:     DBI - booking modul
 *            send RES mask to GUI with KAT overview
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

#define _DEL_RES_DL "DELETE FROM TDBADMIN.RESERVATION \
	WHERE BID = %d AND PERS_ID = %d AND DLG_ID = %d;"
#define _DEL_AKTD_DL "DELETE FROM TDBADMIN.AKT_DETAIL \
	WHERE BID = %d AND PERS_ID = %d AND DLG_ID = %d;"

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMRESsend.c,v 1.4 2009-01-02 16:51:35 mwn Exp $";

int BMRESsend(int len, char *buffer)
{
	extern BUCHUNG bch;
	extern BCH_DLN bd;
	extern PERSONEN pers;
	extern REISENDER rei;
	extern RESERVATION res;
	extern DIENST_ANGEBOT dla;
	extern DIENSTLEISTUNG dtg;
	extern DIENST_TRAEGER dlt;
	extern TRAEGER_VIEW trv;
	extern TRAEGER_TYP dltt;
	extern STATUS_WERTE sta;
	extern PREIS pre;
	extern KONTINGENT kon;
	extern char glob_dtg_res[];
	extern char glob_dl_bch[];
	extern int glob_teil;
	extern int sprache;
	extern unsigned char bm_obj;
	extern unsigned int  bm_dlncnt;

	PREIS cntrlpre;
	TTYP_VIEW dlttv;
	unsigned char oldmenunr;
	unsigned char selectflag;
	char query[_QUERYLEN];
	char buffer1[20*RECLAENGE];
	char buffer2[RECLAENGE];
	char buff_1[5], buff_2[5], buff_3[_RECORDLEN];
	char bez1[_RECORDLEN];
	char bez2[_RECORDLEN];
	char katlabel[_RECORDLEN];
	char preistext[_BEZLEN+1];
	char colorlabel[_BEZLEN+1];
	char dlnbez[_RECORDLEN];
	char resstabez[_BEZLEN+1];
	char konbez[_BEZLEN+1];
	char dltbez[(2*_BEZLEN)+6];
	char dlttbez[(2*_BEZLEN)+6];
	char text[4*_RECORDLEN];
	char *color;
	char *ptr;
	int i;
	int id;
	int anzahl;
	int status;
	int founddl = (int)_UNDEF;
	int arrdl_teil, arrdl_prio;
	long tmplen;
	unsigned long dlen = 0;
	unsigned long alen = 0;
	struct tm DateTime;
	KAT_VIEW *kv = NULL;
	RESERVATION *reservation = NULL;

	if (bm_obj == (unsigned char)_ARRANGEMENT)
		{
		sscanf(buffer, "%4c%4c", buff_1, buff_2);
		buff_1[4] = NULL;
		buff_2[4] = NULL;
		arrdl_teil = atoi(buff_1);
		arrdl_prio = atoi(buff_2);
		glob_teil = arrdl_teil; /* save the arr part, so we know which one if same DLs in 1 ARR */

		ptr = strchr(buffer, ':');
		ptr++;
		(void)strcpy(buffer, ptr);

		(void)strcpy(glob_dtg_res, buffer);
		res.dlg_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, buffer, (char *)&dtg,
		    sizeof(dtg), sizeof(dtg.dlg_id));
		}
	else
		{
		/* if a DL is set in the main BM mask then take this one as booking DL */
		if (*glob_dl_bch == NULL)
			(void)strcpy(glob_dtg_res, buffer);
		else
			{
			(void)strcpy(glob_dtg_res, glob_dl_bch); /*!!! just quick and dirty*/
			(void)strcpy(buffer, glob_dl_bch);
			}
		res.dlg_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, buffer, (char *)&dtg,
		    sizeof(dtg), sizeof(dtg.dlg_id));
		}

	/* check if a DIENSTLEISTUNG was found in the choose-string */
	if (res.dlg_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NODL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* if the ACTION on BMDLN is DELETE then delete all RES of choosed DL */
	if (ACTIONTYP == (unsigned char)MPDELETE)
		{
		(void)sprintf(query, _DEL_RES_DL, bch.bid, rei.pers_id, dtg.dlg_id);
		status = MPAPIdb_sqlcommand(query, &anzahl);
		if (status == (int)MPOK)
			{
			(void)sprintf(query, _DEL_AKTD_DL, bch.bid, rei.pers_id, dtg.dlg_id);
			status = MPAPIdb_sqlcommand(query, &anzahl);
			}
		if (status != (int)MPOK)
			{
			UtilMsg((int)status, MSGTYP_DBERROR, NULL);
			status = (int)MPERROR;
			}
		COMMTYP = (unsigned char)BMEND;
		return((int)status);
		}

	/* get DLT from choosen DL */
	status = MPAPIselectDLT((int)_UNDEF, (int)_UNDEF, res.dlg_id, &dlt);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODLT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	dltt.host_typ = dlt.typ_id;

	/* get current res datas for bid, uid and dlid */
	if (ACTIONTYP == (unsigned char)UPDATE)
		{
		dlen = alen = 0;
		(void)sprintf(query, _SEL_RES_BCHDLN_DL, bch.bid, rei.pers_id,
		              dtg.dlg_id);
		status=MPAPIdb_sqlquery((int)_RESERVATION, (char **)&reservation,
		                        query, &anzahl, &dlen, &alen);
		if (status != (int)MPOK)
			{
			UtilMsg((int)MPE_NORES, MSGTYP_ERROR, NULL);
			MPfree((void *)reservation);
			return((int)MPERROR);
			}
		if (anzahl < 1)
			ACTIONTYP = (unsigned char)INSERT;
		}

	/* set price view */
	cntrlpre.kar_id = (int)_UNDEF;
	cntrlpre.rkr_id = (int)_UNDEF;
	cntrlpre.kat_id = (int)_UNDEF;
	cntrlpre.kont_id = (int)_UNDEF;
	cntrlpre.dl_id = dtg.dlg_id;
	cntrlpre.dla_id = dla.dla_id;

	/* section -1- menu info titel */
	(void)strcpy(buffer2, glob_dtg_res);
	sprintf(buffer, "1\n3\n%s\t%d\t%s\t",
	              buffer2, bch.bid, bch.ref);

	/* section -2- kategorie scroll list */
	(void)strcat(buffer, "2\n");
	UtilMsgGet((int)MPI_BMKATTITEL, MSGTYP_INFO, buffer2);
	(void)strcat(buffer, buffer2);
	(void)strcat(buffer, "\n");

	/* hole alle Kategorien zu einer DL mit einem DLT */
	/* Tabelleninhalt - alle Kategorien der gew�hlten Dienstleistung */
	dlen = alen = 0;
	(void)sprintf(buffer2, _SEL_KATVIEW_DLT, dlt.dlt_id, sprache);
	status=MPAPIdb_sqlquery((int)_KAT_VIEW, (char **)&kv, buffer2, &anzahl,
		                      &dlen, &alen);
	if (status == (int)MPOK && anzahl > 0)
		{
		(void)sprintf(buffer2, "%d\n", anzahl);
		(void)strcat(buffer, buffer2);
		for (i=0; i<anzahl; i++)
			{
			selectflag = '0';

			/*protocol: KATID\tCOLORSTRING\tLABEL\tSELECTFLAG\n */

			sta.typ=(int)_GA;
			id = MPAPIselectOneId((int)_STATUS_WERTE, kv[i].ga, (char *)&sta);
			if (id == (int)_UNDEF)
				(void)strcpy(sta.sta, "red");
			(void)copyTextTo(colorlabel, (char *)sta.sta, (int)_BEZLEN);
			(void)copyTextTo(bez1, (char *)kv[i].bez, (int)_BEZLEN);
			status = MPAPIpre_getprice((int)_KATEGORIE, kv[i].kat_id,
			         &cntrlpre, &pre, preistext);
			if (status == (int)MPOK)
				sprintf(katlabel, "%30.30s    %s", kv[i].bez, preistext);
			else
				sprintf(katlabel, "%30.30s", kv[i].bez);
			if (ACTIONTYP == (unsigned char)UPDATE &&
			    reservation[0].kat_id == kv[i].kat_id)
				selectflag = '1';
			(void)sprintf(buffer2, "%d\t%s\t%s\t%c\n", kv[i].kat_id, colorlabel,
			                                       katlabel, selectflag);
			(void)strcat(buffer, buffer2);
			}
		}
	else
		(void)strcat(buffer, "0\n");

	/* section -3-  button fields */
	if (bm_dlncnt == 1)
		{
		/* fill up the DLN field only if only one DLN is entered */
		id = MPAPIselectOneId((int)_PERSONEN, rei.pers_id, (char *)&pers);
		(void)copyTextTo(bez1, (char *)pers.name, (int)_CHAR512);
		(void)copyTextTo(bez2, (char *)rei.vor, (int)_CHAR512);
		(void)sprintf(dlnbez, "%d : %s : %s", rei.pers_id, bez1, bez2);
		}
	else
		*dlnbez = NULL;
	*resstabez = NULL;
	*dltbez = NULL;
	*dlttbez = NULL;
	*bez1 = NULL;
	*bez2 = NULL;
	*konbez = NULL;
	*text = NULL;
	sta.typ=(int)_R_STA;
	if (ACTIONTYP == (unsigned int)INSERT)
		{
		id = MPAPIselectOneId((int)_STATUS_WERTE, _RES_ENTER, (char *)&sta);
		if (id != (int)_UNDEF)
			id = SelectBez((int)_R_STA, sprache, sta.bez_id, resstabez);
		}
	else
		{
		id = MPAPIselectOneId((int)_STATUS_WERTE, reservation[0].r_sta, (char *)&sta);
		if (id != (int)_UNDEF)
			id = SelectBez((int)_R_STA, sprache, sta.bez_id, resstabez);
		}
	if (ACTIONTYP == (unsigned int)UPDATE)
		{
		/* DIENST_TRAEGER */
		id = MPAPIselectOneId((int)_TRAEGER_VIEW, reservation[0].dlt_id, (char *)&trv);
		if ( id != (int)_UNDEF )
			{
			(void)copyTextTo(buffer2, trv.bez, (int)_BEZLEN);
			(void)strcpy(dltbez, buffer2);
			(void)strcat(dltbez, TRENNER);
			(void)copyTextTo(buffer2, trv.bez, (int)_BEZLEN);
			(void)strcat(dltbez, buffer2);
			}

		/* TRAEGER_TYP */
		id = MPAPIselectOneId((int)_TTYP_VIEW, (int)reservation[0].typ_id, (char *)&dlttv);
		if (id != (int)_UNDEF)
			{
			(void)copyTextTo(buffer2, dlttv.bez, (int)_BEZLEN);
			(void)strcat(dlttbez, buffer2);
			(void)strcat(dlttbez, TRENNER);
			(void)copyTextTo(buffer2, dlttv.hbez, (int)_BEZLEN);
			(void)strcat(dlttbez, buffer2);
			}
		(void)strcat(buffer, "\t");

		/* UNDEF  anfangs zeit */
		if (reservation[0].a_zeit > 1)
			{
			/* DATUM  Anfangszeit der Dienstleistung */
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			DateTime.tm_hour=(int)0;
			DateTime.tm_min =(int)0;
			(void)WriteDate(&DateTime, (time_t *)&reservation[0].a_zeit, bez1);
			}

		/* UNDEF  end zeit */
		if (reservation[0].e_zeit > 1)
			{
			/* DATUM  Endezeit der Dienstleistung */
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			DateTime.tm_hour=(int)0;
			DateTime.tm_min =(int)0;
			(void)WriteDate(&DateTime, (time_t *)&reservation[0].e_zeit, bez2);
			}

		/* KONTINGENT */
		id = MPAPIselectOneId((int)_KONTINGENT, reservation[0].kont_id, (char *)&kon);
		if ( id != (int)_UNDEF )
			(void)SelectBez((int)_KONTINGENT, sprache, kon.bez_id, konbez);

		/* TEXTE */
		id =  SelFromTxt(reservation[0].textid, sprache, (int)_RESERVATION, text);
		}
	(void)sprintf(buffer2, "3\n9\n%s\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\t\0", dlnbez,
	              resstabez, dltbez, dlttbez, bez1, bez2, konbez, text);
	(void)strcat(buffer, buffer2);


	COMMTYP = (unsigned char)BMBOOK;

	MPfree((void *)kv);
	MPfree((void *)reservation);

	return((int)MPOK);
}
