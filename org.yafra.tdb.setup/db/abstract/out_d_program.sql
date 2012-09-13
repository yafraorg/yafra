/*D********************************************/
/* Default:   Aktion PROGRAMM                 */
/* Company:   Demo                            */
/*                                            */
/* Copyright: yafra.org, Switzerland   */  
/**********************************************/


delete from aktionstexte where typ = 1004;

insert into aktionstexte values (1, 1, 1,
 '%sR E I S E P R O G R A M M%s', 1004);
insert into aktionstexte values (2, 1, 1, 'Traeger:', 1004);
insert into aktionstexte values (3, 1, 1, 'Kategorie:', 1004);
insert into aktionstexte values (4, 1, 1, 'Kabine:', 1004);
insert into aktionstexte values (5, 1, 1,
 '%sDATUM    TAG  BESCHREIBUNG                              AN     AB   %s',
 1004);
insert into aktionstexte values (6, 1, 1,
 '%s--------------------------------------------------------------------%s',
 1004);
insert into aktionstexte values (7, 1, 1, '-----', 1004);
insert into aktionstexte values (8, 1, 1, 'lp -onb -o12', 1004);
insert into aktionstexte values (9, 1, 1, 'garantiert', 1004);
insert into aktionstexte values (10, 1, 1, '60', 1004);
insert into aktionstexte values (11, 1, 1, '0', 1004);
insert into aktionstexte values (12, 1, 1, 'Seite: ', 1004);
insert into aktionstexte values (13, 1, 1, '11', 1004);

insert into aktionstexte values (1, 25, 1,
 '%sR E I S E P R O G R A M M%s', 1004);
insert into aktionstexte values (2, 25, 1, 'Traeger:', 1004);
insert into aktionstexte values (3, 25, 1, 'Kategorie:', 1004);
insert into aktionstexte values (4, 25, 1, 'Kabine:', 1004);
insert into aktionstexte values (5, 25, 1,
 '%sDATUM    TAG  BESCHREIBUNG                              AN     AB   %s',
 1004);
insert into aktionstexte values (6, 25, 1,
 '%s--------------------------------------------------------------------%s',
 1004);
insert into aktionstexte values (7, 25, 1, '-----', 1004);
insert into aktionstexte values (8, 25, 1, 'lp -onb -o12', 1004);
insert into aktionstexte values (9, 25, 1, 'garantiert', 1004);
insert into aktionstexte values (10, 25, 1, '60', 1004);
insert into aktionstexte values (11, 25, 1, '0', 1004);
insert into aktionstexte values (12, 25, 1, 'Seite: ', 1004);
insert into aktionstexte values (13, 25, 1, '11', 1004);
commit work;
