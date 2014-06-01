#!/bin/sh
#-------------------------------------------------------------------------------------------
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
#-------------------------------------------------------------------------------------------
# Author:       yafra
#
# Purpose:     build step 1: init build environment
#
# Sequence: build-init, build-db, build-apps, build-install, build-test, build-publish
#-------------------------------------------------------------------------------------------

#
# make sure the generic profile is loaded - run as user !!
#
if [ ! -d $SYSADM/defaults ]
then
	echo "Environment not loaded - install first !"
	exit
fi

VERREL="$YAFRAVER.$YAFRAREL"
TIMESTAMP="$(date +%y%m%d)"

#
# delete working dirs and create a new one
#
echo "delete and create working directories"
if [ -d $WORKNODE ]
then
	rm -rf $WORKNODE
fi

#
# create dirs
#
mkdir -p $WORKNODE
mkdir -p $YAFRADOC
mkdir -p $YAFRAMAN
mkdir -p $YAFRAEXE
mkdir -p $YAFRALIBPATH
mkdir -p $YAFRALIBSO
test -d $TDBO || mkdir $TDBO
test -d $CMDSRVO || mkdir $CMDSRVO
test -d $PSWHATO || mkdir $PSWHATO
test -d $PSEDITO || mkdir $PSEDITO
test -d $TESTSUITEO || mkdir $TESTSUITEO
test -d $WORKNODE/apps || mkdir $WORKNODE/apps
test -d $WORKNODE/yafra-dist || mkdir $WORKNODE/yafra-dist
test -d $YAFRACLASSES || mkdir $YAFRACLASSES

#
# clean maven
#
cd $BASENODE
mvn clean

