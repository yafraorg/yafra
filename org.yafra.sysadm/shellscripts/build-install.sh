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
# Purpose:      install auto build with db init
#-------------------------------------------------------------------------------

#
# make sure the generic profile is loaded and you have enough permissions!!
#
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
# stop all running servers and clean up runtime environment
#
echo "stop server processes:" >> $LOGFILE
$SYSADM/defaults/scripts/psprgkill mpdbi  >> $LOGFILE 2>&1
$SYSADM/defaults/scripts/psprgkill mpnet  >> $LOGFILE 2>&1
$SYSADM/defaults/scripts/psprgkill psserver  >> $LOGFILE 2>&1
$SYSADM/shellscripts/stop-servers.sh >> $LOGFILE 2>&1
rm -rf $TOMEE/webapps/org.yafra* >> $LOGFILE 2>&1

#
# make worknode executables "rwx"
#
chmod 755 $WORKNODE/bin/*
chmod 755 $WORKNODE/classes/*tests*
chmod 755 $WORKNODE/apps/tdbmono/*.exe
chmod 755 $WORKNODE/apps/tdbdbadmin/*.pl
chmod 755 $WORKNODE/apps/tdbpyadmin/main.py
chmod 755 $WORKNODE/apps/yafrapadmin/Main.py

#
# install yafra components
#
echo "install yafra java system" >> $LOGFILE
#python admin
cp $WORKNODE/apps/yafrapadmin/* $APPDIR/yafrapadmin/ >> $LOGFILE
#war's
cp $WORKNODE/classes/org.yafra.wicket.war $TOMEE/webapps >> $LOGFILE 2>&1
cp $WORKNODE/classes/org.yafra.server.jee.war $TOMEE/webapps >> $LOGFILE 2>&1
# create database
if [ -n "$1" ]; then
	#create yafra db and run tests
	cd $JAVANODE/org.yafra.tests.serverdirectclient >> $LOGFILE 2>&1
	if [ "$1" = "mysql" ]; then
		ant installdb >> $LOGFILE 2>&1
	fi
	if [ "$1" = "derby" ]; then
		ant installdbderby >> $LOGFILE 2>&1
	fi
	if [ "$1" = "oracle" ]; then
		ant installdbora >> $LOGFILE 2>&1
	fi
	if [ "$1" = "mssql" ]; then
		ant installdbmssql >> $LOGFILE 2>&1
	fi
	cd - >> $LOGFILE 2>&1
fi
#start servers now
$SYSADM/shellscripts/start-tomcat.sh >> $LOGFILE 2>&1

#
# install tdb components
#
echo "install travelDB classic system" >> $LOGFILE
#create tdb db run tdb test
# create database
if [ -n "$1" ]
	then $TDBSETUP/config/install.sh all $1 >> $LOGFILE 2>&1
	else $TDBSETUP/config/install.sh all >> $LOGFILE 2>&1
fi


