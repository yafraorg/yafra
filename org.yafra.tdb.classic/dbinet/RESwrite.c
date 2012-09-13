/*D***********************************************************
 * Modul:     NET - write a complete BUCHUNG with RES, AKTD
 *
 * Copyright: yafra.org, Switzerland
 **************************************************************/
#include <mpnet.h>
#include <mpmsg.h>
#include <mpsqlsel.h>
#include <mpsqlupd.h>
#include <mpstadef.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbinet/RESwrite.c,v 1.4 2009-01-02 16:51:35 mwn Exp $";

/* for detailed documentation see on the intranet under TO Internet modul */
/* field count from the mpeubook2.pl */
#define _MPNET_SPLITBCHCNT 17
/* 0 = ARR ID */
/* 1 = DL ID */
/* 2 = KAT ID */
/* 3 = Kunden Name */
/* 4 = Kunden Vorname */
/* 5 = Kunden Strasse */
/* 6 = Kunden PLZ */
/* 7 = Kunden Ort */
/* 8 = Kunden FAX */
/* 9 = Kunden Tel */
/* 10 = Kunden email */
/* 11 = DL VON Datum */
/* 12 = Anzahl Tage der DL */
/* 13 = Anzahl Reisender */
/* 14 = Reisender (beinhaltet je 4 Felder: Name, Vorname, Alter, Nat.) */
/* 15 = Buchungstext */
/* 16 = BuchungsId bei zusaetzlichen DL's */
/* 17 = KundenId bei existierendem Kunden */

/*************************************************************
 * function:  KAPA VIEW make information string
 * typ:       public
 * desc:      get KAPA VIEW entries for a DL or ARR
 * input:     DL or ARR ID as char buffer (dlid\tarrid\t\0)
 *************************************************************/
int RESinsert(char *aInbuf, PSmemobj *aOutbuf)
{
	extern int sprache;
	extern int DebugFlag;
	extern MP_PROFIL prof;
	extern PERSONEN pers;
	extern PERSADR adr;
	extern KUNDEN kun;
	extern KUN_VIEW kunv;
	extern BUCHUNG bch;
	extern BCH_DLN bd;
	extern REISENDER dln;
	extern DIENSTLEISTUNG dl;
	extern ARRANGEMENT arr;
	extern KATEGORIE kat;
	extern RESERVATION res;
	extern SPRACHEN spr;
	extern KUNDEN_TYP kunt;
	extern LAND land;
	extern WAEHRUNG whr;
	extern TEXTE txt;

	BCH_DLN *all_bd    = (BCH_DLN *)NULL;

	char **splitbuffer;
	int anzsplit;
	char **dlnbuffer;
	int anzdlnsplit;
	char onedln[_BEZLEN+1][1];
	char *dlnptr;
	char *tmpptr;
	char attr1[_BEZLEN+1];
	char dln_name[_BEZLEN+1];
	char dln_vorname[_BEZLEN+1];
	char dln_alter[_BEZLEN+1];
	char dln_nat[_BEZLEN+1];
	char dln_sex[_BEZLEN+1];
	char tmpbuf[_RECORDLEN];
	char query[_QUERYLEN];

	int status=(int)MPOK;
	int cret = MPOK;
	int anzdln;
	int i;
	int id;
	size_t len;
	struct tm DateTime;

	int old_bid        = (int)_UNDEF;
	int existing_kid   = (int)_UNDEF;
	int anzbd          = 0;
	unsigned long dlen = 0;
	unsigned long alen = 0;

	if (DebugFlag)
		PSSYSdebug(MPNET_DBGFILE, NULL, "welcome to RESwrite");

	/* Init the aOutbuf memory */
	aOutbuf->datalen = _RECORDLEN;
	if (aOutbuf->datalen > aOutbuf->alloclen)
		aOutbuf->buffer = PSSYSallocobj(aOutbuf, PSMEMCHUNK30);
	(void)sprintf(aOutbuf->buffer, "%d\n%d\n%d\n", PSOK, 1, 1);

	/* split incomming fields from CGI script */
	if (aInbuf != NULL && *aInbuf != NULL)
		{
		splitbuffer = (char **)MPAPIbufferSplit(aInbuf, &anzsplit, (char)'\b');
		if (splitbuffer == NULL || anzsplit != 18)
			{
			UtilMsg((int)MPE_SPLIT, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}

	/* set important ID's */
	arr.arr_id = atoi(splitbuffer[0]);
	dl.dlg_id = atoi(splitbuffer[1]);
	kat.kat_id = atoi(splitbuffer[2]);
	anzdln = atoi(splitbuffer[13]);

	old_bid = atoi(splitbuffer[16]);
	if ( strcmp(splitbuffer[16], "0") == (int)MPOK )
		{
		old_bid = (int)_UNDEF;
		}
	else if ( strlen(splitbuffer[16]) > 0 && old_bid == 0)
		{
		UtilMsg((int)MPE_NOBCH, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	existing_kid = atoi(splitbuffer[17]);
	if ( strcmp(splitbuffer[17], "0") == (int)MPOK )
		{
		existing_kid = (int)_UNDEF;
		}
	else if ( strlen(splitbuffer[17]) > 0 && existing_kid == 0)
		{
		UtilMsg((int)MPE_NOKUNT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (anzdln < 1 && old_bid == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NODLN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	DateTime.tm_hour=(int)0;
	DateTime.tm_min =(int)0;
	(void)ReadDate(&DateTime, (time_t *)&res.a_zeit, splitbuffer[11]);
/*
	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	DateTime.tm_hour=(int)0;
	DateTime.tm_min =(int)0;
	(void)ReadDate(&DateTime, (time_t *)&res.e_zeit, splitbuffer[12]);
*/
	res.e_zeit = res.a_zeit + (24*60*60)*(atoi(splitbuffer[12]));


	if ( old_bid == (int)_UNDEF )
		{

/*------------------------------------*/
		if (DebugFlag)
			PSSYSdebug(MPNET_DBGFILE, NULL, "inserting KUNDE now");

		if ( existing_kid > 0 )
			{
			id = MPAPIselectOneId((int)_KUN_VIEW, existing_kid, (char *)&kunv);
			if ( id == (int)_UNDEF )
				{
				UtilMsg((int)MPE_NOKUNT, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			else
				{
				(void)copyTextTo((char *)attr1, kunv.attr1, (int)_BEZLEN);
				if (strcmp(splitbuffer[10], attr1) != (int)MPOK)
					{
					UtilMsg((int)MPE_NOCHOOSE, MSGTYP_ERROR, NULL);
					return((int)MPERROR);
					}
				kun.pers_id = kunv.kun_id;
				bch.kid = kunv.kun_id;
				pers.s_id = sprache;
				(void)copyTextTo((char *)adr.ort, kunv.ort, (int)_BEZLEN);
				}
			}
		else
			{

			/* insert KUNDE + ADR */
			pers.pers_id = (int)_UNDEF;
			pers.sta_id = (int)_UNDEF;
				pers.pers_typ = (int)_PERS_FIRMEN;
			pers.s_id = sprache;
			pers.textid = (int)_UNDEF;
				(void)copyTextTo((char *)pers.name, splitbuffer[3], (int)_BEZLEN);
			(void)copyTextTo((char *)adr.ort, splitbuffer[7], (int)_BEZLEN);
			cret = MPAPIinsertEntry((int)_PERSONEN, (char *)&pers, (BEZEICHNUNG *)NULL);
			if (cret != (int)MPOK)
				return(cret);

			adr.pers_id = pers.pers_id;
			adr.land_id = (int)1;
			*adr.kant = (char)NULL;
			*adr.adr2 = (char)NULL;
			*adr.adr3 = (char)NULL;
			adr.sta_id = (int)_UNDEF;
			(void)copyTextTo((char *)adr.ans, splitbuffer[4], (int)_BEZLEN);
				(void)copyTextTo((char *)adr.adr1, splitbuffer[5], (int)_BEZLEN);
			(void)copyTextTo((char *)adr.plz, splitbuffer[6], (int)_BEZLEN);
			cret = MPAPIinsertEntry((int)_PERSADR, (char *)&adr, (BEZEICHNUNG *)NULL);
			if (cret != (int)MPOK)
				return(cret);

			kun.pers_id = pers.pers_id;
			kun.k_typ_id = (int)1;           /*!! hardcoded */
			kun.whr_id = (int)1;
			*kun.konto = (char)NULL;
			*kun.attr2 = (char)NULL;
			(void)copyTextTo((char *)kun.fax, splitbuffer[8], (int)_BEZLEN);
			(void)copyTextTo((char *)kun.tel, splitbuffer[9], (int)_BEZLEN);
			(void)copyTextTo((char *)kun.attr1, splitbuffer[10], (int)_BEZLEN);
			cret = MPAPIinsertEntry((int)_KUNDEN, (char *)&kun, (BEZEICHNUNG *)NULL);
			if (cret != (int)MPOK)
				return(cret);

			}
/*------------------------*/

		if (DebugFlag)
			PSSYSdebug(MPNET_DBGFILE, NULL, "inserting BUCHUNG now");

		/* insert BUCHUNG with KUNDE as RECHST */
		bch.d_bid = (int)_UNDEF;
		bch.bid = (int)_UNDEF;
		*bch.ref = NULL;
		bch.arr_id = arr.arr_id;
		(void)copyTextTo(bch.anw, prof.mpuser, (int)_USERLEN);
		(void)strcpy(bch.sach, "-");
		(void)time((time_t *)&bch.b_dat);  /* Buchungsdatum setzen */
		(void)time((time_t *)&bch.m_dat);  /* Modifikationsdatum */
		bch.opt_bst = (int)_UNDEF;
		bch.opt_kid = (int)_UNDEF;
		bch.ast = _BCH_EXTWWW;
		bch.sta = _BCH_ENTER;
		bch.sai_id = (int)1;  /*!! muss von der DL oder ARR gelesen werden */
		bch.k_id = (int)_UNDEF;
		bch.kid = kun.pers_id;
		bch.history = (int)_UNDEF;
		bch.b_text = (int)_UNDEF;
		if (*splitbuffer[15] != NULL)
			{
			txt.typ    = (int)_BUCHUNG;
			txt.s_id   = sprache;
			txt.textid = bch.b_text;
			bch.b_text = TXTinsert(splitbuffer[15]);
			}
		cret = MPAPIinsertEntry((int)_BUCHUNG, (char *)&bch, (BEZEICHNUNG *)NULL);
		if (cret != (int)MPOK)
			return(cret);

		bd.bid = bch.bid;
		res.bid = bch.bid;
		if (*splitbuffer[14] != NULL)
			{
			dlnbuffer = (char **)MPAPIbufferSplit(splitbuffer[14], &anzdlnsplit, (char)'\n');
			if (anzdlnsplit == (int)0 && *splitbuffer[14] != (char)NULL)
				anzdlnsplit = 1;
			if ((anzdlnsplit > 1 && dlnbuffer == NULL) || anzdlnsplit < anzdln)
				{
				UtilMsg((int)MPE_SPLIT, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			}

		if (DebugFlag)
			PSSYSdebug(MPNET_DBGFILE, NULL, "inserting DLNs now");

		}
	else
		{
		if ( existing_kid > 0 )
			{
			id = MPAPIselectOneId((int)_KUN_VIEW, existing_kid, (char *)&kunv);
			if ( id == (int)_UNDEF )
				{
				UtilMsg((int)MPE_NOKUNT, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			else
				{
				(void)copyTextTo((char *)attr1, kunv.attr1, (int)_BEZLEN);
				if (strcmp(splitbuffer[10], attr1) != (int)MPOK)
					{
					UtilMsg((int)MPE_NOCHOOSE, MSGTYP_ERROR, NULL);
					return((int)MPERROR);
					}
				kun.pers_id = kunv.kun_id;
				bch.kid = kunv.kun_id;
				}
			}
		else
			{
			UtilMsg((int)MPE_NOKUNT, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		(void)sprintf(query, _SEL_BD_BCH, old_bid);
		status = MPAPIdb_sqlquery((int)_BCH_DLN, (char **)&all_bd, query,
	                	&anzbd, &dlen, &alen);
		if (anzbd > (int)0 && status == (int)MPOK)
			{
			anzdln=anzbd;
			id = MPAPIselectOneId((int)_BUCHUNG, old_bid, (char *)&bch);
			if ( bch.bid == (int)_UNDEF)
				{
				UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			/* check the KundenID with the booking */
			if (bch.kid != kunv.kun_id)
				{
				UtilMsg((int)MPE_NOKUNT, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			}
		else
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}


	/* insert REI */
	for (i = 0; i < anzdln; i++)
		{
		if ( anzbd == (int)0 && old_bid == (int)_UNDEF )
			{
			if (anzdln == 1)
				dlnptr = splitbuffer[14];
			else
				dlnptr = dlnbuffer[i];
			len = strlen(dlnptr);
			if (dlnptr[len - 1] == '\r')
				dlnptr[len - 1] = (char)NULL;

			/* NAME */
			tmpptr = strpbrk(dlnptr, ", ");
			if (tmpptr != (char)NULL)
				*tmpptr = (char)NULL;
			(void)strcpy(dln_name, dlnptr);
			dlnptr = (tmpptr + 2);

			/* VORNAME */
			tmpptr = strpbrk(dlnptr, ", ");
			if (tmpptr != (char)NULL)
				*tmpptr = (char)NULL;
			(void)strcpy(dln_vorname, dlnptr);
			dlnptr = (tmpptr + 2);

			/* SEX */
			tmpptr = strpbrk(dlnptr, ", ");
			if (tmpptr != (char)NULL)
				*tmpptr = (char)NULL;
			(void)strcpy(dln_sex, dlnptr);
			dlnptr = (tmpptr + 2);

			/* NATIONALITAET */
			(void)strcpy(dln_nat, dlnptr);

			/* insert PERSONEN - inherit all except name */
			pers.pers_id = (int)_UNDEF;
			pers.pers_typ = (int)_PERS_PRIVAT;
			(void)copyTextTo((char *)pers.name, dln_name, (int)_BEZLEN);
			cret = MPAPIinsertEntry((int)_PERSONEN, (char *)&pers, (BEZEICHNUNG *)NULL);
			if (cret != (int)MPOK)
				return(cret);

			/* insert ADRESSE - inherit all */
			adr.pers_id = pers.pers_id;
			cret = MPAPIinsertEntry((int)_PERSADR, (char *)&adr, (BEZEICHNUNG *)NULL);
			if (cret != (int)MPOK)
				return(cret);

			/* insert REISENDER */
			dln.pers_id = pers.pers_id;
			(void)copyTextTo((char *)dln.vor, dln_vorname, (int)_BEZLEN);
			dln.rkr_id = 1;
			dln.sex = atoi(dln_sex);
			dln.mutters_id = (int)_UNDEF;
			(void)copyTextTo((char *)dln.age, dln_alter, (int)_BEZLEN);
			(void)strcpy(dln.passnr, "-");
			(void)copyTextTo((char *)dln.attr1, dln_nat, (int)_BEZLEN);
			*dln.attr2 = (char)NULL;
			cret = MPAPIinsertEntry((int)_REISENDER, (char *)&dln, (BEZEICHNUNG *)NULL);
			if (cret != (int)MPOK)
				return(cret);

			/* insert BCH_DLN */
			bd.dln_id = dln.pers_id;
			cret = MPAPIinsertEntry((int)_BCH_DLN, (char *)&bd, (BEZEICHNUNG *)NULL);
			if (cret != (int)MPOK)
				return(cret);

			}
		else if ( anzbd > (int)0 && old_bid != (int)_UNDEF )
			{
			dln.pers_id = all_bd[i].dln_id;
			}

		/* insert RES */
		/* insert AKTD */
		/* update KAPA */
		res.dlg_id = dl.dlg_id;
		res.dl_id = (int)_UNDEF;
		res.pers_id = dln.pers_id;
		res.teil = (int)_UNDEF;
		res.dlt_id = (int)_UNDEF;
		res.typ_id = (int)_UNDEF;
		res.bid = bch.bid;
		res.kont_id = (int)_UNDEF;
		res.kat_id = kat.kat_id;
		res.k_kon = (int)_UNDEF;
		res.b_kon = (int)_UNDEF;
		res.r_sta = (int)_UNDEF;
		res.sai_id = (int)_UNDEF;
		res.textid = (int)_UNDEF;
		cret = RESwrite(bch.bid, dln.pers_id, res.dlg_id, 0, (int *)NULL, &res);
		if (cret == (int)MPOK)
			cret = AKTDwrite(bch.bid, dln.pers_id, res.dlg_id, &res);
		if (cret != (int)MPOK)
			return(cret);

		if (DebugFlag)
			PSSYSdebug(MPNET_DBGFILE, NULL, "insert of DLN no %d done", i);
		}

	MPfreearray(splitbuffer, anzsplit);
	if (anzdlnsplit > (int)1 && old_bid == (int)_UNDEF)
		MPfreearray(dlnbuffer, anzdlnsplit);
	else if ( old_bid != (int)_UNDEF)
		MPfree((char *)all_bd);

	(void)sprintf(tmpbuf, "%d\t%d\r\n", bch.bid, bch.kid);
	(void)strcat(aOutbuf->buffer, tmpbuf);
	aOutbuf->datalen = strlen(aOutbuf->buffer);

	if (DebugFlag)
		PSSYSdebug(MPNET_DBGFILE, NULL, "free up and return from RESwrite");

	return(cret);
}

/*F***********************************************************
 * Function:  Write RES
 *            in INS mode delete default entries and write new ones
 *            in UPD mode change fields KAT/DLT/KONT/RESSTA/DAT
 *            in DEL mode delete all entries
 *
 * In/Out:    BCH id, DLN id, DL id, TDL count and ids, RES data
 *            ACTIONTYP must be set right
 * Out:       status
 **************************************************************/
int RESwrite(int bid, int uid, int dlid, int tdlcnt,
             int *tdlids, RESERVATION *newres)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int DebugFlag;
	extern unsigned char bm_obj;
	extern unsigned int  bm_dlncnt;  /* num. of dln to book in sequence */
	                                 /* controlled by BMRESinput()      */
	extern ARRANGEMENT arr;
	extern DLG_PART dlg;
	extern KONTINGENT kon;
	extern TEXTE txt;

	RESERVATION writeres;
	RESERVATION *reservation;
	DLG_DLG *dldlg;
	ARR_DLG arrdl;
	AKT_DETAIL aktdet;
	KONT_DETAIL aKd;
	KATEGORIE reskat;
	DIENST_TRAEGER resdlt;
	char query[_QUERYLEN];
	char message[_RECORDLEN];
	char konbez[_RECORDLEN];
	char format[_RECORDLEN];
	int status = (int)MPOK;
	int cret;
	int rescnt, dlpartcnt;
	int i;
	int id;
	int space;
	int dltbchid;
	int dltkontid;
	int countdln;
	int set_tdl_undef_flag;
	int busyvalue;

	/* fucking memory job */
	if (newres == NULL)
		return((int)MPERROR);

	/* check up bid */
	if (bid < 1)
		{
		UtilMsg((int)MPE_NOBCH, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* init */
	space = 1;
	writeres.bid = bid;
	writeres.pers_id = uid;
	txt.typ = (int)_RESERVATION;
	txt.s_id = sprache;

	/* get host TDL from DL */
	id = MPAPIselectTDL(dlid, &dlg);

	/* set init TEIL number */
	writeres.teil = MPAPIid_max((int)_RESERVATION, (int)_ORD, (char *)&writeres);
	writeres.teil = writeres.teil + 1;
	if (writeres.teil < 1)
		writeres.teil = 1;

	/* if it's an ARRANGEMENT booking and the DIENSTLEISTUNG entered is */
	/* an other priotiry then the already entered, delete the old */
	/* priority first here */
	if (bm_obj == (unsigned char)_ARRANGEMENT)
		{
		arrdl.teil = (int)_UNDEF;
		arrdl.arr_id = arr.arr_id;
		arrdl.dlg_id = dlid;
		(void)MPAPIselectOneId((int)_ARR_DLG, arrdl.arr_id, (char *)&arrdl);
		writeres.teil = arrdl.teil;

		/* get all TEIL-reservations to check priority */
		(void)sprintf(query, _SEL_RES_BCHDLN_TEIL, bid, uid, writeres.teil);
		status=MPAPIdb_sqlquery((int)_RESERVATION, &sqlmem.buffer,
		         query, &rescnt, &sqlmem.datalen, &sqlmem.alloclen);
		reservation = (RESERVATION *)sqlmem.buffer;
		if (status != (int)MPOK)
			{
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		if (rescnt > 0)
			{
			/* delete RES + AKT_DETAIL entry if it is another priority */
			if (reservation[0].dlg_id != dlid)
				{
				status = MPAPIdeleteEntry((int)_RESERVATION, (char *)&reservation[0]);
				if (status != (int)MPOK)
					{
					UtilMsg(status, MSGTYP_DBERROR, NULL);
					return((int)MPERROR);
					}
				/* delete TEXTE */
				txt.textid = reservation[0].textid;
				if (txt.textid > 0)
					{
					cret = MPAPIdeleteEntry((int)_TEXTE, (char *)&txt);
					if (cret != (int)MPOK && DebugFlag)
						MPsyslog(_LOGMP, MPDEBUG, "Konnte Reservationstext nicht loeschen");
					}
				aktdet.bid = reservation[0].bid;
				aktdet.pers_id = reservation[0].pers_id;
				aktdet.teil = reservation[0].teil;
				status = MPAPIdeleteEntry((int)_AKT_DETAIL, (char *)&aktdet);
				if (status != (int)MPOK)
					{
					UtilMsg(status, MSGTYP_DBERROR, NULL);
					return((int)MPERROR);
					}
				}
			}
		}

	/* hole alle Eintraege mit dlid und mache delete und insert */
	/* falls kein eintrag vorhanden */

	/* read already entered reservations (if there are any) and delete */
	/* them. If there are no entries, it's an INSERT of a new TEIL */
	(void)sprintf(query, _SEL_RES_BCHDLN_DL, bid, uid, dlid);
	status=MPAPIdb_sqlquery((int)_RESERVATION, &sqlmem.buffer,
	         query, &rescnt, &sqlmem.datalen, &sqlmem.alloclen);
	reservation = (RESERVATION *)sqlmem.buffer;
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}
	if (rescnt > 0) /* that means something is already here with this dlid */
		{
		/* MPAPIdeleteEntry deletes all RES on a BCH - DLN - DL */
#ifdef _NICHT_MEHR_LOESCHEN
		writeres.teil = reservation[0].teil; /* take values of the first found */
		status = MPAPIdeleteEntry((int)_RESERVATION, (char *)&reservation[0]);
		if (status != (int)MPOK)
			{
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		/* delete TEXTE */
		txt.textid = reservation[0].textid;
		if (txt.textid > 0)
			{
			cret = MPAPIdeleteEntry((int)_TEXTE, (char *)&txt);
			if (cret != (int)MPOK && DebugFlag)
				MPsyslog(_LOGMP, MPDEBUG, "Konnte Reservationstext nicht loeschen");
			}
		/* if it's a KONTINGENT booking and it's a KATEGORIE KONTINGENT, */
		/* decrement FREE field in KONT_DETAIL table */
		if (reservation[0].kont_id != (int)_UNDEF && reservation[0].kat_id != (int)_UNDEF)
			{
			/* look if there is a KONTINGENT with this KAT and/or DLT */

			/* decrement busy counter of KONT_DETAIL */
			(void)sprintf(query, _UPD_KOND_DELONE, reservation[0].kont_id, reservation[0].kat_id);
			status = MPAPIdb_sqlcommand(query, &i);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				return((int)MPERROR);
				}
			}
		/* manage KAPA table */
		if (reservation[0].kat_id != (int)_UNDEF && dlg.dl_id != (int)_UNDEF)
			{
			(void)sprintf(query, _UPD_KAPA_DELONE, dlg.dl_id, reservation[0].kat_id);
			status = MPAPIdb_sqlcommand(query, &i);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				return((int)MPERROR);
				}
			}
#endif
		}

	/* if upd or ins do it now, else we deleted already everything ! */
	if (ACTIONTYP != (unsigned char)MPDELETE)
		{
		/* init new reservation */
		writeres.dlg_id = dlid;
		writeres.kont_id = newres->kont_id;
		writeres.a_zeit = newres->a_zeit;
		writeres.e_zeit = newres->e_zeit;
		writeres.r_sta = newres->r_sta;
		writeres.sai_id = newres->sai_id;
		writeres.k_kon = newres->k_kon;
		writeres.b_kon = newres->b_kon;
		writeres.dlt_id = newres->dlt_id;
		writeres.kat_id = newres->kat_id;
		writeres.typ_id = newres->typ_id;
		writeres.textid = newres->textid;

		/* check reservation typ */
		switch(dlg.res_f)
			{
			case (int)_RES_IMPOSSIBLE:
				UtilMsg((int)MPE_RESIMPOSSIBLE, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				break;
			case (int)_RES_BOOLEAN:
			case (int)_RES_STATIC:
				if (writeres.a_zeit > 0 || writeres.e_zeit > 0)
					{
					UtilMsg((int)MPE_NORESDAT, MSGTYP_ERROR, NULL);
					writeres.a_zeit = 0;
					writeres.e_zeit = 0;
				/*	return((int)MPERROR); */
					}
				break;
			case (int)_RES_DYNAMIC:
				if (writeres.a_zeit < 1 || writeres.e_zeit < 1)
					{
					UtilMsg((int)MPE_NORESDAT, MSGTYP_ERROR, NULL);
					return((int)MPERROR);
					}
				break;
			}
		/* check saison */
		if (writeres.sai_id == (int)_UNDEF)
			writeres.sai_id = dlg.sai_id;

		/* add count of booked KONTINGENTE or KAPA */
		if (newres->kont_id != (int)_UNDEF && newres->kat_id != (int)_UNDEF)
			{
			/* look if there is a KONTINGENT with this KAT and/or DLT */
			if ( newres->dlt_id == (int)_UNDEF )
				{
				/*--- Check gtee Kontingent Anzahl ---*/
				aKd.hostkont_id = (int)_UNDEF;
				aKd.kont_id = newres->kont_id;
				aKd.kat_id  = newres->kat_id;
				aKd.dlt_id  = (int)_UNDEF;
				aKd.sta_id = (int)0; /*--- Indikator ob Eintrag vorhanden ---*/
				(void)MPAPIselectOneId((int)_KONT_DETAIL, newres->kont_id, (char *)&aKd);
				if ( aKd.sta_id != (int)0 )
					{
					if ( aKd.sta_id > (int)0 )
						{
						/*--- Eintrag gefunden + ueberbuchungsfaktor gesetzt ---*/
						busyvalue = aKd.busy + 1;
						busyvalue -= aKd.sta_id;
						}
					else if ( aKd.sta_id == (int)_UNDEF )
						busyvalue = aKd.busy + 1;    /*--- Eintrag gefunden ---*/

					if ( busyvalue > aKd.anz )
						{
						/*!!!*******
						UtilMsgGet((int)MPE_KONOVERFLOW, MSGTYP_ERROR, message);
						status = UtilImmediatCall(message);
						if (status == (int)TRUE)
						****************/
							status = (int)MPOK;
/****
						else
							return((int)MPERROR);
*******/
						}
					}
				else if (status != (int)MPOK)
					{
					UtilMsg( (int)MPE_KONKATMIS, MSGTYP_ERROR, NULL );
					return((int)MPERROR);
					}
				}

			/* increment busy counter of KONT_DETAIL */
			(void)sprintf(query, _UPD_KOND_ADDONE, newres->kont_id, newres->kat_id);
			status = MPAPIdb_sqlcommand(query, &i);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				return((int)MPERROR);
				}
			}
		/* manage KAPA table */
		if (writeres.kat_id != (int)_UNDEF && dlg.dl_id != (int)_UNDEF)
			{
			(void)sprintf(query, _UPD_KAPA_ADDONE, dlg.dl_id, reservation[0].kat_id);
			status = MPAPIdb_sqlcommand(query, &i);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				}
			}

		/* write new reservation for all dlparts */
		if (tdlcnt > 0)
			{
			for (i=0; i<tdlcnt; i++)
				{
				writeres.dl_id = tdlids[i];
				status = MPAPIinsertEntry((int)_RESERVATION, (char *)&writeres, (BEZEICHNUNG *)NULL);
				if (status != (int)MPOK)
					{
					UtilMsg(status, MSGTYP_DBERROR, NULL);
					return((int)MPERROR);
					}
				}
			}
		else
			{
			writeres.dl_id = (int)_UNDEF;
			status = MPAPIinsertEntry((int)_RESERVATION, (char *)&writeres, (BEZEICHNUNG *)NULL);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				return((int)MPERROR);
				}
			}

		}

	/* set values to RES for further use (AKTDwrite) */
	newres->teil = writeres.teil;
	newres->sai_id = writeres.sai_id;

	return(status);
}

/*F***********************************************************
 * function:  Write AKT detail
 *            in INS mode delete default entries and write new ones
 *            in UPD mode do nothing
 *            in DEL mode delete all entries
 *
 * paras:     BCH id, DLN id, DL id, RES data
 *            ACTIONTYP must be right set
 * return:    status
 **************************************************************/
int AKTDwrite(int bid, int uid, int dlid, RESERVATION *newres)
{
	extern MEMOBJ sqlmem;

	extern BUCHUNG bch;
	extern DIENSTLEISTUNG dtg;
	extern RESERVATION res;
	extern unsigned char bm_obj;

	AKT_DETAIL *adptr = NULL;
	AKT_DETAIL writeaktdet;
	DIENSTLEISTUNG dl;
	DLG_PART *dlpart = NULL;
	AKTIONEN akt;
	char query[_QUERYLEN];
	int status = (int)MPOK;
	int adcnt = (int)0;
	int i;
	int id;
	int dlpartcnt;
	unsigned char akt_art = MULTIPLEAKT;

	/* if bm_obj is ARR then let it be because of DLNdefaults */
	/* did already this job ! */
/*	if (bm_obj == _ARRANGEMENT)
		return((int)MPOK);
*/

	/* fucking memory job */
	if (newres == NULL)
		return((int)MPERROR);

	/* init */
	writeaktdet.bid    = bid;
	writeaktdet.pers_id    = uid;
	writeaktdet.dlg_id = dlid;
	writeaktdet.sai_id = newres->sai_id;
	writeaktdet.parentakt = (int)_UNDEF;
	writeaktdet.ord = (int)1;
	writeaktdet.exec_dat = (int)0;
	writeaktdet.akt_nr = (int)_UNDEF;

	/* get typ of AKTION (single/group) */
	dl.dlg_id = dlid;
	id = MPAPIselectOneId((int)_DIENSTLEISTUNG, dlid, (char *)&dl);
	if (id != (int)_UNDEF)
		{
		akt.akt_id = dl.akt_id;
		id = MPAPIselectOneId((int)_AKTIONEN, akt.akt_id, (char *)&akt);
		if (id != (int)_UNDEF)
			{                    /* _UNDEF w�rde keine Aktion bedeuten */
			if (akt.a_typ_id == (int)_UNDEF)
				akt_art = MULTIPLEAKT;
			else
				akt_art = SINGLEAKT;
			}
		}

	/* read all existing aktdet for bid, uid, dl */
	/* if nothing here then make new entries */
	/* if something here match it, delete old entries */
	/* and insert new entries */

	/* manage already entered reservations */
	(void)sprintf(query, _SEL_AKTDET_BCH_UID_DL, bid, uid, dlid);
	status=MPAPIdb_sqlquery((int)_AKT_DETAIL, &sqlmem.buffer,
	         query, &adcnt, &sqlmem.datalen, &sqlmem.alloclen);
	adptr = (AKT_DETAIL *)sqlmem.buffer;
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	if (adcnt > 0)
		{
		/* in UPD mode we let it be */
		/* in DEL mode we delete all aktionsdetail entries */
		if (ACTIONTYP == (unsigned char)MPDELETE)
			{
			/* delete all old entries */
			status = MPAPIdeleteEntry((int)_AKT_DETAIL, (char *)&adptr[0]);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				return((int)MPERROR);
				}
			}
		}

	/* write new entries only in INSERT mode - in DEL/UPD let it be */
	if ((ACTIONTYP == (unsigned char)INSERT && bm_obj != (int)_ARRANGEMENT) ||
	     adcnt == (int)0)
		{
		(void)sprintf(query, _SEL_HDLG_DL, dlid);
		status=MPAPIdb_sqlquery((int)_DLG_PART, &sqlmem.buffer,
	         query, &dlpartcnt, &sqlmem.datalen, &sqlmem.alloclen);
		dlpart = (DLG_PART *)sqlmem.buffer;
		if (status != (int)MPOK || dlpartcnt < 1)
			{
			UtilMsg((int)MPE_NODLG, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}

		for (i=0; i<dlpartcnt && status == (int)MPOK; i++)
			{
			writeaktdet.dl_id = dlpart[i].dl_id;
			writeaktdet.z_flag = _AKT_READYTOSTART;
			writeaktdet.akt_nr = (int)_UNDEF;
			writeaktdet.teil = newres->teil;          /* get same TEIL as in RES */
			writeaktdet.file_id = (int)_UNDEF;
			if (akt_art == SINGLEAKT)
				{
				writeaktdet.akt_id = akt.akt_id;
				writeaktdet.a_typ_id = akt.a_typ_id;
				status = MPAPIinsertEntry((int)_AKT_DETAIL, (char *)&writeaktdet, (BEZEICHNUNG *)NULL);
				}
			else
				{
				status = AKTDwritegroup(&writeaktdet, akt.akt_id);
				if (status != (int)MPOK)
					UtilMsg((int)MPE_NOAKTFORDLDLA, MSGTYP_ERROR, NULL);
				}
			}
		}

	return( status );
}




/*F***********************************************************
 * function:  Write AKT detail for a group of actions
 *
 * paras:     AKT-DETAIL settings, parent AKT
 * return:    status
 **************************************************************/

#define _SEL_AKTFROMPARENT "SELECT * FROM TDBADMIN.AKTIONSGRP \
	WHERE PARENTAKT = %d ORDER BY ORD;"

int AKTDwritegroup(AKT_DETAIL *aktdet, int parent)
{
	extern AKTIONEN akt;

	char query[_QUERYLEN];
	int i;
	int status=(int)MPOK;
	int anzahl;
	unsigned long dlen = 0;
	unsigned long alen = 0;
	AKTIONSGRP *aktgrp = NULL;

	(void)sprintf(query, _SEL_AKTFROMPARENT, parent);
	status = MPAPIdb_sqlquery((int)_AKTIONSGRP, (char **)&aktgrp, query,
	                &anzahl, &dlen, &alen);
	if (anzahl > (int)0 && status == (int)MPOK)
		{
		for (i=0; i<anzahl && status == (int)MPOK; i++)
			{
			akt.akt_id = aktgrp[i].childakt;
			status = MPAPIselectOneId((int)_AKTIONEN, (int)akt.akt_id,
			                     (char *)&akt);
			if (status == (int)_UNDEF)
				break;
			else
				{
				aktdet->parentakt = parent;
				aktdet->akt_id = akt.akt_id;
				aktdet->a_typ_id = akt.a_typ_id;
				aktdet->ord = aktgrp[i].ord;
				status = MPAPIinsertEntry((int)_AKT_DETAIL, (char *)aktdet,
				                     (BEZEICHNUNG *)NULL);
				}
			}
		}
	else
		status = (int)MPERROR;

	MPfree((char *)aktgrp);
	return(status);
}
