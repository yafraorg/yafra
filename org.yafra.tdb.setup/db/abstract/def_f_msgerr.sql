/**************************************************************
 *
 * yafra.org
 *
 * error messages definition
 *
 * DEF_F_msgerr
 *
 **************************************************************/

/* delete from msg where msg.msg_typ = 1 */

delete from msg where msg.msg_typ = 1 and msg.msg_id = 0 and msg.s_id = 2;
insert into msg values (1, 0, 2, 1,
'Pas d''erreur - tout est en ordre');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 1 and msg.s_id = 2;
insert into msg values (1, 1, 2, 1,
'Erreur generale !');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 10 and msg.s_id = 2;
insert into msg values (1, 10, 2, 1,
'Erreur generale de reservation memoire. Stopper l''application,');
insert into msg values (1, 10, 2, 2,
'reinitialiser le serveur ou rebooter la station');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 11 and msg.s_id = 2;
insert into msg values (1, 11, 2, 1,
'Erreur de protocole entre l''interface graphique et la base de donnees');
insert into msg values (1, 11, 2, 2,
'Prevenir le service technique');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 14 and msg.s_id = 2;
insert into msg values (1, 14, 2, 1,
'Designation non claire; il existe peut-etre deja une');
insert into msg values (1, 14, 2, 2,
'entree sous cette designation');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 15 and msg.s_id = 2;
insert into msg values (1, 15, 2, 1,
'Impossibilite de dechiffrer le contenu du menu. Erreur interne');
insert into msg values (1, 15, 2, 2,
'Prevenir le service technique');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 16 and msg.s_id = 2;
insert into msg values (1, 16, 2, 1,
'La Designation entree ne peut ete memorisee');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 18 and msg.s_id = 2;
insert into msg values (1, 18, 2, 1,
'Aucune entree n''a ete trouvee dans la base de donnees');
insert into msg values (1, 18, 2, 2,
'Soit l''entree n''existe pas  ou alors les contraintes globales sont');
insert into msg values (1, 18, 2, 3,
'conflictuelles');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 20 and msg.s_id = 2;
insert into msg values (1, 20, 2, 1,
'Les informations de l''objet desire ne peuvent etre lues car l''objet');
insert into msg values (1, 20, 2, 2,
'n''est pas actif. Selectionner d''abord l''object');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 21 and msg.s_id = 2;
insert into msg values (1, 21, 2, 1,
'Pas de Langue correcte disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 24 and msg.s_id = 2;
insert into msg values (1, 24, 2, 1,
'Es konnte KEIN Datensatz eingefuegt/modifiziert/geloescht werden.');
insert into msg values (1, 24, 2, 2,
'Beachten Sie bitte die obige englische Datenbankmeldung.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 25 and msg.s_id = 2;
insert into msg values (1, 25, 2, 1,
'Sie haben KEINE BERECHTIGUNG fuer diese Operation. Fragen Sie Ihren');
insert into msg values (1, 25, 2, 2,
'MARCO POLO Administrator wegen Ihrer Berechtigungsstufe.');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 26 and msg.s_id = 2;
insert into msg values (1, 26, 2, 1,
'Pas de Designation correcte disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 28 and msg.s_id = 2;
insert into msg values (1, 28, 2, 1,
'Il n''est pas prevu d''action/selection/graphique pour cet objet');
insert into msg values (1, 28, 2, 2,
'Verifier la documentation a ce sujet');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 29 and msg.s_id = 2;
insert into msg values (1, 29, 2, 1,
'Le nouveau numero d''identification ne peut etre attribue');
insert into msg values (1, 29, 2, 2,
'Contacter le service technique');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 30 and msg.s_id = 2;
insert into msg values (1, 30, 2, 1,
'Fehler beim loeschen einer Bezeichung');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 35 and msg.s_id = 2;
insert into msg values (1, 35, 2, 1,
'Pas de Categorie correcte disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 36 and msg.s_id = 2;
insert into msg values (1, 36, 2, 1,
'Pas de Support correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 37 and msg.s_id = 2;
insert into msg values (1, 37, 2, 1,
'Pas de Type-Support correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 46 and msg.s_id = 2;
insert into msg values (1, 46, 2, 1,
'Pas d''Offre correcte disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 47 and msg.s_id = 2;
insert into msg values (1, 47, 2, 1,
'Pas de Type-Offre correcte disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 48 and msg.s_id = 2;
insert into msg values (1, 48, 2, 1,
'Il n''existe pas d''information pour cet objet. Activer un objet');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 50 and msg.s_id = 2;
insert into msg values (1, 50, 2, 1,
'La duree entree est invalide');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 52 and msg.s_id = 2;
insert into msg values (1, 52, 2, 1,
'Kein gueltiger Kundentyp vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 59 and msg.s_id = 2;
insert into msg values (1, 59, 2, 1,
'Pas de Type-Voyageur/Interesse correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 60 and msg.s_id = 2;
insert into msg values (1, 60, 2, 1,
'Pas de Voyageur/Interesse correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 63 and msg.s_id = 2;
insert into msg values (1, 63, 2, 1,
'Un Support valable doit ete attribue a cette Offre');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 64 and msg.s_id = 2;
insert into msg values (1, 64, 2, 1,
'Pas de Saison correcte disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 66 and msg.s_id = 2;
insert into msg values (1, 66, 2, 1,
'Les dates de depart et de fin sont necessaires. La date de fin');
insert into msg values (1, 66, 2, 2,
'doit etre plus tardive');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 67 and msg.s_id = 2;
insert into msg values (1, 67, 2, 1,
'Pas de Devise correcte disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 68 and msg.s_id = 2;
insert into msg values (1, 68, 2, 1,
'Kein gueltiges Land vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 72 and msg.s_id = 2;
insert into msg values (1, 72, 2, 1,
'Keine gueltige Ortschaft vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 74 and msg.s_id = 2;
insert into msg values (1, 74, 2, 1,
'Pas de Devise correcte disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 78 and msg.s_id = 2;
insert into msg values (1, 78, 2, 1,
'Pas de Programme correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 82 and msg.s_id = 2;
insert into msg values (1, 82, 2, 1,
'Pas d''Arrangement correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 83 and msg.s_id = 2;
insert into msg values (1, 83, 2, 1,
'Pas de Service-Partiel correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 84 and msg.s_id = 2;
insert into msg values (1, 84, 2, 1,
'Pas de Service correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 85 and msg.s_id = 2;
insert into msg values (1, 85, 2, 1,
'Keine gueltige Teildienstleistung fuer die Verknuepfung zur Dienstleistung');
insert into msg values (1, 85, 2, 2,
'ausgewaehlt. Bitte selektieren Sie die gewuenschten Teildienstleistungen !');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 87 and msg.s_id = 2;
insert into msg values (1, 87, 2, 1,
'Pas de Type-Action correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 88 and msg.s_id = 2;
insert into msg values (1, 88, 2, 1,
'Pas d''Action correcte disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 90 and msg.s_id = 2;
insert into msg values (1, 90, 2, 1,
'Pas de Contingent correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 91 and msg.s_id = 2;
insert into msg values (1, 91, 2, 1,
'Pas de Responsable client correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 106 and msg.s_id = 2;
insert into msg values (1, 106, 2, 1,
'Pas de Reservation correcte disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 112 and msg.s_id = 2;
insert into msg values (1, 112, 2, 1,
'Aucune entree n''a ete trouvee');
insert into msg values (1, 112, 2, 2,
'Verifiez vos donnees et relancez l''action');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 117 and msg.s_id = 2;
insert into msg values (1, 117, 2, 1,
'Keine Ortschaft (fuer Personen) vorhanden oder erfasst');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 118 and msg.s_id = 2;
insert into msg values (1, 118, 2, 1,
'Pas de nom de famille correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 119 and msg.s_id = 2;
insert into msg values (1, 119, 2, 1,
'Pas de prenom correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 120 and msg.s_id = 2;
insert into msg values (1, 120, 2, 1,
'Pas de Status correct disponible');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 123 and msg.s_id = 2;
insert into msg values (1, 123, 2, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 123, 2, 2,
'noch Angebote darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 123, 2, 3,
'Angebote mit diesem Dienstleistungstraeger');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 125 and msg.s_id = 2;
insert into msg values (1, 125, 2, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 125, 2, 2,
'noch Buchungen darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 125, 2, 3,
'Buchungen mit diesem Dienstleistungstraeger');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 126 and msg.s_id = 2;
insert into msg values (1, 126, 2, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 126, 2, 2,
'noch Grafiken darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 126, 2, 3,
'Grafiken zu diesem Dienstleistungstraeger');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 127 and msg.s_id = 2;
insert into msg values (1, 127, 2, 1,
'Der aktuelle Dienstleistungstraeger kann nicht geloescht werden, weil');
insert into msg values (1, 127, 2, 2,
'noch Pixelbilder darauf definiert sind. Bitte loeschen Sie zuerst alle');
insert into msg values (1, 127, 2, 3,
'Pixelbilder zu diesem Dienstleistungstraeger');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 128 and msg.s_id = 2;
insert into msg values (1, 128, 2, 1,
'L''object actif ne peut etre efface');
insert into msg values (1, 128, 2, 2,
'Verifiez vos donnees et relancez l''action');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 129 and msg.s_id = 2;
insert into msg values (1, 129, 2, 1,
'La description de l''object actif ne peut etre effacee');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 130 and msg.s_id = 2;
insert into msg values (1, 130, 2, 1,
'La designation de l''object actif ne peut etre effacee');
insert into msg values (1, 130, 2, 2,
'Cette designation est surement necessaire pour un autre objet');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 141 and msg.s_id = 2;
insert into msg values (1, 141, 2, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 141, 2, 2,
'Teildienstleistung darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 141, 2, 3,
'alle Teildienstleistungen mit diesem Angebot');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 158 and msg.s_id = 2;
insert into msg values (1, 158, 2, 1,
'Der aktuelle Aktionstyp kann nicht geloescht werden, weil noch Aktionen');
insert into msg values (1, 158, 2, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst alle Aktionen die diesen');
insert into msg values (1, 158, 2, 3,
'Aktionstyp definiert haben');

delete from msg where msg.msg_typ = 1 and msg.msg_id = 170 and msg.s_id = 2;
insert into msg values (1, 170, 2, 1,
'Das aktuelle Kollektiv/Gruppe kann nicht geloescht werden, weil noch');
insert into msg values (1, 170, 2, 2,
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

delete from msg where msg.msg_typ = 1 and msg.msg_id = 184 and msg.s_id = 2;
insert into msg values (1, 184, 2, 1,
'Die gewaehlte Kategorie oder die Menge der Kategorie deckt sich nicht');
insert into msg values (1, 184, 2, 2,
'mit der Definition auf dem Hauptkontingent. Pruefen Sie die');
insert into msg values (1, 184, 2, 3,
'Definition auf dem Hauptkontingent.');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 185 and msg.s_id = 2;
insert into msg values (1, 185, 2, 1,
'Der gewaehlte Dienstleistungstraeger ist im Hauptkontingent nicht');
insert into msg values (1, 185, 2, 2,
'definiiert. Pruefen Sie die Definition auf dem Hauptkontingent.');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 186 and msg.s_id = 2;
insert into msg values (1, 186, 2, 1,
'Sie muessen entweder eine Kategorie und deren Menge oder ein');
insert into msg values (1, 186, 2, 2,
'Dienstleistungstraeger fuer das Kontingentdetail definieren.');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 187 and msg.s_id = 2;
insert into msg values (1, 187, 2, 1,
'Der gewaehlte Dienstleistungstraeger ist schon vergeben.');
insert into msg values (1, 187, 2, 2,
'Pruefen Sie die Definition aller Details zu diesen Kontingenten.');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 188 and msg.s_id = 2;
insert into msg values (1, 188, 2, 1,
'Die Summe der Mengen der einzelnen Kontingentdetails ist zu gross.');
insert into msg values (1, 188, 2, 2,
'Pruefen Sie die Definition aller Details zu diesem Hauptkontingent.');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 192 and msg.s_id = 2;
insert into msg values (1, 192, 2, 1,
'Vous pouvez definir un prix  pour un Service ou une Offre');
insert into msg values (1, 192, 2, 2,
'mais pas pour les deux en meme temps');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 194 and msg.s_id = 2;
insert into msg values (1, 194, 2, 1,
'Il n''y a pas de Reservation active en ce moment, activez-en une');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 195 and msg.s_id = 2;
insert into msg values (1, 195, 2, 1,
'Il faut selectionner l''object de la Reservation');
insert into msg values (1, 195, 2, 2,
'C''est un Service ou un Arrangement');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 197 and msg.s_id = 2;
insert into msg values (1, 197, 2, 1,
'Il faut selectionner un lieu de reservation et de facturation');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 200 and msg.s_id = 2;
insert into msg values (1, 200, 2, 1,
'Pas de sexe correct disponible');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 203 and msg.s_id = 2;
insert into msg values (1, 203, 2, 1,
'Le status de Reservation est errone. Ce status n''est pas autorise');
insert into msg values (1, 203, 2, 2,
'dans le stade actuel');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 204 and msg.s_id = 2;
insert into msg values (1, 204, 2, 1,
'Des services sont encore definis pour cet Arrangement');
insert into msg values (1, 204, 2, 2,
'Effacer les Services en premier');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 205 and msg.s_id = 2;
insert into msg values (1, 205, 2, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch ein');
insert into msg values (1, 205, 2, 2,
'Arrangement darauf definiert ist. Bitte loeschen Sie zuerst alle auf');
insert into msg values (1, 205, 2, 3,
'diese Dienstleistung definierten Arrangements');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 206 and msg.s_id = 2;
insert into msg values (1, 206, 2, 1,
'Il n''y a ni Graphique ni information disponible pour cet objet');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 208 and msg.s_id = 2;
insert into msg values (1, 208, 2, 1,
'La reservation ne peut etre enregistree a cause d''une situation de conflit');
insert into msg values (1, 208, 2, 2,
'Verifier les valeurs entrees jusqu''a present a l''aide de la fenetre');
insert into msg values (1, 208, 2, 3,
'Info');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 232 and msg.s_id = 2;
insert into msg values (1, 232, 2, 1,
'Un parametre obligatoire a ete oublie');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 244 and msg.s_id = 2;
insert into msg values (1, 244, 2, 1,
'Der aktuelle Aktionstyp kann nicht geloescht werden, weil noch Buchungen');
insert into msg values (1, 244, 2, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst alle Buchungen die diesen');
insert into msg values (1, 244, 2, 3,
'Aktionstyp ueber eine Aktion benoetigen. (AKTIONSDETAIL)');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 247 and msg.s_id = 2;
insert into msg values (1, 247, 2, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch unter-');
insert into msg values (1, 247, 2, 2,
'geordnete Angebote existieren. Ueber den Infromationsknopf erhalten');
insert into msg values (1, 247, 2, 3,
'Sie die detailierten Angaben');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 248 and msg.s_id = 2;
insert into msg values (1, 248, 2, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch Preise');
insert into msg values (1, 248, 2, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst');
insert into msg values (1, 248, 2, 3,
'alle Preise mit diesem Angebot');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 249 and msg.s_id = 2;
insert into msg values (1, 249, 2, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch Kontingente');
insert into msg values (1, 249, 2, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst');
insert into msg values (1, 249, 2, 3,
'alle Kontingente mit diesem Angebot');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 250 and msg.s_id = 2;
insert into msg values (1, 250, 2, 1,
'Das aktuelle Angebot kann nicht geloescht werden, weil noch Kommissionen');
insert into msg values (1, 250, 2, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst');
insert into msg values (1, 250, 2, 3,
'alle Kommissionen mit diesem Angebot');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 251 and msg.s_id = 2;
insert into msg values (1, 251, 2, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch');
insert into msg values (1, 251, 2, 2,
'untergeordnete Teildienstleistung existieren. Ueber den Infromationsknopf');
insert into msg values (1, 251, 2, 3,
'erhalten Sie die detailierten Angaben');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 252 and msg.s_id = 2;
insert into msg values (1, 252, 2, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 252, 2, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 252, 2, 3,
'alle Buchungen/Reservationen fuer diese Teildienstleistung (RESERVATION)');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 253 and msg.s_id = 2;
insert into msg values (1, 253, 2, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 253, 2, 2,
'Dienstleistung darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 253, 2, 3,
'alle Dienstleistungen mit dieser Teildienstleistung');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 254 and msg.s_id = 2;
insert into msg values (1, 254, 2, 1,
'Die aktuelle Teildienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 254, 2, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 254, 2, 3,
'alle Buchungen/Reservationen fuer diese Teildienstleistung (AKTIONSDETAIL)');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 256 and msg.s_id = 2;
insert into msg values (1, 256, 2, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 256, 2, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 256, 2, 3,
'alle Buchungen/Reservationen fuer diese Dienstleistung (RESERVATION)');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 257 and msg.s_id = 2;
insert into msg values (1, 257, 2, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 257, 2, 2,
'Kommission/Reduktion darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 257, 2, 3,
'alle Kommissionen/Reduktionen fuer diese Dienstleistung');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 258 and msg.s_id = 2;
insert into msg values (1, 258, 2, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 258, 2, 2,
'Buchung/Reservation darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 258, 2, 3,
'alle Buchungen/Reservationen fuer diese Dienstleistung (AKTIONSDETAIL)');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 259 and msg.s_id = 2;
insert into msg values (1, 259, 2, 1,
'Die aktuelle Dienstleistung kann nicht geloescht werden, weil noch eine');
insert into msg values (1, 259, 2, 2,
'Teildienstleistung darauf definiert ist. Bitte loeschen Sie zuerst');
insert into msg values (1, 259, 2, 3,
'alle Teildienstleistungen fuer diese Dienstleistung');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 278 and msg.s_id = 2;
insert into msg values (1, 278, 2, 1,
'Das aktuelle Kollektiv/Gruppe kann nicht geloescht werden, weil beim');
insert into msg values (1, 278, 2, 2,
'Loeschen der Kollektiv/Gruppen Kommissionen ein Fehler aufgetreten ist.');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 282 and msg.s_id = 2;
insert into msg values (1, 282, 2, 1,
'Pas de Graphique valide disponible');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 286 and msg.s_id = 2;
insert into msg values (1, 286, 2, 1,
'Dieser Dienstleistungstraeger ist nicht im ausgewaehlten Kontingent');
insert into msg values (1, 286, 2, 2,
'beinhaltet. Pruefen Sie Ihre Kontingentdefinitionen !');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 287 and msg.s_id = 2;
insert into msg values (1, 287, 2, 1,
'Dieser Dienstleistungstraeger befindet sich im Kontingent');
insert into msg values (1, 287, 2, 2, '%s');
insert into msg values (1, 287, 2, 3,
'Buchen Sie in dieses Kontingent oder waehlen Sie einen anderen Traeger !');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 289 and msg.s_id = 2;
insert into msg values (1, 289, 2, 1,
'Erreur d''ecriture des Details de Reservation pour la personne en cours');
insert into msg values (1, 289, 2, 2,
'Interrompre la reservation et en ouvrir une nouvelle');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 292 and msg.s_id = 2;
insert into msg values (1, 292, 2, 1,
'Pas de categorie disponible pour cette Reservation');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 293 and msg.s_id = 2;
insert into msg values (1, 293, 2, 1,
'Erreur pendant la copie des Arrangements');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 294 and msg.s_id = 2;
insert into msg values (1, 294, 2, 1,
'Erreur pendant la copie des Services');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 297 and msg.s_id = 2;
insert into msg values (1, 297, 2, 1,
'Le Graphique n''est pas visible en mode suppression; mais il est possible');
insert into msg values (1, 297, 2, 2,
'd''effacer un Graphique avec toutes les dependances');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 303 and msg.s_id = 2;
insert into msg values (1, 303, 2, 1,
'Aucune identification maximale ne peut etre attribuee a cet objet');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 304 and msg.s_id = 2;
insert into msg values (1, 304, 2, 1,
'Aucune identification minimale ne peut etre attribuee a cet objet');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 313 and msg.s_id = 2;
insert into msg values (1, 313, 2, 1,
'Une designation, un Nom de fichier et un Type respectivement un Typecode');
insert into msg values (1, 313, 2, 2,
'doivent obligatoirement etre entres ou selectionnes');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 314 and msg.s_id = 2;
insert into msg values (1, 314, 2, 1,
'Aucune Identification n''a pu etre attribuee');
insert into msg values (1, 314, 2, 2,
'Renouveller votre essai');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 315 and msg.s_id = 2;
insert into msg values (1, 315, 2, 1,
'Aucune Designation n''a pu etre copiee pour la nouvelle Langue');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 316 and msg.s_id = 2;
insert into msg values (1, 316, 2, 1,
'Aucune Description/Texte n''a pu etre copie pour la nouvelle Langue');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 317 and msg.s_id = 2;
insert into msg values (1, 317, 2, 1,
'Cette Langue ne peut etre supprimee, c''est la Langue du systeme');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 318 and msg.s_id = 2;
insert into msg values (1, 318, 2, 1,
'Les donnees graphiques sont trop grandes, executer un export');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 319 and msg.s_id = 2;
insert into msg values (1, 319, 2, 1,
'Aucun Responsable n''est defini pour le Groupe/Collectif en cours');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 320 and msg.s_id = 2;
insert into msg values (1, 320, 2, 1,
'Les Actions n''ont pu etre executees, verifiez les entrees');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 321 and msg.s_id = 2;
insert into msg values (1, 321, 2, 1,
'Le Type-Offre ne peut etre efface, il est utilise dans la table des Offres');
insert into msg values (1, 321, 2, 2,
'Effacez en premier les entrees correspondantes');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 322 and msg.s_id = 2;
insert into msg values (1, 322, 2, 1,
'Aucune donnee de Reservation n''est disponible pour la Reservation en cours');
insert into msg values (1, 322, 2, 2,
'Verifiez la Reservation a l''aide d''Info');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 323 and msg.s_id = 2;
insert into msg values (1, 323, 2, 1,
'Ce Service ne peut faire l''objet d''une Reservation');
insert into msg values (1, 323, 2, 2,
'Le genre de Reservation du Service ne le permet pas');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 324 and msg.s_id = 2;
insert into msg values (1, 324, 2, 1,
'Les dates (debut, fin) sont necessaires pour ce Service');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 325 and msg.s_id = 2;
insert into msg values (1, 325, 2, 1,
'Plus de Support libre pour le Service !');
insert into msg values (1, 325, 2, 2,
'Choisir un autre Service ou une autre date');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 326 and msg.s_id = 2;
insert into msg values (1, 326, 2, 1,
'Le Support choisi a une contenance de %d personnes');
insert into msg values (1, 326, 2, 2,
'Une reservation avec %d personnes est impossible');
insert into msg values (1, 326, 2, 3,
'Choisir un autre Support ou une autre Categorie');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 327 and msg.s_id = 2;
insert into msg values (1, 327, 2, 1,
'Le support choisi est occupe par la Reservation %d');
insert into msg values (1, 327, 2, 2,
'Dans cette reservation, %d personnes sont prevues');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 328 and msg.s_id = 2;
insert into msg values (1, 328, 2, 1,
'Der aktuelle Aktionstyp kann nicht geloescht werden, weil noch Aktions-');
insert into msg values (1, 328, 2, 2,
'parameter darauf definiert sind. Bitte loeschen Sie zuerst alle Parameter');
insert into msg values (1, 328, 2, 3,
'dieses Aktionstyps');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 329 and msg.s_id = 2;
insert into msg values (1, 329, 2, 1,
'Sie muessen eine Parameterbezeichnung im Feld Parameter eingeben');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 330 and msg.s_id = 2;
insert into msg values (1, 330, 2, 1,
'Sie koennen den Parameter nur als Flag definieren, wenn Sie keinen');
insert into msg values (1, 330, 2, 2,
'Parametertyp waehlen');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 331 and msg.s_id = 2;
insert into msg values (1, 331, 2, 1,
'Der aktuelle Aktion kann nicht geloescht werden, weil noch Aktionsgruppen');
insert into msg values (1, 331, 2, 2,
'darauf definiert sind. Bitte loeschen Sie zuerst alle Aktionsgruppen-');
insert into msg values (1, 331, 2, 3,
'Eintragungen die diese Aktion definiert haben');
commit work;

delete from msg where msg.msg_typ = 1 and msg.msg_id = 332 and msg.s_id = 2;
insert into msg values (1, 332, 2, 1,
'Es liegt keine oder eine fehlerhafte Aktionsdefinition fuer die aktuelle');
insert into msg values (1, 332, 2, 2,
'Dienstleistung/Dienstleistungsangebot vor. Ueberpruefen Sie die');
insert into msg values (1, 332, 2, 3,
'Definitionen im Dienstleistungs-/Angebots-Menu oder die');
insert into msg values (1, 332, 2, 4,
'Definitionen im Aktions-/Aktionsgruppen Menu.');
commit work;
