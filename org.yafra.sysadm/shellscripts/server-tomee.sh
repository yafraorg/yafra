#!/bin/sh
#
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
#
# start tomee
#
if [ -z "$1" ]; then
	echo "missing arguments 1) start stop 2) TOMEE location"
	exit
fi

TOMEE_HOME=/work/apache-tomee-webprofile-1.5.2
if [ -n "$2" ]; then
	TOMEE_HOME="$2"
fi
export TOMEE_HOME

if [ "$1" = "start" ]; then
	echo "starting tomee in path $TOMEE_HOME"
	$TOMEE_HOME/bin/startup.sh run
else
	echo "stoping tomee in path $TOMEE_HOME"
	$TOMEE_HOME/bin/shutdown.sh
fi
sleep 4


# openejb standalone
#/opt/openejb-3.1.2/bin/openejb start &
#/opt/openejb-3.1.2/bin/openejb deploy classes/org.yafra.server.ear-openejb.ear

