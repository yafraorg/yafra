/*D************************************************************/
/* Default:   Aktion KONTROLLAKTION     OUT_D_option.sql      */
/* Company:   Demo                                            */
/*                                                            */              
/* Copyright: yafra.org, Switzerland                   */
/**************************************************************/
 
delete from aktionstexte where typ = 1016 and s_id = 1;

insert into aktionstexte values (1,  1, 1, 'lp -onb -oc', 1016);
commit work;
insert into aktionstexte values (2,  1, 1, 'lp -dsmall -onb -oc', 1016);
commit work;
insert into aktionstexte values (3,  1, 1, 'lp -dpiccolo -onb -oc', 1016);
commit work;
insert into aktionstexte values (4,  1, 1, 'lp -dwenger -onb -oc', 1016);
commit work;
insert into aktionstexte values (5,  1, 1, '71', 1016);
commit work;
insert into aktionstexte values (6,  1, 1, '10',  1016);
commit work;
insert into aktionstexte values (7,  1, 1, 'OPTION VERFALL LISTE', 1016);
commit work;
insert into aktionstexte values (8,  1, 1, 'Seite:', 1016);
commit work;
insert into aktionstexte values (9,  1, 1, 'Source Status: ', 1016);
commit work;
insert into aktionstexte values (10,  1, 1, 'Target Status: ', 1016);
commit work;
insert into aktionstexte values (11,  1, 1, 'Anzahl Reservationen: ', 1016);
commit work;
insert into aktionstexte values (12, 1, 1, 'Date X @ %-9.9s ', 1016);
commit work;
insert into aktionstexte values (13, 1, 1, 'Buchung @ %-9.9s ', 1016);
commit work;
insert into aktionstexte values (14, 1, 1, 'Name @ %-19.19s ', 1016);
commit work;
insert into aktionstexte values (15, 1, 1, 'Dienstleistung @ %-31.31s ', 1016);
commit work;
insert into aktionstexte values (16, 1, 1, 'Kollektiv @ %-11.11s ', 1016);
commit work;
insert into aktionstexte values (17, 1, 1, 'Rechnungstelle @ %-21.21s ', 1016);
commit work;
insert into aktionstexte values (18, 1, 1, 'Modif. @ %-9.9s ', 1016);
commit work;
insert into aktionstexte values (19, 1, 1, 'Opt.KUN @ %-9.9s ', 1016);
commit work;
insert into aktionstexte values (20, 1, 1, 'Opt.LIF @ %-9.9s ', 1016);
commit work;


