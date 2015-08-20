#!/bin/bash

#
# function update git (pull)
#
function updategit {
	echo "Changing to $1 and update git"
	cd "$1"
	pwd
	git status
	git pull
}

#
# main
#
updategit /work/repos/closedprojects
updategit /work/repos/clubmanagement
updategit /work/repos/docker-yafrabase
updategit /work/repos/docker-yafratv
updategit /work/repos/docker-yafraepg
updategit /work/repos/yafra
updategit /work/repos/yafra-database
updategit /work/repos/yafra-java
updategit /work/repos/yafra-mobile
updategit /work/repos/yafra-nodejs
updategit /work/repos/yafra-nodejsmean
updategit /work/repos/yafra-php
updategit /work/repos/yafra-python
updategit /work/repos/yafra-tdb-c
updategit /work/repos/yafra-tdb-csharp
updategit /work/repos/yapki
