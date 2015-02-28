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
test -d $WORKNODE/apps || mkdir -p $WORKNODE/apps

echo "download latest build and make it available as tomcat webapp"
# issues, tomcat users, ports and database type and config of cayenne
cd $WORKNODE
#curl -O -u ftp://ftp.yafra.org/yafra-java-build.tar.gz
#tar xvfz yafra-java-build.tar.gz
# copy to tomcat


echo "done - running now YAPKI under nginx/perl/python with admin scripts under /usr/local/bin"
