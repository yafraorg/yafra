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
BINDIR=$YAFRAEXE
APPDIR=$WORKNODE/apps
WWWDIR=/var/www/html/yafra
test -d $WWWDIR || mkdir $WWWDIR
echo "============================================================"
echo "-> start test build with basenode $BASENODE"
echo "settings:" 
echo "DBSERVER: $DBSERVER"
echo "WWWDIR: $WWWDIR (used for php, perl and python flask)"
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
java -jar $WORKNODE/bin/serverdirectclient-1.0-jar-with-dependencies.jar

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
	cd $JAVANODE/org.yafra.server.ejb-war
	mvn tomee:stop
	cd -
	$YAFRABIN/yafra-prgkill.sh jee-1.0-war-exec.jar
	$BINDIR/mpdbi -daemon
	$BINDIR/psserver -daemon
	$BINDIR/mpnet -daemon
	java -jar $BINDIR/jee-1.0-war-exec.jar -httpPort 8081 &
	cd $JAVANODE/org.yafra.server.ejb-war
	mvn tomee:start
	cd -
fi


#
# test yafra components
#
#run java tests
echo "============================================================"
echo " TEST CASE YAFRA 1: java utils, ejb, ws"
echo "============================================================"
java -jar $WORKNODE/bin/tests-utils-1.0-jar-with-dependencies.jar
java -jar $WORKNODE/bin/tests-ejb3-1.0-jar-with-dependencies.jar $DBSERVER

#run test server, utils, wsclient, rest, url getter of tomee installed apps
echo "============================================================"
echo " TEST CASE YAFRA 2: yafra python test read data from db - reading db"
echo "============================================================"
echo "python db-api case"
python $APPDIR/yafrapython/db-api/Main.py
echo "python sqlalchemy case"
python $APPDIR/yafrapython/db-api/Main.py
echo "python mysql-connector case"
python $APPDIR/yafrapython/mysql-connector/Main.py
#TODO install and produce link to python flask

#run test server, utils, wsclient, rest, url getter of tomee installed apps
echo "============================================================"
echo " TEST CASE YAFRA 3: yafra php slimframework"
echo "============================================================"
cp -r $APPDIR/yafraphp/* $WWWDIR/
cd $WWWDIR
php /usr/local/bin/composer.phar install
echo "php app installed at $WWWDIR"
echo "use http://localhost/yafra/v1 to access the php app"

echo "============================================================"
echo " TEST CASE YAFRA 4: yafra perl catalyst"
echo "============================================================"
echo "TODO: to be created"

echo "============================================================"
echo " TEST CASE YAFRA 5: yafra ansi c common libraries test"
echo "============================================================"
$BINDIR/pschar
$BINDIR/pslog
$BINDIR/psdatetime -d 01.01.1013 -t 12.30
$BINDIR/psdatetime -d 01.02.2013 -t 12.30
$BINDIR/psdatetime -d 01.03.2113 -t 12.30
$BINDIR/psdatetime -d 01.04.3013 -t 12.30
$BINDIR/psclientcons $DBSERVER

#
# test tdb components
#
#get releases of binaries
echo "============================================================"
echo " TEST CASE TDB 1: tdb - get information on binaries"
echo "============================================================"
ldd $BINDIR/mpdbi
ldd $BINDIR/mpgui
ldd $BINDIR/mpnet
$BINDIR/pswhat -i $BINDIR/pswhat
$BINDIR/pswhat $BINDIR/mpdbi
$BINDIR/pswhat $BINDIR/mpgui
#start tests now
echo "============================================================"
echo " TEST CASE TDB 2: tdb classic test db access and structure - reading db"
echo "============================================================"
$BINDIR/mpstruct
$BINDIR/mptest -n $DBSERVER
echo "============================================================"
echo " TEST CASE TDB 3: tdb .net/mono csharp test - reading db"
echo "============================================================"
mono $APPDIR/tdbmono/tdbtest.exe tdbadmin $DBSERVER MySQL
echo "============================================================"
echo " TEST CASE TDB 4: tdb perl DBI test - reading db"
echo "============================================================"
perl $APPDIR/tdbdbadmin/tdb-testdbi.pl tdbadmin $DBSERVER mysql

