/*D***********************************************************
 * Modul:     API - minimum id in a table                           
 *            gibt die kleinste ID einer Tabelle zurueck
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */
#include <mpsqlcnt.h>		/* SQL MIN statements */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/UtilIDmin.c,v 1.2 2008-11-02 19:55:48 mwn Exp $";

int min_id_num(int table, int typ)
{
	extern MEMOBJ apimem;
	extern STATUS_WERTE sta;

	int status=(int)MPOK;

	int anzahl, i;
	int AnzByte=sizeof(int);
	int selecttable = (int)_INTEGER;

	char minquery[_QUERYLEN];
	int minimum;
	short minshort;
	char cntquery[_QUERYLEN];
	int count;
	int cnt;

	/* init */
	count = 1;
	minimum = 0;
	*minquery = NULL;
	*cntquery = NULL;

	switch(table)
		{
		case _DIENST_TRAEGER	:
			(void)sprintf(minquery, _SEL_MIN_DLT);
			break;
		case _TRAEGER_TYP	:
			(void)sprintf(minquery, _SEL_MIN_DLTT);
			break;
		case _DIENST_ANGEBOT	:
			(void)sprintf(minquery, _SEL_MIN_DLA);
			break;
		case _ANGEBOTS_TYP	:
			(void)sprintf(minquery, _SEL_MIN_DLAT);
			break;
		case _STATUS_WERTE:
			(void)sprintf(cntquery, _COUNT_STA_TYP, sta.typ);
			(void)sprintf(minquery, _SEL_MIN_STA, sta.typ);
			break;
		case _AKTIONEN		:
			(void)sprintf(minquery, _SEL_MIN_AKT);
			break;
		case _AKTIONS_TYP	:
			(void)sprintf(minquery, _SEL_MIN_AKTT);
			break;
		case _KATEGORIE		:
			(void)sprintf(minquery, _SEL_MIN_KAT);
			break;
		case _KUNDEN		:
			(void)sprintf(minquery, _SEL_MIN_KUN);
			break;
		case _KUNDEN_TYP		:
			(void)sprintf(minquery, _SEL_MIN_KUNT);
			break;
		case _REISENDER_TYP	:
			(void)sprintf(minquery, _SEL_MIN_REIT);
			break;
		case _KOSTEN_ART	:
			(void)sprintf(minquery, _SEL_MIN_KAR);
			break;
		case _KOLLEKTIV_TYP	:
			(void)sprintf(minquery, _SEL_MIN_KOLT);
			break;
		case _PROGRAMM		:
			(void)sprintf(minquery, _SEL_MIN_PRG);
			break;
		case _REISENDER		:
			(void)sprintf(minquery, _SEL_MIN_REI);
			break;
		case _KOLLEKTIV		:
			(void)sprintf(minquery, _SEL_MIN_KOL);
			break;
		case _SAISON		:
			(void)sprintf(minquery, _SEL_MIN_SAI);
			break;
		case _ARRANGEMENT		:
			(void)sprintf(minquery, _SEL_MIN_ARR);
			break;
		case _DIENSTLEISTUNG	:
			(void)sprintf(minquery, _SEL_MIN_DTG);
			break;
		case _DLG_PART	:
			(void)sprintf(minquery, _SEL_MIN_DLG);
			break;
		case _BUCHUNG		:
			(void)sprintf(minquery, _SEL_MIN_BCH);
			break;
		case _KONTINGENT		:
			(void)sprintf(minquery, _SEL_MIN_KON);
			break;
		case _GRAPHIK		:
			(void)sprintf(minquery, _SEL_MIN_GRA);
			break;
		case _PCX_FILES		:
			(void)sprintf(minquery, _SEL_MIN_PCX);
			break;
		case _BEZEICHNUNG:
			(void)sprintf(cntquery, _COUNT_BEZ_TYP, typ);
			(void)sprintf(minquery, _SEL_MIN_BEZ, typ);
			break;
		case _TEXTE:
			(void)sprintf(cntquery, _COUNT_TXT_TYP, typ);
			(void)sprintf(minquery, _SEL_MIN_TXT, typ);
			break;
		case _SPRACHEN:
			(void)sprintf(cntquery, _COUNT_SPR);
			(void)sprintf(minquery, _SEL_MIN_SPR);
			break;

		default:
			return((int)_UNDEF);
			break;
		}

	/* error if no query is present */
	if (*minquery == NULL)
		return((int)_UNDEF);

	/* set type of max id value */
	if (AnzByte == sizeof(short))
		selecttable = (int)_SHORT;

	/* count the needed ID's first to see if there's at least one entry */
	if (*cntquery != NULL)
		{
		status = MPAPIdb_sqlquery((int)_INTEGER, &apimem.buffer, cntquery, &cnt,
		                         &apimem.datalen, &apimem.alloclen);
		if (status == (int)MPOK && cnt > 0)
			(void)memcpy((void *)&count, (void *)apimem.buffer, sizeof(int));
		else
			count = (int)0;
		}

	/* if count is not 0 then get the max_id */
	if (count > 0)
		{
		status=MPAPIdb_sqlquery(selecttable, &apimem.buffer, minquery, &anzahl,
		                          &apimem.datalen, &apimem.alloclen);
		if (status == (int)MPOK)
			{
			if (anzahl > (int)0)
				{
				if (AnzByte == sizeof(short))
					{
					(void)memcpy((void *)&minshort, (void *)apimem.buffer, AnzByte);
					minimum = (int)minshort;
					}
				else
					(void)memcpy((void *)&minimum, (void *)apimem.buffer, sizeof(int));
				}
			}
		else
			minimum = (int)_UNDEF;
		}

	return(minimum);
}
