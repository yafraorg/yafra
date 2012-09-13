/**************************************************************/
/*                                                            */
/* yafra.org                                           */
/*                                                            */
/* system messages definition                                 */
/*                                                            */
/**************************************************************/

delete from msg where msg.msg_typ = 5 and msg.s_id = 25;

insert into msg values (5, 0, 25, 1,
'Falls Sie diese Fehlermeldung nicht verstehen, melden Sie es umgehend');
insert into msg values (5, 0, 25, 2,
'Ihrer Supportstelle. Sie koennen dies mit einem Fehlerprotokoll tun.');
insert into msg values (5, 0, 25, 3,
'Besten Dank fuer Ihr Verstaendnis.');

insert into msg values (5, 1, 25, 1,
'Interner Fehler bei der Erzeugung eines Fehlertextes !');
insert into msg values (5, 1, 25, 2,
'Supportstelle umgehend benachrichtigen !');

insert into msg values (5, 2, 25, 1,
'Zum Status %d mit der Sprache %d wurde keine Meldung gefunden');

insert into msg values (5, 3, 25, 1,
'Interner Systemfehler beim allozieren von Memory !');
insert into msg values (5, 3, 25, 2,
'Supportstelle umgehend benachrichtigen !');

insert into msg values (5, 4, 25, 1,
'                    E R R O R   -   P R O T O K O L L');
insert into msg values (5, 4, 25, 2,
'                  =====================================');
insert into msg values (5, 4, 25, 3,
'Date: %s         Time: %s           User: %s');
insert into msg values (5, 4, 25, 4, 'Database: %s');
insert into msg values (5, 4, 25, 5, 'Version: %s');
insert into msg values (5, 4, 25, 6, '');
