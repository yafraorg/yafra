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
# Purpose:      make a release of exe's and libraries and tag source with it
# Arguments: 1: dev/rel
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
echo "java classes for yafra project"
YAFRACLASSES=/work/classes
echo "YAFRACLASSES: $YAFRACLASSES"
#
echo "set c flags for compile"
if [ "$1" = "dev"]; then
	export OSHARED=
	export ODEBUG=1
else
	export OSHARED=1
	export ODEBUG=
fi
echo "OSAHRED: $OSHARED and ODEBUG: $ODEBUG"

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

if [ "$PS_COMPTYPE" = "ps_unix" ]; then
	if [ "$PS_COMPTYPE" != "ps_cygwin" ]; then
		cd $WORKNODE/libs
		symlinks -c .
	fi
fi


#MONO/.NET / TDB
cd $BASENODE/org.yafra.tdb.csharp/common
make all
cd $BASENODE/org.yafra.tdb.csharp/tdbadmin
make all


#copy python app to worknode
test -d $WORKNODE/apps/tdbpyadmin || mkdir $WORKNODE/apps/tdbpyadmin
cp $BASENODE/org.yafra.tdb.admin-ui/main/* $WORKNODE/apps/tdbpyadmin/
#copy perl db admin to worknode
test -d $WORKNODE/apps/tdbdbadmin || mkdir $WORKNODE/apps/tdbdbadmin
cp $BASENODE/org.yafra.tdb.setup/db/tdb*pl $WORKNODE/apps/tdbdbadmin
cp $BASENODE/org.yafra.tdb.setup/db/tdbdb.pm $WORKNODE/apps/tdbdbadmin


#
# build java system
#

#utils
cd $JAVANODE/org.yafra.utils
ant all

#core
cd $YAFRACORE
ant all

#directclient
cd $JAVANODE/org.yafra.server.directclient
ant all

#ejb
cd $JAVANODE/org.yafra.server.ejb-openejb
ant

#jee server
cd $JAVANODE/org.yafra.server.jee
ant

#wicket ui
mkdir -p $JAVANODE/org.yafra.wicket/WebContent/WEB-INF/lib
cd $JAVANODE/org.yafra.wicket
ant

#gwt

#rcp

#test as jar exe
cd $JAVANODE/org.yafra.tests.utils
ant deploy
cd $JAVANODE/org.yafra.tests.serverdirectclient
ant deploy
cd $JAVANODE/org.yafra.tests.serverejb3
ant deploy
#cd $JAVANODE/org.yafra.tests.wsclient
#ant deploy

cp $YAFRACLASSES/org.yafra* $WORKNODE/classes/

#copy python yafra app to worknode
test -d $WORKNODE/apps/yafrapadmin || mkdir $WORKNODE/apps/yafrapadmin
cp $BASENODE/org.yafra.padmin/main/Main.py $WORKNODE/apps/yafrapadmin

exit