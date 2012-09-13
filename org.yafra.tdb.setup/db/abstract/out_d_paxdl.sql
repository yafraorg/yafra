/*D********************************************/
/* Default:   Aktion freie PAX_DL_LISTE       */
/* Company:   Demo                            */
/*                                            */
/* Copyright: yafra.org, Switzerland   */ 
/**********************************************/
 
delete from aktionstexte where typ = 1019 and s_id = 1;

insert into aktionstexte values (1,  1, 1, 'lp -onb -oc', 1019);
commit work;
insert into aktionstexte values (2,  1, 1, 'lp -dsmall -onb -oc', 1019);
commit work;
insert into aktionstexte values (3,  1, 1, 'lp -dpiccolo -onb -oc', 1019);
commit work;
insert into aktionstexte values (4,  1, 1, 'lp -dwenger -onb -oc', 1019);
commit work;
insert into aktionstexte values (5,  1, 1, '71', 1019);
commit work;
insert into aktionstexte values (6,  1, 1, '10',  1019);
commit work;

insert into aktionstexte values (7,  1, 1, 'PAX Liste fuer Arrangement: ', 1019);
commit work;
insert into aktionstexte values (8,  1, 1, 'Dienstleistung            : ', 1019);
commit work;

insert into aktionstexte values (9, 1, 1, 'Nr. @ %-6.6s', 1019); 
commit work;
insert into aktionstexte values (10, 1, 1, 'BID @ %-5.5s', 1019); 
commit work;
insert into aktionstexte values (11, 1, 1, 'Reisender @ %-30.30s', 1019); 
commit work;
insert into aktionstexte values (12, 1, 1, 'PERS_ID @ %-7.7s', 1019);
commit work;
insert into aktionstexte values (13, 1, 1, 'Kollektiv @ %-20.20s', 1019); 
commit work;
insert into aktionstexte values (14, 1, 1, 'Status @ %-10.10s', 1019); 
commit work;

insert into aktionstexte values (15, 1, 1, 'KEINE REISENDEN IN DIESER DL IN DIESEM ARR !', 1019); 
commit work;

insert into aktionstexte values (16, 1, 1, 'Seite Nr. ', 1019); 
commit work;
