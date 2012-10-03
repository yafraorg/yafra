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
	echo "missing arguments 1 dev/rel 2 mysql/derby/mssql/oracle"
	exit
fi

#
echo "apache cayenne config file"
CAYCONFIG=src/org.yafra.dbNode.driver.xml
echo "CAYCONFIG: $CAYCONFIG"
#this is the development version - release versions are copied later
CAYSRCCONFIG=src/org.yafra.mysqlNode.driver.xml
echo "CAYSRCCONFIG: $CAYSRCCONFIG - TODO make sure you changed this file according to your environment!"
YAFRACORE=$BASENODE/org.yafra.server.core

# database server
DBSERVER="localhost"
if [ -n "$3" ]; then
	DBSERVER="$3"
fi

# database root/dba password
SAPWD="yafra"
if [ -n "$4" ]; then
	SAPWD="$4"
fi

# print settings
echo "create database in mode $1, dbtype $2, server $DBSERVER, dbapwd $SAPWD"

# create default cayenne config - use CAYCONFIG to set to your default config
if [ ! -f $YAFRACORE/$CAYCONFIG ]
then
cp $YAFRACORE/$CAYSRCCONFIG $YAFRACORE/$CAYCONFIG
fi

# create database YAFRA
cd $JAVANODE/org.yafra.tests.serverdirectclient
if [ "$1" = "dev" ]; then
	ant installdb
else
	if [ "$2" = "mysql" ]; then
		echo "using the mysql localhost database"
		cp $YAFRACORE/src/org.yafra.release.mysql.Node.driver.xml $YAFRACORE/$CAYCONFIG
		ant installmysql
	fi
	if [ "$2" = "derby" ]; then
		echo "using the derby localhost database"
		cp $YAFRACORE/src/org.yafra.release.derby.Node.driver.xml $YAFRACORE/$CAYCONFIG
		ant installderby
	fi
	if [ "$2" = "oracle" ]; then
		echo "using the oracle localhost database"
		cp $YAFRACORE/src/org.yafra.release.oracle.Node.driver.xml $YAFRACORE/$CAYCONFIG
		ant installora
	fi
	if [ "$2" = "mssql" ]; then
		echo "using the mssql localhost database"
		cp $YAFRACORE/src/org.yafra.release.mssql.Node.driver.xml $YAFRACORE/$CAYCONFIG
		ant installmssql
	fi
fi
cd -


# create database TDB
# this works fine on unix with perl
if [ "$1" = "rel" ]; then
	if [ "$2" = "mysql" ]; then
		echo "installing mysql database"
		cd $TDBDB/mysql
		$TDBDB/mysql/generate.sh tdbadmin $SAPWD
	fi
	if [ "$2" = "oracle" ]; then
		echo "installing oracle database"
		cd $TDBDB/oracle
		$TDBDB/oracle/generate.bat tdbadmin $SAPWD
	fi
	if [ "$2" = "mssql" ]; then
		echo "installing mssql database"
		cd $TDBDB/mssql
		$TDBDB/mssql/generate.bat $SAPWD yafra
	fi
fi