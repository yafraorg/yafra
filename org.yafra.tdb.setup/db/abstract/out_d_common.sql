/*D***********************************************/
/* Default:   General Action                     */
/* Type:      _COMMON_TYP                        */
/*            Common texts for all actions       */
/*                                               */
/* Copyright: yafra.org, Switzerland      */
/*************************************************/

delete from aktionstexte where typ = 1099;

insert into aktionstexte values (1, 1, 1, 'lp -oc',             1099);
insert into aktionstexte values (2, 1, 1, 'lp -o12',            1099);
insert into aktionstexte values (3, 1, 1, 'lp -oc -olandscape', 1099);
insert into aktionstexte values (4, 1, 1, 'Seite:',                  1099);
insert into aktionstexte values (5, 1, 1, 'Gruppe/Kollektiv:',       1099);
insert into aktionstexte values (6, 1, 1, 'Teilnehmer:',             1099);
insert into aktionstexte values (7, 1, 1, 'Dienstleistungen:',       1099);
insert into aktionstexte values (8, 1, 1, 'Guarantee',               1099);
insert into aktionstexte values (9, 1, 1, 'z.Hd. %.25s',              1099);
insert into aktionstexte values (10, 1, 1, 'Gtee',                   1099);
insert into aktionstexte values (11, 1, 1, 'LB,GB', 1099);
insert into aktionstexte values (12, 1, 1, 'SGL', 1099);
insert into aktionstexte values (13, 1, 1, 'DBL', 1099);
insert into aktionstexte values (14, 1, 1, 'TPL', 1099);
insert into aktionstexte values (15, 1, 1, 'QD', 1099);
insert into aktionstexte values (16, 1, 1, 'notepad %s', 1099);
insert into aktionstexte values (17, 1, 1, '\\work\\bin\\psedit -f %s -display %s:0', 1099);
insert into aktionstexte values (18, 1, 1, '1,2,3,4,5,6,7,8,9,10,11,12,13,14,15', 1099);
insert into aktionstexte values (19, 1, 1, '$1 $7', 1099);
insert into aktionstexte values (20, 1, 1, '$114', 1099);

insert into aktionstexte values (1, 25, 1, 'lp -oc',             1099);
insert into aktionstexte values (2, 25, 1, 'lp -o12',            1099);
insert into aktionstexte values (3, 25, 1, 'lp -oc -olandscape', 1099);
insert into aktionstexte values (4, 25, 1, 'Seite:',                  1099);
insert into aktionstexte values (5, 25, 1, 'Gruppe/Kollektiv:',       1099);
insert into aktionstexte values (6, 25, 1, 'Teilnehmer:',             1099);
insert into aktionstexte values (7, 25, 1, 'Dienstleistungen:',       1099);
insert into aktionstexte values (8, 25, 1, 'Guarantee',               1099);
insert into aktionstexte values (9, 25, 1, 'z.Hd. %.25s',              1099);
insert into aktionstexte values (10, 25, 1, 'Gtee',                   1099);
insert into aktionstexte values (11, 25, 1, 'LB,GB', 1099);
insert into aktionstexte values (12, 25, 1, 'SGL', 1099);
insert into aktionstexte values (13, 25, 1, 'DBL', 1099);
insert into aktionstexte values (14, 25, 1, 'TPL', 1099);
insert into aktionstexte values (15, 25, 1, 'QD', 1099);
insert into aktionstexte values (16, 25, 1, 'notepad %s', 1099);
insert into aktionstexte values (17, 25, 1, '\\work\\bin\\psedit -f %s -display %s:0', 1099);
insert into aktionstexte values (18, 25, 1, '1,2,3,4,5,6,7,8,9,10,11,12,13,14,15', 1099);
insert into aktionstexte values (19, 25, 1, '$1 $7', 1099);
insert into aktionstexte values (20, 25, 1, '$114', 1099);
commit work;
