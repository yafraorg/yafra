/*D*********************************************/
/* Default:   Aktion KONTROLLAKTION            */
/* Type:      _CONTROL_TYP                     */
/*                                             */
/* Copyright: yafra.org, Switzerland    */ 
/***********************************************/


delete from aktionstexte where typ = 1009;

insert into aktionstexte values (1,  1, 1, 'lp -dlaser', 1009);
insert into aktionstexte values (2,  1, 1, 'lp -dsmall -onb -oc', 1009);
insert into aktionstexte values (3,  1, 1, 'lp -dpiccolo -onb -oc', 1009);
insert into aktionstexte values (4,  1, 1, 'lp -dlarge -onb -oc', 1009);
insert into aktionstexte values (5, 1, 1, ' Aktionskontrolle                                              Datum: %s', 1009);
insert into aktionstexte values (6, 1, 1, '                                                               Seite: %d', 1009);
insert into aktionstexte values (7, 1, 1, '--------------------------------------------------------------------------------', 1009);
insert into aktionstexte values (8,  1, 1, '66', 1009);

insert into aktionstexte values (1,  25, 1, 'lp -dlaser', 1009);
insert into aktionstexte values (2,  25, 1, 'lp -dsmall -onb -oc', 1009);
insert into aktionstexte values (3,  25, 1, 'lp -dpiccolo -onb -oc', 1009);
insert into aktionstexte values (4,  25, 1, 'lp -dlarge -onb -oc', 1009);
insert into aktionstexte values (5, 25, 1, ' Aktionskontrolle                                              Datum: %s', 1009);
insert into aktionstexte values (6, 25, 1, '                                                               Seite: %d', 1009);
insert into aktionstexte values (7, 25, 1, '--------------------------------------------------------------------------------', 1009);
insert into aktionstexte values (8,  25, 1, '66', 1009);
commit work;

