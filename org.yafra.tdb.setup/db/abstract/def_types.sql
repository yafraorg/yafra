/*D*************************************************************/
/* SQL script: inital types                                    */
/*                                                             */
/* copyright:  yafra.org, 2003, Switzerland                    */
/***************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvsroot/mapo/db/abstract/def_types.sql,v 1.5 2009-01-02 16:50:09 mwn Exp $ */


/*********************************************************/
/* TRAEGER_TYP                                           */
/*********************************************************/
delete from traeger_typ where TYP_ID > -1;
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (1, 208, -1, 1, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (2, 210, 1, 1, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (3, 212, 1, 1, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (4, 213, -1, 4, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (5, 214, -1, 5, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (6, 215, 5, 5, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (7, 216, 6, 5, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (8, 217, 7, 5, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (9, 218, -1, 9, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (10, 219, 9, 9, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (11, 220, -1, 11, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (12, 221, 11, 11, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (13, 222, -1, 13, '-1' );
insert into traeger_typ (TYP_ID, BEZ_ID, H_TYP_ID, HOST_TYP, TEXTID) values (14, 223, 13, 13, '-1' );
 
delete from bezeichnung where TYP = 15 and S_ID =25 and BEZ_ID > 0;
insert into bezeichnung values (208, 25, 'Hotel', 15);
insert into bezeichnung values (210, 25, 'Hotel room', 15);
insert into bezeichnung values (212, 25, 'Conference room', 15);
insert into bezeichnung values (213, 25, 'Rental car', 15);
insert into bezeichnung values (214, 25, 'Boat', 15);
insert into bezeichnung values (215, 25, 'Deck', 15);
insert into bezeichnung values (216, 25, 'Cabin', 15);
insert into bezeichnung values (217, 25, 'Bed', 15);
insert into bezeichnung values (218, 25, 'Coach', 15);
insert into bezeichnung values (219, 25, 'Sitting place', 15);
insert into bezeichnung values (220, 25, 'Plane', 15);
insert into bezeichnung values (221, 25, 'Plane sitting place', 15);
insert into bezeichnung values (222, 25, 'Train', 15);
insert into bezeichnung values (223, 25, 'Tain sitting place', 15);
 
delete from bezeichnung where TYP = 15 and S_ID =1 and BEZ_ID > 0;
insert into bezeichnung values (208, 1, 'Hotel', 15);
insert into bezeichnung values (210, 1, 'Hotelzimmer', 15);
insert into bezeichnung values (212, 1, 'Konferenzraum', 15);
insert into bezeichnung values (213, 1, 'Mietauto', 15);
insert into bezeichnung values (214, 1, 'Schiff', 15);
insert into bezeichnung values (215, 1, 'Deck', 15);
insert into bezeichnung values (216, 1, 'Kabine', 15);
insert into bezeichnung values (217, 1, 'Bett', 15);
insert into bezeichnung values (218, 1, 'Bus', 15);
insert into bezeichnung values (219, 1, 'Bussitzplatz', 15);
insert into bezeichnung values (220, 1, 'Flugzeug', 15);
insert into bezeichnung values (221, 1, 'Flugsitzplatz', 15);
insert into bezeichnung values (222, 1, 'Zug', 15);
insert into bezeichnung values (223, 1, 'Zugsitzplatz', 15);



/*********************************************************/
/* ANGEBOTS_TYP                                          */
/*********************************************************/
delete from angebots_typ where ART_ID > -1;
insert into angebots_typ (ART_ID, BEZ_ID, TEXTID) values (1, 1, -1); 
insert into angebots_typ (ART_ID, BEZ_ID, TEXTID) values (2, 2, -1); 
insert into angebots_typ (ART_ID, BEZ_ID, TEXTID) values (3, 3, -1); 
insert into angebots_typ (ART_ID, BEZ_ID, TEXTID) values (4, 4, -1); 
insert into angebots_typ (ART_ID, BEZ_ID, TEXTID) values (5, 5, -1); 
insert into angebots_typ (ART_ID, BEZ_ID, TEXTID) values (6, 6, -1); 
insert into angebots_typ (ART_ID, BEZ_ID, TEXTID) values (7, 7, -1); 
insert into angebots_typ (ART_ID, BEZ_ID, TEXTID) values (8, 8, -1); 
 
delete from bezeichnung where TYP = 18 and S_ID =25 and BEZ_ID > 0;
insert into bezeichnung values (1, 25, 'Accomodation', 18);
insert into bezeichnung values (2, 25, 'Accomodation incl. Breakfast', 18);
insert into bezeichnung values (3, 25, 'Accomodation 1/2 pension', 18);
insert into bezeichnung values (4, 25, 'Accomodation full pension', 18);
insert into bezeichnung values (5, 25, 'Flight', 18);
insert into bezeichnung values (6, 25, 'Car rental', 18);
insert into bezeichnung values (7, 25, 'Bus trip', 18);
insert into bezeichnung values (8, 25, 'Cruise', 18);
 
delete from bezeichnung where TYP = 18 and S_ID =1 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Uebernachtung', 18);
insert into bezeichnung values (2, 1, 'Uebernachtung inkl. Frï¿½hstï¿½ck', 18);
insert into bezeichnung values (3, 1, 'Uebernachtung 1/2 Pension', 18);
insert into bezeichnung values (4, 1, 'Uebernachtung Voll Pension', 18);
insert into bezeichnung values (5, 1, 'Flug', 18);
insert into bezeichnung values (6, 1, 'Automiete', 18);
insert into bezeichnung values (7, 1, 'Busreise', 18);
insert into bezeichnung values (8, 1, 'Kreuzfahrt', 18);



/*********************************************************/
/* KUNDEN_TYP                                            */
/*********************************************************/
delete from kunden_typ where K_TYP_ID > -1;
insert into kunden_typ (K_TYP_ID, BEZ_ID, TEXTID, KUNCODE) values (1, 1, -1, 'bpl' );
insert into kunden_typ (K_TYP_ID, BEZ_ID, TEXTID, KUNCODE) values (2, 2, -1, 'cre' );
insert into kunden_typ (K_TYP_ID, BEZ_ID, TEXTID, KUNCODE) values (3, 3, -1, 'deb' );
 
delete from bezeichnung where TYP = 24 and S_ID =25 and BEZ_ID > 0;
insert into bezeichnung values (1, 25, 'Billing place', 24);
insert into bezeichnung values (2, 25, 'Creditor', 24);
insert into bezeichnung values (3, 25, 'Debitor', 24);
 
delete from bezeichnung where TYP = 24 and S_ID =1 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Buchungstelle', 24);
insert into bezeichnung values (2, 1, 'Kreditor', 24);
insert into bezeichnung values (3, 1, 'Debitor', 24);



/*********************************************************/
/* KOLLEKTIV_TYP                                         */
/*********************************************************/
delete from kollektiv_typ where K_TYP_ID > -1;
insert into kollektiv_typ (K_TYP_ID, BEZ_ID, KOLCODE, TEXTID) values (1, 1, 'FIT', -1 );
insert into kollektiv_typ (K_TYP_ID, BEZ_ID, KOLCODE, TEXTID) values (2, 2, 'GRP', -1 );

delete from bezeichnung where TYP = 32 and S_ID =25 and BEZ_ID > 0;
insert into bezeichnung values (1, 25, 'FIT', 32);
insert into bezeichnung values (2, 25, 'Group', 32);
 
delete from bezeichnung where TYP = 32 and S_ID =1 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Individualreisender', 32);
insert into bezeichnung values (2, 1, 'Gruppe', 32);

/*********************************************************/
/* REISENDER_TYP                                         */
/*********************************************************/
delete from reisender_typ where K_TYP_ID > -1;
insert into reisender_typ (RKR_ID, DLNCODE, BEZ_ID, VONALTER, BISALTER, TEXTID) values (1, 'REG', 1, 16, 65, -1 );
insert into reisender_typ (RKR_ID, DLNCODE, BEZ_ID, VONALTER, BISALTER, TEXTID) values (2, 'RET', 2, 66, 120, -1 );
insert into reisender_typ (RKR_ID, DLNCODE, BEZ_ID, VONALTER, BISALTER, TEXTID) values (3, 'CHLD', 3, 3, 15, -1 );
insert into reisender_typ (RKR_ID, DLNCODE, BEZ_ID, VONALTER, BISALTER, TEXTID) values (4, 'BABY', 4, 0, 2, -1 );

delete from bezeichnung where TYP = 35 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 25, 'Regular person', 35);
insert into bezeichnung values (2, 25, 'Retiree', 35);
insert into bezeichnung values (3, 25, 'Child', 35);
insert into bezeichnung values (4, 25, 'Baby', 35);
 
delete from bezeichnung where TYP = 35 and S_ID =1 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Erwachsener', 35);
insert into bezeichnung values (2, 1, 'Rentner', 35);
insert into bezeichnung values (3, 1, 'Kind', 35);
insert into bezeichnung values (4, 1, 'Kleinkind', 35);


/*********************************************************/
/* KOSTEN_ART                                            */
/*********************************************************/
delete from kosten_art where KAR_ID > -1;
insert into kosten_art (KAR_ID, BEZ_ID, TEXTID) values (1, 1, -1 );
insert into kosten_art (KAR_ID, BEZ_ID, TEXTID) values (2, 2, -1 );

delete from bezeichnung where TYP = 43 and S_ID =25 and BEZ_ID > 0;
insert into bezeichnung values (1, 25, 'Normal price', 43);
insert into bezeichnung values (2, 25, 'Taxes', 43);
 
delete from bezeichnung where TYP = 43 and S_ID =1 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Normalpreis', 43);
insert into bezeichnung values (2, 1, 'Steuern', 43);

