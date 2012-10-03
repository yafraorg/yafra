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
	for dick in $*
		do golly=`ps -e | fgrep $dick | awk '{print $1}'`
 		   if test -n $golly 2>/dev/null
		   then
			echo killing $dick pid $golly
			kill -9 $golly
		   else
			echo no process $dick
		  fi
		done
fi