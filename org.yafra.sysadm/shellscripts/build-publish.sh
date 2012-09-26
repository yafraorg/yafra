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
# Author:        yafra
#
# Purpose:      publish release
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
TDBINSTDIR=/usr/local
if [ ! -d $TDBINSTDIR ]
then
	echo "error: deployment directory not available, exit now - create first !"
	exit
fi
BINDIR=$TDBINSTDIR/bin
ETCDIR=$TDBINSTDIR/etc
LIBSDIR=$TDBINSTDIR/lib
GUIINSTALL=$ETCDIR/tdb
APPDIR=$TDBINSTDIR/apps
echo "-> start publish with basenode $BASENODE"
echo "TIMESTAMP: $TIMESTAMP"

#
# tar release
#

#create tar bundle for download
tar cvfz $WORKNODE/yafra-$TIMESTAMP.tar.gz $WORKNODE/bin/ $WORKNODE/libs/  $WORKNODE/classes/ $WORKNODE/apps/
tar cvfz $WORKNODE/yafra-3rdparty-jars-$TIMESTAMP.tar.gz /work/classes/



