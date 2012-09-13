@ echo off
REM
REM generate database travelDB
REM
REM arguments are: 1: ora sid 2: dba system pwd
if "%1" == "" goto errorargs


REM 
REM CREATE CORE DATABASE
REM
echo Create a new "traveldb" database by your Oracle Client tools
echo. 
sqlplus sqlplus system/%2@%1 <dbe_users.sql >mapo_core_%1.log

REM 
REM convert abstract scripts
REM
echo prepare scripts ...

copy ..\abstract\out_d_common.sql .
perl convert2ora.pl out_d_common.sql
del out_d_common.sql
copy ..\abstract\out_d_request.sql .
perl convert2ora.pl out_d_request.sql
del out_d_request.sql

copy ..\abstract\def_e_labels.sql .
perl convert2ora.pl def_e_labels.sql
del def_e_labels.sql
copy ..\abstract\def_d_labels.sql .
perl convert2ora.pl def_d_labels.sql
del def_d_labels.sql
copy ..\abstract\def_mp2000labels.sql .
perl convert2ora.pl def_mp2000labels.sql
del def_mp2000labels.sql

copy ..\abstract\def_d_msgsys.sql .
perl convert2ora.pl def_d_msgsys.sql
del def_d_msgsys.sql
copy ..\abstract\def_d_msgerr.sql .
perl convert2ora.pl def_d_msgerr.sql
del def_d_msgerr.sql
copy ..\abstract\def_d_msgsql.sql .
perl convert2ora.pl def_d_msgsql.sql
del def_d_msgsql.sql
copy ..\abstract\def_d_msginf.sql .
perl convert2ora.pl def_d_msginf.sql
del def_d_msginf.sql
copy ..\abstract\def_d_msgwar.sql .
perl convert2ora.pl def_d_msgwar.sql
del def_d_msgwar.sql
copy ..\abstract\def_d_msgakt.sql .
perl convert2ora.pl def_d_msgakt.sql
del def_d_msgakt.sql

copy ..\abstract\def_d_aktionen.sql .
perl convert2ora.pl def_d_aktionen.sql
del def_d_aktionen.sql
copy ..\abstract\def_aktionen.sql .
perl convert2ora.pl def_aktionen.sql
del def_aktionen.sql
copy ..\abstract\def_d_status.sql .
perl convert2ora.pl def_d_status.sql
del def_d_status.sql

copy ..\abstract\def_types.sql .
perl convert2ora.pl def_types.sql
del def_types.sql
copy ..\abstract\def_geo.sql .
perl convert2ora.pl def_geo.sql
del def_geo.sql

copy ..\abstract\def_d_init.sql .
perl convert2ora.pl def_d_init.sql
del def_d_init.sql
copy ..\abstract\def_languages.sql .
perl convert2ora.pl def_languages.sql
del def_languages.sql



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
copy ..\abstract\dbe_tables.sql .
perl convert2ora.pl dbe_tables.sql
del dbe_tables.sql

REM
REM execute scripts
REM
echo Creates the core database ...
echo ... tables and functions stored procs
sqlplus sqlplus root/root@%1 <ora_dbe_tables.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <dbe_functions.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <dbe_tdbsp.sql >>mapo_core_%1.log
echo ... views
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

echo ... initial load
sqlplus sqlplus root/root@%1 <ora_def_languages.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_def_d_init.sql >>mapo_core_%1.log
echo ... load geo
sqlplus sqlplus root/root@%1 <ora_def_geo.sql >>mapo_core_%1.log
echo ... load types
sqlplus sqlplus root/root@%1 <ora_def_types.sql >>mapo_core_%1.log
echo ... load status_werte
sqlplus sqlplus root/root@%1 <ora_def_d_status.sql >>mapo_core_%1.log

echo ... load other scripts
sqlplus sqlplus root/root@%1 <ora_def_d_aktionen.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_def_aktionen.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_def_d_msgsys.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_def_d_msgerr.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_def_d_msgsql.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_def_d_msgwar.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_def_d_msgakt.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_def_d_msginf.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_out_d_common.sql >>mapo_core_%1.log
sqlplus sqlplus root/root@%1 <ora_out_d_request.sql >>mapo_core_%1.log
goto end

:errorargs
echo missing arguments - use [ora sid] [system password]

:end