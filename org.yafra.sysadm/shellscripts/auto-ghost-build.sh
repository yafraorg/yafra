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
#-------------------------------------------------------------------------------

#
# make sure the generic profile is loaded and you have enough permissions!!
#
if [ ! -d $SYSADM/defaults ]
then
	echo "Environment not loaded - install first !" > $LOGFILEADM
	exit
fi

#
# settings
#
TIMESTAMP="$(date +%y%m%d)"
LOGFILE=$WORKNODE/YAFRA-buildghost-$TIMESTAMP.log
LOGFILEADM=$WORKNODE/YAFRA-buildghostadmin-$TIMESTAMP.log
echo "-> start auto ghost build with basenode $BASENODE" > $LOGFILEADM
echo "settings:" >> $LOGFILEADM
echo "TIMESTAMP: $TIMESTAMP" >> $LOGFILEADM
echo "LOGFILEADM: $LOGFILEADM" >> $LOGFILEADM
echo "LOGFILE: $LOGFILE" >> $LOGFILEADM

# get newest source via git pull without pwd
echo "reset source now" >> $LOGFILEADM
cd $BASENODE >> $LOGFILEADM 2>&1
cd .. >> $LOGFILEADM 2>&1
rm -rf YafraLocalGit/ >> $LOGFILEADM 2>&1
git clone https://github.com/yafraorg/yafra.git YafraLocalGit >> $LOGFILEADM 2>&1

# build
echo "start makerelease now see logfile $LOGFILE" >> $LOGFILEADM
$SYSADM/shellscripts/auto-build.sh > $LOGFILE 2>&1
echo "build done" >> $LOGFILEADM

# install
echo "start install now see logfile $LOGFILE" >> $LOGFILEADM
$SYSADM/shellscripts/install-build.sh > $LOGFILE 2>&1
echo "install done" >> $LOGFILEADM

# test
echo "start test now see logfile $LOGFILE" >> $LOGFILEADM
$SYSADM/shellscripts/test-build.sh > $LOGFILE 2>&1
echo "test done" >> $LOGFILEADM

echo "ghost build done" >> $LOGFILEADM

exit
