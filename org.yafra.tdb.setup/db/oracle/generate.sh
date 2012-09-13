#!/usr/bin/sh
#
# generate database travelDB
#
# arguments are: 1: ora sid 2: dba system pwd
if [ -z "$1" ]; then
        echo Please specify 2 parameters: 1 ora sid and 2 dba system pwd
        exit
fi

# 
# CREATE CORE DATABASE
#
echo Create a new "traveldb" database by your Oracle Client tools
echo "\n"
sqlplus system/$2@$1 <dbe_users.sql >mapo_core_$1.log

# 
# convert abstract scripts
#
echo prepare scripts ...

cp ../abstract/out_d_common.sql .
perl convert2ora.pl out_d_common.sql
rm out_d_common.sql
cp ../abstract/out_d_request.sql .
perl convert2ora.pl out_d_request.sql
rm out_d_request.sql

cp ../abstract/def_e_labels.sql .
perl convert2ora.pl def_e_labels.sql
rm def_e_labels.sql
cp ../abstract/def_d_labels.sql .
perl convert2ora.pl def_d_labels.sql
rm def_d_labels.sql
cp ../abstract/def_mp2000labels.sql .
perl convert2ora.pl def_mp2000labels.sql
rm def_mp2000labels.sql

cp ../abstract/def_d_msgsys.sql .
perl convert2ora.pl def_d_msgsys.sql
rm def_d_msgsys.sql
cp ../abstract/def_d_msgerr.sql .
perl convert2ora.pl def_d_msgerr.sql
rm def_d_msgerr.sql
cp ../abstract/def_d_msgsql.sql .
perl convert2ora.pl def_d_msgsql.sql
rm def_d_msgsql.sql
cp ../abstract/def_d_msginf.sql .
perl convert2ora.pl def_d_msginf.sql
rm def_d_msginf.sql
cp ../abstract/def_d_msgwar.sql .
perl convert2ora.pl def_d_msgwar.sql
rm def_d_msgwar.sql
cp ../abstract/def_d_msgakt.sql .
perl convert2ora.pl def_d_msgakt.sql
rm def_d_msgakt.sql

cp ../abstract/def_d_aktionen.sql .
perl convert2ora.pl def_d_aktionen.sql
rm def_d_aktionen.sql
cp ../abstract/def_aktionen.sql .
perl convert2ora.pl def_aktionen.sql
rm def_aktionen.sql
cp ../abstract/def_d_status.sql .
perl convert2ora.pl def_d_status.sql
rm def_d_status.sql

cp ../abstract/def_types.sql .
perl convert2ora.pl def_types.sql
rm def_types.sql
cp ../abstract/def_geo.sql .
perl convert2ora.pl def_geo.sql
rm def_geo.sql

cp ../abstract/def_d_init.sql .
perl convert2ora.pl def_d_init.sql
rm def_d_init.sql
cp ../abstract/def_languages.sql .
perl convert2ora.pl def_languages.sql
rm def_languages.sql



cp ../abstract/dbe_tdbviews.sql .
perl convert2ora.pl dbe_tdbviews.sql
rm dbe_tdbviews.sql
cp ../abstract/dbe_tdbviewsgrant.sql .
perl convert2ora.pl dbe_tdbviewsgrant.sql
rm dbe_tdbviewsgrant.sql


cp ../abstract/dbe_grant.sql .
perl convert2ora.pl dbe_grant.sql
rm dbe_grant.sql
cp ../abstract/dbe_views.sql .
perl convert2ora.pl dbe_views.sql
rm dbe_views.sql
cp ../abstract/dbe_index.sql .
perl convert2ora.pl dbe_index.sql
rm dbe_index.sql
cp ../abstract/dbe_tables.sql .
perl convert2ora.pl dbe_tables.sql
rm dbe_tables.sql

#
# execute scripts
#
echo Creates the core database ...
echo ... tables and functions stored procs
sqlplus root/root@$1 <ora_dbe_tables.sql >>mapo_core_$1.log
sqlplus root/root@$1 <dbe_functions.sql >>mapo_core_$1.log
sqlplus root/root@$1 <dbe_tdbsp.sql >>mapo_core_$1.log
echo ... views
sqlplus root/root@$1 <ora_dbe_views.sql >>mapo_core_$1.log
sqlplus root/root@$1 <dbe_javaviews.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_dbe_tdbviews.sql >>mapo_core_$1.log
echo ... index
sqlplus root/root@$1 <ora_dbe_index.sql >>mapo_core_$1.log
echo ... grant
sqlplus root/root@$1 <ora_dbe_grant.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_dbe_tdbviewsgrant.sql >>mapo_core_$1.log
echo ... sequences
sqlplus root/root@$1 <dbe_sequences.sql >>mapo_core_$1.log

echo ... initial load
sqlplus root/root@$1 <ora_def_languages.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_def_d_init.sql >>mapo_core_$1.log
echo ... load geo
sqlplus root/root@$1 <ora_def_geo.sql >>mapo_core_$1.log
echo ... load types
sqlplus root/root@$1 <ora_def_types.sql >>mapo_core_$1.log
echo ... load status_werte
sqlplus root/root@$1 <ora_def_d_status.sql >>mapo_core_$1.log

echo ... load other scripts
sqlplus root/root@$1 <ora_def_d_aktionen.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_def_aktionen.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_def_d_msgsys.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_def_d_msgerr.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_def_d_msgsql.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_def_d_msgwar.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_def_d_msgakt.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_def_d_msginf.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_out_d_common.sql >>mapo_core_$1.log
sqlplus root/root@$1 <ora_out_d_request.sql >>mapo_core_$1.log
