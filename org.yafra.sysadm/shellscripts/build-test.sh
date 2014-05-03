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
#
# Args:           1 (optional) servername
#
# change TOMEE to your local installation
#-------------------------------------------------------------------------------

#
# make sure the generic profile is loaded and you have enough permissions!!
#
if [ ! -d $SYSADM/defaults ]
then
	echo "Environment not loaded - install first !"
	exit
fi

# database server
DBSERVER="localhost"
if [ -n "$1" ]; then
	DBSERVER="$1"
fi

#
# settings
#
TIMESTAMP="$(date +%y%m%d)"
TOMEE=$JAVANODE/org.yafra.server.ejb-ear/target/apache-tomee
BINDIR=$YAFRAEXE
APPDIR=$WORKNODE/apps
echo "============================================================"
echo "-> start test build with basenode $BASENODE"
echo "settings:" 
echo "TOMEE: $TOMEE"
echo "DBSERVER: $DBSERVER"
echo "TIMESTAMP: $TIMESTAMP"
echo "Version $YAFRAVER.$YAFRAREL"
echo "============================================================"

cd $WORKNODE

if [ "$OSHARED" = "1" ]; then
	sudo cp -P $WORKNODE/libs/* /usr/local/lib
	sudo ldconfig
fi

#
# start yafra test first as this creates the tables if they are still missing
echo "============================================================"
echo " TEST CASE 1: Yafra db access with data operation and test data fill"
echo "============================================================"
java -classpath $YAFRACLASSES -jar $WORKNODE/classes/org.yafra.tests.serverdirectclient.jar

#
# start servers first
#
if [ "$DBSERVER" = "localhost" ]; then
	echo "============================================================"
	echo " TEST CASE 1b: starting server processes (daemons/services or JEE)"
	echo "============================================================"
	sudo $YAFRABIN/yafra-prgkill.sh mpdbi
	sudo $YAFRABIN/yafra-prgkill.sh mpnet
	sudo $YAFRABIN/yafra-prgkill.sh psserver
	$BINDIR/mpdbi -daemon
	$BINDIR/psserver -daemon
	$BINDIR/mpnet -daemon
	sudo $SYSADM/shellscripts/server-tomee.sh stop $TOMEE
	sudo rm -rf $TOMEE/webapps/org.yafra*
	sudo cp $WORKNODE/classes/org.yafra.wicket.war $TOMEE/webapps
	sudo cp $WORKNODE/classes/org.yafra.server.jee.war $TOMEE/webapps
	sudo cp $WORKNODE/classes/org.yafra.gwt.admin.war $TOMEE/webapps
	sudo $SYSADM/shellscripts/server-tomee.sh start $TOMEE
# TODO: maven - 1) call mvn tomee / tomcat 2) dont start tomee but copy ear 3rd party libs to tomee/lib and the ejb.jar to apps 3) start openejb standalone with tomee/bin/tomee.sh start
fi


#
# test yafra components
#
echo "============================================================"
echo " TEST CASE 2: java utils, ejb, ws"
echo "============================================================"
java -classpath $YAFRACLASSES -jar $WORKNODE/classes/org.yafra.tests.utils.jar
#java -jar $WORKNODE/classes/org.yafra.tests.serverejb3.jar
#java -jar $WORKNODE/classes/org.yafra.tests.wsclient.jar

#run test server, utils, wsclient, rest, url getter of tomee installed apps
echo "============================================================"
echo " TEST CASE 3: yafra python test read data from db - reading db"
echo "============================================================"
python $APPDIR/yafrapadmin/Main.py

#
# test tdb components
#
#get releases of binaries
echo "============================================================"
echo " TEST CASE 4: tdb - get information on binaries"
echo "============================================================"
ldd $BINDIR/mpdbi
ldd $BINDIR/mpgui
ldd $BINDIR/mpnet
$BINDIR/pswhat -i $BINDIR/pswhat
$BINDIR/pswhat $BINDIR/mpdbi
$BINDIR/pswhat $BINDIR/mpgui
#start tests now
echo "============================================================"
echo " TEST CASE 5: ansi c common libraries test"
echo "============================================================"
$BINDIR/pschar
$BINDIR/pslog
$BINDIR/psdatetime -d 01.01.1013 -t 12.30
$BINDIR/psdatetime -d 01.02.2013 -t 12.30
$BINDIR/psdatetime -d 01.03.2113 -t 12.30
$BINDIR/psdatetime -d 01.04.3013 -t 12.30
$BINDIR/psclientcons $DBSERVER
echo "============================================================"
echo " TEST CASE 6: tdb classic test db access and structure - reading db"
echo "============================================================"
$BINDIR/mpstruct
$BINDIR/mptest -n $DBSERVER
echo "============================================================"
echo " TEST CASE 7: tdb .net/mono csharp test - reading db"
echo "============================================================"
mono $APPDIR/tdbmono/tdbtest.exe tdbadmin $DBSERVER MySQL
echo "============================================================"
echo " TEST CASE 8: tdb perl DBI test - reading db"
echo "============================================================"
perl $APPDIR/tdbdbadmin/tdb-testdbi.pl tdbadmin $DBSERVER mysql
