/*D************************************************************/
/* project:   MARCO POLO                                      */
/*                                                            */
/* DBMS:      HP/ALLBASE                                      */
/*            create sequences                                */
/*            ACHTUNG !!! Zum Teil sind Typen hardcoded !!!   */
/*            Abstimmen mit mpobjdef.h                        */
/*                                                            */
/* copyright: yafra.org     */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvstdbadmin/mapo/db/oracle/dbe_sequences.sql,v 1.1 2004-01-17 12:58:59 mwn Exp $ */

/* create sequence for table kollektiv */
create sequence tdbadmin.kollektiv_seq start with 1;

/* create sequence for table buchung */
create sequence tdbadmin.buchung_seq start with 1;

/* create sequence for table saison */
create sequence tdbadmin.saison_seq start with 1;

/* create sequence for table programm */
create sequence tdbadmin.programm_seq start with 1;

/* create sequence for table arrangement */
create sequence tdbadmin.arrangement_seq start with 1;

/* create sequence for table dienstleistung */
create sequence tdbadmin.dienstleistung_seq start with 1;

/* create sequence for table dlg_parts */
create sequence tdbadmin.dlg_parts_seq start with 1;

/* create sequence for table mp_profil */
create sequence tdbadmin.mp_profil_seq start with 1;

/* create sequence for table mp_reminder */
create sequence tdbadmin.mp_reminder_seq start with 1;

/* create sequence for table personen */
create sequence tdbadmin.personen_seq start with 1;

/* create sequence for table mp_debitor and mp_kreditor */
create sequence tdbadmin.mp_deb_kre_seq start with 1;

/* create sequence for table kontingent */
create sequence tdbadmin.kontingent_seq start with 1;

/* create sequence for table host_kont */
create sequence tdbadmin.host_kont_seq start with 1;

/* create sequence for table kategorie */
create sequence tdbadmin.kategorie_seq start with 1;

/* create sequence for table dienst_traeger */
create sequence tdbadmin.dienst_traeger_seq start with 1;

/* create sequence for table traeger_typ */
create sequence tdbadmin.traeger_typ_seq start with 1;

/* create sequence for table dienst_angebot */
create sequence tdbadmin.dienst_angebot_seq start with 1;

/* create sequence for table kommission */
create sequence tdbadmin.kommission_seq start with 1;

/* create sequence for table preis */
create sequence tdbadmin.preis_seq start with 1;

/* create sequence for table ort */
create sequence tdbadmin.ort_seq start with 1;

/* create sequence for table mp_multimedia */
create sequence tdbadmin.mp_multimedia_seq start with 1;

/* create sequence for table texte and mp_texte */
create sequence tdbadmin.mp_texte_seq start with 1;

/* create sequence for table bezeichnung */
create sequence tdbadmin.bezeichnung_seq start with 1;

/* create sequence for all other tables */
create sequence tdbadmin.mp_common_seq start with 1024;

/* create sequence for a table kunden_typ */
create sequence tdbadmin.kunden_typ_seq start with 1;

/* create sequence for a table kollektiv_typ */
create sequence tdbadmin.kollektiv_typ_seq start with 1;

/* create sequence for a table angebots_typ */
create sequence tdbadmin.angebots_typ_seq start with 1;

/* create sequence for a table reisender_typ */
create sequence tdbadmin.reisender_typ_seq start with 1;

