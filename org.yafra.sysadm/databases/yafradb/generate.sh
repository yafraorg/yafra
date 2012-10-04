#!/bin/sh
#
#  Copyright 2012 yafra.org
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
# generate database yafradb
#
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
mysql --user=root --password=$2 -v -v <dbe_delete.sql
mysql --user=root --password=$2 -v -v <dbe_create.sql >tdb_core_$1.log

echo Creates the core database ...
echo ... tables and functions stored procs
mysql $1 --user=root --password=$2 -v -v <mysql_dbe_tables.sql >>tdb_core_$1.log
