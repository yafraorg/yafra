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
# Purpose:      test build
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
LOGFILE=$WORKNODE/YAFRA-testrun-$TIMESTAMP.log
TOMEE=/work/apache-tomee-webprofile-1.0.0
DBSERVER=webdevelop
BINDIR=/usr/local/bin
APPDIR=/usr/local/app
echo "-> start test build with basenode $BASENODE" > $LOGFILE
echo "settings:" >> $LOGFILE
echo "TOMEE: $TOMEE" >> $LOGFILE
echo "DBSERVER: $DBSERVER" >> $LOGFILE
echo "TIMESTAMP: $TIMESTAMP" >> $LOGFILE
echo "LOGFILE: $LOGFILE" >> $LOGFILE

#
# test yafra components
#
echo "test yafra java system at version $YAFRAVER.$YAFRAREL" >> $LOGFILE
if [ -n "$1" ]; then
	cd $JAVANODE/org.yafra.tests.serverdirectclient >> $LOGFILE 2>&1
	ant >> $LOGFILE 2>&1
	cd - >> $LOGFILE 2>&1
fi

#run test server, utils, wsclient, rest, url getter of tomee installed apps
python $APPDIR/yafrapadmin/Main.py >>$LOGFILE 2>&1

#
# test tdb components
#
echo "test travelDB classic system" >> $LOGFILE
#get releases of binaries
ldd $BINDIR/mpdbi >>$LOGFILE 2>&1
ldd $BINDIR/mpgui >>$LOGFILE 2>&1
ldd $BINDIR/mpnet >>$LOGFILE 2>&1
$BINDIR/pswhat -i $EXEDIR/mpdbi >>$LOGFILE 2>&1
#start tests now
$BINDIR/psclientcons localhost >> $LOGFILE 2>&1
$BINDIR/mpstruct >> $LOGFILE 2>&1
$BINDIR/mptest -n $DBSERVER >> $LOGFILE 2>&1
$APPDIR/tdbmono/tdbtest.exe tdbadmin $DBSERVER MySQL >> $LOGFILE 2>&1
perl $APPDIR/tdbdbadmin/tdb-testdbi.pl tdbadmin $DBSERVER mysql >> $LOGFILE 2>&1



