/**************************************************************/
/* header:    SQL dynam. insert statements                    */
/*                                                            */
/* copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
/*
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpsqlins.h,v 1.3 2009-01-02 16:51:35 mwn Exp $
*/

/*	Definition aller verwendbaren SQL-Insert Befehlen */


#define _INSERT_MAX	"INSERT INTO TDBADMIN.MAXIMA VALUES (%d,%d,%d,%d,%d);"
#define _INSERT_SPR	"INSERT INTO TDBADMIN.SPRACHEN VALUES (%d,%d,%d,\'%s\',%d,%d);"
#define _INSERT_STA	"INSERT INTO TDBADMIN.STATUS_WERTE VALUES (%d,\'%s\',\'%s\',%d,%f,%d);"
#define _INSERT_BEZ	"INSERT INTO TDBADMIN.BEZEICHNUNG VALUES (%d,%d,\'%s\',%d);"
#define _INSERT_TXT	"INSERT INTO TDBADMIN.TEXTE VALUES (%d,%d,%d,\'%s\',%d);"
#define _INSERT_ATXT	"INSERT INTO TDBADMIN.AKTIONSTEXTE VALUES (%d,%d,%d,\'%s\',%d);"
#define _INSERT_HIS	"INSERT INTO TDBADMIN.HISTORY VALUES (%d,%d,%d,\'%s\',%d,%d);"
#define _INSERT_HLP	"INSERT INTO TDBADMIN.HELP VALUES (%d,%d,%d,%d,\'%s\');"
#define _INSERT_MSG	"INSERT INTO TDBADMIN.MSG VALUES (%d,%d,%d,%d,\'%s\');"
#define _INSERT_LAB	"INSERT INTO TDBADMIN.LABEL VALUES (%d,%d,%d,%d,%d,\'%s\');"
#define _INSERT_SAI	"INSERT INTO TDBADMIN.SAISON VALUES (%d,\'%s\',%d,%d,%d,%d);"

#define _INSERT_WHR  "INSERT INTO TDBADMIN.WAEHRUNG VALUES (%d, %d, %d, %d, \'%s\');"
#define _INSERT_LAND "INSERT INTO TDBADMIN.LAND VALUES (%d, %d, %d, \'%s\', %d, %d, %d, %f, \'%s\');"
#define _INSERT_ORT  "INSERT INTO TDBADMIN.ORT VALUES (%d, %d, %d, %d, \'%s\', %d, %d, %d, %d);"
#define _INSERT_LW   "INSERT INTO TDBADMIN.LAND_WHR VALUES (%d, %d, %d, %f, %f, %d);"
#define _INSERT_LS   "INSERT INTO TDBADMIN.LAND_SPR VALUES (%d, %d);"

#define _INSERT_PERS	"INSERT INTO TDBADMIN.PERSONEN VALUES (%d,%d,\'%s\',%d,%d,%d);"
#define _INSERT_PERSADR	"INSERT INTO TDBADMIN.PERSADR VALUES (%d,%d,\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',%d,%d,%d,%d,%d,\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\');"
#define _INSERT_REIT	"INSERT INTO TDBADMIN.REISENDER_TYP VALUES (%d,%d,%d,\'%s\',%d,%d);"
#define _INSERT_REI	"INSERT INTO TDBADMIN.REISENDER VALUES (%d,\'%s\',%d,%d,%d,\'%s\',\'%s\',\'%s\',\'%s\',%d);"
#define _INSERT_KUNT	"INSERT INTO TDBADMIN.KUNDEN_TYP VALUES (%d,%d,%d,\'%s\');"
#define _INSERT_KUN	"INSERT INTO TDBADMIN.KUNDEN VALUES (%d,\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',%d,\'%s\',\'%s\',%d,%d);"
#define _INSERT_KOLT	"INSERT INTO TDBADMIN.KOLLEKTIV_TYP VALUES (%d,%d,\'%s\',%d);"
#define _INSERT_KOL	"INSERT INTO TDBADMIN.KOLLEKTIV VALUES (%d,\'%s\',%d,%d,\'%s\',%d,%d,%d,%d);"



#define _INSERT_DLTT	"INSERT INTO TDBADMIN.TRAEGER_TYP VALUES (%d,%d,%d,%d,%d);"
#define _INSERT_KAT	"INSERT INTO TDBADMIN.KATEGORIE VALUES (%d,%d,%d,%d,%d,%d);"
#define _INSERT_DLT	"INSERT INTO TDBADMIN.DIENST_TRAEGER VALUES (%d,\'%s\',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);"
#define _INSERT_DLAT	"INSERT INTO TDBADMIN.ANGEBOTS_TYP VALUES (%d,%d,%d);"
#define _INSERT_AKTT	"INSERT INTO TDBADMIN.AKTIONS_TYP VALUES (%d,%d,\'%s\',%d);"
#define _INSERT_AKTP	"INSERT INTO TDBADMIN.AKTIONSPARA VALUES (%d,%d,%d,\'%s\',%d,%d,%d);"
#define _INSERT_AKT	"INSERT INTO TDBADMIN.AKTIONEN VALUES (%d,%d,%d,%d,%d,%d,%d,%d,%d);"
#define _INSERT_AKTG	"INSERT INTO TDBADMIN.AKTIONSGRP VALUES (%d,%d,%d,%d);"
#define _INSERT_DLA	"INSERT INTO TDBADMIN.DIENST_ANGEBOT VALUES (%d,%d,%d,%d,\'%s\',%d,%d,\'%s\',%d,%d,%d,%d,%d);"
#define _INSERT_DLG	"INSERT INTO TDBADMIN.DLG_PARTS VALUES (%d,%d,%d,\'%s\',%d,%d,%d,%d,%d,%d,\'%s\',%d,%d,%d);"
#define _INSERT_DTG	"INSERT INTO TDBADMIN.DIENSTLEISTUNG VALUES (%d,\'%s\',%d,%d,%d,%d,%d);"
#define _INSERT_DD	"INSERT INTO TDBADMIN.DLG_DLG VALUES (%d,%d,%d);"
#define _INSERT_PRG	"INSERT INTO TDBADMIN.PROGRAMM VALUES (%d,\'%s\',%d,%d,%d);"
#define _INSERT_ARR	"INSERT INTO TDBADMIN.ARRANGEMENT VALUES (%d,\'%s\',%d,%d,%d,%d,%d);"
#define _INSERT_AD	"INSERT INTO TDBADMIN.ARR_DLG VALUES (%d,%d,%d,%d);"



#define _INSERT_HKON	"INSERT INTO TDBADMIN.HOST_KONT VALUES (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\'%s\',%d);"
#define _INSERT_KON	"INSERT INTO TDBADMIN.KONTINGENT VALUES (%d,%d,%d,%d,%d,\'%s\',%d,%d);"
#define _INSERT_K_D	"INSERT INTO TDBADMIN.KONT_DETAIL VALUES (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);"



#define _INSERT_BCH	"INSERT INTO TDBADMIN.BUCHUNG VALUES (%d,%d,\'%s\',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);"
#define _INSERT_BD	"INSERT INTO TDBADMIN.BCH_DLN VALUES (%d,%d);"
#define _INSERT_AKTD "INSERT INTO TDBADMIN.AKT_DETAIL VALUES (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);"
#define _INS_BCH_AKT	"INSERT INTO TDBADMIN.AKT_DETAIL \
	SELECT DISTINCT RES.BID, RES.PERS_ID, RES.DLG_ID, %d, RES.TEIL, \
	AKTG.CHILDAKT, AKTG.ORD, %d, -1, -1, RES.SAI_ID, AKTG.PARENTAKT, -1, -1 \
	FROM TDBADMIN.RESERVATION RES, TDBADMIN.DIENSTLEISTUNG DL, TDBADMIN.AKTIONSGRP AKTG \
	WHERE	RES.BID = %d AND RES.PERS_ID = %d AND RES.TEIL = %d AND RES.DLG_ID = %d \
	AND RES.DLG_ID = DL.DLG_ID \
	AND AKTG.PARENTAKT = %d \
	AND AKTG.ORD > 0;"
#define _INSERT_KAR	"INSERT INTO TDBADMIN.KOSTEN_ART VALUES (%d,%d,%d);"
#define _INSERT_KOM	"INSERT INTO TDBADMIN.KOMMISSION VALUES (%d,%d,%d,%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);"
#define _INSERT_KD	"INSERT INTO TDBADMIN.KOMM_DETAIL VALUES (%d,%d,%d,%d,%d,%d);"
#define _INSERT_RES	"INSERT INTO TDBADMIN.RESERVATION VALUES (%d, %d, %d, %d, %d, \
	%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d);"
#define _INSERT_PRE	"INSERT INTO TDBADMIN.PREIS VALUES (%d,%f,%f,%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);"
#define _INSERT_KAPA	"INSERT INTO TDBADMIN.KAPA VALUES (%d,%d,%d,%d,%d,%d,%d,%f,%d,%d);"
#define _INSERT_ARRKOM	"INSERT INTO TDBADMIN.MP_ARRKOM VALUES (%d,%d,%d);"



#define _INSERT_GRA	"INSERT INTO TDBADMIN.GRAPHIK VALUES (%d,%d,%d,%d);"
#define _INSERT_GRAFORM	"INSERT INTO TDBADMIN.GRAFORM VALUES (%d,%d,\'%s\');"
#define _INSERT_REG	"INSERT INTO TDBADMIN.REGIONS VALUES (%d,%d,%d,%d,%d,%d);"
#define _INSERT_PCX	"INSERT INTO TDBADMIN.PCX_FILES VALUES (%d,%d,\'%s\',%d,%d,%d,%d,%d);"
