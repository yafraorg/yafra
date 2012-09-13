/*D*******************************************/
/* Default:   Aktion PASSAGIER               */
/* Company:   Demo                           */
/*                                           */
/* Copyright: yafra.org, Switzerland  */
/*********************************************/

delete from aktionstexte where typ = 1003 and s_id = 1;

insert into aktionstexte values (1,  1, 1, 'lp -ob -o12', 1003);
commit work;
insert into aktionstexte values (2,  1, 1, 'lp -dsmall -ob -o12', 1003);
commit work;
insert into aktionstexte values (3,  1, 1, 'lp -dpiccolo -ob -o12', 1003);
commit work;
insert into aktionstexte values (4,  1, 1, 'lp -dwenger  -o12 ', 1003);
commit work;
insert into aktionstexte values (5,  1, 1, '44', 1003);
commit work;
insert into aktionstexte values (6,  1, 1, '6', 1003);
commit work;
insert into aktionstexte values (7,  1, 1, '$1 $2', 1003);
commit work;
insert into aktionstexte values (8,  1, 1, 'P A S S A G I E R   L I S T E    Demo TO AG Z|rich', 1003);
commit work;
insert into aktionstexte values (9,  1, 1, 'Seite: ', 1003);
commit work;
insert into aktionstexte values (10,  1, 1, 'B.Nr @%-6.6s', 1003);
commit work;
insert into aktionstexte values (11,  1, 1, 'Ref.Nr @%-1.1s', 1003);
commit work;
insert into aktionstexte values (12, 1, 1, 'Route @ %-7.7s', 1003);
commit work;
insert into aktionstexte values (13, 1, 1, 'Kat/Kab/B @ %-13.13s', 1003);
commit work;
insert into aktionstexte values (14, 1, 1, 'Name @ %-15.15s', 1003);
commit work;
insert into aktionstexte values (15, 1, 1, 'Vorname @ %-10.10s', 1003);
commit work;
insert into aktionstexte values (16, 1, 1, 'G.@ %-1.1s', 1003);
commit work;
insert into aktionstexte values (17, 1, 1, 'S.@ %-1.1s', 1003);
commit work;
insert into aktionstexte values (18, 1, 1, 'GP Ref. @ %-8.8s', 1003);
commit work;
insert into aktionstexte values (19, 1, 1, 'Remarks @ %-23.23s', 1003);
commit work;
insert into aktionstexte values (20, 1, 1, 'Sit. @ %-4.4s', 1003);
commit work;
insert into aktionstexte values (21, 1, 1, 'Geb.Dat@ %-8.8s', 1003);
commit work;
insert into aktionstexte values (22, 1, 1, 'Geb.Ort@ %-13.13s', 1003);
commit work;
insert into aktionstexte values (23, 1, 1, 'PassNr.@ %-12.12s', 1003);
commit work;
insert into aktionstexte values (24, 1, 1, 'Nat.@ %-4.4s', 1003);
commit work;
insert into aktionstexte values (25, 1, 1, ' ', 1003);
commit work;
insert into aktionstexte values (26, 1, 1, 'gtee', 1003);
commit work;
insert into aktionstexte values (27, 1, 1, 'Anzahl Passagiere: %d', 1003);
commit work;
insert into aktionstexte values (28, 1, 1, 'Sprachen', 1003);
commit work;
insert into aktionstexte values (29, 1, 1, 'Transfer @ %-10.10s', 1003);
commit work;
insert into aktionstexte values (30,  1, 1, '$3 $4 $6 $7 $8 $12 $13', 1003);
commit work;
