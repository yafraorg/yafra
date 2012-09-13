/*D**********************************************/
/* Default:   Aktion Annulation                 */
/* Company:   Demo                              */ 
/*                                              */
/* Copyright: yafra.org, Switzerland     */
/************************************************/

delete from aktionstexte where typ = 1012;

insert into aktionstexte values (1, 1, 1, 'Reisende:', 1012);
insert into aktionstexte values (2, 1, 1, 'Annulation vom:', 1012);
insert into aktionstexte values (3, 1, 1, 'Buchungsreferenz:', 1012);
insert into aktionstexte values (4, 1, 1, 'Status:', 1012);
insert into aktionstexte values (5, 1, 1, 'lp -onb -o12', 1012);
insert into aktionstexte values (6, 1, 1, 'vom', 1012);

insert into aktionstexte values (1, 25, 1, 'Reisende:', 1012);
insert into aktionstexte values (2, 25, 1, 'Annulation vom:', 1012);
insert into aktionstexte values (3, 25, 1, 'Buchungsreferenz:', 1012);
insert into aktionstexte values (4, 25, 1, 'Status:', 1012);
insert into aktionstexte values (5, 25, 1, 'lp -onb -o12', 1012);
insert into aktionstexte values (6, 25, 1, 'vom', 1012);
commit work;
