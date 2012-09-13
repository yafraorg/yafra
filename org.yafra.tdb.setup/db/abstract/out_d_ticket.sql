/*D**********************************************/
/* Default:   Aktion TICKET                     */
/* Company:   Demo                              */
/*                                              */            
/* Copyright: yafra.org, Switzerland     */
/************************************************/

delete from aktionstexte where typ = 1005 and s_id = 1;

insert into aktionstexte values (1, 1, 1, 'lp -ob -o12', 1005); 
commit work;
insert into aktionstexte values (2, 1, 1, 'lp -dsmall  -ob -o12', 1005); 
commit work;
insert into aktionstexte values (3, 1, 1, 'lp -dpiccolo -ob -o12', 1005); 
commit work;
insert into aktionstexte values (4, 1, 1, 'lp -dwenger -ob -o12 ', 1005); 
commit work;
insert into aktionstexte values (5, 1, 1, '24', 1005);
commit work;
insert into aktionstexte values (6, 1, 1, '0', 1005);
commit work;
insert into aktionstexte values (7, 1, 1, '1', 1005);
commit work;
insert into aktionstexte values (8, 1, 1, '3', 1005);
commit work;
insert into aktionstexte values (9, 1, 1, '9', 1005);
commit work;
insert into aktionstexte values (10, 1, 1, '2', 1005);
commit work;
insert into aktionstexte values (11, 1, 1,
 '  XXXXXXXXXXXXXXXX XXXXXXXXXXX XXXXXXXXXXXXXXXX XXXXXXXXXXXXXXX
 XXXXXXXXXXXXXXXXXXXXX XXXXX XXXX', 1005); 
commit work;
insert into aktionstexte values (12, 1, 1, 'F C Z', 1005); 
commit work;
insert into aktionstexte values (13, 1, 1, 'Gtee', 1005); 
commit work;
 
insert into aktionstexte values (14, 1, 1, '4', 1005);
commit work;
insert into aktionstexte values (15, 1, 1, '2', 1005);
commit work;
insert into aktionstexte values (16, 1, 1, '7', 1005);
commit work;

insert into aktionstexte values (17, 1, 1, '2', 1005);
commit work;

insert into aktionstexte values (18, 1, 1, '9', 1005);
commit work;
