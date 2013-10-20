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
echo "OSAHRED: $OSHARED and ODEBUG: $ODEBUG"

rm $YAFRAEXE/*
rm $YAFRALIBPATH/*
rm $YAFRALIBSO/*
rm $TDBO/*
rm $CMDSRVO/*
rm $PSWHATO/*
rm $PSEDITO/*
rm $TESTSUITEO/*

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
make all
#make mpapi
#make alllibs
#make allact

if [ "$PS_COMPTYPE" = "ps_unix" ]; then
	if [ "$PS_OS" != "ps_cygwin" ]; then
		cd $WORKNODE/libs
		symlinks -c .
	fi
fi

sudo ldconfig

exit
