/**************************************************************/
/*                                                            */
/* yafra.org                                           */
/*                                                            */
/* info messages/questions definition                         */
/*                                                            */
/**************************************************************/

delete from msg where msg.msg_typ = 3 and s_id = 1;

insert into msg values (3, 1000, 1, 1,
'Noch eine Dienstleistung buchen ?');

insert into msg values (3, 1001, 1, 1,
'Noch einen Reisender/Kunde buchen ?');

insert into msg values (3, 1002, 1, 1,
'Noetige Aktionen werden nun gestartet');

insert into msg values (3, 1003, 1, 1,
'Ihre Buchung ist erfasst und der Buchungsvorgang beendet');

insert into msg values (3, 1004, 1, 1,
'Buchungsinfo');

insert into msg values (3, 1005, 1, 1,
'Buchung:         ');

insert into msg values (3, 1006, 1, 1,
'Arrangement:     ');

insert into msg values (3, 1007, 1, 1,
'Reisender/Kunde: ');

insert into msg values (3, 1008, 1, 1,
'Teil Dienstleistung                                             Status');

insert into msg values (3, 1009, 1, 1,
'{}');

insert into msg values (3, 1010, 1, 1,
'--');

insert into msg values (3, 1011, 1, 1,
'Kategorien');

insert into msg values (3, 1012, 1, 1,
'Aktion %s gestartet.');

insert into msg values (3, 1013, 1, 1,
'Bitte beachten Sie Ihren Briefkasten/mail !');

insert into msg values (3, 1014, 1, 1,
'Rechnungsstelle: ');

insert into msg values (3, 1015, 1, 1,
'Gruppe:          ');

insert into msg values (3, 1016, 1, 1,
'    Kategorie           Trï¿½ger              Kontingent');

insert into msg values (3, 1017, 1, 1,
'Ja');

insert into msg values (3, 1018, 1, 1,
'Nein');
