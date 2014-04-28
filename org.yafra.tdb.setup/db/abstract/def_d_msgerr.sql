/***************************************************************/
/*                                                             */
/* yafra.org                                            */
/*                                                             */
/* error messages definition                                   */
/*                                                             */
/* DEF_D_msgerr                                                */
/*                                                             */
/***************************************************************/

/* delete from msg where msg.msg_typ = 1 */

delete from msg where msg.msg_typ = 1 and msg.msg_id = 0 and msg.s_id = 1;
insert into msg values (1, 0, 1, 1,
'kein Fehler - alles in Ordnung');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 1 and msg.s_id = 1;
insert into msg values (1, 1, 1, 1,
'Es ist ein allgemeiner Fehler aufgetreten. Falls keine weiteren');
insert into msg values (1, 1, 1, 2,
'Fehlermeldungen vorhanden sind, bitte umgehend melden.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 10 and msg.s_id = 1;
insert into msg values (1, 10, 1, 1,
'Fehler beim reservieren von Speicher. Programm beenden und eventuell');
insert into msg values (1, 10, 1, 2,
'den Server neu starten oder gar Ihren Rechner neu booten');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 11 and msg.s_id = 1;
insert into msg values (1, 11, 1, 1,
'Fehler im internen Protokoll zwischen grafischer Oberflaeche und der');
insert into msg values (1, 11, 1, 2,
'Datenbank. Bitte benachrichtigen Sie Ihre Supportstelle');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 14 and msg.s_id = 1;
insert into msg values (1, 14, 1, 1,
'Sie haben keine eindeutige Bezeichnung eingegeben; vermutlich ist ein');
insert into msg values (1, 14, 1, 2,
'Eintrag unter dieser Bezeichnung schon vorhanden');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 15 and msg.s_id = 1;
insert into msg values (1, 15, 1, 1,
'Das Programm kann den Menuinhalt nicht entschluesseln, es handelt sich hier');
insert into msg values (1, 15, 1, 2,
'um einen internen Fehler, den Sie Ihrer Supportstelle melden sollten');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 16 and msg.s_id = 1;
insert into msg values (1, 16, 1, 1,
'Die eingegebene Bezeichnung konnte nicht abgespeichert werden.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 18 and msg.s_id = 1;
insert into msg values (1, 18, 1, 1,
'Es konnte kein Eintrag in der Datenbank gefunden werden. Entweder ist noch');
insert into msg values (1, 18, 1, 2,
'kein Datensatz in der Datenbank oder Ihre globalen Einschraenkungen');
insert into msg values (1, 18, 1, 3,
'ergeben einen Konflikt');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 20 and msg.s_id = 1;
insert into msg values (1, 20, 1, 1,
'Informationen zum gewuenschten Objekt koennen nicht gelesen werden, da das');
insert into msg values (1, 20, 1, 2,
'Objekt nicht aktiviert ist. Wï¿½hlen Sie das gewuenschte Objekt zuerst aus');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 21 and msg.s_id = 1;
insert into msg values (1, 21, 1, 1,
'Keine gueltige Sprache vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 24 and msg.s_id = 1;
insert into msg values (1, 24, 1, 1,
'Es konnte KEIN Datensatz eingefuegt/modifiziert/geloescht werden.');
insert into msg values (1, 24, 1, 2,
'Beachten Sie bitte die obige englische Datenbankmeldung.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 25 and msg.s_id = 1;
insert into msg values (1, 25, 1, 1,
'Sie haben KEINE BERECHTIGUNG fuer diese Operation. Fragen Sie Ihren');
insert into msg values (1, 25, 1, 2,
'travelDB Administrator wegen Ihrer Berechtigungsstufe.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 26 and msg.s_id = 1;
insert into msg values (1, 26, 1, 1,
'Keine gueltige Bezeichnung vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 28 and msg.s_id = 1;
insert into msg values (1, 28, 1, 1,
'Fï¿½r dieses Objekt ist keine Aktion/Auswahl/Grafik vorgesehen - beachten');
insert into msg values (1, 28, 1, 2,
'Sie Ihre Unterlagen, dort ist vermerkt welches Objekt was kann');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 29 and msg.s_id = 1;
insert into msg values (1, 29, 1, 1,
'Es kann keine neue interne Identifikationsnummer vergeben werden.');
insert into msg values (1, 29, 1, 2,
'Bitte kontaktieren Sie umgehend Ihre Supportstelle mit dieser Meldung.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 30 and msg.s_id = 1;
insert into msg values (1, 30, 1, 1,
'Es wurde versucht eine ungueltige oder geschuetzte Bezeichnung zu');
insert into msg values (1, 30, 1, 2,
'lï¿½schen. Vermutlich besteht ein Programmfehler.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 35 and msg.s_id = 1;
insert into msg values (1, 35, 1, 1,
'Keine gueltige Kategorie vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 36 and msg.s_id = 1;
insert into msg values (1, 36, 1, 1,
'Kein gueltiger Dienstleistungstraeger vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 37 and msg.s_id = 1;
insert into msg values (1, 37, 1, 1,
'Kein gueltiger Dienstleistungstraegertyp vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 46 and msg.s_id = 1;
insert into msg values (1, 46, 1, 1,
'Kein gueltiges Angebot vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 47 and msg.s_id = 1;
insert into msg values (1, 47, 1, 1,
'Kein gueltiger Angebotstyp vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 48 and msg.s_id = 1;
insert into msg values (1, 48, 1, 1,
'Zu diesem Objekt ist keine Information vorhanden - aktivieren Sie ein Objekt');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 50 and msg.s_id = 1;
insert into msg values (1, 50, 1, 1,
'Die angegebene Dauer ist ungï¿½ltig');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 52 and msg.s_id = 1;
insert into msg values (1, 52, 1, 1,
'Kein gueltiger Kundentyp vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 59 and msg.s_id = 1;
insert into msg values (1, 59, 1, 1,
'Kein gueltiger Reisender-/Dienstleistungsnehmer-Typ vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 60 and msg.s_id = 1;
insert into msg values (1, 60, 1, 1,
'Kein gueltiger Reisender/Dienstleistungsnehmer vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 63 and msg.s_id = 1;
insert into msg values (1, 63, 1, 1,
'Auf dem Angebot muss ein gï¿½ltiger Trï¿½ger vergeben werden.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 64 and msg.s_id = 1;
insert into msg values (1, 64, 1, 1,
'Keine gueltige Saison vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 66 and msg.s_id = 1;
insert into msg values (1, 66, 1, 1,
'Sie mï¿½ssen sowohl das von-Datum wie auch das bis-Datum eingeben. Beachten');
insert into msg values (1, 66, 1, 2,
'Sie, dass das bis-Datum spï¿½ter ist als das von-Datum');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 67 and msg.s_id = 1;
insert into msg values (1, 67, 1, 1,
'Keine gueltige Waehrung vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 68 and msg.s_id = 1;
insert into msg values (1, 68, 1, 1,
'Kein gueltiges Land vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 72 and msg.s_id = 1;
insert into msg values (1, 72, 1, 1,
'Keine gueltige Ortschaft vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 74 and msg.s_id = 1;
insert into msg values (1, 74, 1, 1,
'Keine gueltige Waehrung vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 78 and msg.s_id = 1;
insert into msg values (1, 78, 1, 1,
'Kein gueltiges Programm vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 82 and msg.s_id = 1;
insert into msg values (1, 82, 1, 1,
'Kein gueltiges Arrangement vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 83 and msg.s_id = 1;
insert into msg values (1, 83, 1, 1,
'Keine gueltige Teil-Dienstleistung vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 84 and msg.s_id = 1;
insert into msg values (1, 84, 1, 1,
'Keine gueltige Dienstleistung vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 85 and msg.s_id = 1;
insert into msg values (1, 85, 1, 1,
'Keine gueltige Teildienstleistung fuer die Verknuepfung zur Dienstleistung');
insert into msg values (1, 85, 1, 2,
'ausgewaehlt. Bitte selektieren Sie die gewuenschten Teildienstleistungen !');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 87 and msg.s_id = 1;
insert into msg values (1, 87, 1, 1,
'Kein gueltiger Aktionstyp vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 88 and msg.s_id = 1;
insert into msg values (1, 88, 1, 1,
'Keine gueltige Aktion vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 90 and msg.s_id = 1;
insert into msg values (1, 90, 1, 1,
'Kein gueltiges Kontingent vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 91 and msg.s_id = 1;
insert into msg values (1, 91, 1, 1,
'Kein gueltiger Verwalter (als Kunde) vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 106 and msg.s_id = 1;
insert into msg values (1, 106, 1, 1,
'Keine gueltige Buchung vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 112 and msg.s_id = 1;
insert into msg values (1, 112, 1, 1,
'Es konnte kein Eintrag in der Datenbank gefunden werden');
insert into msg values (1, 112, 1, 2,
'Ueberpruefen Sie Ihre Eingaben und wiederholen Sie diese Aktion');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 117 and msg.s_id = 1;
insert into msg values (1, 117, 1, 1,
'Keine Ortschaft (fuer Personen) vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 118 and msg.s_id = 1;
insert into msg values (1, 118, 1, 1,
'Kein Name vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 119 and msg.s_id = 1;
insert into msg values (1, 119, 1, 1,
'Kein Vorname vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 120 and msg.s_id = 1;
insert into msg values (1, 120, 1, 1,
'Kein gueltiger Statuswert vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 123 and msg.s_id = 1;
insert into msg values (1, 123, 1, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 123, 1, 2,
'noch Angebote darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 123, 1, 3,
'Angebote mit diesem Dienstleistungstraeger');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 125 and msg.s_id = 1;
insert into msg values (1, 125, 1, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 125, 1, 2,
'noch Buchungen darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 125, 1, 3,
'Buchungen mit diesem Dienstleistungstraeger');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 126 and msg.s_id = 1;
insert into msg values (1, 126, 1, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 126, 1, 2,
'noch Grafiken darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 126, 1, 3,
'Grafiken zu diesem Dienstleistungstraeger');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 127 and msg.s_id = 1;
insert into msg values (1, 127, 1, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 127, 1, 2,
'noch Pixelbilder darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 127, 1, 3,
'Pixelbilder zu diesem Dienstleistungstraeger');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 128 and msg.s_id = 1;
insert into msg values (1, 128, 1, 1,
'Das gewuenschte Objekt konnte nicht aus der Datenbank geloescht werden');
insert into msg values (1, 128, 1, 2,
'Ueberpruefen Sie Ihre Eingaben und wiederholen Sie diese Aktion');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 129 and msg.s_id = 1;
insert into msg values (1, 129, 1, 1,
'Die Beschreibung des aktiven Objektes konnte nicht geloescht werden');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 130 and msg.s_id = 1;
insert into msg values (1, 130, 1, 1,
'Die Bezeichnung des aktiven Objektes konnte nicht geloescht werden');
insert into msg values (1, 130, 1, 2,
'Die Bezeichnung wird vermutlich in einem anderen Objekt noch benoetigt');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 141 and msg.s_id = 1;
insert into msg values (1, 141, 1, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 141, 1, 2,
'Teildienstleistung darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 141, 1, 3,
'alle Teildienstleistungen mit diesem Angebot');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 158 and msg.s_id = 1;
insert into msg values (1, 158, 1, 1,
'Der aktuelle Aktionstyp kann nicht geloescht werden, weil noch Aktionen');
insert into msg values (1, 158, 1, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst alle Aktionen die diesen');
insert into msg values (1, 158, 1, 3,
'Aktionstyp definiert haben');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 170 and msg.s_id = 1;
insert into msg values (1, 170, 1, 1,
'Das aktuelle Kollektiv/Gruppe kann nicht geloescht werden, weil noch');
insert into msg values (1, 170, 1, 2,
'Buchungen/Dossiers darauf definiert sind. Loeschen Sie zuerst diese.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 172 and msg.s_id = 1;
insert into msg values (1, 172, 1, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch');
insert into msg values (1, 172, 1, 2,
'ein Preis darauf definiert ist. Bitte loeschen Sie zuerst alle auf');
insert into msg values (1, 172, 1, 3,
'diese Dienstleistung definierten Preise');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 173 and msg.s_id = 1;
insert into msg values (1, 173, 1, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch ein');
insert into msg values (1, 173, 1, 2,
'Kontingent darauf definiert ist. Bitte loeschen Sie zuerst alle auf');
insert into msg values (1, 173, 1, 3,
'diese Dienstleistung definierten Kontingente');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 184 and msg.s_id = 1;
insert into msg values (1, 184, 1, 1,
'Die gewaehlte Kategorie oder die Menge der Kategorie deckt sich nicht');
insert into msg values (1, 184, 1, 2,
'mit der Definition auf dem Hauptkontingent. Pruefen Sie die');
insert into msg values (1, 184, 1, 3,
'Definition auf dem Hauptkontingent.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 185 and msg.s_id = 1;
insert into msg values (1, 185, 1, 1,
'Der gewaehlte Dienstleistungstraeger ist im Hauptkontingent nicht');
insert into msg values (1, 185, 1, 2,
'definiiert. Pruefen Sie die Definition auf dem Hauptkontingent.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 186 and msg.s_id = 1;
insert into msg values (1, 186, 1, 1,
'Sie muessen entweder eine Kategorie und deren Menge oder ein');
insert into msg values (1, 186, 1, 2,
'Dienstleistungstraeger fuer das Kontingentdetail definieren.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 187 and msg.s_id = 1;
insert into msg values (1, 187, 1, 1,
'Der gewaehlte Dienstleistungstraeger ist schon vergeben.');
insert into msg values (1, 187, 1, 2,
'Pruefen Sie die Definition aller Details zu diesen Kontingenten.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 188 and msg.s_id = 1;
insert into msg values (1, 188, 1, 1,
'Die Summe der Mengen der einzelnen Kontingentdetails ist zu gross.');
insert into msg values (1, 188, 1, 2,
'Pruefen Sie die Definition aller Details zu diesem Hauptkontingent.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 189 and msg.s_id = 1;
insert into msg values (1, 189, 1, 1,
'Das Kontingent ist bereits ausgebucht. Soll trotzdem gebucht werden ?');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 192 and msg.s_id = 1;
insert into msg values (1, 192, 1, 1,
'Sie kï¿½nnen eine Preis nur auf ein Dienstleistung oder ein Dienstleistungs-');
insert into msg values (1, 192, 1, 2,
'angebot definieren, aber nicht auf beide zur gleichen Zeit');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 194 and msg.s_id = 1;
insert into msg values (1, 194, 1, 1,
'Es ist im Moment keine gueltige Buchung aktiv. Aktivieren Sie eine');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 195 and msg.s_id = 1;
insert into msg values (1, 195, 1, 1,
'Es wurde kein gueltiges Buchungsobjekt gewaehlt. Ein Buchungsobjekt');
insert into msg values (1, 195, 1, 2,
'ist entweder eine Dienstleistung oder ein Arrangement');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 197 and msg.s_id = 1;
insert into msg values (1, 197, 1, 1,
'Es wurde keine gueltige Buchungsstelle und Rechnungsstelle gewaehlt');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 200 and msg.s_id = 1;
insert into msg values (1, 200, 1, 1,
'Kein gueltiges Geschlecht vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 203 and msg.s_id = 1;
insert into msg values (1, 203, 1, 1,
'Sie haben einen falschen Buchungsstatus gewaehlt. Dieser Buchungsstatus');
insert into msg values (1, 203, 1, 2,
'ist im jetzigen Zustand nicht moeglich.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 204 and msg.s_id = 1;
insert into msg values (1, 204, 1, 1,
'Es sind noch Dienstleistungen zu diesem Arrangement definiert; loeschen');
insert into msg values (1, 204, 1, 2,
'Sie diese zuerst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 205 and msg.s_id = 1;
insert into msg values (1, 205, 1, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch ein');
insert into msg values (1, 205, 1, 2,
'Arrangement darauf definiert ist. Bitte loeschen Sie zuerst alle auf');
insert into msg values (1, 205, 1, 3,
'diese Dienstleistung definierten Arrangements');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 206 and msg.s_id = 1;
insert into msg values (1, 206, 1, 1,
'Zu diesem Objekt ist weder eine Grafik noch eine Information vorhanden');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 208 and msg.s_id = 1;
insert into msg values (1, 208, 1, 1,
'In dieser Reservation ist ein Konflikt entstanden und konnte demzufolge');
insert into msg values (1, 208, 1, 2,
'nicht abgespeichert werden. Prï¿½fen Sie Ihre bisherigen Eingaben anhand des');
insert into msg values (1, 208, 1, 3,
'Info-Fensters.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 232 and msg.s_id = 1;
insert into msg values (1, 232, 1, 1,
'Sie haben vergessen einen Mussparameter zu fï¿½llen');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 244 and msg.s_id = 1;
insert into msg values (1, 244, 1, 1,
'Der aktuelle Aktionstyp kann nicht geloescht werden, weil noch Buchungen');
insert into msg values (1, 244, 1, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst alle Buchungen die diesen');
insert into msg values (1, 244, 1, 3,
'Aktionstyp ueber eine Aktion benoetigen. (AKTIONSDETAIL)');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 247 and msg.s_id = 1;
insert into msg values (1, 247, 1, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch unter-');
insert into msg values (1, 247, 1, 2,
'geordnete Angebote existieren. Ueber den Infromationsknopf erhalten');
insert into msg values (1, 247, 1, 3,
'Sie die detailierten Angaben');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 248 and msg.s_id = 1;
insert into msg values (1, 248, 1, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch Preise');
insert into msg values (1, 248, 1, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst');
insert into msg values (1, 248, 1, 3,
'alle Preise mit diesem Angebot');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 249 and msg.s_id = 1;
insert into msg values (1, 249, 1, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch Kontingente');
insert into msg values (1, 249, 1, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst');
insert into msg values (1, 249, 1, 3,
'alle Kontingente mit diesem Angebot');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 250 and msg.s_id = 1;
insert into msg values (1, 250, 1, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch Kommissionen');
insert into msg values (1, 250, 1, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst');
insert into msg values (1, 250, 1, 3,
'alle Kommissionen mit diesem Angebot');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 251 and msg.s_id = 1;
insert into msg values (1, 251, 1, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch');
insert into msg values (1, 251, 1, 2,
'untergeordnete Teildienstleistung existieren. Ueber den Infromationsknopf');
insert into msg values (1, 251, 1, 3,
'erhalten Sie die detailierten Angaben');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 252 and msg.s_id = 1;
insert into msg values (1, 252, 1, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 252, 1, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 252, 1, 3,
'alle Buchungen/Reservationen fuer diese Teildienstleistung (RESERVATION)');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 253 and msg.s_id = 1;
insert into msg values (1, 253, 1, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 253, 1, 2,
'Dienstleistung darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 253, 1, 3,
'alle Dienstleistungen mit dieser Teildienstleistung');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 254 and msg.s_id = 1;
insert into msg values (1, 254, 1, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 254, 1, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 254, 1, 3,
'alle Buchungen/Reservationen fuer diese Teildienstleistung (AKTIONSDETAIL)');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 256 and msg.s_id = 1;
insert into msg values (1, 256, 1, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 256, 1, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 256, 1, 3,
'alle Buchungen/Reservationen fuer diese Dienstleistung (RESERVATION)');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 257 and msg.s_id = 1;
insert into msg values (1, 257, 1, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 257, 1, 2,
'Kommission/Reduktion darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 257, 1, 3,
'alle Kommissionen/Reduktionen fuer diese Dienstleistung');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 258 and msg.s_id = 1;
insert into msg values (1, 258, 1, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 258, 1, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 258, 1, 3,
'alle Buchungen/Reservationen fuer diese Dienstleistung (AKTIONSDETAIL)');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 259 and msg.s_id = 1;
insert into msg values (1, 259, 1, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 259, 1, 2,
'Teildienstleistung darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 259, 1, 3,
'alle Teildienstleistungen fuer diese Dienstleistung');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 278 and msg.s_id = 1;
insert into msg values (1, 278, 1, 1,
'Das aktuelle Kollektiv/Gruppe kann nicht geloescht werden, weil beim');
insert into msg values (1, 278, 1, 2,
'Loeschen der Kollektiv/Gruppen Kommissionen ein Fehler aufgetreten ist.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 282 and msg.s_id = 1;
insert into msg values (1, 282, 1, 1,
'Keine gueltige Grafik vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 286 and msg.s_id = 1;
insert into msg values (1, 286, 1, 1,
'Dieser Dienstleistungstraeger ist nicht im ausgewaehlten Kontingent');
insert into msg values (1, 286, 1, 2,
'beinhaltet. Wollen Sie diese Angaben trotzdem speichern ?');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 287 and msg.s_id = 1;
insert into msg values (1, 287, 1, 1,
'Dieser Dienstleistungstraeger befindet sich im Kontingent');
insert into msg values (1, 287, 1, 2, '%s');
insert into msg values (1, 287, 1, 3,
'Buchen Sie in dieses Kontingent, waehlen Sie einen anderen Traeger,');
insert into msg values (1, 287, 1, 4,
'oder wollen Sie trotzdem mit diesen Angaben die Buchung speichern ?');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 289 and msg.s_id = 1;
insert into msg values (1, 289, 1, 1,
'Fehler beim schreiben des Buchungsdetails fuer den aktiven Reisenden');
insert into msg values (1, 289, 1, 2,
'Brechen Sie den Buchungsvorgang ab und beginnen Sie von neuem');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 292 and msg.s_id = 1;
insert into msg values (1, 292, 1, 1,
'Es konnte keine Kategorie fï¿½r diese Reservation gefunden werden');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 293 and msg.s_id = 1;
insert into msg values (1, 293, 1, 1,
'Fehler beim kopieren des Arrangenments');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 294 and msg.s_id = 1;
insert into msg values (1, 294, 1, 1,
'Fehler beim kopieren der Dienstleistung');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 297 and msg.s_id = 1;
insert into msg values (1, 297, 1, 1,
'Es kann keine Grafik im Loeschmodus angezeigt werden, Sie koennen nur');
insert into msg values (1, 297, 1, 2,
'eine Grafik und alle Verknuepfungen loeschen');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 303 and msg.s_id = 1;
insert into msg values (1, 303, 1, 1,
'Es kann fuer dieses Objekt keine maximum Identifikation zugeteilt werden');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 304 and msg.s_id = 1;
insert into msg values (1, 304, 1, 1,
'Es kann fuer dieses Objekt keine minimum Identifikation zugeteilt werden');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 313 and msg.s_id = 1;
insert into msg values (1, 313, 1, 1,
'Sie muessen zwingend eine Bezeichnung, Dateiname und Typ resp. Typcode');
insert into msg values (1, 313, 1, 2,
'eingeben resp. auswaehlen.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 314 and msg.s_id = 1;
insert into msg values (1, 314, 1, 1,
'Es konnte keine Identifikation zugeteilt werden. Versuchen Sie es noch');
insert into msg values (1, 314, 1, 2,
'einmal');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 315 and msg.s_id = 1;
insert into msg values (1, 315, 1, 1,
'Es konnten keine Bezeichnungen zur neuen Sprache kopiert werden');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 316 and msg.s_id = 1;
insert into msg values (1, 316, 1, 1,
'Es konnten keine Beschreibungen/Texte zur neuen Sprache kopiert werden');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 317 and msg.s_id = 1;
insert into msg values (1, 317, 1, 1,
'Sie koennen diese Sprache nicht loeschen, weil Sie die Systemsprache ist');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 318 and msg.s_id = 1;
insert into msg values (1, 318, 1, 1,
'Die Grafikdaten sind zu gross. Bitte einen Export durchfï¿½hren.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 319 and msg.s_id = 1;
insert into msg values (1, 319, 1, 1,
'Es ist kein Verantwortilcher zum aktuellen Kollektiv/Gruppe definiert.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 320 and msg.s_id = 1;
insert into msg values (1, 320, 1, 1,
'Aktion(en) konnte(n) nicht ausgefï¿½hrt werden. Prï¿½fen Sie Ihre Eingaben.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 321 and msg.s_id = 1;
insert into msg values (1, 321, 1, 1,
'Angebotstyp kann nicht gelï¿½scht werden, da er in der Angebotstabelle');
insert into msg values (1, 321, 1, 2,
'noch benï¿½tigt wird. Lï¿½schen Sie den entsprechenden Eintrag zuerst.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 322 and msg.s_id = 1;
insert into msg values (1, 322, 1, 1,
'Es sind keine Reservationsdaten zu der aktuellen Buchung vorhanden.');
insert into msg values (1, 322, 1, 2,
'Prï¿½fen Sie die Buchung ï¿½ber die Informationsfunktion.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 323 and msg.s_id = 1;
insert into msg values (1, 323, 1, 1,
'Auf diese Dienstleistung kann nicht gebucht werden. Die Reservationsart');
insert into msg values (1, 323, 1, 2,
'dieser Dienstleistung lï¿½sst dies nicht zu.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 324 and msg.s_id = 1;
insert into msg values (1, 324, 1, 1,
'Zu dieser Dienstleistung mï¿½ssen Sie das von- und bis-Datum eingeben.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 325 and msg.s_id = 1;
insert into msg values (1, 325, 1, 1,
'Es ist kein Dienstleistungstrï¿½ger mehr frei ! Wï¿½hlen Sie eine andere');
insert into msg values (1, 325, 1, 2,
'Dienstleistung oder ein anderes Datum !');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 326 and msg.s_id = 1;
insert into msg values (1, 326, 1, 1,
'Der ausgewï¿½hlte Dienstleistungstrï¿½ger hat nur Raum fï¿½r %d Person(en).');
insert into msg values (1, 326, 1, 2,
'Es wurde aber versucht %d Person(en) auf diesen Trï¿½ger zu buchen.');
insert into msg values (1, 326, 1, 3,
'Buchen Sie einen anderen Trï¿½ger oder in eine andere Kategorie.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 327 and msg.s_id = 1;
insert into msg values (1, 327, 1, 1,
'Der ausgewï¿½hlte Dienstleistungstrï¿½ger ist besetzt durch die Buchung %d.');
insert into msg values (1, 327, 1, 2,
'In dieser Buchung wurden %d Person(en) darauf gebucht.');
insert into msg values (1, 327, 1, 3,
'Soll troztdem gebucht werden ?');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 328 and msg.s_id = 1;
insert into msg values (1, 328, 1, 1,
'Der aktuelle Aktionstyp kann nicht geloescht werden, weil noch Aktions-');
insert into msg values (1, 328, 1, 2,
'parameter darauf definiert sind. Bitte loeschen Sie zuerst alle Parameter');
insert into msg values (1, 328, 1, 3,
'dieses Aktionstyps');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 329 and msg.s_id = 1;
insert into msg values (1, 329, 1, 1,
'Sie muessen eine Parameterbezeichnung im Feld Parameter eingeben');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 330 and msg.s_id = 1;
insert into msg values (1, 330, 1, 1,
'Sie koennen den Parameter nur als Flag definieren, wenn Sie keinen');
insert into msg values (1, 330, 1, 2,
'Parametertyp waehlen');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 331 and msg.s_id = 1;
insert into msg values (1, 331, 1, 1,
'Der aktuelle Aktion kann nicht geloescht werden, weil noch Aktionsgruppen');
insert into msg values (1, 331, 1, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst alle Aktionsgruppen-');
insert into msg values (1, 331, 1, 3,
'Eintragungen die diese Aktion definiert haben');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 332 and msg.s_id = 1;
insert into msg values (1, 332, 1, 1,
'Es liegt keine oder eine fehlerhafte Aktionsdefinition fuer die aktuelle');
insert into msg values (1, 332, 1, 2,
'Dienstleistung/Dienstleistungsangebot vor. Ueberpruefen Sie die');
insert into msg values (1, 332, 1, 3,
'Definitionen im Dienstleistungs-/Angebots-Menu oder die');
insert into msg values (1, 332, 1, 4,
'Definitionen im Aktions-/Aktionsgruppen Menu.');
