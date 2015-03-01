#!/bin/sh
#
# docker run script
#
# variables must be set by CI service
# setup local environment first https://github.com/yafraorg/yafra/wiki/Development-Environment
export BASENODE=/work/repos/yafra
export YAPKI=$BASENODE/org.yafra.yapki
export WWWDIR=/var/www/html
export WORKNODE=/work/yafra-runtime
test -d $WORKNODE/bin || mkdir -p $WORKNODE/bin

echo "setup client"
cd $YAPKI
cd www
npm update
node_modules/.bin/bower --allow-root update
cp -r * $WWWDIR

echo "setup server"
cd $YAPKI
cp cgi/*.pl /usr/lib/cgi-bin/
sudo service apache2 start

echo "done - running now YAPKI under nginx/perl/python with admin scripts under /usr/local/bin"
