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
# Purpose:      build step 5: publish release, make release candidate
#               ready for distribution
#
# Arguments: 1) database (mysql, mssql, oracle, derby)
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
INSTDIR=$WORKNODE/yafra-dist
if [ ! -d $INSTDIR ]
then
	echo "error: main staging / publish directory not available: $INSTDIR - perform a full build first !"
	exit
fi
BINDIR=$INSTDIR/bin
ETCDIR=$INSTDIR/etc
LIBSDIR=$INSTDIR/lib
GUIINSTALL=$ETCDIR/tdb
APPDIR=$INSTDIR/apps
DBDIR=$ETCDIR/yafradb
TRAVELDBDIR=$ETCDIR/traveldb
TDBCONFIG=$TDBSETUP/config
echo "-> start publish with worknode $WORKNODE and target install directory $INSTDIR"
echo "TIMESTAMP: $TIMESTAMP"

#
# create staging environment
#
test -d $BINDIR || mkdir $BINDIR
test -d $ETCDIR || mkdir $ETCDIR
test -d $LIBSDIR || mkdir $LIBSDIR
test -d $GUIINSTALL || mkdir $GUIINSTALL
test -d $DBDIR || mkdir $DBDIR
test -d $TRAVELDBDIR || mkdir $TRAVELDBDIR
test -d $APPDIR || mkdir $APPDIR
test -d $APPDIR/yafrarcp || mkdir $APPDIR/yafrarcp
test -d $APPDIR/yafrapython || mkdir $APPDIR/yafrapython
test -d $APPDIR/tdbmono || mkdir $APPDIR/tdbmono
test -d $APPDIR/tdbdbadmin || mkdir $APPDIR/tdbdbadmin
test -d $APPDIR/tdbpyadmin || mkdir $APPDIR/tdbpyadmin

#
# copy files to staging area
#

# system administration files
cp $SYSADM/shellscripts/build-install.sh $INSTDIR/install.sh
cp $SYSADM/README-DISTRIBUTION.txt $INSTDIR
cp $BASENODE/LICENSE $INSTDIR
cp $BASENODE/NOTICE $INSTDIR
cp $SYSADM/defaults/profile.sh $ETCDIR/yafra-profile.sh
cp $SYSADM/shellscripts/server-tomcat.sh $BINDIR
cp $SYSADM/shellscripts/server-tomee.sh $BINDIR
cp $SYSADM/shellscripts/start-tomcat.sh $BINDIR
cp $SYSADM/shellscripts/stop-servers.sh $BINDIR
cp $SYSADM/defaults/scripts/yafra-prgkill.sh $BINDIR


# database generation files
# create yafradb and traveldb scripts and files
# create database TDB
# this works fine on unix with perl
if [ "$1" = "mysql" ]; then
	echo "installing mysql database"
	cd $TDBDB/mysql
	$TDBDB/mysql/convert.sh
	cp $TDBDB/mysql/* $TRAVELDBDIR/
fi
if [ "$1" = "oracle" ]; then
	echo "installing oracle database"
	cd $TDBDB/oracle
	$TDBDB/oracle/convert.sh
	cp $TDBDB/oracle/* $TRAVELDBDIR/
fi
if [ "$1" = "mssql" ]; then
	echo "installing mssql database"
	cd $TDBDB/mssql
	$TDBDB/mssql/convert.sh
	cp $TDBDB/mssql/* $TRAVELDBDIR/
fi
cp $SYSADM/databases/yafradb/* $DBDIR/

#
# YAFRA JAVA parts
cp $WORKNODE/apps/*.jar $LIBSDIR
cp $WORKNODE/apps/*.war $APPDIR
#python admin
cp -r $WORKNODE/apps/yafrapython/* $APPDIR/yafrapython/
#rcp
cp $WORKNODE/apps/yafrarcp/* $APPDIR/yafrarcp/

# TDB parts
cp $TDBCONFIG/linux/mpgui.pro $ETCDIR
cp $YAFRAEXE/* $BINDIR
cp -P $WORKNODE/libs/* $LIBSDIR
#copy csharp tdbadmin app
cp $WORKNODE/apps/tdbmono/* $APPDIR/tdbmono/.
#copy tdb db setup app
cp $WORKNODE/apps/tdbdbadmin/* $APPDIR/tdbdbadmin/.
#copy python db query app
cp $WORKNODE/apps/tdbpyadmin/* $APPDIR/tdbpyadmin/.
if [ "$PS_OS" = "ps_hpux" ]; then
	cp $TDBSETUP/config/hpux/update-services.pl $BINDIR/tdb-setup-services.pl
	cp $TDBCONFIG/hpux/MPgui $GUIINSTALL
	cp $TDBCONFIG/hpux/errors $GUIINSTALL
	cp $TDBCONFIG/hpux/labels* $GUIINSTALL
fi
if [ "$PS_OS" = "ps_linux" ]; then
	cp $TDBSETUP/config/linux/update-services.pl $BINDIR/tdb-setup-services.pl
	cp $TDBCONFIG/linux/MPgui $GUIINSTALL
	cp $TDBCONFIG/linux/errors $GUIINSTALL
	cp $TDBCONFIG/linux/labels* $GUIINSTALL
fi
if [ "$PS_OS" = "ps_cygwin" ]; then
	cp $TDBSETUP/config/linux/update-services.pl $BINDIR/tdb-setup-services.pl
	cp $TDBCONFIG/linux/MPgui $GUIINSTALL
	cp $TDBCONFIG/linux/errors $GUIINSTALL
	cp $TDBCONFIG/linux/labels* $GUIINSTALL
fi
cp $TDBCONFIG/common/* $GUIINSTALL
cp $TDBCONFIG/license.txt $GUIINSTALL


#
# set unix executable bit
#
chmod 755 $BINDIR/*
chmod 755 $APPDIR/tdbmono/*.exe
chmod 755 $APPDIR/tdbdbadmin/*.pl
chmod 755 $APPDIR/tdbpyadmin/main.py
chmod 755 $APPDIR/yafrapython/alchemy/Main.py
chmod 755 $APPDIR/yafrapython/db-api/Main.py
chmod 755 $INSTDIR/install.sh

#
# tar release
#
#create tar bundle for download
cd $WORKNODE
tar cvfz $WORKNODE/yafra-$PS_OS-$TIMESTAMP.tar.gz yafra-dist/
cd $YAFRACLASSES
tar cvfz $WORKNODE/yafra-3rdparty-jars-$PS_OS-$TIMESTAMP.tar.gz --exclude "*yafra*" *

