/*D***********************************************************
 * Modul:     API - give new table id
 *            Returns a new and free ID
 *            min. ID is 1
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

//
// this module must reflect different implementations as the new id feature
// is very different from db to db.
// Oracle uses SEQ.NEXTVAL FROM DUAL
// Mysql needs an auto_increment on the table and mysql_new_id()
// MS SQL
//


static char	rcsid[] = "$Header: /yafra/cvsroot/mapo/source/api/UtilIDnew.c,v 1.3 2008-11-23 15:44:38 mwn Exp $";

#ifdef MPDBORACLE
#define _SEL_COMMONID "SELECT TDBADMIN.MP_COMMON_SEQ.NEXTVAL FROM DUAL;"
#endif

int
MPAPIid_new(int table, int arg1, int arg2)
	{
	extern MEMOBJ apimem;
	extern STATUS_WERTE sta;

	int tmp_sta_typ;
	int free_id;
	char cntquery[_QUERYLEN];
	int status = (int) MPOK;
	int cnt;

#ifdef MPDBORACLE
	switch(table)
		{
		case _BEZEICHNUNG:
			(void)sprintf(cntquery, "SELECT TDBADMIN.BEZEICHNUNG_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _SAISON:
			(void)sprintf(cntquery, "SELECT TDBADMIN.SAISON_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _ORT:
			(void)sprintf(cntquery, "SELECT TDBADMIN.ORT_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _PERSONEN:
			(void)sprintf(cntquery, "SELECT TDBADMIN.PERSONEN_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _KOLLEKTIV:
			(void)sprintf(cntquery, "SELECT TDBADMIN.KOLLEKTIV_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _TRAEGER_TYP:
			(void)sprintf(cntquery, "SELECT TDBADMIN.TRAEGER_TYP_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _KATEGORIE:
			(void)sprintf(cntquery, "SELECT TDBADMIN.KATEGORIE_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _DIENST_TRAEGER:
			(void)sprintf(cntquery, "SELECT TDBADMIN.DIENST_TRAEGER_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _DIENST_ANGEBOT :
			(void)sprintf(cntquery, "SELECT TDBADMIN.DIENST_ANGEBOT_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _DLG_PART :
			(void)sprintf(cntquery, "SELECT TDBADMIN.DLG_PARTS_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _DIENSTLEISTUNG :
			(void)sprintf(cntquery, "SELECT TDBADMIN.DIENSTLEISTUNG_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _PROGRAMM :
			(void)sprintf(cntquery, "SELECT TDBADMIN.PROGRAMM_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _ARRANGEMENT:
			(void)sprintf(cntquery, "SELECT TDBADMIN.ARRANGEMENT_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _HOST_KONT:
			(void)sprintf(cntquery, "SELECT TDBADMIN.HOST_KONT_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _KONTINGENT:
			(void)sprintf(cntquery, "SELECT TDBADMIN.KONTINGENT_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _BUCHUNG:
			(void)sprintf(cntquery, "SELECT TDBADMIN.BUCHUNG_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _KOMMISSION:
			(void)sprintf(cntquery, "SELECT TDBADMIN.KOMMISSION_SEQ.NEXTVAL FROM DUAL;");
			break;
		case _PREIS :
			(void)sprintf(cntquery, "SELECT TDBADMIN.PREIS_SEQ.NEXTVAL FROM DUAL;");
			break;
		default:
			(void)sprintf(cntquery, _SEL_COMMONID);
			break;
		}
	status = MPAPIdb_sqlquery((int)_INTEGER, &apimem.buffer, cntquery, &cnt,
			&apimem.datalen, &apimem.alloclen);
	if (status == (int)MPOK && cnt> 0)
		(void)memcpy((void *)&free_id, (void *)apimem.buffer, sizeof(int));
	else
		free_id = (int)_UNDEF;
#else
	tmp_sta_typ = sta.typ; // save as we need to set it to UNDEF to get a new ID
	sta.typ = _UNDEF;
	free_id = (MPAPIid_max(table, (int) _UNDEF, NULL) + 1);
	if (free_id < 1)
		free_id = (int) 1; //TODO -1/UNDEF could mean an error - no error handling here
	sta.typ = tmp_sta_typ; // restore status type
#endif

	return (free_id);
	}
