#!/bin/sh
#
# docker run script
#
# variables must be set by CI service
# setup local environment first https://github.com/yafraorg/yafra/wiki/Development-Environment
export BASENODE=/work/repos/yafra
export YAPKI=$BASENODE/org.yafra.yapki
export WWWDIR=/usr/share/nginx/html
export WORKNODE=/work/yafra-runtime
test -d $WORKNODE/bin || mkdir -p $WORKNODE/bin

echo "download latest build and make it available as nginx webapp"
cd $YAPKI
ll



echo "done - running now YAPKI under nginx/perl/python with admin scripts under /usr/local/bin"
