/**************************************************************/
/*                                                            */
/* yafra.org                                           */
/*                                                            */
/* info messages/questions definition                         */
/*                                                            */
/**************************************************************/

delete from msg where msg.msg_typ = 3 and s_id = 25;

insert into msg values (3, 1000, 25, 1,
'Noch eine Dienstleistung buchen ?');

insert into msg values (3, 1001, 25, 1,
'Noch einen Reisender/Kunde buchen ?');

insert into msg values (3, 1002, 25, 1,
'Noetige Aktionen werden nun gestartet');

insert into msg values (3, 1003, 25, 1,
'Ihre Buchung ist erfasst und der Buchungsvorgang beendet');

insert into msg values (3, 1004, 25, 1,
'Buchungsinfo');

insert into msg values (3, 1005, 25, 1,
'Buchung:         ');

insert into msg values (3, 1006, 25, 1,
'Arrangement:     ');

insert into msg values (3, 1007, 25, 1,
'Reisender/Kunde: ');

insert into msg values (3, 1008, 25, 1,
'Teil Dienstleistung                                             Status');

insert into msg values (3, 1009, 25, 1,
'{}');

insert into msg values (3, 1010, 25, 1,
'--');

insert into msg values (3, 1011, 25, 1,
'Kategorien');

insert into msg values (3, 1012, 25, 1,
'Aktion %s gestartet.');

insert into msg values (3, 1013, 25, 1,
'Bitte beachten Sie Ihren Briefkasten/mail !');

insert into msg values (3, 1014, 25, 1,
'Rechnungsstelle: ');

insert into msg values (3, 1015, 25, 1,
'Gruppe:          ');

insert into msg values (3, 1016, 25, 1,
'    Kategorie           Trï¿½ger              Kontingent');

insert into msg values (3, 1017, 25, 1,
'Ja');

insert into msg values (3, 1018, 25, 1,
'Nein');
