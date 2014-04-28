
/* file def_e_aktionenbez, that is contains english description of features */
delete from bezeichnung where typ =21 and s_id = 25 and BEZ_ID > 0;
delete from bezeichnung where typ =21 and s_id = 1 and BEZ_ID > 0;

/* file def_aktionen, that is language independant */
delete from aktionsgrp;
delete from aktionen where AKT_ID >= 0;

-- standard lifecycle
insert into aktionen (AKT_ID, BEZ_ID, TEXTID, A_FLAG, B_FLAG, M_FLAG, A_TYP_ID, B2_FLAG, FILE_ID)
 values (1, 1, -1, 1,-1, 6, 1, -1, -1);
insert into aktionen values (10, 10, -1, 4, 1, 6, 9, 2, -1);
insert into aktionen values (20, 20, -1, 4, 2, 6, 1, 3, -1);
insert into aktionen values (30, 30, -1, 4, 4, 6, 1, 5, -1);
insert into aktionen values (40, 40, -1, 4, 4, 6, 1, 5, -1);
insert into aktionen values (50, 50, -1, 4, 4, 6, 1, 5, -1);
insert into aktionen values (60, 60, -1, 4, 4, 6, 1, 5, -1);
insert into aktionen values (70, 70, -1, 4, 9, 6, 1, 10, -1);
insert into aktionen values (80, 80, -1, 4, 10, 6, 1, 10, -1);
insert into aktionen values (90, 90, -1, 4, 11, 6, 1, 12, -1);
/* grouping */
insert into aktionsgrp values (-1, 1, 1, 1);
insert into aktionsgrp values (1, 10, 1, 1);
insert into aktionsgrp values (1, 20, 2, 1);
insert into aktionsgrp values (1, 30, 3, 1);
insert into aktionsgrp values (1, 40, 4, 1);
insert into aktionsgrp values (1, 50, 5, 1);
insert into aktionsgrp values (1, 60, 6, 1);
insert into aktionsgrp values (1, 70, 7, 1);
insert into aktionsgrp values (1, 80, 8, 1);
insert into aktionsgrp values (1, 90, 9, 1);

insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 25, 'Standard Lifecycle', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (10, 25, 'Entry', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (20, 25, 'Requested', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (30, 25, 'Confirmation', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (40, 25, 'Offer', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (50, 25, 'Order', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (60, 25, 'Ticket', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (70, 25, 'Invoice', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (80, 25, 'Thank you', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (90, 25, 'Cancelation', 21);

insert into bezeichnung (bez_id, s_id, bez, typ) values (1, 1, 'Standard Lifecycle', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (10, 1, 'Eingabe', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (20, 1, 'Anfragen', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (30, 1, 'Bestätigung', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (40, 1, 'Offerte', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (50, 1, 'Bestellung', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (60, 1, 'Ticket', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (70, 1, 'Rechnung', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (80, 1, 'Dank', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (90, 1, 'Stornierung', 21);


-- demo lifecycle
insert into aktionen values (1000, 1000, -1, -1,-1, 6, 1, -1, -1);
insert into aktionen values (1010, 1010, -1, 4,1000, 6, 1, 2666, -1);
insert into aktionen values (1020, 1020, -1, 4,2000, 6, 1, 5000, -1);
insert into aktionen values (1030, 1030, -1, 4,3000, 6, 1, 6000, -1);
insert into aktionen values (1040, 1040, -1, 4,4502, 6, 1, 5000, -1);
-- grouping demo lifecycle
insert into aktionsgrp values (-1, 1000, 1, 1000);
insert into aktionsgrp values (1000, 1010, 1, 1000);
insert into aktionsgrp values (1000, 1020, 2, 1000);
insert into aktionsgrp values (1000, 1030, 3, 1000);
insert into aktionsgrp values (1000, 1040, 4, 1000);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1000, 25, 'Demo Folder Life Cycle', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1010, 25, 'DEMO - Entry', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1020, 25, 'DEMO - Offer', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1030, 25, 'DEMO - Invoice', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1040, 25, 'DEMO - Cancel', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1000, 1, 'Demo Folder Life Cycle', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1010, 1, 'DEMO - Eingabe', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1020, 1, 'DEMO - Offerte', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1030, 1, 'DEMO - Rechnung', 21);
insert into bezeichnung (bez_id, s_id, bez, typ) values (1040, 1, 'DEMO - Storno', 21);


