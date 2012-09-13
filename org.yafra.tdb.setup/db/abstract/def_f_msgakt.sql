/**************************************************************
 *
 * yafra.org                            DEF_F_msgakt.sql
 *
 * action messages definition
 *
 * DEF_F_msgakt
 *
 **************************************************************/


delete from msg where msg.msg_typ = 6 and msg.s_id = 2;

insert into msg values (6, 0, 2, 1,
'Tout est en ordre');

insert into msg values (6, 1, 2, 1,
'**** Message d''erreur *****');

insert into msg values (6, 2, 2, 1,
'**** Erreur du syst�me d''exploitation ****');

insert into msg values (6, 3, 2, 1,
'**** Erreur base de donn�es ****');

insert into msg values (6, 4, 2, 1,
'Avertissez votre service technique de cette erreur');

insert into msg values (6, 5, 2, 1,
'Produit le          : %s %s');

insert into msg values (6, 6, 2, 1,
'Produit par         : %s');

insert into msg values (6, 7, 2, 1,
'Prestation          : %d  %s');

insert into msg values (6, 8, 2, 1,
'Support             : %d  %s  %s');

insert into msg values (6, 9, 2, 1,
'Num�ro FAX/TLX      : %s %s');

insert into msg values (6, 10, 2, 1,
'Pages               : %d');

insert into msg values (6, 11, 2, 1,
'Sortie sur          : %s');

insert into msg values (6, 12, 2, 1,
'Action Termin�e');

insert into msg values (6, 13, 2, 1,
'Mode d''execution    : %s');

insert into msg values (6, 14, 2, 1,
'L''action n''a pu �tre d�marr�e: soit elle a d�j� �t� lanc�e par une');
insert into msg values (6, 14, 2, 2,
' autre personne,  soit elle n''est pas executable');

insert into msg values (6, 15, 2, 1,
'Erreur de lecture d''un objet:  soit l''objet n''existe pas');
insert into msg values (6, 15, 2, 2,
'soit il y a un probl�me du syst�me de base de donn�e');

insert into msg values (6, 16, 2, 1,
'Param�tres insuffisants ou erronn�s lors de l''invocation de l''action');
insert into msg values (6, 16, 2, 2,
'Relancez en v�rifiant les param�tres !');

insert into msg values (6, 17, 2, 1,
'Nom du fichier      : %s');

insert into msg values (6, 18, 2, 1,
'L''action du dossier %d est d�j� lanc�e');

insert into msg values (6, 19, 2, 1,
'L''action du dossier %d a d�j� �t� correctement execut�e');

insert into msg values (6, 20, 2, 1,
'L''action du dossier %d avec un status: %s ne peut �tre execut�e');

insert into msg values (6, 21, 2, 1,
'L''action du dossier %d n''est pas executable');

insert into msg values (6, 22, 2, 1,
'Une erreur base de donn�es emp�che la pr�paration de l''action');
insert into msg values (6, 22, 2, 2,
'pour le dossier %d');

insert into msg values (6, 23, 2, 1,
'L''action du dossier %d est pass�e � l''�tat -en erreur- ');

insert into msg values (6, 24, 2, 1,
'L''action du dossier %d est pass�e � l''�tat -non executable- ');

insert into msg values (6, 25, 2, 1,
'Erreur dans la confirmation de l''action de la r�servation %d');

insert into msg values (6, 26, 2, 1,
'Une erreur base de donn�es emp�che la r�alisation de l''action.');
insert into msg values (6, 26, 2, 2,
'Interruption');

insert into msg values (6, 27, 2, 1,
'Offre               : %d  %s');

insert into msg values (6, 28, 2, 1,
'Prestation partielle: %d  %s');

insert into msg values (6, 29, 2, 1,
'Dossier             : %d  %s');

insert into msg values (6, 30, 2, 1,
'Il y a un probl�me dans le traitement de l''appareil de sortie');

insert into msg values (6, 31, 2, 1,
'Le dossier %s a plus que 2 interruptions, des parties manquent !');

insert into msg values (6, 32, 2, 1,
'Dans le dossier %s, le prix n''est pas correct pour la prestation: %s');

insert into msg values (6, 33, 2, 1,
'Status courant     : %s');

insert into msg values (6, 34, 2, 1,
'Status vis�        : %s');

insert into msg values (6, 35, 2, 1,
'Il y a un probl�me dans l''allocation du fichier de sortie: OutBuffer');

insert into msg values (6, 36, 2, 1,
'Arrangement        : %d  %s');

insert into msg values (6, 37, 2, 1,
'Les param�tres choisis ne sont pas compatible pour l''execution de l''action');

insert into msg values (6, 38, 2, 1,
'Dans le dossier %s, il y a trop de commission  %s');

insert into msg values (6, 39, 2, 1,
'Dans le dossier %s, il doit exister au moins une commission %s');

insert into msg values (6, 40, 2, 1,
'Prix pour ID=%d, DLTT_ID=%d, KAT_ID=%d, RKR_ID=%d, DLA_ID=%d, DL_ID=%d !');

insert into msg values (6, 41, 2, 1,
'%d Prix trouvee.');
