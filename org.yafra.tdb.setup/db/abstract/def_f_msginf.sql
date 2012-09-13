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
'R�server un autre Service ?');
commit work;

insert into msg values (3, 1001, 2, 1,
'R�server pour un autre voyager/client ?');
commit work;

insert into msg values (3, 1002, 2, 1,
'Les actions n�c�ssaires sont maintenant execut�es');
commit work;

insert into msg values (3, 1003, 2, 1,
'Votre r�servation est prise en compte, la proc�dure est finie');
commit work;

insert into msg values (3, 1004, 2, 1,
'Infos r�servation');
commit work;

insert into msg values (3, 1005, 2, 1,
'R�servation:         ');
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
'Action %s lanc�e.');
commit work;

insert into msg values (3, 1013, 2, 1,
'Veuillez v�rifier votre boite aux lettres !');
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
