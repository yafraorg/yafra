/*D***********************************************************
 * Modul:     API - maximum id in a table
 *            Gibt die hoechste ID einer Tabelle zurueck
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */
#include <mpsqlcnt.h>		/* SQL MAX statements */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/UtilIDmax.c,v 1.4 2008-11-23 15:44:38 mwn Exp $";

int MPAPIid_max(int table, int typ, char *pointer)
{
	extern MEMOBJ apimem;
	extern STATUS_WERTE sta;

	BEZEICHNUNG *Pbez;
	DIENST_ANGEBOT *dla_ptr;
	DLG_PART *dlg_ptr;
	DIENSTLEISTUNG *dtg_ptr;
	AKTIONEN *akt_ptr;
	AKTIONSPARA *aktpara_ptr;
	ARR_DLG *ad_ptr;
	RESERVATION *resptr;
	KOMM_DETAIL *Pkomd;

	int anzahl, i;
	char maxquery[_QUERYLEN];
	char cntquery[_QUERYLEN];
	int maximum;
	short maxshort;
	int AnzByte=sizeof(int);
	int status=(int)MPOK;
	int selecttable = (int)_INTEGER;
	int count;
	int cnt;

	/* init */
	count = 1;
	maximum = 0;
	*maxquery = NULL;
	*cntquery = NULL;

	switch(table)
		{
		case (int)_SPRACHEN:
			(void)sprintf(cntquery, _COUNT_SPR);
			(void)sprintf(maxquery, _SEL_MAX_SPR);
			break;
		case (int)_STATUS_WERTE:
			if (sta.typ == _UNDEF)
				{
				(void)sprintf(cntquery, _COUNT_STA);
				(void)sprintf(maxquery, _SEL_MAX_STAID);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_STA_TYP, sta.typ);
				(void)sprintf(maxquery, _SEL_MAX_STA, sta.typ);
				}
			break;
		case (int)_BEZEICHNUNG:
			if (typ == _UNDEF)
				{
				(void)sprintf(cntquery, _COUNT_BEZ);
				(void)sprintf(maxquery, _SEL_MAX_BEZID);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_BEZ_TYP, typ);
				(void)sprintf(maxquery, _SEL_MAX_BEZ, typ);
				}
			break;
		case (int)_TEXTE:
			if (typ == _UNDEF)
				{
				(void)sprintf(cntquery, _COUNT_TXT);
				(void)sprintf(maxquery, _SEL_MAX_TXTID);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_TXT_TYP, typ);
				(void)sprintf(maxquery, _SEL_MAX_TXT, typ);
				}
			break;
		case (int)_HISTORY:
			if (typ == _UNDEF)
				{
				(void)sprintf(cntquery, _COUNT_HIS);
				(void)sprintf(maxquery, _SEL_MAX_HISTID);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_HIS_TYP, typ);
				(void)sprintf(maxquery, _SEL_MAX_HISTYP, typ);
				}
			break;
		case (int)_MSG:
			if (typ == _UNDEF)
				{
				(void)sprintf(cntquery, _COUNT_MSG);
				(void)sprintf(maxquery, _SEL_MAX_MSGID);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_MSG_TYP, typ);
				(void)sprintf(maxquery, _SEL_MAX_MSGTYP, typ);
				}
			break;
		case (int)_HELP:
			if (typ == _UNDEF)
				{
				(void)sprintf(cntquery, _COUNT_HELP);
				(void)sprintf(maxquery, _SEL_MAX_HELPID);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_HELP_TYP, typ);
				(void)sprintf(maxquery, _SEL_MAX_HELPTYP, typ);
				}
			break;
		case (int)_SAISON:
			(void)sprintf(cntquery, _COUNT_SAI);
			(void)sprintf(maxquery, _SEL_MAX_SAI);
			break;



		case (int)_LAND:
			(void)sprintf(cntquery, _COUNT_LAND);
			(void)sprintf(maxquery, _SEL_MAX_LAND);
			break;
		case (int)_ORT:
			(void)sprintf(cntquery, _COUNT_ORT);
			(void)sprintf(maxquery, _SEL_MAX_ORT);
			break;
		case (int)_WAEHRUNG:
			(void)sprintf(cntquery, _COUNT_WHR);
			(void)sprintf(maxquery, _SEL_MAX_WHR);
			break;



		case (int)_KUNDEN:
		case (int)_REISENDER:
		case (int)_PERSONEN:
			(void)sprintf(cntquery, _COUNT_PERS);
			(void)sprintf(maxquery, _SEL_MAX_PERS);
			break;
		case (int)_REISENDER_TYP:
			(void)sprintf(cntquery, _COUNT_DLNT);
			(void)sprintf(maxquery, _SEL_MAX_REIT);
			break;
		case (int)_KUNDEN_TYP:
			(void)sprintf(cntquery, _COUNT_KUNT);
			(void)sprintf(maxquery, _SEL_MAX_KUNT);
			break;
		case (int)_KOLLEKTIV_TYP:
			(void)sprintf(cntquery, _COUNT_KOLT);
			(void)sprintf(maxquery, _SEL_MAX_KOLT);
			break;
		case (int)_KOLLEKTIV:
			(void)sprintf(cntquery, _COUNT_KOL);
			(void)sprintf(maxquery, _SEL_MAX_KOL);
			break;


		case (int)_TRAEGER_TYP:
			(void)sprintf(cntquery, _COUNT_DLTT);
			(void)sprintf(maxquery, _SEL_MAX_DLTT);
			break;
		case (int)_KATEGORIE:
			(void)sprintf(cntquery, _COUNT_KAT);
			(void)sprintf(maxquery, _SEL_MAX_KAT);
			break;
		case (int)_DIENST_TRAEGER:
			(void)sprintf(cntquery, _COUNT_DLT);
			(void)sprintf(maxquery, _SEL_MAX_DLT);
			break;
		case (int)_ANGEBOTS_TYP:
			(void)sprintf(cntquery, _COUNT_DLAT);
			(void)sprintf(maxquery, _SEL_MAX_DLAT);
			break;
		case _AKTIONS_TYP:
			if (typ == (int)_ORD)
				{
				if (pointer == NULL)
					return(_UNDEF);
				aktpara_ptr=(AKTIONSPARA *)pointer;
				(void)sprintf(cntquery, _COUNT_AKTP_NR, aktpara_ptr->a_typ_id);
				(void)sprintf(maxquery, _SEL_MAX_AKTPARA_NR, aktpara_ptr->a_typ_id);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_AKTT);
				(void)sprintf(maxquery, _SEL_MAX_AKTT);
				}
			break;
		case (int)_AKTIONEN:
			(void)sprintf(cntquery, _COUNT_AKT);
			(void)sprintf(maxquery, _SEL_MAX_AKT);
			break;
		case (int)_AKTIONSGRP:
			if (pointer == NULL)
				return(_UNDEF);
			akt_ptr=(AKTIONEN *)pointer;
			(void)sprintf(cntquery, _COUNT_AKTG_ORD, akt_ptr->akt_id);
			(void)sprintf(maxquery, _SEL_MAX_AKTG_ORD, akt_ptr->akt_id);
			break;
		case (int)_DIENST_ANGEBOT:
			if (typ == (int)_ORD)
				{
				if (pointer == NULL)
					return(_UNDEF);
				dla_ptr=(DIENST_ANGEBOT *)pointer;
				(void)sprintf(cntquery, _COUNT_DLA_ORD, dla_ptr->h_dla_id);
				(void)sprintf(maxquery, _SEL_MAX_DLA_ORD, dla_ptr->h_dla_id);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_DLA);
				(void)sprintf(maxquery, _SEL_MAX_DLA);
				}
			break;
		case (int)_DLG_PART:
			if (typ == (int)_ORD)
				{
				if (pointer == NULL)
					return(_UNDEF);
				dlg_ptr=(DLG_PART *)pointer;
				(void)sprintf(cntquery, _COUNT_TDL_ORD, dlg_ptr->h_dl_id);
				(void)sprintf(maxquery, _SEL_MAX_DLG_ORD, dlg_ptr->h_dl_id);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_TDL);
				(void)sprintf(maxquery, _SEL_MAX_DLG);
				}
			break;
		case (int)_DIENSTLEISTUNG:
			(void)sprintf(cntquery, _COUNT_DL);
			(void)sprintf(maxquery, _SEL_MAX_DTG);
			break;
		case (int)_DLG_DLG:
			if (pointer == NULL)
				return(_UNDEF);
			dtg_ptr = (DIENSTLEISTUNG *)pointer;
			(void)sprintf(cntquery, _COUNT_DD_ORD, dtg_ptr->dlg_id);
			(void)sprintf(maxquery, _SEL_MAX_DTG_ORD, dtg_ptr->dlg_id);
			break;
		case (int)_PROGRAMM:
			(void)sprintf(cntquery, _COUNT_PRG);
			(void)sprintf(maxquery, _SEL_MAX_PRG);
			break;
		case (int)_ARRANGEMENT:
			(void)sprintf(cntquery, _COUNT_ARR);
			(void)sprintf(maxquery, _SEL_MAX_ARR);
			break;
		case (int)_ARR_DLG:
			if (pointer == NULL)
				return(_UNDEF);
			ad_ptr = (ARR_DLG *)pointer;
			(void)sprintf(cntquery, _COUNT_AD_TEIL, ad_ptr->arr_id);
			(void)sprintf(maxquery, _SEL_MAX_AD_TEIL, ad_ptr->arr_id);
			break;



		case (int)_HOST_KONT:
			(void)sprintf(cntquery, _COUNT_HKON);
			(void)sprintf(maxquery, _SEL_MAX_HKON);
			break;
		case (int)_KONTINGENT:
			(void)sprintf(cntquery, _COUNT_KON);
			(void)sprintf(maxquery, _SEL_MAX_KON);
			break;




		case (int)_BUCHUNG:
			(void)sprintf(cntquery, _COUNT_BCH);
			(void)sprintf(maxquery, _SEL_MAX_BCH);
			break;
		case (int)_AKT_DETAIL:
			/* get new number for a a_typ_id */
			(void)sprintf(cntquery, _COUNT_AKTD_NR, typ);
			(void)sprintf(maxquery, _SEL_MAX_AKTD, typ);
			break;
		case (int)_KOSTEN_ART:
			(void)sprintf(cntquery, _COUNT_KAR);
			(void)sprintf(maxquery, _SEL_MAX_KAR);
			break;
		case (int)_KOMMISSION:
			(void)sprintf(cntquery, _COUNT_KOM);
			(void)sprintf(maxquery, _SEL_MAX_KOM);
			break;
		case (int)_KOMM_DETAIL:
			if (pointer == NULL)
				return(_UNDEF);
			Pkomd = (KOMM_DETAIL *)pointer;
			if (Pkomd->dln_id != (int)_UNDEF)
				{
				(void)sprintf(cntquery, _COUNT_KOMD_PRIODLN, Pkomd->bid, Pkomd->dln_id);
				(void)sprintf(maxquery, _SEL_MAX_KOMD_DLN, Pkomd->bid, Pkomd->dln_id);
				}
			else if (Pkomd->kun_id != (int)_UNDEF)
				{
				(void)sprintf(cntquery, _COUNT_KOMD_KUN, Pkomd->kun_id);
				(void)sprintf(maxquery, _SEL_MAX_KOMD_KUN, Pkomd->kun_id);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_KOMD_KOL, Pkomd->kol_id);
				(void)sprintf(maxquery, _SEL_MAX_KOMD_KOL, Pkomd->kol_id);
				}
			break;
		case (int)_RESERVATION:
			if (pointer == NULL)
				return(_UNDEF);
			resptr = (RESERVATION *)pointer;
			if (resptr->pers_id == (int)_UNDEF)
				{
				(void)sprintf(cntquery, _COUNT_RES_TEIL, resptr->bid);
				(void)sprintf(maxquery, _SEL_MAX_RES_TEIL, resptr->bid);
				}
			else
				{
				(void)sprintf(cntquery, _COUNT_RES_TEILDLN, resptr->bid, resptr->pers_id);
				(void)sprintf(maxquery, _SEL_MAX_RES_TEILUID, resptr->bid, resptr->pers_id);
				}

			break;
		case (int)_PREIS:
			(void)sprintf(cntquery, _COUNT_PRE);
			(void)sprintf(maxquery, _SEL_MAX_PRE);
			break;



		case (int)_GRAPHIK:
			(void)sprintf(cntquery, _COUNT_GRA);
			(void)sprintf(maxquery, _SEL_MAX_GRA);
			break;
		case _PCX_FILES:
			(void)sprintf(cntquery, _COUNT_PCX);
			(void)sprintf(maxquery, _SEL_MAX_PCX);
			break;


		default:
			return((int)_UNDEF);
			break;
		}

	/* error if no query is present */
	if (*maxquery == NULL)
		return((int)_UNDEF);

	/* set type of max id value */
	if (AnzByte == sizeof(short))
		selecttable = (int)_SHORT;

	/* count the needed ID's first to see if there's at least one entry */
	if (*cntquery != NULL)
		{
		status = MPAPIdb_sqlquery((int)_INTEGER, &apimem.buffer, cntquery, &cnt,
		                         &apimem.datalen, &apimem.alloclen);
		if (status == (int)MPOK)
			{
			if (cnt > 0)
				(void)memcpy((void *)&count, (void *)apimem.buffer, sizeof(int));
			else
				count = (int)0;
			}
		else
			return((int)_UNDEF);
		}

	/* if count is not 0 then get the max_id */
	if (count > 0)
		{
		status = MPAPIdb_sqlquery(selecttable, &apimem.buffer, maxquery,
		                         &anzahl, &apimem.datalen, &apimem.alloclen);
		if (status == MPOK)
			{
			if (anzahl > (int)0)
				{
				if (AnzByte == sizeof(short))
					{
					(void)memcpy((void *)&maxshort, (void *)apimem.buffer, AnzByte);
					maximum = (int)maxshort;
					}
				else
					(void)memcpy((void *)&maximum, (void *)apimem.buffer, AnzByte);
				}
			}
		else
			maximum = (int)_UNDEF;
		}


	return(maximum);
}
