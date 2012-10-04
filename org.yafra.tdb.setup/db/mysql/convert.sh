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
# generate database travelDB scripts
#
#

# 
# convert abstract scripts
#
echo prepare scripts ...

cp ../abstract/out_d_common.sql .
perl convert2mysql.pl out_d_common.sql
rm out_d_common.sql
cp ../abstract/out_d_request.sql .
perl convert2mysql.pl out_d_request.sql
rm out_d_request.sql
cp ../abstract/out_d_auftrag.sql .
perl convert2mysql.pl out_d_auftrag.sql
rm out_d_auftrag.sql
cp ../abstract/out_d_order.sql .
perl convert2mysql.pl out_d_order.sql
rm out_d_order.sql


cp ../abstract/def_e_labels.sql .
perl convert2mysql.pl def_e_labels.sql
rm def_e_labels.sql
cp ../abstract/def_d_labels.sql .
perl convert2mysql.pl def_d_labels.sql
rm def_d_labels.sql
cp ../abstract/def_mp2000labels.sql .
perl convert2mysql.pl def_mp2000labels.sql
rm def_mp2000labels.sql

cp ../abstract/def_d_msgsys.sql .
perl convert2mysql.pl def_d_msgsys.sql
rm def_d_msgsys.sql
cp ../abstract/def_d_msgerr.sql .
perl convert2mysql.pl def_d_msgerr.sql
rm def_d_msgerr.sql
cp ../abstract/def_d_msgsql.sql .
perl convert2mysql.pl def_d_msgsql.sql
rm def_d_msgsql.sql
cp ../abstract/def_d_msginf.sql .
perl convert2mysql.pl def_d_msginf.sql
rm def_d_msginf.sql
cp ../abstract/def_d_msgwar.sql .
perl convert2mysql.pl def_d_msgwar.sql
rm def_d_msgwar.sql
cp ../abstract/def_d_msgakt.sql .
perl convert2mysql.pl def_d_msgakt.sql
rm def_d_msgakt.sql

cp ../abstract/def_e_msgsys.sql .
perl convert2mysql.pl def_e_msgsys.sql
rm def_e_msgsys.sql
cp ../abstract/def_e_msgerr.sql .
perl convert2mysql.pl def_e_msgerr.sql
rm def_e_msgerr.sql
cp ../abstract/def_e_msgsql.sql .
perl convert2mysql.pl def_e_msgsql.sql
rm def_e_msgsql.sql
cp ../abstract/def_e_msginf.sql .
perl convert2mysql.pl def_e_msginf.sql
rm def_e_msginf.sql
cp ../abstract/def_e_msgwar.sql .
perl convert2mysql.pl def_e_msgwar.sql
rm def_e_msgwar.sql
cp ../abstract/def_e_msgact.sql .
perl convert2mysql.pl def_e_msgact.sql
rm def_e_msgact.sql


cp ../abstract/def_d_aktionen.sql .
perl convert2mysql.pl def_d_aktionen.sql
rm def_d_aktionen.sql
cp ../abstract/def_aktionen.sql .
perl convert2mysql.pl def_aktionen.sql
rm def_aktionen.sql
cp ../abstract/def_d_status.sql .
perl convert2mysql.pl def_d_status.sql
rm def_d_status.sql

cp ../abstract/def_demo.sql .
perl convert2mysql.pl def_demo.sql
rm def_demo.sql

cp ../abstract/def_types.sql .
perl convert2mysql.pl def_types.sql
rm def_types.sql
cp ../abstract/def_geo.sql .
perl convert2mysql.pl def_geo.sql
rm def_geo.sql

cp ../abstract/def_d_init.sql .
perl convert2mysql.pl def_d_init.sql
rm def_d_init.sql
cp ../abstract/def_languages.sql .
perl convert2mysql.pl def_languages.sql
rm def_languages.sql


cp ../abstract/dbe_tdbviews.sql .
perl convert2mysql.pl dbe_tdbviews.sql
rm dbe_tdbviews.sql
#cp ../abstract/dbe_tdbviewsgrant.sql .
#perl convert2mysql.pl dbe_tdbviewsgrant.sql
#rm dbe_tdbviewsgrant.sql


#cp ../abstract/dbe_grant.sql .
#perl convert2mysql.pl dbe_grant.sql
#rm dbe_grant.sql
cp ../abstract/dbe_views.sql .
perl convert2mysql.pl dbe_views.sql
rm dbe_views.sql
cp ../abstract/dbe_index.sql .
perl convert2mysql.pl dbe_index.sql
rm dbe_index.sql
cp ../abstract/dbe_tables.sql .
perl convert2mysql.pl dbe_tables.sql
rm dbe_tables.sql

echo scripts converted
