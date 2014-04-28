/***************************************************************/
/*                                                             */
/* yafra.org                                            */
/*                                                             */
/* error messages definition                                   */
/*                                                             */
/* DEF_D_msgerr                                                */
/*                                                             */
/***************************************************************/

delete from msg where msg.msg_typ = 1 and msg.s_id = 25;

insert into msg values (1, 0, 25, 1,
'kein Fehler - alles in Ordnung');

insert into msg values (1, 1, 25, 1,
'Es ist ein allgemeiner Fehler aufgetreten. Falls keine weiteren');
insert into msg values (1, 1, 25, 2,
'Fehlermeldungen vorhanden sind, bitte umgehend melden.');

insert into msg values (1, 10, 25, 1,
'Fehler beim reservieren von Speicher. Programm beenden und eventuell');
insert into msg values (1, 10, 25, 2,
'den Server neu starten oder gar Ihren Rechner neu booten');

insert into msg values (1, 11, 25, 1,
'Fehler im internen Protokoll zwischen grafischer Oberflaeche und der');
insert into msg values (1, 11, 25, 2,
'Datenbank. Bitte benachrichtigen Sie Ihre Supportstelle');

insert into msg values (1, 14, 25, 1,
'Sie haben keine eindeutige Bezeichnung eingegeben; vermutlich ist ein');
insert into msg values (1, 14, 25, 2,
'Eintrag unter dieser Bezeichnung schon vorhanden');

insert into msg values (1, 15, 25, 1,
'Das Programm kann den Menuinhalt nicht entschluesseln, es handelt sich hier');
insert into msg values (1, 15, 25, 2,
'um einen internen Fehler, den Sie Ihrer Supportstelle melden sollten');

insert into msg values (1, 16, 25, 1,
'Die eingegebene Bezeichnung konnte nicht abgespeichert werden.');

insert into msg values (1, 18, 25, 1,
'Es konnte kein Eintrag in der Datenbank gefunden werden. Entweder ist noch');
insert into msg values (1, 18, 25, 2,
'kein Datensatz in der Datenbank oder Ihre globalen Einschraenkungen');
insert into msg values (1, 18, 25, 3,
'ergeben einen Konflikt');

insert into msg values (1, 20, 25, 1,
'Informationen zum gewuenschten Objekt koennen nicht gelesen werden, da das');
insert into msg values (1, 20, 25, 2,
'Objekt nicht aktiviert ist. Wï¿½hlen Sie das gewuenschte Objekt zuerst aus');

insert into msg values (1, 21, 25, 1,
'Keine gueltige Sprache vorhanden oder erfasst');

insert into msg values (1, 24, 25, 1,
'Es konnte KEIN Datensatz eingefuegt/modifiziert/geloescht werden.');
insert into msg values (1, 24, 25, 2,
'Beachten Sie bitte die obige englische Datenbankmeldung.');

insert into msg values (1, 25, 25, 1,
'Sie haben KEINE BERECHTIGUNG fuer diese Operation. Fragen Sie Ihren');
insert into msg values (1, 25, 25, 2,
'MARCO POLO Administrator wegen Ihrer Berechtigungsstufe.');

insert into msg values (1, 26, 25, 1,
'Keine gueltige Bezeichnung vorhanden oder erfasst');

insert into msg values (1, 28, 25, 1,
'Fï¿½r dieses Objekt ist keine Aktion/Auswahl/Grafik vorgesehen - beachten');
insert into msg values (1, 28, 25, 2,
'Sie Ihre Unterlagen, dort ist vermerkt welches Objekt was kann');

insert into msg values (1, 29, 25, 1,
'Es kann keine neue interne Identifikationsnummer vergeben werden.');
insert into msg values (1, 29, 25, 2,
'Bitte kontaktieren Sie umgehend Ihre Supportstelle mit dieser Meldung.');

insert into msg values (1, 30, 25, 1,
'Es wurde versucht eine ungueltige oder geschuetzte Bezeichnung zu');
insert into msg values (1, 30, 25, 2,
'lï¿½schen. Vermutlich besteht ein Programmfehler.');

insert into msg values (1, 35, 25, 1,
'Keine gueltige Kategorie vorhanden oder erfasst');

insert into msg values (1, 36, 25, 1,
'Kein gueltiger Dienstleistungstraeger vorhanden oder erfasst');

insert into msg values (1, 37, 25, 1,
'Kein gueltiger Dienstleistungstraegertyp vorhanden oder erfasst');

insert into msg values (1, 46, 25, 1,
'Kein gueltiges Angebot vorhanden oder erfasst');

insert into msg values (1, 47, 25, 1,
'Kein gueltiger Angebotstyp vorhanden oder erfasst');

insert into msg values (1, 48, 25, 1,
'Zu diesem Objekt ist keine Information vorhanden - aktivieren Sie ein Objekt');

insert into msg values (1, 50, 25, 1,
'Die angegebene Dauer ist ungï¿½ltig');

insert into msg values (1, 52, 25, 1,
'Kein gueltiger Kundentyp vorhanden oder erfasst');

insert into msg values (1, 59, 25, 1,
'Kein gueltiger Reisender-/Dienstleistungsnehmer-Typ vorhanden oder erfasst');

insert into msg values (1, 60, 25, 1,
'Kein gueltiger Reisender/Dienstleistungsnehmer vorhanden oder erfasst');

insert into msg values (1, 63, 25, 1,
'Auf dem Angebot muss ein gï¿½ltiger Trï¿½ger vergeben werden.');

insert into msg values (1, 64, 25, 1,
'Keine gueltige Saison vorhanden oder erfasst');

insert into msg values (1, 66, 25, 1,
'Sie mï¿½ssen sowohl das von-Datum wie auch das bis-Datum eingeben. Beachten');
insert into msg values (1, 66, 25, 2,
'Sie, dass das bis-Datum spï¿½ter ist als das von-Datum');

insert into msg values (1, 67, 25, 1,
'Keine gueltige Waehrung vorhanden oder erfasst');

insert into msg values (1, 68, 25, 1,
'Kein gueltiges Land vorhanden oder erfasst');

insert into msg values (1, 72, 25, 1,
'Keine gueltige Ortschaft vorhanden oder erfasst');

insert into msg values (1, 74, 25, 1,
'Keine gueltige Waehrung vorhanden oder erfasst');

insert into msg values (1, 78, 25, 1,
'Kein gueltiges Programm vorhanden oder erfasst');

insert into msg values (1, 82, 25, 1,
'Kein gueltiges Arrangement vorhanden oder erfasst');

insert into msg values (1, 83, 25, 1,
'Keine gueltige Teil-Dienstleistung vorhanden oder erfasst');

insert into msg values (1, 84, 25, 1,
'Keine gueltige Dienstleistung vorhanden oder erfasst');

insert into msg values (1, 85, 25, 1,
'Keine gueltige Teildienstleistung fuer die Verknuepfung zur Dienstleistung');
insert into msg values (1, 85, 25, 2,
'ausgewaehlt. Bitte selektieren Sie die gewuenschten Teildienstleistungen !');

insert into msg values (1, 87, 25, 1,
'Kein gueltiger Aktionstyp vorhanden oder erfasst');

insert into msg values (1, 88, 25, 1,
'Keine gueltige Aktion vorhanden oder erfasst');

insert into msg values (1, 90, 25, 1,
'Kein gueltiges Kontingent vorhanden oder erfasst');

insert into msg values (1, 91, 25, 1,
'Kein gueltiger Verwalter (als Kunde) vorhanden oder erfasst');

insert into msg values (1, 106, 25, 1,
'Keine gueltige Buchung vorhanden oder erfasst');

insert into msg values (1, 112, 25, 1,
'Es konnte kein Eintrag in der Datenbank gefunden werden');
insert into msg values (1, 112, 25, 2,
'Ueberpruefen Sie Ihre Eingaben und wiederholen Sie diese Aktion');

insert into msg values (1, 117, 25, 1,
'Keine Ortschaft (fuer Personen) vorhanden oder erfasst');

insert into msg values (1, 118, 25, 1,
'Kein Name vorhanden oder erfasst');

insert into msg values (1, 119, 25, 1,
'Kein Vorname vorhanden oder erfasst');

insert into msg values (1, 120, 25, 1,
'Kein gueltiger Statuswert vorhanden oder erfasst');

insert into msg values (1, 123, 25, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 123, 25, 2,
'noch Angebote darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 123, 25, 3,
'Angebote mit diesem Dienstleistungstraeger');

insert into msg values (1, 125, 25, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 125, 25, 2,
'noch Buchungen darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 125, 25, 3,
'Buchungen mit diesem Dienstleistungstraeger');

insert into msg values (1, 126, 25, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 126, 25, 2,
'noch Grafiken darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 126, 25, 3,
'Grafiken zu diesem Dienstleistungstraeger');

insert into msg values (1, 127, 25, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 127, 25, 2,
'noch Pixelbilder darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 127, 25, 3,
'Pixelbilder zu diesem Dienstleistungstraeger');

insert into msg values (1, 128, 25, 1,
'Das gewuenschte Objekt konnte nicht aus der Datenbank geloescht werden');
insert into msg values (1, 128, 25, 2,
'Ueberpruefen Sie Ihre Eingaben und wiederholen Sie diese Aktion');

insert into msg values (1, 129, 25, 1,
'Die Beschreibung des aktiven Objektes konnte nicht geloescht werden');

insert into msg values (1, 130, 25, 1,
'Die Bezeichnung des aktiven Objektes konnte nicht geloescht werden');
insert into msg values (1, 130, 25, 2,
'Die Bezeichnung wird vermutlich in einem anderen Objekt noch benoetigt');

insert into msg values (1, 141, 25, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 141, 25, 2,
'Teildienstleistung darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 141, 25, 3,
'alle Teildienstleistungen mit diesem Angebot');

insert into msg values (1, 158, 25, 1,
'Der aktuelle Aktionstyp kann nicht geloescht werden, weil noch Aktionen');
insert into msg values (1, 158, 25, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst alle Aktionen die diesen');
insert into msg values (1, 158, 25, 3,
'Aktionstyp definiert haben');

insert into msg values (1, 170, 25, 1,
'Das aktuelle Kollektiv/Gruppe kann nicht geloescht werden, weil noch');
insert into msg values (1, 170, 25, 2,
'Buchungen/Dossiers darauf definiert sind. Loeschen Sie zuerst diese.');

insert into msg values (1, 172, 25, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch');
insert into msg values (1, 172, 25, 2,
'ein Preis darauf definiert ist. Bitte loeschen Sie zuerst alle auf');
insert into msg values (1, 172, 25, 3,
'diese Dienstleistung definierten Preise');

insert into msg values (1, 173, 25, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch ein');
insert into msg values (1, 173, 25, 2,
'Kontingent darauf definiert ist. Bitte loeschen Sie zuerst alle auf');
insert into msg values (1, 173, 25, 3,
'diese Dienstleistung definierten Kontingente');

insert into msg values (1, 184, 25, 1,
'Die gewaehlte Kategorie oder die Menge der Kategorie deckt sich nicht');
insert into msg values (1, 184, 25, 2,
'mit der Definition auf dem Hauptkontingent. Pruefen Sie die');
insert into msg values (1, 184, 25, 3,
'Definition auf dem Hauptkontingent.');

insert into msg values (1, 185, 25, 1,
'Der gewaehlte Dienstleistungstraeger ist im Hauptkontingent nicht');
insert into msg values (1, 185, 25, 2,
'definiiert. Pruefen Sie die Definition auf dem Hauptkontingent.');

insert into msg values (1, 186, 25, 1,
'Sie muessen entweder eine Kategorie und deren Menge oder ein');
insert into msg values (1, 186, 25, 2,
'Dienstleistungstraeger fuer das Kontingentdetail definieren.');

insert into msg values (1, 187, 25, 1,
'Der gewaehlte Dienstleistungstraeger ist schon vergeben.');
insert into msg values (1, 187, 25, 2,
'Pruefen Sie die Definition aller Details zu diesen Kontingenten.');

insert into msg values (1, 188, 25, 1,
'Die Summe der Mengen der einzelnen Kontingentdetails ist zu gross.');
insert into msg values (1, 188, 25, 2,
'Pruefen Sie die Definition aller Details zu diesem Hauptkontingent.');

insert into msg values (1, 189, 25, 1,
'Das Kontingent ist bereits ausgebucht. Soll trotzdem gebucht werden ?');

insert into msg values (1, 192, 25, 1,
'Sie kï¿½nnen eine Preis nur auf ein Dienstleistung oder ein Dienstleistungs-');
insert into msg values (1, 192, 25, 2,
'angebot definieren, aber nicht auf beide zur gleichen Zeit');

insert into msg values (1, 194, 25, 1,
'Es ist im Moment keine gueltige Buchung aktiv. Aktivieren Sie eine');

insert into msg values (1, 195, 25, 1,
'Es wurde kein gueltiges Buchungsobjekt gewaehlt. Ein Buchungsobjekt');
insert into msg values (1, 195, 25, 2,
'ist entweder eine Dienstleistung oder ein Arrangement');

insert into msg values (1, 197, 25, 1,
'Es wurde keine gueltige Buchungsstelle und Rechnungsstelle gewaehlt');

insert into msg values (1, 200, 25, 1,
'Kein gueltiges Geschlecht vorhanden oder erfasst');

insert into msg values (1, 203, 25, 1,
'Sie haben einen falschen Buchungsstatus gewaehlt. Dieser Buchungsstatus');
insert into msg values (1, 203, 25, 2,
'ist im jetzigen Zustand nicht moeglich.');

insert into msg values (1, 204, 25, 1,
'Es sind noch Dienstleistungen zu diesem Arrangement definiert; loeschen');
insert into msg values (1, 204, 25, 2,
'Sie diese zuerst');

insert into msg values (1, 205, 25, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch ein');
insert into msg values (1, 205, 25, 2,
'Arrangement darauf definiert ist. Bitte loeschen Sie zuerst alle auf');
insert into msg values (1, 205, 25, 3,
'diese Dienstleistung definierten Arrangements');

insert into msg values (1, 206, 25, 1,
'Zu diesem Objekt ist weder eine Grafik noch eine Information vorhanden');

insert into msg values (1, 208, 25, 1,
'In dieser Reservation ist ein Konflikt entstanden und konnte demzufolge');
insert into msg values (1, 208, 25, 2,
'nicht abgespeichert werden. Prï¿½fen Sie Ihre bisherigen Eingaben anhand des');
insert into msg values (1, 208, 25, 3,
'Info-Fensters.');

insert into msg values (1, 232, 25, 1,
'Sie haben vergessen einen Mussparameter zu fï¿½llen');

insert into msg values (1, 244, 25, 1,
'Der aktuelle Aktionstyp kann nicht geloescht werden, weil noch Buchungen');
insert into msg values (1, 244, 25, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst alle Buchungen die diesen');
insert into msg values (1, 244, 25, 3,
'Aktionstyp ueber eine Aktion benoetigen. (AKTIONSDETAIL)');

insert into msg values (1, 247, 25, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch unter-');
insert into msg values (1, 247, 25, 2,
'geordnete Angebote existieren. Ueber den Infromationsknopf erhalten');
insert into msg values (1, 247, 25, 3,
'Sie die detailierten Angaben');

insert into msg values (1, 248, 25, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch Preise');
insert into msg values (1, 248, 25, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst');
insert into msg values (1, 248, 25, 3,
'alle Preise mit diesem Angebot');

insert into msg values (1, 249, 25, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch Kontingente');
insert into msg values (1, 249, 25, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst');
insert into msg values (1, 249, 25, 3,
'alle Kontingente mit diesem Angebot');

insert into msg values (1, 250, 25, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch Kommissionen');
insert into msg values (1, 250, 25, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst');
insert into msg values (1, 250, 25, 3,
'alle Kommissionen mit diesem Angebot');

insert into msg values (1, 251, 25, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch');
insert into msg values (1, 251, 25, 2,
'untergeordnete Teildienstleistung existieren. Ueber den Infromationsknopf');
insert into msg values (1, 251, 25, 3,
'erhalten Sie die detailierten Angaben');

insert into msg values (1, 252, 25, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 252, 25, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 252, 25, 3,
'alle Buchungen/Reservationen fuer diese Teildienstleistung (RESERVATION)');

insert into msg values (1, 253, 25, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 253, 25, 2,
'Dienstleistung darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 253, 25, 3,
'alle Dienstleistungen mit dieser Teildienstleistung');

insert into msg values (1, 254, 25, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 254, 25, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 254, 25, 3,
'alle Buchungen/Reservationen fuer diese Teildienstleistung (AKTIONSDETAIL)');

insert into msg values (1, 256, 25, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 256, 25, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 256, 25, 3,
'alle Buchungen/Reservationen fuer diese Dienstleistung (RESERVATION)');

insert into msg values (1, 257, 25, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 257, 25, 2,
'Kommission/Reduktion darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 257, 25, 3,
'alle Kommissionen/Reduktionen fuer diese Dienstleistung');

insert into msg values (1, 258, 25, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 258, 25, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 258, 25, 3,
'alle Buchungen/Reservationen fuer diese Dienstleistung (AKTIONSDETAIL)');

insert into msg values (1, 259, 25, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 259, 25, 2,
'Teildienstleistung darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 259, 25, 3,
'alle Teildienstleistungen fuer diese Dienstleistung');

insert into msg values (1, 278, 25, 1,
'Das aktuelle Kollektiv/Gruppe kann nicht geloescht werden, weil beim');
insert into msg values (1, 278, 25, 2,
'Loeschen der Kollektiv/Gruppen Kommissionen ein Fehler aufgetreten ist.');

insert into msg values (1, 282, 25, 1,
'Keine gueltige Grafik vorhanden oder erfasst');

insert into msg values (1, 286, 25, 1,
'Dieser Dienstleistungstraeger ist nicht im ausgewaehlten Kontingent');
insert into msg values (1, 286, 25, 2,
'beinhaltet. Wollen Sie diese Angaben trotzdem speichern ?');

insert into msg values (1, 287, 25, 1,
'Dieser Dienstleistungstraeger befindet sich im Kontingent');
insert into msg values (1, 287, 25, 2, '%s');
insert into msg values (1, 287, 25, 3,
'Buchen Sie in dieses Kontingent, waehlen Sie einen anderen Traeger,');
insert into msg values (1, 287, 25, 4,
'oder wollen Sie trotzdem mit diesen Angaben die Buchung speichern ?');

insert into msg values (1, 289, 25, 1,
'Fehler beim schreiben des Buchungsdetails fuer den aktiven Reisenden');
insert into msg values (1, 289, 25, 2,
'Brechen Sie den Buchungsvorgang ab und beginnen Sie von neuem');

insert into msg values (1, 292, 25, 1,
'Es konnte keine Kategorie fï¿½r diese Reservation gefunden werden');

insert into msg values (1, 293, 25, 1,
'Fehler beim kopieren des Arrangenments');

insert into msg values (1, 294, 25, 1,
'Fehler beim kopieren der Dienstleistung');

insert into msg values (1, 297, 25, 1,
'Es kann keine Grafik im Loeschmodus angezeigt werden, Sie koennen nur');
insert into msg values (1, 297, 25, 2,
'eine Grafik und alle Verknuepfungen loeschen');

insert into msg values (1, 303, 25, 1,
'Es kann fuer dieses Objekt keine maximum Identifikation zugeteilt werden');

insert into msg values (1, 304, 25, 1,
'Es kann fuer dieses Objekt keine minimum Identifikation zugeteilt werden');

insert into msg values (1, 313, 25, 1,
'Sie muessen zwingend eine Bezeichnung, Dateiname und Typ resp. Typcode');
insert into msg values (1, 313, 25, 2,
'eingeben resp. auswaehlen.');

insert into msg values (1, 314, 25, 1,
'Es konnte keine Identifikation zugeteilt werden. Versuchen Sie es noch');
insert into msg values (1, 314, 25, 2,
'einmal');

insert into msg values (1, 315, 25, 1,
'Es konnten keine Bezeichnungen zur neuen Sprache kopiert werden');

insert into msg values (1, 316, 25, 1,
'Es konnten keine Beschreibungen/Texte zur neuen Sprache kopiert werden');

insert into msg values (1, 317, 25, 1,
'Sie koennen diese Sprache nicht loeschen, weil Sie die Systemsprache ist');

insert into msg values (1, 318, 25, 1,
'Die Grafikdaten sind zu gross. Bitte einen Export durchfï¿½hren.');

insert into msg values (1, 319, 25, 1,
'Es ist kein Verantwortilcher zum aktuellen Kollektiv/Gruppe definiert.');

insert into msg values (1, 320, 25, 1,
'Aktion(en) konnte(n) nicht ausgefï¿½hrt werden. Prï¿½fen Sie Ihre Eingaben.');

insert into msg values (1, 321, 25, 1,
'Angebotstyp kann nicht gelï¿½scht werden, da er in der Angebotstabelle');
insert into msg values (1, 321, 25, 2,
'noch benï¿½tigt wird. Lï¿½schen Sie den entsprechenden Eintrag zuerst.');

insert into msg values (1, 322, 25, 1,
'Es sind keine Reservationsdaten zu der aktuellen Buchung vorhanden.');
insert into msg values (1, 322, 25, 2,
'Prï¿½fen Sie die Buchung ï¿½ber die Informationsfunktion.');

insert into msg values (1, 323, 25, 1,
'Auf diese Dienstleistung kann nicht gebucht werden. Die Reservationsart');
insert into msg values (1, 323, 25, 2,
'dieser Dienstleistung lï¿½sst dies nicht zu.');

insert into msg values (1, 324, 25, 1,
'Zu dieser Dienstleistung mï¿½ssen Sie das von- und bis-Datum eingeben.');

insert into msg values (1, 325, 25, 1,
'Es ist kein Dienstleistungstrï¿½ger mehr frei ! Wï¿½hlen Sie eine andere');
insert into msg values (1, 325, 25, 2,
'Dienstleistung oder ein anderes Datum !');

insert into msg values (1, 326, 25, 1,
'Der ausgewï¿½hlte Dienstleistungstrï¿½ger hat nur Raum fï¿½r %d Person(en).');
insert into msg values (1, 326, 25, 2,
'Es wurde aber versucht %d Person(en) auf diesen Trï¿½ger zu buchen.');
insert into msg values (1, 326, 25, 3,
'Buchen Sie einen anderen Trï¿½ger oder in eine andere Kategorie.');

insert into msg values (1, 327, 25, 1,
'Der ausgewï¿½hlte Dienstleistungstrï¿½ger ist besetzt durch die Buchung %d.');
insert into msg values (1, 327, 25, 2,
'In dieser Buchung wurden %d Person(en) darauf gebucht.');
insert into msg values (1, 327, 25, 3,
'Soll troztdem gebucht werden ?');

insert into msg values (1, 328, 25, 1,
'Der aktuelle Aktionstyp kann nicht geloescht werden, weil noch Aktions-');
insert into msg values (1, 328, 25, 2,
'parameter darauf definiert sind. Bitte loeschen Sie zuerst alle Parameter');
insert into msg values (1, 328, 25, 3,
'dieses Aktionstyps');

insert into msg values (1, 329, 25, 1,
'Sie muessen eine Parameterbezeichnung im Feld Parameter eingeben');

insert into msg values (1, 330, 25, 1,
'Sie koennen den Parameter nur als Flag definieren, wenn Sie keinen');
insert into msg values (1, 330, 25, 2,
'Parametertyp waehlen');

insert into msg values (1, 331, 25, 1,
'Der aktuelle Aktion kann nicht geloescht werden, weil noch Aktionsgruppen');
insert into msg values (1, 331, 25, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst alle Aktionsgruppen-');
insert into msg values (1, 331, 25, 3,
'Eintragungen die diese Aktion definiert haben');

insert into msg values (1, 332, 25, 1,
'Es liegt keine oder eine fehlerhafte Aktionsdefinition fuer die aktuelle');
insert into msg values (1, 332, 25, 2,
'Dienstleistung/Dienstleistungsangebot vor. Ueberpruefen Sie die');
insert into msg values (1, 332, 25, 3,
'Definitionen im Dienstleistungs-/Angebots-Menu oder die');
insert into msg values (1, 332, 25, 4,
'Definitionen im Aktions-/Aktionsgruppen Menu.');
