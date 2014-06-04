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
# Purpose:      build step 3: make a release of exe's and libraries and tag source with it
#
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
VERREL="$YAFRAVER.$YAFRAREL"
echo "-> settings for release $VERREL with basenode $BASENODE on $TIMESTAMP"
#
echo "yafra java server core"
YAFRACORE=$JAVANODE/org.yafra.server.core
echo "YAFRACORE: $YAFRACORE"
#
echo "OSAHRED: $OSHARED and ODEBUG: $ODEBUG"

#
#CLASSIC/ANSIC
#
cd $YAFRALIBS
#make clean
make all
cd psipc/testsuite/psserver
#make clean
make all
cd ../psclient-cons
#make clean
make all
cd ../fork
#make clean
make all
cd $YAFRALIBS/pssys/testsuite/datetime
#make clean
make all
cd ../logging
#make clean
make all
cd ../chars
#make clean
make all
if [ "$PS_OS" = "ps_cygwin" ]; then
	cd $PSMATRIXLIB
	make clean
	make all
fi

#CLASSIC/ADDONS
cd $PSWHAT
#make clean
make all
cd $PSEDIT
#make clean
make all
cd $CMDSRV
#make clean
make all

#CLASSIC/TDB
cd $TDBS
#make clean
make mpapi
make all

if [ "$PS_COMPTYPE" = "ps_unix" ]; then
	if [ "$PS_OS" != "ps_cygwin" ]; then
		if [ "$PS_OS" != "ps_osx" ]; then
			cd $WORKNODE/libs
			symlinks -c .
		fi
	fi
fi


#MONO/.NET / TDB
if [ "$PS_OS" != "ps_osx" ]; then
	cd $BASENODE/org.yafra.tdb.csharp/common
	make all
	cd $BASENODE/org.yafra.tdb.csharp/tdbadmin
	make all
fi


#copy python app to worknode
test -d $WORKNODE/apps/tdbpyadmin || mkdir $WORKNODE/apps/tdbpyadmin
cp $BASENODE/org.yafra.tdb.admin-ui/* $WORKNODE/apps/tdbpyadmin/
#copy perl db admin to worknode
test -d $WORKNODE/apps/tdbdbadmin || mkdir $WORKNODE/apps/tdbdbadmin
cp $BASENODE/org.yafra.tdb.setup/db/tdb*pl $WORKNODE/apps/tdbdbadmin
cp $BASENODE/org.yafra.tdb.setup/db/tdbdb.pm $WORKNODE/apps/tdbdbadmin


#
# build java system
#

# maven build - build all and run some extras afterwards
cd $JAVANODE
mvn install
# yafra java core
cd $BASENODE/org.yafra.server.core/target
cp *.jar $WORKNODE/apps
# yafra java J2EE wicket and cxf
cd $BASENODE/org.yafra.server.jee/target
cp *.war $WORKNODE/apps
cp *.jar $WORKNODE/bin
# yafra java EJB3
cd $BASENODE/org.yafra.server.ejb/target
cp *client.jar $WORKNODE/apps
cd $BASENODE/org.yafra.server.ejb-war/target
cp *.war $WORKNODE/apps

#gwt
cd $JAVANODE/org.yafra.gwt.admin
ant war

#rcp
cd $JAVANODE/org.yafra.rcpbuild
./build-rcp.sh

#copy python yafra app to worknode
test -d $WORKNODE/apps/yafrapython || mkdir $WORKNODE/apps/yafrapython
cp -R $BASENODE/org.yafra.python/* $WORKNODE/apps/yafrapython

#copy python yafra flask app to worknode
test -d $WORKNODE/apps/yafrapythonflask || mkdir $WORKNODE/apps/yafrapythonflask
cp -R $BASENODE/org.yafra.python.flask/* $WORKNODE/apps/yafrapythonflask

#compile GAE python - org.yafra.gae.python
echo "TODO: compile the google appengine python app"

#copy nodejs yafra app
test -d $WORKNODE/apps/yafranodejs || mkdir $WORKNODE/apps/yafranodejs
cp -R $BASENODE/org.yafra.nodejs/* $WORKNODE/apps/yafranodejs

#copy php yafra app to worknode
test -d $WORKNODE/apps/yafraphp || mkdir $WORKNODE/apps/yafraphp
cp -R $BASENODE/org.yafra.phpslim/* $WORKNODE/apps/yafraphp

#copy perl catalyst yafra app to worknode
test -d $WORKNODE/apps/yafraperl || mkdir $WORKNODE/apps/yafraperl
cp -R $BASENODE/org.yafra.perl/* $WORKNODE/apps/yafraperl

#compile mobile app
echo "TODO: compile the mobile app"

# create doxygen documentation from source
echo "running doxygen now"
cd $BASENODE
doxygen

exit
