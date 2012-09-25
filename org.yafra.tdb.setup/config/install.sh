#!/usr/bin/env bash
#-------------------------------------------------------------------------------
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
#-------------------------------------------------------------------------------
#
# Author:       Administrator
#
# Purpose:      install tdb classic on posix based systems (including cygwin)
#-------------------------------------------------------------------------------

#
# make sure the generic profile is loaded and you have superuser/ROOT permissions!!
#
if [ ! -d $SYSADM/defaults ]
then
	echo "Environment not loaded - install first !"
	exit
fi

TDBINSTDIR=/usr/local
if [ ! -d $TDBINSTDIR ]
then
	echo "deployment directory not available - create first !"
	exit
fi
BINDIR=$TDBINSTDIR/bin
ETCDIR=$TDBINSTDIR/etc
LIBSDIR=$TDBINSTDIR/lib
GUIINSTALL=$ETCDIR/tdb
APPDIR=$TDBINSTDIR/apps

TDBCONFIG=$TDBSETUP/config
SYSTEMTYPE=`uname -s`

# check if all or server or client
# arguments are: 1: client, server, all
if [ -z "$1" ]; then
        echo "Please specify 1 parameter: client, server or all - and optional 2nd parameter db type"
        exit
fi

# create database
if [ -n "$2" ]; then
	# this works fine on unix with perl
	if [ "$2" = "mysql" ]; then
		echo "installing mysql database"
		cd $TDBDB/mysql
		$TDBDB/mysql/generate.sh tdbadmin tdbadmin
	fi
	if [ "$2" = "oracle" ]; then
		echo "installing oracle database"
		cd $TDBDB/oracle
		$TDBDB/oracle/generate.sh tdbadmin tdbadmin
	fi
	if [ "$2" = "mssql" ]; then
		echo "installing mssql database"
		cd $TDBDB/mssql
		$TDBDB/mssql/generate.sh tdbadmin tdbadmin
	fi
fi

#create dirs
test -d $BINDIR || mkdir $BINDIR
test -d $ETCDIR || mkdir $ETCDIR
test -d $LIBSDIR || mkdir $LIBSDIR
test -d $APPDIR || mkdir $APPDIR
test -d $APPDIR/tdbmono || mkdir $APPDIR/tdbmono
test -d $APPDIR/tdbdbadmin || mkdir $APPDIR/tdbdbadmin
test -d $APPDIR/tdbpyadmin || mkdir $APPDIR/tdbpyadmin

# installing programs
echo "installing tdb with option $1 and destination directory $TDBINSTDIR"
echo "copy generic configs, binaries and libs"
cp $YAFRAEXE/* $BINDIR

#copy csharp tdbadmin app
cp $WORKNODE/apps/tdbmono/* $APPDIR/tdbmono/.

#copy tdb db setup app
cp $WORKNODE/apps/tdbdbadmin/* $APPDIR/tdbdbadmin/.

#copy python db query app
cp $WORKNODE/apps/tdbpyadmin/* $APPDIR/tdbpyadmin/.

if [ "$SYSTEMTYPE" = "HP-UX" ]; then
	GET_OSTYPE=ps_unix
fi

if [ "$SYSTEMTYPE" = "Linux" ]; then
	cp -P $WORKNODE/libs/lib* $LIBSDIR
	ldconfig
	cp $TDBCONFIG/linux/mpgui.pro $ETCDIR
fi

if [[ "$SYSTEMTYPE" == *CYGWIN* ]]; then
	cp -P $WORKNODE/libs/lib* $LIBSDIR
	cp $TDBCONFIG/linux/mpgui.pro $ETCDIR
fi


if [ ["$1"] = ["server"] -o ["$1"] = ["all"] ]; then
	echo "install server $1"
	if [ "$SYSTEMTYPE" = "HP-UX" ]; then
		# update service file
		$TDBSETUP/config/hpux/update-services.pl
		# start servers
		$BINDIR/mpdbi -daemon
		$BINDIR/psserver -daemon
		$BINDIR/mpnet -daemon
	fi

	if [ "$SYSTEMTYPE" = "Linux" ]; then
		# update service file
		$TDBSETUP/config/linux/update-services.pl
		# start servers
		$BINDIR/mpdbi -daemon
		$BINDIR/psserver -daemon
		$BINDIR/mpnet -daemon
	fi

	if [[ "$SYSTEMTYPE" == *CYGWIN* ]]; then
		# update service file
		$TDBSETUP/config/linux/update-services.pl
		# start servers
		$BINDIR/mpdbi -daemon
		$BINDIR/psserver -daemon
		$BINDIR/mpnet -daemon
	fi
fi

if [ ["$1"] = ["client"] -o ["$1"] = ["all"] ]; then
	echo install client $1
	test -d $GUIINSTALL || mkdir $GUIINSTALL
	if [ "$SYSTEMTYPE" = "HP-UX" ]; then
		echo "copy client files"
		cp $TDBCONFIG/hpux/MPgui /usr/X11/app-defaults
		cp $TDBCONFIG/hpux/errors $GUIINSTALL
		cp $TDBCONFIG/hpux/labels* $GUIINSTALL
	fi

	if [ "$SYSTEMTYPE" = "Linux" ]; then
		echo "copy client files"
		cp $TDBCONFIG/linux/MPgui /etc/X11/app-defaults
		cp $TDBCONFIG/linux/errors $GUIINSTALL
		cp $TDBCONFIG/linux/labels* $GUIINSTALL
	fi

	if [[ "$SYSTEMTYPE" == *CYGWIN* ]]; then
		echo "copy client files"
		cp $TDBCONFIG/linux/MPgui /etc/X11/app-defaults
		cp $TDBCONFIG/linux/errors $GUIINSTALL
		cp $TDBCONFIG/linux/labels* $GUIINSTALL
	fi
	cp $TDBCONFIG/common/* $GUIINSTALL
	cp $TDBCONFIG/license.txt $GUIINSTALL
fi

exit