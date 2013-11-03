#!/bin/sh
#
#  Copyright 2002 yafra.org
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
# generate database travelDB
#
# no grant support as mysql < 6.0 has not support for roles/groups
# you need to do it manually by user
# no sequence support or new_id, done by count and max.
# mysql $1 --default-character-set=utf8 -> add this to have UTF-8 support
#    else its latin 1
#
# arguments are: 1: mysql database/schema 2: dba system pwd
if [ -z "$1" ]; then
        echo Please specify 2 parameters: 1 db/schema and 2 dba system pwd
        exit
fi

# 
# CREATE CORE DATABASE
#
echo Create a new "traveldb" database by your mysql tools
echo "\n"
mysql --user=root --password=$2 --force -v -v <dbe_init.sql >/tmp/mysql_tdb_setup$i.log

#
# execute scripts
#
echo Creates the core database ...
echo ... tables and functions stored procs
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_dbe_tables.sql >>/tmp/mysql_tdb_setup$i.log
#mysql $1 --user=tdbadmin --password=yafra -v -v <dbe_functions.sql >>/tmp/mysql_tdb_setup$i.log
#mysql $1 --user=tdbadmin --password=yafra -v -v <dbe_tdbsp.sql >>/tmp/mysql_tdb_setup$i.log
echo ... views
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_dbe_views.sql >>/tmp/mysql_tdb_setup$i.log
#mysql $1 --user=tdbadmin --password=yafra -v -v <dbe_javaviews.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_dbe_tdbviews.sql >>/tmp/mysql_tdb_setup$i.log
echo ... index
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_dbe_index.sql >>/tmp/mysql_tdb_setup$i.log

#echo ... grant
#mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_dbe_grant.sql >>/tmp/mysql_tdb_setup$i.log
#mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_dbe_tdbviewsgrant.sql >>/tmp/mysql_tdb_setup$i.log

echo ... initial load lang: german
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_languages.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_d_init.sql >>/tmp/mysql_tdb_setup$i.log
echo ... load geo
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_geo.sql >>/tmp/mysql_tdb_setup$i.log
echo ... load types
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_types.sql >>/tmp/mysql_tdb_setup$i.log
echo ... load status_werte
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_d_status.sql >>/tmp/mysql_tdb_setup$i.log

echo ... load other scripts lang: german
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_d_aktionen.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_aktionen.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_d_labels.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_mp2000labels.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_d_msgsys.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_d_msgerr.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_d_msgsql.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_d_msgwar.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_d_msgakt.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_d_msginf.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_out_d_common.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_out_d_request.sql >>/tmp/mysql_tdb_setup$i.log

echo ... load other scripts lang: english
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_e_labels.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_e_msgsys.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_e_msgerr.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_e_msgsql.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_e_msgwar.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_e_msgact.sql >>/tmp/mysql_tdb_setup$i.log
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_e_msginf.sql >>/tmp/mysql_tdb_setup$i.log

echo ... load demo data
mysql $1 --user=tdbadmin --password=yafra -v -v <mysql_def_demo.sql >>/tmp/mysql_tdb_setup$i.log

echo ... removing converted sql files
rm mysql_*

