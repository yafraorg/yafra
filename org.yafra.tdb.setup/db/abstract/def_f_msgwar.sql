/**************************************************************
 * DEF_F_msgvar
 * yafra.org
 *
 * warning messages definition
 *
 **************************************************************/

delete from msg where msg.msg_typ = 2 and msg.s_id = 2 ;
commit work;

insert into msg values (2, 178, 2, 1,
'Cet arrangement est toujours utilis� dans une r�servation');
insert into msg values (2, 178, 2, 2,
'Effacer d''abord cette r�servation');
commit work;

insert into msg values (2, 500, 2, 1,
'Impossible de lib�rer de la m�moire, stopper MarcoPolo');
insert into msg values (2, 500, 2, 2,
'et recommencer. Si l''erreur se reproduit,');
insert into msg values (2, 500, 2, 3,
'prendre contact avec le service technique!');
commit work;

insert into msg values (2, 501, 2, 1,
'Ce support est encore utilis� par d''autres supports.');
insert into msg values (2, 501, 2, 2,
'Voulez-vous effacer celui-ci et les autres ?');
commit work;

insert into msg values (2, 502, 2, 1,
'Voulez-vous copier les textes de d�signation et de description');
insert into msg values (2, 502, 2, 2,
'd''une langue dans la nouvelle ?');
commit work;

insert into msg values (2, 503, 2, 1,
'Voulez-vous �galement effacer les pourcentages sous cette commission?');
commit work;

insert into msg values (2, 504, 2, 1,
'Voulez-vous modifier les services?');
commit work;

insert into msg values (2, 505, 2, 1,
'Voulez-vous totalement effacer les voyageurs?');
commit work;
