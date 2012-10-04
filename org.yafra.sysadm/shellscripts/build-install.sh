#!/bin/sh
#-------------------------------------------------------------------------------
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
#-------------------------------------------------------------------------------
#
# Author:       Administrator
#
# Purpose:      build step 6: install build with db init
#                    This script installs the yafra distribution
#                    and is part of the build system
#-------------------------------------------------------------------------------

#
# make sure the generic profile is loaded and you have enough permissions!!
#
if [ ! -d $SYSADM/defaults ]
then
	. ../defaults/profile.sh
fi
if [ ! -d $SYSADM/defaults ]
then
	echo "Environment not loaded - install first !"
	exit
fi

#
# settings
#
TIMESTAMP="$(date +%y%m%d)"
LOGFILE=$WORKNODE/YAFRA-install-$TIMESTAMP.log
TOMEE=/work/apache-tomee-webprofile-1.0.0
DBSERVER=webdevelop
echo "-> start auto build with basenode $BASENODE and version $YAFRAVER.$YAFRAREL" > $LOGFILE
echo "settings:" >> $LOGFILE
echo "TOMEE: $TOMEE" >> $LOGFILE
echo "DBSERVER: $DBSERVER" >> $LOGFILE
echo "TIMESTAMP: $TIMESTAMP" >> $LOGFILE
echo "LOGFILE: $LOGFILE" >> $LOGFILE


TDBINSTDIR=/usr/local
if [ ! -d $TDBINSTDIR ]
then
	echo "error: deployment directory not available, exit now - create first !" >> $LOGFILE
	exit
fi
BINDIR=$TDBINSTDIR/bin
ETCDIR=$TDBINSTDIR/etc
LIBSDIR=$TDBINSTDIR/lib
GUIINSTALL=$ETCDIR/tdb
APPDIR=$TDBINSTDIR/apps
#create dirs
test -d $BINDIR || mkdir $BINDIR  >> $LOGFILE 2>&1
test -d $ETCDIR || mkdir $ETCDIR  >> $LOGFILE 2>&1
test -d $LIBSDIR || mkdir $LIBSDIR  >> $LOGFILE 2>&1
test -d $APPDIR || mkdir $APPDIR  >> $LOGFILE 2>&1
test -d $APPDIR/yafrapadmin || mkdir $APPDIR/yafrapadmin  >> $LOGFILE 2>&1

#
# copy setup scripts first
#
echo "installing setup scripts"
cp bin/*.sh $BINDIR

#
# stop all running servers and clean up runtime environment
#
echo "stop server processes"
$BINDIR/yafra-prgkill.sh mpdbi
$BINDIR/yafra-prgkill.sh mpnet
$BINDIR/yafra-prgkill.sh psserver
$BINDIR/stop-servers.sh
rm -rf $TOMEE/webapps/org.yafra*

#
# install all binaries and apps
#
echo "install binaries and apps"
cp bin/* $BINDIR
cp -P lib/* $LIBSDIR
#python admin
cp $WORKNODE/apps/yafrapadmin/* $APPDIR/yafrapadmin/




#war's
cp $WORKNODE/classes/org.yafra.wicket.war $TOMEE/webapps
cp $WORKNODE/classes/org.yafra.server.jee.war $TOMEE/webapps
# create database
if [ -n "$1" ]; then
	#create yafra db and run tests
	cd $JAVANODE/org.yafra.tests.serverdirectclient
	if [ "$1" = "mysql" ]; then
		echo "installing mysql database"
		cd $TDBDB/mysql
		$TDBDB/mysql/generate.sh tdbadmin $SAPWD
		ant installmysql
	fi
	if [ "$1" = "derby" ]; then
		ant installdbderby >> $LOGFILE 2>&1
	fi
	if [ "$1" = "oracle" ]; then
		echo "installing oracle database"
		cd $TDBDB/oracle
		$TDBDB/oracle/generate.bat tdbadmin $SAPWD
		ant installdbora >> $LOGFILE 2>&1
	fi
	if [ "$1" = "mssql" ]; then
		echo "installing mssql database"
		cd $TDBDB/mssql
		$TDBDB/mssql/generate.bat $SAPWD yafra
		ant installdbmssql >> $LOGFILE 2>&1
	fi
	cd - >> $LOGFILE 2>&1
fi
#start servers now
$SYSADM/shellscripts/start-tomcat.sh >> $LOGFILE 2>&1

#
# install tdb components
#
echo "install travelDB classic system"
#create tdb db run tdb test
# create database
if [ -n "$1" ]
	then $TDBSETUP/config/install.sh all $1 >> $LOGFILE 2>&1
	else $TDBSETUP/config/install.sh all >> $LOGFILE 2>&1
fi


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
