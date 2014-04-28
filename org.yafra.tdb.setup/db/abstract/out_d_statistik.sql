/*D************************************************************/
/* Default:   Aktion STATISTIK                OUT_D_statistik */
/* Company:   Demo                                            */
/*                                                            */
/* Copyright: yafra.org, Switzerland                   */
/**************************************************************/


delete from root.aktionstexte where typ = 1011 and s_id = 1;

insert into root.aktionstexte values (1, 1, 1, 'Seite', 1011); 
commit work;
insert into root.aktionstexte values (2, 1, 1, 'Total', 1011); 
commit work;
insert into root.aktionstexte values (3, 1, 1, 'Kategorie', 1011); 
commit work;
insert into root.aktionstexte values (4, 1, 1, 'Kapazitï¿½t', 1011); 
commit work;
insert into root.aktionstexte values (5, 1, 1, 'lp -onb -oc -olandscape',1011); 
commit work;
insert into root.aktionstexte values (6, 1, 1, 'Buchungen', 1011); 
commit work;
insert into root.aktionstexte values (7, 1, 1, '%', 1011); 
commit work;
insert into root.aktionstexte values (8, 1, 1, 'Optionen', 1011); 
commit work;
insert into root.aktionstexte values (9, 1, 1, '%', 1011); 
commit work;
insert into root.aktionstexte values (10, 1, 1, 'Einkauf', 1011); 
commit work;
insert into root.aktionstexte values (11, 1, 1, 'Umsatz', 1011); 
commit work;
insert into root.aktionstexte values (12, 1, 1, 'Reduktion', 1011); 
commit work;
insert into root.aktionstexte values (13, 1, 1, 'Marge in %', 1011); 
commit work;
insert into root.aktionstexte values (14, 1, 1, 'Marge', 1011); 
commit work;
insert into root.aktionstexte values (15, 1, 1, 'S T A T I S T I K', 1011); 
commit work;
insert into root.aktionstexte values (16, 1, 1, '-----------------', 1011); 
commit work;
insert into root.aktionstexte values (17, 1, 1, 'Buchungen %', 1011); 
commit work;
insert into root.aktionstexte values (18, 1, 1, 'Optionen %', 1011); 
commit work;
insert into root.aktionstexte values (19, 1, 1, 'ohne Kategorie', 1011); 
commit work;
