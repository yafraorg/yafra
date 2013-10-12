/*D************************************************************/
/* Modul:     get global data's from the db                   */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbinet/tdbnetGLOBinit.c,v 1.1 2008-11-23 15:44:38 mwn Exp $";

int GLOBinit(MP_PROFIL *aProf, GLOBDATA *aGlobdata)
{
	extern int sprache;
	extern int glob_spr_bez;

	extern KUN_VIEW globBCHST;
	extern SPRACHEN globSPR;
	extern LAND globLAND;
	extern TRAEGER_TYP globDLTT;
	extern DIENST_TRAEGER globDLT;
	extern KATEGORIE globKAT;
	extern ANGEBOTS_TYP globDLAT;
	extern REISENDER_TYP globDLNT;
	extern PROGRAMM globPRG;
	extern SAISON globSAI;
	extern int globA_ZEIT;
	extern int globE_ZEIT;
	extern int globP_RANGE;

	struct tm DateTime;
	char bez[_RECORDLEN];
	int status = (int)MPOK;
	int id;
	time_t tmpdate;

	/* init global ID's to UNDEF */
	globBCHST.kun_id = (int)_UNDEF;
	globLAND.land_id = (int)_UNDEF;
	globDLTT.typ_id = (int)_UNDEF;
	globDLTT.bez_id = (int)_UNDEF;
	globKAT.kat_id = (int)_UNDEF;
	globKAT.typ_id = (int)_UNDEF;
	globDLT.dlt_id = (int)_UNDEF;
	globDLT.bez_id = (int)_UNDEF;
	globDLT.typ_id = (int)_UNDEF;
	globDLT.kat_id = (int)_UNDEF;
	globDLT.stufe = (int)0;
	globDLAT.art_id = (int)_UNDEF;
	globDLAT.bez_id = (int)_UNDEF;
	globDLNT.rkr_id = (int)_UNDEF;
	globDLNT.bez_id = (int)_UNDEF;
	globSAI.sai_id = (int)_UNDEF;
	globSAI.bez_id = (int)_UNDEF;
	globPRG.prg_id = (int)_UNDEF;
	globPRG.bez_id = (int)_UNDEF;
	globA_ZEIT=(int)_UNDEF;
	globE_ZEIT=(int)_UNDEF;
	globP_RANGE=(int)_UNDEF;

	/* start DB transaction */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		status=(int)MPERROR;
		return(status);
		}

	/* user BCHST */
	if (aProf->bchst != (int)_UNDEF)
		{
		id = MPAPIselectOneId(_KUN_VIEW, aProf->bchst, (char *)&globBCHST);
		id = KUNmkbez(globBCHST.kun_id, bez, (size_t)_RECORDLEN);
		(void)strcpy(aGlobdata->bchst, bez);
		}

	/* global gui language */
	if (aProf->s_id != (int)_UNDEF)
		{
		sprache = glob_spr_bez = aProf->s_id;
		id = MPAPIselectOneId(_SPRACHEN, aProf->s_id, (char *)&globSPR);
		id = SelectBez(_SPRACHEN, sprache, globSPR.bez_id, bez);
		(void)strcpy(aGlobdata->sprache, bez);
		}

	/* global country settings */
	if (aProf->land_id != (int)_UNDEF)
		{
		id = MPAPIselectOneId(_LAND, aProf->land_id, (char *)&globLAND);
		id = SelectBez(_LAND, sprache, globLAND.bez_id, bez);
		(void)strcpy(aGlobdata->land, bez);
		}

	/*	Globaler Traegertyp festlegen */
	if (aProf->dltt_id != (int)_UNDEF)
		{
		id = MPAPIselectOneId(_TRAEGER_TYP, aProf->dltt_id, (char *)&globDLTT);
		id = SelectBez(_TRAEGER_TYP, sprache, globDLTT.bez_id, bez);
		(void)strcpy(aGlobdata->dltt, bez);
		}

	/*	Globale Kategorie festlegen */
	if (aProf->kat_id != (int)_UNDEF)
		{
		id = MPAPIselectOneId(_KATEGORIE, aProf->kat_id, (char *)&globKAT);
		id = SelectBez(_KATEGORIE, sprache, globKAT.bez_id, bez);
		(void)strcpy(aGlobdata->dltt, bez);
		}

	/* Globaler Dienstleistungstraeger festlegen */
	if (aProf->dlt_id != (int)_UNDEF)
		{
		globDLT.stufe = (int)1;
		id = MPAPIselectOneId(_DIENST_TRAEGER, aProf->dlt_id, (char *)&globDLT);
		id = SelectBez(_DIENST_TRAEGER, sprache, globDLT.bez_id, bez);
		(void)strcpy(aGlobdata->dltt, bez);
		}

	/*	Globaler Angebotstyp festlegen */
	if (aProf->dlat_id != (int)_UNDEF)
		{
		id = MPAPIselectOneId(_ANGEBOTS_TYP, aProf->dlat_id, (char *)&globDLAT);
		id = SelectBez(_ANGEBOTS_TYP, sprache, globDLAT.bez_id, bez);
		(void)strcpy(aGlobdata->dlat, bez);
		}

	/*	Globaler Reisendentyp festlegen */
	if (aProf->dlnt_id != (int)_UNDEF)
		{
		id = MPAPIselectOneId(_REISENDER_TYP, aProf->dlnt_id, (char *)&globDLNT);
		id = SelectBez(_REISENDER_TYP, sprache, globDLNT.bez_id, bez);
		(void)strcpy(aGlobdata->dlnt, bez);
		}

	/*	Globale Saison festlegen */
	if (aProf->sai_id != (int)_UNDEF)
		{
		id = MPAPIselectOneId(_SAISON, aProf->sai_id, (char *)&globSAI);
		id = SelectBez(_SAISON, sprache, globSAI.bez_id, bez);
		(void)strcpy(aGlobdata->saison, bez);
		}

	/*	Globales Programm festlegen */
	if (aProf->prg_id != (int)_UNDEF)
		{
		id = MPAPIselectOneId(_PROGRAMM, aProf->prg_id, (char *)&globPRG);
		id = SelectBez(_PROGRAMM, sprache, globPRG.bez_id, bez);
		(void)strcpy(aGlobdata->programm, bez);
		}

	/*	Globale Abfahrtszeit festlegen */
	globA_ZEIT = aProf->a_zeit;
	if (aProf->a_zeit != (int)_UNDEF)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		DateTime.tm_hour=(int)_UNDEF;
		DateTime.tm_min =(int)_UNDEF;
		tmpdate = (time_t)aProf->a_zeit;
		(void)WriteDate(&DateTime, &tmpdate, bez);
		(void)strcpy(aGlobdata->a_zeit, bez);
		}

	/*	Globale Ankunftszeit festlegen */
	globE_ZEIT = aProf->e_zeit;
	if (aProf->e_zeit != (int)_UNDEF)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		DateTime.tm_hour=(int)_UNDEF;
		DateTime.tm_min =(int)_UNDEF;
		tmpdate = (time_t)aProf->e_zeit;
		(void)WriteDate(&DateTime, &tmpdate, bez);
		(void)strcpy(aGlobdata->e_zeit, bez);
		}

	/*	range for 'planungsboard' */
	globP_RANGE = aProf->p_range;
	if (aProf->p_range > (int)0)
		{
		(void)sprintf(bez, "%d", aProf->p_range);
		(void)strcpy(aGlobdata->p_range, bez);
		}

	/* end DB transaction */
	(void)MPAPIdb_committrx();

	return(status);
}



int GLOBsave(MP_PROFIL *aProf, GLOBDATA *aGlobdata)
{
	extern int sprache;

	extern int glob_spr_bez;
	extern char glob_host_dlt[];
	extern char glob_dlt_bch[];

	extern SPRACHEN globSPR;
	extern LAND globLAND;
	extern TRAEGER_TYP globDLTT;
	extern DIENST_TRAEGER globDLT;
	extern KATEGORIE globKAT;
	extern ANGEBOTS_TYP globDLAT;
	extern REISENDER_TYP globDLNT;
	extern SAISON globSAI;
	extern PROGRAMM globPRG;
	extern int globA_ZEIT;
	extern int globE_ZEIT;
	extern int globP_RANGE;

	struct tm DateTime;
	int status = (int)MPOK;
	int id;

	(void)memcpy((void *)aGlobdata, (void *)comm.buffer, sizeof(GLOBDATA));
	globDLTT.typ_id = (int)_UNDEF;
	globDLTT.bez_id = (int)_UNDEF;
	globKAT.kat_id = (int)_UNDEF;
	globKAT.typ_id = (int)_UNDEF;
	globDLT.dlt_id = (int)_UNDEF;
	globDLT.bez_id = (int)_UNDEF;
	globDLT.typ_id = (int)_UNDEF;
	globDLT.kat_id = (int)_UNDEF;
	globDLT.stufe = (int)0;
	globDLAT.art_id = (int)_UNDEF;
	globDLAT.bez_id = (int)_UNDEF;
	globDLNT.rkr_id = (int)_UNDEF;
	globDLNT.bez_id = (int)_UNDEF;
	globSAI.sai_id = (int)_UNDEF;
	globSAI.bez_id = (int)_UNDEF;
	globPRG.prg_id = (int)_UNDEF;
	globPRG.bez_id = (int)_UNDEF;
	globA_ZEIT=(int)_UNDEF;
	globE_ZEIT=(int)_UNDEF;
	globP_RANGE=(int)_UNDEF;

	/* begin trx */
	status=MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		status=(int)MPERROR;
		}

	/* SPRACHEN */
	if (*aGlobdata->sprache != NULL)
		{
		id = MPAPIselectEntry((int)_SPRACHEN, aGlobdata->sprache,
									 (char *)&globSPR, sizeof(SPRACHEN), sizeof(globSPR.s_id));
		if (id != _UNDEF)
			{
			aProf->s_id = globSPR.s_id;
			glob_spr_bez = sprache = aProf->s_id;
			}
		}

	/* LAND */
	if (*aGlobdata->land != NULL)
		{
		id = MPAPIselectEntry((int)_LAND, aGlobdata->land,
									 (char *)&globLAND, sizeof(LAND), sizeof(globLAND.land_id));
		if (id != _UNDEF)
			aProf->land_id = globLAND.land_id;
		}

	/*	TRAEGER_TYP */
	if (*aGlobdata->dltt != NULL)
		{
		id = MPAPIselectEntry((int)_TRAEGER_TYP, aGlobdata->dltt,
									 (char *)&globDLTT, sizeof(TRAEGER_TYP), sizeof(globDLTT.typ_id));
		if (id != _UNDEF)
			aProf->dltt_id = globDLTT.typ_id;
		}

	/*	KATEGORIE */
	if (*aGlobdata->kat != NULL)
		{
		id = MPAPIselectEntry((int)_KATEGORIE, aGlobdata->kat,
									 (char *)&globKAT, sizeof(KATEGORIE), sizeof(globKAT.kat_id));
		if (id != _UNDEF)
			aProf->kat_id = globKAT.kat_id;
		}

	/* DIENST_TRAEGER */
	globDLT.stufe = (int)1;
	if (*aGlobdata->dlt != NULL)
		{
		id = MPAPIselectEntry((int)_DIENST_TRAEGER, aGlobdata->dlt,
									 (char *)&globDLT, sizeof(DIENST_TRAEGER), sizeof(globDLT.dlt_id));
		if (id != _UNDEF)
			{
			aProf->dlt_id = globDLT.dlt_id;
			strcpy(glob_host_dlt, aGlobdata->dlt);
			strcpy(glob_dlt_bch, aGlobdata->dlt);
			}
		}

	/*	ANGEBOTS_TYP */
	if (*aGlobdata->dlat != NULL)
		{
		id = MPAPIselectEntry((int)_ANGEBOTS_TYP, aGlobdata->dlat,
									 (char *)&globDLAT, sizeof(ANGEBOTS_TYP), sizeof(globDLAT.art_id));
		if (id != _UNDEF)
			aProf->dlat_id = globDLAT.art_id;
		}

	/*	REISENDER_TYP DLNT */
	if (*aGlobdata->dlnt != NULL)
		{
		id = MPAPIselectEntry((int)_REISENDER_TYP, aGlobdata->dlnt,
									 (char *)&globDLNT, sizeof(REISENDER_TYP), sizeof(globDLNT.rkr_id));
		if (id != _UNDEF)
			aProf->dlnt_id = globDLNT.rkr_id;
		}

	/*	SAISON */
	if (*aGlobdata->saison != NULL)
		{
		id = MPAPIselectEntry((int)_SAISON, aGlobdata->saison,
									 (char *)&globSAI, sizeof(SAISON), sizeof(globSAI.sai_id));
		if (id != _UNDEF)
			aProf->sai_id = globSAI.sai_id;
		}

	/*	PROGRAMM */
	if (*aGlobdata->programm != NULL)
		{
		id = MPAPIselectEntry((int)_PROGRAMM, aGlobdata->programm,
									 (char *)&globPRG, sizeof(PROGRAMM), sizeof(globPRG.prg_id));
		if (id != _UNDEF)
			aProf->prg_id = globPRG.prg_id;
		}

	/*	Abfahrtszeit */
	if (*aGlobdata->a_zeit != NULL)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		DateTime.tm_hour=(int)_UNDEF;
		DateTime.tm_min=(int)_UNDEF;
		(void)ReadDate(&DateTime, (time_t *)&globA_ZEIT, aGlobdata->a_zeit);
		aProf->a_zeit = globA_ZEIT;
		}

	/*	Globale Ankunftszeit festlegen */
	if (*aGlobdata->e_zeit != NULL)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		DateTime.tm_hour=(int)_UNDEF;
		DateTime.tm_min=(int)_UNDEF;
		(void)ReadDate(&DateTime, (time_t *)&globE_ZEIT, aGlobdata->e_zeit);
		aProf->e_zeit = globE_ZEIT;
		}


	(void)MPAPIdb_committrx();

	/* send GLOBDATA to GUI */
	(void)memcpy((void *)comm.buffer, (void *)aGlobdata, sizeof(GLOBDATA));
	comm.datalen = sizeof(GLOBDATA);

	/* update mp_profil table */

	return(status);
}
