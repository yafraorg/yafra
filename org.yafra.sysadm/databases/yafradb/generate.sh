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
# arguments are: 1: db type 2: dba_pwd 3: dba_username
if [ -z "$1" ]; then
        echo "Please specify 1: db type 2: dba_pwd [3: dba_username 4: hostname]"
        exit
fi

DBANAME="root"
# set the db administrator username
if [ -z "$3" ]; then
	if [ "$1" = "oracle" ]; then
		DBANAME="system"
	fi
	if [ "$1" = "mssql" ]; then
		DBANAME="sa"
	fi
else
	DBANAME="$3"
fi

# set the db hostname
if [ -z "$4" ]; then
	DBHOST="127.0.0.1"
else
	DBHOST="$4"
fi

# 
# CREATE CORE DATABASE
#
echo Create a new "yafradb" database by your tools

if [ "$1" = "mysql" ]; then
	echo "installing mysql database - add --force if needed"
	mysql --user=$DBANAME --password=$2 -v -v -h $DBHOST <dbe_init_mysql.sql
fi
if [ "$1" = "oracle" ]; then
	echo "installing oracle database"
	sqlplus $DBANAME/$2@XE <dbe_init_oracle.sql
fi
if [ "$1" = "mssql" ]; then
	echo "installing mssql database"
	sqlcmd -S .\SQLExpress -U $DBANAME -P $2 -d yafradb -Q "CREATE LOGIN [%TDBUSER%] WITH PASSWORD=N'$1', CHECK_POLICY=OFF, DEFAULT_DATABASE=[%DBNAME%]"
	sqlcmd -S .\SQLExpress -U $DBANAME -P $2 -d yafradb -Q "CREATE SCHEMA [%TDBUSER%] AUTHORIZATION [dbo]" >>tdb_core.REM %DBCMD% -U sa -P %1 -d %DBNAME% -Q "CREATE LOGIN [%TDBUSER%] WITH PASSWORD=N'%2', CHECK_POLICY=OFF, DEFAULT_DATABASE=[%DBNAME%]"
	sqlcmd -S .\SQLExpress -U sa -P $2 -i dbe_init_mssql.sql
fi
