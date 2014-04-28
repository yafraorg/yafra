/*D******************************************/
/* Default:   Aktion Auftragsbestaetigung   */
/* Type:      _AUFTRAG_TYP (1001)           */
/* Kunde:     Demo                          */
/*                                          */
/* Copyright: yafra.org, Switzerland */
/********************************************/

delete from aktionstexte where typ = 1001 and s_id = 1;

insert into aktionstexte values (1, 1, 1, 'lp -onb -o12', 1001); 
insert into aktionstexte values (2, 1, 1, ' ',  1001); 
insert into aktionstexte values (3, 1, 1, ' ',  1001); 
insert into aktionstexte values (4, 1, 1, ' ',  1001); 
insert into aktionstexte values (5, 1, 1, ', den %.15s',    1001); 
insert into aktionstexte values (6, 1, 1, 'Abfahrtsdatum: %.10s', 1001); 
insert into aktionstexte values (7, 1, 1, 'Auftragsbestï¿½tigung',  1001); 
insert into aktionstexte values (8, 1, 1, 'Referenz-Nr:',         1001); 
insert into aktionstexte values (9,  1, 1, ' ', 1001); 
insert into aktionstexte values (10, 1, 1, ' ', 1001); 
insert into aktionstexte values (11, 1, 1, ' ', 1001); 
insert into aktionstexte values (12, 1, 1, ' ', 1001); 
insert into aktionstexte values (13, 1, 1, ' ', 1001); 
insert into aktionstexte values (14, 1, 1, 'Besten Dank fï¿½r Ihren Auftrag', 1001); 
insert into aktionstexte values (15, 1, 1, 'Subtotal', 1001); 
insert into aktionstexte values (16, 1, 1, 'RECHNUNGSTOTAL       sFr.',  1001); 
insert into aktionstexte values (17, 1, 1, ' ', 1001); 
insert into aktionstexte values (18, 1, 1, 'BRUTTO', 1001); 
insert into aktionstexte values (19, 1, 1, 'SUBTOTAL', 1001); 
insert into aktionstexte values (20, 1, 1, 'ABZUG', 1001); 
insert into aktionstexte values (21, 1, 1, 'NETTO', 1001); 
insert into aktionstexte values (22, 1, 1, 'REDUK.', 1001); 
insert into aktionstexte values (23, 1, 1, 'UEBERTRAG', 1001); 

insert into aktionstexte values (1, 25, 1, 'lp -onb -o12', 1001); 
insert into aktionstexte values (2, 25, 1, ' ',  1001); 
insert into aktionstexte values (3, 25, 1, ' ',  1001); 
insert into aktionstexte values (4, 25, 1, ' ',  1001); 
insert into aktionstexte values (5, 25, 1, ', den %.15s',    1001); 
insert into aktionstexte values (6, 25, 1, 'Abfahrtsdatum: %.10s', 1001); 
insert into aktionstexte values (7, 25, 1, 'Auftragsbestï¿½tigung',  1001); 
insert into aktionstexte values (8, 25, 1, 'Referenz-Nr:',         1001); 
insert into aktionstexte values (9,  25, 1, ' ', 1001); 
insert into aktionstexte values (10, 25, 1, ' ', 1001); 
insert into aktionstexte values (11, 25, 1, ' ', 1001); 
insert into aktionstexte values (12, 25, 1, ' ', 1001); 
insert into aktionstexte values (13, 25, 1, ' ', 1001); 
insert into aktionstexte values (14, 25, 1, 'Besten Dank fï¿½r Ihren Auftrag', 1001); 
insert into aktionstexte values (15, 25, 1, 'Subtotal', 1001); 
insert into aktionstexte values (16, 25, 1, 'RECHNUNGSTOTAL       sFr.',  1001); 
insert into aktionstexte values (17, 25, 1, ' ', 1001); 
insert into aktionstexte values (18, 25, 1, 'BRUTTO', 1001); 
insert into aktionstexte values (19, 25, 1, 'SUBTOTAL', 1001); 
insert into aktionstexte values (20, 25, 1, 'ABZUG', 1001); 
insert into aktionstexte values (21, 25, 1, 'NETTO', 1001); 
insert into aktionstexte values (22, 25, 1, 'REDUK.', 1001); 
insert into aktionstexte values (23, 25, 1, 'UEBERTRAG', 1001); 

commit work;
