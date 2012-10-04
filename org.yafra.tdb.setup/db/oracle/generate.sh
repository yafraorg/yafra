#!/usr/bin/sh
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
