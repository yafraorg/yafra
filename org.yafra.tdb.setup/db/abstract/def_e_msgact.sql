/**************************************************************/
/*                                                            */
/* yafra.org                        DEF_D_msgakt.sql   */
/*                                                            */
/* action messages definition                                 */
/*                                                            */
/**************************************************************/

delete from msg where msg.msg_typ = 6 and msg.s_id = 25;

insert into msg values (6, 0, 25, 1,
'alles in Ordnung');

insert into msg values (6, 1, 25, 1,
'**** Fehlermeldung *****');

insert into msg values (6, 2, 25, 1,
'**** Betriebssystemfehler ****');

insert into msg values (6, 3, 25, 1,
'**** Datenbankfehler ****');

insert into msg values (6, 4, 25, 1,
'Benachrichtigen Sie Ihre Supportstelle mit dieser Meldung');

insert into msg values (6, 5, 25, 1,
'Erstellt am        : %s %s');

insert into msg values (6, 6, 25, 1,
'Erstellt von       : %s');

insert into msg values (6, 7, 25, 1,
'Dienstleistung     : %d  %s');

insert into msg values (6, 8, 25, 1,
'DL-Traeger         : %d  %s %s');

insert into msg values (6, 9, 25, 1,
'FAX/TLX an Nummer  : %s %s');

insert into msg values (6, 10, 25, 1,
'Seiten             : %d');

insert into msg values (6, 11, 25, 1,
'Ausgabe auf        : %s');

insert into msg values (6, 12, 25, 1,
'Aktion ist beendet');

insert into msg values (6, 13, 25, 1,
'Ausfuehrungsart    : %s');

insert into msg values (6, 14, 25, 1,
'Aktion konnte nicht gestartet werden, weil sie schon in diesem Augenblick');
insert into msg values (6, 14, 25, 2,
'von jemanden gestartet wurde oder weil sie unausfuehrbar ist');

insert into msg values (6, 15, 25, 1,
'Fehler beim lesen eines Objektes - Entweder wurde kein Eintrag gefunden');
insert into msg values (6, 15, 25, 2,
'oder es liegt ein Systemfehler in der Datenbank vor');

insert into msg values (6, 16, 25, 1,
'Es wurden zu wenig oder falsche Parameter beim Aufruf der Aktion mitgegeben');
insert into msg values (6, 16, 25, 2,
'Bitte starten Sie die Aktion neu und achten Sie auf die Parameter !');

insert into msg values (6, 17, 25, 1,
'Dateiname          : %s');

insert into msg values (6, 18, 25, 1,
'Aktion zur Buchung %d wurde schon gestartet');

insert into msg values (6, 19, 25, 1,
'Aktion zur Buchung %d wurde schon erfolgreich ausgefuehrt');

insert into msg values (6, 20, 25, 1,
'Aktion zur Buchung: %d kann beim Status: %s nicht ausgefï¿½hrt werden');

insert into msg values (6, 21, 25, 1,
'Aktion zur Buchung %d ist unausfuehrbar');

insert into msg values (6, 22, 25, 1,
'In der Ausfertigung der Aktion zur Buchung %d liegt ein Datenbankfehler vor');

insert into msg values (6, 23, 25, 1,
'Die Aktion zur Buchung %d wurde auf den Status -fehlerhaft- gesetzt');

insert into msg values (6, 24, 25, 1,
'Die Aktion zur Buchung %d wurde auf den Status -unausfï¿½hrbar- gesetzt');

insert into msg values (6, 25, 25, 1,
'Fehler in Bestï¿½tigung der Aktion der Buchung %d');

insert into msg values (6, 26, 25, 1,
'In der Ausfertigung der Aktion liegt ein Datenbankfehler vor - Abbruch');

insert into msg values (6, 27, 25, 1,
'Angebot            : %d  %s');

insert into msg values (6, 28, 25, 1,
'Teildienstleistung : %d  %s');

insert into msg values (6, 29, 25, 1,
'Buchung            : %d  %s');

insert into msg values (6, 30, 25, 1,
'In der Device Behandlung liegt ein Fehler vor');

insert into msg values (6, 31, 25, 1,
'Die Buchung %s hat mehr als eine Unterbrechung, Teile werden fehlen !');

insert into msg values (6, 32, 25, 1,
'In der Buchung %s hat die Dienstleistung: %s ein Preisproblem');

insert into msg values (6, 33, 25, 1,
'Ausgangsstatus     : %s');

insert into msg values (6, 34, 25, 1,
'Zielstatus         : %s');

insert into msg values (6, 35, 25, 1,
'In der IO Buffer oder File Behandlung liegt ein Fehler vor');

insert into msg values (6, 36, 25, 1,
'Arrangement        : %d  %s');

insert into msg values (6, 37, 25, 1,
'Die gewaehlte Aktionsparameters sind nicht kompatible miteinander');

insert into msg values (6, 38, 25, 1,
'In der Buchung %s gibt es zuviel %s Kommissionen ');

insert into msg values (6, 39, 25, 1,
'In der Buchung %s gibt es keine %s Kommission');

insert into msg values (6, 40, 25, 1,
'Preis fuer ID=%d, DLTT_ID=%d, KAT_ID=%d, RKR_ID=%d, DLA_ID=%d, DL_ID=%d !');

insert into msg values (6, 41, 25, 1,
'%d Preise gefunden.');

insert into msg values (6, 42, 25, 1,
'Hauptkontingent    : %s');
