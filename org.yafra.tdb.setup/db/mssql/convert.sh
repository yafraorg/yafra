#!/bin/sh
#
# generate database travelDB
#
# ONLY conversion to be executed on linux to get the sql server scripts

# delete old scripts and logs
rm mssql*


# 
# convert abstract scripts
#
echo prepare scripts ...

cp ../abstract/out_d_common.sql .
perl convert2mssql.pl out_d_common.sql
rm out_d_common.sql
cp ../abstract/out_d_request.sql .
perl convert2mssql.pl out_d_request.sql
rm out_d_request.sql
cp ../abstract/out_d_auftrag.sql .
perl convert2mssql.pl out_d_auftrag.sql
rm out_d_auftrag.sql
cp ../abstract/out_d_order.sql .
perl convert2mssql.pl out_d_order.sql
rm out_d_order.sql


cp ../abstract/def_e_labels.sql .
perl convert2mssql.pl def_e_labels.sql
rm def_e_labels.sql
cp ../abstract/def_d_labels.sql .
perl convert2mssql.pl def_d_labels.sql
rm def_d_labels.sql
cp ../abstract/def_mp2000labels.sql .
perl convert2mssql.pl def_mp2000labels.sql
rm def_mp2000labels.sql

cp ../abstract/def_d_msgsys.sql .
perl convert2mssql.pl def_d_msgsys.sql
rm def_d_msgsys.sql
cp ../abstract/def_d_msgerr.sql .
perl convert2mssql.pl def_d_msgerr.sql
rm def_d_msgerr.sql
cp ../abstract/def_d_msgsql.sql .
perl convert2mssql.pl def_d_msgsql.sql
rm def_d_msgsql.sql
cp ../abstract/def_d_msginf.sql .
perl convert2mssql.pl def_d_msginf.sql
rm def_d_msginf.sql
cp ../abstract/def_d_msgwar.sql .
perl convert2mssql.pl def_d_msgwar.sql
rm def_d_msgwar.sql
cp ../abstract/def_d_msgakt.sql .
perl convert2mssql.pl def_d_msgakt.sql
rm def_d_msgakt.sql

cp ../abstract/def_e_msgsys.sql .
perl convert2mssql.pl def_e_msgsys.sql
rm def_e_msgsys.sql
cp ../abstract/def_e_msgerr.sql .
perl convert2mssql.pl def_e_msgerr.sql
rm def_e_msgerr.sql
cp ../abstract/def_e_msgsql.sql .
perl convert2mssql.pl def_e_msgsql.sql
rm def_e_msgsql.sql
cp ../abstract/def_e_msginf.sql .
perl convert2mssql.pl def_e_msginf.sql
rm def_e_msginf.sql
cp ../abstract/def_e_msgwar.sql .
perl convert2mssql.pl def_e_msgwar.sql
rm def_e_msgwar.sql
cp ../abstract/def_e_msgact.sql .
perl convert2mssql.pl def_e_msgact.sql
rm def_e_msgact.sql


cp ../abstract/def_d_aktionen.sql .
perl convert2mssql.pl def_d_aktionen.sql
rm def_d_aktionen.sql
cp ../abstract/def_aktionen.sql .
perl convert2mssql.pl def_aktionen.sql
rm def_aktionen.sql
cp ../abstract/def_d_status.sql .
perl convert2mssql.pl def_d_status.sql
rm def_d_status.sql

cp ../abstract/def_demo.sql .
perl convert2mssql.pl def_demo.sql
rm def_demo.sql

cp ../abstract/def_types.sql .
perl convert2mssql.pl def_types.sql
rm def_types.sql
cp ../abstract/def_geo.sql .
perl convert2mssql.pl def_geo.sql
rm def_geo.sql

cp ../abstract/def_d_init.sql .
perl convert2mssql.pl def_d_init.sql
rm def_d_init.sql
cp ../abstract/def_languages.sql .
perl convert2mssql.pl def_languages.sql
rm def_languages.sql


cp ../abstract/dbe_tdbviews.sql .
perl convert2mssql.pl dbe_tdbviews.sql
rm dbe_tdbviews.sql
cp ../abstract/dbe_tdbviewsgrant.sql .
perl convert2mssql.pl dbe_tdbviewsgrant.sql
rm dbe_tdbviewsgrant.sql


cp ../abstract/dbe_grant.sql .
perl convert2mssql.pl dbe_grant.sql
rm dbe_grant.sql
cp ../abstract/dbe_views.sql .
perl convert2mssql.pl dbe_views.sql
rm dbe_views.sql
cp ../abstract/dbe_index.sql .
perl convert2mssql.pl dbe_index.sql
rm dbe_index.sql
cp ../abstract/dbe_tables.sql .
perl convert2mssql.pl dbe_tables.sql
rm dbe_tables.sql

