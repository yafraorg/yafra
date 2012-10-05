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
mysql --user=root --password=$2 --force -v -v <dbe_init.sql >tdb_core_$1.log

#
# execute scripts
#
echo Creates the core database ...
echo ... tables and functions stored procs
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_dbe_tables.sql >>tdb_core_$1.log
#mysql $1 --user=tdbadmin --password=$2 -v -v <dbe_functions.sql >>tdb_core_$1.log
#mysql $1 --user=tdbadmin --password=$2 -v -v <dbe_tdbsp.sql >>tdb_core_$1.log
echo ... views
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_dbe_views.sql >>tdb_core_$1.log
#mysql $1 --user=tdbadmin --password=$2 -v -v <dbe_javaviews.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_dbe_tdbviews.sql >>tdb_core_$1.log
echo ... index
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_dbe_index.sql >>tdb_core_$1.log

#echo ... grant
#mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_dbe_grant.sql >>tdb_core_$1.log
#mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_dbe_tdbviewsgrant.sql >>tdb_core_$1.log

echo ... initial load lang: german
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_languages.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_d_init.sql >>tdb_core_$1.log
echo ... load geo
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_geo.sql >>tdb_core_$1.log
echo ... load types
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_types.sql >>tdb_core_$1.log
echo ... load status_werte
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_d_status.sql >>tdb_core_$1.log

echo ... load other scripts lang: german
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_d_aktionen.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_aktionen.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_d_labels.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_mp2000labels.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_d_msgsys.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_d_msgerr.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_d_msgsql.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_d_msgwar.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_d_msgakt.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_d_msginf.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_out_d_common.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_out_d_request.sql >>tdb_core_$1.log

echo ... load other scripts lang: english
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_e_labels.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_e_msgsys.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_e_msgerr.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_e_msgsql.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_e_msgwar.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_e_msgact.sql >>tdb_core_$1.log
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_e_msginf.sql >>tdb_core_$1.log

echo ... load demo data
mysql $1 --user=tdbadmin --password=$2 -v -v <mysql_def_demo.sql >>tdb_core_$1.log

