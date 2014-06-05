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
# Author:       yafra
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

echo "-> start yafra installation"

#
# settings
#
TIMESTAMP="$(date +%y%m%d)"
LOGFILE=$WORKNODE/YAFRA-install-$TIMESTAMP.log
TOMEE=/work/tomee
DBSERVER=localhost
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
X11APPDEF=/etc/X11/app-defaults
#create dirs
test -d $BINDIR || mkdir $BINDIR
test -d $ETCDIR || mkdir $ETCDIR
test -d $LIBSDIR || mkdir $LIBSDIR
test -d $APPDIR || mkdir $APPDIR
test -d $GUIINSTALL || mkdir $GUIINSTALL

#
# copy setup scripts first
#
echo "installing setup scripts"
cp bin/*.sh $BINDIR

echo "make sure TomEE is installed in $TOMEE"
echo "is that the case ? (yes/no)"
read yesno
if [ "$yesno" = "no" ]; then
	exit 1
fi

#
# copy jar/war files
#

# yafra java core
cd $BASENODE/org.yafra.server.core/target
cp *.jar $APPDIR

# yafra java J2EE wicket and cxf
cd $BASENODE/org.yafra.server.jee/target
cp *.war $APPDIR
cd $BASENODE/org.yafra.server.jee
#mvn tomcat7:exec-war

# yafra java EJB3
cd $BASENODE/org.yafra.server.ejb/target
cp *client.jar $APPDIR
cd $BASENODE/org.yafra.server.ejb-war/target
cp *.war $APPDIR
cd $BASENODE/org.yafra.server.ejb-war
#mvn tomee:build
#mvn tomee:start

# database server
DBSERVER="localhost"
echo "your database and application server is set to $DBSERVER"
echo "is that correct ? (yes/no)"
read yesno
if [ "$yesno" = "no" ]; then
	echo "enter the hostname now:"
	read hostname
	if [ -z "$hostname" ]; then
		echo "you need to enter a hostname - start script again"
		exit 1
	else
		DBSERVER=$hostname
	fi
fi

#
# stop all running servers and clean up runtime environment
#

if [ "$DBSERVER" = "localhost" ]; then
	# database root/dba password
	SAPWD="yafra"
	echo "your database admin password is set to $SAPWD"
	echo "is that correct ? (yes/no)"
	read yesno
	if [ "$yesno" = "no" ]; then
		echo "enter the password now:"
		read dbpwd
		if [ -z "$dbpwd" ]; then
			echo "you need to enter a password - start script again"
			exit 1
		else
			SAPWD=$dbpwd
		fi
	fi
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
cp -r apps/* $APPDIR
cp etc/mpgui.pro $ETCDIR
cp etc/tdb/* $GUIINSTALL
cp etc/tdb/MPgui $X11APPDEF

if [ "$DBSERVER" = "localhost" ]; then
	perl bin/tdb-setup-services.pl
	#war's
	#start servers now
	$BINDIR/start-tomcat.sh
	$BINDIR/mpdbi -daemon
	$BINDIR/mpnet -daemon
	$BINDIR/psserver -daemon

	# create database YAFRA
	# create database TDB
	# this works fine on unix with perl
	echo "installing database"
	cd etc/yafradb
	generate.sh yafradmin $SAPWD
	cd ../traveldb
	generate.sh tdbadmin $SAPWD
	cd ../..
fi

echo "done"
