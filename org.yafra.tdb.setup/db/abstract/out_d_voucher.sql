/*D**************************************************/
/* Default:   Aktion VOUCHER          OUT_D_voucher */
/* Company:   Demo                                  */
/*                                                  */ 
/* Copyright: yafra.org, Switzerland         */ 
/****************************************************/


delete from aktionstexte where typ = 1006;

insert into aktionstexte values (1, 1, 1, 'lp -ob -o12', 1006); 
insert into aktionstexte values (2, 1, 1, 'lp -dsmall  -ob -o12', 1006); 
insert into aktionstexte values (3, 1, 1, 'lp -dpiccolo -ob -o12', 1006); 
insert into aktionstexte values (4, 1, 1, 'lp -dwenger -ob -o12 ', 1006); 
insert into aktionstexte values (5, 1, 1, '18', 1006);
insert into aktionstexte values (6, 1, 1, '3', 1006);
insert into aktionstexte values (7, 1, 1, '%-81s%c%d', 1006);
insert into aktionstexte values (8, 1, 1, '%-2s%-21s%-6s%-21s%-9s%-12s%-6s%-10s', 1006); 
insert into aktionstexte values (9, 1, 1, '%-2s%-21s%-2s%-39s%-2s%-21s', 1006);

insert into aktionstexte values (1, 25, 1, 'lp -ob -o12', 1006); 
insert into aktionstexte values (2, 25, 1, 'lp -dsmall  -ob -o12', 1006); 
insert into aktionstexte values (3, 25, 1, 'lp -dpiccolo -ob -o12', 1006); 
insert into aktionstexte values (4, 25, 1, 'lp -dwenger -ob -o12 ', 1006); 
insert into aktionstexte values (5, 25, 1, '18', 1006);
insert into aktionstexte values (6, 25, 1, '3', 1006);
insert into aktionstexte values (7, 25, 1, '%-81s%c%d', 1006);
insert into aktionstexte values (8, 25, 1, '%-2s%-21s%-6s%-21s%-9s%-12s%-6s%-10s', 1006); 
insert into aktionstexte values (9, 25, 1, '%-2s%-21s%-2s%-39s%-2s%-21s', 1006);
commit work;
