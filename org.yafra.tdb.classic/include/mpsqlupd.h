/**************************************************************/
/* Header:    SQL dynam. update statements                    */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
/*
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpsqlupd.h,v 1.3 2008-11-02 19:55:33 mwn Exp $
*/


/* Definition aller verwendbaren SQL-Update Befehlen */
#define _UPDATE_SPR "UPDATE TDBADMIN.SPRACHEN \
	SET BEZ_ID = %d, DIALOG = %d, SYSBEZ = \'%s\', OUTPUT = %d, GUI = %d WHERE S_ID = %d;"
#define _UPDATE_STA "UPDATE TDBADMIN.STATUS_WERTE \
	SET BEZ_ID = %d, ABK = \'%s\', STA = \'%s\', KOND = %f \
	WHERE STA_ID = %d AND TYP = %d;"
#define	_UPDATE_BEZ	"UPDATE TDBADMIN.BEZEICHNUNG \
	SET BEZ = \'%s\' \
	WHERE BEZ_ID = %d AND S_ID = %d AND TYP = %d;"
#define	_UPDATE_TXT	"UPDATE TDBADMIN.TEXTE \
	SET TEXT = \'%s\' \
	WHERE TEXTID = %d AND TEXTNR = %d AND S_ID = %d AND TYP = %d;"
#define _UPDATE_MSG "UPDATE TDBADMIN.MSG \
	SET MSG_TYP = %d, TEXT = \'%s\' \
	WHERE MSG_ID = %d AND TEXTNR = %d AND S_ID = %d;"
#define _UPDATE_SAI "UPDATE TDBADMIN.SAISON \
	SET CODE = \'%s\', BEZ_ID = %d, VON = %d, BIS = %d, TEXTID = %d \
	WHERE SAI_ID = %d;"



#define _UPDATE_WHR "UPDATE TDBADMIN.WAEHRUNG \
	SET BEZ_ID = %d, TEXTID = %d, STATUS = %d, KRZL = \'%s\' \
	WHERE WHR_ID = %d;"
#define _UPDATE_LAND "UPDATE TDBADMIN.LAND \
	SET BEZ_ID = %d, TEXTID = %d, KRZL = \'%s\', HAUPT_ORT = %d, \
	HAUPT_WHR = %d, HAUPT_SPR = %d, VAT = %f, DATEFORMAT = \'%s\' \
	WHERE LAND_ID = %d;"
#define _UPDATE_ORT "UPDATE TDBADMIN.ORT \
	SET BEZ_ID = %d, LAND_ID = %d, TEXTID = %d, KRZL = \'%s\', \
	ZEITVER = %d, KOORD1 = %d, KOORD2 = %d, ORT_TYP = %d WHERE ORT_ID = %d;"
#define _UPDATE_LW "UPDATE TDBADMIN.LAND_WHR \
	SET A_KURS = %f, V_KURS = %f, VON_DAT = %d \
	WHERE LAND_ID = %d AND WHR_ID = %d AND KURS_TYP = %d;"




#define _UPDATE_PERS "UPDATE TDBADMIN.PERSONEN \
	SET NAME = \'%s\', S_ID = %d, STA_ID = %d, TEXTID = %d \
	WHERE PERS_ID = %d;"
#define _UPDATE_PERSADR "UPDATE TDBADMIN.PERSADR \
	SET ANS = \'%s\', ADR1 = \'%s\', ADR2 = \'%s\', ADR3 = \'%s\', ORT = \'%s\', \
	PLZ = \'%s\', STA_ID = %d, ADR_TYP = %d, KANT = \'%s\', LAND_ID = %d, \
   HAUPT_FLAG = %d, RCH_FLAG = %d, MAIL_FLAG = %d, TEL = \'%s\', HANDY = \'%s\', \
   FAX = \'%s\', EMAIL = \'%s\', WEB = \'%s\' \
   WHERE PERS_ID = %d;"
#define _UPDATE_REIT "UPDATE TDBADMIN.REISENDER_TYP \
	SET BEZ_ID = %d, TEXTID = %d, DLNCODE = \'%s\', VONALTER=%d, BISALTER=%d \
	WHERE RKR_ID = %d;"
#define _UPDATE_REI "UPDATE TDBADMIN.REISENDER \
	SET VOR = \'%s\', RKR_ID = %d, SEX = %d, EXT_TXT = %d, MUTTERS_ID = %d, \
	AGE = \'%s\', PASSNR = \'%s\', ATTR1 = \'%s\', ATTR2 = \'%s\' \
	WHERE PERS_ID = %d;"
#define _UPDATE_KUNT "UPDATE TDBADMIN.KUNDEN_TYP \
	SET BEZ_ID = %d, TEXTID = %d, KUNCODE = \'%s\' \
	WHERE K_TYP_ID = %d;"
#define _UPDATE_KUN "UPDATE TDBADMIN.KUNDEN \
	SET HANDY = \'%s\', TEL = \'%s\', FAX = \'%s\', TLX = \'%s\', \
	 KONTO = \'%s\', LEITER = \'%s\', ATTR1 = \'%s\', ATTR2 = \'%s\', EMAIL = \'%s\', WEB = \'%s\', \
	 K_TYP_ID = %d, WHR_ID = %d \
	WHERE PERS_ID = %d;"
#define _UPDATE_KOLT "UPDATE TDBADMIN.KOLLEKTIV_TYP \
	SET BEZ_ID = %d, TEXTID = %d, KOLCODE = \'%s\' \
	WHERE K_TYP_ID = %d;"
#define _UPDATE_KOL "UPDATE TDBADMIN.KOLLEKTIV \
	SET NAME = \'%s\', REF = \'%s\', HAUPTPERS = %d, K_STA = %d, \
	 K_TYP_ID = %d, TEXTID = %d, KID = %d, KBST = %d \
	WHERE K_ID = %d;"






#define _UPDATE_DLTT "UPDATE TDBADMIN.TRAEGER_TYP \
	SET BEZ_ID = %d, H_TYP_ID = %d, HOST_TYP = %d, TEXTID = %d \
	WHERE TYP_ID = %d;"
#define	_UPDATE_KAT	"UPDATE TDBADMIN.KATEGORIE \
	SET BEZ_ID = %d, H_KAT_ID = %d, TYP_ID	= %d, GA	= %d, TEXTID = %d \
	WHERE KAT_ID = %d;"
#define	_UPDATE_DLT	"UPDATE TDBADMIN.DIENST_TRAEGER \
	SET CODE = \'%s\', BEZ_ID = %d, KAT_ID = %d, H_DLT_ID = %d, HOST_ID = %d, \
	TYP_ID = %d, TEXTID = %d, STUFE = %d, STA_ID = %d, ANZ = %d \
	WHERE DLT_ID = %d AND H_DLT_ID = %d;"
#define	_UPDATE_DLAT	"UPDATE TDBADMIN.ANGEBOTS_TYP \
	SET BEZ_ID = %d, TEXTID = %d WHERE ART_ID = %d;"
#define	_UPDATE_AKTT	"UPDATE TDBADMIN.AKTIONS_TYP \
	SET BEZ_ID = %d, PROZ = \'%s\', TEXTID = %d WHERE A_TYP_ID = %d;"
#define _UPDATE_AKTP	"UPDATE TDBADMIN.AKTIONSPARA \
	SET TYP = %d, BEZ = \'%s\', \
	TEXTID = %d, MUSS = %d, FLAG = %d \
	WHERE A_TYP_ID = %d AND NR = %d;"
#define	_UPDATE_AKT	"UPDATE TDBADMIN.AKTIONEN \
	SET BEZ_ID = %d, TEXTID = %d, A_FLAG = %d, B_FLAG = %d, \
	M_FLAG = %d, A_TYP_ID = %d, B2_FLAG = %d, FILE_ID = %d WHERE AKT_ID = %d;"
#define	_UPDATE_DLA	"UPDATE TDBADMIN.DIENST_ANGEBOT \
	SET H_DLA_ID = %d, ORD	 = %d, DLT_ID  = %d, CODE =  \'%s\', BEZ_ID = %d, \
	 AKT_ID = %d, ORT = \'%s\', ART_ID = %d, DAU	 = %d, \
	 TEXTID = %d, VON	= %d, NACH = %d \
	WHERE DLA_ID = %d;"
#define _UPDATE_DLG "UPDATE TDBADMIN.DLG_PARTS \
	SET H_DL_ID = %d, DLA_ID = %d, CODE = \'%s\', BEZ_ID = %d, ORD = %d, A_ZEIT = %d, \
	 E_ZEIT = %d, RES_F = %d, KID = %d, KONTO = \'%s\', TEXTID = %d, \
	 SAI_ID = %d, RECHST = %d \
	WHERE DL_ID = %d;"
#define	_UPDATE_DTG	"UPDATE TDBADMIN.DIENSTLEISTUNG \
	SET CODE = \'%s\', BEZ_ID = %d, TEXTID	= %d, SAI_ID = %d, A_ZEIT = %d, AKT_ID = %d \
	WHERE DLG_ID = %d;"
#define _UPDATE_DLGDLG "UPDATE TDBADMIN.DLG_DLG \
	SET ORD = %d WHERE DLG_ID = %d AND DL_ID = %d;"
#define	_UPDATE_PRG	"UPDATE TDBADMIN.PROGRAMM \
	SET CODE = \'%s\', BEZ_ID = %d, TEXTID = %d, SAI_ID = %d \
	WHERE PRG_ID = %d;"
#define	_UPDATE_ARR	"UPDATE TDBADMIN.ARRANGEMENT \
	SET CODE = \'%s\', BEZ_ID = %d, A_DAT = %d, PRG_ID = %d, TEXTID = %d, SAI_ID = %d \
	WHERE ARR_ID = %d;"



#define _UPDATE_HKON "UPDATE TDBADMIN.HOST_KONT \
	SET BEZ_ID = %d, FROM_PERS = %d, KBST = %d, \
	 DLA_ID = %d, DL_ID = %d, DL_VONDAT = %d, DL_BISDAT = %d, \
	 TEXTID = %d, OPT_DAT = %d, SAI_ID = %d, REF = \'%s\', HISTORY = %d \
	WHERE HOSTKONT_ID = %d;"
#define _UPDATE_KON "UPDATE TDBADMIN.KONTINGENT \
	SET BEZ_ID = %d, HOSTKONT_ID = %d, KUNDEN_ID = %d, \
	 TEXTID = %d, OPT_DAT = %d, SAI_ID = %d, REF = \'%s\' \
	WHERE KONT_ID = %d;"
#define _UPDATE_KOND_BUSY "UPDATE TDBADMIN.KONT_DETAIL \
	SET BUSY = %d WHERE HOSTKONT_ID = %d AND KONT_ID = %d \
	AND KAT_ID = %d;"
#define _UPDATE_KOND_ANZ "UPDATE TDBADMIN.KONT_DETAIL \
	SET ANZ = %d, MINANZ = %d WHERE HOSTKONT_ID = %d AND KONT_ID = %d \
	AND KAT_ID = %d;"
#define _UPD_KOND_ADDONE "UPDATE TDBADMIN.KONT_DETAIL SET BUSY = BUSY + 1 \
	WHERE KONT_ID = %d AND HOSTKONT_ID = -1 AND KAT_ID = %d;"
#define _UPD_KOND_DELONE "UPDATE TDBADMIN.KONT_DETAIL SET BUSY = BUSY - 1 \
	WHERE KONT_ID = %d AND HOSTKONT_ID = -1 AND KAT_ID = %d;"




#define	_UPDATE_BCH	"UPDATE TDBADMIN.BUCHUNG \
	SET D_BID = %d, REF = \'%s\', ARR_ID = %d, KID = %d, SACH = %d, \
	 MPID = %d, ANW = %d, B_DAT = %d, M_DAT = %d, OPT_BST = %d, \
	 OPT_KID = %d, STA = %d, AST = %d, SAI_ID = %d, K_ID = %d, \
    HISTORY = %d, B_TEXT = %d \
	WHERE BID = %d;"
#define	_UPDATE_AKT_DET	"UPDATE TDBADMIN.AKT_DETAIL \
	SET Z_FLAG = %d, AKT_NR = %d, EXEC_DAT = %d, FILE_ID = %d \
	WHERE BID = %d AND PERS_ID = %d AND TEIL = %d AND AKT_ID = %d AND ORD = %d;"
#define _UPDATE_KAR "UPDATE TDBADMIN.KOSTEN_ART \
	SET BEZ_ID = %d, TEXTID = %d \
	WHERE KAR_ID = %d;"
#define	_UPDATE_KOM	"UPDATE TDBADMIN.KOMMISSION \
	SET BEZ_ID  = %d, SATZ_ART = %d, SATZ = %f, KOMM_TYP = %d, \
	KAR_ID = %d, DLTT_ID = %d, KAT_ID = %d, RKR_ID = %d, DLA_ID = %d, \
	DL_ID = %d, DL_VONDAT = %d, DL_BISDAT = %d, KONT_ID = %d, BID = %d, \
	SAI_ID = %d, HISTORY = %d, TEXTID = %d WHERE KOMM_ID = %d;"
#define _UPDATE_PRE "UPDATE TDBADMIN.PREIS \
	SET APR = %f, VPR = %f, EPR = %f, GLT = %d, WHR_ID = %d, KBST = %d, \
	KAR_ID = %d, DLTT_ID = %d, KAT_ID = %d, RKR_ID = %d, DLA_ID  = %d, DL_ID = %d, \
	DL_VONDAT = %d, DL_BISDAT = %d, KONT_ID = %d, STA_ID = %d, TEXTID = %d, \
	HISTORY = %d, SAI_ID = %d, \
   ARR_ID = %d, EXT_ID = %d, UNIT_TYP = %d, UNIT_VON = %d, UNIT_BIS = %d, DAU = %d, \
   DAU_VON = %d, DAU_BIS = %d WHERE PRE_ID = %d;"
#define _UPDATE_KAPA_BUSY "UPDATE TDBADMIN.KAPA \
	SET BUSY = %d WHERE KAT_ID = %d AND TDL_ID = %d;"
#define _UPDATE_KAPA_ANZ "UPDATE TDBADMIN.KAPA \
	SET ANZ = %d WHERE KAT_ID = %d AND TDL_ID = %d;"
#define _UPD_KAPA_ADDONE "UPDATE TDBADMIN.KAPA SET BUSY = BUSY + 1 \
	WHERE TDL_ID = %d AND KAT_ID = %d;"
#define _UPD_KAPA_DELONE "UPDATE TDBADMIN.KAPA SET BUSY = BUSY - 1 \
	WHERE TDL_ID = %d AND KAT_ID = %d;"




#define	_UPDATE_GRA	"UPDATE TDBADMIN.GRAPHIK \
	SET BEZ_ID = %d, TEXTID = %d, DLT_ID = %d \
	WHERE GRA_ID = %d;"
#define	_UPDATE_PCX	"UPDATE TDBADMIN.PCX_FILES \
	SET X = %d, Y = %d, FILENAME = \'%s\', \
	 BEZ_ID = %d, TYP = %d, TYPCODE = %d, FOLGE = %d \
	WHERE PCX_ID = %d;"



