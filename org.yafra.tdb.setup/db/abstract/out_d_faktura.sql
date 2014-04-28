/*D***********************************************************/
/* Default:   Aktion FAKTURA                                 */    
/* Type:      _FAKTURA_TYP                                   */
/* Kunde:     Demo                                           */
/*                                                           */
/* Copyright: yafra.org, Aesch, Switzerland           */ 
/*************************************************************/


delete from aktionstexte where typ = 1002 and s_id = 1;

insert into aktionstexte values (1, 1, 1, 'lp -dlaser', 1002); 
insert into aktionstexte values (2, 1, 1, 'lp -dsmall',  1002); 
insert into aktionstexte values (3, 1, 1, 'lp -dpiccolo',  1002); 
insert into aktionstexte values (4, 1, 1, 'lp -dwenger',  1002); 

insert into aktionstexte values (5, 1, 1, '60', 1002);
insert into aktionstexte values (6, 1, 1, '0', 1002);
insert into aktionstexte values (7, 1, 1, '1', 1002);
insert into aktionstexte values (8, 1, 1, '3', 1002);
insert into aktionstexte values (9, 1, 1, '9', 1002);
insert into aktionstexte values (10, 1, 1, '2', 1002);
insert into aktionstexte values (11,  1, 1, 'Seite: ', 1002);

insert into aktionstexte values (12, 1, 1, 'RECHNUNG',             1002); 
insert into aktionstexte values (13, 1, 1, ', %.15s',          1002); 
insert into aktionstexte values (14, 1, 1, 'Abfahrtsdatum: %.10s', 1002); 
insert into aktionstexte values (15, 1, 1, 'RECHNUNG Nr.',         1002); 
insert into aktionstexte values (16, 1, 1, '(MWST Nr. 308192)',      1002); 

insert into aktionstexte values (17, 1, 1, 'Name @%-19.19s', 1002); 
insert into aktionstexte values (18, 1, 1, 'Kateg. @ %-7.7s', 1002); 
insert into aktionstexte values (19, 1, 1, 'Kab. @ %-5.5s', 1002);
insert into aktionstexte values (20, 1, 1, 'Brutto @ %11.11s', 1002); 
insert into aktionstexte values (21, 1, 1, 'Reduk1 @ %-8.8s', 1002); 
insert into aktionstexte values (22, 1, 1, 'Reduk2 @ %-8.8s', 1002); 
insert into aktionstexte values (23, 1, 1, 'Reduk3 @ %-8.8s', 1002); 
insert into aktionstexte values (24, 1, 1, 'Netto-Pax @ %11.11s', 1002); 
insert into aktionstexte values (25, 1, 1, 'Kom. @ %10.10s', 1002); 
insert into aktionstexte values (26, 1, 1, 'Netto @ %11.11s', 1002); 

insert into aktionstexte values (27, 1, 1, 'Total', 1002); 
insert into aktionstexte values (28, 1, 1, 'MWST Inlandanteil', 1002); 
insert into aktionstexte values (29, 1, 1, 'TOTAL NETTO inkl. MWST SFr.@%-73.73s',  1002); 


insert into aktionstexte values (30, 1, 1, 'Bemerkungen:', 1002); 

insert into aktionstexte values (31, 1, 1, 'Wir bitten Sie, die Anzahlung in den nï¿½chsten Tagen zu ï¿½berweisen.', 1002); 
insert into aktionstexte values (32, 1, 1, 'Der Restbetrag wird spï¿½testens 4 Wochen vor Abreise fï¿½llig.', 1002); 
insert into aktionstexte values (33, 1, 1, 'Die Dokumente werden wir Ihnen nach eingegangener Zahlung des gesamten', 1002); 
insert into aktionstexte values (34, 1, 1, 'Rechnungsbetrages (ca. 3 Wochen vor Abreise) zustellen.', 1002); 
insert into aktionstexte values (35, 1, 1, 'Mit Ihrer Anzahlung akzeptieren Sie die allgemeinen Vertragsbedingungen', 1002); 
insert into aktionstexte values (36, 1, 1, 'der Demo Touroperator AG. Diese entnehmen Sie bitte beiliegendem', 1002); 
insert into aktionstexte values (54, 1, 1, 'Separatdruck oder der aktuellen Hauptbroschï¿½re der Demo Touroperator AG.', 1002); 
insert into aktionstexte values (37, 1, 1, 'Inklusive 6.5%% MWST Inlandteil (Ihre Vorsteuer)', 1002); 

insert into aktionstexte values (38, 1, 1, 'Total Taxen  ', 1002); 
insert into aktionstexte values (39, 1, 1, 'Total Versicherung  ', 1002); 

insert into aktionstexte values (40, 1, 1, '10', 1002);
insert into aktionstexte values (41, 1, 1, '2', 1002);
insert into aktionstexte values (42, 1, 1, 'Taxe', 1002);
insert into aktionstexte values (43, 1, 1, '3', 1002);

insert into aktionstexte values (44, 1, 1, '4', 1002);
insert into aktionstexte values (45, 1, 1, '2', 1002);
insert into aktionstexte values (46, 1, 1, '7', 1002);

insert into aktionstexte values (47, 1, 1, '15', 1002);

insert into aktionstexte values (48, 1, 1, '9', 1002);
insert into aktionstexte values (49, 1, 1, '6', 1002); 

insert into aktionstexte values (50, 1, 1, 'Anreise ind. oder Bus Schweiz-Genua/Venedig', 1002); 
insert into aktionstexte values (51, 1, 1, 'Rï¿½ckreise ind. oder Bus Genua/Venedig-Schweiz', 1002);

insert into aktionstexte values (52, 1, 1, '9', 1002);

insert into aktionstexte values (53, 1, 1, '5', 1002);

insert into aktionstexte values (55, 1, 1, 'BITTE BEILIEGENDEN EINZAHLUNGSSCHEIN BENï¿½TZEN.', 1002); 

insert into aktionstexte values (56, 1, 1, 'Wir bitten Sie, die Rechnung bis spï¿½testens 4 Wochen vor Abreise', 1002); 
insert into aktionstexte values (57, 1, 1, 'zu begleichen. Die Dokumente werden wir Ihnen nach eingegangener Zahlung', 1002); 
insert into aktionstexte values (58, 1, 1, 'des gesamten Rechnungsbetrages (ca. 3 Wochen vor Abreise) zustellen.', 1002); 
insert into aktionstexte values (59, 1, 1, 'Mit Ihrer Bezahlung akzeptieren Sie die allgemeinen Vertragsbedingungen', 1002); 
insert into aktionstexte values (60, 1, 1, 'der Demo Touroperator AG. Diese entnehmen Sie bitte beiliegendem', 1002); 
insert into aktionstexte values (61, 1, 1, 'Separatdruck oder der aktuellen Hauptbroschï¿½re der Demo Touroperator AG.', 1002); 

insert into aktionstexte values (62, 1, 1, 'Wir bitten Sie, den Totalbetrag sogleich nach Erhalt der Rechnung auf', 1002); 
insert into aktionstexte values (63, 1, 1, 'unser Konto zu ï¿½berweisen. Die Dokumente werden wir Ihnen nach', 1002); 
insert into aktionstexte values (64, 1, 1, 'eingegangener Zahlung zustellen.', 1002); 
insert into aktionstexte values (65, 1, 1, 'Mit Ihrer Bezahlung akzeptieren Sie die allgemeinen Vertragsbedingungen', 1002); 
insert into aktionstexte values (66, 1, 1, 'der Demo Touroperator AG. Diese entnehmen Sie bitte beiliegendem', 1002); 
insert into aktionstexte values (67, 1, 1, 'Separatdruck oder der aktuellen Hauptbroschï¿½re der Demo Touroperator AG.', 1002); 
insert into aktionstexte values (68, 1, 1, 'Sind Ihre Einreisedokumente noch gï¿½ltig ?', 1002); 
commit work;
