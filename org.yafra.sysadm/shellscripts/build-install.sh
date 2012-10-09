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
	. etc/yafra-profile.sh
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
DBSERVER=localhost
echo "-> start auto build with basenode $BASENODE and version $YAFRAVER.$YAFRAREL" > $LOGFILE
echo "settings:" >> $LOGFILE
echo "TOMEE: $TOMEE" >> $LOGFILE
echo "DBSERVER: $DBSERVER" >> $LOGFILE
echo "TIMESTAMP: $TIMESTAMP" >> $LOGFILE
echo "LOGFILE: $LOGFILE" >> $LOGFILE


DESTDIR=/usr/local
if [ ! -d $DESTDIR ]
then
	echo "error: deployment directory not available, exit now - create first !" >> $LOGFILE
	exit
fi
BINDIR=$DESTDIR/bin
ETCDIR=$DESTDIR/etc
LIBSDIR=$DESTDIR/lib
GUIINSTALL=$ETCDIR/tdb
APPDIR=$DESTDIR/apps
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

if [ "$DBSERVER" = "localhost" ]; then
	echo "stop server processes"
	$BINDIR/yafra-prgkill.sh mpdbi
	$BINDIR/yafra-prgkill.sh mpnet
	$BINDIR/yafra-prgkill.sh psserver
	$BINDIR/stop-servers.sh
	rm -rf $TOMEE/webapps/org.yafra*
fi

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

# create database YAFRA
# create database TDB
# this works fine on unix with perl
if [ "$1" = "setupdb" ]; then
	if [ "$2" = "mysql" ]; then
		echo "installing mysql database"
		cd $TDBDB/mysql
		$TDBDB/mysql/generate.sh tdbadmin $SAPWD
		cd $YAFRADB
		./generate.sh mysql $SAPWD
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
