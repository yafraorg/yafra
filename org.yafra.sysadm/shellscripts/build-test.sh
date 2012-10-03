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
# Purpose:      build step 4: test build
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
TOMEE=/work/apache-tomee-webprofile-1.0.0
DBSERVER=localhost
BINDIR=$YAFRAEXE
APPDIR=$WORKNODE/apps
echo "-> start test build with basenode $BASENODE"
echo "settings:" 
echo "TOMEE: $TOMEE"
echo "DBSERVER: $DBSERVER"
echo "TIMESTAMP: $TIMESTAMP"

cd $WORKNODE

#
# test yafra components
#
echo "test yafra java system at version $YAFRAVER.$YAFRAREL"
java -classpath $YAFRACLASSES -jar $WORKNODE/classes/org.yafra.tests.utils.jar
java -classpath $YAFRACLASSES -jar $WORKNODE/classes/org.yafra.tests.serverdirectclient.jar
#java -jar $WORKNODE/classes/org.yafra.tests.serverejb3.jar
#java -jar $WORKNODE/classes/org.yafra.tests.wsclient.jar

#run test server, utils, wsclient, rest, url getter of tomee installed apps
python $APPDIR/yafrapadmin/Main.py

#
# test tdb components
#
echo "test travelDB classic system"
#get releases of binaries
ldd $BINDIR/mpdbi
ldd $BINDIR/mpgui
ldd $BINDIR/mpnet
$BINDIR/pswhat -i $EXEDIR/mpdbi
#start tests now
$BINDIR/pschar
$BINDIR/pslog
$BINDIR/psdatetime -d 01.01.2013 -t 12.30
$BINDIR/psclientcons localhost
$BINDIR/mpstruct
$BINDIR/mptest -n $DBSERVER
$APPDIR/tdbmono/tdbtest.exe tdbadmin $DBSERVER MySQL
perl $APPDIR/tdbdbadmin/tdb-testdbi.pl tdbadmin $DBSERVER mysql
