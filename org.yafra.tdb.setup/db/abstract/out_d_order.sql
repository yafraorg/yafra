/*D********************************************/
/* Default:   Aktion KONTROLLAKTION           */
/* Type:      _TYPE_ORDER_                    */
/* Company:   Demo                            */
/*                                            */
/* Copyright: yafra.org, Switzerland   */  
/**********************************************/

delete from aktionstexte where typ = 1013;

insert into aktionstexte values (1,  1, 1, 'lp -onb -oc', 1013);
insert into aktionstexte values (2,  1, 1, 'lp -dsmall -onb -oc', 1013);
insert into aktionstexte values (3,  1, 1, 'lp -dpiccolo -onb -oc', 1013);
insert into aktionstexte values (4,  1, 1, 'lp -dwenger -onb -oc', 1013);
insert into aktionstexte values (5,  1, 1, '71', 1013);
insert into aktionstexte values (6,  1, 1, '10',  1013);
insert into aktionstexte values (7,  1, 1, 'ORDER KONTROLLE', 1013);
insert into aktionstexte values (8,  1, 1, 'Seite:', 1013);
insert into aktionstexte values (9,  1, 1, 'Source Status: ', 1013);
insert into aktionstexte values (10,  1, 1, 'Target Status: ', 1013);
insert into aktionstexte values (11,  1, 1, 'Anzahl Reservationen: ', 1013);

insert into aktionstexte values (12, 1, 1, 'Date X @ %-9.9s ', 1013);
insert into aktionstexte values (13, 1, 1, 'Buchung @ %-9.9s ', 1013);
insert into aktionstexte values (14, 1, 1, 'Name @ %-19.19s ', 1013);
insert into aktionstexte values (15, 1, 1, 'Dienstleistung @ %-31.31s ', 1013);
insert into aktionstexte values (16, 1, 1, 'Kollektiv @ %-11.11s ', 1013);
insert into aktionstexte values (17, 1, 1, 'Rechnungstelle @ %-21.21s ', 1013);
insert into aktionstexte values (18, 1, 1, 'Modif. @ %-9.9s ', 1013);
insert into aktionstexte values (19, 1, 1, 'Status @ %-11.11s ', 1013);
insert into aktionstexte values (20, 1, 1, 'Opt.KUN @ %-9.9s ', 1013);

insert into aktionstexte values (1,  25, 1, 'lp -onb -oc', 1013);
insert into aktionstexte values (2,  25, 1, 'lp -dsmall -onb -oc', 1013);
insert into aktionstexte values (3,  25, 1, 'lp -dpiccolo -onb -oc', 1013);
insert into aktionstexte values (4,  25, 1, 'lp -dwenger -onb -oc', 1013);
insert into aktionstexte values (5,  25, 1, '71', 1013);
insert into aktionstexte values (6,  25, 1, '10',  1013);
insert into aktionstexte values (7,  25, 1, 'ORDER KONTROLLE', 1013);
insert into aktionstexte values (8,  25, 1, 'Seite:', 1013);
insert into aktionstexte values (9,  25, 1, 'Source Status: ', 1013);
insert into aktionstexte values (10,  25, 1, 'Target Status: ', 1013);
insert into aktionstexte values (11,  25, 1, 'Anzahl Reservationen: ', 1013);

insert into aktionstexte values (12, 25, 1, 'Date X @ %-9.9s ', 1013);
insert into aktionstexte values (13, 25, 1, 'Buchung @ %-9.9s ', 1013);
insert into aktionstexte values (14, 25, 1, 'Name @ %-19.19s ', 1013);
insert into aktionstexte values (15, 25, 1, 'Dienstleistung @ %-31.31s ', 1013);
insert into aktionstexte values (16, 25, 1, 'Kollektiv @ %-11.11s ', 1013);
insert into aktionstexte values (17, 25, 1, 'Rechnungstelle @ %-21.21s ', 1013);
insert into aktionstexte values (18, 25, 1, 'Modif. @ %-9.9s ', 1013);
insert into aktionstexte values (19, 25, 1, 'Status @ %-11.11s ', 1013);
insert into aktionstexte values (20, 25, 1, 'Opt.KUN @ %-9.9s ', 1013);
commit work;

