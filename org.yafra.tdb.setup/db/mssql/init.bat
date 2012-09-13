@ echo off
REM
REM delete database travelDB
REM
REM arguments are: 1: sapwd
if "%1" == "" goto errorargs

REM 
REM CREATE CORE DATABASE
REM
echo Deletes the old database first and then
echo creating new traveldb database as sa ... 
echo Deleting and creating new database >tdb_init.log
sqlcmd -S .\SQLExpress -U sa -P %1 -i dbe_init.sql >>tdb_init.log
if not errorlevel 0 goto errorisql
echo done
goto end

:errorargs
echo missing argument sa password
goto end

:errorisql
echo error returned from isql

:end
