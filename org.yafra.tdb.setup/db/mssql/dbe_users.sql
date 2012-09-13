/* create users */
USE [traveldb]
GO

/*
if not exists (select * from master.dbo.syslogins where loginname = N'mwn')
BEGIN
	CREATE LOGIN mwn WITH PASSWORD = 'mwn', CHECK_POLICY = OFF, DEFAULT_DATABASE = traveldb;
	CREATE USER mwn FOR LOGIN mwn WITH DEFAULT_SCHEMA = root;
	GRANT  CREATE FUNCTION ,  CREATE TABLE ,  CREATE VIEW ,  CREATE PROCEDURE ,  DUMP DATABASE ,  CREATE DEFAULT ,  DUMP TRANSACTION ,  CREATE RULE  TO mwn;
	exec sp_addrolemember N'mpuser', N'mwn';
END

-- exec sp_addrolemember N'db_accessadmin', N'mwn'
-- exec sp_addrolemember N'db_backupoperator', N'mwn'
-- exec sp_addrolemember N'db_datareader', N'mwn'
-- exec sp_addrolemember N'db_datawriter', N'mwn'
-- exec sp_addrolemember N'db_ddladmin', N'mwn'
-- exec sp_addrolemember N'db_denydatareader', N'mwn'
-- exec sp_addrolemember N'db_denydatawriter', N'mwn'
-- exec sp_addrolemember N'db_owner', N'mwn'
-- exec sp_addrolemember N'db_securityadmin', N'mwn'
exec sp_addrolemember N'mpadmin', N'mwn'
exec sp_addrolemember N'mpbooker', N'mwn'
exec sp_addrolemember N'mpreadonly', N'mwn'
exec sp_addrolemember N'mpuser', N'mwn'
GO
*/

/* demo */
if not exists (select * from master.dbo.syslogins where loginname = N'demo')
BEGIN
	CREATE LOGIN demo WITH PASSWORD = 'demo', CHECK_POLICY = OFF, DEFAULT_DATABASE = traveldb;
	CREATE USER demo FOR LOGIN demo WITH DEFAULT_SCHEMA = root;
	GRANT  CREATE FUNCTION ,  CREATE TABLE ,  CREATE VIEW ,  CREATE PROCEDURE ,  DUMP DATABASE ,  CREATE DEFAULT ,  DUMP TRANSACTION ,  CREATE RULE  TO demo;
	exec sp_addrolemember N'mpuser', N'demo';
END
GO


/* www */
if not exists (select * from master.dbo.syslogins where loginname = N'www')
BEGIN
	CREATE LOGIN www WITH PASSWORD = 'www', CHECK_POLICY = OFF, DEFAULT_DATABASE = traveldb;
	CREATE USER www FOR LOGIN www WITH DEFAULT_SCHEMA = root;
	GRANT  CREATE TABLE, CREATE VIEW TO www;
	exec sp_addrolemember N'mpreadonly', N'www';
END
GO

