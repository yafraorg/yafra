
Port from HP/ALLBASE G.1 to ORACLE 7.x
======================================

Vorraussetzungen:

 * ORACLE server installiert auf einem host
 * SQLNET installiert (host und windows)
 * ODBC drivers for oracle (16/32bit)
 * setzen von Variablen $ORACLE_HOME (is directory),
   $ORACLE_SID (is dbname ?????) export ORACLE_SID=mapo,
   $PATH auf $ORACLE_HOME/xxx/bin
 * config files init????.ora and config?????.ora generieren
 * sqlnet config files generieren /etc/listener.ora and /etc/tnsnames.ora

Generieren der DB und Erstellen der Objekte:

 Die konvertierung der unload Daten von HP-Allbase konnen im load Directory
 via Makefile durchgefuehrt werden. Dabei werden Files fuer den sqlloader
 von Oracle erstellt, welche nochmals in ein tiefers Directory load geschrieben
 werden. Um alle Daten zu laden kann das file 'dates.bat' ausgefuehrt werden.
 Die Creationskript's koennen via Makefile erstellt werden.
 Die Creationskript's der Objekte koennen vie Makefile ausgefuehrt werden.

 * configmapo.ora in $ORACLE_HOME/dbs erstellen resp. default configSID.ora
   kopieren und anpassen
 * initmapo.ora in $ORACLE_HOME/dbs erstellen resp. default initSID.ora
   kopieren und anpassen
 * sqldba
   - connect internal
   - startup pfile=initmapo.ora nomount
   - @DBE_create.sql
   - scripts im $ORACLE_HOME/rdbms/admin/catalog.sql und
              $ORACLE_HOME/rdbms/admin/catproc.sql als connect internal starten
   - In /etc/oratab die neue DB eintragen und mit '....:Y' kennzeichnen, damit
     beim dbstart die DB automatisch aufgestartet wird.
   - Tablespace fœr Daten,Indx,Rollback und Temp erstellen und einrichten.
     @DBE_tablespace.sql
   - Rollback segment erstellen einrichten Rollback segment im initmapo.ora
     eintragen. DBE_rollback.sql
   - @DBE_user.sql
     Nicht vergessen: os_authent_prefix = "" und remote_os_authent = true damit
     kann ein Benutzer sich œbers Netz einloggen.
   - @DBE_tables.sql
   - @DBE_views.sql
   - @DBE_index.sql
   - @DBE_grantuser.sql
   - @DBE_grant.sql
   - listener.ora und tnsnames.ora in $ORACLE_HOME/network/admin erstellen/
     anpassen
   - tnsnames.ora in /etc/tnsnames.ora auf die clients kopieren.
   - lsnrctl start


   (folgende Befehle koennen auch mit DBE_init gestartet werden)
   - @DBE_tables.sql
   - @DBE_views.sql
   - @DBE_index.sql
   - @DBE_grant.sql
   - @DBE_grantuser.sql
   - @../sql/DEF_?_????.sql (alle default werte fuer init)

Pruefen:

 * sqlplus root/root
   - select table_name from user_tables;
   - select view_name from user_views;


Wie sollte die Oracle-DB aufgebaut sein:
----------------------------------------
- Genuegend grosses DB-Datenfile anlegen, damit nicht gleich wieder vergroessert
  werden muss, da dabei ein neues Datenfile erzeugt wird.

- Es sollten vier Tablespaces erstellt werden:
	1. Daten-Tablespace
	2. Index-Tablespace
	3. Tmp-Tablespace
	4. Rollback-Tablespace

- Ein Rollbacksegment erstellen.

- Create table mit storage parametern versehen.

- Ev. Create index mit storage parametern versehen.

- Jedem Benutzer das Data- und Tmp-Tablespace zuweisen.

