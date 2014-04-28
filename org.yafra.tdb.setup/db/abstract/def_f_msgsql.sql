/**************************************************************
 *
 * yafra.org
 *
 * sql messages definition
 *
 **************************************************************/

delete from msg where msg.msg_typ = 4 and msg.s_id = 2;
commit work;

insert into msg values (4, 2609, 2, 1,
'Erreur Base de donnï¿½es - Des types de donnï¿½es inï¿½gales ont ï¿½tï¿½ utilisï¿½es');
commit work;

insert into msg values (4, 2600, 2, 1,
'Erreur Base de donnï¿½es - Le nombre utilisï¿½ est trop grand, la base');
insert into msg values (4, 2600, 2, 2,
'ne peut le traiter');
commit work;

insert into msg values (4, 2509, 2, 1,
'Erreur Base de donnï¿½es - Une telle entrï¿½e existe dï¿½jï¿½ dans la base');
commit work;

insert into msg values (4, 2420, 2, 1,
'Erreur Base de donnï¿½es - Trop de donnï¿½es ou donnï¿½es insuffisantes lors');
insert into msg values (4, 2420, 2, 2,
' de la rentrï¿½e des donnï¿½es dans la base');
commit work;

insert into msg values (4, 2295, 2, 1,
'Erreur Base de donnï¿½es - Des valeurs clefs erronnï¿½es ont ï¿½tï¿½ utilisï¿½es');
insert into msg values (4, 2295, 2, 2,
' pour entrer ou modifier/effacer');
commit work;

insert into msg values (4, 2211, 2, 1,
'Erreur Base de donnï¿½es - Une des erreurs est inconnue lors des opï¿½rations');
insert into msg values (4, 2211, 2, 2,
' effectuï¿½es sur la base');
commit work;

insert into msg values (4, 2103, 2, 1,
'Erreur Base de donnï¿½es - Une opï¿½ration est en cours sur la base; terminez ');
insert into msg values (4, 2103, 2, 2,
'le programme et demarrez ï¿½ nouveau, si l''erreur se reproduit,');
insert into msg values (4, 2103, 2, 3,
'veuillez avertir votre service technique');
commit work;

insert into msg values (4, 2100, 2, 1,
'Erreur Base de donnï¿½es - La base de donnï¿½es n''a pas pu ï¿½tre ouverte;');
insert into msg values (4, 2100, 2, 2,
' vï¿½rifiez-en le nom et le chemin d''acces');
commit work;

insert into msg values (4, 1006, 2, 1,
'Erreur Base de donnï¿½es - Mot clef inconnu dans l''ordre');
commit work;

insert into msg values (4, 1004, 2, 1,
'Erreur Base de donnï¿½es - Le caractï¿½re final est manquant');
insert into msg values (4, 1004, 2, 2,
' dans un ordre interne');
commit work;

insert into msg values (4, 1001, 2, 1,
'Erreur Base de donnï¿½es - Erreur de syntaxe gï¿½nerale dans un ordre');
insert into msg values (4, 1001, 2, 2,
' pour la base de donnï¿½es');
commit work;
