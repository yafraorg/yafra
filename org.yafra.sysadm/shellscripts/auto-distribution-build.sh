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
# Purpose:      automatic distribution build
# Arguments: 1: "database type (mysql, mssql, oracle, derby)" 2: "reset" (reset local git repo)
#-------------------------------------------------------------------------------

#
# make sure the generic profile is loaded and you have enough permissions!!
#
if [ ! -d $SYSADM/defaults ]
then
	echo "Environment not loaded - install first !" > $LOGFILEADM
	exit
fi

if [ -z "$1" ]; then
	echo "missing arguments 1 dev/rel 2 mysql/derby/mssql/oracle"
	exit
fi


#
# settings
#
TIMESTAMP="$(date +%y%m%d)"
LOGFILE=/tmp/YAFRA-buildghost-$TIMESTAMP.log
LOGFILEADM=/tmp/YAFRA-buildghostadmin-$TIMESTAMP.log
echo "-> start auto distribution build with basenode $BASENODE" > $LOGFILEADM
echo "settings:" >> $LOGFILEADM
echo "TIMESTAMP: $TIMESTAMP" >> $LOGFILEADM
echo "LOGFILEADM: $LOGFILEADM" >> $LOGFILEADM
echo "LOGFILE: $LOGFILE" >> $LOGFILEADM

# set environment to build distribution - no debug, correct build settings
if [ "$PS_OS" = "ps_cygwin" ]; then
	export OSHARED=
	export ODEBUG=
else
	export OSHARED=1
	export ODEBUG=
fi

if [ "$1" = "mysql" ]; then
	export TDBMYSQL=1
fi
if [ "$1" = "mssql" ]; then
	#export TDBMSSQL=1
	export TDBODBC=1
fi
if [ "$1" = "oracle" ]; then
	export TDBORACLE=1
	#export TDBORACLECLASSIC=1
fi

# get newest source via git pull without pwd
if [ "$2" = "reset" ]; then
	echo "reset source now" >> $LOGFILEADM
	cd $BASENODE >> $LOGFILEADM 2>&1
	cd .. >> $LOGFILEADM 2>&1
	rm -rf YafraLocalGit/ >> $LOGFILEADM 2>&1
	git clone https://github.com/yafraorg/yafra.git YafraLocalGit >> $LOGFILEADM 2>&1
fi
cd $BASENODE >> $LOGFILEADM 2>&1

# init build
echo "init build" >> $LOGFILEADM
$SYSADM/shellscripts/build-init.sh > $LOGFILE 2>&1
echo "init done" >> $LOGFILEADM

# create release note
echo "yafra release $YAFRAVER.$YAFRAREL" > $WORKNODE/yafra-dist/RELEASE.txt
echo "\n" >> $WORKNODE/yafra-dist/RELEASE.txt
echo "distribution release build on $TIMESTAMP" >> $WORKNODE/yafra-dist/RELEASE.txt
echo "distribution target OS: $PS_OS and DB: $1" >> $WORKNODE/yafra-dist/RELEASE.txt
echo "\n" >> $WORKNODE/yafra-dist/RELEASE.txt
echo "https://github.com/yafraorg/yafra/wiki/Release" >> $WORKNODE/yafra-dist/RELEASE.txt


# set db
echo "create rel $1 db now" >> $LOGFILEADM
$SYSADM/shellscripts/build-db.sh rel $1 >> $LOGFILE 2>&1
echo "build done" >> $LOGFILEADM

# build
echo "build" >> $LOGFILEADM
$SYSADM/shellscripts/build-apps.sh >> $LOGFILE 2>&1
echo "build done" >> $LOGFILEADM

# publish build
echo "publish build" >> $LOGFILEADM
$SYSADM/shellscripts/build-publish.sh $1 >> $LOGFILE 2>&1
echo "publish done" >> $LOGFILEADM

echo "distribution build done" >> $LOGFILEADM

exit
