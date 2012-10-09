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
# Purpose:      kill running process
#-------------------------------------------------------------------------------

if test $# -lt 1
	then echo usage: $0 processname ...
else
	for i in `ps -e | grep $1 | awk '{ printf "%06d%s ",$1,$4 }'`
	do
		PID=`echo $i | cut -c1-6 | awk '{ printf "%d",$1 }'`
		NAME=`echo $i | cut -c7-78` 
 		if test -n $PID 2>/dev/null
		then
			echo killing $NAME pid $PID
			kill -9 $PID
		fi
	done
fi