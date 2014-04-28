/**************************************************************
 * DEF_F_msginf
 * yafra.org
 *
 * info messages/questions definition
 *
 **************************************************************/

delete from msg where msg.msg_typ = 3 and msg.s_id = 2;
commit work;

insert into msg values (3, 1000, 2, 1,
'Rï¿½server un autre Service ?');
commit work;

insert into msg values (3, 1001, 2, 1,
'Rï¿½server pour un autre voyager/client ?');
commit work;

insert into msg values (3, 1002, 2, 1,
'Les actions nï¿½cï¿½ssaires sont maintenant executï¿½es');
commit work;

insert into msg values (3, 1003, 2, 1,
'Votre rï¿½servation est prise en compte, la procï¿½dure est finie');
commit work;

insert into msg values (3, 1004, 2, 1,
'Infos rï¿½servation');
commit work;

insert into msg values (3, 1005, 2, 1,
'Rï¿½servation:         ');
commit work;

insert into msg values (3, 1006, 2, 1,
'Arrangement:     ');
commit work;

insert into msg values (3, 1007, 2, 1,
'Voyageur/Client: ');
commit work;

insert into msg values (3, 1008, 2, 1,
'Service partiel                                                 Status');
commit work;

insert into msg values (3, 1009, 2, 1,
'{}');
commit work;

insert into msg values (3, 1010, 2, 1,
'--');
commit work;

insert into msg values (3, 1011, 2, 1,
'Categories');
commit work;

insert into msg values (3, 1012, 2, 1,
'Action %s lancï¿½e.');
commit work;

insert into msg values (3, 1013, 2, 1,
'Veuillez vï¿½rifier votre boite aux lettres !');
commit work;

insert into msg values (3, 1014, 2, 1,
'Lieu de facturation: ');
commit work;

insert into msg values (3, 1015, 2, 1,
'Groupe:          ');
commit work;

insert into msg values (3, 1016, 2, 1,
'    Categorie           Support             Contingent');
commit work;
