/*D********************************************/
/* Default:   Aktion REVENU REPORT STATISTIK  */
/* Company:   Demo                            */
/*                                            */
/* Copyright: yafra.org, Switzerland   */
/**********************************************/

delete from aktionstexte where typ = 1017 and s_id = 1;

insert into aktionstexte values (1, 1, 1, 'lp -ob -o12', 1017); 
commit work;
insert into aktionstexte values (2, 1, 1, 'lp -dsmall  -ob -o12', 1017); 
commit work;
insert into aktionstexte values (3, 1, 1, 'lp -dpiccolo -ob -o12', 1017); 
commit work;
insert into aktionstexte values (4, 1, 1, 'lp -dwenger -ob -o12 ', 1017); 
commit work;
insert into aktionstexte values (5, 1, 1, '39', 1017);
commit work;
insert into aktionstexte values (6, 1, 1, '0', 1017);
commit work;
insert into aktionstexte values (7, 1, 1, '1', 1017);
commit work;
insert into aktionstexte values (8, 1, 1, '3', 1017);
commit work;
insert into aktionstexte values (9, 1, 1, '9', 1017);
commit work;
insert into aktionstexte values (10, 1, 1, '2', 1017);
commit work;
insert into aktionstexte values (11,  1, 1, 'REVENUE REPORT', 1017);
commit work;
insert into aktionstexte values (12,  1, 1, 'Seite: ', 1017);
commit work;

insert into aktionstexte values (13,  1, 1, 'Leader @%-18.18s', 1017);
commit work;
insert into aktionstexte values (14,  1, 1, 'Alt @ %-3.3s', 1017);
commit work;
insert into aktionstexte values (15,  1, 1, 'Kateg. @ %7.7s', 1017);
commit work;
insert into aktionstexte values (16,  1, 1, 'Kat.Preis @ %10.10s', 1017);
commit work;
insert into aktionstexte values (17,  1, 1, 'Status 1 2 3 @ %-20.20s', 1017);
commit work;
insert into aktionstexte values (18,  1, 1, 'Redukt. @ %10.10s', 1017);
commit work;
insert into aktionstexte values (19,  1, 1, 'Fares @ %10.10s', 1017);
commit work;
insert into aktionstexte values (20,  1, 1, 'GIT Satz@ %5.5s', 1017);
commit work;
insert into aktionstexte values (21,  1, 1, 'GIT @ %10.10s', 1017);
commit work;
insert into aktionstexte values (22,  1, 1, 'Tot.Fares @ %10.10s', 1017);
commit work;
insert into aktionstexte values (23,  1, 1, 'Kom.FCZ @ %10.10s', 1017);
commit work;
insert into aktionstexte values (24,  1, 1, 'Total Net @ %10.10s', 1017);
commit work;
insert into aktionstexte values (25,  1, 1, ' @ %0.0s', 1017);
commit work;

insert into aktionstexte values (26,  1, 1, 'Total', 1017);
commit work;
insert into aktionstexte values (27,  1, 1, 'Unterbr.Taxe Erw.', 1017);
commit work;
insert into aktionstexte values (28,  1, 1, 'Unterbr.Taxe Kind', 1017);
commit work;
insert into aktionstexte values (29,  1, 1, 'Total mit Taxe', 1017);
commit work;
insert into aktionstexte values (30,  1, 1, 'Transport', 1017);
commit work;
insert into aktionstexte values (31,  1, 1, 'Total netto FCP', 1017);
commit work;
insert into aktionstexte values (32,  1, 1, 'Pax free', 1017);
commit work;
insert into aktionstexte values (33,  1, 1, 'Uebertrag', 1017);
commit work;

insert into aktionstexte values (34, 1, 1, '4', 1017);
commit work;
insert into aktionstexte values (35, 1, 1, '2', 1017);
commit work;
insert into aktionstexte values (36, 1, 1, '7', 1017);
commit work;
insert into aktionstexte values (37,  1, 1, 'Reference @%-10.10s', 1017);
commit work;
insert into aktionstexte values (38,  1, 1, 'TO / TA @ %-18.17s', 1017);
commit work;
insert into aktionstexte values (39,  1, 1, '600', 1017);
commit work;

