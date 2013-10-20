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
# Purpose:      automatic nightly build
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
	echo "missing arguments 1 mysql/derby/mssql/oracle (2 reset - optional reset of git / or servername)"
	exit
fi


#
# settings
#
TIMESTAMP="$(date +%y%m%d)"
LOGFILE=/tmp/YAFRA-buildghost-$TIMESTAMP.log
echo "-> start auto ghost build with basenode $BASENODE" > $LOGFILE
echo "settings:" >> $LOGFILE
echo "TIMESTAMP: $TIMESTAMP" >> $LOGFILE
echo "LOGFILEADM: $LOGFILEADM" >> $LOGFILE
echo "LOGFILE: $LOGFILE" >> $LOGFILE

# get newest source via git pull without pwd
if [ "$2" = "reset" ]; then
	echo "reset source now" >> $LOGFILE
	cd $BASENODE >> $LOGFILE 2>&1
	cd .. >> $LOGFILE 2>&1
	rm -rf YafraLocalGit/ >> $LOGFILE 2>&1
	git clone https://github.com/yafraorg/yafra.git YafraLocalGit >> $LOGFILE 2>&1
fi
cd $BASENODE >> $LOGFILE 2>&1
git pull >> $LOGFILE 2>&1

# init build
echo "init build" >> $LOGFILE
$SYSADM/shellscripts/build-init.sh >> $LOGFILE 2>&1
echo "init done" >> $LOGFILE

# create development db
echo "create dev db now" >> $LOGFILE
if [ "$2" = "reset" ]; then
	$SYSADM/shellscripts/build-db.sh dev $1 setupdb >> $LOGFILE 2>&1
else
	$SYSADM/shellscripts/build-db.sh dev $1 $2 >> $LOGFILE 2>&1
fi
echo "build done" >> $LOGFILE

# build
echo "build" >> $LOGFILE
$SYSADM/shellscripts/build-apps.sh >> $LOGFILE 2>&1
echo "build done" >> $LOGFILE

sudo ldconfig

# test
echo "test" >> $LOGFILE
if [ "$2" = "reset" ]; then
	$SYSADM/shellscripts/build-test.sh >> $LOGFILE 2>&1
else
	$SYSADM/shellscripts/build-test.sh $2 >> $LOGFILE 2>&1
fi
echo "test done" >> $LOGFILE

echo "ghost build done" >> $LOGFILE

exit
