#!/bin/bash
export WORKDIR=/work/repos

#
# function update git (pull)
#
function updategit {
	echo "Changing to $1 and update git"
	if [ ! -d "$WORKDIR/$1" ]; then
		# Control will enter here if $DIRECTORY doesn't exist.
		echo "YAFRA - cloning $1"
		git clone https://github.com/yafraorg/$1
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
updategit docker-yafrabase
updategit docker-yafrac
updategit docker-yafraepg
updategit docker-yafrajava
updategit docker-yafranodejs
updategit docker-yafraphp
updategit docker-yafratv
updategit docker-yapki
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
updategit yafra-toroam
updategit yapki
