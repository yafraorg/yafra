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
'Erreur Base de donn�es - Des types de donn�es in�gales ont �t� utilis�es');
commit work;

insert into msg values (4, 2600, 2, 1,
'Erreur Base de donn�es - Le nombre utilis� est trop grand, la base');
insert into msg values (4, 2600, 2, 2,
'ne peut le traiter');
commit work;

insert into msg values (4, 2509, 2, 1,
'Erreur Base de donn�es - Une telle entr�e existe d�j� dans la base');
commit work;

insert into msg values (4, 2420, 2, 1,
'Erreur Base de donn�es - Trop de donn�es ou donn�es insuffisantes lors');
insert into msg values (4, 2420, 2, 2,
' de la rentr�e des donn�es dans la base');
commit work;

insert into msg values (4, 2295, 2, 1,
'Erreur Base de donn�es - Des valeurs clefs erronn�es ont �t� utilis�es');
insert into msg values (4, 2295, 2, 2,
' pour entrer ou modifier/effacer');
commit work;

insert into msg values (4, 2211, 2, 1,
'Erreur Base de donn�es - Une des erreurs est inconnue lors des op�rations');
insert into msg values (4, 2211, 2, 2,
' effectu�es sur la base');
commit work;

insert into msg values (4, 2103, 2, 1,
'Erreur Base de donn�es - Une op�ration est en cours sur la base; terminez ');
insert into msg values (4, 2103, 2, 2,
'le programme et demarrez � nouveau, si l''erreur se reproduit,');
insert into msg values (4, 2103, 2, 3,
'veuillez avertir votre service technique');
commit work;

insert into msg values (4, 2100, 2, 1,
'Erreur Base de donn�es - La base de donn�es n''a pas pu �tre ouverte;');
insert into msg values (4, 2100, 2, 2,
' v�rifiez-en le nom et le chemin d''acces');
commit work;

insert into msg values (4, 1006, 2, 1,
'Erreur Base de donn�es - Mot clef inconnu dans l''ordre');
commit work;

insert into msg values (4, 1004, 2, 1,
'Erreur Base de donn�es - Le caract�re final est manquant');
insert into msg values (4, 1004, 2, 2,
' dans un ordre interne');
commit work;

insert into msg values (4, 1001, 2, 1,
'Erreur Base de donn�es - Erreur de syntaxe g�nerale dans un ordre');
insert into msg values (4, 1001, 2, 2,
' pour la base de donn�es');
commit work;
