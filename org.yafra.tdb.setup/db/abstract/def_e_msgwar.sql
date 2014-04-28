/**************************************************************/
/*                                                            */
/* yafra.org                                           */
/*                                                            */
/* warning messages definition                                */
/*                                                            */
/**************************************************************/

delete from msg where msg.msg_typ = 2 and msg.s_id = 25;

insert into msg values (2, 178, 25, 1,
'In einer Buchung wird immer noch auf dieses Arrangement verwiesen');
insert into msg values (2, 178, 25, 2,
'Bitte zuerst diese Buchung loeschen');

insert into msg values (2, 500, 25, 1,
'Konnte kein Arbeitsspeicher freigeben, bitte MarcoPolo beenden');
insert into msg values (2, 500, 25, 2,
'und neu beginnen. Falls dann der Fehler immer noch auftritt, umgehend');
insert into msg values (2, 500, 25, 3,
'Ihre Supportstelle mit dieser Meldung benachritigen !');

insert into msg values (2, 501, 25, 1,
'Dieser Dienstleistungstrï¿½ger wird noch von anderen Dienstleistungstrï¿½gern');
insert into msg values (2, 501, 25, 2,
'benï¿½tigt. Wollen Sie sowohl diesen und auch die anderen lï¿½schen ?');

insert into msg values (2, 502, 25, 1,
'Wollen Sie die Bezeichnungen und Beschreibungen/Texte einer bestehenden');
insert into msg values (2, 502, 25, 2,
'Sprache in die neue kopieren ?');

insert into msg values (2, 503, 25, 1,
'Wollen Sie die Kommissionssï¿½tze unter dieser Kommission ebenfalls lï¿½schen ?');

insert into msg values (2, 504, 25, 1,
'Wollen Sie die bestehenden Dienstleistungen ï¿½ndern ?');

insert into msg values (2, 505, 25, 1,
'Wollen Sie Reisenden komplett lï¿½schen ?');
