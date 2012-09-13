/*D***********************************************************
 * Modul:     DBI - database action
 *            Preis
 *
 * Copyright: yafra.org, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPREinput.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int PREinput(int len, char *buffer )
{
	extern MP_PROFIL prof;
	extern PREIS pre;
	extern REISENDER_TYP reit;
	extern KOSTEN_ART kar;
	extern TRAEGER_TYP dltt;
	extern KATEGORIE kat;
	extern KONTINGENT kon;
	extern DIENST_ANGEBOT dla;
	extern DIENSTLEISTUNG dtg;
   extern ARRANGEMENT arr;
	extern STATUS_WERTE sta;
	extern KUNDEN kun;
	extern SAISON sai;
	extern TEXTE txt;
	extern WAEHRUNG whr;
	extern int sprache;
	extern unsigned char logging_user;
	extern unsigned char logging_mp;

	struct tm DateTime;
	time_t tloc;
	char tmpbuf[_RECORDLEN];
	char actionbez[_BEZLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	char **splitbuffer;
	int status=(int)MPOK;
	int count = (int)0;
	int anzsplit;
	int splitflag;
	int i;
	int id;

	/* initialisiere bei INSERT Werte auf UNDEF */
	splitflag = NOPARTS;
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		(void)strcpy(actionbez, "eingegeben");
		pre.pre_id=(int)_UNDEF;
		pre.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		pre.dl_id=(int)_UNDEF;
		pre.dla_id=(int)_UNDEF;
		pre.kar_id=(int)_UNDEF;
		pre.sai_id=(int)_UNDEF;
		pre.dltt_id = (int)_UNDEF;
		}
	else if (ACTIONTYP == (unsigned char)UPDATE)
		(void)strcpy(actionbez, "mutiert");
	else
		(void)strcpy(actionbez, "geloescht");

	/* hole Eintrage aus dem Menustring der GUI */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* PREISE */
	if (readDouble(&pre.apr, to_buffers[MPRE_APREIS]) == (int)MPERROR)
		pre.apr=(double)0.;
	if (readDouble(&pre.vpr, to_buffers[MPRE_VPREIS]) == (int)MPERROR)
		pre.vpr=(double)0.;
	if (readDouble(&pre.epr, to_buffers[MPRE_EPREIS]) == (int)MPERROR)
		pre.epr=(double)0.;
	/*!!! attention to divisions by zero */
	if (pre.vpr < 0)
		{
		UtilMsg((int)MPE_NOPRE, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* WAEHRUNG */
	if (*to_buffers[MPRE_WHR] != NULL && 
		(id = MPAPIselectEntry(_WAEHRUNG, to_buffers[MPRE_WHR],
		(char *)&whr, sizeof(whr), sizeof(whr.whr_id)) != (int)_UNDEF))
		{
		pre.whr_id = whr.whr_id;
		}
	else
		{
		UtilMsg((int)MPE_NOWHR, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* G�ltigkeitsdatum festlegen */
	if (*to_buffers[MPRE_GLTAB] != NULL)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		if ( ReadDate( &DateTime, (time_t *)&pre.glt,
			 to_buffers[MPRE_GLTAB] ) != (int)MPOK )
			{
			UtilMsg((int)MPE_PREGLTABDAT, MSGTYP_ERROR, NULL);
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		}
	else
		{
		UtilMsg((int)MPE_PREGLTABDAT, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* KUNDEN Buchungsstelle */
	if (*to_buffers[MPRE_BST] != NULL)
		pre.kbst = MPAPIselectEntry((int)_KUNDEN, to_buffers[MPRE_BST],
		   (char *)&kun, sizeof(KUNDEN), sizeof(pre.kbst));
	else
		{
		pre.kbst = (int)_UNDEF;
		UtilMsg((int)MPE_NOBCHST, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* SECURITY: check if user is in this BCHST */
	if ( ((prof.bchst != pre.kbst) && (prof.seclevel != _SECLEVEL_DBA)) ||
	     ((prof.bchst == pre.kbst) &&
	    (prof.seclevel != _SECLEVEL_DBA && prof.seclevel != _SECLEVEL_USER)) )
		{
		pre.kbst = (int)_UNDEF;
		UtilMsg((int)MPE_NOPERMISSION, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* KOSTEN_ART pr�fen */
	if (*to_buffers[MPRE_KAR] == NULL && ACTIONTYP == (unsigned char)MPDELETE)
		pre.kar_id = (int)_UNDEF;
	else if (*to_buffers[MPRE_KAR] == NULL)
		{
		UtilMsg((int)MPE_NOKAR, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}
	else
		{
		pre.kar_id=MPAPIselectEntry((int)_KOSTEN_ART, to_buffers[MPRE_KAR],
		(char *)&kar, sizeof(KOSTEN_ART), sizeof(pre.kar_id));
		if (pre.kar_id == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOKAR, MSGTYP_ERROR, NULL);
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		}

	/* TRAEGER_TYP */
	if (*to_buffers[MPRE_DLTT] != NULL)
		{
		pre.dltt_id = MPAPIselectEntry((int)_TRAEGER_TYP, to_buffers[MPRE_DLTT],
		   (char *)&dltt, sizeof(TRAEGER_TYP), sizeof(pre.dltt_id));
		}
	else
		pre.dltt_id = (int)_UNDEF;

	/* KATEGORIE pr�fen */
	if (*to_buffers[MPRE_KAT] != NULL)
		{
		pre.kat_id = (int)MPAPIselectEntry((int)_KATEGORIE, to_buffers[MPRE_KAT],
		    (char *)&kat, sizeof(KATEGORIE), sizeof(pre.kat_id));
		}
	else
		pre.kat_id = (int)_UNDEF;

	/* check that only KAT or DLTT is set - not both at the same time */
	if (pre.dltt_id != (int)_UNDEF && pre.kat_id != (int)_UNDEF)
		{
		UtilMsg((int)MPE_NODLTT, MSGTYP_ERROR, NULL); /*!!! wrong message */
		return((int)MPERROR);
		}

	/* REISENDER_TYP */
	if ( *to_buffers[MPRE_DLNT] != NULL )
		{
		pre.rkr_id = (int)MPAPIselectEntry((int)_REISENDER_TYP, to_buffers[MPRE_DLNT],
		   (char *)&reit,	sizeof(REISENDER_TYP), sizeof(pre.rkr_id));
		}
	else
		pre.rkr_id = (int)_UNDEF;

	/* Dienstleistung pr�fen */
	if (*to_buffers[MPRE_DL] != NULL)
		{
		splitbuffer = (char **)UtilSplitBuffer(to_buffers[MPRE_DL], &anzsplit, (char)'\n');
		if (splitbuffer == NULL && anzsplit == (int)_UNDEF)
			{
			UtilMsg((int)MPE_SPLIT, MSGTYP_ERROR, NULL);
			dtg.dlg_id = (int)_UNDEF;
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		else if (anzsplit == (int)0)
			{
			splitflag = SINGLESEL;
			pre.dl_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, to_buffers[MPRE_DL],
				  (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
			if (pre.dl_id > 0)
				pre.sai_id = dtg.sai_id;
			}
		else
			splitflag = MULTISEL;
		count++;
		pre.dla_id=(int)_UNDEF;

		/* DL von / bis Daten */
		if (*to_buffers[MPRE_DLVON] != NULL)
			{
			(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			ReadDate(&DateTime,(time_t *)&pre.dl_vondat, to_buffers[MPRE_DLVON]);
			}
		else
			pre.dl_vondat = (int)_UNDEF;

		if (*to_buffers[MPRE_DLBIS] != NULL)
			{
			(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			ReadDate(&DateTime,(time_t *)&pre.dl_bisdat, to_buffers[MPRE_DLBIS]);
			}
		else
			pre.dl_bisdat = (int)_UNDEF;
		}
	else
		{
		pre.dl_id=(int)_UNDEF;
		pre.dl_vondat = (int)_UNDEF;
		pre.dl_bisdat = (int)_UNDEF;

		/* DIENST_ANGEBOT */
		if (*to_buffers[MPRE_DLA] != NULL )
			{
			pre.dla_id=MPAPIselectEntry((int)_DIENST_ANGEBOT, to_buffers[MPRE_DLA],
			   (char *)&dla, sizeof(DIENST_ANGEBOT), sizeof(pre.dla_id));
			count++;
			}
		else
			pre.dla_id=(int)_UNDEF;
		}

	/* KONTINGENT �berpr�fen */
	if (*to_buffers[MPRE_KON] != NULL )
		{
		pre.kont_id=MPAPIselectEntry((int)_KONTINGENT, to_buffers[MPRE_KON],
		  (char *)&kon, sizeof(KONTINGENT), sizeof(pre.kont_id));
		count++;
		}
	else
		pre.kont_id=(int)_UNDEF;

	/* PREIS status */
	if (*to_buffers[MPRE_STA] != (char)NULL)
		{
		sta.typ = (int)_PREISSTA;
		if (getAttribut((int)_PREISSTA, to_buffers[MPRE_STA]) != (int)MPOK)
			{
			UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		pre.sta_id = sta.sta_id;
		}
	else
	   pre.sta_id = (int)_UNDEF;

	/* Saison Eintrag f�r den Preis suchen */
	if (kon.kont_id != (int)_UNDEF && kon.sai_id > 0)
		pre.sai_id = kon.sai_id;
	else
		pre.sai_id = (int)_UNDEF;

	/* Arrangement setzen */
	if (*to_buffers[MBME_ARR] != (char)NULL)
		pre.arr_id = MPAPIselectEntry((int)_ARRANGEMENT, to_buffers[MPRE_ARR],
	        (char *)&arr, sizeof(ARRANGEMENT), sizeof(pre.arr_id));
	else
		pre.arr_id = (int)_UNDEF;

	/* STATUS_WERTE  Einheitstypen */
	if (*to_buffers[MPRE_UNITTYP] != (char)NULL)
		{
		sta.typ = (int)_STA_UNIT;
		if (getAttribut((int)_STA_UNIT, to_buffers[MPRE_UNITTYP]) != (int)MPOK)
			{
			UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		pre.unit_typ = sta.sta_id;
		}
	else
		pre.unit_typ = (int)_UNDEF;

   /* _UNDEF Einheiten Von */
	if (*to_buffers[MPRE_UNITVON] == NULL)
		pre.unit_von = (int)_UNDEF;
	else
	   {
		status = readInteger(&pre.unit_von, to_buffers[MPRE_UNITVON]);
		if (status == (int)MPERROR)
			pre.unit_von = (int)_UNDEF;
		else
			if (pre.unit_von < (int)1)
				pre.unit_von = (int)_UNDEF;
		}

   /* _UNDEF Einheiten Bis */
	if (*to_buffers[MPRE_UNITVON] == NULL)
		pre.unit_von = (int)_UNDEF;
	else
	   {
		status = readInteger(&pre.unit_bis, to_buffers[MPRE_UNITBIS]);
		if (status == (int)MPERROR)
			pre.unit_von = (int)_UNDEF;
		else
			if (pre.unit_von < (int)1)
				pre.unit_von = (int)_UNDEF;
		}

	/* PREIS-Text schreiben */
	txt.typ    = (int)_PREIS;
	txt.s_id   = sprache;
	txt.textid = pre.textid;
	pre.textid = xTxtWrite(to_buffers[MPRE_TXT]);

	/* PREIS-Eintrag schreiben */
	if (splitflag == SINGLESEL || splitflag == NOPARTS)
		{
		if (logging_user)
			{
			(void)sprintf(tmpbuf, "Preisnummer %d %s", pre.pre_id, actionbez); 
			MPlog(_LOGUSER, status, tmpbuf, __FILE__);
			}
		status = WriteEntry((int)_PREIS,(char *)&pre,(BEZEICHNUNG *)NULL);
		}
	else
		{
		for (i=0; i<anzsplit && status == MPOK; i++)
			{
			pre.dl_id=MPAPIselectEntry((int)_DIENSTLEISTUNG, splitbuffer[i],
				  (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
			if (pre.dl_id != (int)_UNDEF)
				{
				pre.sai_id = dtg.sai_id;
				status=WriteEntry((int)_PREIS,(char *)&pre,(BEZEICHNUNG *)NULL);
				if (logging_user)
					{
					(void)sprintf(tmpbuf, "Preisnummer %d %s", pre.pre_id, actionbez); 
					MPlog(_LOGUSER, status, tmpbuf, __FILE__);
					}
				}
			else
				status = (int)MPERROR;
			}
		}

	/* free up twin select split buffer */
	if (splitflag == MULTISEL)
		MPfreearray(splitbuffer, anzsplit);

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
