/**************************************************************/
/*                                                            */
/* yafra.org                                           */
/*                                                            */
/* system messages definition                                 */
/*                                                            */
/**************************************************************/

delete from msg where msg.msg_typ = 5 and msg.s_id = 1;

insert into msg values (5, 0, 1, 1,
'Falls Sie diese Fehlermeldung nicht verstehen, melden Sie es umgehend');
insert into msg values (5, 0, 1, 2,
'Ihrer Supportstelle. Sie koennen dies mit einem Fehlerprotokoll tun.');
insert into msg values (5, 0, 1, 3,
'Besten Dank fuer Ihr Verstaendnis.');

insert into msg values (5, 1, 1, 1,
'Interner Fehler bei der Erzeugung eines Fehlertextes !');
insert into msg values (5, 1, 1, 2,
'Supportstelle umgehend benachrichtigen !');

insert into msg values (5, 2, 1, 1,
'Zum Status %d mit der Sprache %d wurde keine Meldung gefunden');

insert into msg values (5, 3, 1, 1,
'Interner Systemfehler beim allozieren von Memory !');
insert into msg values (5, 3, 1, 2,
'Supportstelle umgehend benachrichtigen !');

insert into msg values (5, 4, 1, 1,
'                    F E H L E R   -   P R O T O K O L L');
insert into msg values (5, 4, 1, 2,
'                  =======================================');
insert into msg values (5, 4, 1, 3,
'Datum: %s        Uhrzeit: %s        Benutzer: %s');
insert into msg values (5, 4, 1, 4, 'Datenbank: %s');
insert into msg values (5, 4, 1, 5, 'Version: %s');
insert into msg values (5, 4, 1, 6, '');
