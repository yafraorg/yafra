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
# Author:       Administrator
#
# Purpose:      build rcp client
#------------------------------------------------------------------------

TOMEEDIR=../../../../apache-tomee-webprofile-1.5.1/lib

test -d $WORKNODE/apps/yafrarcp || mkdir $WORKNODE/apps/yafrarcp

# copy run time libraries used by yafra rcp client
# yafra jars
cp $YAFRACLASSES/org.yafra.utils.jar $BASENODE/org.yafra.rcp/libs/
cp $YAFRACLASSES/org.yafra.server.coreclient.jar $BASENODE/org.yafra.rcp/libs/
cp $YAFRACLASSES/org.yafra.server.ejbstubs.jar $BASENODE/org.yafra.rcp/libs/

# 3rd party jars
cp $YAFRACLASSES/commons-logging-1.1.1.jar $BASENODE/org.yafra.rcp/libs/
cp $YAFRACLASSES/log4j-1.2.17.jar $BASENODE/org.yafra.rcp/libs/
cp $TOMEEDIR/javaee-api-6.0-4-tomcat.jar $BASENODE/org.yafra.rcp/libs/
cp $TOMEEDIR/openejb-client-4.5.1.jar $BASENODE/org.yafra.rcp/libs/
cp $TOMEEDIR/openejb-core-4.5.1.jar $BASENODE/org.yafra.rcp/libs/


# call build and product creation
#./makeproduct.sh
