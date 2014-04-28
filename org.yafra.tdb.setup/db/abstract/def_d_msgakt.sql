/**************************************************************/
/*                                                            */
/* yafra.org                        DEF_D_msgakt.sql   */
/*                                                            */
/* action messages definition                                 */
/*                                                            */
/**************************************************************/

delete from msg where msg.msg_typ = 6 and msg.s_id = 1;

insert into msg values (6, 0, 1, 1,
'alles in Ordnung');

insert into msg values (6, 1, 1, 1,
'**** Fehlermeldung *****');

insert into msg values (6, 2, 1, 1,
'**** Betriebssystemfehler ****');

insert into msg values (6, 3, 1, 1,
'**** Datenbankfehler ****');

insert into msg values (6, 4, 1, 1,
'Benachrichtigen Sie Ihre Supportstelle mit dieser Meldung');

insert into msg values (6, 5, 1, 1,
'Erstellt am        : %s %s');

insert into msg values (6, 6, 1, 1,
'Erstellt von       : %s');

insert into msg values (6, 7, 1, 1,
'Dienstleistung     : %d  %s');

insert into msg values (6, 8, 1, 1,
'DL-Traeger         : %d  %s %s');

insert into msg values (6, 9, 1, 1,
'FAX/TLX an Nummer  : %s %s');

insert into msg values (6, 10, 1, 1,
'Seiten             : %d');

insert into msg values (6, 11, 1, 1,
'Ausgabe auf        : %s');

insert into msg values (6, 12, 1, 1,
'Aktion ist beendet');

insert into msg values (6, 13, 1, 1,
'Ausfuehrungsart    : %s');

insert into msg values (6, 14, 1, 1,
'Aktion konnte nicht gestartet werden, weil sie schon in diesem Augenblick');
insert into msg values (6, 14, 1, 2,
'von jemanden gestartet wurde oder weil sie unausfuehrbar ist');

insert into msg values (6, 15, 1, 1,
'Fehler beim lesen eines Objektes - Entweder wurde kein Eintrag gefunden');
insert into msg values (6, 15, 1, 2,
'oder es liegt ein Systemfehler in der Datenbank vor');

insert into msg values (6, 16, 1, 1,
'Es wurden zu wenig oder falsche Parameter beim Aufruf der Aktion mitgegeben');
insert into msg values (6, 16, 1, 2,
'Bitte starten Sie die Aktion neu und achten Sie auf die Parameter !');

insert into msg values (6, 17, 1, 1,
'Dateiname          : %s');

insert into msg values (6, 18, 1, 1,
'Aktion zur Buchung %d wurde schon gestartet');

insert into msg values (6, 19, 1, 1,
'Aktion zur Buchung %d wurde schon erfolgreich ausgefuehrt');

insert into msg values (6, 20, 1, 1,
'Aktion zur Buchung: %d kann beim Status: %s nicht ausgefï¿½hrt werden');

insert into msg values (6, 21, 1, 1,
'Aktion zur Buchung %d ist unausfuehrbar');

insert into msg values (6, 22, 1, 1,
'In der Ausfertigung der Aktion zur Buchung %d liegt ein Datenbankfehler vor');

insert into msg values (6, 23, 1, 1,
'Die Aktion zur Buchung %d wurde auf den Status -fehlerhaft- gesetzt');

insert into msg values (6, 24, 1, 1,
'Die Aktion zur Buchung %d wurde auf den Status -unausfï¿½hrbar- gesetzt');

insert into msg values (6, 25, 1, 1,
'Fehler in Bestï¿½tigung der Aktion der Buchung %d');

insert into msg values (6, 26, 1, 1,
'In der Ausfertigung der Aktion liegt ein Datenbankfehler vor - Abbruch');

insert into msg values (6, 27, 1, 1,
'Angebot            : %d  %s');

insert into msg values (6, 28, 1, 1,
'Teildienstleistung : %d  %s');

insert into msg values (6, 29, 1, 1,
'Buchung            : %d  %s');

insert into msg values (6, 30, 1, 1,
'In der Device Behandlung liegt ein Fehler vor');

insert into msg values (6, 31, 1, 1,
'Die Buchung %s hat mehr als eine Unterbrechung, Teile werden fehlen !');

insert into msg values (6, 32, 1, 1,
'In der Buchung %s hat die Dienstleistung: %s ein Preisproblem');

insert into msg values (6, 33, 1, 1,
'Ausgangsstatus     : %s');

insert into msg values (6, 34, 1, 1,
'Zielstatus         : %s');

insert into msg values (6, 35, 1, 1,
'In der IO Buffer oder File Behandlung liegt ein Fehler vor');

insert into msg values (6, 36, 1, 1,
'Arrangement        : %d  %s');

insert into msg values (6, 37, 1, 1,
'Die gewaehlte Aktionsparameters sind nicht kompatible miteinander');

insert into msg values (6, 38, 1, 1,
'In der Buchung %s gibt es zuviel %s Kommissionen ');

insert into msg values (6, 39, 1, 1,
'In der Buchung %s gibt es keine %s Kommission');

insert into msg values (6, 40, 1, 1,
'Preis fuer ID=%d, DLTT_ID=%d, KAT_ID=%d, RKR_ID=%d, DLA_ID=%d, DL_ID=%d !');

insert into msg values (6, 41, 1, 1,
'%d Preise gefunden.');

insert into msg values (6, 42, 1, 1,
'Hauptkontingent    : %s');
