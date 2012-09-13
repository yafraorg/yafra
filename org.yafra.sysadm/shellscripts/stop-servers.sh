#!/bin/sh
#
#  Copyright 2002 yafra.org
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
# stop servers
#
DERBY_HOME=/work/db-derby-10.8.2.2-bin
TOMEE_HOME=/work/apache-tomee-webprofile-1.0.0
#export CATALINA_HOME=/opt/openreports-tomcat/tomcat

echo "stoping servers"

$TOMEE_HOME/bin/shutdown.sh
#$DERBY_HOME/bin/stopNetworkServer
#/opt/openejb-3.1.2/bin/openejb stop
#/opt/geronimo-tomcat7-javaee6-3.0-M1/bin/shutdown
