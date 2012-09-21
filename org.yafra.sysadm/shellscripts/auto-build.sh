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
LOGFILEADM=/tmp/YAFRA-buildadmin-$TIMESTAMP.log
LOGFILE=/tmp/YAFRA-build-$TIMESTAMP.log
echo "-> start auto build with basenode $BASENODE" > $LOGFILEADM
echo "settings:" >> $LOGFILEADM
echo "TIMESTAMP: $TIMESTAMP" >> $LOGFILEADM
echo "LOGFILE: $LOGFILE" >> $LOGFILEADM

# get newest source via git pull without pwd

# save stdout and stderr
echo "start makerelease now see logfile $LOGFILE" >> $LOGFILEADM
$SYSADM/defaults/scripts/makerelease.sh > $LOGFILE 2>&1
echo "build done" >> $LOGFILEADM

exit
