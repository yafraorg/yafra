/* use the newly created database now */
use [traveldb];
GO

/* create tdbadmin user */
CREATE USER [tdbadmin] FOR LOGIN [tdbadmin] WITH DEFAULT_SCHEMA=[tdbadmin];
GO
EXEC sys.sp_addsrvrolemember @loginame = N'tdbadmin', @rolename = N'sysadmin';
GO
GRANT  CREATE FUNCTION ,  CREATE TABLE ,  CREATE VIEW ,  CREATE PROCEDURE ,  DUMP DATABASE ,  CREATE DEFAULT ,  DUMP TRANSACTION ,  CREATE RULE  TO tdbadmin;
GO

/* create roles */
EXEC sp_addrole N'mpuser';
GO
EXEC sp_addrole N'mpbooker';
GO
EXEC sp_addrole N'mpreadonly';
GO
EXEC sp_addrole N'mpadmin';
GO

ALTER AUTHORIZATION ON ROLE::[mpuser] TO [tdbadmin]
GO
ALTER AUTHORIZATION ON ROLE::[mpbooker] TO [tdbadmin]
GO
ALTER AUTHORIZATION ON ROLE::[mpreadonly] TO [tdbadmin]
GO
ALTER AUTHORIZATION ON ROLE::[mpadmin] TO [tdbadmin]
GO

ALTER AUTHORIZATION ON SCHEMA::[tdbadmin] TO [tdbadmin]
GO
ALTER AUTHORIZATION ON SCHEMA::[mpadmin] TO [tdbadmin];
GO
ALTER AUTHORIZATION ON SCHEMA::[mpbooker] TO [tdbadmin];
GO
ALTER AUTHORIZATION ON SCHEMA::[mpuser] TO [tdbadmin];
GO
ALTER AUTHORIZATION ON SCHEMA::[mpreadonly] TO [tdbadmin];
GO

EXEC sp_addrolemember N'mpadmin', N'tdbadmin';
GO
EXEC sp_addrolemember N'mpbooker', N'tdbadmin';
GO
EXEC sp_addrolemember N'mpreadonly', N'tdbadmin';
GO
EXEC sp_addrolemember N'mpuser', N'tdbadmin';
GO
EXEC sp_addrolemember N'db_securityadmin', N'tdbadmin';
GO
EXEC sp_addrolemember N'db_accessadmin', N'tdbadmin';
GO
EXEC sp_addrolemember N'db_owner', N'tdbadmin';
GO

GRANT ALTER ANY APPLICATION ROLE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY ASSEMBLY TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY ASYMMETRIC KEY TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY CERTIFICATE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY CONTRACT TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY DATABASE DDL TRIGGER TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY DATABASE EVENT NOTIFICATION TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY DATASPACE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY FULLTEXT CATALOG TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY MESSAGE TYPE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY REMOTE SERVICE BINDING TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY ROLE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY ROUTE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY SCHEMA TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY SERVICE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY SYMMETRIC KEY TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER ANY USER TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT ALTER TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT AUTHENTICATE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT BACKUP DATABASE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT BACKUP LOG TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CHECKPOINT TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CONNECT REPLICATION TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CONNECT TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CONTROL TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE AGGREGATE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE ASSEMBLY TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE ASYMMETRIC KEY TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE CERTIFICATE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE CONTRACT TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE DATABASE DDL EVENT NOTIFICATION TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE DEFAULT TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE FULLTEXT CATALOG TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE FUNCTION TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE MESSAGE TYPE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE PROCEDURE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE QUEUE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE REMOTE SERVICE BINDING TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE ROLE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE ROUTE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE RULE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE SCHEMA TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE SERVICE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE SYMMETRIC KEY TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE SYNONYM TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE TABLE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE TYPE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE VIEW TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT CREATE XML SCHEMA COLLECTION TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT DELETE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT EXECUTE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT INSERT TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT REFERENCES TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT SELECT TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT SHOWPLAN TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT SUBSCRIBE QUERY NOTIFICATIONS TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT TAKE OWNERSHIP TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT UPDATE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT VIEW DATABASE STATE TO [tdbadmin] WITH GRANT OPTION 
GO
use [traveldb]
GO
GRANT VIEW DEFINITION TO [tdbadmin] WITH GRANT OPTION 
GO
