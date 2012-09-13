@ echo off
REM
REM updates travelDB
REM
REM arguments are: 1: sapwd


REM 
REM convert abstract scripts
REM
echo prepare scripts ...

copy ..\abstract\dbe_tdbviews.sql .
perl convert2ora.pl dbe_tdbviews.sql
del dbe_tdbviews.sql

copy ..\abstract\dbe_tdbviewsgrant.sql .
perl convert2ora.pl dbe_tdbviewsgrant.sql
del dbe_tdbviewsgrant.sql

REM copy ..\abstract\dbe_grant.sql .
REM perl convert2mssql.pl dbe_grant.sql
REM del dbe_grant.sql
REM copy ..\abstract\dbe_views.sql .
REM perl convert2mssql.pl dbe_views.sql
REM del dbe_views.sql
REM copy ..\abstract\dbe_index.sql .
REM perl convert2mssql.pl dbe_index.sql
REM del dbe_index.sql
REM copy ..\abstract\dbe_tables.sql .
REM perl convert2mssql.pl dbe_tables.sql
REM del dbe_tables.sql

REM
REM execute scripts
REM
echo drop tdbviews and addons ...
sqlplus root/root@%1 <ora_drop.sql >mapo_core_%1.log
echo ... views
sqlplus root/root@%1 <ora_dbe_tdbviews.sql >>mapo_core_%1.log
echo ... grant
sqlplus root/root@%1 <ora_dbe_tdbviewsgrant.sql >>mapo_core_%1.log
echo ... stored procs
sqlplus root/root@%1 <dbe_functions.sql >>mapo_core_%1.log

REM echo ... initial load
REM isql -U root -P root -d traveldb -n <mssql_def_languages.sql >>mapo_core_%1.log
REM isql -U root -P root -d traveldb -n <mssql_def_d_init.sql >>mapo_core_%1.log
REM echo ... load geo
REM isql -U root -P root -d traveldb -n <mssql_def_geo.sql >>mapo_core_%1.log
REM echo ... load types
REM isql -U root -P root -d traveldb -n <mssql_def_types.sql >>mapo_core_%1.log
REM echo ... load status_werte
REM isql -U root -P root -d traveldb -n <mssql_def_d_status.sql >>mapo_core_%1.log
REM 
REM echo ... load other scripts
REM isql -U root -P root -d traveldb -n <mssql_def_d_aktionen.sql >>mapo_core_%1.log
REM isql -U root -P root -d traveldb -n <mssql_def_aktionen.sql >>mapo_core_%1.log
REM isql -U root -P root -d traveldb -n <mssql_def_d_msgsys.sql >>mapo_core_%1.log
REM isql -U root -P root -d traveldb -n <mssql_def_d_msgerr.sql >>mapo_core_%1.log
REM isql -U root -P root -d traveldb -n <mssql_def_d_msgsql.sql >>mapo_core_%1.log
REM isql -U root -P root -d traveldb -n <mssql_def_d_msgwar.sql >>mapo_core_%1.log
REM isql -U root -P root -d traveldb -n <mssql_def_d_msgakt.sql >>mapo_core_%1.log
REM isql -U root -P root -d traveldb -n <mssql_def_d_msginf.sql >>mapo_core_%1.log
REM isql -U root -P root -d traveldb -n <mssql_out_d_common.sql >>mapo_core_%1.log
REM isql -U root -P root -d traveldb -n <mssql_out_d_request.sql >>mapo_core_%1.log
