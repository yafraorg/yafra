/*D***********************************************************
 * Modul:     DBI - database select
 *            Holt einen Eintrag anhand einer Bezeichnung
 *
 * Copyright: yafra.org, Basel, Switzerland
 *
 * Diese Funktion ist Gian gewidmet !!!
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f?r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/SelectEntry.c,v 1.3 2008-11-29 21:56:39 mwn Exp $";

/*
* Definition aller verwendbaren SQL-Select Befehle nach BEZ_ID
*/

#define	_SEL_ONE_SPR	"SELECT S.* \
	FROM TDBADMIN.SPRACHEN S, TDBADMIN.BEZEICHNUNG B \
	WHERE B.S_ID = %d AND B.TYP = %d AND B.BEZ = \'%s\' \
	AND S.BEZ_ID=B.BEZ_ID;"
#define	_SEL_ONE_STA_BEZ "SELECT * FROM TDBADMIN.BEZEICHNUNG \
	WHERE BEZ = \'%s\' AND S_ID=%d AND BEZ_ID = 0;"
#define	_SEL_ONE_STA	"SELECT SW.* \
	FROM TDBADMIN.STATUS_WERTE SW, TDBADMIN.BEZEICHNUNG B \
	WHERE SW.BEZ_ID=B.BEZ_ID AND B.S_ID = %d \
	AND B.TYP = %d AND SW.TYP = %d AND B.BEZ = \'%s\';"
#define	_SEL_ONE_BEZ_NAM "SELECT * FROM TDBADMIN.BEZEICHNUNG \
	WHERE BEZ = \'%s\' AND S_ID=%d AND BEZ_ID = 0;"
#define	_SEL_ONE_BEZ	"SELECT * FROM TDBADMIN.BEZEICHNUNG \
	WHERE BEZ = \'%s\' AND S_ID=%d AND TYP= %d;"
#define	_SEL_ONE_TXT "SELECT * FROM TDBADMIN.TEXTE WHERE S_ID=%d \
	AND TYP= %d AND TEXT = \'%s\';"
#define	_SEL_ONE_SAI	"SELECT SA.* \
	FROM TDBADMIN.SAISON SA, TDBADMIN.BEZEICHNUNG B \
	WHERE SA.BEZ_ID=B.BEZ_ID AND B.S_ID = %d \
	AND B.TYP = %d AND B.BEZ = \'%s\';"



#define _SEL_ONE_LAND "SELECT L.* \
	FROM TDBADMIN.LAND L, TDBADMIN.BEZEICHNUNG B \
	WHERE L.BEZ_ID=B.BEZ_ID AND B.S_ID = %d AND B.TYP = %d \
	AND B.BEZ = \'%s\';"
#define _SEL_ONE_ORT "SELECT O.* \
	FROM TDBADMIN.ORT O, TDBADMIN.BEZEICHNUNG B \
	WHERE O.BEZ_ID=B.BEZ_ID AND B.S_ID = %d AND B.TYP = %d \
	AND B.BEZ = \'%s\';"
#define _SEL_ONE_WHR "SELECT W.* \
	FROM TDBADMIN.WAEHRUNG W, TDBADMIN.BEZEICHNUNG B \
	WHERE W.BEZ_ID=B.BEZ_ID AND B.S_ID = %d AND B.TYP = %d \
	AND B.BEZ = \'%s\';"



#define	_SEL_ONE_REIT	"SELECT RT.* \
	FROM TDBADMIN.REISENDER_TYP RT, TDBADMIN.BEZEICHNUNG B \
	WHERE RT.BEZ_ID=B.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ = \'%s\';"
#define	_SEL_ONE_REI "SELECT * FROM TDBADMIN.REISENDER \
	WHERE PERS_ID = %d;"
#define	_SEL_ONE_DLNV "SELECT * FROM TDBADMIN.DLN_VIEW \
	WHERE DLN_ID = %d;"
#define	_SEL_ONE_KUNT	"SELECT KT.* \
	FROM TDBADMIN.KUNDEN_TYP KT, TDBADMIN.BEZEICHNUNG B \
	WHERE KT.BEZ_ID=B.BEZ_ID AND B.S_ID = %d \
	AND B.TYP = %d AND B.BEZ = \'%s\';"
#define _SEL_ONE_KUN "SELECT * FROM TDBADMIN.KUNDEN K \
	WHERE K.PERS_ID = %d;"
#define _SEL_ONE_KUNV "SELECT * FROM TDBADMIN.KUNDEN_VIEW \
	WHERE KUN_ID = %d;"
#define	_SEL_ONE_KOLT	"SELECT KOLT.* \
	FROM TDBADMIN.KOLLEKTIV_TYP KOLT, TDBADMIN.BEZEICHNUNG B \
	WHERE KOLT.BEZ_ID=B.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ = \'%s\';"
#define	_SEL_ONE_KOL	"SELECT KO.* \
	FROM TDBADMIN.KOLLEKTIV KO \
	WHERE KO.NAME = \'%s\';"




#define	_SEL_ONE_DLTT	"SELECT TTYP.* \
	FROM TDBADMIN.TRAEGER_TYP TTYP, TDBADMIN.TTYP_VIEW TTYPV \
	WHERE TTYPV.BEZ= \'%s\' AND TTYPV.HBEZ = \'%s\' \
	AND TTYPV.SPR = %d AND TTYP.TYP_ID = TTYPV.ID;"
#define	_SEL_ONE_KAT	"SELECT K.* \
	FROM TDBADMIN.KATEGORIE K, TDBADMIN.BEZEICHNUNG B \
	WHERE K.BEZ_ID=B.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ = \'%s\';"

/* DLT: DLT im Format  BEZ-DLT  -  BEZ-H_DLT */
#define	_SEL_ONE_DLT "SELECT DLT.* \
	FROM TDBADMIN.DIENST_TRAEGER DLT, TDBADMIN.TRAEGER_VIEW DLTV, TDBADMIN.TRAEGER_VIEW HDLTV \
	WHERE DLTV.BEZ = \'%s\' AND HDLTV.BEZ = \'%s\' AND DLTV.SPR = %d \
	AND HDLTV.SPR = DLTV.SPR \
	AND HDLTV.ID = DLTV.HID AND DLT.DLT_ID = DLTV.ID;"

/* DLT: DLT im Format  BEZ-DLT  -  BEZ-H_DLT  -  HOSTID */
#define	_SEL_ONE_DLT_HOST "SELECT DLT.* \
	FROM TDBADMIN.DIENST_TRAEGER DLT, TDBADMIN.TRAEGER_VIEW DLTV, TDBADMIN.TRAEGER_VIEW HDLTV \
	WHERE DLTV.HOST = %d \
	AND DLTV.BEZ = \'%s\' AND HDLTV.BEZ = \'%s\' AND DLTV.SPR = %d \
	AND HDLTV.SPR = DLTV.SPR \
	AND HDLTV.ID = DLTV.HID AND DLT.DLT_ID = DLTV.ID;"

/* hole ein HOST DLT Eintrag anhand der Bezeichnung */
#define _SEL_ONE_DLT_STU1 "SELECT D.* \
	FROM TDBADMIN.DIENST_TRAEGER D, TDBADMIN.BEZEICHNUNG B \
	WHERE B.TYP = %d AND B.BEZ = \'%s\' AND B.S_ID = %d \
	AND D.BEZ_ID = B.BEZ_ID;"

#define	_SEL_ONE_DLAT	"SELECT AT.* \
	FROM TDBADMIN.ANGEBOTS_TYP AT, TDBADMIN.BEZEICHNUNG B \
	WHERE AT.BEZ_ID=B.BEZ_ID AND B.S_ID = %d \
	AND B.TYP = %d AND B.BEZ = \'%s\';"
#define	_SEL_ONE_AKTT	"SELECT AT.* \
	FROM TDBADMIN.AKTIONS_TYP AT, TDBADMIN.BEZEICHNUNG B \
	WHERE AT.BEZ_ID=B.BEZ_ID AND B.S_ID = %d \
	AND B.TYP = %d AND B.BEZ = \'%s\';"
#define _SEL_ONE_AKT "SELECT A.* \
	FROM TDBADMIN.AKTIONEN A, TDBADMIN.BEZEICHNUNG B \
	WHERE A.BEZ_ID=B.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ = \'%s\';"
#define	_SEL_ONE_DLA	"SELECT DLA.* \
	FROM TDBADMIN.DIENST_ANGEBOT DLA, TDBADMIN.BEZEICHNUNG B \
	WHERE DLA.BEZ_ID=B.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ = \'%s\';"
#define	_SEL_ONE_DLG	"SELECT TDBADMIN.DLG_PARTS.* \
	FROM TDBADMIN.DLG_PARTS, TDBADMIN.BEZEICHNUNG \
	WHERE TDBADMIN.DLG_PARTS.BEZ_ID=TDBADMIN.BEZEICHNUNG.BEZ_ID \
	AND TDBADMIN.BEZEICHNUNG.S_ID = %d \
	AND TDBADMIN.BEZEICHNUNG.TYP = %d \
	AND TDBADMIN.BEZEICHNUNG.BEZ = \'%s\' \
	AND TDBADMIN.DLG_PARTS.A_ZEIT = %d;"
#define	_SEL_ONE_DTG	"SELECT DL.* \
	FROM TDBADMIN.DIENSTLEISTUNG DL, TDBADMIN.BEZEICHNUNG B \
	WHERE DL.BEZ_ID=B.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ = \'%s\' \
	AND DL.A_ZEIT = %d;"
#define	_SEL_ONE_PRG	"SELECT P.* \
	FROM TDBADMIN.PROGRAMM P, TDBADMIN.BEZEICHNUNG B \
	WHERE P.BEZ_ID=B.BEZ_ID AND B.S_ID = %d \
	AND B.TYP = %d AND B.BEZ = \'%s\';"
#define	_SEL_ONE_ARR	"SELECT ARR.* \
	FROM TDBADMIN.ARRANGEMENT ARR, TDBADMIN.BEZEICHNUNG B \
	WHERE ARR.BEZ_ID=B.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ = \'%s\' \
	AND ARR.A_DAT BETWEEN %d AND %d;"


#define _SEL_ONE_HKON "SELECT HK.* \
	FROM TDBADMIN.HOST_KONT HK, TDBADMIN.BEZEICHNUNG B \
	WHERE B.BEZ = \'%s\' AND B.TYP = %d AND B.S_ID = %d \
	AND HK.BEZ_ID = B.BEZ_ID;"
#define _SEL_ONE_KON "SELECT K.* \
	FROM TDBADMIN.KONTINGENT K, TDBADMIN.BEZEICHNUNG B \
	WHERE B.BEZ = \'%s\' AND B.TYP = %d AND B.S_ID = %d \
	AND K.BEZ_ID = B.BEZ_ID;"


#define	_SEL_ONE_BCH	"SELECT * FROM TDBADMIN.BUCHUNG WHERE REF = \'%s\';"
#define	_SEL_ONE_KAR	"SELECT KA.* \
	FROM TDBADMIN.KOSTEN_ART KA, TDBADMIN.BEZEICHNUNG B \
	WHERE KA.BEZ_ID=B.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ = \'%s\';"
#define	_SEL_ONE_KOM	"SELECT K.* \
	FROM TDBADMIN.KOMMISSION K, TDBADMIN.BEZEICHNUNG B \
	WHERE K.BEZ_ID=B.BEZ_ID AND B.S_ID = %d AND B.TYP = %d \
	AND B.BEZ = \'%s\';"
#define _SEL_ONE_PRE "SELECT * FROM TDBADMIN.PREIS \
	WHERE PRE_ID = %d;"


/* Grafik Bezeichnungen */
#define	_SEL_ONE_GRA "SELECT G.* \
	FROM TDBADMIN.GRAPHIK G, TDBADMIN.BEZEICHNUNG B \
	WHERE G.BEZ_ID = B.BEZ_ID AND B.S_ID = %d AND B.TYP = %d \
	AND B.BEZ = \'%s\';"
#define	_SEL_ONE_PCX	"SELECT PCX.* \
	FROM TDBADMIN.PCX_FILES PCX, TDBADMIN.BEZEICHNUNG B \
	WHERE PCX.BEZ_ID=B.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ = \'%s\';"


int MPAPIselectEntry(int table , char *bezeichnung , char *pointer , int bytes , size_t id_type )
{
	extern MEMOBJ apimem;
	extern BUCHUNG bch;
	extern int sprache;
	extern unsigned char logging_mp;

	TEXTE *txt_ptr;
	DIENST_TRAEGER *dlt_ptr;
	BEZEICHNUNG *bez_ptr;
	STATUS_WERTE *sta_ptr;
	BUCHUNG *bch_ptr;
	struct tm DateTime;
	char query[_QUERYLEN];
	char buffer1[_RECORDLEN];
	char buffer2[_RECORDLEN];
	char buffer3[_RECORDLEN];
	int anzahl, id, a_dat;
	int status=(int)MPOK;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	(void)memset((void *)buffer2, NULL, sizeof(buffer2));
	(void)memset((void *)buffer3, NULL, sizeof(buffer3));

	/* set default id_type size to integer if none is given */
	if (id_type == (size_t)0)
		id_type = sizeof(int);

	switch(table)
		{
		case _SPRACHEN:
			(void)sprintf(query, _SEL_ONE_SPR, sprache, table, bezeichnung);
			break;
		case _BEZEICHNUNG:
			bez_ptr=(BEZEICHNUNG *)pointer;
			if (bez_ptr->typ != (int)_NAMEN)
				{
				if (bez_ptr->typ == (int)_UNDEF)
					(void)sprintf(query, _SEL_ONE_BEZ_NAM, bez_ptr->bez, bez_ptr->s_id);
				else
					(void)sprintf(query, _SEL_ONE_BEZ, bez_ptr->bez, bez_ptr->s_id, bez_ptr->typ);
				}
			else
				(void)sprintf(query, _SEL_ONE_STA_BEZ, bez_ptr->bez, bez_ptr->s_id);
			break;
		case _TEXTE:
			txt_ptr=(TEXTE *)pointer;
			(void)sprintf(query, _SEL_ONE_TXT, txt_ptr->s_id, txt_ptr->typ, bezeichnung);
			break;
		case _STATUS_WERTE:
			sta_ptr=(STATUS_WERTE *)pointer;
			(void)sprintf(query, _SEL_ONE_STA, sprache, sta_ptr->typ, sta_ptr->typ, bezeichnung);
			break;
		case _SAISON:
			(void)sprintf(query, _SEL_ONE_SAI, sprache, table, bezeichnung);
			break;


		case _LAND:
			(void)sprintf(query, _SEL_ONE_LAND, sprache, table, bezeichnung);
			break;
		case _ORT:
			(void)sprintf(query, _SEL_ONE_ORT, sprache, table, bezeichnung);
			break;
		case _WAEHRUNG:
			(void)sprintf(query, _SEL_ONE_WHR, sprache, table, bezeichnung);
			break;



		case _REISENDER:
			(void)sscanf(bezeichnung, "%[^:]%*2c%[^:]%*2c%31c", buffer1, buffer2, buffer3);
			buffer1[strlen(buffer1)-1] = '\0';
			buffer2[strlen(buffer2)-1] = '\0';
			id = atoi(buffer1);
			(void)sprintf(query, _SEL_ONE_REI, id);
			break;
		case _DLN_VIEW:
			(void)sscanf(bezeichnung, "%[^:]%*2c%[^:]%*2c%31c", buffer1, buffer2, buffer3);
			buffer1[strlen(buffer1)-1] = '\0';
			buffer2[strlen(buffer2)-1] = '\0';
			id = atoi(buffer1);
			(void)sprintf(query, _SEL_ONE_DLNV, id);
			break;
		case	_KOLLEKTIV:
			(void)sprintf(query, _SEL_ONE_KOL, bezeichnung);
			break;
		case _KUNDEN:
			(void)sscanf(bezeichnung, "%[^:]%*2c%[^:]%*2c%31c", buffer1, buffer2, buffer3);
			buffer1[strlen(buffer1)-1] = '\0';
			buffer2[strlen(buffer2)-1] = '\0';
			id = atoi(buffer1);
			(void)sprintf(query, _SEL_ONE_KUN, id);
			break;
		case _KUN_VIEW:
			(void)sscanf(bezeichnung, "%[^:]%*2c%[^:]%*2c%31c", buffer1, buffer2, buffer3);
			buffer1[strlen(buffer1)-1] = '\0';
			buffer2[strlen(buffer2)-1] = '\0';
			id = atoi(buffer1);
			(void)sprintf(query, _SEL_ONE_KUNV, id);
			break;
		case	_KUNDEN_TYP	:
			(void)sprintf(query, _SEL_ONE_KUNT, sprache, table, bezeichnung);
			break;
		case	_REISENDER_TYP	:
			(void)sprintf(query, _SEL_ONE_REIT, sprache, table, bezeichnung);
			break;
		case	_KOLLEKTIV_TYP	:
			(void)sprintf(query, _SEL_ONE_KOLT, sprache, table, bezeichnung);
			break;


		case	_TRAEGER_TYP	:
			(void)sscanf(bezeichnung, "%[^=]%*3c%31c", buffer1, buffer2);
			buffer1[strlen(buffer1)-1] = '\0';
			(void)sprintf(query, _SEL_ONE_DLTT, buffer1, buffer2, sprache);
			break;
		case	_KATEGORIE	:
			(void)sprintf(query, _SEL_ONE_KAT, sprache, table, bezeichnung);
			break;
		case _DIENST_TRAEGER:
			/* Host DLT:    Stufe       =  1
                         Bezeichnung =  DLT
				normal DLT:  Stufe       >  1
                         Bezeichnung =  DLT => H_DLT
         */
			dlt_ptr=(DIENST_TRAEGER *)pointer;
			if (dlt_ptr->stufe == (int)1)
				(void)sprintf(query, _SEL_ONE_DLT_STU1, (int)_DIENST_TRAEGER, bezeichnung, sprache);
			else
				{
				(void)sscanf(bezeichnung, "%[^=]%*3c%31c", buffer1, buffer2);
				buffer1[strlen(buffer1)-1] = '\0';
				if (dlt_ptr->host_id > 0)
					(void)sprintf(query, _SEL_ONE_DLT_HOST, dlt_ptr->host_id,
					              buffer1, buffer2, sprache);
				else
					(void)sprintf(query, _SEL_ONE_DLT, buffer1, buffer2, sprache);
				}
			break;
		case	_ANGEBOTS_TYP	:
			(void)sprintf(query, _SEL_ONE_DLAT, sprache, table, bezeichnung);
			break;
		case	_AKTIONS_TYP	:
			(void)sprintf(query, _SEL_ONE_AKTT, sprache, table, bezeichnung);
			break;
		case	_AKTIONEN	:
			(void)sprintf(query, _SEL_ONE_AKT, sprache, (int)_AKTIONEN, bezeichnung);
			break;
		case	_DIENST_ANGEBOT	:
			(void)sprintf(query, _SEL_ONE_DLA, sprache, table, bezeichnung);
			break;
		case	_DLG_PART	:
			(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
			DateTime.tm_min=(int)_UNDEF;
			DateTime.tm_hour=(int)_UNDEF;
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			(void)sscanf(bezeichnung, "%[^=]%*3c%31c", buffer1, buffer2);
			buffer1[strlen(buffer1)-1] = '\0';
			(void)ReadDate(&DateTime, (time_t *)&a_dat, buffer2);
			(void)sprintf(query, _SEL_ONE_DLG, sprache, table, buffer1, a_dat);
			break;
		case	_DIENSTLEISTUNG	:
			(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
			DateTime.tm_min=(int)_UNDEF;
			DateTime.tm_hour=(int)_UNDEF;
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			(void)sscanf(bezeichnung, "%[^=]%*3c%31c", buffer1, buffer2);
			buffer1[strlen(buffer1)-1] = '\0';
			(void)ReadDate(&DateTime, (time_t *)&a_dat, buffer2);
			(void)sprintf(query, _SEL_ONE_DTG, sprache, table, buffer1, a_dat);
			break;
		case	_PROGRAMM	:
			(void)sprintf(query, _SEL_ONE_PRG, sprache, table, bezeichnung);
			break;
		case	_ARRANGEMENT	:
			(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			(void)sscanf(bezeichnung, "%[^=]%*3c%31c", buffer1, buffer2);
			buffer1[strlen(buffer1)-1] = '\0';
			(void)ReadDate(&DateTime, (time_t *)&a_dat, buffer2);
			(void)sprintf(query, _SEL_ONE_ARR, sprache, table, buffer1, a_dat, a_dat +(int)86399);
			break;


		case _HOST_KONT:
			(void)sprintf(query, _SEL_ONE_HKON, bezeichnung, table, sprache);
			break;
		case _KONTINGENT:
			(void)sprintf(query, _SEL_ONE_KON, bezeichnung, table, sprache);
			break;


		case	_BUCHUNG	:
			(void)sprintf(query, _SEL_ONE_BCH, bezeichnung);
			break;
		case	_KOSTEN_ART	:
			(void)sprintf(query, _SEL_ONE_KAR, sprache, table, bezeichnung);
			break;
		case	_KOMMISSION	:
			(void)sprintf(query, _SEL_ONE_KOM, sprache, table, bezeichnung);
			break;
		case _PREIS:
			(void)sscanf(bezeichnung, "%[^:]%*2c%[^:]%*2c%31c", buffer1, buffer2, buffer3);
			buffer1[strlen(buffer1)-1] = '\0';
			buffer2[strlen(buffer2)-1] = '\0';
			id = atoi(buffer1);
			(void)sprintf(query, _SEL_ONE_PRE, id);
			break;
		case	_RESERVATION	:
			return((int)_UNDEF);
			break;


		case	_PCX_FILES	:
			(void)sprintf(query, _SEL_ONE_PCX, sprache, table, bezeichnung);
			break;
		case	_GRAPHIK	:
			(void)sprintf(query, _SEL_ONE_GRA, sprache, table, bezeichnung);
			break;

		/* unwahrscheinliches Abfangen */
		default:
			if (logging_mp)
				MPlog(_LOGMP, NULL, "switch Fehler", __FILE__);
			status = (int)MPERROR;
			break;
		}

	if (status==(int)MPOK)
		{
		status=MPAPIdb_sqlquery(table, &apimem.buffer, query, &anzahl,
		                         &apimem.datalen, &apimem.alloclen);

		if (status == (int)MPOK)
			{
			if (anzahl == (int)1)
				{
				(void)memcpy((void *)pointer, (void *)apimem.buffer, (size_t)bytes);
				switch (id_type)
					{
					case sizeof(short):
						id = (int)*(short *)apimem.buffer;
						break;
					case sizeof(int):
						id = (int)*(int *)apimem.buffer;
						/* if BUCHUNG then set to bid NOT TO D_BID (is first field) */
						if (table == (int)_BUCHUNG)
							{
							bch_ptr = (BUCHUNG *)pointer;
							id = bch_ptr->bid;
							}
						break;
					default:
						id = (int)_UNDEF;
						break;
					}
				}
			else
				id = (int)_UNDEF;
			}
		else
			id=(int)_UNDEF;
		}
	else
		id=(int)_UNDEF;

	return(id);
}
