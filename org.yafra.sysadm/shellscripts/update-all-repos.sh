#!/usr/bin/env bash
#
#  Copyright 2016 yafra.org
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
#
# boot to other os on other partition
export WORKDIR=/work/repos

#
# function update git (pull)
#
function updategit {
	echo "Changing to $1 and update git"
	if [ ! -d "$WORKDIR/$1" ]; then
		# Control will enter here if $DIRECTORY doesn't exist.
		echo "YAFRA - cloning $1"
		cd $WORKDIR
		git clone https://github.com/yafraorg/$1.git

	else
		cd "$WORKDIR/$1"
		echo "YAFRA - pull $1"
		pwd
		git status
		git pull
	fi
	cd $WORKDIR
}

#
# main
#
updategit closedprojects
updategit clubmanagement
updategit pax
updategit docker-yafrabase
updategit docker-yafradb
updategit docker-yafrac
updategit docker-yafraepg
updategit docker-yafrajava
updategit docker-yafranodejs
updategit docker-yafraphp
updategit docker-yafratv
updategit docker-yapki
updategit docker-arm-yafrabase
updategit docker-arm-yafranodejs
updategit docker-arm-yapki
updategit docker-arm-yafraproxy
updategit docker-arm-yafradb
updategit ionictests
updategit yafra
updategit yafra-archive
updategit yafra-database
updategit yafra-java
updategit yafra-mobile
updategit yafra-nodejs
updategit yafra-php
updategit yafra-tdb-c
updategit yafra-tdb-csharp
updategit yafra-tdb-python
updategit yafra-toroam
updategit yapki
updategit yafra.wiki

echo ==================================
echo DONE with update
echo ==================================

echo git clone https://github.com/webernissle/sagetv

echo do a rebase now:
echo cd sagetv
echo git status
echo git pull
echo git remote add upstream https://github.com/google/sagetv.git
echo git fetch upstream
echo git rebase upstream/master
echo git push origin master

echo done
