set head off
set linesize 500
set numwidth 11
set colsep ""
set pagesize 20000
set echo off

SPOOL mpul_1
select * from ROOT.MAXIMA;
SPOOL OFF

SPOOL mpul_2 
select * from ROOT.SPRACHEN;
SPOOL OFF

SPOOL mpul_3
select * from ROOT.BEZEICHNUNG;
SPOOL OFF

SPOOL mpul_4
select sta_id, abk, sta, bez_id, TO_CHAR(kond,'999999999999999.9999999'), typ from ROOT.STATUS_WERTE;
SPOOL OFF

SPOOL mpul_5
select * from ROOT.TEXTE;
SPOOL OFF

SPOOL mpul_9
select * from ROOT.TMP_TEXTE;
SPOOL OFF

SPOOL mpul_6
select * from ROOT.TMP_BEZEICHNUNG;
SPOOL OFF

SPOOL mpul_7
select * from ROOT.AKTIONSTEXTE;
SPOOL OFF

SPOOL mpul_8
select * from ROOT.HISTORY;
SPOOL OFF

SPOOL mpul_10
select * from ROOT.HELP;
SPOOL OFF

SPOOL mpul_12
select * from ROOT.MSG;
SPOOL OFF

SPOOL mpul_11
select * from ROOT.LABEL;
SPOOL OFF

SPOOL mpul_13
select * from ROOT.SAISON;
SPOOL OFF

SPOOL mpul_14
select * from ROOT.WAEHRUNG;
SPOOL OFF

SPOOL mpul_15
select * from ROOT.LAND;
SPOOL OFF

SPOOL mpul_16
select * from ROOT.ORT;
SPOOL OFF

SPOOL mpul_17
select * from ROOT.LAND_WHR;
SPOOL OFF

SPOOL mpul_18
select * from ROOT.LAND_SPR;
SPOOL OFF

SPOOL mpul_19
select * from ROOT.PERSONEN;
SPOOL OFF

SPOOL mpul_21
select * from ROOT.REISENDER_TYP;
SPOOL OFF

SPOOL mpul_20
select * from ROOT.REISENDER;
SPOOL OFF

SPOOL mpul_22
select * from ROOT.PERSADR;
SPOOL OFF

SPOOL mpul_23
select * from ROOT.KUNDEN_TYP;
SPOOL OFF

SPOOL mpul_24
select * from ROOT.KUNDEN;
SPOOL OFF

SPOOL mpul_25
select * from ROOT.KOLLEKTIV_TYP;
SPOOL OFF

SPOOL mpul_26
select * from ROOT.KOLLEKTIV;
SPOOL OFF

SPOOL mpul_27
select * from ROOT.TRAEGER_TYP;
SPOOL OFF

SPOOL mpul_28
select * from ROOT.KATEGORIE;
SPOOL OFF

SPOOL mpul_29
select * from ROOT.DIENST_TRAEGER;
SPOOL OFF

SPOOL mpul_30
select * from ROOT.ANGEBOTS_TYP;
SPOOL OFF

SPOOL mpul_31
select * from ROOT.AKTIONS_TYP;
SPOOL OFF

SPOOL mpul_32
select * from ROOT.AKTIONSPARA;
SPOOL OFF

SPOOL mpul_33
select * from ROOT.AKTIONEN;
SPOOL OFF

SPOOL mpul_34
select * from ROOT.AKTIONSGRP;
SPOOL OFF

SPOOL mpul_35
select * from ROOT.DIENST_ANGEBOT;
SPOOL OFF

SPOOL mpul_36
select * from ROOT.DLG_PARTS;
SPOOL OFF

SPOOL mpul_37
select * from ROOT.DIENSTLEISTUNG;
SPOOL OFF

SPOOL mpul_38
select * from ROOT.DLG_DLG;
SPOOL OFF

SPOOL mpul_39
select * from ROOT.PROGRAMM;
SPOOL OFF

SPOOL mpul_40
select * from ROOT.ARRANGEMENT;
SPOOL OFF

SPOOL mpul_41
select * from ROOT.ARR_DLG;
SPOOL OFF

SPOOL mpul_42
select * from ROOT.HOST_KONT;
SPOOL OFF

SPOOL mpul_43
select * from ROOT.KONTINGENT;
SPOOL OFF

SPOOL mpul_44
select * from ROOT.KONT_DETAIL;
SPOOL OFF

SPOOL mpul_58
select * from ROOT.MP_PROFIL;
SPOOL OFF

SPOOL mpul_45
select * from ROOT.BUCHUNG;
SPOOL OFF

SPOOL mpul_46
select * from ROOT.BCH_DLN;
SPOOL OFF

SPOOL mpul_47
select * from ROOT.AKT_DETAIL;
SPOOL OFF

SPOOL mpul_48
select * from ROOT.KOSTEN_ART;
SPOOL OFF

SPOOL mpul_49
select * from ROOT.KOMMISSION;
SPOOL OFF

SPOOL mpul_50
select * from ROOT.KOMM_DETAIL;
SPOOL OFF

SPOOL mpul_51
select * from ROOT.RESERVATION;
SPOOL OFF

SPOOL mpul_52
select pre_id, 
TO_CHAR(apr,'999999999999999.9999999'),
TO_CHAR(epr,'999999999999999.9999999'),
TO_CHAR(vpr,'999999999999999.9999999'),
glt, WHR_ID, KBST, KAR_ID, DLTT_ID, KAT_ID,
RKR_ID, DLA_ID, DL_ID, DL_VONDAT, DL_BISDAT,
KONT_ID, STA_ID, TEXTID, HISTORY, SAI_ID
from ROOT.PREIS;
SPOOL OFF

SPOOL mpul_53
select * from ROOT.KAPA;
SPOOL OFF

SPOOL mpul_59
select * from ROOT.MP_ARRKOM;
SPOOL OFF

SPOOL mpul_54
select * from ROOT.GRAPHIK;
SPOOL OFF

SPOOL mpul_55
select * from ROOT.PCX_FILES;
SPOOL OFF

SPOOL mpul_56
select * from ROOT.GRAFORM;
SPOOL OFF

SPOOL mpul_57
select * from ROOT.REGIONS;
SPOOL OFF

COMMIT WORK;
