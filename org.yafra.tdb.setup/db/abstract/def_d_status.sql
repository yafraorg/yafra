/*D************************************************************/
/* Default:   STATUS_WERTE                                    */
/*            Statuswerte initialisieren                      */
/*                                                            */
/* Copyright: yafra.org     */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvsroot/mapo/db/abstract/def_d_status.sql,v 1.6 2009-01-02 16:50:09 mwn Exp $ */

delete from status_werte where STA_ID > 0;
delete from bezeichnung where typ between 1100 and 2000;

/* INIT Statuswerte region */
insert into bezeichnung values (0, 1, 'INT-Statuswerte', 1100);
insert into bezeichnung values (0, 25, 'INT-Statuswerte', 1100);

insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1100);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1100);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1100);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1101);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1103);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1103);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1103);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1104);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1104);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1104);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1105);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1105);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1105);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1106);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1106);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1106);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1107);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1109);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1110);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1110);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1110);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1111);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1111);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1111);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1113);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1114);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1114);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1114);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1115);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1115);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1115);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1116);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1117);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1117);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1117);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1118);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1119);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1120);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1121);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1122);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1123);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1124);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1124);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1124);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1125);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1125);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1125);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1126);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1127);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1128);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1128);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1128);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (-1, 'n/a', 'n/a', -1,-1, 1129);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 1, 'n/a', 1129);
insert into bezeichnung (bez_id, s_id, bez, typ) values (-1, 25, 'n/a', 1129);




/* Package pirority */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, '1', '-', 1,1, 1101);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, '1', '-', 2,1, 1101);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, '1', '-', 3,1, 1101);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, '1', '-', 4,1, 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Prioritï¿½t des Arrangements', 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Prioritï¿½tsstufe 1', 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Prioritï¿½tsstufe 2', 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Prioritï¿½tsstufe 3', 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Prioritï¿½tsstufe 4', 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Arrangement Priority', 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Priority level 1', 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Priority level 2', 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Priority level 3', 1101);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Priority level 4', 1101);

/* Colors */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, '-', 'white', 1,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, '-', 'grey', 2,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, '-', 'green', 3,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, '-', 'blue', 4,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5, '-', 'yellow', 5,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (6, '-', 'red', 6,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (7, '-', 'black', 7,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (8, '-', 'pink', 8,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (9, '-', 'gold', 9,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (10, '-', 'magenta', 10,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (11, '-', 'tomato', 11,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (12, '-', 'SteelBlue', 12,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (13, '-', 'snow', 13,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (14, '-', 'sienna', 14,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (15, '-', 'salmon', 15,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (16, '-', 'purple', 16,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (17, '-', 'plum', 17,-1, 1102);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (18, '-', 'orchid', 18,-1, 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Farben', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Weiss', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Grau', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Grï¿½n', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Blau', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 1, 'Gelb', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6, 1, 'Rot', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (7, 1, 'Schwarz', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (8, 1, 'Pink', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (9, 1, 'Gold', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (10, 1, 'Magenta', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (11, 1, 'Tomatenrot', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (12, 1, 'Stahlblau', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (13, 1, 'Schnee', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (14, 1, 'Sienna', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (15, 1, 'Salmon', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (16, 1, 'Purple', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (17, 1, 'Plum', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (18, 1, 'Orchidee', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Colors', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'White', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Grey', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Green', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Blue', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 25, 'Yellow', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6, 25, 'Red', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (7, 25, 'Black', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (8, 25, 'Pink', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (9, 25, 'Gold', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (10, 25, 'Magenta', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (11, 25, 'Tomato-red', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (12, 25, 'Steel-blue', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (13, 25, 'Snow', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (14, 25, 'Sienna', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (15, 25, 'Salmon', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (16, 25, 'Purple', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (17, 25, 'Plum', 1102);
insert into bezeichnung (bez_id, s_id, bez, typ) values (18, 25, 'Orchidee', 1102);

/*TODO init Group state */
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Gruppenstatus', 1103);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Group status', 1103);

/* Person type privat/company */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'priv', 'privat', 1,-1, 1104);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'comp', 'company', 2,-1, 1104);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Presonentypen', 1104);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Privatpersonen', 1104);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Firmen', 1104);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Person type', 1104);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Private person', 1104);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Firm', 1104);

/* State of the price */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'y', '-', 1,-1, 1105);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'n', '-', 2,-1, 1105);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Preisstatus', 1105);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Ermï¿½ssigung am Preis mï¿½glich', 1105);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Ermï¿½ssigungen nicht mï¿½glich', 1105);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Price status', 1105);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Reduction on price possible', 1105);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Reduction on price impossible', 1105);

/* Gender of a private person m/f */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'w', '-', 1,-1, 1106);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'm', '-', 2,-1, 1106);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Geschlecht des Reisenden', 1106);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'weiblich', 1106);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'mï¿½nnlich', 1106);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Traveler Sex', 1106);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Woman', 1106);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Man', 1106);

/* Output state */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'r', '-', 1,-1, 1107);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'h', '-', 2,-1, 1107);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 'o', '-', 3,-1, 1107);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, 'e', '-', 4,-1, 1107);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5, 'i', '-', 5,-1, 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Zustand einer Aktion', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Gut zur Ausfï¿½hrung', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'In Ausfï¿½hrung', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Ausfï¿½hrung i.O. beendet', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Fehler bei Ausfï¿½hrung', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 1, 'Interner Fehler in Aktion', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Actions status', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Ready to execute', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Executing', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Execution well terminated', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Execution error', 1107);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 25, 'Internal error in the action', 1107);


/**************************************************************/
/* STATUS: Buchungsstatus                                     */
/* NAME:   buchung.sta                                        */
/* TYP:    user definable                                     */
/**************************************************************/
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Buchungsstatus', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Booking states', 1108);
insert into status_werte values (1, 'EIN', 'EIN',     1, -1.0,    1108);
insert into bezeichnung values (1, 1, 'Eingabe',                  1108);
insert into bezeichnung values (1, 25, 'New entry',                  1108);
insert into status_werte values (2, 'ANF', 'ANF',     2, -1.0,    1108);
insert into bezeichnung values (2, 1, 'Anfrage',                  1108);
insert into bezeichnung values (2, 25, 'Request',                  1108);
insert into status_werte values (3, 'ANFOK', 'ANFOK', 3, -1.0,    1108);
insert into bezeichnung values (3, 1, 'Anfrage bestï¿½tigt',        1108);
insert into bezeichnung values (3, 25, 'Request confirmed',        1108);
insert into status_werte values (4, 'MOD', 'MOD',     4, -1.0,    1108);
insert into bezeichnung values (4, 1, 'Modifikation',             1108);
insert into bezeichnung values (4, 25, 'Modification',             1108);
insert into status_werte values (5, 'MODOK', 'MODOK', 5, -1.0,    1108);
insert into bezeichnung values (5, 1, 'Modifikation bestï¿½tigt',   1108);
insert into bezeichnung values (5, 25, 'Modification confirmed',   1108);
insert into status_werte values (6, 'OPT', 'OPT',     6, -1.0,    1108);
insert into bezeichnung values (6, 1, 'Option',                   1108);
insert into bezeichnung values (6, 25, 'Option',                   1108);
insert into status_werte values (7, 'DEF', 'DEF',     7, -1.0,    1108);
insert into bezeichnung values (7, 1, 'Definitiv',                1108);
insert into bezeichnung values (7, 25, 'Final',                1108);
insert into status_werte values (8, 'REOPEN', 'REOPEN', 8, -1.0,  1108);
insert into bezeichnung values (8, 1, 'Rechnung offen',           1108);
insert into bezeichnung values (8, 25, 'Open invoice',                1108);
insert into status_werte values (9, 'REOK', 'REOK',   9, -1.0,    1108);
insert into bezeichnung values (9, 1, 'Rechnung bezahlt',         1108);
insert into bezeichnung values (9, 25, 'Invoice payed',         1108);
insert into status_werte values (10, 'OK', 'OK',     10, -1.0,    1108);
insert into bezeichnung values (10, 1, 'Erledigt',                1108);
insert into bezeichnung values (10, 25, 'Done',                1108);
insert into status_werte values (11, 'ANN', 'ANN',   11, -1.0,    1108);
insert into bezeichnung values (11, 1, 'Annullation',             1108);
insert into bezeichnung values (11, 25, 'Cancelation',             1108);
insert into status_werte values (12, 'ANNOK', 'ANNOK', 12, -1.0,  1108);
insert into bezeichnung values (12, 1, 'Annullation bestï¿½tigt',   1108);
insert into bezeichnung values (12, 25, 'Cancelation confirmed',   1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2000, 'OK_REQ', 'OK_REQ', 2000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2666, 'INT_INFREQ', 'INT_INFREQ', 2666,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3000, 'OK_INF', 'OK_INF', 3000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5000, 'OK_REQ_SENT', 'OK_REQ_SENT', 5000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (6000, 'OK_OFF', 'OK_OFF', 6000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (8000, 'OK_OFF_SENT', 'OK_OFF_SENT', 8000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (9000, 'OK_CONF', 'OK_CONF', 9000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (11000, 'OK_INV', 'OK_INV', 11000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (13000, 'OK_INV_SENT', 'OK_INV_SENT', 13000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (15000, 'OK_PAY', 'OK_PAY', 15000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (16000, 'OK_VOU', 'OK_VOU', 16000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (18000, 'OK_COMP', 'OK_COMP', 18000,-1, 1108);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (19000, 'OK_FIN', 'OK_FIN', 19000,-1, 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2000, 1, 'Anfrage bereit', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2666, 1, 'Information/Anfrage bereit', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3000, 1, 'Information bereit', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5000, 1, 'Anfrage geschickt', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6000, 1, 'Offerte bereit', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (8000, 1, 'Offerte geschickt', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (9000, 1, 'Bestï¿½tigung bereit', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (11000, 1, 'Rechnung bereit', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (13000, 1, 'Rechnung geschickt', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (15000, 1, 'Rechnung offen OK', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (16000, 1, 'Voucher bereit', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (18000, 1, 'Erledigt OK', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (19000, 1, 'Fertig OK', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2000, 25, 'Request ready', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2666, 25, 'Information/request ready', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3000, 25, 'Information ready', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5000, 25, 'Request sent OK', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6000, 25, 'Offer ready', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (8000, 25, 'Offer sent', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (9000, 25, 'Confirmation ready', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (11000, 25, 'Invoice ready OK', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (13000, 25, 'Invoice sent', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (15000, 25, 'Opened invoice OK', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (16000, 25, 'Voucher ready', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (18000, 25, 'Complete OK', 1108);
insert into bezeichnung (bez_id, s_id, bez, typ) values (19000, 25, 'Finished OK', 1108);

/* Start type of an action */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'w', 'w', 1,-1, 1109);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'i', 'i', 2,-1, 1109);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 's', 's', 3,-1, 1109);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, 'm', 'm', 4,-1, 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Ausfï¿½hrungsstatus der Aktionen', 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Aktion nicht ausfï¿½hren', 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Aktion automatisch sofort', 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Aktion automatisch gespoolt', 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Aktion manuell', 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Action execution status', 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Action not to execute', 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Automatic immediate action', 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Automaticaly spooled action', 1109);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Manual action', 1109);

/*TODO state of a person - set init values */
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Personenstatus', 1110);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Person status', 1110);

/* Shipment mode */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'n', 'normal', 1,-1, 1111);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'e', 'express', 2,-1, 1111);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Versandcode', 1111);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Normalversand (B-Post)', 1111);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Expressversand (A-Post)', 1111);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Sending mode', 1111);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Normal sending', 1111);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Express sending', 1111);


/**************************************************************/
/* STATUS: Reservationsstatus                                 */
/* NAME:   reservation.r_sta                                  */
/*         aktionen.b_flag                                    */
/*         aktionen.b2_flag                                   */
/* TYP:    user definable                                     */
/**************************************************************/
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Reservationsstatus', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Reservation status', 1112);
insert into status_werte values (1, 'EIN', 'EIN',     1, -1.0,    1112);
insert into bezeichnung values (1, 1, 'Eingabe',                  1112);
insert into bezeichnung values (1, 25, 'New entry',                  1112);
insert into status_werte values (2, 'ANF', 'ANF',     2, -1.0,    1112);
insert into bezeichnung values (2, 1, 'Anfrage',                  1112);
insert into bezeichnung values (2, 25, 'Request',                  1112);
insert into status_werte values (3, 'ANFOK', 'ANFOK', 3, -1.0,    1112);
insert into bezeichnung values (3, 1, 'Anfrage bestaetigt',       1112);
insert into bezeichnung values (3, 25, 'Request confirmed',        1112);
insert into status_werte values (4, 'MOD', 'MOD',     4, -1.0,    1112);
insert into bezeichnung values (4, 1, 'Modifikation',             1112);
insert into bezeichnung values (4, 25, 'Modification',             1112);
insert into status_werte values (5, 'MODOK', 'MODOK', 5, -1.0,    1112);
insert into bezeichnung values (5, 1, 'Modifikation bestaetigt',  1112);
insert into bezeichnung values (5, 25, 'Modification confirmed',   1112);
insert into status_werte values (6, 'OPT', 'OPT',     6, -1.0,    1112);
insert into bezeichnung values (6, 1, 'Option',                   1112);
insert into bezeichnung values (6, 25, 'Option',                   1112);
insert into status_werte values (7, 'DEF', 'DEF',     7, -1.0,    1112);
insert into bezeichnung values (7, 1, 'Definitiv',                1112);
insert into bezeichnung values (7, 25, 'Final',                1112);
insert into status_werte values (8, 'REOPEN', 'REOPEN', 8, -1.0,  1112);
insert into bezeichnung values (8, 1, 'Rechnung offen',           1112);
insert into bezeichnung values (8, 25, 'Open invoice',                1112);
insert into status_werte values (9, 'REOK', 'REOK',     9, -1.0,  1112);
insert into bezeichnung values (9, 1, 'Rechnung bezahlt',         1112);
insert into bezeichnung values (9, 25, 'Invoice payed',                1112);
insert into status_werte values (10, 'OK', 'OK',       10, -1.0,  1112);
insert into bezeichnung values (10, 1, 'Erledigt',                 1112);
insert into bezeichnung values (10, 25, 'Done',                 1112);
insert into status_werte values (11, 'ANN', 'ANN',     11, -1.0,   1112);
insert into bezeichnung values (11, 1, 'Annullation',              1112);
insert into bezeichnung values (11, 25, 'Cancelation',             1112);
insert into status_werte values (12, 'ANNOK', 'ANNOK', 12, -1.0,   1112);
insert into bezeichnung values (12, 1, 'Annullation bestaetigt',   1112);
insert into bezeichnung values (12, 25, 'Cancelation confirmed',   1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1000, 'INP', 'INP', 1000,-1, 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4001, 'AN_INFREQ', 'AN_INFREQ', 4001,-1, 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4502, 'QM_REQ', 'QM_REQ', 4502,-1, 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5502, 'QM_OFF', 'QM_OFF', 5502,-1, 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (7001, 'AN_OFF', 'AN_OFF', 7001,-1, 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (8502, 'QM_CONF', 'QM_CONF', 8502,-1, 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (10001, 'AN_CONF', 'AN_CONF', 10001,-1, 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (12001, 'AN_INV', 'AN_INV', 12001,-1, 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (14001, 'AN_PAY', 'AN_PAY', 14001,-1, 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (17001, 'AN_VOU', 'AN_VOU', 17001,-1, 1112);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (20000, 'ANN2', 'ANN2', 20000,-1, 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1000, 1, 'Eingabe neu', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4001, 1, 'Information/Anfrage Modifikation', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4502, 1, 'Anfrage Schnellï¿½nderung', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5502, 1, 'Offerte Schnellï¿½nderung', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (7001, 1, 'Offerte Modification', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (8502, 1, 'Bestï¿½tigung Schnellï¿½nderung', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (10001, 1, 'Bestï¿½tigung Modifikation', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (12001, 1, 'Rechnung Annulation', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (14001, 1, 'Bezahlung Modifikation', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (17001, 1, 'Voucher Modifikation', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (20000, 1, 'Annullation 2', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1000, 25, 'Input', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4001, 25, 'Information/request modification', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4502, 25, 'Quick request modification', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5502, 25, 'Quick offer modification', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (7001, 25, 'Offer modification', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (8502, 25, 'Quick confirmation modification', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (10001, 25, 'Confirmation modification', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (12001, 25, 'Invoice modification', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (14001, 25, 'Payment modification', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (17001, 25, 'Voucher modification', 1112);
insert into bezeichnung (bez_id, s_id, bez, typ) values (20000, 25, 'Annulated', 1112);

/* Reservation type (static / dynamic / yes-no) */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'n', '-', 1,-1, 1113);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 's', '-', 2,-1, 1113);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 'd', '-', 3,-1, 1113);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, 'b', '-', 4,-1, 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Reservationsart der DL', 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Keine Reservation mï¿½glich', 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Statische Reservation', 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Dynamische Reservation', 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Ja/Nein Reservation', 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Reservation type', 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'No reservation allowed', 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Static reservation', 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Dynamic reservation', 1113);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Yes/No reservation', 1113);

/* Exchange rate type */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, '1', 'cash', 1,-1, 1114);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, '1', 'credit', 2,-1, 1114);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Kurstyp', 1114);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Barkurs', 1114);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Devisenkurs', 1114);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Exchange Type', 1114);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Cash', 1114);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Credit', 1114);

/* value type */
insert into status_werte values (1, '1', '%', 1,-1, 1115);
insert into status_werte values (2, '1', '!', 2, -1, 1115);
insert into status_werte values (3, '2', '+', 3,-1, 1115);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Satz/Wert Art', 1115);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Prozent', 1115);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Absolut/Fix', 1115);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Normal positiv', 1115);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Record/value type', 1115);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Percent', 1115);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Absolute/fix', 1115);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Normal positive', 1115);

/* Attribute of a supplier object which defines the level of attractivness */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, '1', 'level1', 1,-1, 1116);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, '2', 'level2', 2,-1, 1116);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, '3', 'level3', 3,-1, 1116);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, '4', 'level4', 4,-1, 1116);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5, '5', 'level5', 5,-1, 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Bestplatzattribut', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Level 1', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Level 2', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Level 3', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Level 4', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 1, 'Level 5', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Best place attribute', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Level 1', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Level 2', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Level 3', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Level 4', 1116);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 25, 'Level 5', 1116);

/* How many times you allow over booking */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, '1', 'einmal', 1,-1, 1117);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, '2', 'zweimal', 2,-1, 1117);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Ueberbuchungs-Faktor', 1117);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'einmal ï¿½berbuchen', 1117);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'zweimal ï¿½berbuchen', 1117);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Surbooking factor', 1117);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'One-time-surbooking', 1117);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Two-times-surbooking', 1117);

/* Message type */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'E', 'ERROR', 1,-1, 1118);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'W', 'WARNING', 2,-1, 1118);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 'I', 'INFORMATION', 3,-1, 1118);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, 'D', 'DBERROR', 4,-1, 1118);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5, 'S', 'SYSTEM', 5,-1, 1118);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (6, 'A', 'AKTIONEN', 6,-1, 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Nachrichtentypen', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Fehlermeldung', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Warnung', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Information', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Datenbank Fehlermeldung', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 1, 'Systemmeldung', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6, 1, 'Aktionsmeldungen', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Information type', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Error message', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Warning', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Information', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Database error message', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 25, 'System message', 1118);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6, 25, 'Action message', 1118);

/* System devices */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'prt', 'Printer', 1,-1, 1119);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'fax', 'Fax', 2,-1, 1119);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 'tlx', 'Telex', 3,-1, 1119);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, 'mdm', 'Modem', 4,-1, 1119);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5, 'scr', 'Screen', 5,-1, 1119);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (6, 'fil', 'File', 6,-1, 1119);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (7, 'prt2', 'Printer2', 7,-1, 1119);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (8, 'prt3', 'Printer3', 8,-1, 1119);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (9, 'prt4', 'Printer4', 9,-1, 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Gerï¿½te am System', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Drucker', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Telefax', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Telex', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'e-mail', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 1, 'Bildschirm', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6, 1, 'Datei', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (7, 1, 'Drucker 2', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (8, 1, 'Drucker 3', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (9, 1, 'Drucker 4', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'System devices', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Printer', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Fax', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Telex', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'E-Mail', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 25, 'Screen', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6, 25, 'File', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (7, 25, 'Printer 2', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (8, 25, 'Printer 3', 1119);
insert into bezeichnung (bez_id, s_id, bez, typ) values (9, 25, 'Printer 4', 1119);

/* Commission type */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, '1', 'dla', 1,-1, 1120);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, '2', 'dlg', 2,-1, 1120);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, '3', 'kont', 3,-1, 1120);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, '4', 'mwst', 4,-1, 1120);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5, '5', 'kun', 5,-1, 1120);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (6, '6', 'kol', 6,-1, 1120);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (7, '7', 'bid', 7,-1, 1120);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (8, '8', 'fix', 8,-1, 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Kommissionstypen', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Angebotsrabatt', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Dienstleistungsrabatt', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Kontingentsrabatt', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Mehrwertsteuer', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 1, 'Extra Kundensrabatt', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6, 1, 'Extra Gruppensrabatt', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (7, 1, 'Extra prozent Buchungsrabatt', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (8, 1, 'Extra fixes Buchungsrabatt', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Commission type', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Rebate on offer', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Rebate on service', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Rebate on allotement', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Value Added Tax', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 25, 'Extra Rebate on client', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6, 25, 'Extra Rebate on group', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (7, 25, 'Extra rate rebate on booking', 1120);
insert into bezeichnung (bez_id, s_id, bez, typ) values (8, 25, 'Extra fix rebate on booking', 1120);

/* System access / application type */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, '1', 'local', 1,-1, 1121);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, '2', 'localwww', 2,-1, 1121);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, '3', 'extern', 3,-1, 1121);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, '4', 'externkk', 4,-1, 1121);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5, '5', 'externwww', 5,-1, 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Buchungsauslï¿½sestatus', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'lokale Buchung MP classic', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'lokale Buchung MP WWW', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'externe Buchung MP classic', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'externe Buchung K u.K', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 1, 'externe Buchung Internet WWW', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Reservation release status', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Local MPClassic booking', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Local MPwww booking', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'External MPClassic booking', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'External K a. K booking', 1121);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 25, 'External internet www booking', 1121);

/* Privileges */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, '1', 'dba', 1,-1, 1122);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, '2', 'user', 2,-1, 1122);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, '3', 'booking', 3,-1, 1122);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, '4', 'readonly', 4,-1, 1122);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5, '5', 'nop', 5,-1, 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Privilegien', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Datenbankadmin', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Normalbenutzer', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Buchungsbenutzer', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Nur Lesen', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 1, 'Keine Berechtigung', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Privileges', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Database administrator', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Normal user', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Booking user', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Read Only', 1122);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 25, 'No authorization', 1122);

/* Place / location type */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'c', 'city', 1,-1, 1123);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'a', 'airport', 2,-1, 1123);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 'b', 'bus station', 3,-1, 1123);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, 'r', 'railroad station', 4,-1, 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Orttypen', 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Stadt', 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Flughafen', 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Bushaltestelle', 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Bahnhof', 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Place type', 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'City', 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Airport', 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Bus station', 1123);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Railroad station', 1123);

/* File type */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'gif', 'gif', 1,-1, 1124);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'jpeg', 'jpeg', 2,-1, 1124);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 'cfg', 'cfg', 3,-1, 1124);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Filetypen fuer mp_file', 1124);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'gif', 1124);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'jpeg', 1124);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'cfg', 1124);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'File type', 1124);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'gif', 1124);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'jpeg', 1124);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'cfg', 1124);

/* Parameter type */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'int', 'integer', 1,-1, 1125);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'str', 'string', 2,-1, 1125);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 'combo', 'combo choice', 3,-1, 1125);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Parametertypen fuer mp_param', 1125);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'int', 1125);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'str', 1125);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'combo', 1125);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Parameter type', 1125);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'int', 1125);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'str', 1125);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'combo', 1125);

/* Multimedia type */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'gif', 'gif', 1,-1, 1126);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'jpeg', 'jpeg', 2,-1, 1126);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 'html', 'html', 3,-1, 1126);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, 'wav', 'wav', 4,-1, 1126);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (5, 'mp3', 'mp3', 5,-1, 1126);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (6, 'mp4', 'mp4', 6,-1, 1126);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (7, 'avi', 'avi', 7,-1, 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Multimediatypen fuer mp_multimedia', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'gif', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'jpeg', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'html', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'wav', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 1, 'mp3', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6, 1, 'mp4', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (7, 1, 'avi', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Multimedia type', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'picture gif', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'picture jpeg', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'web page html', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'audio wav', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (5, 25, 'audio mp3', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (6, 25, 'video mp4', 1126);
insert into bezeichnung (bez_id, s_id, bez, typ) values (7, 25, 'video avi', 1126);

/* Address type */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'p', 'private', 1,-1, 1127);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'o', 'office', 2,-1, 1127);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 'p2', 'private 2', 3,-1, 1127);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (4, 'o2', 'office 2', 4,-1, 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Adressetypen fuer persadr', 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Persï¿½nlisches Adresse', 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Beruflisches Adresse', 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Zweite Persï¿½nlisches Adresse', 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 1, 'Zweite Beruflisches Adresse', 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Address type', 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Private address', 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Office address', 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Second private address', 1127);
insert into bezeichnung (bez_id, s_id, bez, typ) values (4, 25, 'Second office address', 1127);

/* Price unit type */
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (1, 'dlt', 'traeger', 1,-1, 1128);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (2, 'pers', 'person', 2,-1, 1128);
insert into status_werte (sta_id, abk, sta, bez_id, kond, typ) values (3, 'k', 'group', 3,-1, 1128);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Preis Unit Typ', 1128);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Preis pro Dienstleistingstraeger', 1128);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 1, 'Preis pro Reisender', 1128);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 1, 'Preis pro Kollektiv', 1128);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Price unit type', 1128);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Price per carrier', 1128);
insert into bezeichnung (bez_id, s_id, bez, typ) values (2, 25, 'Price per traveler', 1128);
insert into bezeichnung (bez_id, s_id, bez, typ) values (3, 25, 'Price per group', 1128);

/* Currency type */
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 1, 'Wï¿½hrungstyp', 1129);
insert into bezeichnung (bez_id, s_id, bez, typ) values (0, 25, 'Currency type', 1129);

