#!/bin/sh
#
# docker run script
#
export BASENODE=/work/repos/yafra
export YAPKI=$BASENODE/org.yafra.yapki

echo "update git"
cd $YAPKI
git pull

echo "setup yapki"
./run-yapki.sh

echo "done - run-docker"
