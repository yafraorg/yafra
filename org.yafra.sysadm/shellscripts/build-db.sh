#!/bin/sh
#-------------------------------------------------------------------------------------------
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
#-------------------------------------------------------------------------------------------
# Author:        yafra
#
# Purpose:      build step 2: init database
# Arguments: 1: dev/rel 2: mysql/oracle/derby/mssql 3: servername 4: sapwd
#-------------------------------------------------------------------------------------------

#
# make sure the generic profile is loaded - run as user !!
#
if [ ! -d $SYSADM/defaults ]
then
	echo "Environment not loaded - install first !"
	exit
fi
if [ -z "$2" ]; then
	echo "missing arguments 1 dev/rel 2 mysql/derby/mssql/oracle 3 host or setupdb 4 sa/dba pwd"
	exit
fi

#
echo "apache cayenne config file"
CAYCONFIG=src/main/resources/cayenne-org_yafra.xml
echo "CAYCONFIG: $CAYCONFIG"
#this is the development version - release versions are copied later
CAYSRCCONFIG=src/main/resources/cayenne-org_yafra-localmysql.xml
echo "CAYSRCCONFIG: $CAYSRCCONFIG - TODO make sure you changed this file according to your environment!"
YAFRACORE=$BASENODE/org.yafra.server.core

# database server
DBSERVER="localhost"
if [ -n "$3" ]; then
	if [ "$3" != "setupdb" ]; then
		DBSERVER="$3"
	fi
fi

# database root/dba password
SAPWD="yafra"
if [ -n "$4" ]; then
	SAPWD="$4"
fi

# print settings
echo "create database in mode $1, dbtype $2, server $DBSERVER, dbapwd $SAPWD"

#if [ ! -f $YAFRACORE/$CAYCONFIG ]; then
#cp $YAFRACORE/$CAYSRCCONFIG $YAFRACORE/$CAYCONFIG
#fi

# create database YAFRA
cd $JAVANODE/org.yafra.tests.serverdirectclient
if [ "$1" = "dev" ]; then
	if [ "$2" = "mysql" ]; then
		echo "using the mysql $DBSERVER database"
		#cp $YAFRACORE/src/main/resources/cayenne-org_yafra-localmysql.xml $YAFRACORE/$CAYCONFIG
	fi
	if [ "$2" = "derby" ]; then
		echo "using the derby $DBSERVER database"
		cp $YAFRACORE/src/main/resources/cayenne-org_yafra-localderby.xml $YAFRACORE/$CAYCONFIG
	fi
	if [ "$2" = "oracle" ]; then
		echo "using the oracle $DBSERVER database"
		cp $YAFRACORE/src/main/resources/cayenne-org_yafra-localoracle.xml $YAFRACORE/$CAYCONFIG
	fi
	if [ "$2" = "mssql" ]; then
		echo "using the mssql $DBSERVER database"
		cp $YAFRACORE/src/main/resources/cayenne-org_yafra-localmssql.xml $YAFRACORE/$CAYCONFIG
	fi
	if [ "$DBSERVER" != "localhost" ]; then
		sed -i "s/localhost/$DBSERVER/g" $YAFRACORE/$CAYCONFIG
	fi
else
	# copy a default config and later the correct one according $2
	cp $YAFRACORE/$CAYSRCCONFIG $YAFRACORE/$CAYCONFIG
	if [ "$2" = "mysql" ]; then
		echo "using the mysql $DBSERVER database"
		cp $YAFRACORE/src/main/resources/cayenne-org_yafra-localmysql.xml $YAFRACORE/$CAYCONFIG
	fi
	if [ "$2" = "derby" ]; then
		echo "using the derby $DBSERVER database"
		cp $YAFRACORE/src/main/resources/cayenne-org_yafra-localderby.xml $YAFRACORE/$CAYCONFIG
	fi
	if [ "$2" = "oracle" ]; then
		echo "using the oracle $DBSERVER database"
		cp $YAFRACORE/src/main/resources/cayenne-org_yafra-localoracle.xml $YAFRACORE/$CAYCONFIG
	fi
	if [ "$2" = "mssql" ]; then
		echo "using the mssql $DBSERVER database"
		cp $YAFRACORE/src/main/resources/cayenne-org_yafra-localmssql.xml $YAFRACORE/$CAYCONFIG
	fi
fi

cd -


# create database TDB and YafraDB as part of setupdb command
# this works fine on unix with perl
if [ "$3" = "setupdb" ]; then
	cd $JAVANODE/org.yafra.utils
	mvn install
	cd $JAVANODE/org.yafra.server.core
	mvn install
	cd $SYSADM/databases/yafradb
	./generate.sh $2 $SAPWD
	if [ "$2" = "mysql" ]; then
		echo "installing mysql database"
		cd $TDBDB/mysql
		$TDBDB/mysql/convert.sh
		$TDBDB/mysql/generate.sh tdbadmin $SAPWD
		cd $JAVANODE/org.yafra.tests.serverdirectclient
		mvn install -P installmysql
	fi
	if [ "$2" = "oracle" ]; then
		echo "installing oracle database"
		cd $TDBDB/oracle
		$TDBDB/oracle/convert.sh
		$TDBDB/oracle/generate.bat tdbadmin $SAPWD
		cd $JAVANODE/org.yafra.tests.serverdirectclient
		mvn install -P installora
	fi
	if [ "$2" = "mssql" ]; then
		echo "installing mssql database"
		cd $TDBDB/mssql
		$TDBDB/mssql/convert.sh
		$TDBDB/mssql/generate.bat $SAPWD yafra
		cd $JAVANODE/org.yafra.tests.serverdirectclient
		mvn install -P installmssql
	fi
	if [ "$2" = "derby" ]; then
		echo "installing derby database"
		mvn install -P installderby
	fi
fi
