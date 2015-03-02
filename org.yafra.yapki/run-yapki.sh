#!/bin/sh
#-------------------------------------------------------------------------------
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
# (c) yafra.org, 2002, Switzerland
#
#-------------------------------------------------------------------------------
#
# docker run script
#

# variables must be set by CI service
# setup local environment first https://github.com/yafraorg/yafra/wiki/Development-Environment
export BASENODE=/work/repos/yafra
export YAPKI=$BASENODE/org.yafra.yapki
export WWWDIR=/var/www/html
export WORKNODE=/work/yafra-runtime
export PKINODE=/data/pki
test -d $WORKNODE/bin || mkdir -p $WORKNODE/bin
test -d $PKINODE || mkdir -p $PKINODE

echo "setup client"
cd $YAPKI
cd www
npm update
node_modules/.bin/bower --allow-root update
cp -r * $WWWDIR

echo "setup openssl"
cd $PKINODE
mkdir yapki
mkdir yapki/certs
mkdir yapki/crl
mkdir yapki/newcerts
mkdir yapki/private
cd $YAPKI/pki
cp * $PKINODE

echo "setup server"
cd $YAPKI
cp cgi/*.pl /usr/lib/cgi-bin/
sudo service apache2 start

mkdir /work/ssl-rest
cp $YAPKI/backend/* /work/ssl-rest
cd /work/ssl-rest
pip install -r requirements.txt

echo "done - running now YAPKI under nginx/perl/python with admin scripts under /usr/local/bin"
