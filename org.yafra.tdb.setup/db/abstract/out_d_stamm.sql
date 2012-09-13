/*D***********************************************/
/* Default:   Aktion STAMM LISTE                 */ 
/* Company:   Demo                               */
/*                                               */
/* Copyright: yafra.org, Switzerland      */
/*************************************************/

delete from aktionstexte where typ = 1015;

insert into aktionstexte values (1,  1, 1, 'lp -oc', 1015);
insert into aktionstexte values (2,  1, 1, 'lp -dsmall -oc', 1015);
insert into aktionstexte values (3,  1, 1, 'lp -dpiccolo -oc', 1015);
insert into aktionstexte values (4,  1, 1, 'lp -dwenger  -oc', 1015);
insert into aktionstexte values (5,  1, 1, '71', 1015);
insert into aktionstexte values (6,  1, 1, '5', 1015);
insert into aktionstexte values (7,  1, 1, '$6', 1015);
insert into aktionstexte values (8,  1, 1, '$1 $2', 1015);
insert into aktionstexte values (9,  1, 1, 'STAMM DATEN CONTROL LISTE', 1015);
insert into aktionstexte values (10,  1, 1, 'Seite: ', 1015);
insert into aktionstexte values (11,  1, 1, 'Von:', 1015);
insert into aktionstexte values (12,  1, 1, 'An :', 1015);
insert into aktionstexte values (13,  1, 1, 'Route:', 1015);
insert into aktionstexte values (14,  1, 1, 'ab', 1015);
insert into aktionstexte values (15,  1, 1, 'an', 1015);
insert into aktionstexte values (16,  1, 1, 'nach', 1015);
insert into aktionstexte values (17,  1, 1, '%55.55s Subtotal: %d', 1015);
insert into aktionstexte values (18,  1, 1, ' ', 1015);
insert into aktionstexte values (19,  1, 1, 'Demo AG Basel', 1015);
insert into aktionstexte values (20, 1, 1, 'Anr. @  %-3.3s', 1015);
insert into aktionstexte values (21, 1, 1, 'Name @ %-18.18s', 1015);
insert into aktionstexte values (22, 1, 1, 'Vorname @ %-15.15s', 1015);
insert into aktionstexte values (23, 1, 1, 'Remarks @ %-40.40s', 1015);
insert into aktionstexte values (24, 1, 1, ' ', 1015);
insert into aktionstexte values (25, 1, 1, '%55.55s Anzahl Arrangments: %d', 1015);

insert into aktionstexte values (1,  25, 1, 'lp -oc', 1015);
insert into aktionstexte values (2,  25, 1, 'lp -dsmall -oc', 1015);
insert into aktionstexte values (3,  25, 1, 'lp -dpiccolo -oc', 1015);
insert into aktionstexte values (4,  25, 1, 'lp -dwenger  -oc', 1015);
insert into aktionstexte values (5,  25, 1, '71', 1015);
insert into aktionstexte values (6,  25, 1, '5', 1015);
insert into aktionstexte values (7,  25, 1, '$6', 1015);
insert into aktionstexte values (8,  25, 1, '$1 $2', 1015);
insert into aktionstexte values (9,  25, 1, 'STAMM DATEN CONTROL LISTE', 1015);
insert into aktionstexte values (10,  25, 1, 'Seite: ', 1015);
insert into aktionstexte values (11,  25, 1, 'Von:', 1015);
insert into aktionstexte values (12,  25, 1, 'An :', 1015);
insert into aktionstexte values (13,  25, 1, 'Route:', 1015);
insert into aktionstexte values (14,  25, 1, 'ab', 1015);
insert into aktionstexte values (15,  25, 1, 'an', 1015);
insert into aktionstexte values (16,  25, 1, 'nach', 1015);
insert into aktionstexte values (17,  25, 1, '%55.55s Subtotal: %d', 1015);
insert into aktionstexte values (18,  25, 1, ' ', 1015);
insert into aktionstexte values (19,  25, 1, 'Demo AG Basel', 1015);
insert into aktionstexte values (20, 25, 1, 'Anr. @  %-3.3s', 1015);
insert into aktionstexte values (21, 25, 1, 'Name @ %-18.18s', 1015);
insert into aktionstexte values (22, 25, 1, 'Vorname @ %-15.15s', 1015);
insert into aktionstexte values (23, 25, 1, 'Remarks @ %-40.40s', 1015);
insert into aktionstexte values (24, 25, 1, ' ', 1015);
insert into aktionstexte values (25, 25, 1, '%55.55s Anzahl Arrangments: %d', 1015);
commit work;
