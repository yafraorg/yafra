@ echo off
REM
REM generate database travelDB with a dump
REM
REM arguments are: 1: ora sid 2: dba system pwd
if "%1" == "" goto errorargs


REM 
REM CREATE CORE DATABASE
REM
echo Create a new "traveldb" database by your Oracle Client tools
echo. 
sqlplus sqlplus system/%2@%1 <dbe_users.sql >mapo_core_%1.log
imp root/root\@%1 FILE=mapodemo.dmp FROMUSER=root TOUSER=root COMMIT=yes IGNORE=yes BUFFER=103200 LOG=%1.txt GRANTS=no

copy ..\abstract\dbe_tdbviews.sql .
perl convert2ora.pl dbe_tdbviews.sql
del dbe_tdbviews.sql
copy ..\abstract\dbe_tdbviewsgrant.sql .
perl convert2ora.pl dbe_tdbviewsgrant.sql
del dbe_tdbviewsgrant.sql

copy ..\abstract\dbe_grant.sql .
perl convert2ora.pl dbe_grant.sql
del dbe_grant.sql
copy ..\abstract\dbe_views.sql .
perl convert2ora.pl dbe_views.sql
del dbe_views.sql
copy ..\abstract\dbe_index.sql .
perl convert2ora.pl dbe_index.sql
del dbe_index.sql

REM
REM execute scripts
REM
echo Creates the core database ...
echo ... tables and functions stored procs
sqlplus sqlplus root/root@%1 <dbe_functions.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <dbe_tdbsp.sql >>mapo_core_%1.log
echo ... views
sqlplus sqlplus root/root@%1 <ora_dbe_drop_views.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_dbe_views.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <dbe_javaviews.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_dbe_tdbviews.sql >>mapo_core_%1.log
echo ... index
sqlplus sqlplus root/root@%1 <ora_dbe_index.sql >>mapo_core_%1.log
echo ... grant
sqlplus sqlplus root/root@%1 <ora_dbe_grant.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_dbe_tdbviewsgrant.sql >>mapo_core_%1.log
echo ... sequences
sqlplus sqlplus root/root@%1 <dbe_sequences.sql >>mapo_core_%1.log
goto end

:errorargs
echo missing arguments - use [ora sid] [system password]

:end