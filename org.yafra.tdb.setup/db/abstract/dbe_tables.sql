/*DSQL***********************************************************************/
/*  Copyright 2002 yafra.org                                                */
/*                                                                          */
/*  Licensed under the Apache License, Version 2.0 (the "License");         */
/*  you may not use this file except in compliance with the License.        */
/*  You may obtain a copy of the License at                                 */
/*                                                                          */
/*      http://www.apache.org/licenses/LICENSE-2.0                          */
/*                                                                          */
/*  Unless required by applicable law or agreed to in writing, software     */
/*  distributed under the License is distributed on an "AS IS" BASIS,       */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*/
/*  See the License for the specific language governing permissions and     */
/*  limitations under the License.                                          */
/*                                                                          */
/* project:   TDB                                                           */
/*                                                                          */
/* DBMS:      abstract                                                      */
/*                                                                          */
/* function:  create tables                                                 */
/****************************************************************************/
/* SCM Information: */
/* $Header: $ */

drop table mp_debitor;
drop table mp_kreditor;
drop table mp_reminder;
drop table mp_param;

drop table graform;
drop table graphik;
drop table regions;
drop table pcx_files;

drop table mp_kol_pers;
drop table mp_kapa;
drop table kapa;
drop table preis;
drop table mp_gemein_res;
drop table reservation;
drop table komm_detail;
drop table mp_arrkom;
drop table kommission;
drop table kosten_art;
drop table akt_detail;
drop table mp_bch_dlg;
drop table bch_dln;
drop table buchung;

drop table mp_preferences;
drop table mp_profil;

drop table kont_detail;
drop table kontingent;
drop table host_kont;

drop table arr_dlg;
drop table arrangement;
drop table programm;
drop table dlg_dlg;
drop table dienstleistung;
drop table dlg_parts;
drop table dienst_angebot;
drop table aktionsgrp;
drop table aktionen;
drop table aktionspara;
drop table aktions_typ;
drop table angebots_typ;
drop table traeger_detail;
drop table dienst_traeger;
drop table kategorie;
drop table traeger_typ;

drop table kollektiv;
drop table kollektiv_typ;
drop table persadr;
drop table reisender;
drop table reisender_typ;
drop table kunden;
drop table kunden_typ;
drop table personen;

drop table mp_prox;
drop table land_spr;
drop table land_whr;
drop table ort;
drop table land;
drop table waehrung;

drop table mp_file;
drop table saison;
drop table msg;
drop table mp_label;
drop table label;
drop table help;
drop table status_werte;
drop table bezeichnung;
drop table tmp_bezeichnung; 
drop table history;
drop table mp_texte;
drop table mp_text_doc;
drop table mp_multimedia;
drop table aktionstexte;
drop table texte;
drop table tmp_texte;
drop table sprachen;
drop table maxima;
drop table tdb_version;

/*********************************************************/
/* CODEs - INTERNALS - TEXTE/BEZ                         */
/*********************************************************/

/* TDB Version Table */
create table tdb_version (
DBVERSION integer NOT NULL,
DBDATE    datetime NOT NULL,
primary key (DBVERSION)
);

/* MAXIMA Tabelle 0 */
create table maxima (
TABELLE	integer NOT NULL,
TYP		integer NOT NULL,
MAX_ID	integer NULL,
MIN_ID   integer NULL,
INCR		integer NULL,
primary key (TABELLE, TYP)
);



/* SPRACHEN Tabelle 1 */
create table sprachen (
S_ID		integer	NOT NULL,
BEZ_ID	integer	NOT NULL unique,
DIALOG	integer	NOT NULL,
SYSBEZ	varchar(256) NOT NULL,
OUTPUT	integer	NULL,
GUI		integer	NULL,
primary key (S_ID)
);


/* STATUS_WERTE Tabelle 2  */
create table status_werte (
STA_ID	integer	NOT NULL,
ABK		varchar(256)	NOT NULL,
STA		varchar(1024)	NOT NULL,
BEZ_ID	integer	NOT NULL,
KOND		float		NOT NULL,
TYP		integer	NOT NULL,
primary key (STA_ID, TYP)
);



/* BEZEICHNUNG Tabelle 3 */
create table bezeichnung (
BEZ_ID	integer	NOT NULL,
S_ID		integer	NOT NULL,
BEZ		varchar(1024)	NOT NULL,
TYP		integer	NOT NULL,
primary key (BEZ_ID, S_ID, TYP),
foreign key (S_ID) references sprachen (S_ID)
);

/* TMP-BEZEICHNUNG Tabelle */
create table tmp_bezeichnung (
BEZ_ID	integer	NOT NULL,
S_ID		integer	NOT NULL,
BEZ		varchar(1024)	NOT NULL,
TYP		integer	NOT NULL
);


/* TEXTE Tabelle 4 */
create table texte (
TEXTID	integer	NOT NULL,
S_ID		integer	NOT NULL,
TEXTNR	integer	NOT NULL,
TEXT		varchar(1024)	NOT NULL,
TYP		integer	NOT NULL,
primary key (TEXTID, TEXTNR, S_ID, TYP),
foreign key (S_ID) references sprachen (S_ID)
);

/* TMP-TEXTE Tabelle */
create table tmp_texte (
TEXTID	integer	NOT NULL,
S_ID		integer	NOT NULL,
TEXTNR	integer	NOT NULL,
TEXT		varchar(1024)	NOT NULL,
TYP		integer	NOT NULL
);


/* AKTIONSTEXTE Tabelle 5 */
create table aktionstexte (
TEXTID	integer	NOT NULL,
S_ID		integer	NOT NULL,
TEXTNR	integer	NOT NULL,
TEXT		varchar(1024)	NOT NULL,
TYP		integer	NOT NULL,
primary key (TEXTID, TEXTNR, S_ID, TYP),
foreign key (S_ID) references sprachen (S_ID)
);

create table mp_multimedia (
MULT_ID	integer	NOT NULL,
MULT_TYP	integer	NULL,
S_ID	integer	NULL,
MULT	blob	NULL,
primary key (MULT_ID),
foreign key (S_ID) references sprachen (S_ID)
);

create table mp_text_doc (
TEXTID       integer	NOT NULL,
TYP          integer	NOT NULL,
MULT_ID      integer	NOT NULL,
primary key (TEXTID, TYP, MULT_ID),
foreign key (MULT_ID) references mp_multimedia (MULT_ID)
);

create table mp_texte (
TEXTID       integer	NOT NULL,
TYP          integer	NOT NULL,
S_ID         integer	NOT NULL,
TEXT         varchar(1024)	NOT NULL,
primary key (TEXTID, TYP, S_ID),
foreign key (S_ID) references sprachen (S_ID)
);

/* HISTORY Tabelle 52 */
create table history (
HIS_ID	integer	NOT NULL,
S_ID		integer	NOT NULL,
TEXTNR	integer	NOT NULL,
TEXT		varchar(1024)	NOT NULL,
DAT		bigint	NOT NULL,
TYP		integer	NOT NULL,
primary key (HIS_ID, TEXTNR, S_ID),
foreign key (S_ID) references sprachen (S_ID)
);


/* HELP Tabelle 6 */
create table help (
HELP_TYP	integer	NOT NULL,
HELP_ID	integer  NOT NULL,
S_ID		integer	NOT NULL,
TEXTNR	integer  NOT NULL,
TEXT		varchar(1024) NOT NULL,
primary key (HELP_TYP, HELP_ID, S_ID, TEXTNR),
foreign key (S_ID) references sprachen (S_ID)
);


/* MSG Tabelle 7 */
create table msg (
MSG_TYP	integer	NOT NULL,
MSG_ID	integer  NOT NULL,
S_ID		integer	NOT NULL,
TEXTNR	integer  NOT NULL,
TEXT		varchar(1024) NOT NULL,
primary key (MSG_TYP, MSG_ID, S_ID, TEXTNR),
foreign key (S_ID) references sprachen (S_ID)
);


/* LABEL Tabelle 8 */
create table label (
LABEL_PRG	integer NOT NULL,
LABEL_TYP	integer NOT NULL,
STUFE1		integer NOT NULL,
STUFE2		integer NOT NULL,
S_ID			integer NOT NULL,
LABEL			varchar(1024) NOT NULL,
primary key (LABEL_PRG, LABEL_TYP, STUFE1, STUFE2, S_ID),
foreign key (S_ID) references sprachen (S_ID)
);


create table mp_label (
LABEL_ID     integer	NOT NULL,
SEC_ID       integer	NOT NULL,
LABEL_TYP    integer	NOT NULL,
S_ID         integer	NOT NULL,
LABEL        varchar(1024)	NOT NULL,
primary key (LABEL_ID, SEC_ID, LABEL_TYP, S_ID),
foreign key (S_ID) references sprachen (S_ID)
);


/* SAISON Tabelle 9 */
create table saison (
SAI_ID	integer	NOT NULL,
CODE		varchar(256) NULL,
BEZ_ID	integer	NOT NULL unique,
VON		bigint	NOT NULL,
BIS		bigint	NOT NULL,
TEXTID	integer  NULL,
primary key (SAI_ID)
);


/* FILE table id 00 */
create table mp_file (
FILE_ID      integer			NOT NULL,
CODE         varchar(256)	NULL,
FILE_TYP     integer			NULL,
LABEL_ID     integer			NULL,
FILENAME     varchar(1024)	NULL,
primary key (FILE_ID)
);


/**********************************************/
/* GEOGRAPHIE                                 */
/**********************************************/

/* WAEHRUNG Tabelle 12 */
create table waehrung (
WHR_ID		integer	NOT NULL,
BEZ_ID		integer  NOT NULL unique,
TEXTID		integer  NULL,
STATUS		integer  NULL,
KRZL			varchar(256) NULL,
primary key (WHR_ID)
);


/* LAND Tabelle 10 */
create table land (
LAND_ID		integer	NOT NULL,
BEZ_ID		integer NOT NULL unique,
TEXTID		integer NULL,
KRZL			varchar(256) NULL,
HAUPT_ORT	integer NULL,
HAUPT_WHR	integer NULL,
HAUPT_SPR	integer NULL,
VAT			float NULL,
DATEFORMAT	varchar(256) NULL,
primary key (LAND_ID),
foreign key (HAUPT_WHR) references waehrung (WHR_ID),
foreign key (HAUPT_SPR) references sprachen (S_ID)
);


/* ORT Tabelle 11 */
create table ort (
ORT_ID		integer  NOT NULL,
BEZ_ID		integer  NOT NULL unique,
LAND_ID		integer	NOT NULL,
TEXTID		integer  NULL,
KRZL			varchar(256) NULL,
ZEITVER		integer  NULL,
KOORD1		integer  NULL,
KOORD2		integer  NULL,
ORT_TYP		integer  NULL,
primary key (ORT_ID),
foreign key (LAND_ID) references land (LAND_ID)
);


/* LAND_WHR Tabelle 13 */
create table land_whr (
LAND_ID		integer	NOT NULL,
WHR_ID		integer	NOT NULL,
KURS_TYP		integer	NOT NULL,
A_KURS		float		NOT NULL,
V_KURS		float		NOT NULL,
VON_DAT		bigint	NULL,
primary key (LAND_ID, WHR_ID, KURS_TYP),
foreign key (LAND_ID) references land (LAND_ID),
foreign key (WHR_ID) references waehrung (WHR_ID)
);


/* LAND_SPR Tabelle 14 */
create table land_spr (
LAND_ID		integer NOT NULL,
S_ID			integer NOT NULL,
primary key (LAND_ID, S_ID),
foreign key (LAND_ID) references land (LAND_ID),
foreign key (S_ID) references sprachen (S_ID)
);


create table mp_prox (
ORT_ID       integer	NOT NULL,
PROX_ID      integer	NOT NULL,
primary key (ORT_ID, PROX_ID)
);



/**********************************************/
/* PERSONEN STAMM  (KUNDEN, REISENDE)         */
/**********************************************/

/* PERSONEN Tabelle 34 */
create table personen (
PERS_ID		integer	NOT NULL,
PERS_TYP		integer  NOT NULL,
NAME			varchar(512)	NOT NULL,
S_ID			integer	NOT NULL,
STA_ID		integer  NULL,
TEXTID      integer  NULL,
primary key (PERS_ID),
foreign key (S_ID) references sprachen (S_ID)
);

/* DLN_TYP Tabelle 35 */
create table reisender_typ (
RKR_ID		integer	NOT NULL,
DLNCODE     varchar(256) NULL,
BEZ_ID		integer	NOT NULL unique,
VONALTER		integer  NULL,
BISALTER		integer  NULL,
TEXTID		integer  NULL,
primary key (RKR_ID)
);


/* DLN Tabelle 36 */
create table reisender (
PERS_ID	integer	NOT NULL unique,
VOR		varchar(512)	NOT NULL,
RKR_ID	integer	NOT NULL,
SEX		integer  NULL,
MUTTERS_ID	integer  NULL,
AGE		varchar(256)  NULL,
PASSNR   varchar(256)  NULL,
ATTR1    varchar(1024)  NULL,
ATTR2    varchar(1024)  NULL,
TEXTID	integer  NULL,
foreign key (PERS_ID) references personen (PERS_ID),
foreign key (RKR_ID) references reisender_typ (RKR_ID)
);


/* PERSADR Tabelle 37 */
create table persadr (
PERS_ID	integer NOT NULL unique,
ADR_TYP	integer	NOT NULL,
ANS		varchar(256)  NULL,
ADR1		varchar(1024)  NULL,
ADR2		varchar(1024)  NULL,
ADR3		varchar(1024)  NULL,
PLZ		varchar(256)  NULL,
ORT		varchar(256)  NULL,
KANT		varchar(256)  NULL,
LAND_ID	integer  NULL,
STA_ID	integer  NULL,
HAUPT_FLAG	integer  NULL,
RCH_FLAG	integer  NULL,
MAIL_FLAG	integer  NULL,
TEL		varchar(256)  NULL,
HANDY		varchar(256)  NULL,
FAX		varchar(256)  NULL,
TLX		varchar(256)  NULL,
EMAIL		varchar(1024)  NULL,
WEB		varchar(1024)  NULL,
primary key (PERS_ID, ADR_TYP),
foreign key (PERS_ID) references personen (PERS_ID)
);


/* KUNDENTYP Tabelle 24 */
create table kunden_typ (
K_TYP_ID		integer	NOT NULL,
KUNCODE     varchar(256)  NULL,
BEZ_ID		integer	NOT NULL unique,
TEXTID		integer  NULL,
primary key (K_TYP_ID)
);


/* KUNDEN Tabelle  25 */
create table kunden (
PERS_ID	integer	NOT NULL unique,
TEL		varchar(256)  NULL,
HANDY		varchar(256)  NULL,
FAX		varchar(256)  NULL,
TLX		varchar(256)  NULL,
EMAIL		varchar(1024)  NULL,
WEB		varchar(1024)  NULL,
KONTO		varchar(256)  NULL,
LEITER	integer	NULL,
ATTR1    varchar(1024)  NULL,
ATTR2    varchar(1024)  NULL,
K_TYP_ID	integer	NOT NULL,
WHR_ID	integer	NOT NULL,
foreign key (PERS_ID) references personen (PERS_ID),
foreign key (K_TYP_ID) references kunden_typ (K_TYP_ID),
foreign key (WHR_ID) references waehrung (WHR_ID)
);


/* KOLLEKTIVTYP Tabelle 32 */
create table kollektiv_typ (
K_TYP_ID		integer	NOT NULL,
KOLCODE     varchar(256)  NULL,
BEZ_ID		integer	NOT NULL unique,
TEXTID		integer  NULL,
primary key (K_TYP_ID)
);


/* KOLLEKTIV Tabelle  33 */
create table kollektiv (
K_ID			integer	NOT NULL,
REF			varchar(256) NULL,
NAME			varchar(512) NULL unique,
K_TYP_ID		integer	NOT NULL,
KBST			integer	NOT NULL,
K_STA			integer  NULL,
HAUPTPERS	integer  NULL,
KID			integer  NULL,
TEXTID		integer  NULL,
primary key (K_ID),
foreign key (K_TYP_ID) references kollektiv_typ (K_TYP_ID),
foreign key (KBST) references personen (PERS_ID),
foreign key (HAUPTPERS) references personen (PERS_ID),
foreign key (KID) references personen (PERS_ID)
);



/**********************************************/
/* RESERVATIONSKERN  (TRAEGER, ANGEBOT)       */
/**********************************************/

/* TRAEGERTYP Tabelle 15 */
create table traeger_typ (
TYP_ID		integer	NOT NULL,
BEZ_ID		integer	NOT NULL unique,
H_TYP_ID		integer	NOT NULL,
HOST_TYP		integer	NOT NULL,
TEXTID		integer  NULL,
primary key (TYP_ID)
);

/* KATEGORIE Tabelle  16 */
create table kategorie (
KAT_ID		integer	NOT NULL,
BEZ_ID		integer	NOT NULL unique,
H_KAT_ID		integer  NULL,
TYP_ID		integer	NOT NULL,
GA				integer  NULL,
TEXTID		integer  NULL,
primary key (KAT_ID),
foreign key (TYP_ID) references traeger_typ (TYP_ID)
);

/* DIENSTLEISTUNGSTRAEGER Tabelle 17 */
create table dienst_traeger (
DLT_ID		integer	NOT NULL,
CODE			varchar(256) NULL,
BEZ_ID		integer	NOT NULL,
KAT_ID		integer  NULL,
H_DLT_ID		integer	NOT NULL,
DLT_GRP_ID	integer	NOT NULL,
HOST_ID		integer	NOT NULL,
TYP_ID		integer	NOT NULL,
TEXTID		integer  NULL,
STUFE			integer	NOT NULL,
STA_ID      integer  NULL,
ANZ			INTEGER	NULL,
primary key (DLT_ID),
foreign key (TYP_ID) references traeger_typ (TYP_ID),
foreign key (KAT_ID) references kategorie (KAT_ID)
);


create table traeger_detail (
DLT_ID       integer	NOT NULL,
FIRMA        integer	NOT NULL,
primary key (DLT_ID, FIRMA),
foreign key (DLT_ID) references dienst_traeger (DLT_ID),
foreign key (FIRMA) references personen (PERS_ID)
);

/* see graphic section for graphic tables */

/* ANGEBOTSTYP Tabelle 18 */
create table angebots_typ (
ART_ID		integer	NOT NULL,
BEZ_ID		integer	NOT NULL unique,
TEXTID		integer  NULL,
primary key (ART_ID)
);


/* AKTIONSTYP Tabelle 19 */
create table aktions_typ (
A_TYP_ID		integer	NOT NULL,
BEZ_ID		integer	NOT NULL unique,
PROZ			varchar(1024) NOT NULL,
TEXTID		integer  NULL,
primary key (A_TYP_ID)
);


/* AKTIONSPARA Tabelle 20 */
create table aktionspara (
A_TYP_ID		integer	NOT NULL,
NR				integer	NOT NULL,
TYP			integer  NULL,
BEZ			varchar(1024) NOT NULL,
MUSS			integer  NULL,
FLAG			integer  NULL,
TEXTID		integer  NULL,
primary key (A_TYP_ID, NR),
foreign key (A_TYP_ID) references aktions_typ (A_TYP_ID)
);


/* AKTIONEN Tabelle 21 */
/* A_FLAG  Ausfuehrungsstatus */
/* B_FLAG  Ausfuehrung bei welchen Reservationsstatus */
/* B2_FLAG bei Erfolg setzen auf welchen Res.-Status  */
/* M_FLAG  Ausgabe auf welches Medium */
create table aktionen (
AKT_ID		integer	NOT NULL,
BEZ_ID		integer	NOT NULL unique,
TEXTID		integer  NULL,
A_FLAG		integer  NULL,
B_FLAG		integer  NULL,
M_FLAG		integer  NULL,
A_TYP_ID		integer	NOT NULL,
B2_FLAG		integer  NULL,
FILE_ID		integer	NULL,
primary key (AKT_ID),
foreign key (A_TYP_ID) references aktions_typ (A_TYP_ID),
foreign key (FILE_ID) references mp_file (FILE_ID)
);


/* AKTIONSGRP Tabelle 22 */
create table aktionsgrp (
PARENTAKT	integer	NOT NULL,
CHILDAKT		integer	NOT NULL,
ORD			integer	NOT NULL,
H_AKT_ID		integer	NOT NULL,
primary key (PARENTAKT, CHILDAKT, ORD),
foreign key (PARENTAKT) references aktionen (AKT_ID),
foreign key (CHILDAKT) references aktionen (AKT_ID),
foreign key (H_AKT_ID) references aktionen (AKT_ID)
);


/* DIENSTLEISTUNGSANGEBOT Tabelle 23 */
create table dienst_angebot (
DLA_ID	integer	NOT NULL,
CODE		varchar(256) NULL,
H_DLA_ID	integer	NOT NULL,
ORD		integer	NOT NULL,
DLT_ID	integer	NOT NULL,
BEZ_ID	integer	NOT NULL unique,
AKT_ID	integer	NOT NULL,
ORT		varchar(256)	NOT NULL,
ART_ID	integer	NOT NULL,
DAU		integer  NULL,
TEXTID	integer  NULL,
VON		integer	NOT NULL,
NACH		integer	NOT NULL,
primary key (DLA_ID),
foreign key (DLT_ID) references dienst_traeger (DLT_ID),
foreign key (AKT_ID) references aktionen (AKT_ID),
foreign key (ART_ID) references angebots_typ (ART_ID),
foreign key (VON) references ort (ORT_ID),
foreign key (NACH) references ort (ORT_ID)
);


/* DLG_PART service parts table ID 26 */
create table dlg_parts (
DL_ID		integer	NOT NULL,
CODE		varchar(256) NULL,
BEZ_ID	integer	NOT NULL,
H_DL_ID	integer	NOT NULL,
DLA_ID	integer	NOT NULL,
ORD		integer  NULL,
A_ZEIT	bigint  NULL,
E_ZEIT	bigint  NULL,
RES_F		integer	NOT NULL,
KID		integer  NULL,
KONTO		varchar(256)  NULL,
TEXTID	integer  NULL,
SAI_ID	integer	NOT NULL,
RECHST	integer  NULL,
primary key (DL_ID),
foreign key (DLA_ID) references dienst_angebot (DLA_ID),
foreign key (KID) references personen (PERS_ID),
foreign key (RECHST) references personen (PERS_ID),
foreign key (SAI_ID) references saison (SAI_ID)
);


/* DIENSTLEISTUNG service table ID 27 */
create table dienstleistung (
DLG_ID		integer	NOT NULL,
CODE			varchar(256) NULL,
BEZ_ID		integer	NOT NULL,
TEXTID		integer  NULL,
SAI_ID		integer	NOT NULL,
A_ZEIT		bigint  NULL,
AKT_ID		integer  NULL,
primary key (DLG_ID),
foreign key (SAI_ID) references saison (SAI_ID),
foreign key (AKT_ID) references aktionen (AKT_ID)
);


/* DLG_DLG joining services and service parts table ID 28 */
create table dlg_dlg (
DLG_ID	integer	NOT NULL,
DL_ID		integer	NOT NULL,
ORD		integer	NOT NULL,
primary key (DLG_ID, DL_ID),
foreign key (DLG_ID) references dienstleistung (DLG_ID),
foreign key (DL_ID) references dlg_parts (DL_ID)
);


/* PROGRAMM Tabelle 29 */
create table programm (
PRG_ID		integer	NOT NULL,
CODE			varchar(256) NULL,
BEZ_ID		integer	NOT NULL unique,
TEXTID		integer  NULL,
SAI_ID		integer	NOT NULL,
primary key (PRG_ID),
foreign key (SAI_ID) references saison (SAI_ID)
);


/* ARRANGEMENT Tabelle 30 */
create table arrangement (
ARR_ID		integer	NOT NULL,
CODE			varchar(256) NULL,
BEZ_ID		integer	NOT NULL,
A_DAT 		bigint	NOT NULL,
PRG_ID		integer	NOT NULL,
TEXTID		integer  NULL,
SAI_ID		integer	NOT NULL,
primary key (ARR_ID),
foreign key (PRG_ID) references programm (PRG_ID),
foreign key (SAI_ID) references saison (SAI_ID)
);


/* ARR_DLG Tabelle 31 */
create table arr_dlg (
ARR_ID		integer	NOT NULL,
TEIL			integer	NOT NULL,
PRIO			integer	NOT NULL,
DLG_ID		integer	NOT NULL,
primary key (ARR_ID, TEIL, DLG_ID),
foreign key (ARR_ID) references arrangement (ARR_ID),
foreign key (DLG_ID) references dienstleistung (DLG_ID)
);





/**********************************************/
/* KONTINGENTIERUNG                           */
/**********************************************/

/* HOST_KONT Tabelle 38 */
create table host_kont (
HOSTKONT_ID	integer	NOT NULL,
BEZ_ID		integer	NOT NULL unique,
FROM_PERS	integer	NOT NULL,
KBST			integer	NOT NULL,
DLA_ID 		integer  NULL,
DL_ID 		integer  NULL,
DL_VONDAT	bigint  NULL,
DL_BISDAT	bigint  NULL,
TEXTID		integer  NULL,
OPT_DAT		bigint  NULL,
SAI_ID		integer	NOT NULL,
REF			varchar(256)  NULL,
HISTORY		integer  NULL,
primary key (HOSTKONT_ID),
foreign key (FROM_PERS) references personen (PERS_ID),
foreign key (KBST) references personen (PERS_ID),
foreign key (DLA_ID) references dienst_angebot (DLA_ID),
foreign key (DL_ID) references dienstleistung (DLG_ID),
foreign key (SAI_ID) references saison (SAI_ID)
);


/* KONTINGENT Tabelle 39 */
create table kontingent (
KONT_ID		integer	NOT NULL,
BEZ_ID		integer	NOT NULL unique,
HOSTKONT_ID	integer	NOT NULL,
KUNDEN_ID	integer	NOT NULL,
OPT_DAT		bigint  NULL,
REF			varchar(256)  NULL,
SAI_ID		integer	NOT NULL,
TEXTID		integer  NULL,
primary key (KONT_ID),
foreign key (HOSTKONT_ID) references host_kont (HOSTKONT_ID),
foreign key (KUNDEN_ID) references personen (PERS_ID),
foreign key (SAI_ID) references saison (SAI_ID)
);


/* KONT_DETAIL Tabelle 40 */
/* entweder auf HOSTKONT_ID oder auf KONT_ID */
create table kont_detail (
HOSTKONT_ID	integer	NOT NULL,
KONT_ID		integer	NOT NULL,
KAT_ID		integer	NOT NULL,
DLT_ID 		integer	NOT NULL,
STA_ID		integer  NULL,
ANZ			integer  NULL,
BUSY			integer  NULL,
MINANZ		integer  NULL,
VON_DAT 		bigint	NOT NULL,
BIS_DAT 		bigint	NOT NULL,
primary key (HOSTKONT_ID, KONT_ID, KAT_ID, DLT_ID, VON_DAT, BIS_DAT),
foreign key (HOSTKONT_ID) references host_kont (HOSTKONT_ID),
foreign key (KONT_ID) references kontingent (KONT_ID),
foreign key (KAT_ID) references kategorie (KAT_ID),
foreign key (DLT_ID) references dienst_traeger (DLT_ID)
);




/********************************************************/
/* PROFIL / META                                        */
/********************************************************/

/* Profil Tabelle 55  (15 Felder) */
create table mp_profil (
MPID		integer	NOT NULL,
MPUSER	varchar(128)	NOT NULL,
BCHST		integer	NOT NULL,
SECLEVEL	integer	NOT NULL,
S_ID		integer	NOT NULL,
LAND_ID	integer	NOT NULL,
DLTT_ID	integer	NOT NULL,
DLT_ID	integer	NOT NULL,
KAT_ID	integer	NOT NULL,
DLAT_ID	integer	NOT NULL,
DLNT_ID	integer	NOT NULL,
SAI_ID	integer	NOT NULL,
PRG_ID	integer	NOT NULL,
A_ZEIT	bigint	NOT NULL,
E_ZEIT	bigint	NOT NULL,
P_RANGE	integer	NOT NULL,
primary key (MPID),
foreign key (BCHST) references personen (PERS_ID),
foreign key (S_ID) references sprachen (S_ID),
foreign key (LAND_ID) references land (LAND_ID),
foreign key (DLTT_ID) references traeger_typ (TYP_ID),
foreign key (DLT_ID) references dienst_traeger (DLT_ID),
foreign key (KAT_ID) references kategorie (KAT_ID),
foreign key (DLAT_ID) references angebots_typ (ART_ID),
foreign key (DLNT_ID) references reisender_typ (RKR_ID),
foreign key (SAI_ID) references saison (SAI_ID),
foreign key (PRG_ID) references programm (PRG_ID),
constraint MPUSERUNIQUE unique (BCHST, MPUSER)
);

create table mp_preferences (
MPID         integer NOT NULL unique,
FULLNAME     varchar(1024)	NULL,
FILTER       varchar(1024)	NULL,
GUI          varchar(1024)	NULL,
CUSTOM       varchar(1024)	NULL,
foreign key (MPID) references mp_profil (MPID)
);



/**********************************************/
/* RESERVATION - BUCHUNG - PREIS              */
/**********************************************/

/* BUCHUNGS Tabelle 41 */
create table buchung (
D_BID			integer	NOT NULL,
BID			integer	NOT NULL,
REF			varchar(256)	NOT NULL unique,
ARR_ID		integer	NOT NULL,
KID			integer	NOT NULL,
SACH			integer	NOT NULL,
ANW			integer	NOT NULL,
B_DAT			bigint  NULL,
M_DAT			bigint  NULL,
OPT_BST		integer  NULL,
OPT_KID		integer  NULL,
STA			integer	NOT NULL,
AST			integer	NOT NULL,
SAI_ID		integer	NOT NULL,
K_ID			integer	NOT NULL,
MPID			integer	NULL,
HISTORY		integer  NULL,
TEXTID		integer  NULL,
primary key (BID),
foreign key (ARR_ID) references arrangement (ARR_ID),
foreign key (KID) references personen (PERS_ID),
foreign key (SAI_ID) references saison (SAI_ID),
foreign key (MPID) references mp_profil (MPID),
foreign key (K_ID) references kollektiv (K_ID)
);


/* BCH_DLN Tabelle 53 */
create table bch_dln (
BID			integer	NOT NULL,
DLN_ID		integer	NOT NULL,
foreign key (BID) references buchung (BID),
foreign key (DLN_ID) references personen (PERS_ID)
);


create table mp_bch_dlg (
BID          integer	NOT NULL,
DLG_ID       integer	NOT NULL,
TEIL         integer	NOT NULL,
primary key (BID, TEIL),
foreign key (BID) references buchung (BID),
foreign key (DLG_ID) references dienstleistung (DLG_ID)
);


/* AKT_DETAIL Tabelle 42 */
create table akt_detail (
BID			integer	NOT NULL,
PERS_ID		integer	NOT NULL,
DLG_ID		integer	NOT NULL,
DL_ID			integer	NOT NULL,
TEIL			integer	NOT NULL,
AKT_ID		integer	NOT NULL,
ORD			integer	NOT NULL,
A_TYP_ID		integer	NOT NULL,
Z_FLAG		integer	NOT NULL,
AKT_NR		integer	NOT NULL,
SAI_ID		integer	NOT NULL,
PARENTAKT	integer	NOT NULL,
EXEC_DAT		bigint	NOT NULL,
FILE_ID		integer	NULL,
foreign key (PARENTAKT) references aktionen (AKT_ID),
foreign key (AKT_ID) references aktionen (AKT_ID),
foreign key (A_TYP_ID) references aktions_typ (A_TYP_ID),
foreign key (BID) references buchung (BID),
foreign key (PERS_ID) references personen (PERS_ID),
foreign key (SAI_ID) references saison (SAI_ID),
foreign key (DLG_ID) references dienstleistung (DLG_ID),
foreign key (DL_ID) references dlg_parts (DL_ID),
foreign key (FILE_ID) references mp_file (FILE_ID)
);


/* KOSTEN_ART Tabelle 43 */
create table kosten_art (
KAR_ID		integer	NOT NULL,
BEZ_ID		integer	NOT NULL unique,
TEXTID		integer  NULL,
primary key (KAR_ID)
);


/* KOMMISSION  Tabelle 44 */
create table kommission (
KOMM_ID		integer	NOT NULL,
BEZ_ID		integer	NOT NULL,
SATZ_ART    integer	NOT NULL,
SATZ   		float		NOT NULL,
KOMM_TYP		integer	NOT NULL,
KBST			integer	NOT NULL,
KAR_ID		integer  NULL,
DLTT_ID		integer  NULL,
KAT_ID		integer  NULL,
RKR_ID		integer  NULL,
DLA_ID		integer  NULL,
DL_ID			integer  NULL,
DL_VONDAT	bigint  NULL,
DL_BISDAT	bigint  NULL,
KONT_ID		integer  NULL,
BID			integer  NULL,
HISTORY		integer  NULL,
SAI_ID		integer	NOT NULL,
TEXTID		integer  NULL,
primary key (KOMM_ID),
foreign key (KBST) references personen (PERS_ID),
foreign key (KAR_ID) references kosten_art (KAR_ID),
foreign key (DLTT_ID) references traeger_typ (TYP_ID),
foreign key (KAT_ID) references kategorie (KAT_ID),
foreign key (RKR_ID) references reisender_typ (RKR_ID),
foreign key (DLA_ID) references dienst_angebot (DLA_ID),
foreign key (DL_ID) references dienstleistung (DLG_ID),
foreign key (KONT_ID) references kontingent (KONT_ID),
foreign key (BID) references buchung (BID),
foreign key (SAI_ID) references saison (SAI_ID)
);


/* MP_ARRKOM Tabelle 56 (3 Felder) */
create table mp_arrkom (
ARR_ID		integer	NOT NULL,
KOMM_ID		integer	NOT NULL,
KOMM_BEZID	integer	NOT NULL,
foreign key (ARR_ID) references arrangement (ARR_ID),
foreign key (KOMM_ID) references kommission (KOMM_ID)
);


/* KOMM_DETAIL Tabelle 45 */
create table komm_detail (
KOMM_ID		integer	NOT NULL,
BID			integer  NOT NULL,
DLN_ID		integer	NOT NULL,
KUN_ID		integer	NOT NULL,
KOL_ID		integer	NOT NULL,
PRIO			integer  NULL,
foreign key (KOMM_ID) references kommission (KOMM_ID),
foreign key (BID) references buchung (BID),
foreign key (DLN_ID) references personen (PERS_ID),
foreign key (KUN_ID) references personen (PERS_ID),
foreign key (KOL_ID) references kollektiv (K_ID)
);


/* RESERVATIONS Tabelle 46 */
create table reservation (
PERS_ID		integer	NOT NULL,
DLG_ID		integer 	NOT NULL,
DL_ID			integer 	NOT NULL,
TEIL			integer	NOT NULL,
DLT_ID		integer 	NOT NULL,
TYP_ID		integer	NOT NULL,
BID			integer	NOT NULL,
KONT_ID		integer	NOT NULL,
KAT_ID		integer	NOT NULL,
K_KON			integer  NULL,
B_KON			integer  NULL,
R_STA			integer	NOT NULL,
SAI_ID		integer	NOT NULL,
A_ZEIT		bigint  NULL,
E_ZEIT		bigint  NULL,
TEXTID		integer  NULL,
foreign key (PERS_ID) references personen (PERS_ID),
foreign key (DLG_ID) references dienstleistung (DLG_ID),
foreign key (DL_ID) references dlg_parts (DL_ID),
foreign key (TYP_ID) references traeger_typ (TYP_ID),
foreign key (DLT_ID) references dienst_traeger (DLT_ID),
foreign key (BID) references buchung (BID),
foreign key (KONT_ID) references kontingent (KONT_ID),
foreign key (KAT_ID) references kategorie (KAT_ID),
foreign key (SAI_ID) references saison (SAI_ID)
);


create table mp_gemein_res (
PERS_ID      integer	NOT NULL,
DL_ID        integer	NOT NULL,
TEIL         integer	NOT NULL,
BID          integer	NOT NULL,
GPERS_ID     integer	NOT NULL,
primary key (PERS_ID, DL_ID, TEIL, BID, GPERS_ID),
foreign key (PERS_ID) references personen (PERS_ID),
foreign key (BID) references buchung (BID),
foreign key (DL_ID) references dlg_parts (DL_ID)
);

/* PREIS Tabelle 47 */
create table preis (
PRE_ID		integer	NOT NULL,
APR			float		NOT NULL,
EPR			float		NOT NULL,
VPR			float		NOT NULL,
GLT			bigint	NOT NULL,
WHR_ID		integer	NOT NULL,
KBST			integer	NOT NULL,
KAR_ID		integer  NULL,
DLTT_ID		integer  NULL,
KAT_ID		integer  NULL,
RKR_ID		integer  NULL,
DLA_ID		integer  NULL,
ARR_ID		integer	NULL,
DL_ID			integer  NULL,
EXT_ID		integer  NULL,
DL_VONDAT	bigint  NULL,
DL_BISDAT	bigint  NULL,
KONT_ID		integer  NULL,
STA_ID		integer  NULL,
TEXTID		integer  NULL,
HISTORY		integer  NULL,
SAI_ID		integer	NOT NULL,
UNIT_TYP		integer  NULL,
UNIT_VON		integer  NULL,
UNIT_BIS		integer  NULL,
DAU			integer  NULL,
DAU_VON		bigint  NULL,
DAU_BIS		bigint  NULL,
primary key (PRE_ID),
foreign key (WHR_ID) references waehrung (WHR_ID),
foreign key (KBST) references personen (PERS_ID),
foreign key (KAR_ID) references kosten_art (KAR_ID),
foreign key (DLTT_ID) references traeger_typ (TYP_ID),
foreign key (KAT_ID) references kategorie (KAT_ID),
foreign key (RKR_ID) references reisender_typ (RKR_ID),
foreign key (DLA_ID) references dienst_angebot (DLA_ID),
foreign key (DL_ID) references dienstleistung (DLG_ID),
foreign key (KONT_ID) references kontingent (KONT_ID),
foreign key (SAI_ID) references saison (SAI_ID)
);


/* KAPAZITAET Tabelle 54 */
create table kapa (
KAT_ID		integer	NOT NULL,
KATBEZ_ID	integer	NOT NULL,
TDL_ID		integer	NOT NULL,
TDLBEZ_ID	integer	NOT NULL,
PRE_ID		integer	NOT NULL,
ANZ			integer  NULL,
BUSY			integer  NULL,
VPR			float  NULL,
VON_DAT		bigint	NOT NULL,
BIS_DAT		bigint	NOT NULL,
primary key (KAT_ID, TDL_ID, VON_DAT, BIS_DAT),
foreign key (KAT_ID) references kategorie (KAT_ID),
foreign key (TDL_ID) references dlg_parts (DL_ID)
);

create table mp_kapa (
KAT_ID       integer	NOT NULL,
KATBEZ_ID    integer	NULL,
DLT_ID       integer	NOT NULL,
DLTBEZ_ID    integer	NULL,
DL_ID        integer	NOT NULL,
DLBEZ_ID     integer	NULL,
ANZ          integer	NULL,
BUSY         integer	NULL,
VON_DAT      bigint	NOT NULL,
BIS_DAT      bigint	NOT NULL,
primary key (KAT_ID, DLT_ID, DL_ID, VON_DAT, BIS_DAT),
foreign key (KAT_ID) references kategorie (KAT_ID),
foreign key (DLT_ID) references dienst_traeger (DLT_ID),
foreign key (DL_ID) references dlg_parts (DL_ID)
);

create table mp_kol_pers (
PERS_ID      integer	NOT NULL,
ADR_TYP      integer	NOT NULL,
MPID         integer	NOT NULL,
K_ID         integer	NOT NULL,
primary key (PERS_ID, ADR_TYP, MPID, K_ID),
foreign key (PERS_ID) references personen (PERS_ID),
foreign key (MPID) references mp_profil (MPID),
foreign key (K_ID) references kollektiv (K_ID)
);


/********************************************************/
/* GRAFIK - PIXELBILDER                                 */
/********************************************************/

/* GRAPHIK-FILES Tabelle 48 */
create table graphik (
GRA_ID			integer	NOT NULL,
BEZ_ID			integer  NOT NULL unique,
DLT_ID			integer	NOT NULL unique,
TEXTID			integer  NULL,
primary key (GRA_ID),
foreign key (DLT_ID) references dienst_traeger (DLT_ID)
);


/* PCX-FILES Tabelle 49 */
create table pcx_files (
PCX_ID			integer	 NOT NULL,
BEZ_ID			integer   NOT NULL unique,
FILENAME			varchar(1024) NOT NULL,
X					integer  NULL,
Y					integer  NULL,
TYP				integer	NOT NULL,
TYPCODE			integer  NOT NULL,
FOLGE				integer	NOT NULL,
primary key (PCX_ID)
);

/* GRAFORM Tabelle 50 */
create table graform (
GRA_ID         integer	NOT NULL,
FORMNR         integer	NOT NULL,
FORM           varchar(256) NOT NULL,
primary key (GRA_ID, FORMNR),
foreign key (GRA_ID) references graphik (GRA_ID)
);


/* REGIONS Tabelle 51 */
create table regions (
HOST_ID			integer	NOT NULL,
H_DLT_ID			integer	NOT NULL,
DLT_ID			integer	NOT NULL,
FOLGE				integer	NOT NULL,
STUFE				integer	NOT NULL,
NUMMER			integer	NOT NULL,
primary key (HOST_ID, H_DLT_ID, DLT_ID, FOLGE),
foreign key (DLT_ID) references dienst_traeger (DLT_ID)
);

create table mp_param (
PARAM_ID     integer	NOT NULL,
CODE         varchar(256)	NULL,
FILE_ID      integer	NULL,
PARAM_TYP    integer	NULL,
LABEL_ID     integer	NULL,
PARAM        varchar(1024)	NULL,
primary key (PARAM_ID),
foreign key (FILE_ID) references mp_file (FILE_ID)
);

/* ============================================================ */
/*   Table: Debitor for OUTfaktura action                       */
/* ============================================================ */

create table mp_reminder (
REM_ID       integer	NOT NULL,
MPID         integer	NOT NULL,
K_ID         integer	NULL,
BID          integer	NULL,
PERS_ID      integer	NULL,
KID          integer	NULL,
ENTRY        datetime	NULL,
DEADLINE     datetime	NULL,
PERSON       integer	NULL,
PERS_TYP     integer	NULL,
NOTICE       varchar(1024)	NULL,
OPT          varchar(1024)	NULL,
primary key (REM_ID),
foreign key (MPID) references mp_profil (MPID),
foreign key (K_ID) references kollektiv (K_ID),
foreign key (BID) references buchung (BID),
foreign key (PERS_ID) references personen (PERS_ID),
foreign key (KID) references personen (PERS_ID)
);

create table mp_kreditor (
KRE_ID       integer	NOT NULL,
BID          integer	NOT NULL,
STA_ID       integer	NULL,
KID          integer	NOT NULL,
KONTO        varchar(256)	NULL,
NACHSALDO    float	NULL,
K_ID         integer	NULL,
FAKT_ID      integer	NULL,
FAKT_ZEIT    datetime		NULL,
FAKT_NR      varchar(256)	NULL,
FAKT_TEXT    varchar(1024)	NULL,
DLN_DETAIL   varchar(1024)	NULL,
DLG_DETAIL   varchar(1024)	NULL,
WHR_ID       integer	NULL,
WHR_LAND_ID  integer	NULL,
WHR_KURS     float	NULL,
WHR_TEXT     varchar(1024)	NULL,
WHR_EXCL     float	NULL,
WHR_INKL     float	NULL,
VAT_ID       integer	NOT NULL,
VAT_LAND_ID  integer	NULL,
VAT          float	NULL,
VAT_TEXT     varchar(1024)	NULL,
RST_EXCL     float	NULL,
RST_INKL     float	NULL,
RST_GEWINN   float	NULL,
OPT_TEXT     varchar(1024)	NULL,
primary key (KRE_ID, KID, VAT_ID),
foreign key (K_ID) references kollektiv (K_ID),
foreign key (BID) references buchung (BID),
foreign key (FAKT_ID) references mp_multimedia (MULT_ID),
foreign key (VAT_ID) references kommission (KOMM_ID),
foreign key (KID) references personen (PERS_ID),
foreign key (VAT_LAND_ID) references land (LAND_ID),
foreign key (WHR_LAND_ID) references land (LAND_ID),
foreign key (WHR_ID) references waehrung (WHR_ID),
foreign key (KID) references personen (PERS_ID)
);

create table mp_debitor (
DEB_ID       integer	NOT NULL,
BID          integer	NOT NULL,
STA_ID       integer	NULL,
KID          integer	NULL,
KONTO        varchar(256)	NULL,
NACHSALDO    float	NULL,
K_ID         integer	NULL,
FAKT_ID      integer	NULL,
FAKT_ZEIT    datetime	NULL,
FAKT_NR      varchar(256)	NULL,
FAKT_TEXT    varchar(1024)	NULL,
DLN_DETAIL   varchar(1024)	NULL,
DLG_DETAIL   varchar(1024)	NULL,
WHR_ID       integer	NULL,
WHR_LAND_ID  integer	NULL,
WHR_KURS     float	NULL,
WHR_TEXT     varchar(1024)	NULL,
WHR_EXCL     float	NULL,
WHR_INKL     float	NULL,
VAT_ID       integer	NOT NULL,
VAT_LAND_ID  integer	NULL,
VAT          float	NULL,
VAT_TEXT     varchar(1024)	NULL,
RST_EXCL     float	NULL,
RST_INKL     float	NULL,
RST_GEWINN   float	NULL,
OPT_TEXT     varchar(1024)	NULL,
primary key (DEB_ID, VAT_ID),
foreign key (K_ID) references kollektiv (K_ID),
foreign key (BID) references buchung (BID),
foreign key (FAKT_ID) references mp_multimedia (MULT_ID),
foreign key (VAT_ID) references kommission (KOMM_ID),
foreign key (KID) references personen (PERS_ID),
foreign key (VAT_LAND_ID) references land (LAND_ID),
foreign key (WHR_LAND_ID) references land (LAND_ID),
foreign key (WHR_ID) references waehrung (WHR_ID),
foreign key (KID) references personen (PERS_ID)
);
