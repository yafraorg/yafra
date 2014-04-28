/**************************************************************
 * DEF_F_msgsys
 * yafra.org
 *
 * system messages definition
 *
 **************************************************************/

delete from msg where msg.msg_typ = 5 and msg.s_id = 2;
commit work;

insert into msg values (5, 0, 2, 1,
'Dans le cas ou vous ne comprendriez pas ce message d''erreur,');
insert into msg values (5, 0, 2, 2,
' veuillez vour rï¿½fï¿½rer rapidement ï¿½ votre support technique.');
insert into msg values (5, 0, 2, 3,
'Vous pouvez utiliser un formulaire d''erreur.');
insert into msg values (5, 0, 2, 4,
'En comptant sur votre comprehension.');
commit work;

insert into msg values (5, 1, 2, 1,
'Erreur interne lors de la composition du texte d''erreur !');
insert into msg values (5, 1, 2, 2,
'Avertissez immï¿½diatement votre support technique !');
commit work;

insert into msg values (5, 2, 2, 1,
'Il n''a pas ï¿½tï¿½ trouvï¿½ d''information correspondante');
insert into msg values (5, 2, 2, 2,
'au status %d dans la langue %d ');
commit work;

insert into msg values (5, 3, 2, 1,
'Erreur systeme interne lors de l''allocation de mï¿½moire !');
insert into msg values (5, 3, 2, 2,
'Avertissez immï¿½diatement votre support technique !');
commit work;

insert into msg values (5, 4, 2, 1,
'                    M E S S A G E  D'' E R R E U R');
insert into msg values (5, 4, 2, 2,
'                    ===============================');
insert into msg values (5, 4, 2, 3,
'Date: %s        Heure: %s        Utilisateur: %s');
insert into msg values (5, 4, 2, 4, 'Database: %s');
insert into msg values (5, 4, 2, 5, 'Version: %s');
insert into msg values (5, 4, 2, 6, '');
commit work;
