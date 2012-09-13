/*D******************************************/
/* Default:   Aktion PAX BUS                */
/* Company:   Demo                          */
/*                                          */                 
/* Copyright: yafra.org, Switzerland */
/********************************************/

delete from aktionstexte where typ = 1014 and s_id = 1;

insert into aktionstexte values (1,  1, 1, 'lp -ob -o12',           1014);
commit work;
insert into aktionstexte values (2,  1, 1, 'lp -dsmall -ob -o12',   1014);
commit work;
insert into aktionstexte values (3,  1, 1, 'lp -dpiccolo -ob -o12', 1014);
commit work;
insert into aktionstexte values (4,  1, 1, 'lp -dwenger -ob -o12',  1014);
commit work;
insert into aktionstexte values (5,  1, 1, '71', 1014);
commit work;
insert into aktionstexte values (6,  1, 1, '5', 1014);
commit work;
insert into aktionstexte values (7,  1, 1, '$6', 1014);
commit work;
insert into aktionstexte values (8,  1, 1, '$1 $2', 1014);
commit work;
insert into aktionstexte values (9,  1, 1, 'BUS PASSAGIER LISTE', 1014);
commit work;
insert into aktionstexte values (10,  1, 1, 'Seite: ', 1014);
commit work;
insert into aktionstexte values (11,  1, 1, 'Von:', 1014);
commit work;
insert into aktionstexte values (12,  1, 1, 'An :', 1014);
commit work;
insert into aktionstexte values (13,  1, 1, 'Route:', 1014);
commit work;
insert into aktionstexte values (14,  1, 1, 'ab', 1014);
commit work;
insert into aktionstexte values (15,  1, 1, 'an', 1014);
commit work;
insert into aktionstexte values (16,  1, 1, 'nach', 1014);
commit work;
insert into aktionstexte values (17,  1, 1, '%55.55s Subtotal: %d', 1014);
commit work;
insert into aktionstexte values (18,  1, 1, ' ', 1014);
commit work;
insert into aktionstexte values (19,  1, 1, 'Demo TO AG Z|rich', 1014);
commit work;
insert into aktionstexte values (20, 1, 1, 'Anr. @  %-3.3s', 1014);
commit work;
insert into aktionstexte values (21, 1, 1, 'Name @ %-18.18s', 1014);
commit work;
insert into aktionstexte values (22, 1, 1, 'Vorname @ %-15.15s', 1014);
commit work;
insert into aktionstexte values (23, 1, 1, 'Remarks @ %-23.23s', 1014);
commit work;
insert into aktionstexte values (24, 1, 1, ' ', 1014);
commit work;
insert into aktionstexte values (25, 1, 1, '%55.55s Anzahl Passagiere: %d', 1014);
commit work;
insert into aktionstexte values (26, 1, 1, 'Kollektiv @ %-10.10s', 1014);
commit work;
insert into aktionstexte values (27, 1, 1, 'Schiff @ %-10.10s', 1014);
commit work;
