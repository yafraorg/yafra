/**************************************************************/
/* Header:    SQL dynam. select statements                    */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
/*
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpsqlsel.h,v 1.4 2008-11-29 21:56:38 mwn Exp $
*/


/************************************************************
 * SPRACHEN
 *************************************************************/
#define _SEL_BEZ_SPR "SELECT * \
	FROM TDBADMIN.SPR_VIEW SPR \
	WHERE SPR.S_ID > -1 AND SPR.BEZSPRID=%d \
	ORDER BY SPR.BEZ;"

#define _SEL_BEZ_SPRDIALOG "SELECT * \
	FROM TDBADMIN.SPR_VIEW SPR \
	WHERE SPR.S_ID > -1 AND SPR.BEZSPRID=%d AND SPR.DIALOG = 1 \
	ORDER BY SPR.BEZ;"

#define	_SEL_BEZ_SPR_ID "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.SPRACHEN S \
	WHERE S.S_ID=%d AND B.TYP=%d AND B.S_ID=%d AND B.BEZ_ID = S.BEZ_ID \
	ORDER BY B.S_ID;"

#define _SEL_ALL_DIALOGSPR "SELECT * FROM TDBADMIN.SPRACHEN \
	WHERE DIALOG = %d;"

/* select from the bez the init SPRACHEN */
#define _SEL_INIT_SPR	"SELECT DISTINCT S.* \
	FROM TDBADMIN.SPRACHEN S, TDBADMIN.BEZEICHNUNG B \
	WHERE	B.BEZ = \'%s\' AND B.TYP = %d AND S.BEZ_ID = B.BEZ_ID;"


/************************************************************
 * BEZEICHNUNG / TEXTE
 *************************************************************/
#define _SEL_BEZ_BEZ_TYP "SELECT * FROM TDBADMIN.BEZEICHNUNG B \
	WHERE B.S_ID = %d AND B.TYP = %d AND B.BEZ_ID > 0 \
	ORDER BY B.BEZ;"

/* BEZEICHNUNG:  hole alle Bezeichnungstypen zu einer Sprache */
#define _SEL_BEZ_BEZ "SELECT * FROM TDBADMIN.BEZEICHNUNG B \
	WHERE B.BEZ_ID = %d AND B.S_ID = %d AND B.TYP > -1 \
	ORDER BY B.BEZ;"

#define _SELECT_BEZ "SELECT * FROM TDBADMIN.BEZEICHNUNG \
	WHERE BEZ_ID = %d AND S_ID = %d AND TYP = %d;"

#define _SEL_BEZ_FROMTYP "SELECT * FROM TDBADMIN.BEZEICHNUNG \
	WHERE BEZ = \'%s\' AND S_ID = %d AND TYP = %d;"

#define _SELECT_TXT "SELECT * FROM TDBADMIN.TEXTE \
	WHERE TEXTID = %d AND S_ID = %d AND TYP = %d ORDER BY TEXTNR;"



/************************************************************
 * DATUM Typ f�r Datumfelder
 *************************************************************/
#define _SEL_DS_DATUM "SELECT TDL.* \
	FROM TDBADMIN.DLG_PARTS TDL, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE TDL.H_DL_ID = -1 \
	 AND DLA.DLA_ID = TDL.DLA_ID \
	 AND DLA.DLT_ID = %d \
	 AND TDL.SAI_ID = %d \
	ORDER BY TDL.A_ZEIT;"

#define _SEL_D_DATUM "SELECT TDL.* \
	FROM TDBADMIN.DLG_PARTS TDL, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE TDL.H_DL_ID = -1 \
	 AND DLA.DLA_ID = TDL.DLA_ID \
	 AND DLA.DLT_ID = %d \
	ORDER BY TDL.A_ZEIT;"

#define _SEL_S_DATUM "SELECT * FROM TDBADMIN.DLG_PARTS \
	WHERE TDBADMIN.DLG_PARTS.H_DL_ID = -1 \
	AND TDBADMIN.DLG_PARTS.SAI_ID = %d \
	ORDER BY TDBADMIN.DLG_PARTS.A_ZEIT;"

#define _SEL_ALL_DATUM "SELECT * FROM TDBADMIN.DLG_PARTS DLG \
	WHERE DLG.H_DL_ID = -1 \
	ORDER BY DLG.A_ZEIT;"

#define _SEL_P_DATUM "SELECT * FROM TDBADMIN.PREIS ORDER BY GLT;"


/************************************************************
 * MSG / HELP / LABELS
 *************************************************************/
#define _SEL_MSG "SELECT DISTINCT MSG_ID FROM TDBADMIN.MSG \
	WHERE S_ID = %d AND MSG_TYP = %d ORDER BY MSG_ID;"

#define _SEL_MSGTXT "SELECT * FROM TDBADMIN.MSG \
	WHERE MSG_TYP = %d AND MSG_ID = %d AND S_ID = %d \
	ORDER BY TEXTNR;"

#define _SEL_ALL_MSG "SELECT * FROM TDBADMIN.MSG \
	WHERE S_ID = %d ORDER BY MSG_TYP, MSG_ID, TEXTNR;"

#define _SEL_ALL_MEMORYMSG "SELECT * FROM TDBADMIN.MSG \
	WHERE S_ID=%d AND (MSG_TYP = %d OR MSG_TYP = %d) \
	ORDER BY MSG_TYP, MSG_ID, TEXTNR;"

/************************************************************
 * STATUS_WERTE
 *************************************************************/

/* STATUS_WERT XY BEZ   nach STA_ID sortiert */
#define _SEL_BEZ_STA_ORDSTA "SELECT STA.STA_ID, B.S_ID, B.BEZ, B.TYP \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.STATUS_WERTE STA \
	WHERE B.BEZ_ID = STA.BEZ_ID AND B.S_ID=%d  \
	AND B.TYP=%d AND STA.TYP=%d AND STA.STA_ID > -1 \
	ORDER BY STA.STA_ID;"

/* STATUS_WERTE XY BEZ   nach BEZ sortiert */
#define _SEL_BEZ_STA "SELECT STA.STA_ID, B.S_ID, B.BEZ, B.TYP \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.STATUS_WERTE STA \
	WHERE B.BEZ_ID=STA.BEZ_ID AND B.S_ID=%d  \
	AND B.TYP=%d AND STA.TYP=%d AND STA.STA_ID > -1 \
	ORDER BY B.BEZ;"

/* STATUS_WERTE BEZ   alle Statuswert-Typen zur Uebersicht */
#define _SEL_BEZ_STA_ALL "SELECT * FROM TDBADMIN.BEZEICHNUNG B \
	WHERE B.BEZ_ID = %d AND B.S_ID = %d \
	AND B.TYP > 1100 AND B.TYP <= 1128 \
	ORDER BY B.BEZ;"

/* STATUS_WERTE alle Statuswert-TYPEN die mutiert werden d�rfen */
#define	_SEL_BEZ_STA_NAM	"SELECT * FROM TDBADMIN.BEZEICHNUNG B \
	WHERE B.BEZ_ID = 0 AND B.S_ID = %d \
	AND (B.TYP = 1101 OR B.TYP = 1102 OR B.TYP = 1108 OR B.TYP = 1112 \
    OR B.TYP = 1116 OR B.TYP=1123 OR B.TYP=1127 OR B.TYP=1128) \
	ORDER BY B.BEZ;"

/* STATUS_WERTE alle Statuswerte eines Typs */
#define _SEL_BEZ_ONE_TYP "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.STATUS_WERTE S \
	WHERE B.BEZ_ID = S.BEZ_ID \
	AND B.TYP = S.TYP AND B.S_ID = %d AND B.TYP = %d \
	ORDER BY B.BEZ;"

/* STATUS_WERTE alle Statuswerte die mutiert werden duerfen */
#define	_SEL_BEZ_STA_SEL	"SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.STATUS_WERTE S \
	WHERE B.BEZ_ID = S.BEZ_ID AND B.TYP = S.TYP \
	AND B.S_ID = %d AND (B.TYP = 1101 OR B.TYP = 1102 \
	OR B.TYP = 1108 OR B.TYP = 1112 OR B.TYP=1116 OR B.TYP=1123 OR B.TYP=1127 OR B.TYP=1128) \
	ORDER BY B.BEZ;"

/* alle GA fuer KATEGORIE holen */
#define _SEL_BEZ_STA_COL "SELECT * FROM TDBADMIN.STATUS_WERTE WHERE TYP=1102;"

/* hole Kommissionssaetze */
#define _SEL_BEZ_ALL_SATZ "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B \
	WHERE B.S_ID = %d \
	AND (B.TYP=1103 OR B.TYP=1104 OR B.TYP=1110 OR B.TYP=1111 ) \
	ORDER BY B.BEZ;"

/* hole Kommissionssaetze pro Kommission */
#define _SEL_BEZ_SATZ_KOM "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.STATUS_WERTE S, TDBADMIN.KOMM_DETAIL KD \
	WHERE B.S_ID = %d AND KD.KOMM_ID = %d \
	AND S.TYP = KD.TYP AND S.STA_ID = KD.STA_ID \
	AND B.TYP = S.TYP AND B.BEZ_ID = S.BEZ_ID \
	ORDER BY B.BEZ;"

/* hole Kommissionssaetze pro Satztyp */
#define	_SEL_BEZ_KOM_STA	"SELECT BEZ.* \
	FROM TDBADMIN.BEZEICHNUNG BEZ, TDBADMIN.BEZEICHNUNG TYPBEZ, TDBADMIN.STATUS_WERTE STA \
	WHERE TYPBEZ.BEZ_ID = 0 \
	AND TYPBEZ.S_ID = %d AND TYPBEZ.BEZ = \'%s\' \
	AND BEZ.TYP = TYPBEZ.TYP AND STA.TYP = TYPBEZ.TYP \
	AND BEZ.S_ID = %d \
	AND BEZ.BEZ_ID = STA.BEZ_ID;"


/************************************************************
 * MP_PROFIL
 *************************************************************/

/* MP_PROFIL: get a user profile */
#define _SEL_PROF_USER "SELECT * FROM TDBADMIN.MP_PROFIL PROF \
	WHERE PROF.MPUSER = \'%s\';"


/************************************************************
 * SAISON
 *************************************************************/
/* SAISON BEZ  Auswahl aller Saison */
#define	_SEL_BEZ_SAI "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.SAISON SAI \
	WHERE B.BEZ_ID=SAI.BEZ_ID AND SAI.SAI_ID > -1 \
	AND B.S_ID=%d AND B.TYP=%d \
	ORDER BY B.BEZ;"

/* SAISON BEZ Auswahl nach Programm */
#define	_SEL_BEZ_SAI_PRG	"SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.SAISON S, TDBADMIN.PROGRAMM P \
	WHERE B.BEZ_ID = S.BEZ_ID \
	AND P.SAI_ID = S.SAI_ID AND B.S_ID = %d AND P.SAI_ID = %d \
	AND B.TYP = %d ORDER BY B.BEZ;"






/************************************************************
 * GEOGRAFIE: LAND/ORT/WAEHRUNG
 *************************************************************/
/* LAND */
#define _SEL_BEZ_LAND "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.LAND L \
	WHERE B.S_ID = %d AND B.TYP = %d \
	AND L.LAND_ID > -1 AND B.BEZ_ID = L.BEZ_ID \
	ORDER BY B.BEZ;"

/* ORT */
#define _SEL_BEZ_ORT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.ORT O \
	WHERE B.S_ID = %d AND B.TYP = %d \
	AND O.ORT_ID > -1 AND B.BEZ_ID = O.BEZ_ID \
	ORDER BY B.BEZ;"

/* WAEHRUNG */
#define _SEL_BEZ_WHR "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.WAEHRUNG W \
	WHERE B.S_ID = %d AND B.TYP = %d \
	AND W.WHR_ID > -1 AND B.BEZ_ID = W.BEZ_ID \
	ORDER BY B.BEZ;"








/************************************************************
 * PERSONEN
 *************************************************************/

/* abstraction */
#define _ORDER_DLN_NAME "DLN.NAME, DLN.VOR"
#define _ORDER_DLN_ID "DLN.DLN_ID"

/* DLN_VIEW  Auswahl aller Reisender */
#define _SEL_DLNVIEW "SELECT * FROM TDBADMIN.DLN_VIEW DLN WHERE DLN.DLN_ID > -1 \
	ORDER BY %s;"

/* DLN_VIEW  Auswahl nach Reisendertyp */
#define _SEL_DLNVIEW_DLNT "SELECT * FROM TDBADMIN.DLN_VIEW DLN \
	WHERE DLN.RKR_ID = %d ORDER BY %s;"

/* DLN_VIEW  Auswahl nach Buchung */
#define _SEL_DLNVIEW_BID "SELECT DLN.* \
	FROM TDBADMIN.DLN_VIEW DLN, TDBADMIN.BCH_DLN BD \
	WHERE BD.BID = %d AND DLN.DLN_ID = BD.DLN_ID \
	ORDER BY %s;"

/* REISENDER_TYP  Auswahl aller Reisendertypen */
#define _SEL_BEZ_REIT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.REISENDER_TYP RKR \
	WHERE B.BEZ_ID=RKR.BEZ_ID AND RKR.RKR_ID > -1 \
	AND B.S_ID=%d AND B.TYP=%d \
	ORDER BY B.BEZ;"

/* hole 1 DLN zu einer Buchung BMRESinput() */
#define _SEL_ONEDLN "SELECT * FROM TDBADMIN.BCH_DLN \
	WHERE BID = %d AND DLN_ID = %d;"

/* hole alle DLNs zu einer Buchung BMRESinput() */
#define _SEL_DLN_BCH "SELECT * FROM TDBADMIN.BCH_DLN \
	WHERE BID = %d;"



/* KUN_VIEW  hole alle Kunden */
#define _SEL_KUNVIEW "SELECT * FROM TDBADMIN.PERSONEN WHERE PERS_ID > -1 \
	AND PERS_TYP = %d ORDER BY NAME, ORT;"

#define _SEL_KUNADRVIEW "SELECT * FROM TDBADMIN.MPV_KUNADR WHERE PERS_ID > -1 \
	ORDER BY NAME, PLZ, ORT;"

/* KUN_VIEW  hole alle Kunden nach Typen */
#define _SEL_KUNVIEW_TYP "SELECT * FROM TDBADMIN.KUNDEN_VIEW WHERE KUN_ID > -1 \
	AND K_TYP_ID = %d ORDER BY NAME, ORT;"

/* KUNDEN_TYP  Auswahl aller Kundentypen */
#define _SEL_BEZ_KUNT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KUNDEN_TYP KT \
	WHERE B.BEZ_ID=KT.BEZ_ID AND KT.K_TYP_ID > -1 \
	AND B.S_ID=%d AND B.TYP=%d \
	ORDER BY B.BEZ;"



/* KOLLEKTIV  hole alle Kollektivs */
#define _SEL_BEZ_KOL "SELECT K.* \
	FROM TDBADMIN.KOLLEKTIV K \
	WHERE K.K_ID > -1 \
	ORDER BY K.NAME;"

/* KOLLEKTIV  hole alle Kollektivs eines Typs */
#define _SEL_BEZ_KOL_TYP "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KOLLEKTIV K \
	WHERE B.BEZ_ID = K.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d AND K.K_TYP_ID = %d \
	ORDER BY B.BEZ;"

/* KOLLEKTIV_TYP  hole alle Kollektivtypen */
#define _SEL_BEZ_KOLT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KOLLEKTIV_TYP KOLT \
	WHERE B.BEZ_ID=KOLT.BEZ_ID AND KOLT.K_TYP_ID > -1 \
	AND B.S_ID=%d AND B.TYP=%d \
	ORDER BY B.BEZ;"







/************************************************************
 * section:  DLT
 *************************************************************/

/* DLT_VIEW: Hole alle */
#define _SEL_DLTVIEW "SELECT * FROM TDBADMIN.DLT_VIEW \
	WHERE S_ID = %d AND DLT_ID > -1 ORDER BY BEZ;"

/* DLT_VIEW: Hole alle nach Kategorie */
#define _SEL_DLTVIEW_KAT "SELECT * FROM TDBADMIN.DLT_VIEW DV \
	WHERE DV.S_ID = %d DV.KAT_ID = %d ORDER BY DV.BEZ;"

/* DLT_VIEW: Hole alle DLTs eines HOST-DLT's */
#define	_SEL_DLTVIEW_HOST	"SELECT * FROM TDBADMIN.DLT_VIEW DV \
	WHERE DV.S_ID = %d AND DV.HOST_ID = %d \
	ORDER BY DV.STUFE, DV.BEZ;"

/* DLT_VIEW:  Hole alle Host DLTs mit Bez */
#define	_SEL_DLTVIEW_HOSTS "SELECT * FROM TDBADMIN.DLT_VIEW D	\
	WHERE D.S_ID = %d AND D.STUFE = 1 \
	ORDER BY D.BEZ;"

/* DLT_VIEW: Hole alle Host DLTs mit Bez nach einem Typ */
#define	_SEL_DLTVIEW_HOSTS_DLTT "SELECT * FROM TDBADMIN.DLT_VIEW D \
	WHERE D.S_ID = %d AND D.STUFE = 1 AND D.TYP_ID = %d \
	ORDER BY D.BEZ;"

/* DLT_VIEW: Hole alle Host DLTs mit Bez nach einer DL */
#define	_SEL_DLTVIEW_HOSTS_DL "SELECT DISTINCT DLT.* \
	FROM TDBADMIN.DLT_VIEW DLT, TDBADMIN.DIENST_ANGEBOT DLA, TDBADMIN.DLG_PARTS DLG, \
	 TDBADMIN.DLG_DLG DLDLG \
	WHERE DLT.S_ID = %d AND DLT.STUFE = 1 \
	 AND DLA.DLT_ID = DLT.DLT_ID AND DLG.DLA_ID = DLA.DLA_ID \
	 AND DLDLG.DL_ID = DLG.DL_ID AND DLDLG.DLG_ID = %d \
	ORDER BY DLT.BEZ;"

/* TRAEGER_VIEW: Hole alle */
#define _SEL_TRAEGERVIEW "SELECT * FROM TDBADMIN.TRAEGER_VIEW \
	WHERE SPR = %d AND ID > -1 ORDER BY BEZ;"

/* TRAEGER_VIEW: Hole alle nach HOST */
#define	_SEL_TRAEGERVIEW_HOSTDLT	"SELECT * FROM TDBADMIN.TRAEGER_VIEW \
	WHERE SPR = %d AND HOST = %d \
	ORDER BY BEZ;"

/* TRAEGER_VIEW: Hole alle nach HOST und TYP eing. */
#define	_SEL_TRAEGERVIEW_HOSTDLT_DLTT "SELECT * FROM TDBADMIN.TRAEGER_VIEW \
	WHERE SPR = %d AND HOST = %d AND TYP = %d \
	ORDER BY BEZ;"

/* TRAEGER_VIEW: Hole alle nach HDLT */
#define	_SEL_TRAEGERVIEW_HDLT "SELECT * FROM TDBADMIN.TRAEGER_VIEW \
	WHERE SPR = %d AND HID = %d \
	ORDER BY BEZ;"

/* TRAEGER_VIEW: Hole alle nach Typ */
#define _SEL_TRAEGERVIEW_DLTT "SELECT * FROM TDBADMIN.TRAEGER_VIEW \
	WHERE SPR = %d AND TYP = %d ORDER BY BEZ;"

/* TODO fix D.H_BEZ_ID -> not valid anymore - TRAEGER_VIEW: Hole alle nach Kategorie */
#define _SEL_TRAEGERVIEW_KAT "SELECT BEZ_A.S_ID, D.TYP_ID, D.DLT_ID, \
	BEZ_A.BEZ, D.H_DLT_ID, BEZ_B.BEZ, D.HOST_ID \
	FROM TDBADMIN.BEZEICHNUNG BEZ_B, TDBADMIN.BEZEICHNUNG BEZ_A, TDBADMIN.DIENST_TRAEGER D \
	WHERE BEZ_A.S_ID = %d AND BEZ_B.S_ID = %d AND BEZ_A.TYP = %d \
	AND BEZ_B.TYP = %d AND D.KAT_ID = %d AND BEZ_A.BEZ_ID = D.BEZ_ID \
	AND BEZ_B.BEZ_ID = D.H_BEZ_ID ORDER BY BEZ_A.BEZ;"

/* TRAEGER_VIEW: Hole alle nach einem HOST-DLT einer DL */
#define _SEL_TRAEGERVIEW_DL "SELECT DISTINCT DLT.* \
	FROM TDBADMIN.TRAEGER_VIEW DLT, TDBADMIN.DIENST_ANGEBOT DLA, TDBADMIN.DLG_PARTS DLG, \
	 TDBADMIN.DLG_DLG DLDLG \
	WHERE DLT.SPR = %d \
	 AND DLT.HOST = DLA.DLT_ID AND DLG.DLA_ID = DLA.DLA_ID \
	 AND DLDLG.DL_ID = DLG.DL_ID AND DLDLG.DLG_ID = %d \
	ORDER BY DLT.BEZ;"

/* TRAEGER_VIEW: Hole alle nach einem HOST-DLT einer DLA */
#define _SEL_TRAEGERVIEW_DLA "SELECT DISTINCT DLT.* \
	FROM TDBADMIN.TRAEGER_VIEW DLT, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE DLT.SPR = %d AND DLT.HOST = DLA.DLT_ID AND DLA.DLA_ID = %d \
	ORDER BY DLT.BEZ;"

/* TRAEGER_VIEW: Hole DLTs eines bestehenden KONT_DETAIL nach HKON */
#define _SEL_TRAEGERVIEW_KOND_HKON "SELECT DLT.* \
	FROM TDBADMIN.TRAEGER_VIEW DLT, TDBADMIN.KONT_DETAIL KD \
	WHERE KD.HOSTKONT_ID = %d AND KD.DLT_ID > 0 AND DLT.ID = KD.DLT_ID \
	AND DLT.SPR = %d ORDER BY DLT.BEZ;"

/* TRAEGER_VIEW: Hole DLTs eines bestehenden KONT_DETAIL nach KON */
#define _SEL_TRAEGERVIEW_KOND_KON "SELECT DLT.* \
	FROM TDBADMIN.TRAEGER_VIEW DLT, TDBADMIN.KONT_DETAIL KD \
	WHERE KD.KONT_ID = %d AND KD.DLT_ID > 0 AND DLT.ID = KD.DLT_ID \
	AND DLT.SPR = %d ORDER BY DLT.BEZ;"


/* DIENST_TRAEGER: hole alle DLT's zu einem HOST (intern) */
#define  _SEL_DLT_ALLFROMHOST "SELECT * FROM TDBADMIN.DIENST_TRAEGER D \
	WHERE D.HOST_ID=%d ORDER BY D.STUFE;"

/* DIENST_TRAEGER: hole alle KAT zu einem HOST (intern) */
#define _SEL_DLT_HOSTDLT_KAT "SELECT * FROM TDBADMIN.DIENST_TRAEGER DLT \
	WHERE DLT.HOST_ID = %d AND DLT.KAT_ID = %d;"

/* DIENST_TRAEGER: count all elements of a KAT from a HOST */
#define _SEL_COUNTDLT "SELECT COUNT(DLT_ID) FROM TDBADMIN.DIENST_TRAEGER DLT \
	WHERE DLT.KAT_ID = %d AND HOST_ID = %d;"


/************************************************************
 * section:  DLTT
 *************************************************************/

// TODO HARDCODED typs

#define _SEL_BEZ_TYP_KON "SELECT DISTINCT BEZ_A.S_ID, DLTT_A.TYP_ID, BEZ_A.BEZ,	\
	DLTT_A.H_TYP_ID, BEZ_B.BEZ	\
	FROM	TDBADMIN.BEZEICHNUNG BEZ_B, TDBADMIN.BEZEICHNUNG BEZ_A, TDBADMIN.TRAEGER_TYP DLTT_B, \
   	TDBADMIN.TRAEGER_TYP DLTT_A, TDBADMIN.KONT_DETAIL	\
	WHERE 	TDBADMIN.KONT_DETAIL.KONT_ID = %d \
   AND   DLTT_A.TYP_ID = TDBADMIN.KONT_DETAIL.TYP_ID \
	AND   BEZ_A.TYP = 15	\
	AND   BEZ_B.TYP = 15	\
	AND   DLTT_A.H_TYP_ID = DLTT_B.TYP_Id	\
	AND   DLTT_A.BEZ_ID = BEZ_A.BEZ_Id	\
	AND   DLTT_B.BEZ_ID = BEZ_B.BEZ_Id	\
	AND   DLTT_A.TYP_ID > -1 \
	AND   BEZ_A.S_ID = %d \
	AND	BEZ_B.S_ID = %d \
	ORDER BY BEZ_A.BEZ;"

#define	_SEL_BEZ_TTYP	"SELECT   BEZ_A.S_ID, DLTT_A.TYP_ID, BEZ_A.BEZ,	\
	DLTT_A.H_TYP_ID, BEZ_B.BEZ	\
	FROM TDBADMIN.BEZEICHNUNG BEZ_B, TDBADMIN.BEZEICHNUNG BEZ_A, TDBADMIN.TRAEGER_TYP DLTT_B, TDBADMIN.TRAEGER_TYP DLTT_A	\
	WHERE BEZ_A.TYP = 15	\
	AND   BEZ_B.TYP = 15	\
	AND   DLTT_A.H_TYP_ID = DLTT_B.TYP_Id	\
	AND   DLTT_A.BEZ_ID = BEZ_A.BEZ_Id	\
	AND   DLTT_B.BEZ_ID = BEZ_B.BEZ_Id	\
	AND   DLTT_A.TYP_ID > -1 \
	AND   BEZ_A.S_ID = %d \
	AND	BEZ_B.S_ID = %d \
	ORDER BY BEZ_A.BEZ;"

#define	_SEL_BEZ_TTYP_NUM	"SELECT   BEZ_A.S_ID, DLTT_A.TYP_ID, BEZ_A.BEZ,	\
				DLTT_A.H_TYP_ID, BEZ_B.BEZ	\
				FROM TDBADMIN.BEZEICHNUNG BEZ_B, TDBADMIN.BEZEICHNUNG BEZ_A, TDBADMIN.TRAEGER_TYP DLTT_B, TDBADMIN.TRAEGER_TYP DLTT_A	\
				WHERE DLTT_A.TYP_ID IN (%s)	\
					AND	BEZ_A.TYP = 15	\
					AND   BEZ_B.TYP = 15	\
					AND   DLTT_A.H_TYP_ID = DLTT_B.TYP_Id	\
					AND   DLTT_A.BEZ_ID = BEZ_A.BEZ_Id	\
					AND   DLTT_B.BEZ_ID = BEZ_B.BEZ_Id	\
					AND   BEZ_A.S_ID = %d \
					AND	BEZ_B.S_ID = %d;"

#define	_SEL_BEZ_TTYP_DLT	"SELECT DISTINCT BEZ_A.S_ID, DLTT_A.TYP_ID, BEZ_A.BEZ,	\
				DLTT_A.H_TYP_ID, BEZ_B.BEZ	\
				FROM TDBADMIN.BEZEICHNUNG BEZ_B, TDBADMIN.BEZEICHNUNG BEZ_A, TDBADMIN.TRAEGER_TYP DLTT_B,	\
					TDBADMIN.TRAEGER_TYP DLTT_A, TDBADMIN.DIENST_TRAEGER DLT_A	\
				WHERE		DLT_A.HOST_ID = %d \
					AND	DLT_A.TYP_ID = DLTT_A.TYP_ID	\
					AND	BEZ_A.TYP = 15	\
					AND   BEZ_B.TYP = 15	\
					AND   DLTT_A.H_TYP_ID = DLTT_B.TYP_Id	\
					AND   DLTT_A.BEZ_ID = BEZ_A.BEZ_Id	\
					AND   DLTT_B.BEZ_ID = BEZ_B.BEZ_Id	\
					AND   BEZ_A.S_ID = %d \
					AND	BEZ_B.S_ID = %d;"

#define _SEL_BEZ_DLTT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.TRAEGER_TYP D \
	WHERE B.BEZ_ID = D.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d \
	ORDER BY B.BEZ;"


/************************************************************
 * KATEGORIE
 *************************************************************/
/* KATEGORIE hole alle Kategorien */
#define _SEL_BEZ_KAT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KATEGORIE K \
	WHERE B.BEZ_ID=K.BEZ_ID AND K.KAT_ID > -1 \
	AND B.S_ID=%d AND B.TYP=%d ORDER BY B.BEZ;"

/* KATEGORIE hole alle Kategorien pro DLT */
#define _SEL_BEZ_KAT_DLT "SELECT DISTINCT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KATEGORIE K, TDBADMIN.DIENST_TRAEGER D \
	WHERE D.HOST_ID = %d AND K.KAT_ID > 0 AND K.KAT_ID = D.KAT_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ_ID = K.BEZ_ID \
	ORDER BY B.BEZ;"

/* KATEGORIE hole alle Kategorien pro DLT-Typ */
#define	_SEL_BEZ_KAT_TYP "SELECT DISTINCT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KATEGORIE K \
	WHERE K.TYP_ID = %d AND B.S_ID=%d AND B.TYP=%d \
	AND B.BEZ_ID = K.BEZ_ID \
	ORDER BY B.BEZ;"

/* KATEGORIE hole alle Kategorien eines bestehenden KONT_DETAIL nach HKON */
#define _SEL_BEZ_KAT_KOND_HKON "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KATEGORIE K, TDBADMIN.KONT_DETAIL KD \
	WHERE KD.HOSTKONT_ID = %d AND KD.KAT_ID > 0 AND K.KAT_ID = KD.KAT_ID	\
	AND B.BEZ_ID = K.BEZ_ID AND B.S_ID=%d AND B.TYP=%d \
	ORDER BY B.BEZ;"

/* KATEGORIE hole alle Kategorien eines bestehenden KONT_DETAIL nach KON */
#define _SEL_BEZ_KAT_KOND_KON "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KATEGORIE K, TDBADMIN.KONT_DETAIL KD \
	WHERE KD.KONT_ID = %d AND KD.KAT_ID > 0 AND K.KAT_ID = KD.KAT_ID	\
	AND B.BEZ_ID = K.BEZ_ID AND B.S_ID=%d AND B.TYP=%d \
	ORDER BY B.BEZ;"

/* KAT_VIEW hole alle Kategorien nach einer Sprache von der KAT_VIEW */
#define _SEL_KATVIEW_DLT "SELECT DISTINCT KV.* \
	FROM TDBADMIN.KAT_VIEW KV, TDBADMIN.DIENST_TRAEGER D \
	WHERE D.HOST_ID = %d AND KV.S_ID = %d \
	AND KV.KAT_ID > 0 AND KV.KAT_ID = D.KAT_ID \
	ORDER BY KV.BEZ;"

/* KAT_VIEW hole alle Kategorien nach einer TDL via KAPA table */
#define _SEL_KATVIEW_KAPA "SELECT DISTINCT KV.* \
	FROM TDBADMIN.KAT_VIEW KV, TDBADMIN.KAPA K \
	WHERE K.TDL_ID = %d AND KV.S_ID = %d AND KV.KAT_ID > 0 \
	AND KV.KAT_ID = K.KAT_ID ORDER BY KV.KAT_ID;"

/* KATEGORIE  hole alle Kategorien eines DLT */
#define _SEL_KAT_DLT "SELECT DISTINCT KAT.* \
	FROM TDBADMIN.KATEGORIE KAT, TDBADMIN.DIENST_TRAEGER D \
	WHERE D.HOST_ID = %d AND KAT.KAT_ID > 0 AND KAT.KAT_ID = D.KAT_ID;"

/******************************************************************
 * AKTIONEN / AKTIONSGRP / AKTIONS_TYP / AKTIONSPARA / AKT_DETAIL
 ******************************************************************/
/* alle Aktionen mit ihrer Bezeichnung */
#define _SEL_BEZ_AKT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.AKTIONEN A \
	WHERE B.S_ID=%d AND B.TYP=%d AND A.AKT_ID > -1 \
	AND B.BEZ_ID=A.BEZ_ID ORDER BY B.BEZ;"

/* alle Oberbegriffe (parents) mit Bezeichnung */
#define _SEL_BEZ_PARENTAKT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.AKTIONEN A \
	WHERE B.S_ID = %d AND B.TYP = %d \
	AND A.A_TYP_ID = -1 AND A.AKT_ID > -1 \
	AND B.BEZ_ID = A.BEZ_ID	ORDER BY B.BEZ;"

/* alle ausf�hrbaren Aktionen (mit einem Aktionstyp, f�r Output) */
#define _SEL_BEZ_OUTAKT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.AKTIONEN A \
	WHERE B.S_ID = %d AND B.TYP = %d \
	AND A.A_TYP_ID > -1 AND A.AKT_ID > -1 AND A.A_FLAG <> %d \
	AND B.BEZ_ID = A.BEZ_ID	ORDER BY B.BEZ;"

/* alle Aktionsgruppen Oberbegriffe */
#define _SEL_BEZ_HAKT "SELECT DISTINCT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.AKTIONEN A, TDBADMIN.AKTIONSGRP AG \
	WHERE AG.PARENTAKT > -1 AND A.AKT_ID = AG.PARENTAKT \
	AND B.BEZ_ID = A.BEZ_ID AND B.S_ID = %d AND B.TYP = %d \
	ORDER BY B.BEZ;"

/* alle Aktionsgruppen - Kind-Begriffe */
#define _SEL_BEZ_AKTG_CHILDAKT "SELECT B.BEZ_ID, B.S_ID, B.BEZ, AG.ORD \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.AKTIONEN A, TDBADMIN.AKTIONSGRP AG \
	WHERE AG.PARENTAKT = %d AND A.AKT_ID = AG.CHILDAKT \
	AND B.BEZ_ID = A.BEZ_ID AND B.S_ID = %d AND B.TYP = %d \
	ORDER BY AG.ORD;"

/* alle Kinder einer Gruppenaktion */
#define _SEL_AKTG_PARENT "SELECT * FROM TDBADMIN.AKTIONSGRP AG \
	WHERE AG.PARENTAKT = %d ORDER BY AG.ORD;"

#define _SEL_BEZ_AKTV   "SELECT * FROM TDBADMIN.AKT_VIEW \
	WHERE SPR=%d AND ID > -1 ORDER BY BEZ, UBEZ;"
#define _SEL_BEZ_AKTV_BEZ   "SELECT * FROM TDBADMIN.AKT_VIEW \
	WHERE SPR=%d AND ID > -1 ORDER BY BEZ, UBEZ;"
#define _SEL_ONE_AKT_NR "SELECT * FROM TDBADMIN.AKT_DETAIL \
	WHERE A_TYP_ID = %d AND BID = %d AND DL_ID = %d;"

#define	_SEL_BEZ_AKTT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.AKTIONS_TYP AT \
	WHERE B.S_ID=%d AND B.TYP=%d AND AT.A_TYP_ID > -1 \
	AND B.BEZ_ID=AT.BEZ_ID ORDER BY B.BEZ;"

/* hole alle Parameter zu einem Aktionstyp */
#define _SEL_PARA_AKTT "SELECT AP.* FROM TDBADMIN.AKTIONSPARA AP \
	WHERE AP.A_TYP_ID = %d ORDER BY AP.NR;"

/* hole alle Aktionendetails zu einer Buchung */
#define	_SEL_AKTD_BCH "SELECT * FROM TDBADMIN.AKT_DETAIL \
	WHERE BID = %d ORDER BY PERS_ID, TEIL, ORD;"

/* hole alle Aktionendetails zu einer Buchung und einer DL */
#define	_SEL_AKTD_BCH_DL "SELECT * FROM TDBADMIN.AKT_DETAIL \
	WHERE BID = %d AND DLG_ID = %d ORDER BY PERS_ID, ORD;"

/* hole alle Aktionendetails zu einer Buchung und einem DLN */
#define	_SEL_AKTDET_BCH_UID_DL "SELECT * FROM TDBADMIN.AKT_DETAIL AD \
	WHERE AD.BID = %d AND AD.PERS_ID = %d AND AD.DLG_ID = %d \
	ORDER BY AD.ORD;"


/************************************************************
 * DIENSTLEISTUNGSANGEBOT / ANGEBOTSTYP
 *************************************************************/

/* abstraction */
#define _DLA_ONLYHOSTS "DLA.H_DLA_ID = -1 AND"
#define _DLA_ALL " "

/* DLA_VIEW  Auswahl aller Angebote */
#define _SEL_DLAVIEW "SELECT * FROM TDBADMIN.DLA_VIEW DLA \
	WHERE %s DLA.S_ID = %d AND DLA.DLA_ID > -1 ORDER BY DLA.BEZ;"

/* DLA_VIEW  Auswahl nach DL */
#define _SEL_DLAVIEW_DL "SELECT DLA.* \
	FROM TDBADMIN.DLA_VIEW DLA, TDBADMIN.DLG_PARTS TDL, TDBADMIN.DLG_DLG DD \
	WHERE %s DD.DLG_ID = %d AND TDL.DL_ID = DD.DL_ID \
	AND DLA.DLA_ID = TDL.DLA_ID AND DLA.S_ID = %d ORDER BY DLA.BEZ;"

/* DLA_VIEW  Auswahl nach Traeger */
#define _SEL_DLAVIEW_DLT "SELECT * FROM TDBADMIN.DLA_VIEW DLA \
	WHERE %s DLA.S_ID = %d AND DLA.DLT_ID = %d AND DLA.DLA_ID > -1 \
	ORDER BY DLA.BEZ;"

/* DLA_VIEW  Auswahl nach Angebotstyp */
#define _SEL_DLAVIEW_DLAT "SELECT * FROM TDBADMIN.DLA_VIEW DLA \
	WHERE %s DLA.S_ID = %d AND DLA.ART_ID = %d AND DLA.DLA_ID > -1 \
	ORDER BY DLA.BEZ;"

/* DLA_VIEW  Auswahl fuer DLAinfo() */
#define _SEL_BEZ_DLA_ID "SELECT * FROM TDBADMIN.DLA_VIEW \
	WHERE ( DLA_ID = %d OR H_DLA_ID=%d ) AND S_ID=%d \
	ORDER BY H_DLA_ID, ORD;"

/* DIENST_ANGEBOT alle Eintr�ge eines HOSTS */
#define _SEL_DLA_ALLFROMHOST "SELECT DLA.* \
	FROM TDBADMIN.DIENST_ANGEBOT DLA WHERE DLA.H_DLA_ID = %d;"

/* ANGEBOTS_TYP BEZ  alle Angebotstypen */
#define _SEL_BEZ_DLAT "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.ANGEBOTS_TYP AT \
	WHERE B.S_ID=%d AND B.TYP=%d AND AT.ART_ID > -1 \
	AND B.BEZ_ID=AT.BEZ_ID ORDER BY B.BEZ;"



/************************************************************
 * DLG_PARTS (DLG / DL_ID)  was macht Dienstleistungstr�ger
 *************************************************************/

/* abstraction */
#define _ORDER_DLPARTS_DAT "D.A_ZEIT, D.BEZ"
#define _ORDER_DLPARTS_BEZ "D.BEZ, D.A_ZEIT"
#define _DLGPARTS_ONLYHOSTS "D.H_DL_ID = -1 AND"
#define _DLGPARTS_ALL " "

/* DLG_VIEW  Auswahl aller Dienstleistungsteile */
#define _SEL_DLGVIEW "SELECT * FROM TDBADMIN.DLG_VIEW D \
	WHERE %s D.S_ID = %d AND D.DL_ID > -1 ORDER BY %s;"

/* DLG_VIEW  Auswahl nach Dienstleistung */
#define _SEL_DLGVIEW_DL "SELECT D.* \
	FROM TDBADMIN.DLG_VIEW D, TDBADMIN.DLG_DLG DD \
	WHERE DD.DLG_ID = %d AND D.DL_ID = DD.DL_ID AND D.S_ID = %d ORDER BY %s;"

/* DLG_VIEW  Auswahl nach Saison */
#define _SEL_DLGVIEW_SAI "SELECT * FROM TDBADMIN.DLG_VIEW D \
	WHERE %s D.S_ID = %d AND D.DL_ID > -1 AND D.SAI_ID = %d ORDER BY %s;"

/* DLG_VIEW  Auswahl nach Anfangs- und Endzeit */
#define _SEL_DLGVIEW_AE "SELECT * FROM TDBADMIN.DLG_VIEW D \
	WHERE %s D.S_ID = %d AND D.DL_ID > -1 \
	AND ((D.A_ZEIT >= %d AND D.E_ZEIT <= %d) OR D.A_ZEIT = -1) \
	ORDER BY %s;"

/* DLG_VIEW  Auswahl nach Anfangszeit */
#define _SEL_DLGVIEW_A "SELECT * FROM TDBADMIN.DLG_VIEW D \
	WHERE %s D.S_ID = %d AND D.DL_ID > -1 \
	AND (D.A_ZEIT >= %d OR D.A_ZEIT = -1) \
	ORDER BY %s;"

/* DLG_VIEW  Auswahl nach Endzeit */
#define _SEL_DLGVIEW_E "SELECT * FROM TDBADMIN.DLG_VIEW D \
	WHERE %s D.S_ID = %d AND D.DL_ID > -1 \
	AND D.E_ZEIT <= %d ORDER BY %s;"

/* DLG_VIEW  Auswahl nach Angebotstyp */
#define _SEL_DLGVIEW_DLAT "SELECT D.* \
	FROM TDBADMIN.DLG_VIEW D, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE %s D.S_ID = %d AND DLA.ART_ID = %d \
	AND D.DLA_ID = DLA.DLA_ID ORDER BY %s;"

/* DLG_VIEW  mit einer bestimmten AKTION */
#define _SEL_DLGVIEW_AKTDET "SELECT DISTINCT D.* \
	FROM TDBADMIN.DLG_VIEW D, TDBADMIN.AKT_DETAIL AD \
	WHERE AD.AKT_ID = %d AND D.DL_ID = AD.DL_ID \
	AND D.S_ID = %d AND D.DL_ID > -1 ORDER BY %s;"

/* DLG_VIEW  hole alle Teile fuer DLG_PART INFO */
#define	_SEL_BEZ_DLG_DLG	"SELECT * FROM TDBADMIN.DLG_VIEW D \
	WHERE (D.DL_ID = %d OR D.H_DL_ID = %d)	\
	AND D.S_ID = %d \
	ORDER BY D.H_DL_ID, D.ORD;"


/* DLG_PART Auswahl aller dlparts nach Angebot */
#define _SEL_DLG_DLA "SELECT DLG.* FROM TDBADMIN.DLG_PARTS DLG \
	WHERE DLG.DLA_ID = %d ORDER BY DLG.A_ZEIT;"

/* DLG_PART alle HOST Eintr�ge einer DIENSTLEISTUNG */
#define _SEL_HDLG_DL "SELECT DISTINCT HTDL.* \
	FROM TDBADMIN.DLG_PARTS HTDL, TDBADMIN.DLG_PARTS TDL, TDBADMIN.DLG_DLG DD \
	WHERE DD.DLG_ID = %d AND TDL.DL_ID = DD.DL_ID AND \
	((TDL.H_DL_ID > 0 AND HTDL.DL_ID = TDL.H_DL_ID) OR \
	 (TDL.H_DL_ID < 1 AND HTDL.DL_ID = TDL.DL_ID));"

/* DLG_PART alle Eintr�ge eines HOSTS */
#define _SEL_DLG_ALLFROMHOST "SELECT * \
	FROM TDBADMIN.DLG_PARTS WHERE H_DL_ID = %d;"

/* DLG_PART alle HOST Eintr�ge */
#define _SEL_TDL_HOST "SELECT TDL.* FROM TDBADMIN.DLG_PARTS TDL \
	WHERE TDL.H_DL_ID = -1 AND TDL.DL_ID > 0;"

/* DLG_PART alle HOST Eintr�ge nach DLA */
#define _SEL_TDL_HOST_DLA "SELECT TDL.* FROM TDBADMIN.DLG_PARTS TDL \
	WHERE TDL.H_DL_ID = -1 AND TDL.DLA_ID = %d AND TDL.DL_ID > 0;"

/* DLG_PART alle Eintraege auf einer DLA */
#define _SEL_TDL_DLA "SELECT TDL.* \
	FROM TDBADMIN.DLG_PARTS TDL \
	WHERE TDL.DLA_ID = %d ORDER BY TDL.A_ZEIT;"

/************************************************************
 * DIENSTLEISTUNG (DTG / DLG_ID) was macht Reisender
 *************************************************************/

/* abstraction */
#define _ORDER_DL_DAT "DL.A_ZEIT, DL.BEZ"
#define _ORDER_DL_BEZ "DL.BEZ, DL.A_ZEIT"


/* DTG_VIEW  Auswahl aller Dienstleistungen sortiert nach Anfangsdatum */
#define _SEL_DTGVIEW "SELECT * FROM TDBADMIN.DTG_VIEW DL \
	WHERE DL.S_ID = %d AND DL.DLG_ID > -1 ORDER BY %s;"

/* DTG_VIEW  Auswahl nach Arrangement */
#define _SEL_DTGVIEW_ARR "SELECT DL.* \
	FROM TDBADMIN.DTG_VIEW DL, TDBADMIN.ARR_DLG AD \
	WHERE AD.ARR_ID = %d AND DL.DLG_ID = AD.DLG_ID \
	AND DL.S_ID = %d AND DL.DLG_ID > -1 ORDER BY %s;"

/* DTG_VIEW  Auswahl nach Saison */
#define _SEL_DTGVIEW_SAI "SELECT * FROM TDBADMIN.DTG_VIEW DL \
	WHERE DL.SAI_ID = %d AND DL.S_ID = %d AND DL.DLG_ID > -1 ORDER BY %s;"

/* DTG_VIEW  Auswahl nach Anfangs- und Endzeit */
#define _SEL_DTGVIEW_AE "SELECT * FROM TDBADMIN.DTG_VIEW DL \
	WHERE DL.S_ID = %d AND DL.DLG_ID > -1 \
	AND (DL.A_ZEIT >= %d AND DL.A_ZEIT <= %d) ORDER BY %s;"

/* DTG_VIEW  Auswahl nach Anfangszeit */
#define _SEL_DTGVIEW_A "SELECT * FROM TDBADMIN.DTG_VIEW DL \
	WHERE DL.S_ID = %d AND DL.DLG_ID > -1 \
	AND (DL.A_ZEIT >= %d OR DL.A_ZEIT = -1) ORDER BY %s;"

/* DTG_VIEW  Auswahl nach Endzeit */
#define _SEL_DTGVIEW_E "SELECT * FROM TDBADMIN.DTG_VIEW DL \
	WHERE DL.S_ID = %d AND DL.DLG_ID > -1 \
	AND (DL.A_ZEIT <= %d OR DL.A_ZEIT = -1) ORDER BY %s;"

/* DTG_VIEW  Auswahl nach Angebotstyp */
#define _SEL_DTGVIEW_DLAT "SELECT DISTINCT DL.* \
	FROM TDBADMIN.DTG_VIEW DL, TDBADMIN.DLG_DLG DD, \
	TDBADMIN.DLG_PARTS DLP, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE DL.S_ID = %d AND DLA.ART_ID = %d AND DLP.DLA_ID = DLA.DLA_ID \
	AND DD.DL_ID = DLP.DL_ID AND DL.DLG_ID = DD.DLG_ID ORDER BY %s;"

/* DTG_VIEW  Auswahl nach Buchung und DLN */
#define	_SEL_DTGVIEW_BCHDLN "SELECT DISTINCT DL.* \
	FROM TDBADMIN.DTG_VIEW DL, TDBADMIN.RESERVATION R \
	WHERE R.BID = %d AND R.PERS_ID = %d \
	AND DL.DLG_ID = R.DLG_ID AND DL.S_ID = %d \
	ORDER BY %s;"

/* DTG_VIEW  Auswahl nach Traeger */
#define _SEL_DTGVIEW_DLT "SELECT DISTINCT DL.* \
	FROM TDBADMIN.DTG_VIEW DL, TDBADMIN.DLG_DLG DLDLG, \
	 TDBADMIN.DLG_PARTS DLG, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE DL.S_ID = %d AND DL.DLG_ID > -1 \
	 AND DL.DLG_ID = DLDLG.DLG_ID AND DLDLG.DL_ID = DLG.DL_ID \
	 AND DLG.DLA_ID = DLA.DLA_ID AND DLA.DLT_ID = %d \
	ORDER BY %s;"

/* DTG_VIEW  Auswahl nach Traeger und Datum */
#define _SEL_DTG_VIEW_DLTAE "SELECT DISTINCT DL.* \
	FROM TDBADMIN.DTG_VIEW DL, TDBADMIN.DLG_DLG DLDLG, \
	     TDBADMIN.DLG_PARTS DLG, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE DL.DLG_ID > -1 AND DL.S_ID = %d \
	 AND (DL.A_ZEIT >= %d AND DL.A_ZEIT <= %d) \
	 AND DL.DLG_ID = DLDLG.DLG_ID AND DLDLG.DL_ID = DLG.DL_ID \
	 AND DLG.DLA_ID = DLA.DLA_ID AND DLA.DLT_ID = %d \
	ORDER BY %s;"


/* DIENSTLEISTUNG  Auswahl nach Angebot */
#define _SEL_DL_DLA "SELECT DISTINCT DL.* \
	FROM TDBADMIN.DIENSTLEISTUNG DL, TDBADMIN.DLG_DLG DLDLG, TDBADMIN.DLG_PARTS DLG \
	WHERE DL.DLG_ID = DLDLG.DLG_ID AND DLDLG.DL_ID = DLG.DL_ID \
	 AND DLG.DLA_ID = %d \
	ORDER BY DL.A_ZEIT;"

/* DIENSTLEISTUNG  Auswahl aller DL's einer host TDL */
#define _SEL_DL_HTDL "SELECT DISTINCT DL.* \
	FROM TDBADMIN.DIENSTLEISTUNG DL, TDBADMIN.DLG_DLG DD, TDBADMIN.DLG_PARTS TDL \
	WHERE DL.DLG_ID = DD.DLG_ID AND DD.DL_ID = TDL.DL_ID \
	AND (TDL.H_DL_ID = %d OR (TDL.H_DL_ID = -1 AND TDL.DL_ID = %d)) \
	ORDER BY DL.DLG_ID;"




/************************************************************
 * DLG_DLG  Verkn�pfung von DL und DLG_PART
 *************************************************************/
/* DLG_DLG  Suche Eintrag nach DL und ORD */
#define _SEL_DLDLG_ORD "SELECT * FROM TDBADMIN.DLG_DLG DD \
	WHERE DD.DLG_ID = %d AND ORD = %d;"

/* DLG_DLG  Liste aller DLG_PARTs f�r eine DL nach ORD sortiert */
#define _SEL_DLDLG "SELECT * FROM TDBADMIN.DLG_DLG DD \
	WHERE DD.DLG_ID = %d ORDER BY DD.ORD;"

/* DLG_DLG  hole genau ein Eintrag ueber DL und DLPART */
#define _SEL_ONEDLDLG "SELECT * FROM TDBADMIN.DLG_DLG DD \
	WHERE DD.DLG_ID = %d AND DD.DL_ID = %d;"

/* DLG_DLG  hole alle DLs nach einer TDL */
#define _SEL_TDLDLG "SELECT * FROM TDBADMIN.DLG_DLG DD \
	WHERE DD.DL_ID = %d;"

/* DLG_DLG get all DL's from a list of TDL */
#define _SEL_DD_TDL "SELECT DISTINCT DD.* \
	FROM TDBADMIN.DLG_DLG DD WHERE DD.DL_ID IN (%s);"

/* DL_DLG_VIEW  alle TDL nach einer DL */
#define _SEL_DLDLG_VIEW "SELECT * FROM TDBADMIN.DL_DLG_VIEW \
	WHERE DLG_ID = %d AND S_ID = %d \
	ORDER BY ORD;"


/************************************************************
 * PROGRAMM
 *************************************************************/
/* PROGRAMM BEZ  Auswahl aller Programms */
#define _SEL_BEZ_PRG "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.PROGRAMM P \
	WHERE B.BEZ_ID=P.BEZ_ID AND P.PRG_ID > -1 \
	AND B.S_ID=%d AND B.TYP=%d \
	ORDER BY B.BEZ;"

/* PROGRAMM BEZ Auswahl nach Saison */
#define _SEL_BEZ_PRG_SAI "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.PROGRAMM P \
	WHERE B.BEZ_ID=P.BEZ_ID \
	AND B.S_ID=%d AND B.TYP=%d \
	AND P.SAI_ID=%d \
	ORDER BY B.BEZ;"


/************************************************************
 * ARRANGEMENT
 *************************************************************/

/* abstraction */
#define _ORDER_ARR_DAT "A.A_DAT, A.BEZ"
#define _ORDER_ARR_BEZ "A.BEZ, A.A_DAT"


/* ARR_VIEW  Auswahl aller Arrangements */
#define _SEL_ARRVIEW "SELECT * FROM TDBADMIN.ARR_VIEW A \
	WHERE A.ARR_ID > -1 AND A.S_ID = %d ORDER BY %s;"

/* ARR_VIEW  Auswahl nach Saison */
#define _SEL_ARRVIEW_SAI "SELECT * FROM TDBADMIN.ARR_VIEW A \
	WHERE A.ARR_ID > -1 AND A.S_ID = %d AND A.SAI_ID = %d ORDER BY %s;"

/* ARR_VIEW  Auswahl nach Programm */
#define _SEL_ARRVIEW_PRG "SELECT * FROM TDBADMIN.ARR_VIEW A \
	WHERE A.ARR_ID > -1 AND A.S_ID = %d AND A.PRG_ID = %d ORDER BY %s;"

/* ARR_VIEW  Auswahl nach Saison und Programm */
#define _SEL_ARRVIEW_PRG_SAI "SELECT * FROM TDBADMIN.ARR_VIEW A \
	WHERE A.ARR_ID > -1 AND A.S_ID = %d \
	AND A.PRG_ID = %d AND A.SAI_ID = %d ORDER BY %s;"

/* ARR_VIEW  Auswahl nach Dienstleistung */
#define _SEL_ARRVIEW_DL "SELECT DISTINCT A.* \
	FROM TDBADMIN.ARR_VIEW A, TDBADMIN.ARR_DLG D \
	WHERE D.DLG_ID = %d AND A.ARR_ID = D.ARR_ID AND A.S_ID = %d \
	ORDER BY %s;"

/* ARR_VIEW  Auswahl nach Datumszone */
#define _SEL_ARRVIEW_AE "SELECT * FROM TDBADMIN.ARR_VIEW A \
	WHERE A.ARR_ID > -1 AND A.S_ID = %d \
	AND (A.A_DAT > %d AND A.A_DAT < %d) ORDER BY %s;"



/************************************************************
 * ARR_DL  Verkn�pfung von ARR und DL
 *************************************************************/
/* ARR_DL  Suche Eintrag nach ARR */
#define _SEL_ARRDL_ARR "SELECT * FROM TDBADMIN.ARR_DLG AD \
	WHERE AD.ARR_ID = %d ORDER BY AD.TEIL, AD.PRIO;"

/* ARR_DL  Suche Eintrag nach ARR und PRIO 1 */
#define _SEL_ARRDL_ARRPRIO "SELECT * FROM TDBADMIN.ARR_DLG AD \
	WHERE AD.ARR_ID = %d AND AD.PRIO = %d ORDER BY AD.TEIL;"

/* ARR_DL  Suche Eintrag nach ARR und TEIL */
#define _SEL_ARRDL_ORD "SELECT * FROM TDBADMIN.ARR_DLG AD \
	WHERE AD.ARR_ID = %d and TEIL = %d;"

/* ARR_DL_VIEW  Hole alle DL's nach einem ARR */
#define _SEL_ARRDLVIEW_DL "SELECT * FROM TDBADMIN.ARR_DL_VIEW AV \
	WHERE AV.S_ID = %d AND AV.ARR_ID = %d ORDER BY AV.TEIL, AV.PRIO;"

/* ARR_DL_VIEW  Hole alle DL's in einer RES mit ARR */
#define _SEL_ARRDLVIEW_RES "SELECT DISTINCT AV.* \
	FROM TDBADMIN.ARR_DL_VIEW AV, TDBADMIN.RESERVATION RES \
	WHERE AV.ARR_ID = %d AND RES.BID = %d AND RES.PERS_ID = %d \
	AND AV.DLG_ID = RES.DLG_ID \
	AND AV.S_ID = %d ORDER BY AV.TEIL, AV.PRIO;"

// TODO HARDCODED typs
#define	_SEL_BEZ_ARR_DTG	"SELECT AD.ARR_ID, AD.TEIL, AD.PRIO, \
	AD.DLG_ID, DL.BEZ_ID, DL.SAI_ID, DL.A_ZEIT, DL.DLG_ID, A.BEZ, B.BEZ, \
	A.S_ID, DL.A_ZEIT \
	FROM	TDBADMIN.ARR_DLG AD, TDBADMIN.ARRANGEMENT ARR, TDBADMIN.DIENSTLEISTUNG DL, \
	TDBADMIN.BEZEICHNUNG A, TDBADMIN.BEZEICHNUNG B \
	WHERE	AD.ARR_ID = %d AND AD.DLG_ID = DL.DLG_ID \
	AND AD.ARR_ID = ARR.ARR_ID AND A.TYP = 30 AND A.S_ID = %d \
	AND A.BEZ_ID=ARR.BEZ_ID AND B.TYP = 27 AND B.S_ID = %d \
	AND B.BEZ_ID=DL.BEZ_ID ORDER BY AD.TEIL, AD.PRIO;"

// TODO HARDCODED typs
#define	_SEL_BEZ_ARR_DLG "SELECT AD.ARR_ID, AD.TEIL, AD.PRIO, \
	AD.DLG_ID, TDL.DL_ID, DD.ORD, TDL.A_ZEIT, TDL.RES_F, A.BEZ, B.BEZ, A.S_ID, \
	DL.A_ZEIT \
	FROM	TDBADMIN.ARR_DLG AD, TDBADMIN.DLG_DLG DD, TDBADMIN.DLG_PARTS TDL, \
	TDBADMIN.DIENSTLEISTUNG DL, TDBADMIN.BEZEICHNUNG A, TDBADMIN.BEZEICHNUNG B \
	WHERE	AD.ARR_ID = %d AND AD.DLG_ID = DD.DLG_ID \
	AND TDL.DL_ID = DD.DL_ID AND AD.DLG_ID = DL.DLG_ID AND A.TYP = 26 \
	AND A.S_ID = %d AND A.BEZ_ID=TDL.BEZ_ID AND B.TYP = 27 AND B.S_ID = %d \
	AND B.BEZ_ID=DL.BEZ_ID ORDER BY AD.TEIL, AD.PRIO, DD.ORD;"


/************************************************************
 * KONTINGENT / HOST_KONT / KONT_DETAIL
 *************************************************************/
/* HOST_KONT  alle Bezeichnungen */
#define _SEL_BEZ_HKON "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.HOST_KONT K \
	WHERE K.HOSTKONT_ID > -1 AND B.BEZ_ID = K.BEZ_ID \
	AND B.S_ID=%d AND B.TYP=%d ORDER BY B.BEZ;"

/* HOST_KONT  nach Buchungsstelle-Kunden eingeschraenkt */
#define _SEL_BEZ_HKON_BST "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.HOST_KONT K \
	WHERE B.BEZ_ID = K.BEZ_ID AND B.S_ID=%d AND B.TYP=%d \
	AND K.KBST=%d ORDER BY B.BEZ;"

/* KONTINGENT  alle Bezeichnungen */
#define _SEL_BEZ_KON "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KONTINGENT K \
	WHERE K.KONT_ID > -1 AND B.BEZ_ID = K.BEZ_ID \
	AND B.S_ID=%d AND B.TYP=%d ORDER BY B.BEZ;"

/* KONTINGENT  nach an-Kunde eingeschraenkt */
#define _SEL_BEZ_KON_KUN "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KONTINGENT K \
	WHERE B.BEZ_ID = K.BEZ_ID AND B.S_ID=%d AND B.TYP=%d \
	AND K.KUNDEN_ID=%d \
	ORDER BY B.BEZ;"

/* KONTINGENT  nach DL eingeschraenkt */
#define _SEL_BEZ_KON_DL "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KONTINGENT K, TDBADMIN.HOST_KONT HK \
	WHERE (HK.DL_ID = %d OR (HK.DLA_ID = %d AND HK.DL_ID < 1)) \
	AND K.HOSTKONT_ID = HK.HOSTKONT_ID \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ_ID = K.BEZ_ID \
	ORDER BY B.BEZ;"

/* KONTINGENT  nach DL und RECH-STELLE eingeschraenkt */
#define _SEL_BEZ_KON_DL_KUN "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KONTINGENT K, TDBADMIN.HOST_KONT HK \
	WHERE (HK.DL_ID = %d OR (HK.DLA_ID = %d AND HK.DL_ID < 1)) \
	AND K.HOSTKONT_ID = HK.HOSTKONT_ID \
	AND (K.KUNDEN_ID = -1 OR K.KUNDEN_ID = %d) \
	AND B.S_ID = %d AND B.TYP = %d AND B.BEZ_ID = K.BEZ_ID \
	ORDER BY B.BEZ;"


#define _SEL_ONE_KON_D "SELECT * FROM TDBADMIN.KONT_DETAIL \
	WHERE KONT_ID = %d ORDER BY KAT_ID;"

/* KONT_DETAIL  nach KONTINGENT */
#define _SELECT_KOND_KON "SELECT * FROM TDBADMIN.KONT_DETAIL WHERE KONT_ID = %d \
	ORDER BY KAT_ID, DLT_ID;"

/* KONT_DETAIL  nach HOST_KONT */
#define _SELECT_KOND_HKON "SELECT * FROM TDBADMIN.KONT_DETAIL WHERE HOSTKONT_ID = %d \
	ORDER BY KAT_ID, DLT_ID;"


/************************************************************
 * KAPAZITAETEN TABELLE
 *************************************************************/
/* KAPA: hole ein Eintraege mit KAT und TDL */
#define _SEL_KAPA_TDLKAT "SELECT K.* FROM TDBADMIN.KAPA K \
	WHERE K.TDL_ID = %d AND K.KAT_ID = %d;"

/* MPV_KAPA: hole alle Eintraege von mehreren TDLs */
#define _SEL_KAPAV_TDLS "SELECT KV.* FROM TDBADMIN.MPV_KAPA KV \
	WHERE KV.TDL_ID IN (%s) AND KV.TDL_S_ID = %d AND KV.KAT_S_ID = %d \
	ORDER BY KV.KATBEZ, KV.TDL_ID;"

/* KAPA hole alle Kategorien nach einer TDL */
#define _SEL_KAPA_KAT "SELECT KV.* \
	FROM TDBADMIN.MPV_KAPA KV \
	WHERE KV.TDL_ID = %d AND KV.TDL_S_ID = %d AND KV.KAT_S_ID = %d \
	ORDER BY KV.KATBEZ;"

/************************************************************
 * KOSTEN ART  /  PREIS  /  KOMMISSION
 *************************************************************/

/* KOSTEN_ART BEZ:  hole alle */
#define _SEL_BEZ_KAR "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KOSTEN_ART KA \
	WHERE B.S_ID=%d AND B.TYP=%d \
	AND KA.KAR_ID > -1 AND B.BEZ_ID=KA.BEZ_ID \
	ORDER BY B.BEZ;"

/* PREIS  Preis Info Select */
#define _SEL_PRE "SELECT * FROM TDBADMIN.PREIS ORDER BY DLA_ID, DL_ID, PRE_ID;"

/* PREIS hole alle Preise zu einem DLA */
#define _SEL_PRE_DLA "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.DLA_ID = %d;"

/* PREIS hole alle Preise zu einer DL */
#define _SEL_PRE_DL "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.DL_ID = %d;"

/* PREIS hole alle Preise zu einer KAT */
#define _SEL_PRE_KAT "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.KAT_ID = %d;"

/* PREIS hole alle Preise zu einer KAR */
#define _SEL_PRE_KAR "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.KAR_ID = %d;"

/* PREIS hole alle Preise zu einem DLNT */
#define _SEL_PRE_DLNT "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.RKR_ID = %d;"

/* PREIS hole alle Preise zu einem KON */
#define _SEL_PRE_KON "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.KONT_ID = %d;"

/* PREIS dynamischer Preis-select fuer info */
#define _SEL_ALL_PRE_WHE "SELECT * FROM TDBADMIN.PREIS %s;"

/* KOMMISSION BEZ  hole alle Kommissionbezeichnungen */
#define _SEL_BEZ_KOM "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KOMMISSION K \
	WHERE K.KOMM_ID > -1 \
	AND B.BEZ_ID = K.BEZ_ID AND B.S_ID = %d AND B.TYP = %d \
	ORDER BY B.BEZ;"

/* KOMMISSION BEZ  hole alle Kommissionskoepfe nach Typ */
#define _SEL_BEZ_KOM_TYP "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KOMMISSION K \
	WHERE K.KOMM_ID > -1 AND K.KOMM_TYP = %d \
	AND B.BEZ_ID = K.BEZ_ID AND B.S_ID=%d AND B.TYP=%d \
	ORDER BY B.BEZ;"

/* KOMMISSION BEZ hole alle Kommissionen nach Typ */
#define _SEL_BEZ_KOM_KOMTYP "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KOMMISSION K \
	WHERE K.KOMM_TYP = %d AND B.BEZ_ID = K.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d \
	ORDER BY B.BEZ;"

/* KOMMISSION BEZ hole alle Reisenden-Kommissionen nach Arrangement */
#define _SEL_BEZ_DLN_ARRKOM "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.MP_ARRKOM AK \
	WHERE AK.ARR_ID = %d AND B.S_ID = %d AND B.TYP = %d \
	AND B.BEZ_ID = AK.KOMM_BEZID ORDER BY B.BEZ;"

/* KOMMISSION BEZ hole alle Kommissionen nach Typ und Arrangement */
#define _SEL_BEZ_KOM_KOMTYP_ARR "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.KOMMISSION K \
	WHERE K.KOMM_TYP = %d \
	AND ((K.DLA_ID = -1 AND K.DL_ID = -1) \
	OR ((K.DLA_ID IN (SELECT DISTINCT TDL.DLA_ID \
	  FROM TDBADMIN.DLG_PARTS TDL, TDBADMIN.ARR_DLG AD, TDBADMIN.DLG_DLG DD WHERE AD.ARR_ID = %d \
	  AND DD.DLG_ID = AD.DLG_ID AND TDL.DL_ID = DD.DL_ID) \
	 OR (K.DLA_ID IN (SELECT DISTINCT DLA.H_DLA_ID FROM TDBADMIN.DLG_PARTS TDL, \
	  TDBADMIN.ARR_DLG AD, TDBADMIN.DLG_DLG DD, TDBADMIN.DIENST_ANGEBOT DLA \
	  WHERE AD.ARR_ID = %d AND DD.DLG_ID = AD.DLG_ID AND TDL.DL_ID = DD.DL_ID \
	  AND DLA.DLA_ID = TDL.DLA_ID))) \
	 AND K.DL_ID = -1) \
	OR (K.DLA_ID = -1 AND K.DL_ID IN (SELECT AD.DLG_ID FROM TDBADMIN.ARR_DLG AD \
	 WHERE AD.ARR_ID = %d))) \
	AND B.BEZ_ID = K.BEZ_ID AND B.S_ID = %d AND B.TYP = %d \
	ORDER BY B.BEZ;"

/* KOMMISSION hole alle Kommissionen nach Typ und Arrangement */
#define _SEL_KOM_KOMTYP_ARR "SELECT K.* \
	FROM TDBADMIN.KOMMISSION K WHERE K.KOMM_TYP = %d \
	AND ((K.DLA_ID = -1 AND K.DL_ID = -1) \
	OR ((K.DLA_ID IN (SELECT DISTINCT TDL.DLA_ID \
	  FROM TDBADMIN.DLG_PARTS TDL, TDBADMIN.ARR_DLG AD, TDBADMIN.DLG_DLG DD WHERE AD.ARR_ID = %d \
	  AND DD.DLG_ID = AD.DLG_ID AND TDL.DL_ID = DD.DL_ID) \
	 OR (K.DLA_ID IN (SELECT DISTINCT DLA.H_DLA_ID FROM TDBADMIN.DLG_PARTS TDL, \
	  TDBADMIN.ARR_DLG AD, TDBADMIN.DLG_DLG DD, TDBADMIN.DIENST_ANGEBOT DLA \
	  WHERE AD.ARR_ID = %d AND DD.DLG_ID = AD.DLG_ID AND TDL.DL_ID = DD.DL_ID \
	  AND DLA.DLA_ID = TDL.DLA_ID))) \
	 AND K.DL_ID = -1) \
	OR (K.DLA_ID = -1 AND K.DL_ID IN (SELECT AD.DLG_ID FROM TDBADMIN.ARR_DLG AD \
	 WHERE AD.ARR_ID = %d)));"

/* KOMMISSION:  hole alle einer BCH und eines DLN gem. KOMM_DETAIL */
#define _SEL_KOM_BCHDLN "SELECT K.* \
	FROM TDBADMIN.KOMMISSION K, TDBADMIN.KOMM_DETAIL KD \
	WHERE KD.BID = %d AND KD.DLN_ID = %d AND K.KOMM_ID = KD.KOMM_ID;"

/* KOMM_DETAIL: hole alle Eintraege fuer eine Kommission */
#define _SEL_KOMMDET_KOMM "SELECT * FROM TDBADMIN.KOMM_DETAIL KD \
	WHERE KD.KOMM_ID = %d ORDER BY KD.DLN_ID, KD.KUN_ID, KD.KOL_ID;"

/* KOMM_DETAIL: hole alle Eintraege fuer einen DLN */
#define _SEL_KOMMDET_DLN "SELECT * FROM TDBADMIN.KOMM_DETAIL KD \
	WHERE KD.DLN_ID = %d ORDER BY KD.BID, KD.PRIO;"

/* KOMM_DETAIL: hole alle Eintraege fuer einen KUN */
#define _SEL_KOMMDET_KUN "SELECT * FROM TDBADMIN.KOMM_DETAIL KD \
	WHERE KD.KUN_ID = %d ORDER BY KD.PRIO;"

/* KOMM_DETAIL: hole alle Eintraege fuer ein KOL */
#define _SEL_KOMMDET_KOL "SELECT * FROM TDBADMIN.KOMM_DETAIL KD \
	WHERE KD.KOL_ID = %d ORDER BY KD.PRIO;"


/************************************************************
 * BUCHUNG / RESERVATION
 *************************************************************/
/* abstraction */
#define _ORDER_BCH_REF "B.REF DESC"
#define _ORDER_BCH_ID  "B.BID DESC"
#define _SEC_USERBCHST "AND B.KBST = %d AND B.ANW = \'%s\'"
#define _SEC_BCHST "AND B.KBST = %d"

/* BUCHUNG  hole alle Buchungen */
#define _SEL_REF_BCH "SELECT * FROM TDBADMIN.BUCHUNG B WHERE B.BID > 0 %s \
	ORDER BY %s;"
/* BUCHUNG  hole nach Arrangement */
#define _SEL_REF_BCH_ARR "SELECT * FROM TDBADMIN.BUCHUNG B \
	WHERE B.ARR_ID = %d %s ORDER BY %s;"
/* BUCHUNG  hole nach Reisender/DLN */
#define _SEL_REF_BCH_DLN "SELECT B.* \
	FROM TDBADMIN.BUCHUNG B, TDBADMIN.BCH_DLN BD \
	WHERE BD.DLN_ID = %d AND B.BID = BD.BID %s ORDER BY %s;"
/* BUCHUNG  hole nach Kunden */
#define _SEL_REF_BCH_KUN "SELECT * FROM TDBADMIN.BUCHUNG B \
	WHERE B.KID = %d %s ORDER BY %s;"
/* BUCHUNG  hole nach Arrangement */
#define _SEL_REF_BCH_ARRKUN "SELECT * FROM TDBADMIN.BUCHUNG B \
	WHERE B.ARR_ID = %d AND B.KID = %d %s ORDER BY %s;"


/* BUCHUNG  hole nach einer Dienstleistung vom AKT_DETAIL */
#define _SEL_BCH_DL "SELECT DISTINCT B.* \
	FROM TDBADMIN.BUCHUNG B, TDBADMIN.AKT_DETAIL AD \
	WHERE AD.DLG_ID = %d AND B.BID = AD.BID \
	ORDER BY B.K_ID, B.KID, B.BID;"

/* BUCHUNG  hole nach einer DL und einem KOLLEKTIV */
#define _SEL_BCH_DL_KOL "SELECT DISTINCT B.* \
	FROM TDBADMIN.BUCHUNG B, TDBADMIN.AKT_DETAIL AD \
	WHERE B.K_ID = %d AND AD.DLG_ID = %d \
	AND B.BID = AD.BID ORDER BY B.KID, B.BID;"

/* BUCHUNG  hole nach einer BUCHUNGSNUMMER */
#define _SEL_BCH_BCH "SELECT B.* \
	FROM TDBADMIN.BUCHUNG B WHERE B.BID = %d;"


/* BCH_DLN  hole alle reisenden/DLN einer Buchung */
#define _SEL_BD_BCH "SELECT * FROM TDBADMIN.BCH_DLN WHERE BID = %d;"

/* hole alle Reservationen zu einem Reisenden in einer Buchung */
#define	_SEL_RES_BCHDLN "SELECT * FROM TDBADMIN.RESERVATION \
	WHERE BID = %d AND PERS_ID = %d \
	ORDER BY TEIL, DL_ID;"

/* hole alle DL-Reservationen zu einem Reisenden in einer Buchung */
#define	_SEL_RES_BCHDLN_DL "SELECT * FROM TDBADMIN.RESERVATION RES \
	WHERE RES.BID = %d AND RES.PERS_ID = %d \
	AND RES.DLG_ID = %d ORDER BY RES.DL_ID;"

/* hole DLPART-Reservation zu einem Reisenden in einer Buchung */
#define	_SEL_RES_BCHDLN_DLPART "SELECT * FROM TDBADMIN.RESERVATION RES \
	WHERE RES.BID = %d AND RES.PERS_ID = %d AND RES.DLG_ID = %d \
	AND RES.DL_ID = %d;"

/* hole TEIL-Reservation zu einem Reisenden in einer Buchung */
#define	_SEL_RES_BCHDLN_TEIL "SELECT * FROM TDBADMIN.RESERVATION RES \
	WHERE RES.BID = %d AND RES.PERS_ID = %d AND RES.TEIL = %d;"

/* RESERVATION:  hole alle RES von gewissen TDL's */
#define _SEL_RES_TDL "SELECT * FROM TDBADMIN.RESERVATION R WHERE R.DL_ID IN (%s) \
	ORDER BY R.DLT_ID;"

/* RESERVATION:  hole alle RES von gewissen TDL's in einem Zeitraum */
#define _SEL_RES_TDL_DAT "SELECT * FROM TDBADMIN.RESERVATION R \
	WHERE R.DL_ID IN (%s) AND (R.A_ZEIT <= %d AND R.E_ZEIT >= %d) \
	ORDER BY R.DLT_ID;"

/* RESERVATION:  hole alle RES von gewissen DL's */
#define _SEL_RES_DL "SELECT * FROM TDBADMIN.RESERVATION R WHERE R.DLG_ID = %d \
	ORDER BY R.DLT_ID;"

/* RESERVATION:  hole alle RES von gewissen DL's in einem Zeitraum */
#define _SEL_RES_DL_DAT "SELECT * FROM TDBADMIN.RESERVATION R \
	WHERE R.DLG_ID = %d AND (R.A_ZEIT <= %d AND R.E_ZEIT >= %d) \
	ORDER BY R.DLT_ID;"

#define _SEL_COUNT_RES_BUSYDLT "SELECT COUNT(RES.DLT_ID) \
	FROM TDBADMIN.RESERVATION RES \
	WHERE RES.KAT_ID = %d AND RES.DLG_ID IN (%s) GROUP BY RES.DLT_ID;"

#define _SEL_COUNT_RES_BUSYDLT_DAT "SELECT COUNT(RES.DLT_ID) \
	FROM TDBADMIN.RESERVATION RES \
	WHERE RES.KAT_ID = %d AND RES.DLG_ID IN (%s) \
	AND (RES.A_ZEIT <= %d AND RES.E_ZEIT >= %d) GROUP BY RES.DLT_ID;"

#define _SEL_COUNT_RES_BUSYDL "SELECT COUNT(RES.DLG_ID) \
	FROM TDBADMIN.RESERVATION RES \
	WHERE RES.DLG_ID IN (%s);"



/************************************************************
 * GRAFIK / REGIONS / PCX
 *************************************************************/
#define _SEL_BEZ_GRA "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.GRAPHIK G \
	WHERE B.S_ID=%d AND B.TYP=%d \
	AND G.GRA_ID > -1 AND B.BEZ_ID=G.BEZ_ID \
	ORDER BY B.BEZ;"

#define _SEL_BEZ_PCX "SELECT B.* \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.PCX_FILES P \
	WHERE B.S_ID=%d AND B.TYP=%d \
	AND P.PCX_ID > -1 AND B.BEZ_ID=P.BEZ_ID \
	ORDER BY B.BEZ;"

#define _SEL_BEZ_TYP_PCX "SELECT B.* \
   FROM TDBADMIN.BEZEICHNUNG B \
   WHERE B.S_ID=%d AND B.TYP=%d AND B.BEZ_ID > 0 \
   ORDER BY B.BEZ;"

#define	_SEL_REG_GRA	"SELECT * FROM TDBADMIN.REGIONS \
	WHERE TDBADMIN.REGIONS.HOST_ID = %d ORDER BY DLT_ID, FOLGE;"

#define	_SEL_REG_DLT	"SELECT * FROM TDBADMIN.REGIONS \
	WHERE TDBADMIN.REGIONS.DLT_ID = %d ORDER BY FOLGE;"

#define	_SEL_FORM_GRA	"SELECT * FROM TDBADMIN.GRAFORM \
	WHERE TDBADMIN.GRAFORM.GRA_ID = %d ORDER BY FORMNR;"




/*-------------------------------------------------------------------------*/
/*----	Definition der diversen OUTPUT - SQL-Befehle fuer einr DTG -------*/
/*-------------------------------------------------------------------------*/
#define	_SEL_PRE_DTG	"SELECT * FROM TDBADMIN.PREIS \
	ORDER BY DLA_ID, DLG_ID, GLT DESC;"
#define	_SEL_RES_DTG	"SELECT RES.* FROM TDBADMIN.RESERVATION RES, \
	TDBADMIN.BUCHUNG B, TDBADMIN.ARR_DLG AD \
	WHERE AD.DLG_ID = %d AND AD.ARR_ID = B.ARR_ID \
	AND B.BID = RES.BID ORDER BY RES.BID, RES.TEIL;"
#define	_SEL_1_RES_DTG	"SELECT * FROM TDBADMIN.RESERVATION \
			 WHERE TDBADMIN.RESERVATION.BID = %d \
			 ORDER BY TDBADMIN.RESERVATION.TEIL;"
#define	_SEL_BCH_DTG	"SELECT * FROM TDBADMIN.BUCHUNG \
			 WHERE BID IN (SELECT DISTINCT BID FROM TDBADMIN.RESERVATION \
				WHERE TDBADMIN.RESERVATION.DLG_ID = %d) \
			 ORDER BY K_ID;"
#define	_SEL_1_BCH_DTG	"SELECT * FROM TDBADMIN.BUCHUNG WHERE TDBADMIN.BUCHUNG.BID = %d;"
#define	_SEL_ARR_DTG	"SELECT DISTINCT TDBADMIN.ARR_DLG_VIEW.* FROM TDBADMIN.ARR_DLG_VIEW, TDBADMIN.BUCHUNG, TDBADMIN.RESERVATION \
			 WHERE TDBADMIN.ARR_DLG_VIEW.ARR_ID = TDBADMIN.BUCHUNG.ARR_ID \
			 AND TDBADMIN.BUCHUNG.BID = TDBADMIN.RESERVATION.BID \
			 AND TDBADMIN.RESERVATION.DLG_ID = %d \
			 ORDER BY TDBADMIN.ARR_DLG_VIEW.ARR_ID,  TDBADMIN.ARR_DLG_VIEW.TEIL,  TDBADMIN.ARR_DLG_VIEW.ORD;"
#define	_SEL_REI_DTG	"SELECT * FROM TDBADMIN.REISENDER WHERE PERS_ID IN \
				(SELECT DISTINCT PERS_ID FROM TDBADMIN.RESERVATION WHERE DLG_ID = %d);"
#define	_SEL_DLG_DTG	"SELECT DISTINCT TDBADMIN.DLG_VIEW.* FROM TDBADMIN.DLG_VIEW, TDBADMIN.RESERVATION, \
					 TDBADMIN.BUCHUNG, TDBADMIN.ARR_DLG \
			 WHERE TDBADMIN.ARR_DLG.DLG_ID = %d \
			 AND TDBADMIN.ARR_DLG.ARR_ID = TDBADMIN.BUCHUNG.ARR_ID \
			 AND TDBADMIN.BUCHUNG.BID = TDBADMIN.RESERVATION.BID \
			 AND TDBADMIN.RESERVATION.DL_ID = TDBADMIN.DLG_VIEW.DL_ID \
			 ORDER BY TDBADMIN.DLG_VIEW.DL_ID;"
#define	_SEL_DTG_DTG	"SELECT * FROM TDBADMIN.DTG_VIEW ORDER BY DLG_ID;"
#define	_SEL_DLA_DTG	"SELECT * FROM TDBADMIN.DLA_VIEW ORDER BY DLA_ID;"
#define	_SEL_DLT_DTG	"SELECT DISTINCT TDBADMIN.DLT_VIEW.* FROM TDBADMIN.DLT_VIEW, TDBADMIN.RESERVATION \
			 WHERE TDBADMIN.RESERVATION.DLG_ID = %d \
			 AND TDBADMIN.RESERVATION.DLT_ID = TDBADMIN.DLT_VIEW.DLT_ID \
			 UNION \
			 SELECT DISTINCT TDBADMIN.DLT_VIEW.* FROM TDBADMIN.DLT_VIEW, TDBADMIN.DLG_DLG, \
				TDBADMIN.DLG_PARTS, TDBADMIN.DIENST_ANGEBOT \
			 WHERE TDBADMIN.DLG_DLG.DLG_ID = %d \
			 AND TDBADMIN.DLG_DLG.DL_ID = TDBADMIN.DLG_PARTS.DL_ID \
			 AND TDBADMIN.DLG_PARTS.DLA_ID = TDBADMIN.DIENST_ANGEBOT.DLA_ID \
			 AND TDBADMIN.DLT_VIEW.DLT_ID = TDBADMIN.DIENST_ANGEBOT.DLT_ID \
			 ORDER BY TDBADMIN.DLT_VIEW.DLT_ID;"
#define	_SEL_KUN_DTG	"SELECT * FROM TDBADMIN.KUNDEN;"
#define	_SEL_KOL_DTG	"SELECT * FROM TDBADMIN.KOLLEKTIV;"
#define	_SEL_KOM_DTG	"SELECT * FROM TDBADMIN.KOMMISSION;"
#define	_SEL_STA_DTG	"SELECT * FROM TDBADMIN.STA_VIEW;"
#define	_SEL_KAR_DTG	"SELECT * FROM TDBADMIN.KAR_VIEW;"
#define	_SEL_KAT_DTG	"SELECT * FROM TDBADMIN.KAT_VIEW ORDER BY KAT_ID;"
#define	_SEL_KON_DTG	"SELECT * FROM TDBADMIN.KON_VIEW;"
#define	_SEL_AKT_DTG	"SELECT DISTINCT TDBADMIN.AKT_DETAIL_VIEW.* \
			 FROM TDBADMIN.AKT_DETAIL_VIEW, TDBADMIN.BUCHUNG, TDBADMIN.ARR_DLG \
			 WHERE TDBADMIN.AKT_DETAIL_VIEW.A_TYP_ID = %d \
			 AND TDBADMIN.ARR_DLG.DLG_ID = %d \
			 AND TDBADMIN.ARR_DLG.ARR_ID = TDBADMIN.BUCHUNG.ARR_ID \
			 AND TDBADMIN.BUCHUNG.BID = TDBADMIN.AKT_DETAIL_VIEW.BID \
			 ORDER BY TDBADMIN.AKT_DETAIL_VIEW.BID, TDBADMIN.AKT_DETAIL_VIEW.PERS_ID, TDBADMIN.AKT_DETAIL_VIEW.TEIL;"
#define	_SEL_1_AKT_DTG	"SELECT DISTINCT * FROM TDBADMIN.AKT_DETAIL_VIEW \
			 WHERE TDBADMIN.AKT_DETAIL_VIEW.BID = %d  \
			 AND TDBADMIN.AKT_DETAIL_VIEW.A_TYP_ID = %d \
			 ORDER BY TDBADMIN.AKT_DETAIL_VIEW.PERS_ID, TDBADMIN.AKT_DETAIL_VIEW.TEIL;"



/************************************************************
 * ALL  select a hole relation (only in DBI)
 *************************************************************/
#define	_SEL_ALL_DLT	"SELECT * FROM TDBADMIN.DIENST_TRAEGER ORDER BY DLT_ID;"
#define	_SEL_ALL_DLT_VIEW	"SELECT * FROM TDBADMIN.DLT_VIEW WHERE S_ID = %d AND DLT_ID > -1;"
#define	_SEL_ALL_DLT_TYP	"SELECT * FROM TDBADMIN.DIENST_TRAEGER WHERE TYP_ID=%d ORDER BY DLT_ID;"
#define	_SEL_ALL_DLTT	"SELECT * FROM TDBADMIN.TRAEGER_TYP ORDER BY TYP_ID;"
#define	_SEL_ALL_DLA	"SELECT * FROM TDBADMIN.DIENST_ANGEBOT ORDER BY DLA_ID;"
#define	_SEL_ALL_DLA_ART	"SELECT * FROM TDBADMIN.DIENST_ANGEBOT WHERE ART_ID=%d ORDER BY DLA_ID;"
#define	_SEL_ALL_DLAT	"SELECT * FROM TDBADMIN.ANGEBOTS_TYP ORDER BY ART_ID;"
#define	_SEL_ALL_AKT	"SELECT * FROM TDBADMIN.AKTIONEN WHERE ORD=0 ORDER BY AKT_ID;"
#define	_SEL_ALL_AKT_ORD	"SELECT * FROM TDBADMIN.AKTIONEN WHERE AKT_ID=%d ORDER BY ORD;"
#define	_SEL_ALL_AKTT	"SELECT * FROM TDBADMIN.AKTIONS_TYP ORDER BY A_TYP_ID, ORD;"
#define	_SEL_ALL_KAT	"SELECT * FROM TDBADMIN.KATEGORIE ORDER BY KAT_ID;"
#define	_SEL_ALL_REIT	"SELECT * FROM TDBADMIN.REISENDER_TYP ORDER BY RKR_ID;"
#define	_SEL_ALL_KOLT	"SELECT * FROM TDBADMIN.KOLLEKTIV_TYP ORDER BY K_TYP_ID;"
#define	_SEL_ALL_PRG	"SELECT * FROM TDBADMIN.PROGRAMM ORDER BY PRG_ID;"
#define	_SEL_ALL_PRG_SAI	"SELECT * FROM TDBADMIN.PROGRAMM WHERE SAI_ID=%d ORDER BY PRG_ID;"
#define	_SEL_ALL_PRE	"SELECT * FROM TDBADMIN.PREIS;"
#define	_SEL_ALL_REI	"SELECT * FROM TDBADMIN.REISENDER ORDER BY PERS_ID;"
#define	_SEL_ALL_REI_TYP	"SELECT * FROM TDBADMIN.REISENDER WHERE RKR_ID=%d ORDER BY PERS_ID;"
#define	_SEL_ALL_KOL	"SELECT * FROM TDBADMIN.KOLLEKTIV ORDER BY K_ID;"
#define	_SEL_ALL_KOL_TYP	"SELECT * FROM TDBADMIN.KOLLEKTIV WHERE K_ID=%d ORDER BY K_ID;"
#define	_SEL_ALL_SAI	"SELECT * FROM TDBADMIN.SAISON ORDER BY SAI_ID;"
#define	_SEL_ALL_ARR	"SELECT * FROM TDBADMIN.ARRANGEMENT ORDER BY ARR_ID;"
#define	_SEL_ALL_DTG_ARR	"SELECT * FROM TDBADMIN.ARR_DLG WHERE ARR_ID = %d ORDER BY DLG_ID;"
#define	_SEL_ALL_ARR_PRG	"SELECT * FROM TDBADMIN.ARRANGEMENT WHERE PRG_ID=%d ORDER BY ARR_ID;"
#define	_SEL_ALL_DLG	"SELECT * FROM TDBADMIN.DLG_PARTS ORDER BY DL_ID;"
#define	_SEL_ALL_DLG_DLA	"SELECT * FROM TDBADMIN.DLG_PARTS WHERE DLA_ID=%d ORDER BY DL_ID;"
#define	_SEL_ALL_BCH	"SELECT * FROM TDBADMIN.BUCHUNG ORDER BY BID;"
#define	_SEL_ALL_RES	"SELECT * FROM TDBADMIN.RESERVATION;"
#define	_SEL_ALL_RES_BID "SELECT * FROM TDBADMIN.RESERVATION WHERE BID = %d \
	ORDER BY PERS_ID, TEIL, DL_ID;"
#define	_SEL_ALL_RES_BID_UID "SELECT * FROM TDBADMIN.RESERVATION WHERE BID = %d \
	AND PERS_ID = %d ORDER BY TEIL, DL_ID;"
#define	_SEL_ALL_RES_DLG "SELECT * FROM TDBADMIN.RESERVATION WHERE DL_ID IN (%s) ORDER BY DLT_ID;"
#define	_SEL_ALL_RES_DL  "SELECT * FROM TDBADMIN.RESERVATION WHERE DL_ID IN (%s) ORDER BY DLT_ID, PERS_ID;"
#define	_SEL_ALL_RES_DL_DAT  "SELECT * FROM TDBADMIN.RESERVATION \
	WHERE DL_ID IN (%s) AND (A_ZEIT > %d AND A_ZEIT < %d) \
	ORDER BY DLT_ID, PERS_ID;"
#define	_SEL_ALL_KON	"SELECT * FROM TDBADMIN.KONTINGENT ORDER BY KONT_ID;"
#define	_SEL_ALL_GRA	"SELECT * FROM TDBADMIN.GRAPHIK ORDER BY GRA_ID;"
#define	_SEL_ALL_PCX	"SELECT * FROM TDBADMIN.PCX_FILES ORDER BY PCX_ID;"
#define	_SEL_ALL_BEZ	"SELECT * FROM TDBADMIN.BEZEICHNUNG WHERE S_ID=%hd AND TYP=%hd ORDER BY BEZ_ID;"
#define	_SEL_ALL_TXT	"SELECT * FROM TDBADMIN.TEXTE WHERE S_ID=%hd AND TYP=%hd ORDER BY TEXTID,TEXTNR;"
#define	_SEL_ALL_SPR	"SELECT * FROM TDBADMIN.SPRACHEN ORDER BY S_ID;"
#define	_SEL_ONE_SPRACHE	"SELECT * FROM TDBADMIN.SPRACHEN WHERE S_ID = %d;"
#define	_SEL_ALL_PLA	"SELECT * FROM TDBADMIN.PLAETZE WHERE DLT_ID=%d;"
#define	_SEL_ALL_LAB	"SELECT * FROM TDBADMIN.LABEL WHERE S_ID = %d ORDER BY LABEL_PRG, LABEL_TYP, STUFE1, STUFE2;"








/* DIENST_ANGEBOT  Auswahl aller Dienstleistungsangebote */
#define	_SEL_BEZ_DLA "SELECT D.DLA_ID, B.S_ID, B.BEZ, D.ORD \
	FROM TDBADMIN.BEZEICHNUNG B , TDBADMIN.DIENST_ANGEBOT D \
	WHERE B.BEZ_ID = D.BEZ_ID AND B.S_ID=%d AND B.TYP=%d AND D.DLA_ID > -1 \
	ORDER BY B.BEZ;"

/* DIENST_ANGEBOT  Auswahl nach Dienstleistung */
#define _SEL_BEZ_DLA_DL "SELECT DLA.DLA_ID, B.S_ID, \
	B.BEZ, DLA.ORD \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.DIENST_ANGEBOT DLA, TDBADMIN.DLG_PARTS TDL, TDBADMIN.DLG_DLG DD \
	WHERE DD.DLG_ID = %d AND TDL.DL_ID = DD.DL_ID \
	AND DLA.DLA_ID = TDL.DLA_ID AND B.BEZ_ID = DLA.BEZ_ID \
	AND B.S_ID = %d AND B.TYP = %d ORDER BY B.BEZ;"

/* DIENST_ANGEBOT  Auswahl nach Dienstleistungstr�ger */
#define	_SEL_BEZ_DLA_DLT	"SELECT DLA.DLA_ID, B.S_ID, B.BEZ, DLA.ORD \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE B.BEZ_ID=DLA.BEZ_ID \
	AND B.S_ID=%d  \
	AND B.TYP=%d \
	AND DLA.DLT_ID=%d \
	ORDER BY B.BEZ;"

/* DIENST_ANGEBOT  Auswahl nach Angebotstyp */
#define	_SEL_BEZ_DLA_DLAT	"SELECT DLA.DLA_ID, B.S_ID, B.BEZ, DLA.ORD \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE B.BEZ_ID=DLA.BEZ_ID \
	AND B.S_ID=%d  \
	AND B.TYP=%d \
	AND DLA.ART_ID=%d \
	ORDER BY B.BEZ;"

/* DIENST_ANGEBOT  alle Hosteintr�ge */
#define	_SEL_BEZ_DLA1	"SELECT DLA.DLA_ID, B.S_ID, B.BEZ, DLA.ORD \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE B.BEZ_ID=DLA.BEZ_ID \
	AND DLA.H_DLA_ID = -1 \
	AND DLA.DLA_ID > -1 \
	AND B.S_ID=%d  \
	AND B.TYP=%d \
	ORDER BY B.BEZ;"

/* DIENST_ANGEBOT  alle Hosteintr�ge nach Dienstleistungstr�ger */
#define	_SEL_BEZ_DLA_DLT1	"SELECT DLA.DLA_ID, B.S_ID, \
	B.BEZ, DLA.ORD \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE B.BEZ_ID=DLA.BEZ_ID \
	AND DLA.H_DLA_ID = -1 \
	AND B.S_ID=%d  \
	AND B.TYP=%d \
	AND DLA.DLT_ID=%d \
	ORDER BY B.BEZ;"

/* DIENST_ANGEBOT  alle Hosteintr�ge nach Angebot */
#define	_SEL_BEZ_DLA_DLAT1 "SELECT DLA.DLA_ID, B.S_ID, \
	B.BEZ, DLA.ORD \
	FROM TDBADMIN.BEZEICHNUNG B, TDBADMIN.DIENST_ANGEBOT DLA \
	WHERE B.BEZ_ID=DLA.BEZ_ID \
	AND DLA.H_DLA_ID = -1 \
	AND B.S_ID=%d  \
	AND B.TYP=%d \
	AND DLA.ART_ID=%d \
	ORDER BY B.BEZ;"
