/**************************************************************/
/*                                                            */
/* yafra.org                                           */
/*                                                            */
/* sql messages definition                                    */
/*                                                            */
/**************************************************************/

delete from msg where msg.msg_typ = 4 and msg.s_id = 25;

insert into msg values (4, 2609, 25, 1,
'Datenbankfehler - Es wurden intern ungleiche Datentypen gebraucht');

insert into msg values (4, 2600, 25, 1,
'Datenbankfehler - Es wurde eine zu grosse Zahl benutzt, die die Datenbank');
insert into msg values (4, 2600, 25, 2,
'nicht mehr bearbeiten kann');

insert into msg values (4, 2509, 25, 1,
'Datenbankfehler - Es besteht schon ein solcher Eintrag in der Datenbank');

insert into msg values (4, 2420, 25, 1,
'Datenbankfehler - Bei der Eingabe von Daten in die Datenbank wurden entweder');
insert into msg values (4, 2420, 25, 2,
'zuviel oder zuwenig Daten mitgegeben');

insert into msg values (4, 2301, 25, 1,
'Berechtigungsfehler - Sie haben keine Berechtigung um diese Transaktion');
insert into msg values (4, 2301, 25, 2,
'zustarten - Ihr Systemadministrator kennt Ihre Zugriffsrechte.');

insert into msg values (4, 2295, 25, 1,
'Datenbankfehler - Es wurde versucht ein Eintrag zu modifizieren/loeschen');
insert into msg values (4, 2295, 25, 2,
'oder eingeben mit fehlerhaften Schlï¿½sselbeziehungen');

insert into msg values (4, 2211, 25, 1,
'Datenbankfehler - Eines der Felder in der Datenbankoperation ist unbekannt');

insert into msg values (4, 2103, 25, 1,
'Datenbankfehler - Es ist schon eine Datenbankoperation im gange; beenden Sie');
insert into msg values (4, 2103, 25, 2,
'das Programm und starten es neu, falls der Fehler immer noch vorkommnt,');
insert into msg values (4, 2103, 25, 3,
'benachrichtigen Sie Ihre Supportstelle');

insert into msg values (4, 2100, 25, 1,
'Datenbankfehler - Die Datenbank konnte nicht geoeffnet werden; pruefen Sie');
insert into msg values (4, 2100, 25, 2,
'den Datenbank Pfad und Namen');

insert into msg values (4, 1006, 25, 1,
'Datenbankfehler - Unbekanntes Hauptwort im Datenbankbefehl');

insert into msg values (4, 1004, 25, 1,
'Datenbankfehler - Das Schlusszeichen in einem internen Datenbankbefehl fehlt');

insert into msg values (4, 1001, 25, 1,
'Datenbankfehler - Allgemeine Syntax verletzung im Datenbankbefehl');
