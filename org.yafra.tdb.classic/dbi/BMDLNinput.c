/*D***********************************************************
 * Modul:     DBI - booking modul
 *            insert/update/delete DLN
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMDLNinput.c,v 1.4 2009-01-02 16:51:35 mwn Exp $";

int BMDLNinput(int len, char *buffer)
{
	extern int sprache;
	extern BUCHUNG bch;              /* aktive Buchung */
	extern BCH_DLN bd;
	extern REISENDER rei;            /* bleibt aktiver DLN */
	extern PERSONEN pers;
	extern PERSADR adr;
	extern SPRACHEN spr;
	extern ARRANGEMENT arr;          /* because of default entries in ARR case */
	extern STATUS_WERTE sta;
	extern REISENDER_TYP reit;
	extern KOMMISSION	kom;
	extern KOMM_DETAIL komd;
	extern TEXTE txt;

	extern unsigned char bm_state;
	extern unsigned char bm_obj;
	extern unsigned int  bm_dlncnt;
	extern unsigned char bm_dlnatonce;
	extern unsigned char logging_mp;
	extern unsigned char logging_booking;
	extern int DebugFlag;
	extern FILE *MP_DBIDEBUGFILE;

	MEMOBJ bez;
	int status = MPOK;
	int id;
	int i;
	int tmplen;
	int anzfields;
	int anzsplit;
	int splitflag = NOPARTS;
	unsigned char Fdelwhole_dln = (unsigned char)FALSE;
	char **splitbuffer;
	char *ptr;
	char bezeichnung[_RECORDLEN+1];
	char kommbez[_RECORDLEN+1];
	char message[_RECORDLEN];
	char logtext[_RECORDLEN];
	time_t aclock;

	/* DLN logging */
	if (logging_booking)
		{
		if (ACTIONTYP == (unsigned char)UPDATE)
			{
			(void)sprintf(logtext, "%d: Reisender %d mutiert",
			      bch.bid, bd.dln_id);
			MPlog(_LOGBOOKING, status, logtext, __FILE__);
			}
		else
			{
			(void)sprintf(logtext, "%d: Reisender %d geloescht", bch.bid, bd.dln_id);
			MPlog(_LOGBOOKING, status, logtext, __FILE__);
			}
		}

	if (DebugFlag)
		{
		aclock = time(NULL);
		PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "manage a DLN in BCH %d", bch.bid);
		}

	/* init */
	tmplen = 0;
	bez.buffer = bezeichnung;
	bez.alloclen = _RECORDLEN;
	ptr = buffer;

	/* set PERSONEN to reisender/privat typ */
	pers.pers_typ = (int)_PERS_PRIVAT;

	/* Reisender Init */
	pers.sta_id = (int)_UNDEF;
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		bd.dln_id = (int)_UNDEF;

		pers.pers_id = (int)_UNDEF;
		(void)strcpy(adr.ort, "-");
		pers.sta_id = (int)_UNDEF;

		rei.pers_id = (int)_UNDEF;
		rei.rkr_id = (int)_UNDEF;
		adr.land_id = (int)_UNDEF;
		*rei.passnr = (char)NULL;
		*rei.age = (char)NULL;
		*rei.attr1 = (char)NULL;
		*rei.attr2 = (char)NULL;

		adr.pers_id = (int)_UNDEF;
		*adr.ans = (char)NULL;
		*adr.adr1 = (char)NULL;
		*adr.adr2 = (char)NULL;
		*adr.adr3 = (char)NULL;
		*adr.plz = (char)NULL;
		adr.sta_id = (int)_UNDEF;
		}

	/* get number of fields */
	anzfields = MPgetSection(ptr, &tmplen, (char)_MPSYMB_CR);
	if (anzfields != 9)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		rei.pers_id=(int)_UNDEF;
		return((int)MPERROR);
		}
	ptr = ptr + (tmplen+_MPSYMBLEN);

	/* -1- STATUS_WERTE  sex */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	sta.typ = (int)_SEX;
	status  = getAttribut((int)_SEX, bezeichnung);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NOSEX, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	rei.sex = sta.sta_id;

	/* -2- REISENDER   name */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung == (char)NULL)      /* Name ist ein MUSS Feld */
		{
		pers.pers_id = (int)_UNDEF;
		rei.pers_id = (int)_UNDEF;
		UtilMsg((int)MPE_NONAM, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)copyTextTo(pers.name, bezeichnung, (int)_CHAR512);

	/* -3- REISENDER  vorname */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung == (char)NULL)    /* Vorname ist ein MUSS Feld */
		{
		pers.pers_id = (int)_UNDEF;
		rei.pers_id = (int)_UNDEF;
		UtilMsg((int)MPE_NOVOR, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)copyTextTo(rei.vor, bezeichnung, (int)_CHAR512);

	/* -4- _UNDEF  dyn. attribute of dln */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	(void)copyTextTo(rei.age, bezeichnung, (int)_CHAR256);

	/* -5- TEXTE internal */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	txt.typ = (int)_PERSONEN;
	txt.s_id = sprache;
	txt.textid = (int)_UNDEF;
	pers.textid = xTxtWrite(bezeichnung);

	/* -6- TEXTE external */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	txt.typ = (int)_REISENDER;
	txt.textid = (int)_UNDEF;
	rei.mutters_id = xTxtWrite(bezeichnung);

	/* -7- SPRACHEN  */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung != (char)NULL)
		{
		pers.s_id = MPAPIselectEntry((int)_SPRACHEN, bezeichnung,
		            (char *)&spr, sizeof(SPRACHEN), sizeof(pers.s_id));
		if (pers.s_id == (int)_UNDEF)
			pers.s_id = sprache;
		}
	else
		pers.s_id = sprache;

	/* -8- KOMM  (twin sel) */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung != (char)NULL)
		{
		splitbuffer = (char **)UtilSplitBuffer(bezeichnung, &anzsplit, (char)'\n');
		if (splitbuffer == NULL && anzsplit == (int)_UNDEF)
			{
			UtilMsg((int)MPE_SPLIT, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		else if (anzsplit == (int)0)
			{
			splitflag = SINGLESEL;
			(void)strcpy(kommbez, bezeichnung);
			}
		else
			splitflag = MULTISEL;
		}

	/* -9- REISENDER_TYP   DLN Typ */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	id = MPAPIselectEntry((int)_REISENDER_TYP, bezeichnung, (char *)&reit,
	         sizeof(reit), sizeof(reit.rkr_id));
	if (id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	rei.rkr_id = reit.rkr_id;


	/* check up if we need to insert or to modify DL's */
	/* TRUE is update  FALSE is insert */
	if (ACTIONTYP == (unsigned char)MPDELETE)
		{
		UtilMsgGet((int)MPW_DELALLDLN, MSGTYP_WARNING, message);
		Fdelwhole_dln = (unsigned char)UtilImmediatCall(message);
		}

	/* write PERSONEN entry first, because of new pers_id */
	/* but in DELETE case, this job is done by DLNdelete() */
	if (ACTIONTYP != (unsigned char)MPDELETE)
		{
		status = WriteEntry((int)_PERSONEN, (char *)&pers, (BEZEICHNUNG *)NULL);
		if (status == (int)MPOK)
			{
			WriteInfo((int)_PERSONEN, (char *)&pers, buffer);
			rei.pers_id = pers.pers_id;
			bd.dln_id = pers.pers_id;
			adr.pers_id = pers.pers_id;
			}
		else
			{
			UtilMsg(status, MSGTYP_ERROR, NULL);
			pers.pers_id = (int)_UNDEF;
			rei.pers_id  = (int)_UNDEF;
			return((int)MPERROR);
			}
		}

	/* write PERSADR entry after PERSONEN (exept in DELETE case) */
	if (status == (int)MPOK && (ACTIONTYP != (unsigned char)MPDELETE ||
	    (ACTIONTYP == (unsigned char)MPDELETE && Fdelwhole_dln == (unsigned char)TRUE)))
		{
		status = WriteEntry((int)_PERSADR, (char *)&adr, (BEZEICHNUNG *)NULL);
		if (status == (int)MPOK)
			WriteInfo((int)_PERSADR, (char *)&adr, buffer);
		else
			{
			UtilMsg(status, MSGTYP_ERROR, NULL);
			pers.pers_id = (int)_UNDEF;
			rei.pers_id  = (int)_UNDEF;
			adr.pers_id  = (int)_UNDEF;
			return((int)MPERROR);
			}
		}

	/* write REISENDER entry after PERSONEN (exept in DELETE case) */
	if (status == (int)MPOK && (ACTIONTYP != (unsigned char)MPDELETE ||
	    (ACTIONTYP == (unsigned char)MPDELETE && Fdelwhole_dln == (unsigned char)TRUE)))
		{
		status = WriteEntry((int)_REISENDER, (char *)&rei, (BEZEICHNUNG *)NULL);
		if (status == (int)MPOK)
			WriteInfo((int)_REISENDER, (char *)&rei, buffer);
		else
			{
			UtilMsg(status, MSGTYP_ERROR, NULL);
			pers.pers_id = (int)_UNDEF;
			rei.pers_id  = (int)_UNDEF;
			return((int)MPERROR);
			}
		}

	/* handle KOMM-DETAIL entries, in DELETE case it's already deleted */
	/* by DLNdelete() function ! */
	if (ACTIONTYP != (unsigned char)MPDELETE)
		{
		komd.komm_id = (int)_UNDEF;
		komd.bid = bd.bid;
		komd.dln_id = bd.dln_id;
		komd.kun_id = (int)_UNDEF;
		komd.kol_id = (int)_UNDEF;
		id = KOMDdelete();
		if (splitflag == SINGLESEL)
			{
			id = MPAPIselectEntry(_KOMMISSION, kommbez, (char *)&kom,
			         sizeof(KOMMISSION), sizeof(kom.komm_id));

			/* write now komm_detail entry for this person */
			if (id != (int)_UNDEF)
				status = KOMDinput_dln(kom.komm_id, bd.dln_id, bd.bid);
			}
		else if (splitflag == MULTISEL)
			{
			for (i=0; i<anzsplit && status == MPOK; i++)
				{
				id = MPAPIselectEntry(_KOMMISSION, splitbuffer[i], (char *)&kom,
				         sizeof(KOMMISSION), sizeof(kom.komm_id));

				/* write now komm_detail entry for this person */
				if (id != (int)_UNDEF)
					status = KOMDinput_dln(kom.komm_id, bd.dln_id, bd.bid);
				}
			}
		}

	/* free up twin select split buffer */
	if (splitflag == MULTISEL)
		MPfreearray(splitbuffer, anzsplit);

	if (status != MPOK)
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* set bm to dln-input state */
	bm_state = (unsigned char)_BM_DLN;

	/* Neues ModifikationsDatum */
	status = MPAPIupdate_booksta(bch.bid); /* update sta of BUCHUNG */
	if (status == (int)MPERROR)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		rei.pers_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	/* BOOKINGLOG: DLN changes */
	if (logging_booking)
		{
		(void)sprintf(logtext, "%d: Reisender %d modifiziert",
			      bch.bid, bd.dln_id);
		MPlog(_LOGBOOKING, status, logtext, __FILE__);
		}

	switch (ACTIONTYP)
		{
		case (unsigned char)MPDELETE:
			/* check if we should delete a whole DLN or only DL's from the DLN */
			if (Fdelwhole_dln == (unsigned char)FALSE)
				status = BMobjChoose(len, buffer);
			break;
		case (unsigned char)UPDATE:
			status = BMobjChoose(len, buffer);
			break;
		case (unsigned char)INSERT:
			status = MPAPIinsertEntry((int)_BCH_DLN, (char *)&bd, (BEZEICHNUNG *)NULL);
			if (status == (int)MPERROR)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				rei.pers_id = (int)_UNDEF;
				return((int)MPERROR);
				}
			bm_dlncnt++; /* increase dln count */
			/* log db usage time for DLNdefaults() */
			if (DebugFlag)
				{
				PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "time before DLNdefaults() %f secs",
				      (difftime(time(NULL), aclock)));
				}

			/* write default entries */
			status = DLNdefaults(&arr, &rei);
			if (status == (int)MPERROR)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				rei.pers_id = (int)_UNDEF;
				return((int)MPERROR);
				}

			/* log db usage time for DLNdefaults() */
			if (DebugFlag)
				{
				PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "time after DLNdefaults() %f secs",
						  (difftime(time(NULL), aclock)));
				}

			/* enter more DLN */
			if (bm_dlnatonce == (unsigned char)TRUE)
				{
				/* check up if we need more dln-input */
				UtilMsgGet((int)MPI_MOREDLN, MSGTYP_INFO, message);
				status = UtilImmediatCall(message);
				if (status == (int)TRUE)
					status = BMDLNsend(len, buffer);
				else
					status = BMobjChoose(len, buffer);
				}
			else
				status = BMobjChoose(len, buffer);
			break;
		}

	return(status);
}
