/*D*******************************************/
/* Default:   Aktion STATDLT                 */
/* Company:   Demo                           */
/*                                           */
/* Copyright: yafra.org, Switzerland  */  
/*********************************************/

delete from aktionstexte where typ = 1018;

insert into aktionstexte values (1, 1, 1, 'lp -dlaser ', 1018); 
insert into aktionstexte values (2, 1, 1, 'lp -dsmall ', 1018); 
insert into aktionstexte values (3, 1, 1, 'lp -dpiccolo ', 1018); 
insert into aktionstexte values (4, 1, 1, 'lp -dwenger ', 1018); 
insert into aktionstexte values (5, 1, 1, 'Benutzungsgrad fuer %s: %s', 1018);
insert into aktionstexte values (6, 1, 1, 'fuer Dienstleistung: %s', 1018);
insert into aktionstexte values (7, 1, 1, 'TOTAL Einheiten in dieser KATEGORIE: %d (%d)', 1018);
insert into aktionstexte values (8, 1, 1, 'TOTAL Einheiten: %d (%d) ', 1018); 
insert into aktionstexte values (9, 1, 1, '%-2s%-21s%-2s%-39s%-2s%-21s', 1018);

insert into aktionstexte values (1, 25, 1, 'lp -dlaser ', 1018); 
insert into aktionstexte values (2, 25, 1, 'lp -dsmall ', 1018); 
insert into aktionstexte values (3, 25, 1, 'lp -dpiccolo ', 1018); 
insert into aktionstexte values (4, 25, 1, 'lp -dwenger ', 1018); 
insert into aktionstexte values (5, 25, 1, 'Benutzungsgrad fuer %s: %s', 1018);
insert into aktionstexte values (6, 25, 1, 'fuer Dienstleistung: %s', 1018);
insert into aktionstexte values (7, 25, 1, 'TOTAL Einheiten in dieser KATEGORIE: %d (%d)', 1018);
insert into aktionstexte values (8, 25, 1, 'TOTAL Einheiten: %d (%d) ', 1018); 
insert into aktionstexte values (9, 25, 1, '%-2s%-21s%-2s%-39s%-2s%-21s', 1018);
commit work;
