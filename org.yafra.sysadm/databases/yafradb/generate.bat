@ echo off
REM
REM generate database travelDB
REM
REM arguments are: 1: sapwd 2: tdbadminpwd
if "%1" == "" goto errorargs
if "%2" == "" goto errorargs

set DBCMD=sqlcmd -S .\SQLExpress
set TDBUSER=tdbadmin
set DBNAME=traveldb

REM 
REM CREATE CORE DATABASE
REM
echo Deletes the old database first and then
echo creating new traveldb database as sa ... 
echo Deleting and creating new database >tdb_init.log
sqlcmd -S .\SQLExpress -U sa -P %1 -i dbe_init_mssql.sql >>tdb_init.log
if not errorlevel 0 goto errorisql
echo database creation done

REM 
REM CREATE CORE DATABASE
REM
echo Creates new "traveldb" database sa/%1 and tdbadmin/%2 (create this user first with dba) >tdb_core.log
echo Creates new "traveldb" database sa/%1 and tdbadmin/%2 (create this user first with dba)
echo. 
echo creating logins and schemas
REM %DBCMD% -U sa -P %1 -d %DBNAME% -Q "CREATE LOGIN [%TDBUSER%] WITH PASSWORD=N'%2', CHECK_POLICY=OFF, DEFAULT_DATABASE=[%DBNAME%]" >>tdb_core.log
%DBCMD% -U sa -P %1 -d %DBNAME% -Q "CREATE SCHEMA [%TDBUSER%] AUTHORIZATION [dbo]" >>tdb_core.log
%DBCMD% -U sa -P %1 -i dbe_create.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i dbe_users.sql >>tdb_core.log


REM
REM execute scripts
REM
echo Creates the core database ... >>tdb_core.log
echo Creates the core database ...
echo ... tables and functions stored procs
echo tables >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_dbe_tables.sql >>tdb_core.log
echo tdbsp >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i dbe_tdbsp.sql >>tdb_core.log
echo ... views
echo views >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_dbe_views.sql >>tdb_core.log
echo tdbviews >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_dbe_tdbviews.sql >>tdb_core.log
echo ... index
echo index >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_dbe_index.sql >>tdb_core.log
echo ... grant
echo grant >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_dbe_grant.sql >>tdb_core.log
echo grant tdbviews >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_dbe_tdbviewsgrant.sql >>tdb_core.log
REM echo ... sequences
REM sqlcmd -S .\SQLExpress -U tdbadmin -P %2 -d traveldb -i dbe_sequences.sql >>tdb_core.log

echo ... initial load
echo lang >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_languages.sql >>tdb_core.log
echo init >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_d_init.sql >>tdb_core.log
echo ... load geo
echo geo >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_geo.sql >>tdb_core.log
echo ... load types
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_types.sql >>tdb_core.log
echo ... load status_werte
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_d_status.sql >>tdb_core.log

echo ... load other scripts
echo msg >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_d_labels.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_mp2000labels.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_d_aktionen.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_aktionen.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_d_msgsys.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_d_msgerr.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_d_msgsql.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_d_msgwar.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_d_msgakt.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_d_msginf.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_out_d_common.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_out_d_request.sql >>tdb_core.log

echo ... load other scripts lang: english
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_e_labels.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_e_msgsys.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_e_msgerr.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_e_msgsql.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_e_msgwar.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_e_msgact.sql >>tdb_core.log
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_e_msginf.sql >>tdb_core.log

echo ... load demo data
%DBCMD% -U %TDBUSER% -P %2 -d %DBNAME% -i mssql_def_demo.sql >>tdb_core.log

goto end

:errorargs
echo missing arguments - use [sa password] [tdbadmin password]

:errorisql
echo error returned from isql

:end
