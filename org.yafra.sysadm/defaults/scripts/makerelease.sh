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
# Purpose:      make a release of exe's and libraries and tag source with it
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
# setup some variables
#
TIMESTAMP="$(date +%y%m%d)"
YAFRAREL="1.0.B1"
echo "-> settings for release $YAFRAREL with basenode $BASENODE on $TIMESTAMP"
#
echo "yafra java server core"
YAFRACORE=$JAVANODE/org.yafra.server.core
echo "YAFRACORE: $YAFRACORE"
#
echo "apache cayenne config file"
CAYCONFIG=src/org.yafra.dbNode.driver.xml
echo "CAYCONFIG: $CAYCONFIG"
CAYSRCCONFIG=src/org.yafra.mysqlNode.driver.xml
echo "CAYSRCCONFIG: $CAYSRCCONFIG - TODO make sure you changed this file according to your environment!"
#
echo "java classes for yafra project"
YAFRACLASSES=/work/classes
echo "YAFRACLASSES: $YAFRACLASSES"
#
echo "set c flags for compile"
export OSHARED=1
export ODEBUG=
echo "OSAHRED: $OSHARED and ODEBUG: $ODEBUG"


#
# delete working dirs and create a new one
#
echo "delete and create working directories"
if [ -d $WORKNODE ]
then
	rm $YAFRACLASSES/org.yafra*
	rm -rf $WORKNODE
fi
cd $SYSADM/defaults/scripts
./profile-create-dirs.sh

#
#CLASSIC/ANSIC
#
cd $YAFRALIBS
make clean
make all
cd psipc/testsuite/psserver
make clean
make all
cd ../psclient-cons
make clean
make all
cd ../fork
make clean
make all
cd $YAFRALIBS/pssys/testsuite/datetime
make clean
make all
cd ../logging
make clean
make all
cd ../chars
make clean
make all

#CLASSIC/ADDONS
cd $PSWHAT
make clean
make all
cd $PSEDIT
make clean
make all
cd $CMDSRV
make clean
make all

#CLASSIC/TDB
cd $TDBS
make clean
make mpapi
make all

#
# build java system
#

#utils
cd $JAVANODE/org.yafra.utils
ant all

#core
if [ ! -f $YAFRACORE/$CAYCONFIG ]
then
	cp $YAFRACORE/$CAYSRCCONFIG $YAFRACORE/$CAYCONFIG
fi
cd $YAFRACORE
ant all

#
cd $JAVANODE/org.yafra.server.directclient
ant all

#
cd $JAVANODE/org.yafra.server.ejb-openejb
ant

#jee server
cd $JAVANODE/org.yafra.server.jee
ant

#wicket ui
mkdir -p $JAVANODE/org.yafra.wicket/WebContent/WEB-INF/lib
cd $JAVANODE/org.yafra.wicket
ant

#
#print versions of binaries 
#
$YAFRAEXE/pswhat $YAFRAEXE/mpdbi

#create tar bundle for download
cp $YAFRACLASSES/org.yafra* $WORKNODE/classes/
tar cvfz $WORKNODE/yafra-$TIMESTAMP.tar.gz $WORKNODE/bin/ $WORKNODE/libs/  $WORKNODE/classes/

exit
